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

	


	Backend() {
		directory = Application::StartupPath;
		//for now.
		nameOfFile = "default.txt";
		//initialize the (now empty) dynamically allocated array.
		filesToExtract = gcnew List<String^>();
		selectedWavelengths = gcnew List<float>();
	}


	int saveToFile(String^ name, bool selectedOnly) {
		//see if user put in any input; if not, do a default
		if (name) {
			nameOfFile = "\\"+name;
		}
		if (!name->EndsWith(".asc")) {
			nameOfFile = nameOfFile + ".asc";
		}
		else {
			//TODO: save a file with current date
		}
		//if o
		Dictionary<float, float>^ whatToSave = selectedOnly ? presentToUserResult : result;
		StreamWriter^ sw = gcnew StreamWriter(directory + nameOfFile);
		//loop through all the keys
		for each (float key in whatToSave->Keys) {
			sw->Write(Convert::ToString(key));
			sw->Write(',');
			sw->Write(Convert::ToString(result[key]));
			sw->Write('\n');
		}

		sw->Close();
		//TODO: exception handling
		return 1;
	}

	int loadFiles(array<String^>^ fileNames, float cutoff) {
		for each (String^ filename in fileNames) {
			if (filename->EndsWith(".asc")) {
				filesToExtract->Add(filename);
			}
			else {
				return 0;
			}
		}
		initializeMemoryFiles(cutoff);

		return 1;
	}

	//function to be called by the UI to process the dictionary as per our selected wavelengths.
	//option values:	1 - find highest peak within range
	//					2 - sum all datapoints within range
	int getRequestedSpectra(int option, float range) {
		//first, keys CLOSEST to the value that the user input must be found.
		findKeys();
		findRequestedValues(option, range);
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

	int initializeMemoryFiles(float cutoff) {
		int lengthOfListOfMaps = filesToExtract->Count;
		//allocating memory so that the array does not need resizing
		listOfDictionaries = gcnew List<Dictionary<float, float>^>(lengthOfListOfMaps);
		//create and populate a dictionary of data for each of the files.
		for (int i = 0; i < lengthOfListOfMaps; i++) {
			listOfDictionaries->Add(gcnew Dictionary<float, float>(DATASIZE - LINESTOSKIP));
			processFileIntoDictionary(listOfDictionaries[i], filesToExtract[i], cutoff);
		}
		return 1;
	}

	//sum all our dictionaries into one resulting dictionary. This can be useful when we want to see the strongest peaks across n files.
	int sumDictionaries() {
		//TODO - check if the dictionary isn't already created.
		//Shouldn't be that big of a deal however because automated garbage collection.
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
		if (userSelectionsToKeys == nullptr) {
			userSelectionsToKeys = gcnew List<float>();
			userSelectionsIndexes = gcnew List<int>();
		}

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
		float rangeEachWay = range / 2;
		if (option == 2) { option = 0; }	//TODO clean this up
		float tempResult = option ? -9999 : 0;
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
	


























};
