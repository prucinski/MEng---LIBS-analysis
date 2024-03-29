/*****************************************************************//**
 * @file   Backend.h
 * @brief  File handling all the backend functions, invisible to the user.
 * 
 * @author PR
 * @date   April 2023
 *********************************************************************/
#pragma once


using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;


//how many datapoints are there?
#define DATASIZE 26607
#define LINESTOSKIP 105


/** 
* @brief Class handling the backend functions of the entire programme. Public variables are expanded on within the code.
*
*  The class has the following main functions:
* \n-opening files after UI has provided this class a list of filenames.
* \n-converting said files into a data format processable by the programme.
* \n-storing the selected peaks, as well as any database present in memory.
* \n-saving information to a file.
*
*/
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
	/**
	 * Save a processed data structure to a file in standard LIBS mode.
	 * 
	 * \param name Name of file to save to.
	 * \param selectedOnly Save all wavelengths to a file; or only the ones selected by the user.
	 * \param lowestPoint Option describing whether the user is also interested in saving the lowest values in range to file.
	 * \return Returns an integer describing success/fail of function. 1 - file saved; 0 - file locked by OS; -1 - file not saved because of user/programmer error.
	 */
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
			sw->Write("Supp. wavelength,Result\n");
			for each (float result in listOfAveragedIndividualResults) {
				if (i % 2 != 0 && lowestPoint) {
					i++;
					continue;
				}
				sw->Write(Convert::ToString(userSelectionsToKeys[j])+","+Convert::ToString(result)+",");
				i++;
				j++;
			}
			sw->Write("\nDivision of averaged first intensity over the other:,,,,,");
			if (!lowestPoint) {
				sw->Write(Convert::ToString(returnDivisionFromTwoFirst(listOfAveragedIndividualResults)) + "\n\n");
			}
			else {
				sw->Write(Convert::ToString(returnDivisionFromFirstThird(listOfAveragedIndividualResults)) + "\n\n");
			}
			sw->Write("Individual results\n");
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
					if (j % 2 == 0 && j > 0 && lowestPoint) {
						if (tempHighest > 3 * tempLowest) {
							sw->Write("yes,,");
						}
						else {
							sw->Write("no,,");
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
	/**
	 * Save a processed data structure to a file in calibration LIBS mode. 
	 *
	 * \param name Name of file to save to. Does not have to have a correct extension.
	 * \param lowestPoint Option describing whether the user is also interested in saving the lowest values in range to file.
	 * \return Returns an integer describing success/fail of function. 1 - file saved; 0 - file locked by OS; -1 - file not saved because of user/programmer error.
	 */
	int saveToFileCalibration(String^ name, bool lowestPoint) {
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
				sw->Write(Convert::ToString(listOfAverages[i]) + ",");
				if (differentDivisors) {
					sw->Write(Convert::ToString(userSelectionsToKeys[whichKey]) + ",");
					sw->Write(Convert::ToString(userSelectionsToKeys[whichKey + 1]) + ",");
					whichKey += 2;
				}
				else {
					sw->Write(Convert::ToString(userSelectionsToKeys[0]) + ",");
					sw->Write(Convert::ToString(userSelectionsToKeys[1]) + ",");
				}
				sw->Write(Convert::ToString(listOfConcentrations[i]) + "\n");
			}
			sw->Write("R2 score," + Convert::ToString(global_r2) + "\n");
			sw->Write("Individual results\n");
			if (lowestPoint) {
				sw->Write(",HIGHEST->,,,,LOWEST->,,,\n");
			}
			sw->Write("File no., divid. wavelength, intensity, divisor wavelength, intensity,");
			if (lowestPoint) {
				sw->Write(",,,,,1.peak?,2.peak?,");
			}
			for (int i = 0; i < metadata->Count; i++) {
				sw->Write("\nS" + Convert::ToString(i + 1) + "\n");
				if (listOfAverages[i] == -1) {
					sw->Write(",,,");
					continue;
				}
				int j = 1;
				for each (Dictionary<float, float> ^ fileAsDictionary in listOfProcessedSets[i]) {
					sw->Write("File " + (Convert::ToString(j)) + ",");
					int k = 0;
					float firstHighest, firstLowest, secondHighest, secondLowest;
					for each (float key in fileAsDictionary->Keys) {
						if (k % 4 == 0) {
							firstHighest = fileAsDictionary[key];
						}
						else if (k % 4 == 1) {
							secondHighest = fileAsDictionary[key];
						}
						else if (k % 4 == 2) {
							firstLowest = fileAsDictionary[key];
						}
						else if (k % 4 == 3) {
							secondLowest = fileAsDictionary[key];
						}
						sw->Write(Convert::ToString(key) + "," + Convert::ToString(fileAsDictionary[key]) + ",");
						k++;
						if (k % 4 == 0 && k > 0 && lowestPoint) {
							if (firstHighest > 3 * firstLowest) {
								sw->Write(",yes,");
							}
							else {
								sw->Write(",no,");
							}
							if (secondHighest > 3 * secondLowest) {
								sw->Write("yes,");
							}
							else {
								sw->Write("no,");
							}
						}
					}
					j++;
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
	/**
	 * Function reading files from disc. . 
	 * 
	 * \param fileNames Array of filenames. This list of files should be selected by the user in the GUI; using standard Windows libraries.
	 * \param cutoff Values of light intensities below which the intensity will be set to 0 when initializing data structures. Default -199.
	 * \param whichMode Integer describing which mode the programme is operating in. 1 - standard LIBS mode, 2 - calibration LIBS mode.
	 * \return Returns an integer indicating status. 0 - loading of files failed. 1 - load successful.
	 */
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
	/**
	 * Function initializing data structures in memory. These are intialized in order to be index-addressable in other functions.
	 * 
	 * \param length Number of sets of files that should be initialized.
	 * \return Always returns 1 - function cannot fail execution.
	 */
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
	/**
	 * Function adding loaded files to a set at a given index.
	 * 
	 * \param concentration User-supplied for a given set.
	 * \param index of the current set selected. Provided by which set user currently has selected in the GUI.
	 * \param cutoff Values of light intensities below which the intensity will be set to 0 when initializing data structures. Default -199.
	 * \return Returns 1 on success and 0 on failure.
	 */
	int addSetToSets(float concentration, int index, float cutoff) {
		try {
			listOfConcentrations[index] = concentration;
			listOfSets[index] = gcnew List<Dictionary<float, float>^>();
			listOfSets[index]->AddRange(listOfDictionaries_B);
			metadata[index] = Convert::ToString(index + 1) + ".SET: " + listOfDictionaries_B->Count + " FILES, CUTOFF " +
				cutoff + ", CONT." + concentration;
			return 1;
		}
		catch (...) {
			return 0;
		}
	}


	/**
	 * Function called by the UI frontend, processing loaded data in accordance to the selected wavelengths in single mode. Serves as an intermediate step
	 * between other functions.
	 * 
	 * \param option Option for how to process the data. 1 - find the highest peak within range,
	 *													 2- sum all datapoints within range.
	 * \param range Float specifying how many datapoints are looked at. User provided values for wavelengths assumed to be in them middle of this range.
	 * \param doLowerRange boolean specifying whether the user has requested to find lowest values in some range as well.
	 * \param lowerRange If the user requests that lowest point is found - analogous to parameter 'range'.
	 * \return Always returns 1 - programme will fail before reaching the call of this function.
	 */
	int getRequestedSpectraStandardMode(int option, float range, bool doLowerRange, float lowerRange) {
		//first, keys CLOSEST to the value that the user input must be found.
		findKeys();
		findRequestedValues(option, range, doLowerRange, lowerRange);
		return 1;
	}
	/**
	 * Function called by the UI frontend, processing loaded data in accordance to the selected wavelengths in calibration mode. Serves as an intermediate step
	 * between other functions.
	 *
	 * \param option Option for how to process the data. 1 - find the highest peak within range,
	 *													 2- sum all datapoints within range.
	 * \param range Float specifying how many datapoints are looked at. User provided values for wavelengths assumed to be in them middle of this range.
	 * \param doLowerRange - boolean specifying whether the user has requested to find lowest values in some range as well.
	 * \param lowerRange If the user requests that lowest point is found - analogous to parameter 'range'.
	 * \return Returns 1 on success, 0 on failure.
	 */
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
	/**
	 * Function averaging all spectra out in a set. Serves as an intermediate step between UI and a private function.
	 * 
	 * \return Returns 1 on success, 0 otherwise.
	 */
	int getAveragedSpectra() {
		return sumDictionaries();
	}
	/**
	 * Function adding an user-supplied wavelength to an internal data structure. Checks if wavelength is correct as well.
	 * 
	 * \param wavelength Wavelength to be added.
	 * \return Returns 1 if wavelength is valid; 0 otherwise.
	 */
	int addWavelength(float wavelength) {
		if (wavelength < 200.93 || wavelength > 1031.86) {
			return 0;
		}
		selectedWavelengths->Add(wavelength);
		return 1;
	}
	/**
	 * Function removing an user-supplied wavelength from an internal data structure.
	 * 
	 * \param wavelength Wavelength to be removed.
	 * \return 1 if removal successful, 0 otherwise. 0 should never be reached and this should be ensured in the Window.h file.
	 */
	int removeWavelength(float wavelength) {
		if (!selectedWavelengths->Contains(wavelength)) {
			return 0;
		}
		selectedWavelengths->Remove(wavelength);
		return 1;
	}

	/**
	 * Function calculating R^2 value; called after files in calibration mode have been initialized.
	 * 
	 * \return Returns the value of R^2. ALso initializes the global value of R^2 in the prgramme.
	 */
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
	/**
	 * Private function converting a raw file to a dictionary data structure.
	 * 
	 * \param dict Pass by reference - dictionary into which a file should be parsed.
	 * \param filename Name of file to be processed into a datastructure.
	 * \param cutoff Value of cutoff, below which the intensity of a given datapoint will be brought down to 0. Default -199.
	 * \return Returns a status flag. 1 - file successfully processed. 0 - file read failed.
	 */
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
	/**
	 * Private function to extract data from all selected files (as per internally initialized list of files) and load them into RAM.
	 * Goes one by one for each filename provided.
	 * 
	 * \param cutoff Value of cutoff, below which the intensity of a given datapoint will be brought down to 0. Default -199.
	 * \param whichMode Integer describing which mode the programme is operating in. 1 - standard LIBS mode, 2 - calibration LIBS mode.
	 * \return Returns 1 on success and 0 on failure.
	 */
	int initializeMemoryFiles(float cutoff, int whichMode) {
		List<String^>^ files;
		int lengthOfListOfMaps;
		List<Dictionary<float, float>^>^ currentListOfDictionaries;
		if (whichMode == 1) {
			lengthOfListOfMaps = filesToExtract->Count;
			////allocating memory so that the array does not need resizing
			listOfDictionaries = gcnew List<Dictionary<float, float>^>(lengthOfListOfMaps);
			//point to the relevant array.
			currentListOfDictionaries = listOfDictionaries;
			files = filesToExtract;

		}
		else if (whichMode == 2) {
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

	/**
	 * Private function summing all dictionaries into one resulting dictionaries, for when the strongest signal wants to be seen across n files.
	 * This function also initializes indexed keys, which in itself is crucial for O(1) operation - however, it would be good practice to have them
	 * be initialized in a separate function and decouple the code a bit.
	 * 
	 * \return Returns 0 on failure, 1 on success.
	 */
	int sumDictionaries() {
		//Even if there was a dictionary before, garbage collect it and create a new one.
		result = gcnew Dictionary<float, float>(DATASIZE - LINESTOSKIP);
		indexedKeys = gcnew List<float>(DATASIZE - LINESTOSKIP);
		if (listOfDictionaries == nullptr) {
			if (listOfDictionaries_B == nullptr) {
				return 0;
			}
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

	/**
	 * Private function that finds the appropriate keys for the values that user supplies. It does so by looking for the closest key to the value supplied.
	 * Heavily amortized O(n) time complexity for this search. Fills the self-contained dictionary.
	 * 
	 * \return Always returns 1.
	 */
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
	/**
	 * Private function finding requested values of intensities for previously provided wavelengths in range for standard LIBS mode.
	 * 
	 * \param option Option for how to process the data. 1 - find the highest peak within range,
	 *													    2- sum all datapoints within range.
	 * \param range	Range in which to find the highest peak value.
	 * \param doLowerRange Does the user want to find lowest value in range?
	 * \param lowerRange If yes, what is that range?
	 * \return Always returns 1.
	 */
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
	/**
	 * Private function finding requested values of intensities for previously provided wavelengths in range for calibration LIBS mode.
	 *
	 * \param option Option for how to process the data. 1 - find the highest peak within range,
	 *													    2- sum all datapoints within range.
	 * \param range	Range in which to find the highest peak value.
	 * \param doLowerRange Does the user want to find lowest value in range?
	 * \param lowerRange If yes, what is that range?
	 * \return Always returns 1.
	 */
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
						 retValDividerLower = findHighestKeyValuePair(whichKey+1, divisor, option, lowerRange / 2, false, fileAsDictionary);
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

	/**
	 * Function for counting how many non-null elements there are in the sets.
	 * Example: user supplies 4 values of wavelengths.
	 * However, user also claims there are 3 sets to process - but user only submitted to 
	 * set 1 and 3. This code works around that.
	 * 
	 * \return Returns the number of valid sets.
	 */
	int numberOfValidSets() {
		int elems = 0;
		for each (List<Dictionary<float, float>^> ^ set in listOfSets) {
			if (set != nullptr) { elems++; }
		}
		return elems;
	}

	/**
	 * Private function for finding the highest key in a given set.
	 * 
	 * \param i The index of the key in the indexedKeys array.
	 * \param key The value of the key for the dictionary.
	 * \param option Option for how to process the data. 1 - find the highest peak within range,
	 *													    2- sum all datapoints within range.
	 * If whichDir == false, this parameter is discarded.
	 * \param rangeEachWay The range to check, each way away from the key.
	 * \param whichDir boolean determining whether the function finds the highest or lowest value in range.
	 * \param inputDict Dictionary (i. e. file) on which the search is performed; passed by reference.
	 * \return Returns a tuple of values <highestKey, highestValue> or <lowestKey, lowestValue>, depending on whichDir.
	 */
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

	/**
	 * Private function that averages the values of keys in the same user-supplied keys. However, the keys don't necessarily have to be the same -
	 * this enables calculations for slightly different keys (for example, the highest keys) that had the same user-supplied key value.
	 * 
	 * \param LOD List of Dictionaries - passed by reference to find a result in a set of dictionaries.
	 * \return Returns a smart pointer to a list that holds the results for a given list of dictionaries (files).
	 */
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
	/**
	 * Function that divides first two items of a list. For programmer's convenience.
	 * 
	 * \param givenList List that the division is performed on.
	 * \return Returns the result of the division.
	 */
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

	//function to return a division of first and third values from list
	/**
	 * Function that divides first two items of a list. For programmer's convenience.
	 *
	 * \param givenList List that the division is performed on.
	 * \return Returns the result of the division.
	 */
	float returnDivisionFromFirstThird(List<float>^ givenList) {
		if (givenList->Count < 3) {
			return 0;
		}
		if (givenList[0] > givenList[2]) {
			return givenList[0] / givenList[2];
		}
		else {
			return givenList[2] / givenList[0];
		}
	}


	


























};
