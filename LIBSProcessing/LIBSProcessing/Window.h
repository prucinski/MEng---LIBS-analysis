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
	private: System::Windows::Forms::TextBox^ noiseCutoff;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ cutoffLabel;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ modeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ standardToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ calibrationToolStripMenuItem;
	private: System::Windows::Forms::Label^ setAlabel;
	private: System::Windows::Forms::Label^ setBlabel;

	private: System::Windows::Forms::Label^ cutoffLabel_setB;
	private: System::Windows::Forms::Label^ noOfFiles_setB;
	private: System::Windows::Forms::Label^ selectFilesLabel_setB;

	private: System::Windows::Forms::Button^ fileSelect_setB;
	private: System::Windows::Forms::TextBox^ analyteBox;
	private: System::Windows::Forms::Label^ analyteLabel;
	private: System::Windows::Forms::Label^ analyteLabel_setB;


	private: System::Windows::Forms::TextBox^ analyteBox_setB;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Label^ setNumbersLabel;






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
			this->noiseCutoff = (gcnew System::Windows::Forms::TextBox());
			this->analyteBox = (gcnew System::Windows::Forms::TextBox());
			this->analyteBox_setB = (gcnew System::Windows::Forms::TextBox());
			this->setNumbersLabel = (gcnew System::Windows::Forms::Label());
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
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->cutoffLabel = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->modeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->standardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->calibrationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->setAlabel = (gcnew System::Windows::Forms::Label());
			this->setBlabel = (gcnew System::Windows::Forms::Label());
			this->cutoffLabel_setB = (gcnew System::Windows::Forms::Label());
			this->noOfFiles_setB = (gcnew System::Windows::Forms::Label());
			this->selectFilesLabel_setB = (gcnew System::Windows::Forms::Label());
			this->fileSelect_setB = (gcnew System::Windows::Forms::Button());
			this->analyteLabel = (gcnew System::Windows::Forms::Label());
			this->analyteLabel_setB = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->groupBox1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(194, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Add element (to be filled with db entries)";
			// 
			// waveEdit
			// 
			this->waveEdit->Location = System::Drawing::Point(12, 96);
			this->waveEdit->Name = L"waveEdit";
			this->waveEdit->Size = System::Drawing::Size(100, 20);
			this->waveEdit->TabIndex = 2;
			// 
			// waveSubmit
			// 
			this->waveSubmit->Location = System::Drawing::Point(133, 93);
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
			this->label2->Location = System::Drawing::Point(9, 77);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Add wavelengths";
			// 
			// elemSubmit
			// 
			this->elemSubmit->Location = System::Drawing::Point(133, 43);
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
			this->elemDropdown->Location = System::Drawing::Point(12, 43);
			this->elemDropdown->MaxDropDownItems = 100;
			this->elemDropdown->Name = L"elemDropdown";
			this->elemDropdown->Size = System::Drawing::Size(100, 21);
			this->elemDropdown->TabIndex = 0;
			// 
			// rangeInput
			// 
			this->rangeInput->Location = System::Drawing::Point(12, 151);
			this->rangeInput->Name = L"rangeInput";
			this->rangeInput->Size = System::Drawing::Size(100, 20);
			this->rangeInput->TabIndex = 6;
			this->rangeInput->Text = L"0.07";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 135);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(118, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Range (default 0.07nm)";
			// 
			// noiseCutoff
			// 
			this->noiseCutoff->Location = System::Drawing::Point(254, 46);
			this->noiseCutoff->Name = L"noiseCutoff";
			this->noiseCutoff->Size = System::Drawing::Size(100, 20);
			this->noiseCutoff->TabIndex = 29;
			this->toolTip1->SetToolTip(this->noiseCutoff, L"Values below this threshold will be dropped to 0.");
			// 
			// analyteBox
			// 
			this->analyteBox->Enabled = false;
			this->analyteBox->Location = System::Drawing::Point(254, 135);
			this->analyteBox->Name = L"analyteBox";
			this->analyteBox->Size = System::Drawing::Size(100, 20);
			this->analyteBox->TabIndex = 40;
			this->toolTip1->SetToolTip(this->analyteBox, L"Values below this threshold will be dropped to 0.");
			// 
			// analyteBox_setB
			// 
			this->analyteBox_setB->Enabled = false;
			this->analyteBox_setB->Location = System::Drawing::Point(254, 219);
			this->analyteBox_setB->Name = L"analyteBox_setB";
			this->analyteBox_setB->Size = System::Drawing::Size(100, 20);
			this->analyteBox_setB->TabIndex = 42;
			this->toolTip1->SetToolTip(this->analyteBox_setB, L"Values below this threshold will be dropped to 0.");
			// 
			// setNumbersLabel
			// 
			this->setNumbersLabel->AutoSize = true;
			this->setNumbersLabel->Enabled = false;
			this->setNumbersLabel->Location = System::Drawing::Point(12, 224);
			this->setNumbersLabel->Name = L"setNumbersLabel";
			this->setNumbersLabel->Size = System::Drawing::Size(152, 13);
			this->setNumbersLabel->TabIndex = 44;
			this->setNumbersLabel->Text = L"Set A: 1st/2nd; Set B: 3rd/4th.";
			this->toolTip1->SetToolTip(this->setNumbersLabel, L"3rd and 4th can be left blank; they will remain the same for set A.");
			// 
			// allWavelenghts
			// 
			this->allWavelenghts->FormattingEnabled = true;
			this->allWavelenghts->Location = System::Drawing::Point(12, 198);
			this->allWavelenghts->MaxDropDownItems = 100;
			this->allWavelenghts->Name = L"allWavelenghts";
			this->allWavelenghts->Size = System::Drawing::Size(100, 21);
			this->allWavelenghts->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(9, 182);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(154, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Currently selected wavelenghts";
			// 
			// removeWave
			// 
			this->removeWave->Location = System::Drawing::Point(133, 198);
			this->removeWave->Name = L"removeWave";
			this->removeWave->Size = System::Drawing::Size(75, 23);
			this->removeWave->TabIndex = 11;
			this->removeWave->Text = L"Remove";
			this->removeWave->UseVisualStyleBackColor = true;
			this->removeWave->Click += gcnew System::EventHandler(this, &Window::removeWave_Click);
			// 
			// saveFolderSelect
			// 
			this->saveFolderSelect->Location = System::Drawing::Point(303, 378);
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
			this->label5->Location = System::Drawing::Point(129, 364);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(72, 13);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Save location";
			// 
			// savePath
			// 
			this->savePath->Location = System::Drawing::Point(132, 381);
			this->savePath->Name = L"savePath";
			this->savePath->ReadOnly = true;
			this->savePath->Size = System::Drawing::Size(143, 20);
			this->savePath->TabIndex = 14;
			// 
			// nameOfFile
			// 
			this->nameOfFile->Location = System::Drawing::Point(180, 429);
			this->nameOfFile->Name = L"nameOfFile";
			this->nameOfFile->Size = System::Drawing::Size(143, 20);
			this->nameOfFile->TabIndex = 15;
			this->nameOfFile->Text = L"TEMP.csv";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(203, 413);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(104, 13);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Name of file to save:";
			// 
			// saveToFile
			// 
			this->saveToFile->Location = System::Drawing::Point(215, 455);
			this->saveToFile->Name = L"saveToFile";
			this->saveToFile->Size = System::Drawing::Size(75, 23);
			this->saveToFile->TabIndex = 17;
			this->saveToFile->Text = L"Save";
			this->saveToFile->UseVisualStyleBackColor = true;
			this->saveToFile->Click += gcnew System::EventHandler(this, &Window::saveToFile_Click);
			// 
			// fileSelect
			// 
			this->fileSelect->Location = System::Drawing::Point(425, 93);
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
			this->label7->Location = System::Drawing::Point(251, 98);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(113, 13);
			this->label7->TabIndex = 19;
			this->label7->Text = L"Select files to process:";
			// 
			// preview
			// 
			this->preview->Location = System::Drawing::Point(196, 298);
			this->preview->Name = L"preview";
			this->preview->Size = System::Drawing::Size(108, 21);
			this->preview->TabIndex = 20;
			this->preview->Text = L"Process results";
			this->preview->UseVisualStyleBackColor = true;
			this->preview->Click += gcnew System::EventHandler(this, &Window::preview_Click);
			// 
			// noOfFiles
			// 
			this->noOfFiles->AutoSize = true;
			this->noOfFiles->Location = System::Drawing::Point(422, 119);
			this->noOfFiles->Name = L"noOfFiles";
			this->noOfFiles->Size = System::Drawing::Size(80, 13);
			this->noOfFiles->TabIndex = 21;
			this->noOfFiles->Text = L"files selected: 0";
			// 
			// fileOpener
			// 
			this->fileOpener->FileName = L"Select your files...";
			this->fileOpener->Filter = L"ASC files (*.asc)|*.asc";
			this->fileOpener->Multiselect = true;
			// 
			// saveSelectedBox
			// 
			this->saveSelectedBox->AutoSize = true;
			this->saveSelectedBox->Checked = true;
			this->saveSelectedBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->saveSelectedBox->Location = System::Drawing::Point(12, 244);
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
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->highestCheckbox);
			this->groupBox1->Controls->Add(this->sumCheckbox);
			this->groupBox1->Location = System::Drawing::Point(132, 130);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(103, 49);
			this->groupBox1->TabIndex = 28;
			this->groupBox1->TabStop = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(251, 27);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(192, 13);
			this->label8->TabIndex = 30;
			this->label8->Text = L"Noise cutoff (select before loading files)";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(374, 49);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(126, 13);
			this->label9->TabIndex = 31;
			this->label9->Text = L"Leave blank for no cutoff";
			// 
			// cutoffLabel
			// 
			this->cutoffLabel->AutoSize = true;
			this->cutoffLabel->Location = System::Drawing::Point(422, 132);
			this->cutoffLabel->Name = L"cutoffLabel";
			this->cutoffLabel->Size = System::Drawing::Size(64, 13);
			this->cutoffLabel->TabIndex = 32;
			this->cutoffLabel->Text = L"at no cutoff.";
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->modeToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(519, 24);
			this->menuStrip1->TabIndex = 33;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// modeToolStripMenuItem
			// 
			this->modeToolStripMenuItem->BackColor = System::Drawing::SystemColors::Control;
			this->modeToolStripMenuItem->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->modeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->standardToolStripMenuItem,
					this->calibrationToolStripMenuItem
			});
			this->modeToolStripMenuItem->Name = L"modeToolStripMenuItem";
			this->modeToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->modeToolStripMenuItem->Text = L"Mode";
			// 
			// standardToolStripMenuItem
			// 
			this->standardToolStripMenuItem->Checked = true;
			this->standardToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->standardToolStripMenuItem->Name = L"standardToolStripMenuItem";
			this->standardToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->standardToolStripMenuItem->Text = L"Standard";
			this->standardToolStripMenuItem->Click += gcnew System::EventHandler(this, &Window::standardToolStripMenuItem_Click);
			// 
			// calibrationToolStripMenuItem
			// 
			this->calibrationToolStripMenuItem->Name = L"calibrationToolStripMenuItem";
			this->calibrationToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->calibrationToolStripMenuItem->Text = L"Calibration";
			this->calibrationToolStripMenuItem->Click += gcnew System::EventHandler(this, &Window::calibrationToolStripMenuItem_Click);
			// 
			// setAlabel
			// 
			this->setAlabel->AutoSize = true;
			this->setAlabel->Location = System::Drawing::Point(251, 85);
			this->setAlabel->Name = L"setAlabel";
			this->setAlabel->Size = System::Drawing::Size(36, 13);
			this->setAlabel->TabIndex = 34;
			this->setAlabel->Text = L"Set A:";
			// 
			// setBlabel
			// 
			this->setBlabel->AutoSize = true;
			this->setBlabel->Enabled = false;
			this->setBlabel->Location = System::Drawing::Point(251, 169);
			this->setBlabel->Name = L"setBlabel";
			this->setBlabel->Size = System::Drawing::Size(36, 13);
			this->setBlabel->TabIndex = 39;
			this->setBlabel->Text = L"Set B:";
			// 
			// cutoffLabel_setB
			// 
			this->cutoffLabel_setB->AutoSize = true;
			this->cutoffLabel_setB->Enabled = false;
			this->cutoffLabel_setB->Location = System::Drawing::Point(422, 216);
			this->cutoffLabel_setB->Name = L"cutoffLabel_setB";
			this->cutoffLabel_setB->Size = System::Drawing::Size(64, 13);
			this->cutoffLabel_setB->TabIndex = 38;
			this->cutoffLabel_setB->Text = L"at no cutoff.";
			// 
			// noOfFiles_setB
			// 
			this->noOfFiles_setB->AutoSize = true;
			this->noOfFiles_setB->Enabled = false;
			this->noOfFiles_setB->Location = System::Drawing::Point(422, 203);
			this->noOfFiles_setB->Name = L"noOfFiles_setB";
			this->noOfFiles_setB->Size = System::Drawing::Size(80, 13);
			this->noOfFiles_setB->TabIndex = 37;
			this->noOfFiles_setB->Text = L"files selected: 0";
			// 
			// selectFilesLabel_setB
			// 
			this->selectFilesLabel_setB->AutoSize = true;
			this->selectFilesLabel_setB->Enabled = false;
			this->selectFilesLabel_setB->Location = System::Drawing::Point(251, 182);
			this->selectFilesLabel_setB->Name = L"selectFilesLabel_setB";
			this->selectFilesLabel_setB->Size = System::Drawing::Size(113, 13);
			this->selectFilesLabel_setB->TabIndex = 36;
			this->selectFilesLabel_setB->Text = L"Select files to process:";
			// 
			// fileSelect_setB
			// 
			this->fileSelect_setB->Enabled = false;
			this->fileSelect_setB->Location = System::Drawing::Point(425, 177);
			this->fileSelect_setB->Name = L"fileSelect_setB";
			this->fileSelect_setB->Size = System::Drawing::Size(75, 23);
			this->fileSelect_setB->TabIndex = 35;
			this->fileSelect_setB->Text = L"Browse...";
			this->fileSelect_setB->UseVisualStyleBackColor = true;
			this->fileSelect_setB->Click += gcnew System::EventHandler(this, &Window::fileSelect_setB_Click);
			// 
			// analyteLabel
			// 
			this->analyteLabel->AutoSize = true;
			this->analyteLabel->Enabled = false;
			this->analyteLabel->Location = System::Drawing::Point(251, 121);
			this->analyteLabel->Name = L"analyteLabel";
			this->analyteLabel->Size = System::Drawing::Size(143, 13);
			this->analyteLabel->TabIndex = 41;
			this->analyteLabel->Text = L"Analyte concentration - set A";
			// 
			// analyteLabel_setB
			// 
			this->analyteLabel_setB->AutoSize = true;
			this->analyteLabel_setB->Enabled = false;
			this->analyteLabel_setB->Location = System::Drawing::Point(251, 205);
			this->analyteLabel_setB->Name = L"analyteLabel_setB";
			this->analyteLabel_setB->Size = System::Drawing::Size(143, 13);
			this->analyteLabel_setB->TabIndex = 43;
			this->analyteLabel_setB->Text = L"Analyte concentration - set B";
			// 
			// Window
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(519, 495);
			this->Controls->Add(this->setNumbersLabel);
			this->Controls->Add(this->analyteLabel_setB);
			this->Controls->Add(this->analyteBox_setB);
			this->Controls->Add(this->analyteLabel);
			this->Controls->Add(this->analyteBox);
			this->Controls->Add(this->setBlabel);
			this->Controls->Add(this->cutoffLabel_setB);
			this->Controls->Add(this->noOfFiles_setB);
			this->Controls->Add(this->selectFilesLabel_setB);
			this->Controls->Add(this->fileSelect_setB);
			this->Controls->Add(this->setAlabel);
			this->Controls->Add(this->cutoffLabel);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->noiseCutoff);
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
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Window";
			this->Text = L"Zeus";
			this->Load += gcnew System::EventHandler(this, &Window::Window_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


		//CODE HANDLING THE UI & calls to the "backend".

	//GUI handler - submit an ELEMENT'S wavelengths to the list
	private: System::Void elemSubmit_Click(System::Object^ sender, System::EventArgs^ e) {

		//TODO: database handling!

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
		waveEdit->Text = "";

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
		//Perform operations to retrieve division information 
		if (calibrationToolStripMenuItem->Checked) {
			b.getRequestedSpectraCalibrationMode();
		}
		//standard mode operation
		else {
			b.getRequestedSpectraStandardMode(option, range);
		}
	}

	//GUI handler - save file
	private: System::Void saveToFile_Click(System::Object^ sender, System::EventArgs^ e) {
		if (calibrationToolStripMenuItem->Checked) {
			if(int success = b.saveToFile(nameOfFile->Text, saveSelectedBox->Checked) == 0){
				MessageBox::Show("Error - file was unable to be saved with name " + b.nameOfFile);

			}
			else if (success == -1) {
				MessageBox::Show("Error - one of the data structures has not been initialized. This most often happens if 'Process' has not been clicked. ");
			}
			else {
				MessageBox::Show("File saved at " + b.directory + b.nameOfFile);
			}
		}
		//standard mode saving.
		else {
			if (int success = b.saveToFile(nameOfFile->Text, saveSelectedBox->Checked) == 0) {

			}
			else if (success == -1) {
				MessageBox::Show("Error - one of the data structures has not been initialized. This most often happens if 'Process' has not been clicked. ");
			}
			else {
				MessageBox::Show("File saved at " + b.directory + b.nameOfFile);
			}
		}


	}

	//GUI handler - load the files into the system
	private: System::Void fileSelect_Click(System::Object^ sender, System::EventArgs^ e) {
		handleSelection(1);
	}

	 private: System::Void fileSelect_setB_Click(System::Object^ sender, System::EventArgs^ e) {
		 handleSelection(2);
	 }
	private: System::Void Window_Load(System::Object^ sender, System::EventArgs^ e) {
	}

private: System::Void standardToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	setCalibrationGroup(true);

}
private: System::Void calibrationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	setCalibrationGroup(false);

}	

	/// <summary>
	/// Helper functions, not to clutter the main UI code - mainly with a single switch
	/// </summary>

	private: void handleSelection(int selectionWindow) {
		float cutoff;
		//if loaded files successfully, 
		if (fileOpener->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//try converting noiseCutoff to double,
			try {
				if (noiseCutoff->Text == "") {
					cutoff = -199;
				}
				else {
					cutoff = Convert::ToDouble(noiseCutoff->Text);
				}
			}
			//if unsuccessful, inform user and continue operation.
			catch (...) {
				MessageBox::Show("Cutoff value is not a float, setting to no cutoff.");
				cutoff = -199;
			}
			//and process the files into the memory.
			if (b.loadFiles(fileOpener->FileNames, cutoff, selectionWindow)) {
				if (selectionWindow == 1) {
					noOfFiles->Text = "files selected: " + fileOpener->FileNames->Length;
					if (cutoff == -199) {
						cutoffLabel->Text = "at no cutoff. ";
					}
					else {
						cutoffLabel->Text = "at cutoff: " + cutoff;
					}
				}
				else if (selectionWindow == 2) {
					noOfFiles_setB->Text = "files selected: " + fileOpener->FileNames->Length;
					if (cutoff == -199) {
						cutoffLabel_setB->Text = "at no cutoff. ";
					}
					else {
						cutoffLabel_setB->Text = "at cutoff: " + cutoff;
					}

				}

			}
			//very basic handling for now.
			else {
				noOfFiles->Text = "Error: one of the files is not an .asc file.";
			}
		}
	}
	private: void setCalibrationGroup(bool value) {
		standardToolStripMenuItem->Checked = value;
		calibrationToolStripMenuItem->Checked = !value;
		//setAlabel->Enabled = !value;
		analyteLabel->Enabled = !value;
		analyteBox->Enabled = !value;
		setBlabel->Enabled = !value;
		selectFilesLabel_setB->Enabled = !value;
		analyteLabel_setB->Enabled = !value;
		analyteBox_setB->Enabled = !value;
		fileSelect_setB->Enabled = !value;
		selectFilesLabel_setB->Enabled = !value;
		noOfFiles_setB->Enabled = !value;
		cutoffLabel_setB->Enabled = !value;
		setNumbersLabel->Enabled = !value;
		saveSelectedBox->Enabled = value;

		   }

};
}
