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

	//multi-set processing.
	List<String^>^ metadata;
	List< List<Dictionary<float, float>^>^>^ listOfSets;
	List<float>^ listOfConcentrations;
	List<float>^ listOfAverages;


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
		try {
			for each (float key in whatToSave->Keys) {
				sw->Write(Convert::ToString(key));
				sw->Write(',');
				sw->Write(Convert::ToString(result[key]));
				sw->Write('\n');
			}
		}
		catch (...) {
			//data structure not initialized
			sw->Close();
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
			/* OBSOLETE CODE - REMOVE WHEN SURE - TODO
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
			*/
			int elems = numberOfValidSets(); int whichKey = 0;
			bool differentDivisors = false;
			if (userSelectionsToKeys->Count / 2 == elems) {
				differentDivisors = true;
			}
			//write headers
			sw->Write(",Average of sums from division,");
			sw->Write("dividend,");
			sw->Write("divisor,");
			sw->Write("Concentration\n");
			for (int i = 0; i < metadata->Count; i++) {
				//coded for "no set input"
				sw->Write("S" + Convert::ToString(i + 1) + ",");
				if (listOfAverages[i] == -1) {
					sw->Write(",,,");
					continue;
				}
				sw->Write(Convert::ToString(listOfAverages[i])+",");
				if (differentDivisors) {
					sw->Write(Convert::ToString(userSelectionsToKeys[whichKey]) +",");
					sw->Write(Convert::ToString(userSelectionsToKeys[whichKey+1])+",");
					whichKey+=2;
				}
				else {
					sw->Write(Convert::ToString(userSelectionsToKeys[0])+",");
					sw->Write(Convert::ToString(userSelectionsToKeys[1])+",");
				}
				sw->Write(Convert::ToString(listOfConcentrations[i])+"\n");
			}
		}
		catch (...) {
			//Data structures not initialized yet.
			sw->Close();
			return -1;
		}

		/*OBSOLETE CODE - TO REMOVE - TODO
		* 
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
		*/



		sw->Close();


		return 1;
	}

	int loadFiles(array<String^>^ fileNames, float cutoff, int whichMode) {
		List<String^>^ files;
		if (whichMode == 1) {
			//reinitialize the arrays each time.
			filesToExtract = gcnew List<String^>();
			//point to the relevant array.
			files = filesToExtract;
		}
		else if(whichMode == 2){
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
		return initializeMemoryFiles(cutoff, whichMode);

	}

	int initializeSets(int length) {
		metadata = gcnew List <String^>(length);
		listOfSets = gcnew List< List<Dictionary<float, float>^>^>(length);
		listOfConcentrations = gcnew List<float>(length);
		listOfAverages = gcnew List<float>(length);

		for (int i = 0; i < length; i++) {
			metadata->Add(Convert::ToString(i+1)+ ". THIS SET IS EMPTY.");
			//I'd like these structures to be index-addressable after they have been initialized.
			listOfSets->Add(nullptr);
			listOfConcentrations->Add(-1);
			listOfAverages->Add(-1);

		}

		return 1;

	}

	int addSetToSets(float concentration, int index, float cutoff) {
		listOfConcentrations[index] = concentration;
		listOfSets[index] = gcnew List<Dictionary<float, float>^>();
		listOfSets[index]->AddRange(listOfDictionaries_B);
		metadata[index] = Convert::ToString(index + 1) + ".SET: " + listOfDictionaries_B->Count + " FILES, CUTOFF " +
			cutoff + ", CONT." + concentration;
		return 1;
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
		//if we have less than 1 item, discard. We will check for whether each set has it's own wavelengths later.
		if (selectedWavelengths->Count < 1) {
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

	//function to calculate the R value, after we have processed all the data files.
	float getRSquared() {
		//calculate average intensity & average concentration; all concentrations.
		float runningSumInt = 0, runningSumCon = 0;
		int goodEntries = 0;

		for (int i = 0; i < listOfConcentrations->Count; i++) {
			if (listOfConcentrations[i] == -1) {
				continue;
			}
			goodEntries++;
			runningSumInt += listOfAverages[i];
			runningSumCon += listOfConcentrations[i];
		}
		float averageConcentration = runningSumCon / goodEntries;
		float averageIntensity = runningSumInt / goodEntries;
		//now, we have everything we need. Plug it into the R score formula.
		//1. Dividend - sum(Ii-Iaavg)(Ci-Cavg)
		float div = 0;
		for (int i = 0; i < listOfConcentrations->Count; i++) {
			if (listOfConcentrations[i] == -1) {
				continue;
			}
			div += (listOfConcentrations[i] - averageConcentration)*(listOfAverages[i] - averageConcentration);
		}
		//2. Divisor - sqrt(sum(Ii-Iavg)^2)*sqrt(sum(Ci-Cavg)^2)
		float divisor;
		float sumI = 0, sumC = 0;
		for (int i = 0; i < listOfConcentrations->Count; i++) {
			if (listOfConcentrations[i] == -1) {
				continue;
			}
			sumC += (listOfConcentrations[i] - averageConcentration)*(listOfConcentrations[i] - averageConcentration);
			sumI += (listOfAverages[i] - averageIntensity) * (listOfAverages[i] - averageIntensity);
		}
		sumC = Convert::ToSingle(Math::Sqrt(sumC));
		sumI = Convert::ToSingle(Math::Sqrt(sumI));
		divisor = sumC * sumI;
		//3. Finally, caluclate the R score.
		float R = div / divisor;
		return R * R;
		
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
			if (Convert::ToSingle(thisKeyValArray[1]) < cutoff) {
				dict->Add(Convert::ToSingle(thisKeyValArray[0]), 0);
			}
			else {
				dict->Add(Convert::ToSingle(thisKeyValArray[0]), Convert::ToSingle(thisKeyValArray[1]));
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
			lengthOfListOfMaps = filesToExtract->Count;
			////allocating memory so that the array does not need resizing
			listOfDictionaries = gcnew List<Dictionary<float, float>^>(lengthOfListOfMaps);
			//point to the relevant array.
			currentListOfDictionaries = listOfDictionaries;
			files = filesToExtract;

		}
		else if (whichDictionary == 2) {
			lengthOfListOfMaps = filesToExtract_B->Count;
			listOfDictionaries_B = gcnew List<Dictionary<float, float>^>(lengthOfListOfMaps);
			currentListOfDictionaries = listOfDictionaries_B;
			files = filesToExtract_B;

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
	//this function also initializes indexed keys, which are crucial for O(1) operation.
	int sumDictionaries() {
		//Even if there was a dictionary before, garbage collect it and create a new one.
		result = gcnew Dictionary<float, float>(DATASIZE - LINESTOSKIP);
		indexedKeys = gcnew List<float>(DATASIZE - LINESTOSKIP);
		if (listOfDictionaries == nullptr) {
			//in case user is operating in mode B.
			listOfDictionaries = listOfDictionaries_B;
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
			int assumedIndex = Convert::ToInt32(Math::Floor(Math::Pow(10, 5) / 6.21 * Math::Log(wavelength / 200.9381)));
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

	//Count how many non-null elements there are in the sets
	//Example: user supplies 4 values of wavelengths.
	//However, user also claims there are 3 sets to process - but user only submitted to 
	//set 1 and 3. This code works around tha
	int numberOfValidSets() {
		int elems = 0;
		for each (List<Dictionary<float, float>^> ^ set in listOfSets) {
			if (set != nullptr) { elems++; }
		}
		return elems;
	}


	//find the division values and save them to an array. Function to be called after there is at least 1
	//key selected by the user.
	int findDivisionValues() {

		/** OBSOLETE CODE, WILL REMOVE LATER - TODO. Keeping it now in case I need to revisit division
		* AcrossA.
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
		**/
		bool differentDivisors = false;
		int elems = numberOfValidSets();
		for each (List<Dictionary<float, float>^> ^ set in listOfSets) {
			if (set != nullptr) { elems++;}
		}

		//check if we have as many selected pairs of wavelengths as sets
		if (userSelectionsToKeys->Count / 2 == elems) {
			differentDivisors = true;
		}

		int whichKey = 0, curr = 0;
		float divisor, dividend;
		bool singleMode = false;

		//case of no division - code still runs, but it divides by 1 (i. e. returns intensity)
		if (userSelectionsToKeys->Count == 1) {
			dividend = userSelectionsToKeys[0];
			divisor = 1;
			//makeshift solution - it's quite bad practice since this key does not exist;
			//but it works out for saving a file
			userSelectionsToKeys->Add(1);
			userSelectionsIndexes->Add(-1);
			singleMode = true;
		}

		//outer loop - run through all the sets of files.
		else if (!differentDivisors) {
			dividend = userSelectionsToKeys[0];
			divisor = userSelectionsToKeys[1];
		}
		for each (List<Dictionary<float, float>^> ^ set in listOfSets) {
			//first, handle the first dictionary.
			if (set == nullptr) {
				curr++;
				continue;

			}
			float runningSum = 0, res;
			for each (Dictionary<float, float> ^ dict in set) {
				if (differentDivisors) {
					dividend = userSelectionsToKeys[whichKey];
					divisor = userSelectionsToKeys[whichKey + 1];
					whichKey += 2;
				}
				res = dict[dividend] /  (singleMode ? 1 : dict[divisor]);
				runningSum += res;
			}
			listOfAverages[curr] = runningSum / listOfDictionaries->Count;
			curr++;
		}
		return 1;

	}
	


























};
