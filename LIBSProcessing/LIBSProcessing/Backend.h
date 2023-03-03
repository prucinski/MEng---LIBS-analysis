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
	List<Dictionary<float, float>^>^ listOfDictionaries;		//dictionary has O(1) access time when passed the key.
	Dictionary<float, float>^ result;
	


	Backend() {
		directory = Application::StartupPath;
		//for now.
		nameOfFile = "default.txt";
		//initialize the (now empty) dynamically allocated array.
		filesToExtract = gcnew List<String^>();
	}


	int saveToFile(String^ name) {
		//see if user put in any input; if not, do a default
		if (name) {
			nameOfFile = "\\"+name;
		}
		else {
			//TODO: save a file with current date
		}
		StreamWriter^ sw = gcnew StreamWriter(directory + nameOfFile);
		//testwrite
		sw->Write("Hello World1\n");
		sw->Write("Hello world 2");
		sw->Close();
		//TODO: exception handling
		return 1;
	}

	int loadFiles(array<String^>^ fileNames) {
		for each (String^ filename in fileNames) {
			if (filename->EndsWith(".asc")) {
				filesToExtract->Add(filename);
			}
			else {
				return 0;
			}
		}
		initializeMemoryFiles();

		return 1;
	}




private:
	//pass by reference. Function to pass the information from the file into a data structure.
	int processFileIntoDictionary(Dictionary<float, float>^ dict, String^ filename) {
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
			dict->Add(Convert::ToDouble(thisKeyValArray[0]), Convert::ToDouble(thisKeyValArray[1]));
		}
		return 1;
	}

	//function to internally extract data from files, and initialize them into RAM.
	//Overheads were considered, but overall loading 10 files, 26606 lines, each line being 2 * 4 bytes,
	//we have 10*26606 *8 = 2128480B = 2078 KiB = around 2MiB. All is good.
	//Depending on the version of the programme, data will be double instead of float, so 4MiB.

	int initializeMemoryFiles() {
		int lengthOfListOfMaps = filesToExtract->Count;
		//allocating memory so that the array does not need resizing
		listOfDictionaries = gcnew List<Dictionary<float, float>^>(lengthOfListOfMaps);
		//create and populate a dictionary of data for each of the files.
		for (int i = 0; i < lengthOfListOfMaps; i++) {
			listOfDictionaries->Add(gcnew Dictionary<float, float>(DATASIZE - LINESTOSKIP));
			processFileIntoDictionary(listOfDictionaries[i], filesToExtract[i]);
		}
		return 1;
	}

	//sum all our dictionaries into one resulting dictionary. This can be useful when we want to see the strongest peaks across n files.
	int sumDictionaries() {
		//TODO - check if the dictionary isn't already created.
		//Shouldn't be that big of a deal however because automated garbage collection.
		result = gcnew Dictionary<float, float>(DATASIZE - LINESTOSKIP);

		for each (float key in listOfDictionaries[0]->Keys) {
			float tempValue = 0;
			for (int j = 0; j < listOfDictionaries->Count; j++) {
				//it's upset when I'm doing double dereferencing. It's a good thing temp is a pointer so there is not a lot
				//of overhead.
				Dictionary<float, float>^ temp = listOfDictionaries[j];
				tempValue += temp[key];
			}
		}


	}


























};
