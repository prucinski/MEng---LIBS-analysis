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

	List<Dictionary<float, float>^>^ listOfResultsForFiles;		//List holding results for selected wavelengths for each file.
	List<float>^ listOfAveragedIndividualResults;				//List holding the individual results.
	
	//Calibration mode variables.
	List<String^>^ filesToExtract_B;							//Temporarily selected files & temporarily initialized dictionary when user is selecting.
	List<Dictionary<float, float>^>^ listOfDictionaries_B;

	//multi-set processing.
	List<String^>^ metadata;									//Metadata about a set to be displayed about a given set.						
	List< List<Dictionary<float, float>^>^>^ listOfSets;		//Processed files as sets inside of a list.
	List<float>^ listOfConcentrations;							//Concentrations as supplied by the user.
	List<float>^ listOfAverages;								//result of average division of first wavelength/second wavelength for each set of files.

	List< List<Dictionary<float, float>^>^>^ listOfProcessedSets;	//List holding results for selected wavlengths for each file, for each set.
	List<List<float>^>^ listOfAveragedIndividualResults_sets;		//List holding individual results for each file for each set - average from division.

	float global_r2;
	Backend() {
		directory = Application::StartupPath;
		//for now.
		nameOfFile = "default.csv";
		//initialize the (now empty) dynamically allocated array.
		selectedWavelengths = gcnew List<float>();
	}


	int saveToFile(String^ name, bool selectedOnly, bool lowestPoint) {
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
		//loop through all the keyss
		try {
			sw->Write("AVERAGE OF SUM OF FILES,\n");
			sw->Write("Highest key in range, result\n");
			for each (float key in whatToSave->Keys) {
				sw->Write(Convert::ToString(key));
				sw->Write(',');
				sw->Write(Convert::ToString(result[key]));
				sw->Write('\n');
			}
			sw->Write("AVERAGE OF INDIVIDUAL HIGHEST WITHIN RANGE\n");
			int i = 0, j = 0;
			sw->Write("Key,Result\n");
			for each (float result in listOfAveragedIndividualResults) {
				if (i % 2 != 0 && lowestPoint) {
					i++;
					continue;
				}
				sw->Write(Convert::ToString(userSelectionsToKeys[j])+","+Convert::ToString(result)+",");
				i++;
				j++;
			}
			sw->Write("\n");
			sw->Write("Division of averaged first intensity over the other:,,,,,"+Convert::ToString(returnDivisionFromTwoFirst(listOfAveragedIndividualResults))+"\n\n");
			sw->Write("(Individual results\n");
			if (lowestPoint) {
				sw->Write(",,,,(optional),(optional)\n");
			}

			if (lowestPoint) {
				sw->Write("File no., wavelength, intensity,Lowest key in range, result,peak?\n");
			}
			else {
				sw->Write("File no., wavelength,intensity,\n");
			}

			i = 1;
			for each (Dictionary<float, float> ^ fileAsDictionary in listOfResultsForFiles) {
				sw->Write("File " + (Convert::ToString(i)) + ",");
				//this is quite bad, as no calculations should be done inside this function. However, I am too tired to do it otherwise right now.
				j = 0;
				float tempHighest, tempLowest;

				for each (float key in fileAsDictionary->Keys) {
					if (lowestPoint) {
						if (j %2 == 0) {
							tempHighest = fileAsDictionary[key];
						}
						if (j % 2 != 0) {
							tempLowest = fileAsDictionary[key];
						}
					}
					sw->Write(Convert::ToString(key) + "," + Convert::ToString(fileAsDictionary[key])+",");
					j++;
					if (j % 2 == 0 && j > 0) {
						if (tempHighest > 3 * tempLowest) {
							sw->Write("yes,");
						}
						else {
							sw->Write("no,");
						}
					}
				}
				sw->Write("\n");
				i++;
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
			int elems = numberOfValidSets(); int whichKey = 0;
			bool differentDivisors = false;
			if (userSelectionsToKeys->Count / 2 == elems) {
				differentDivisors = true;
			}
			//write headers
			sw->Write(",Average (sum first intensity then sum second intensity then divide one by the other),");
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
			sw->Write("R2 score," + Convert::ToString(global_r2)+"\n");
			sw->Write("Individual results\n");
			sw->Write("File no., wavelength, intensity\n");
			for (int i = 0; i < metadata->Count; i++) {
				sw->Write("S" + Convert::ToString(i + 1) + "\n");
				if (listOfAverages[i] == -1) {
					sw->Write(",,,");
					continue;
				}
				int j = 1;
				for each (Dictionary<float, float> ^ fileAsDictionary in listOfProcessedSets[i]) {
					sw->Write("File " + (Convert::ToString(j)) + ",");
					for each (float key in fileAsDictionary->Keys) {
						sw->Write(Convert::ToString(key) + "," + Convert::ToString(fileAsDictionary[key]) + ",");
						j++;
					}
					sw->Write("\n");
				}
			}
		}
		catch (...) {
			//Data structures not initialized yet.
			sw->Close();
			return -1;
		}





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
	int getRequestedSpectraStandardMode(int option, float range, bool doLowerRange, float lowerRange) {
		//first, keys CLOSEST to the value that the user input must be found.
		findKeys();
		findRequestedValues(option, range, doLowerRange, lowerRange);
		return 1;
	}

	int getRequestedSpectraCalibrationMode(int option, float range, bool doLowerRange, float lowerRange) {
		//if we have less than 1 item, discard. We will check for whether each set has it's own wavelengths later.
		if (selectedWavelengths->Count < 1) {
			return 0;
		}
		//first, keys CLOSEST to the value that the user input must be found.
		findKeys();
		findRequestedValuesCalibration(option, range, doLowerRange, lowerRange);
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
		global_r2 = R * R;
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
	int findRequestedValues(int option, float range, bool doLowerRange, float lowerRange) {
		//reset the "presentToUser" dictionary.
		presentToUserResult = gcnew Dictionary<float, float>();
		float rangeEachWay = range / 2;
		//i must be kept track of - it indicates which key we're currently looking at
		int i = 0;
		for each (float key in userSelectionsToKeys) {
			//first, find it for the averaged dictionaries
			Tuple<float, float>^ retVal = findHighestKeyValuePair(i, key, option, rangeEachWay, true, result);
			//now we have found the highest value. Add to the proper result dictionary.
			presentToUserResult->Add(retVal->Item1, retVal->Item2);
			i++;
		}

		//now, find the results for individual files
		int j = 0;		//keeping track of which file we're in right now
		listOfResultsForFiles = gcnew List<Dictionary<float, float>^>(listOfDictionaries->Count);
		for each (Dictionary<float, float> ^ fileAsDictionary in listOfDictionaries) {
			//TODO - have a size predetermined for this dictionary
			listOfResultsForFiles->Add(gcnew Dictionary<float, float>());
			i = 0;
			for each (float key in userSelectionsToKeys) {
				Tuple<float, float>^ retVal = findHighestKeyValuePair(i, key, option, rangeEachWay, true, fileAsDictionary);
				Tuple<float, float>^ retValLower;
				if (doLowerRange) {
					retValLower = findHighestKeyValuePair(i, key, option, lowerRange/2, false, fileAsDictionary);
				}
				listOfResultsForFiles[j]->Add(retVal->Item1, retVal->Item2);
				if (doLowerRange) {
					listOfResultsForFiles[j]->Add(retValLower->Item1, retValLower->Item2);
				}
				i++;
			}
			j++;
		}
		//finally, average out the individual elements 
		listOfAveragedIndividualResults = averageIndividualKeyValuePairs(listOfResultsForFiles);
		return 1;
	}

	int findRequestedValuesCalibration(int option, float range, bool doLowerRange, float lowerRange) {
		float rangeEachWay = range / 2;
		//first, we must measure what kind of values have been selected in the "Currently selected wavelengths" box...
		bool differentDivisors = false;
		int elems = numberOfValidSets();
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

		else if (!differentDivisors) {
			dividend = userSelectionsToKeys[0];
			divisor = userSelectionsToKeys[1];
		}
		//...We have now measured what kind of values have been selected in the "Currently selected wavelengths" box.
		//outer loop - run through all the sets of files.
		listOfProcessedSets = gcnew List<List<Dictionary<float, float>^>^>();
		int i, j = 0;
		for each (List<Dictionary<float, float>^> ^ set in listOfSets) {
			j = 0;
			listOfProcessedSets->Add(gcnew List <Dictionary<float, float>^>());
			//first, handle the first dictionary.
			if (set == nullptr) {
				i++;
				continue;

			}
			if (differentDivisors) {
				dividend = userSelectionsToKeys[whichKey];
				divisor = userSelectionsToKeys[whichKey + 1];
				whichKey += 2;
			}
			for each (Dictionary<float, float> ^ fileAsDictionary in set) {
				listOfProcessedSets[i]->Add(gcnew Dictionary<float, float> ());

				//We now definitely have the correct key for dividend and divisor - now, find the highest key/value pair within range
				Tuple<float, float>^ retValDividend = findHighestKeyValuePair(whichKey, dividend, option, rangeEachWay, true, fileAsDictionary);
				Tuple<float, float>^ retValDividendLower;
				Tuple<float, float>^ retValDividerLower;
				if (doLowerRange) {
					retValDividendLower = findHighestKeyValuePair(whichKey, dividend, option, lowerRange/2, false, fileAsDictionary);
				}
				Tuple<float, float>^ retValDivisor;
				if (!singleMode) {
					retValDivisor = findHighestKeyValuePair(whichKey+1, divisor, option, rangeEachWay, true, fileAsDictionary);
					if (doLowerRange) {
						 retValDividerLower = findHighestKeyValuePair(whichKey, divisor, option, lowerRange / 2, false, fileAsDictionary);
					}
				}
				//res = dict[dividend] / (singleMode ? 1 : dict[divisor]);
				//runningSum += res;
				//pointer - will retain information
				List<Dictionary<float, float>^>^ temp = listOfProcessedSets[i];
				temp[j]->Add(retValDividend->Item1, retValDividend->Item2);
				if (!singleMode) {
					temp[j]->Add(retValDivisor->Item1, retValDivisor->Item2);
				}
				else{
					//adding a value of 1 with a key of 1 to divide by 1 for result. Key of 1 works as a flag
					temp[j]->Add(1, 1);
				}
				if (doLowerRange) {
					//third and fourth column will be reserved for the smallest value within the given range.
					temp[j]->Add(retValDividendLower->Item1, retValDividendLower->Item2);
					if (!singleMode) {
						temp[j]->Add(retValDividerLower->Item1, retValDividerLower->Item2);
					}
				}
				
				j++;
			}
			if (differentDivisors) {
				whichKey += 2;
			}
			i++;
		}
		//we have now found the wavelength of biggest intensity in  range. We may proceed to calculating the averages for each set.
		listOfAveragedIndividualResults_sets = gcnew  List<List<float>^>();
		i = 0;
		for each (List<Dictionary<float, float>^> ^ set  in listOfProcessedSets) {
			listOfAveragedIndividualResults_sets->Add(averageIndividualKeyValuePairs(set));
			//there will actually be only two pieces of information in each list anyway, making this perfect
			listOfAverages[i] = returnDivisionFromTwoFirst(listOfAveragedIndividualResults_sets[i]);
			i++;
		}
		return 1;
	}

	//Count how many non-null elements there are in the sets
	//Example: user supplies 4 values of wavelengths.
	//However, user also claims there are 3 sets to process - but user only submitted to 
	//set 1 and 3. This code works around that
	int numberOfValidSets() {
		int elems = 0;
		for each (List<Dictionary<float, float>^> ^ set in listOfSets) {
			if (set != nullptr) { elems++; }
		}
		return elems;
	}

	//private function for finding the highest key IN a given set. Function results as a simplification of code when refractoring
	System::Tuple<float,float>^ findHighestKeyValuePair(int i, float key, int option, float rangeEachWay, bool whichDir, Dictionary<float,float>^ inputDict) {
		int index = userSelectionsIndexes[i];
		float currKey = indexedKeys[index];
		float tempKey, tempResult;
		if (!whichDir) {
			tempResult = 99999; tempKey = -1;
		}
		else if (option == 1) { tempResult = -9999; tempKey = -1; }
		else if (option == 2) { tempResult = 0; tempKey = key;}
		while (Math::Abs(key - currKey) < rangeEachWay) {
			//if we're finding the lowest value, we ignore what option was selected (by design)
			 if (!whichDir) {
				tempResult = inputDict[currKey] < tempResult ? inputDict[currKey] : tempResult;
				tempKey = inputDict[currKey] == tempResult ? currKey : tempKey;
			}
			else if (option == 1) {
				tempResult = inputDict[currKey] > tempResult ? inputDict[currKey] : tempResult;
				tempKey = inputDict[currKey] == tempResult ? currKey : tempKey;
			}
			else {
				tempResult += inputDict[currKey];
			}
			if (index == 0) { break; }
			index--;

			currKey = indexedKeys[index];
		}
		//escaped the while loop. Now do it again, but the other way. Admittedly there is redundancy in this code.
		index = userSelectionsIndexes[i];
		currKey = indexedKeys[index + 1];
		while (Math::Abs(key - currKey) < rangeEachWay) {
			if (option == 1 && whichDir) {
				tempResult = inputDict[currKey] > tempResult ? inputDict[currKey] : tempResult;
				tempKey = inputDict[currKey] == tempResult ? currKey : tempKey;

			}
			else if (!whichDir) {
				tempResult = inputDict[currKey] < tempResult ? inputDict[currKey] : tempResult;
				tempKey = inputDict[currKey] == tempResult ? currKey : tempKey;
			}

			else {
				tempResult += inputDict[currKey];
			}
			if (index == DATASIZE - LINESTOSKIP) { break; }
			index++;
			currKey = indexedKeys[index];
		}
		//finally, found the highest key & the value corresponding. Return
		System::Tuple<float, float>^ retVal = gcnew Tuple<float, float>(tempKey, tempResult);
		return retVal;
	}

	//function to be called privately to average the values for keys in same places
	List<float>^ averageIndividualKeyValuePairs(List<Dictionary<float, float>^>^ LOD) {
		int i;
		int howManyWavelengths = LOD[0]->Count;
		List<float>^ pointerToResult = gcnew List<float>(howManyWavelengths);
		for (int i = 0; i < howManyWavelengths; i++) {
			pointerToResult->Add(0);
		}
		for each(Dictionary<float,float>^ dict in LOD) {
			i = 0;
			for each (float key in dict->Keys) {
				pointerToResult[i] += dict[key];
				i++;
			}
		}
		//now we have our list; divide each item by times called
		for (int i = 0; i < howManyWavelengths; i++) {
			pointerToResult[i] = pointerToResult[i] / LOD->Count;
		}

		//success
		return pointerToResult;
	}

	//function to return a division of two first values from list
	float returnDivisionFromTwoFirst(List<float>^ givenList) {
		if (givenList->Count < 2) {
			return 0;
		}
		if (givenList[0] > givenList[1]) {
			return givenList[0] / givenList[1];
		}
		else {
			return givenList[1] / givenList[0];
		}
	}


	


























};
