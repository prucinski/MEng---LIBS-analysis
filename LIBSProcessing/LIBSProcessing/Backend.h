#pragma once


using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
/*
* Class handling the backend functions of the entire programme. That includes:
* -opening files after UI has provided this class a list of filenames.
* -converting said files into a data format processable by the programme.
* -storing the selected peaks, as well as the database in memory.
* -saving information to a file.
* 
*/

//how many datapoints are there?
#define DATASIZE 26607
#define LINESTOSKIP 105

public ref class Backend {



public:
	String^ directory;
	String^ nameOfFile;
	List<String^>^ filesToExtract;
	List<Dictionary<float, float>^>^ listOfDictionaries;		//dictionary has O(1) access time when passed the key. Holds all files.
	Dictionary<float, float>^ result;							//summed dictionary of provided files.
	List<float>^ indexedKeys;									//Indexing the keys in the dictionary for easy sequential access.
	Dictionary<float, float>^ presentToUserResult;				//Final-final result that is saved to the computer.
	List<float>^ selectedWavelengths;							//A list of floats that the user selected for processing.
	List<float>^ userSelectionsToKeys;							//A list which holds the user selections, but as keys that can be used with dictionaries.
	List<int>^ userSelectionsIndexes;							//As dictionaries are unsorted, we need to keep track of the indexes as well.

	
	//Calibration mode variables.
	List<String^>^ filesToExtract_B;
	List<Dictionary<float, float>^>^ listOfDictionaries_B;
	List<float>^ divisionAcrossA;								// divisions of two wavelengths across files.
	List<float>^ divisionAcrossB;
	float avgA, avgB;											//average values of two lists above.


	Backend() {
		directory = Application::StartupPath;
		//for now.
		nameOfFile = "default.csv";
		//initialize the (now empty) dynamically allocated array.
		selectedWavelengths = gcnew List<float>();
	}


	int saveToFile(String^ name, bool selectedOnly) {
		//see if user put in any input; if not, do a default
		if (name) {
			nameOfFile = "\\"+name;
		}
		else {
			nameOfFile = "\\"+System::DateTime::Now.ToString("dd_MM_hhmm");
		}
		if (!name->EndsWith(".csv")) {
			nameOfFile = nameOfFile + ".csv";
		}

		Dictionary<float, float>^ whatToSave = selectedOnly ? presentToUserResult : result;
		StreamWriter^ sw;
		try {
			sw = gcnew StreamWriter(directory + nameOfFile);
		}
		catch (...) {
			return 0;
		}
		//loop through all the keys
		try {//TODO: this try-catch block doesn't work. I have no clue why.
			for each (float key in whatToSave->Keys) {
				sw->Write(Convert::ToString(key));
				sw->Write(',');
				sw->Write(Convert::ToString(result[key]));
				sw->Write('\n');
			}
		}
		catch (...) {
			//data structure not initialized
			return -1;
		}
		sw->Close();
		return 1;
	}
	int saveToFileCalibration(String^ name, String^ analyteA, String^ analyteB) {
		if (name) {
			nameOfFile = "\\" + name;
		}
		else {
			nameOfFile = "\\" + System::DateTime::Now.ToString("dd_MM_hhmm");
		}
		if (!name->EndsWith(".csv")) {
			nameOfFile = nameOfFile + ".csv";
		}
		StreamWriter^ sw;
		try {
			sw = gcnew StreamWriter(directory + nameOfFile);
		}
		catch (...) {
			return 0;
		}
		//write the header of the excel file.
		try {

			sw->Write("Divisions for acquisitions A, Average division value A, Concentration (ppm) A, dividend A, divisor A,");
			sw->Write("Divisions for acquisitions B, Average division value B, Concentration (ppm) B,dividend B, divisor B\n");
			//write the first row of the data.
			sw->Write(Convert::ToString(divisionAcrossA[0])); sw->Write(",");
			sw->Write(Convert::ToString(avgA)); sw->Write(",");
			sw->Write(analyteA + ",");
			sw->Write(Convert::ToString(userSelectionsToKeys[0])), sw->Write(",");
			sw->Write(Convert::ToString(userSelectionsToKeys[1])); sw->Write(",");  //first row for A complete

			sw->Write(Convert::ToString(divisionAcrossB[0])); sw->Write(",");
			sw->Write(Convert::ToString(avgB)); sw->Write(",");
			sw->Write(analyteB + ",");
			if (userSelectionsToKeys->Count != 2) { sw->Write(Convert::ToString(userSelectionsToKeys[2])); }
			else { sw->Write(Convert::ToString(userSelectionsToKeys[0])); }
			sw->Write(",");
			if (userSelectionsToKeys->Count != 2) { sw->Write(Convert::ToString(userSelectionsToKeys[3])); }
			else { sw->Write(Convert::ToString(userSelectionsToKeys[1])); }
			sw->Write("\n");
		}
		catch (...) {
			//Data structures not initialized yet.
			return -1;
		}

		//write the remaining rows of data.
		int i = 1;
		while (i < divisionAcrossA->Count || i < divisionAcrossB->Count) {
			if (i < divisionAcrossA->Count) {
				sw->Write(Convert::ToString(divisionAcrossA[i]));
			}
			sw->Write(",,,,,");
			if (i < divisionAcrossB->Count) {
				sw->Write(Convert::ToString(divisionAcrossB[i]));
			}
			sw->Write(",,,,\n");
			i++;
		}



		sw->Close();


		return 1;
	}

	int loadFiles(array<String^>^ fileNames, float cutoff, int whichDictionary) {
		List<String^>^ files;
		if (whichDictionary == 1) {
			//reinitialize the arrays each time.
			filesToExtract = gcnew List<String^>();
			//point to the relevant array.
			files = filesToExtract;
		}
		else if(whichDictionary == 2){
			filesToExtract_B = gcnew List<String^>();
			files = filesToExtract_B;
		}
		else {
			//this should never be reached.
			files = gcnew List<String^>();
			return 0;
		}
		for each (String^ filename in fileNames) {
			if (filename->EndsWith(".asc")) {
				files->Add(filename);
			}
			else {
				return 0;
			}
		}
		return initializeMemoryFiles(cutoff, whichDictionary);

	}

	//function to be called by the UI to process the dictionary as per our selected wavelengths.
	//option values:	1 - find highest peak within range
	//					2 - sum all datapoints within range
	int getRequestedSpectraStandardMode(int option, float range) {
		//first, keys CLOSEST to the value that the user input must be found.
		findKeys();
		findRequestedValues(option, range);
		return 1;
	}

	int getRequestedSpectraCalibrationMode() {
		//we either ha ve just 2 values; or more than 3. Any values besides 0,1,2,3 will be discarded.
		if (selectedWavelengths->Count < 2 || selectedWavelengths->Count == 3) {
			return 0;
		}
		//first, keys CLOSEST to the value that the user input must be found.
		findKeys();
		findDivisionValues();
		return 1;
	}

	int getAveragedSpectra() {
		return sumDictionaries();
	}

	int addWavelength(float wavelength) {
		if (wavelength < 200.93 || wavelength > 1031.86) {
			return 0;
		}
		selectedWavelengths->Add(wavelength);
		return 1;
	}

	int removeWavelength(float wavelength) {
		selectedWavelengths->Remove(wavelength);
		return 1;
	}




private:
	//pass by reference. Function to pass the information from the file into a data structure.
	int processFileIntoDictionary(Dictionary<float, float>^ dict, String^ filename, float cutoff) {
		//file might be opened by another process
		StreamReader^ sr;
		try {
			sr = gcnew StreamReader(filename);
		}
		catch (...) {
			//0 - file used by another process
			return 0;
		}


		String^ line;
		array<String^>^ thisKeyValArray;
		int i = 0;

		//read file line by line.
		while (line = sr->ReadLine()){
			if (i < LINESTOSKIP) {
				i++;
				continue;
			}
			//split line into two strings
			thisKeyValArray = line->Split(',', 2);
			//and add to the dictionary.
			if (Convert::ToDouble(thisKeyValArray[1]) < cutoff) {
				dict->Add(Convert::ToDouble(thisKeyValArray[0]), 0);
			}
			else {
				dict->Add(Convert::ToDouble(thisKeyValArray[0]), Convert::ToDouble(thisKeyValArray[1]));
			}

		}
		return 1;
	}

	//function to internally extract data from files, and initialize them into RAM.
	//Overheads were considered, but overall loading 10 files, 26606 lines, each line being 2 * 4 bytes,
	//we have 10*26606 *8 = 2128480B = 2078 KiB = around 2MiB. All is good.
	//Depending on the version of the programme, data will be double instead of float, so 4MiB.

	int initializeMemoryFiles(float cutoff, int whichDictionary) {
		List<String^>^ files;
		int lengthOfListOfMaps;
		List<Dictionary<float, float>^>^ currentListOfDictionaries;
		if (whichDictionary == 1) {
			////allocating memory so that the array does not need resizing
			listOfDictionaries = gcnew List<Dictionary<float, float>^>(lengthOfListOfMaps);
			//point to the relevant array.
			currentListOfDictionaries = listOfDictionaries;
			files = filesToExtract;
			lengthOfListOfMaps = filesToExtract->Count;
		}
		else if (whichDictionary == 2) {
			listOfDictionaries_B = gcnew List<Dictionary<float, float>^>(lengthOfListOfMaps);
			currentListOfDictionaries = listOfDictionaries_B;
			files = filesToExtract_B;
			lengthOfListOfMaps = filesToExtract_B->Count;
		}
		else {
			//this should never be reached.
			currentListOfDictionaries = gcnew List<Dictionary<float, float>^>();
			return 0;
		}
		//create and populate a dictionary of data for each of the files.
		for (int i = 0; i < lengthOfListOfMaps; i++) {
			currentListOfDictionaries->Add(gcnew Dictionary<float, float>(DATASIZE - LINESTOSKIP));
			processFileIntoDictionary(currentListOfDictionaries[i], files[i], cutoff);
		}
		return 1;
	}

	//sum all our dictionaries into one resulting dictionary. This can be useful when we want to see the strongest peaks across n files.
	int sumDictionaries() {
		//Even if there was a dictionary before, garbage collect it and create a new one.
		result = gcnew Dictionary<float, float>(DATASIZE - LINESTOSKIP);
		indexedKeys = gcnew List<float>(DATASIZE - LINESTOSKIP);
		if (listOfDictionaries == nullptr) {
			return 0;
		}

		for each (float key in listOfDictionaries[0]->Keys) {
			float tempValue = 0; 
			Dictionary<float, float>^ temp;
			for (int j = 0; j < listOfDictionaries->Count; j++) {
				//it's upset when I'm doing double dereferencing. It's a good thing temp is a pointer so there is not a lot
				//of overhead; still the reassignments are taking up processor cycles
				temp = listOfDictionaries[j];
				tempValue += temp[key];
			}
			//average of n spectra.
			result->Add(key, tempValue / listOfDictionaries->Count);
			indexedKeys->Add(key);
		}
		return 1;


	}

	//find keys for user-supplied values. This was probably the trickiest part of the design to get a good time complexity.
	//It fills the dictionary that's self-contained.
	int findKeys() {
		//if (userSelectionsToKeys == nullptr) {
		//every time we process again; we reset the list - easier to handle
			userSelectionsToKeys = gcnew List<float>();
			userSelectionsIndexes = gcnew List<int>();
		//}

		for each (float wavelength in selectedWavelengths) {
			//guesstimate the index based the distances of the datapoints.
			//A line of best fit that maps index to wavelength is y = 201.96*e^(6*10^-5*x), as per Excel.
			//I have modified it slightly after manually inspecting the mappings, and the formula for loosely recovering
			//the index is presented below.
			int assumedIndex = Math::Floor(Math::Pow(10, 5) / 6.21 * Math::Log(wavelength / 200.9381));
			//now, see and compare. This is heavily amortized computationally, and will not go over more than 200 iterations for each point.
			//1.Rarest scenario. We have estimated exactly the correct key
			float tempDiff, newDiff;
			if (indexedKeys[assumedIndex] == wavelength) {
				userSelectionsToKeys->Add(wavelength);
				userSelectionsIndexes->Add(assumedIndex);
				continue;
			}
			//2. We have estmimated the key to be too large. Try a lower key one by one.
			else if (indexedKeys[assumedIndex] >= wavelength) {
				while (indexedKeys[assumedIndex] >= wavelength) {
					tempDiff = Math::Abs(indexedKeys[assumedIndex] - wavelength);
					assumedIndex -= 1;
					newDiff = Math::Abs(indexedKeys[assumedIndex] - wavelength);
				}
				//now, we are pretty much spot on. Just check whether to select assumedIndex or assumedIndex+1.
				if (tempDiff > newDiff) {
					userSelectionsToKeys->Add(indexedKeys[assumedIndex]);
					userSelectionsIndexes->Add(assumedIndex);
				}
				else {
					userSelectionsToKeys->Add(indexedKeys[assumedIndex + 1]);
					userSelectionsIndexes->Add(assumedIndex+1);
				}
				continue;
			}
			//3. We have estimated the key to be too small. Try a higher key.
			else {
				while (indexedKeys[assumedIndex] <= wavelength) {
					tempDiff = Math::Abs(indexedKeys[assumedIndex] - wavelength);
					assumedIndex += 1;
					newDiff = Math::Abs(indexedKeys[assumedIndex] - wavelength);
				}
				if (tempDiff > newDiff) {
					userSelectionsToKeys->Add(indexedKeys[assumedIndex]);
					userSelectionsIndexes->Add(assumedIndex);
				}
				else {
					userSelectionsToKeys->Add(indexedKeys[assumedIndex -1]);
					userSelectionsIndexes->Add(assumedIndex-1);
				}
				continue;
			}

		}
		//success.
		return 1;
	}

	//Find the results in a provided range.
	int findRequestedValues(int option, float range) {
		//reset the "presentToUser" dictionary.
		presentToUserResult = gcnew Dictionary<float, float>();
		float rangeEachWay = range / 2, tempResult;
		if (option == 2) { tempResult = 0;} else { tempResult = -9999; }
		float currKey;
		int index;
		int i = 0;
		for each (float key in userSelectionsToKeys) {
			index = userSelectionsIndexes[i];
			currKey = indexedKeys[index];
			//left hand side of the selected point
			while (Math::Abs(key - currKey) < rangeEachWay) {
				if (option) {
					tempResult = result[currKey] > tempResult ? result[currKey] : tempResult;
				}
				else {
					tempResult += result[currKey];
				}
				if (index == 0) { break; }
				index--;

				currKey = indexedKeys[index];
			}
			//escaped the while loop. Now do it again, but the other way. Admittedly there is redundancy in this code.
			index = userSelectionsIndexes[i];
			currKey = indexedKeys[index + 1];
			while (Math::Abs(key - currKey) < rangeEachWay) {
				if (option) {
					tempResult = result[currKey] > tempResult ? result[currKey] : tempResult;
				}
				else {
					tempResult += result[currKey];
				}
				if (index == DATASIZE - LINESTOSKIP) {break;}
				index++;
				currKey = indexedKeys[index];
			}
			//now we have found the highest value. Add to the proper result dictionary.
			if (presentToUserResult == nullptr) {
				presentToUserResult = gcnew Dictionary<float, float>();
			}
			presentToUserResult->Add(key, tempResult);
			i++;

		}
		return 1;
	}


	//find the division values and save them to an array. Function to be called after there are at least 2 
	//keys selected by the user.
	int findDivisionValues() {
		divisionAcrossA = gcnew List<float>(listOfDictionaries->Count);
		divisionAcrossB = gcnew List<float>(listOfDictionaries_B->Count);
		float divisorA, divisorB, dividendA, dividendB;
		if (userSelectionsToKeys->Count == 2) {
			divisorA = divisorB = userSelectionsToKeys[1];
			dividendA = dividendB = userSelectionsToKeys[0];
		}
		else {
			divisorA = userSelectionsToKeys[1];
			dividendA = userSelectionsToKeys[0];
			divisorB = userSelectionsToKeys[3];
			dividendB = userSelectionsToKeys[2];
		}
		float runningSum = 0, res;
		//first, handle the first dictionary.
		for each (Dictionary<float, float> ^ dict in listOfDictionaries) {
			res = dict[dividendA] / dict[divisorA];
			divisionAcrossA->Add(res);
			runningSum += res;
		}
		avgA = runningSum / listOfDictionaries->Count;
		//then the other one.
		runningSum = 0;
		for each (Dictionary<float, float> ^ dict in listOfDictionaries_B) {
			res = dict[dividendB] / dict[divisorB];
			divisionAcrossB->Add(res);
			runningSum += res;
		}
		avgB = runningSum / listOfDictionaries->Count;
		return 1;

	}
	


























};
