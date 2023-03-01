#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
/*
* Class handling the backend functions of the entire programme. That includes:
* -opening files after UI has provided this class a list of filenames.
* -converting said files into a data format processable by the programme.
* -storing the selected peaks, as well as the database in memory.
* -saving information to a file.
* 
*/


public ref class Backend {

public:
	String^ directory;
	String^ nameOfFile;

	Backend() {
		directory = Application::StartupPath;
		//for now.
		nameOfFile = "default.txt";
	
	
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

		return 0;


	}

























};
