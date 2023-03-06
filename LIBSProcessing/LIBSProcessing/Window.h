#pragma once
#include "Backend.h"

namespace LIBSProcessing {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Window
	/// </summary>
	public ref class Window : public System::Windows::Forms::Form
	{
	public:
		
		Window(void)
		{
			InitializeComponent();
			//Initializing the backend here.

			
		}
	private: System::Windows::Forms::CheckBox^ saveSelectedBox;
	private: System::Windows::Forms::RadioButton^ highestCheckbox;
	private: System::Windows::Forms::RadioButton^ sumCheckbox;
	private: System::Windows::Forms::GroupBox^ groupBox1;




	public:

	protected:
		Backend b;
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Window()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ waveEdit;

	private: System::Windows::Forms::Button^ waveSubmit;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ elemSubmit;
	private: System::Windows::Forms::ComboBox^ elemDropdown;
	private: System::Windows::Forms::TextBox^ rangeInput;
	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::ComboBox^ allWavelenghts;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ removeWave;
	private: System::Windows::Forms::Button^ saveFolderSelect;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowser;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ savePath;
	private: System::Windows::Forms::TextBox^ nameOfFile;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ saveToFile;
	private: System::Windows::Forms::Button^ fileSelect;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ preview;
	private: System::Windows::Forms::Label^ noOfFiles;
	private: System::Windows::Forms::OpenFileDialog^ fileOpener;




	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->waveEdit = (gcnew System::Windows::Forms::TextBox());
			this->waveSubmit = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->elemSubmit = (gcnew System::Windows::Forms::Button());
			this->elemDropdown = (gcnew System::Windows::Forms::ComboBox());
			this->rangeInput = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->allWavelenghts = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->removeWave = (gcnew System::Windows::Forms::Button());
			this->saveFolderSelect = (gcnew System::Windows::Forms::Button());
			this->folderBrowser = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->savePath = (gcnew System::Windows::Forms::TextBox());
			this->nameOfFile = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->saveToFile = (gcnew System::Windows::Forms::Button());
			this->fileSelect = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->preview = (gcnew System::Windows::Forms::Button());
			this->noOfFiles = (gcnew System::Windows::Forms::Label());
			this->fileOpener = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveSelectedBox = (gcnew System::Windows::Forms::CheckBox());
			this->highestCheckbox = (gcnew System::Windows::Forms::RadioButton());
			this->sumCheckbox = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(194, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Add element (to be filled with db entries)";
			this->label1->Click += gcnew System::EventHandler(this, &Window::label1_Click);
			// 
			// waveEdit
			// 
			this->waveEdit->Location = System::Drawing::Point(12, 88);
			this->waveEdit->Name = L"waveEdit";
			this->waveEdit->Size = System::Drawing::Size(100, 20);
			this->waveEdit->TabIndex = 2;
			this->waveEdit->Text = L"12";
			// 
			// waveSubmit
			// 
			this->waveSubmit->Location = System::Drawing::Point(133, 85);
			this->waveSubmit->Name = L"waveSubmit";
			this->waveSubmit->Size = System::Drawing::Size(75, 23);
			this->waveSubmit->TabIndex = 3;
			this->waveSubmit->Text = L"Submit";
			this->waveSubmit->UseVisualStyleBackColor = true;
			this->waveSubmit->Click += gcnew System::EventHandler(this, &Window::waveSubmit_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 69);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Add wavelengths";
			this->label2->Click += gcnew System::EventHandler(this, &Window::label2_Click);
			// 
			// elemSubmit
			// 
			this->elemSubmit->Location = System::Drawing::Point(133, 35);
			this->elemSubmit->Name = L"elemSubmit";
			this->elemSubmit->Size = System::Drawing::Size(75, 23);
			this->elemSubmit->TabIndex = 5;
			this->elemSubmit->Text = L"Submit";
			this->elemSubmit->UseVisualStyleBackColor = true;
			this->elemSubmit->Click += gcnew System::EventHandler(this, &Window::elemSubmit_Click);
			// 
			// elemDropdown
			// 
			this->elemDropdown->FormattingEnabled = true;
			this->elemDropdown->Location = System::Drawing::Point(12, 35);
			this->elemDropdown->MaxDropDownItems = 100;
			this->elemDropdown->Name = L"elemDropdown";
			this->elemDropdown->Size = System::Drawing::Size(100, 21);
			this->elemDropdown->TabIndex = 0;
			// 
			// rangeInput
			// 
			this->rangeInput->Location = System::Drawing::Point(12, 143);
			this->rangeInput->Name = L"rangeInput";
			this->rangeInput->Size = System::Drawing::Size(100, 20);
			this->rangeInput->TabIndex = 6;
			this->rangeInput->Text = L"0.07";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 127);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(118, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Range (default 0.07nm)";
			// 
			// allWavelenghts
			// 
			this->allWavelenghts->FormattingEnabled = true;
			this->allWavelenghts->Location = System::Drawing::Point(12, 190);
			this->allWavelenghts->MaxDropDownItems = 100;
			this->allWavelenghts->Name = L"allWavelenghts";
			this->allWavelenghts->Size = System::Drawing::Size(100, 21);
			this->allWavelenghts->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(9, 174);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(154, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Currently selected wavelenghts";
			// 
			// removeWave
			// 
			this->removeWave->Location = System::Drawing::Point(133, 190);
			this->removeWave->Name = L"removeWave";
			this->removeWave->Size = System::Drawing::Size(75, 23);
			this->removeWave->TabIndex = 11;
			this->removeWave->Text = L"Remove";
			this->removeWave->UseVisualStyleBackColor = true;
			this->removeWave->Click += gcnew System::EventHandler(this, &Window::removeWave_Click);
			// 
			// saveFolderSelect
			// 
			this->saveFolderSelect->Location = System::Drawing::Point(415, 140);
			this->saveFolderSelect->Name = L"saveFolderSelect";
			this->saveFolderSelect->Size = System::Drawing::Size(75, 23);
			this->saveFolderSelect->TabIndex = 12;
			this->saveFolderSelect->Text = L"Browse...";
			this->saveFolderSelect->UseVisualStyleBackColor = true;
			this->saveFolderSelect->Click += gcnew System::EventHandler(this, &Window::saveFolderSelect_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(241, 126);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(72, 13);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Save location";
			this->label5->Click += gcnew System::EventHandler(this, &Window::label5_Click_1);
			// 
			// savePath
			// 
			this->savePath->Location = System::Drawing::Point(244, 143);
			this->savePath->Name = L"savePath";
			this->savePath->ReadOnly = true;
			this->savePath->Size = System::Drawing::Size(143, 20);
			this->savePath->TabIndex = 14;
			// 
			// nameOfFile
			// 
			this->nameOfFile->Location = System::Drawing::Point(170, 376);
			this->nameOfFile->Name = L"nameOfFile";
			this->nameOfFile->Size = System::Drawing::Size(143, 20);
			this->nameOfFile->TabIndex = 15;
			//this->nameOfFile->Text = "TEMP.asc";
			this->nameOfFile->Text = System::DateTime::Now.ToString("dd_MM_hhmm") + ".asc";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(193, 360);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(104, 13);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Name of file to save:";
			// 
			// saveToFile
			// 
			this->saveToFile->Location = System::Drawing::Point(205, 402);
			this->saveToFile->Name = L"saveToFile";
			this->saveToFile->Size = System::Drawing::Size(75, 23);
			this->saveToFile->TabIndex = 17;
			this->saveToFile->Text = L"Save";
			this->saveToFile->UseVisualStyleBackColor = true;
			this->saveToFile->Click += gcnew System::EventHandler(this, &Window::saveToFile_Click);
			// 
			// fileSelect
			// 
			this->fileSelect->Location = System::Drawing::Point(415, 33);
			this->fileSelect->Name = L"fileSelect";
			this->fileSelect->Size = System::Drawing::Size(75, 23);
			this->fileSelect->TabIndex = 18;
			this->fileSelect->Text = L"Browse...";
			this->fileSelect->UseVisualStyleBackColor = true;
			this->fileSelect->Click += gcnew System::EventHandler(this, &Window::fileSelect_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(241, 38);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(113, 13);
			this->label7->TabIndex = 19;
			this->label7->Text = L"Select files to process:";
			// 
			// preview
			// 
			this->preview->Location = System::Drawing::Point(196, 260);
			this->preview->Name = L"preview";
			this->preview->Size = System::Drawing::Size(108, 21);
			this->preview->TabIndex = 20;
			this->preview->Text = L"Preview results";
			this->preview->UseVisualStyleBackColor = true;
			this->preview->Click += gcnew System::EventHandler(this, &Window::preview_Click);
			// 
			// noOfFiles
			// 
			this->noOfFiles->AutoSize = true;
			this->noOfFiles->Location = System::Drawing::Point(241, 90);
			this->noOfFiles->Name = L"noOfFiles";
			this->noOfFiles->Size = System::Drawing::Size(135, 13);
			this->noOfFiles->TabIndex = 21;
			this->noOfFiles->Text = L"Number of files selected: 0 ";
			// 
			// fileOpener
			// 
			this->fileOpener->FileName = L"Select your files...";
			this->fileOpener->Multiselect = true;
			// 
			// saveSelectedBox
			// 
			this->saveSelectedBox->AutoSize = true;
			this->saveSelectedBox->Checked = true;
			this->saveSelectedBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->saveSelectedBox->Location = System::Drawing::Point(12, 230);
			this->saveSelectedBox->Name = L"saveSelectedBox";
			this->saveSelectedBox->Size = System::Drawing::Size(179, 17);
			this->saveSelectedBox->TabIndex = 23;
			this->saveSelectedBox->Text = L"Save selected wavelengths only";
			this->saveSelectedBox->UseVisualStyleBackColor = true;
			// 
			// highestCheckbox
			// 
			this->highestCheckbox->AutoSize = true;
			this->highestCheckbox->Checked = true;
			this->highestCheckbox->Location = System::Drawing::Point(6, 10);
			this->highestCheckbox->Name = L"highestCheckbox";
			this->highestCheckbox->Size = System::Drawing::Size(102, 17);
			this->highestCheckbox->TabIndex = 26;
			this->highestCheckbox->TabStop = true;
			this->highestCheckbox->Text = L"Highest in range";
			this->highestCheckbox->UseVisualStyleBackColor = true;
			this->highestCheckbox->CheckedChanged += gcnew System::EventHandler(this, &Window::highestCheckbox_CheckedChanged);
			// 
			// sumCheckbox
			// 
			this->sumCheckbox->AutoSize = true;
			this->sumCheckbox->Location = System::Drawing::Point(6, 26);
			this->sumCheckbox->Name = L"sumCheckbox";
			this->sumCheckbox->Size = System::Drawing::Size(87, 17);
			this->sumCheckbox->TabIndex = 27;
			this->sumCheckbox->Text = L"Sum in range";
			this->sumCheckbox->UseVisualStyleBackColor = true;
			this->sumCheckbox->CheckedChanged += gcnew System::EventHandler(this, &Window::sumCheckbox_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->highestCheckbox);
			this->groupBox1->Controls->Add(this->sumCheckbox);
			this->groupBox1->Location = System::Drawing::Point(132, 122);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(103, 49);
			this->groupBox1->TabIndex = 28;
			this->groupBox1->TabStop = false;
			// 
			// Window
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(519, 495);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->saveSelectedBox);
			this->Controls->Add(this->noOfFiles);
			this->Controls->Add(this->preview);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->fileSelect);
			this->Controls->Add(this->saveToFile);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->nameOfFile);
			this->Controls->Add(this->savePath);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->saveFolderSelect);
			this->Controls->Add(this->removeWave);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->allWavelenghts);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->rangeInput);
			this->Controls->Add(this->elemSubmit);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->waveSubmit);
			this->Controls->Add(this->waveEdit);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->elemDropdown);
			this->Name = L"Window";
			this->Text = L"Window";
			this->Load += gcnew System::EventHandler(this, &Window::Window_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


		//CODE HANDLING THE UI & calls to the "backend".

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {//cleanup
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {//cleanup
	}
	private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {//cleanup
	}
	private: System::Void label5_Click_1(System::Object^ sender, System::EventArgs^ e) {//cleanup
	}

	//GUI handler - submit an ELEMENT'S wavelengths to the list
	private: System::Void elemSubmit_Click(System::Object^ sender, System::EventArgs^ e) {



	}
	//GUI handler - submit custom wavelengths to the list
	private: System::Void waveSubmit_Click(System::Object^ sender, System::EventArgs^ e) {
		float attemptConversion;
		//try converting - if failed, show a message to the user
		try {
			attemptConversion = Convert::ToDouble(waveEdit->Text);
		}
		catch (...) {
			MessageBox::Show("Error - please input a float value");
			return;
		}

		if (!b.addWavelength(attemptConversion)) {
			MessageBox::Show("Error - please input a value between 200.93 and 1031.86");
		}
		//for some reason, it order to update the list in the GUI it needs to be fully reset
		allWavelenghts->DataSource = nullptr;
		allWavelenghts->DataSource = b.selectedWavelengths;

	}

	//GUI handler - save the folder path for saving the results.
	private: System::Void saveFolderSelect_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowser->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ folderName = folderBrowser->SelectedPath;
			savePath->Text = folderName;
			b.directory = folderName;		//set the directory in the backend
		}
	}
	//GUI handler - remove wavelength from analysis
	private: System::Void removeWave_Click(System::Object^ sender, System::EventArgs^ e) {
		float waveToRemove = Convert::ToDouble(allWavelenghts->Text);
		b.removeWavelength(waveToRemove);
		allWavelenghts->DataSource = nullptr;
		allWavelenghts->DataSource = b.selectedWavelengths;
	}

	//GUI handler - preview all options - actually processes the data for now as well
	private: System::Void preview_Click(System::Object^ sender, System::EventArgs^ e) {
		if (b.getAveragedSpectra()) {}
		else { MessageBox::Show("Error - no files loaded"); return; }
		int option = 2;
		if (highestCheckbox->Checked) { option = 1; }
		float range;
		try {
			range = Convert::ToDouble(rangeInput->Text);
			if (range < 0) { range = -1 * range; };
		}
		catch (...) {
			MessageBox::Show("Error - range must be a float");
			return;
		}

		b.getRequestedSpectra(option, range);
	}

	//GUI handler - save file
	private: System::Void saveToFile_Click(System::Object^ sender, System::EventArgs^ e) {
		b.saveToFile(nameOfFile->Text, saveSelectedBox->Checked);
	}

	//GUI handler - load the files into the system
	private: System::Void fileSelect_Click(System::Object^ sender, System::EventArgs^ e) {
		if (fileOpener->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//if loaded files successfully, 
			if (b.loadFiles(fileOpener->FileNames)) {
				noOfFiles->Text = "Number of files selected: " + fileOpener->FileNames->Length;
			}
			//very basic handling for now.
			else {
				noOfFiles->Text = "Error: one of the files is not an .asc file.";
			}
		}

	}
	private: System::Void Window_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	//GUI handlers for the two checkbox for range controls.
	private: System::Void highestCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

	};
	private: System::Void sumCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

	}
};
}
