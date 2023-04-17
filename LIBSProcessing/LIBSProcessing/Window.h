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



	private: System::Windows::Forms::Label^ selectFilesLabel_setB;

	private: System::Windows::Forms::Button^ fileSelect_setB;


	private: System::Windows::Forms::Label^ analyteLabel_setB;


	private: System::Windows::Forms::TextBox^ analyteBox_setB;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Label^ setNumbersLabel;
	private: System::Windows::Forms::Label^ howManyLabel;
	private: System::Windows::Forms::Button^ howManySubmit;


	private: System::Windows::Forms::TextBox^ howManySets;
	private: System::Windows::Forms::ComboBox^ setsOfData;
	private: System::Windows::Forms::Label^ setsOfData_label;
	private: System::Windows::Forms::Button^ addSetButton;
	private: System::Windows::Forms::Label^ Rscore;
	private: System::Windows::Forms::TextBox^ rangeLowerInput;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::RadioButton^ lowerRangeYes;

	private: System::Windows::Forms::RadioButton^ radioButton2;







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

	private: System::Windows::Forms::TextBox^ waveEdit;

	private: System::Windows::Forms::Button^ waveSubmit;

	private: System::Windows::Forms::Label^ label2;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Window::typeid));
			this->waveEdit = (gcnew System::Windows::Forms::TextBox());
			this->waveSubmit = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->rangeInput = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->noiseCutoff = (gcnew System::Windows::Forms::TextBox());
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
			this->selectFilesLabel_setB = (gcnew System::Windows::Forms::Label());
			this->fileSelect_setB = (gcnew System::Windows::Forms::Button());
			this->analyteLabel_setB = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->howManyLabel = (gcnew System::Windows::Forms::Label());
			this->howManySubmit = (gcnew System::Windows::Forms::Button());
			this->howManySets = (gcnew System::Windows::Forms::TextBox());
			this->setsOfData = (gcnew System::Windows::Forms::ComboBox());
			this->setsOfData_label = (gcnew System::Windows::Forms::Label());
			this->addSetButton = (gcnew System::Windows::Forms::Button());
			this->Rscore = (gcnew System::Windows::Forms::Label());
			this->rangeLowerInput = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->lowerRangeYes = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// waveEdit
			// 
			this->waveEdit->Location = System::Drawing::Point(12, 46);
			this->waveEdit->Name = L"waveEdit";
			this->waveEdit->Size = System::Drawing::Size(100, 20);
			this->waveEdit->TabIndex = 2;
			// 
			// waveSubmit
			// 
			this->waveSubmit->Location = System::Drawing::Point(133, 43);
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
			this->label2->Location = System::Drawing::Point(9, 27);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Add wavelengths";
			// 
			// rangeInput
			// 
			this->rangeInput->Location = System::Drawing::Point(12, 88);
			this->rangeInput->Name = L"rangeInput";
			this->rangeInput->Size = System::Drawing::Size(100, 20);
			this->rangeInput->TabIndex = 6;
			this->rangeInput->Text = L"0.07";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 72);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(118, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Range (default 0.07nm)";
			// 
			// noiseCutoff
			// 
			this->noiseCutoff->Location = System::Drawing::Point(244, 43);
			this->noiseCutoff->Name = L"noiseCutoff";
			this->noiseCutoff->Size = System::Drawing::Size(100, 20);
			this->noiseCutoff->TabIndex = 29;
			this->toolTip1->SetToolTip(this->noiseCutoff, L"Values below this threshold will be dropped to 0.");
			// 
			// analyteBox_setB
			// 
			this->analyteBox_setB->Enabled = false;
			this->analyteBox_setB->Location = System::Drawing::Point(244, 258);
			this->analyteBox_setB->Name = L"analyteBox_setB";
			this->analyteBox_setB->Size = System::Drawing::Size(100, 20);
			this->analyteBox_setB->TabIndex = 42;
			this->toolTip1->SetToolTip(this->analyteBox_setB, L"Values below this threshold will be dropped to 0.");
			// 
			// setNumbersLabel
			// 
			this->setNumbersLabel->AutoSize = true;
			this->setNumbersLabel->Enabled = false;
			this->setNumbersLabel->Location = System::Drawing::Point(9, 201);
			this->setNumbersLabel->Name = L"setNumbersLabel";
			this->setNumbersLabel->Size = System::Drawing::Size(161, 26);
			this->setNumbersLabel->TabIndex = 44;
			this->setNumbersLabel->Text = L"Set 1: 1st/2nd; Set 2: 3rd/4th... \r\n Hover over for more information.";
			this->toolTip1->SetToolTip(this->setNumbersLabel, resources->GetString(L"setNumbersLabel.ToolTip"));
			// 
			// allWavelenghts
			// 
			this->allWavelenghts->FormattingEnabled = true;
			this->allWavelenghts->Location = System::Drawing::Point(12, 175);
			this->allWavelenghts->MaxDropDownItems = 100;
			this->allWavelenghts->Name = L"allWavelenghts";
			this->allWavelenghts->Size = System::Drawing::Size(100, 21);
			this->allWavelenghts->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(9, 159);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(154, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Currently selected wavelenghts";
			// 
			// removeWave
			// 
			this->removeWave->Location = System::Drawing::Point(133, 175);
			this->removeWave->Name = L"removeWave";
			this->removeWave->Size = System::Drawing::Size(75, 23);
			this->removeWave->TabIndex = 11;
			this->removeWave->Text = L"Remove";
			this->removeWave->UseVisualStyleBackColor = true;
			this->removeWave->Click += gcnew System::EventHandler(this, &Window::removeWave_Click);
			// 
			// saveFolderSelect
			// 
			this->saveFolderSelect->Location = System::Drawing::Point(170, 450);
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
			this->label5->Location = System::Drawing::Point(17, 435);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(72, 13);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Save location";
			// 
			// savePath
			// 
			this->savePath->Location = System::Drawing::Point(20, 452);
			this->savePath->Name = L"savePath";
			this->savePath->ReadOnly = true;
			this->savePath->Size = System::Drawing::Size(143, 20);
			this->savePath->TabIndex = 14;
			// 
			// nameOfFile
			// 
			this->nameOfFile->Location = System::Drawing::Point(277, 453);
			this->nameOfFile->Name = L"nameOfFile";
			this->nameOfFile->Size = System::Drawing::Size(143, 20);
			this->nameOfFile->TabIndex = 15;
			this->nameOfFile->Text = L"TEMP.csv";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(273, 435);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(104, 13);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Name of file to save:";
			// 
			// saveToFile
			// 
			this->saveToFile->Location = System::Drawing::Point(426, 452);
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
			this->label7->Location = System::Drawing::Point(241, 95);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(113, 13);
			this->label7->TabIndex = 19;
			this->label7->Text = L"Select files to process:";
			// 
			// preview
			// 
			this->preview->Location = System::Drawing::Point(204, 389);
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
			this->saveSelectedBox->Location = System::Drawing::Point(12, 237);
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
			this->groupBox1->Location = System::Drawing::Point(132, 61);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(103, 49);
			this->groupBox1->TabIndex = 28;
			this->groupBox1->TabStop = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(241, 24);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(192, 13);
			this->label8->TabIndex = 30;
			this->label8->Text = L"Noise cutoff (select before loading files)";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(364, 46);
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
			this->standardToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->standardToolStripMenuItem->Text = L"Standard";
			this->standardToolStripMenuItem->Click += gcnew System::EventHandler(this, &Window::standardToolStripMenuItem_Click);
			// 
			// calibrationToolStripMenuItem
			// 
			this->calibrationToolStripMenuItem->Name = L"calibrationToolStripMenuItem";
			this->calibrationToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->calibrationToolStripMenuItem->Text = L"Calibration";
			this->calibrationToolStripMenuItem->Click += gcnew System::EventHandler(this, &Window::calibrationToolStripMenuItem_Click);
			// 
			// setAlabel
			// 
			this->setAlabel->AutoSize = true;
			this->setAlabel->Location = System::Drawing::Point(241, 77);
			this->setAlabel->Name = L"setAlabel";
			this->setAlabel->Size = System::Drawing::Size(110, 13);
			this->setAlabel->TabIndex = 34;
			this->setAlabel->Text = L"Single-set processing:";
			// 
			// setBlabel
			// 
			this->setBlabel->AutoSize = true;
			this->setBlabel->Enabled = false;
			this->setBlabel->Location = System::Drawing::Point(241, 141);
			this->setBlabel->Name = L"setBlabel";
			this->setBlabel->Size = System::Drawing::Size(103, 13);
			this->setBlabel->TabIndex = 39;
			this->setBlabel->Text = L"Multi-set processing:";
			// 
			// selectFilesLabel_setB
			// 
			this->selectFilesLabel_setB->AutoSize = true;
			this->selectFilesLabel_setB->Enabled = false;
			this->selectFilesLabel_setB->Location = System::Drawing::Point(241, 221);
			this->selectFilesLabel_setB->Name = L"selectFilesLabel_setB";
			this->selectFilesLabel_setB->Size = System::Drawing::Size(113, 13);
			this->selectFilesLabel_setB->TabIndex = 36;
			this->selectFilesLabel_setB->Text = L"Select files to process:";
			// 
			// fileSelect_setB
			// 
			this->fileSelect_setB->Enabled = false;
			this->fileSelect_setB->Location = System::Drawing::Point(425, 219);
			this->fileSelect_setB->Name = L"fileSelect_setB";
			this->fileSelect_setB->Size = System::Drawing::Size(75, 23);
			this->fileSelect_setB->TabIndex = 35;
			this->fileSelect_setB->Text = L"Browse...";
			this->fileSelect_setB->UseVisualStyleBackColor = true;
			this->fileSelect_setB->Click += gcnew System::EventHandler(this, &Window::fileSelect_setB_Click);
			// 
			// analyteLabel_setB
			// 
			this->analyteLabel_setB->AutoSize = true;
			this->analyteLabel_setB->Enabled = false;
			this->analyteLabel_setB->Location = System::Drawing::Point(241, 244);
			this->analyteLabel_setB->Name = L"analyteLabel_setB";
			this->analyteLabel_setB->Size = System::Drawing::Size(174, 13);
			this->analyteLabel_setB->TabIndex = 43;
			this->analyteLabel_setB->Text = L"Analyte concentration for given set:";
			// 
			// howManyLabel
			// 
			this->howManyLabel->AutoSize = true;
			this->howManyLabel->Enabled = false;
			this->howManyLabel->Location = System::Drawing::Point(241, 157);
			this->howManyLabel->Name = L"howManyLabel";
			this->howManyLabel->Size = System::Drawing::Size(131, 13);
			this->howManyLabel->TabIndex = 47;
			this->howManyLabel->Text = L"How may sets to process\?";
			// 
			// howManySubmit
			// 
			this->howManySubmit->Enabled = false;
			this->howManySubmit->Location = System::Drawing::Point(425, 176);
			this->howManySubmit->Name = L"howManySubmit";
			this->howManySubmit->Size = System::Drawing::Size(75, 23);
			this->howManySubmit->TabIndex = 46;
			this->howManySubmit->Text = L"Submit";
			this->howManySubmit->UseVisualStyleBackColor = true;
			this->howManySubmit->Click += gcnew System::EventHandler(this, &Window::howManySubmit_Click);
			// 
			// howManySets
			// 
			this->howManySets->Enabled = false;
			this->howManySets->Location = System::Drawing::Point(244, 176);
			this->howManySets->Name = L"howManySets";
			this->howManySets->Size = System::Drawing::Size(100, 20);
			this->howManySets->TabIndex = 45;
			// 
			// setsOfData
			// 
			this->setsOfData->Enabled = false;
			this->setsOfData->FormattingEnabled = true;
			this->setsOfData->Location = System::Drawing::Point(244, 311);
			this->setsOfData->MaxDropDownItems = 20;
			this->setsOfData->Name = L"setsOfData";
			this->setsOfData->Size = System::Drawing::Size(256, 21);
			this->setsOfData->TabIndex = 48;
			// 
			// setsOfData_label
			// 
			this->setsOfData_label->AutoSize = true;
			this->setsOfData_label->Enabled = false;
			this->setsOfData_label->Location = System::Drawing::Point(241, 295);
			this->setsOfData_label->Name = L"setsOfData_label";
			this->setsOfData_label->Size = System::Drawing::Size(118, 13);
			this->setsOfData_label->TabIndex = 49;
			this->setsOfData_label->Text = L"Sets of data information";
			// 
			// addSetButton
			// 
			this->addSetButton->Enabled = false;
			this->addSetButton->Location = System::Drawing::Point(425, 258);
			this->addSetButton->Name = L"addSetButton";
			this->addSetButton->Size = System::Drawing::Size(75, 23);
			this->addSetButton->TabIndex = 50;
			this->addSetButton->Text = L"Add set";
			this->addSetButton->UseVisualStyleBackColor = true;
			this->addSetButton->Click += gcnew System::EventHandler(this, &Window::addSetButton_Click);
			// 
			// Rscore
			// 
			this->Rscore->AutoSize = true;
			this->Rscore->Location = System::Drawing::Point(201, 413);
			this->Rscore->Name = L"Rscore";
			this->Rscore->Size = System::Drawing::Size(0, 13);
			this->Rscore->TabIndex = 51;
			// 
			// rangeLowerInput
			// 
			this->rangeLowerInput->Location = System::Drawing::Point(12, 129);
			this->rangeLowerInput->Name = L"rangeLowerInput";
			this->rangeLowerInput->Size = System::Drawing::Size(100, 20);
			this->rangeLowerInput->TabIndex = 52;
			this->rangeLowerInput->Text = L"0.2";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 113);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(147, 13);
			this->label1->TabIndex = 53;
			this->label1->Text = L"Range for finding lowest point";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->lowerRangeYes);
			this->groupBox2->Controls->Add(this->radioButton2);
			this->groupBox2->Location = System::Drawing::Point(176, 113);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(59, 49);
			this->groupBox2->TabIndex = 29;
			this->groupBox2->TabStop = false;
			// 
			// lowerRangeYes
			// 
			this->lowerRangeYes->AutoSize = true;
			this->lowerRangeYes->Checked = true;
			this->lowerRangeYes->Location = System::Drawing::Point(6, 10);
			this->lowerRangeYes->Name = L"lowerRangeYes";
			this->lowerRangeYes->Size = System::Drawing::Size(43, 17);
			this->lowerRangeYes->TabIndex = 26;
			this->lowerRangeYes->TabStop = true;
			this->lowerRangeYes->Text = L"Yes";
			this->lowerRangeYes->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(6, 26);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(46, 17);
			this->radioButton2->TabIndex = 27;
			this->radioButton2->Text = L"Skip";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// Window
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(519, 495);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->rangeLowerInput);
			this->Controls->Add(this->Rscore);
			this->Controls->Add(this->addSetButton);
			this->Controls->Add(this->setsOfData_label);
			this->Controls->Add(this->setsOfData);
			this->Controls->Add(this->howManyLabel);
			this->Controls->Add(this->howManySubmit);
			this->Controls->Add(this->howManySets);
			this->Controls->Add(this->setNumbersLabel);
			this->Controls->Add(this->analyteLabel_setB);
			this->Controls->Add(this->analyteBox_setB);
			this->Controls->Add(this->setBlabel);
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
			this->Controls->Add(this->label2);
			this->Controls->Add(this->waveSubmit);
			this->Controls->Add(this->waveEdit);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Window";
			this->Text = L"Zeus";
			this->Load += gcnew System::EventHandler(this, &Window::Window_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
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
			attemptConversion = Convert::ToSingle(waveEdit->Text);
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
		float waveToRemove = Convert::ToSingle(allWavelenghts->Text);
		b.removeWavelength(waveToRemove);
		allWavelenghts->DataSource = nullptr;
		allWavelenghts->DataSource = b.selectedWavelengths;
	}

	//GUI handler - preview all options - actually processes the data for now as well
	private: System::Void preview_Click(System::Object^ sender, System::EventArgs^ e) {
		if (b.getAveragedSpectra()) {}
		else { MessageBox::Show("Error - no files loaded"); return; }
		int option;
		//option 1 - highest point in range, skip range for finding lowest point
		//option 2 - sum in range, skip range for finding lowest point
		//option 3 - highest point in range, yes for range for finding lowest point
		//option 4 - sum in range, yes for range for finding lowest point
		if (highestCheckbox->Checked) { option = 1; }
		
		float range;
		float lowerRange;
		try {
			range = Convert::ToSingle(rangeInput->Text);
			lowerRange = Convert::ToSingle(rangeLowerInput->Text);
			if (range < 0) { range = -1 * range; };
		}
		catch (...) {
			MessageBox::Show("Error - range must be a float");
			return;
		}
		//Perform operations to retrieve division information 
		if (calibrationToolStripMenuItem->Checked) {
			b.getRequestedSpectraCalibrationMode(option, range, lowerRangeYes->Checked, lowerRange);
			Rscore->Text = "R^2 score: " + Convert::ToString(b.getRSquared());
		}
		//standard mode operation
		else {
			b.getRequestedSpectraStandardMode(option, range, lowerRangeYes->Checked, lowerRange);
			
		}
	}

	//GUI handler - save file
	private: System::Void saveToFile_Click(System::Object^ sender, System::EventArgs^ e) {
		if (calibrationToolStripMenuItem->Checked) {
			int success = b.saveToFileCalibration(nameOfFile->Text, "TODO", analyteBox_setB->Text);
			if(success == 0){
				MessageBox::Show("Error - file was unable to be saved with name " + b.nameOfFile);

			}
			else if (success == 1) {
				MessageBox::Show("File saved at " + b.directory + b.nameOfFile);
			}
			else{
				MessageBox::Show("Error - one of the data structures has not been initialized. This most often happens if 'Process' has not been clicked. ");
			}
		}
		//standard mode saving.
		else {
			int success = b.saveToFile(nameOfFile->Text, saveSelectedBox->Checked);
			if (success == 0) {
				MessageBox::Show("Error - file was unable to be saved with name " + b.nameOfFile);
			}

			else if (success == 1) {
				MessageBox::Show("File saved at " + b.directory + b.nameOfFile);
			}
			else{
				MessageBox::Show("Error - one of the data structures has not been initialized. This most often happens if 'Process' has not been clicked. ");
			}
		}


	}

	//GUI handler - load the files into the system
	private: System::Void fileSelect_Click(System::Object^ sender, System::EventArgs^ e) {
		handleSelection(1);
	}

	 private: System::Void fileSelect_setB_Click(System::Object^ sender, System::EventArgs^ e) {
		 handleSelection(2);
		 selectFilesLabel_setB->Text = "Files selected.";
	 }
	private: System::Void Window_Load(System::Object^ sender, System::EventArgs^ e) {
	}

