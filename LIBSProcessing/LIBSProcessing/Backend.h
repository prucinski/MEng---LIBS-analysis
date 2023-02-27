#pragma once
#include <iostream>
#include <fstream>
#include <msclr\marshal_cppstd.h>
using namespace System;
using namespace std;
/*
* Class handling the backend functions of the entire programme. That includes:
* -opening files after UI has provided this class a list of filenames.
* -converting said files into a data format processable by the programme.
* -storing the selected peaks, as well as the database in memory.
* -saving information to a file.
* 
*/


class Backend {

public:
	string directory;
	string nameOfFile;

	Backend() {
	
	
	}


	int saveToFile() {
		ofstream resultFile;
		//needs to be wrapped from String^ to string.
		string location = msclr::interop::marshal_as<std::string>(directory) + msclr::interop::marshal_as<std::string>(nameOfFile);
		resultFile.open(location);
		resultFile << "SavingTest.\n";
		resultFile << "SavingTestLine2. \n";
		resultFile.close();
		return 0;


	}

























};
