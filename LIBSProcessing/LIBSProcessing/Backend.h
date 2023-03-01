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

public ref class Backend {



public:
	String^ directory;
	String^ nameOfFile;
	List<String^>^ filesToExtract;
	List<Dictionary<float, float>^> listOfDictionaries;		//dictionary has O(1) access time when passed the key.
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
	//pass by reference
	int processFileIntoDictionary(Dictionary<float, float>^ dict, String^ filename) {
		StreamReader^ sr = gcnew StreamReader(filename);
		String^ line;
		array<String^>^ thisKeyValArray;

		//read file line by line.
		while (line = sr->ReadLine()){
			//split line into two strings
			thisKeyValArray = line->Split(',', 2);
			dict->Add(thisKeyValArray[0]->ToDouble, 

		}
	}

	//function to internally extract data from files, and initialize them into RAM.
	//Overheads were considered, but overall loading 10 files, 26606 lines, each line being 2 * 4 bytes,
	//we have 10*26606 *8 = 2128480B = 2078 KiB = around 2MiB. All is good.
	int initializeMemoryFiles() {
		int lengthOfListOfMaps = filesToExtract->Count;


	}


























};