private: System::Void standardToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	setCalibrationGroup(true);

}
private: System::Void calibrationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	setCalibrationGroup(false);

}	
	   //HANDLER - see how many sets the user is trying to initialize
	   private: System::Void howManySubmit_Click(System::Object^ sender, System::EventArgs^ e) {
		   int attemptConversion;
		   try {
			   attemptConversion = Convert::ToInt32(howManySets->Text);
		   }
		   catch (...) {
			   MessageBox::Show("Error - please input an integer value");
			   return;
		   }
		   b.initializeSets(attemptConversion);
		   setsOfData->DataSource = nullptr;
		   setsOfData->DataSource = b.metadata;
		   howManySets->Text = "";


	   }
		//HANDLER - initialize sets in the backend
	private: System::Void addSetButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (b.filesToExtract_B == nullptr || b.filesToExtract_B->Count == 0) {
			MessageBox::Show("Error - no files selected");
			return;
		}
		if (b.metadata == nullptr || b.metadata->Count == 0) {
			MessageBox::Show("Error - no empty sets initialized");
			return;
		}
		float concentration;
		try {
			concentration = Convert::ToSingle(analyteBox_setB->Text);
		}
		catch (...) {
			MessageBox::Show("Error - please input a float value for the concentration");
			return;
		}
		int i = setsOfData->SelectedIndex;
		float cutoff;
		try {
			cutoff = Convert::ToSingle(noiseCutoff->Text);
		}
		catch (...) {
			cutoff = -199;
		}

		b.addSetToSets(concentration, i, cutoff);
		setsOfData->DataSource = nullptr;
		setsOfData->DataSource = b.metadata;
		selectFilesLabel_setB->Text = "Select files to process:.";
		setsOfData->SelectedIndex = i >= b.metadata->Count-1 ? i : i + 1;
		return;
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
					cutoff = Convert::ToSingle(noiseCutoff->Text);
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
					//noOfFiles_setB->Text = "files selected: " + fileOpener->FileNames->Length;
					if (cutoff == -199) {
						//cutoffLabel_setB->Text = "at no cutoff. ";
					}
					else {
						//cutoffLabel_setB->Text = "at cutoff: " + cutoff;
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
		//single set processing bit
		setAlabel->Enabled = value;
		label7 -> Enabled = value;
		fileSelect->Enabled = value;
		noOfFiles->Enabled = value;
		cutoffLabel->Enabled = value;
		//dual set processing bit
		setBlabel->Enabled = !value;
		howManyLabel->Enabled = !value;
		howManySets->Enabled = !value;
		howManySubmit->Enabled = !value;
		selectFilesLabel_setB->Enabled = !value;
		analyteLabel_setB->Enabled = !value;
		analyteBox_setB->Enabled = !value;
		fileSelect_setB->Enabled = !value;
		selectFilesLabel_setB->Enabled = !value;
		addSetButton->Enabled = !value;
		//information
		setsOfData->Enabled = !value;
		setsOfData_label->Enabled = !value;
		//left hand side
		label3->Enabled = value;
		//rangeInput->Enabled = value;
		setNumbersLabel->Enabled = !value;
		saveSelectedBox->Enabled = value;

		   }
};
}
