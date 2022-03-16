#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include "Chart.h"

Chart theChart;
int SelectedLineType = 1;
int SelectedNoteType = 1;

int findLine(std::list<NotesNode>::iterator nextNode) {
	int outputLine = 0;

	for (std::list<NotesNode>::iterator itr = theChart.Notes.begin(); itr != theChart.Notes.end(); itr++) {
		if (itr == nextNode)
			break;
		outputLine++;
	}

	return outputLine;
}

bool sortNotesListByBeat(const NotesNode& lhs, const NotesNode& rhs) {
	if (lhs.beat < rhs.beat)
		return true;
	else if ((lhs.beat == rhs.beat) && (lhs.subBeat < rhs.subBeat))
		return true;
	else
		return false;
}
bool sortPreChartListByBeat(const PreChartNode& lhs, const PreChartNode& rhs) {
	if (lhs.beat < rhs.beat)
		return true;
	else if ((lhs.beat == rhs.beat) && (lhs.subBeat < rhs.subBeat))
		return true;
	else
		return false;
}

namespace BAKKAEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip;
	protected:

	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::Button^ TapButton;
	private: System::Windows::Forms::Button^ OrangeButton;
	private: System::Windows::Forms::Button^ GreenButton;





	private: System::Windows::Forms::Button^ RedButton;
	private: System::Windows::Forms::Button^ BlueButton;
	private: System::Windows::Forms::Button^ YellowButton;
	private: System::Windows::Forms::Button^ HoldButton;
	private: System::Windows::Forms::Button^ EndChartButton;


	private: System::Windows::Forms::GroupBox^ NoteTypeBox;




	private: System::Windows::Forms::ToolTip^ ToolTip;

	private: System::Windows::Forms::CheckBox^ EndHoldBox;
	private: System::Windows::Forms::Button^ InsertButton;
	private: System::Windows::Forms::Label^ PosLabel;
	private: System::Windows::Forms::Label^ posInfo;
	private: System::Windows::Forms::NumericUpDown^ SizeNum;
	private: System::Windows::Forms::Label^ SizeInfo;
	private: System::Windows::Forms::Label^ SizeLabel;
	private: System::Windows::Forms::NumericUpDown^ PosNum;
	private: System::Windows::Forms::Panel^ NoteSizeBox;


	private: System::Windows::Forms::GroupBox^ GimmickBox;
	private: System::Windows::Forms::Button^ Mask;
	private: System::Windows::Forms::RadioButton^ RemoveMask;
	private: System::Windows::Forms::RadioButton^ AddMask;
	private: System::Windows::Forms::Button^ Reverse;
	private: System::Windows::Forms::Button^ Stop;
	private: System::Windows::Forms::Button^ Hispeed;
	private: System::Windows::Forms::Button^ TimeSignature;
	private: System::Windows::Forms::Button^ BPMChange;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::NumericUpDown^ SubBeat2Num;
	private: System::Windows::Forms::NumericUpDown^ SubBeat1Num;
	private: System::Windows::Forms::NumericUpDown^ BeatNum;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ Beat;
	private: System::Windows::Forms::GroupBox^ GimmickSettingsBox;
	private: System::Windows::Forms::NumericUpDown^ HiSpeedChangeNum;
	private: System::Windows::Forms::NumericUpDown^ TimeSigNum2;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::NumericUpDown^ TimeSigNum1;
	private: System::Windows::Forms::NumericUpDown^ BPMChangeNum;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd2SBNum2;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd2SBNum1;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd2BNum;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd1SBNum2;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd1SBNum1;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd1BNum;
	private: System::Windows::Forms::NumericUpDown^ StopEndBNum;
	private: System::Windows::Forms::NumericUpDown^ StopEndSBNum2;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::NumericUpDown^ StopEndSBNum1;
	private: System::Windows::Forms::GroupBox^ InitialSettingsPane;
	private: System::Windows::Forms::NumericUpDown^ MovieOffsetNum;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::NumericUpDown^ OffsetNum;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::NumericUpDown^ InitTimeSigNum2;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::NumericUpDown^ InitTimeSigNum1;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::NumericUpDown^ InitialBPMNum;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
private: System::Windows::Forms::RadioButton^ BonusFlairRadioButton;
private: System::Windows::Forms::RadioButton^ BonusGetRadioButton;
private: System::Windows::Forms::RadioButton^ NoBonusRadioButton;
private: System::Windows::Forms::Button^ InitialSetSave;
private: System::Windows::Forms::GroupBox^ MaskSettingsBox;
private: System::Windows::Forms::RadioButton^ MaskCenter;
private: System::Windows::Forms::RadioButton^ MaskCClockwise;
private: System::Windows::Forms::RadioButton^ MaskClockwise;
private: System::Windows::Forms::Label^ label18;
private: System::Windows::Forms::Label^ CurrentObjectText;




















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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TapButton = (gcnew System::Windows::Forms::Button());
			this->OrangeButton = (gcnew System::Windows::Forms::Button());
			this->GreenButton = (gcnew System::Windows::Forms::Button());
			this->RedButton = (gcnew System::Windows::Forms::Button());
			this->BlueButton = (gcnew System::Windows::Forms::Button());
			this->YellowButton = (gcnew System::Windows::Forms::Button());
			this->HoldButton = (gcnew System::Windows::Forms::Button());
			this->EndChartButton = (gcnew System::Windows::Forms::Button());
			this->NoteTypeBox = (gcnew System::Windows::Forms::GroupBox());
			this->BonusFlairRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->BonusGetRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->NoBonusRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->EndHoldBox = (gcnew System::Windows::Forms::CheckBox());
			this->ToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->BPMChange = (gcnew System::Windows::Forms::Button());
			this->TimeSignature = (gcnew System::Windows::Forms::Button());
			this->Hispeed = (gcnew System::Windows::Forms::Button());
			this->Stop = (gcnew System::Windows::Forms::Button());
			this->Reverse = (gcnew System::Windows::Forms::Button());
			this->InsertButton = (gcnew System::Windows::Forms::Button());
			this->PosLabel = (gcnew System::Windows::Forms::Label());
			this->posInfo = (gcnew System::Windows::Forms::Label());
			this->SizeNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->SizeInfo = (gcnew System::Windows::Forms::Label());
			this->SizeLabel = (gcnew System::Windows::Forms::Label());
			this->PosNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->NoteSizeBox = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SubBeat2Num = (gcnew System::Windows::Forms::NumericUpDown());
			this->SubBeat1Num = (gcnew System::Windows::Forms::NumericUpDown());
			this->BeatNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Beat = (gcnew System::Windows::Forms::Label());
			this->GimmickBox = (gcnew System::Windows::Forms::GroupBox());
			this->RemoveMask = (gcnew System::Windows::Forms::RadioButton());
			this->AddMask = (gcnew System::Windows::Forms::RadioButton());
			this->Mask = (gcnew System::Windows::Forms::Button());
			this->GimmickSettingsBox = (gcnew System::Windows::Forms::GroupBox());
			this->ReverseEnd2SBNum2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->ReverseEnd2SBNum1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->ReverseEnd2BNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->ReverseEnd1SBNum2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->ReverseEnd1SBNum1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->ReverseEnd1BNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->StopEndBNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->StopEndSBNum2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->StopEndSBNum1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->HiSpeedChangeNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->TimeSigNum2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->TimeSigNum1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->BPMChangeNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->InitialSettingsPane = (gcnew System::Windows::Forms::GroupBox());
			this->InitialSetSave = (gcnew System::Windows::Forms::Button());
			this->MovieOffsetNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->OffsetNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->InitTimeSigNum2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->InitTimeSigNum1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->InitialBPMNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->MaskSettingsBox = (gcnew System::Windows::Forms::GroupBox());
			this->MaskCenter = (gcnew System::Windows::Forms::RadioButton());
			this->MaskCClockwise = (gcnew System::Windows::Forms::RadioButton());
			this->MaskClockwise = (gcnew System::Windows::Forms::RadioButton());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->CurrentObjectText = (gcnew System::Windows::Forms::Label());
			this->menuStrip->SuspendLayout();
			this->NoteTypeBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SizeNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PosNum))->BeginInit();
			this->NoteSizeBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SubBeat2Num))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SubBeat1Num))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BeatNum))->BeginInit();
			this->GimmickBox->SuspendLayout();
			this->GimmickSettingsBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2SBNum2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2SBNum1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2BNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1SBNum2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1SBNum1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1BNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndBNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndSBNum2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndSBNum1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HiSpeedChangeNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TimeSigNum2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TimeSigNum1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BPMChangeNum))->BeginInit();
			this->InitialSettingsPane->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MovieOffsetNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OffsetNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InitTimeSigNum2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InitTimeSigNum1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InitialBPMNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->MaskSettingsBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			resources->ApplyResources(this->menuStrip, L"menuStrip");
			this->menuStrip->Name = L"menuStrip";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->newToolStripMenuItem,
					this->openToolStripMenuItem, this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			resources->ApplyResources(this->fileToolStripMenuItem, L"fileToolStripMenuItem");
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			resources->ApplyResources(this->newToolStripMenuItem, L"newToolStripMenuItem");
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			resources->ApplyResources(this->openToolStripMenuItem, L"openToolStripMenuItem");
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			resources->ApplyResources(this->saveToolStripMenuItem, L"saveToolStripMenuItem");
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			resources->ApplyResources(this->saveAsToolStripMenuItem, L"saveAsToolStripMenuItem");
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveAsToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			resources->ApplyResources(this->exitToolStripMenuItem, L"exitToolStripMenuItem");
			// 
			// TapButton
			// 
			resources->ApplyResources(this->TapButton, L"TapButton");
			this->TapButton->Name = L"TapButton";
			this->TapButton->UseVisualStyleBackColor = true;
			this->TapButton->Click += gcnew System::EventHandler(this, &MyForm::TapButton_Click);
			// 
			// OrangeButton
			// 
			resources->ApplyResources(this->OrangeButton, L"OrangeButton");
			this->OrangeButton->Name = L"OrangeButton";
			this->OrangeButton->UseVisualStyleBackColor = true;
			this->OrangeButton->Click += gcnew System::EventHandler(this, &MyForm::OrangeButton_Click);
			// 
			// GreenButton
			// 
			resources->ApplyResources(this->GreenButton, L"GreenButton");
			this->GreenButton->Name = L"GreenButton";
			this->GreenButton->UseVisualStyleBackColor = true;
			this->GreenButton->Click += gcnew System::EventHandler(this, &MyForm::GreenButton_Click);
			// 
			// RedButton
			// 
			resources->ApplyResources(this->RedButton, L"RedButton");
			this->RedButton->Name = L"RedButton";
			this->RedButton->UseVisualStyleBackColor = true;
			this->RedButton->Click += gcnew System::EventHandler(this, &MyForm::RedButton_Click);
			// 
			// BlueButton
			// 
			resources->ApplyResources(this->BlueButton, L"BlueButton");
			this->BlueButton->Name = L"BlueButton";
			this->BlueButton->UseVisualStyleBackColor = true;
			this->BlueButton->Click += gcnew System::EventHandler(this, &MyForm::BlueButton_Click);
			// 
			// YellowButton
			// 
			resources->ApplyResources(this->YellowButton, L"YellowButton");
			this->YellowButton->Name = L"YellowButton";
			this->YellowButton->UseVisualStyleBackColor = true;
			this->YellowButton->Click += gcnew System::EventHandler(this, &MyForm::YellowButton_Click);
			// 
			// HoldButton
			// 
			resources->ApplyResources(this->HoldButton, L"HoldButton");
			this->HoldButton->Name = L"HoldButton";
			this->ToolTip->SetToolTip(this->HoldButton, resources->GetString(L"HoldButton.ToolTip"));
			this->HoldButton->UseVisualStyleBackColor = true;
			this->HoldButton->Click += gcnew System::EventHandler(this, &MyForm::HoldButton_Click);
			// 
			// EndChartButton
			// 
			resources->ApplyResources(this->EndChartButton, L"EndChartButton");
			this->EndChartButton->Name = L"EndChartButton";
			this->ToolTip->SetToolTip(this->EndChartButton, resources->GetString(L"EndChartButton.ToolTip"));
			this->EndChartButton->UseVisualStyleBackColor = true;
			this->EndChartButton->Click += gcnew System::EventHandler(this, &MyForm::EndChartButton_Click);
			// 
			// NoteTypeBox
			// 
			this->NoteTypeBox->Controls->Add(this->BonusFlairRadioButton);
			this->NoteTypeBox->Controls->Add(this->BonusGetRadioButton);
			this->NoteTypeBox->Controls->Add(this->NoBonusRadioButton);
			this->NoteTypeBox->Controls->Add(this->EndHoldBox);
			this->NoteTypeBox->Controls->Add(this->EndChartButton);
			this->NoteTypeBox->Controls->Add(this->TapButton);
			this->NoteTypeBox->Controls->Add(this->HoldButton);
			this->NoteTypeBox->Controls->Add(this->OrangeButton);
			this->NoteTypeBox->Controls->Add(this->YellowButton);
			this->NoteTypeBox->Controls->Add(this->GreenButton);
			this->NoteTypeBox->Controls->Add(this->BlueButton);
			this->NoteTypeBox->Controls->Add(this->RedButton);
			resources->ApplyResources(this->NoteTypeBox, L"NoteTypeBox");
			this->NoteTypeBox->Name = L"NoteTypeBox";
			this->NoteTypeBox->TabStop = false;
			// 
			// BonusFlairRadioButton
			// 
			resources->ApplyResources(this->BonusFlairRadioButton, L"BonusFlairRadioButton");
			this->BonusFlairRadioButton->Name = L"BonusFlairRadioButton";
			this->ToolTip->SetToolTip(this->BonusFlairRadioButton, resources->GetString(L"BonusFlairRadioButton.ToolTip"));
			this->BonusFlairRadioButton->UseVisualStyleBackColor = true;
			this->BonusFlairRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::BonusFlairRadioButton_CheckedChanged);
			// 
			// BonusGetRadioButton
			// 
			resources->ApplyResources(this->BonusGetRadioButton, L"BonusGetRadioButton");
			this->BonusGetRadioButton->Name = L"BonusGetRadioButton";
			this->ToolTip->SetToolTip(this->BonusGetRadioButton, resources->GetString(L"BonusGetRadioButton.ToolTip"));
			this->BonusGetRadioButton->UseVisualStyleBackColor = true;
			this->BonusGetRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::BonusGetRadioButton_CheckedChanged);
			// 
			// NoBonusRadioButton
			// 
			resources->ApplyResources(this->NoBonusRadioButton, L"NoBonusRadioButton");
			this->NoBonusRadioButton->Checked = true;
			this->NoBonusRadioButton->Name = L"NoBonusRadioButton";
			this->NoBonusRadioButton->TabStop = true;
			this->NoBonusRadioButton->UseVisualStyleBackColor = true;
			this->NoBonusRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::NoBonusRadioButton_CheckedChanged);
			// 
			// EndHoldBox
			// 
			resources->ApplyResources(this->EndHoldBox, L"EndHoldBox");
			this->EndHoldBox->Name = L"EndHoldBox";
			this->ToolTip->SetToolTip(this->EndHoldBox, resources->GetString(L"EndHoldBox.ToolTip"));
			this->EndHoldBox->UseVisualStyleBackColor = true;
			this->EndHoldBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::EndHoldBox_CheckedChanged);
			// 
			// BPMChange
			// 
			resources->ApplyResources(this->BPMChange, L"BPMChange");
			this->BPMChange->Name = L"BPMChange";
			this->ToolTip->SetToolTip(this->BPMChange, resources->GetString(L"BPMChange.ToolTip"));
			this->BPMChange->UseVisualStyleBackColor = true;
			this->BPMChange->Click += gcnew System::EventHandler(this, &MyForm::BPMChange_Click);
			// 
			// TimeSignature
			// 
			resources->ApplyResources(this->TimeSignature, L"TimeSignature");
			this->TimeSignature->Name = L"TimeSignature";
			this->ToolTip->SetToolTip(this->TimeSignature, resources->GetString(L"TimeSignature.ToolTip"));
			this->TimeSignature->UseVisualStyleBackColor = true;
			this->TimeSignature->Click += gcnew System::EventHandler(this, &MyForm::TimeSignature_Click);
			// 
			// Hispeed
			// 
			resources->ApplyResources(this->Hispeed, L"Hispeed");
			this->Hispeed->Name = L"Hispeed";
			this->ToolTip->SetToolTip(this->Hispeed, resources->GetString(L"Hispeed.ToolTip"));
			this->Hispeed->UseVisualStyleBackColor = true;
			this->Hispeed->Click += gcnew System::EventHandler(this, &MyForm::Hispeed_Click);
			// 
			// Stop
			// 
			resources->ApplyResources(this->Stop, L"Stop");
			this->Stop->Name = L"Stop";
			this->ToolTip->SetToolTip(this->Stop, resources->GetString(L"Stop.ToolTip"));
			this->Stop->UseVisualStyleBackColor = true;
			this->Stop->Click += gcnew System::EventHandler(this, &MyForm::Stop_Click);
			// 
			// Reverse
			// 
			resources->ApplyResources(this->Reverse, L"Reverse");
			this->Reverse->Name = L"Reverse";
			this->ToolTip->SetToolTip(this->Reverse, resources->GetString(L"Reverse.ToolTip"));
			this->Reverse->UseVisualStyleBackColor = true;
			this->Reverse->Click += gcnew System::EventHandler(this, &MyForm::Reverse_Click);
			// 
			// InsertButton
			// 
			resources->ApplyResources(this->InsertButton, L"InsertButton");
			this->InsertButton->Name = L"InsertButton";
			this->InsertButton->UseVisualStyleBackColor = true;
			this->InsertButton->Click += gcnew System::EventHandler(this, &MyForm::InsertButton_Click);
			// 
			// PosLabel
			// 
			resources->ApplyResources(this->PosLabel, L"PosLabel");
			this->PosLabel->Name = L"PosLabel";
			// 
			// posInfo
			// 
			resources->ApplyResources(this->posInfo, L"posInfo");
			this->posInfo->Name = L"posInfo";
			// 
			// SizeNum
			// 
			resources->ApplyResources(this->SizeNum, L"SizeNum");
			this->SizeNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 60, 0, 0, 0 });
			this->SizeNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->SizeNum->Name = L"SizeNum";
			this->SizeNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// SizeInfo
			// 
			resources->ApplyResources(this->SizeInfo, L"SizeInfo");
			this->SizeInfo->Name = L"SizeInfo";
			// 
			// SizeLabel
			// 
			resources->ApplyResources(this->SizeLabel, L"SizeLabel");
			this->SizeLabel->Name = L"SizeLabel";
			// 
			// PosNum
			// 
			resources->ApplyResources(this->PosNum, L"PosNum");
			this->PosNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 59, 0, 0, 0 });
			this->PosNum->Name = L"PosNum";
			// 
			// NoteSizeBox
			// 
			this->NoteSizeBox->Controls->Add(this->label1);
			this->NoteSizeBox->Controls->Add(this->SubBeat2Num);
			this->NoteSizeBox->Controls->Add(this->SubBeat1Num);
			this->NoteSizeBox->Controls->Add(this->BeatNum);
			this->NoteSizeBox->Controls->Add(this->label2);
			this->NoteSizeBox->Controls->Add(this->PosNum);
			this->NoteSizeBox->Controls->Add(this->Beat);
			this->NoteSizeBox->Controls->Add(this->SizeLabel);
			this->NoteSizeBox->Controls->Add(this->SizeInfo);
			this->NoteSizeBox->Controls->Add(this->PosLabel);
			this->NoteSizeBox->Controls->Add(this->posInfo);
			this->NoteSizeBox->Controls->Add(this->SizeNum);
			resources->ApplyResources(this->NoteSizeBox, L"NoteSizeBox");
			this->NoteSizeBox->Name = L"NoteSizeBox";
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->Name = L"label1";
			// 
			// SubBeat2Num
			// 
			resources->ApplyResources(this->SubBeat2Num, L"SubBeat2Num");
			this->SubBeat2Num->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 192, 0, 0, 0 });
			this->SubBeat2Num->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->SubBeat2Num->Name = L"SubBeat2Num";
			this->SubBeat2Num->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// SubBeat1Num
			// 
			resources->ApplyResources(this->SubBeat1Num, L"SubBeat1Num");
			this->SubBeat1Num->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 191, 0, 0, 0 });
			this->SubBeat1Num->Name = L"SubBeat1Num";
			// 
			// BeatNum
			// 
			resources->ApplyResources(this->BeatNum, L"BeatNum");
			this->BeatNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->BeatNum->Name = L"BeatNum";
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->Name = L"label2";
			// 
			// Beat
			// 
			resources->ApplyResources(this->Beat, L"Beat");
			this->Beat->Name = L"Beat";
			// 
			// GimmickBox
			// 
			this->GimmickBox->Controls->Add(this->Reverse);
			this->GimmickBox->Controls->Add(this->Stop);
			this->GimmickBox->Controls->Add(this->Hispeed);
			this->GimmickBox->Controls->Add(this->TimeSignature);
			this->GimmickBox->Controls->Add(this->BPMChange);
			this->GimmickBox->Controls->Add(this->RemoveMask);
			this->GimmickBox->Controls->Add(this->AddMask);
			this->GimmickBox->Controls->Add(this->Mask);
			resources->ApplyResources(this->GimmickBox, L"GimmickBox");
			this->GimmickBox->Name = L"GimmickBox";
			this->GimmickBox->TabStop = false;
			// 
			// RemoveMask
			// 
			resources->ApplyResources(this->RemoveMask, L"RemoveMask");
			this->RemoveMask->Name = L"RemoveMask";
			this->RemoveMask->UseVisualStyleBackColor = true;
			this->RemoveMask->CheckedChanged += gcnew System::EventHandler(this, &MyForm::RemoveMask_CheckedChanged);
			// 
			// AddMask
			// 
			resources->ApplyResources(this->AddMask, L"AddMask");
			this->AddMask->Checked = true;
			this->AddMask->Name = L"AddMask";
			this->AddMask->TabStop = true;
			this->AddMask->UseVisualStyleBackColor = true;
			this->AddMask->CheckedChanged += gcnew System::EventHandler(this, &MyForm::AddMask_CheckedChanged);
			// 
			// Mask
			// 
			resources->ApplyResources(this->Mask, L"Mask");
			this->Mask->Name = L"Mask";
			this->Mask->UseVisualStyleBackColor = true;
			this->Mask->Click += gcnew System::EventHandler(this, &MyForm::Mask_Click);
			// 
			// GimmickSettingsBox
			// 
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd2SBNum2);
			this->GimmickSettingsBox->Controls->Add(this->label12);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd2SBNum1);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd2BNum);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd1SBNum2);
			this->GimmickSettingsBox->Controls->Add(this->label11);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd1SBNum1);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd1BNum);
			this->GimmickSettingsBox->Controls->Add(this->StopEndBNum);
			this->GimmickSettingsBox->Controls->Add(this->StopEndSBNum2);
			this->GimmickSettingsBox->Controls->Add(this->label10);
			this->GimmickSettingsBox->Controls->Add(this->StopEndSBNum1);
			this->GimmickSettingsBox->Controls->Add(this->HiSpeedChangeNum);
			this->GimmickSettingsBox->Controls->Add(this->TimeSigNum2);
			this->GimmickSettingsBox->Controls->Add(this->label9);
			this->GimmickSettingsBox->Controls->Add(this->TimeSigNum1);
			this->GimmickSettingsBox->Controls->Add(this->BPMChangeNum);
			this->GimmickSettingsBox->Controls->Add(this->label8);
			this->GimmickSettingsBox->Controls->Add(this->label7);
			this->GimmickSettingsBox->Controls->Add(this->label6);
			this->GimmickSettingsBox->Controls->Add(this->label5);
			this->GimmickSettingsBox->Controls->Add(this->label4);
			this->GimmickSettingsBox->Controls->Add(this->label3);
			resources->ApplyResources(this->GimmickSettingsBox, L"GimmickSettingsBox");
			this->GimmickSettingsBox->Name = L"GimmickSettingsBox";
			this->GimmickSettingsBox->TabStop = false;
			// 
			// ReverseEnd2SBNum2
			// 
			resources->ApplyResources(this->ReverseEnd2SBNum2, L"ReverseEnd2SBNum2");
			this->ReverseEnd2SBNum2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 192, 0, 0, 0 });
			this->ReverseEnd2SBNum2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->ReverseEnd2SBNum2->Name = L"ReverseEnd2SBNum2";
			this->ReverseEnd2SBNum2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// label12
			// 
			resources->ApplyResources(this->label12, L"label12");
			this->label12->Name = L"label12";
			// 
			// ReverseEnd2SBNum1
			// 
			resources->ApplyResources(this->ReverseEnd2SBNum1, L"ReverseEnd2SBNum1");
			this->ReverseEnd2SBNum1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 191, 0, 0, 0 });
			this->ReverseEnd2SBNum1->Name = L"ReverseEnd2SBNum1";
			// 
			// ReverseEnd2BNum
			// 
			resources->ApplyResources(this->ReverseEnd2BNum, L"ReverseEnd2BNum");
			this->ReverseEnd2BNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->ReverseEnd2BNum->Name = L"ReverseEnd2BNum";
			// 
			// ReverseEnd1SBNum2
			// 
			resources->ApplyResources(this->ReverseEnd1SBNum2, L"ReverseEnd1SBNum2");
			this->ReverseEnd1SBNum2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 192, 0, 0, 0 });
			this->ReverseEnd1SBNum2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->ReverseEnd1SBNum2->Name = L"ReverseEnd1SBNum2";
			this->ReverseEnd1SBNum2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// label11
			// 
			resources->ApplyResources(this->label11, L"label11");
			this->label11->Name = L"label11";
			// 
			// ReverseEnd1SBNum1
			// 
			resources->ApplyResources(this->ReverseEnd1SBNum1, L"ReverseEnd1SBNum1");
			this->ReverseEnd1SBNum1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 191, 0, 0, 0 });
			this->ReverseEnd1SBNum1->Name = L"ReverseEnd1SBNum1";
			// 
			// ReverseEnd1BNum
			// 
			resources->ApplyResources(this->ReverseEnd1BNum, L"ReverseEnd1BNum");
			this->ReverseEnd1BNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->ReverseEnd1BNum->Name = L"ReverseEnd1BNum";
			// 
			// StopEndBNum
			// 
			resources->ApplyResources(this->StopEndBNum, L"StopEndBNum");
			this->StopEndBNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->StopEndBNum->Name = L"StopEndBNum";
			// 
			// StopEndSBNum2
			// 
			resources->ApplyResources(this->StopEndSBNum2, L"StopEndSBNum2");
			this->StopEndSBNum2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 192, 0, 0, 0 });
			this->StopEndSBNum2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->StopEndSBNum2->Name = L"StopEndSBNum2";
			this->StopEndSBNum2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// label10
			// 
			resources->ApplyResources(this->label10, L"label10");
			this->label10->Name = L"label10";
			// 
			// StopEndSBNum1
			// 
			resources->ApplyResources(this->StopEndSBNum1, L"StopEndSBNum1");
			this->StopEndSBNum1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 191, 0, 0, 0 });
			this->StopEndSBNum1->Name = L"StopEndSBNum1";
			// 
			// HiSpeedChangeNum
			// 
			this->HiSpeedChangeNum->DecimalPlaces = 6;
			resources->ApplyResources(this->HiSpeedChangeNum, L"HiSpeedChangeNum");
			this->HiSpeedChangeNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->HiSpeedChangeNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
			this->HiSpeedChangeNum->Name = L"HiSpeedChangeNum";
			this->HiSpeedChangeNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// TimeSigNum2
			// 
			resources->ApplyResources(this->TimeSigNum2, L"TimeSigNum2");
			this->TimeSigNum2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 192, 0, 0, 0 });
			this->TimeSigNum2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->TimeSigNum2->Name = L"TimeSigNum2";
			this->TimeSigNum2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// label9
			// 
			resources->ApplyResources(this->label9, L"label9");
			this->label9->Name = L"label9";
			// 
			// TimeSigNum1
			// 
			resources->ApplyResources(this->TimeSigNum1, L"TimeSigNum1");
			this->TimeSigNum1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 191, 0, 0, 0 });
			this->TimeSigNum1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->TimeSigNum1->Name = L"TimeSigNum1";
			this->TimeSigNum1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// BPMChangeNum
			// 
			this->BPMChangeNum->DecimalPlaces = 6;
			resources->ApplyResources(this->BPMChangeNum, L"BPMChangeNum");
			this->BPMChangeNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->BPMChangeNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->BPMChangeNum->Name = L"BPMChangeNum";
			this->BPMChangeNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// label8
			// 
			resources->ApplyResources(this->label8, L"label8");
			this->label8->Name = L"label8";
			// 
			// label7
			// 
			resources->ApplyResources(this->label7, L"label7");
			this->label7->Name = L"label7";
			// 
			// label6
			// 
			resources->ApplyResources(this->label6, L"label6");
			this->label6->Name = L"label6";
			// 
			// label5
			// 
			resources->ApplyResources(this->label5, L"label5");
			this->label5->Name = L"label5";
			// 
			// label4
			// 
			resources->ApplyResources(this->label4, L"label4");
			this->label4->Name = L"label4";
			// 
			// label3
			// 
			resources->ApplyResources(this->label3, L"label3");
			this->label3->Name = L"label3";
			// 
			// InitialSettingsPane
			// 
			this->InitialSettingsPane->Controls->Add(this->InitialSetSave);
			this->InitialSettingsPane->Controls->Add(this->MovieOffsetNum);
			this->InitialSettingsPane->Controls->Add(this->label17);
			this->InitialSettingsPane->Controls->Add(this->OffsetNum);
			this->InitialSettingsPane->Controls->Add(this->label16);
			this->InitialSettingsPane->Controls->Add(this->InitTimeSigNum2);
			this->InitialSettingsPane->Controls->Add(this->label15);
			this->InitialSettingsPane->Controls->Add(this->InitTimeSigNum1);
			this->InitialSettingsPane->Controls->Add(this->label14);
			this->InitialSettingsPane->Controls->Add(this->InitialBPMNum);
			this->InitialSettingsPane->Controls->Add(this->label13);
			resources->ApplyResources(this->InitialSettingsPane, L"InitialSettingsPane");
			this->InitialSettingsPane->Name = L"InitialSettingsPane";
			this->InitialSettingsPane->TabStop = false;
			// 
			// InitialSetSave
			// 
			resources->ApplyResources(this->InitialSetSave, L"InitialSetSave");
			this->InitialSetSave->Name = L"InitialSetSave";
			this->InitialSetSave->UseVisualStyleBackColor = true;
			this->InitialSetSave->Click += gcnew System::EventHandler(this, &MyForm::InitialSetSave_Click);
			// 
			// MovieOffsetNum
			// 
			this->MovieOffsetNum->DecimalPlaces = 6;
			resources->ApplyResources(this->MovieOffsetNum, L"MovieOffsetNum");
			this->MovieOffsetNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->MovieOffsetNum->Name = L"MovieOffsetNum";
			// 
			// label17
			// 
			resources->ApplyResources(this->label17, L"label17");
			this->label17->Name = L"label17";
			// 
			// OffsetNum
			// 
			this->OffsetNum->DecimalPlaces = 6;
			resources->ApplyResources(this->OffsetNum, L"OffsetNum");
			this->OffsetNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->OffsetNum->Name = L"OffsetNum";
			// 
			// label16
			// 
			resources->ApplyResources(this->label16, L"label16");
			this->label16->Name = L"label16";
			// 
			// InitTimeSigNum2
			// 
			resources->ApplyResources(this->InitTimeSigNum2, L"InitTimeSigNum2");
			this->InitTimeSigNum2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 192, 0, 0, 0 });
			this->InitTimeSigNum2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->InitTimeSigNum2->Name = L"InitTimeSigNum2";
			this->InitTimeSigNum2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// label15
			// 
			resources->ApplyResources(this->label15, L"label15");
			this->label15->Name = L"label15";
			// 
			// InitTimeSigNum1
			// 
			resources->ApplyResources(this->InitTimeSigNum1, L"InitTimeSigNum1");
			this->InitTimeSigNum1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 191, 0, 0, 0 });
			this->InitTimeSigNum1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->InitTimeSigNum1->Name = L"InitTimeSigNum1";
			this->InitTimeSigNum1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// label14
			// 
			resources->ApplyResources(this->label14, L"label14");
			this->label14->Name = L"label14";
			// 
			// InitialBPMNum
			// 
			this->InitialBPMNum->DecimalPlaces = 6;
			resources->ApplyResources(this->InitialBPMNum, L"InitialBPMNum");
			this->InitialBPMNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->InitialBPMNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->InitialBPMNum->Name = L"InitialBPMNum";
			this->InitialBPMNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// label13
			// 
			resources->ApplyResources(this->label13, L"label13");
			this->label13->Name = L"label13";
			// 
			// pictureBox1
			// 
			resources->ApplyResources(this->pictureBox1, L"pictureBox1");
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->TabStop = false;
			// 
			// MaskSettingsBox
			// 
			this->MaskSettingsBox->Controls->Add(this->MaskCenter);
			this->MaskSettingsBox->Controls->Add(this->MaskCClockwise);
			this->MaskSettingsBox->Controls->Add(this->MaskClockwise);
			resources->ApplyResources(this->MaskSettingsBox, L"MaskSettingsBox");
			this->MaskSettingsBox->Name = L"MaskSettingsBox";
			this->MaskSettingsBox->TabStop = false;
			// 
			// MaskCenter
			// 
			resources->ApplyResources(this->MaskCenter, L"MaskCenter");
			this->MaskCenter->Name = L"MaskCenter";
			this->MaskCenter->UseVisualStyleBackColor = true;
			this->MaskCenter->CheckedChanged += gcnew System::EventHandler(this, &MyForm::MaskCenter_CheckedChanged);
			// 
			// MaskCClockwise
			// 
			resources->ApplyResources(this->MaskCClockwise, L"MaskCClockwise");
			this->MaskCClockwise->Name = L"MaskCClockwise";
			this->MaskCClockwise->UseVisualStyleBackColor = true;
			this->MaskCClockwise->CheckedChanged += gcnew System::EventHandler(this, &MyForm::MaskCClockwise_CheckedChanged);
			// 
			// MaskClockwise
			// 
			resources->ApplyResources(this->MaskClockwise, L"MaskClockwise");
			this->MaskClockwise->Checked = true;
			this->MaskClockwise->Name = L"MaskClockwise";
			this->MaskClockwise->TabStop = true;
			this->MaskClockwise->UseVisualStyleBackColor = true;
			this->MaskClockwise->CheckedChanged += gcnew System::EventHandler(this, &MyForm::MaskClockwise_CheckedChanged);
			// 
			// label18
			// 
			resources->ApplyResources(this->label18, L"label18");
			this->label18->Name = L"label18";
			// 
			// CurrentObjectText
			// 
			resources->ApplyResources(this->CurrentObjectText, L"CurrentObjectText");
			this->CurrentObjectText->Name = L"CurrentObjectText";
			// 
			// MyForm
			// 
			this->AllowDrop = true;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->CurrentObjectText);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->MaskSettingsBox);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->InitialSettingsPane);
			this->Controls->Add(this->GimmickSettingsBox);
			this->Controls->Add(this->GimmickBox);
			this->Controls->Add(this->NoteSizeBox);
			this->Controls->Add(this->InsertButton);
			this->Controls->Add(this->NoteTypeBox);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"MyForm";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->NoteTypeBox->ResumeLayout(false);
			this->NoteTypeBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SizeNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PosNum))->EndInit();
			this->NoteSizeBox->ResumeLayout(false);
			this->NoteSizeBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SubBeat2Num))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SubBeat1Num))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BeatNum))->EndInit();
			this->GimmickBox->ResumeLayout(false);
			this->GimmickBox->PerformLayout();
			this->GimmickSettingsBox->ResumeLayout(false);
			this->GimmickSettingsBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2SBNum2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2SBNum1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2BNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1SBNum2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1SBNum1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1BNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndBNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndSBNum2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndSBNum1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HiSpeedChangeNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TimeSigNum2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TimeSigNum1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BPMChangeNum))->EndInit();
			this->InitialSettingsPane->ResumeLayout(false);
			this->InitialSettingsPane->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MovieOffsetNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OffsetNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InitTimeSigNum2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InitTimeSigNum1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InitialBPMNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->MaskSettingsBox->ResumeLayout(false);
			this->MaskSettingsBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void newToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		theChart.PreChart.sort(sortPreChartListByBeat);
		theChart.Notes.sort(sortNotesListByBeat);
		
		std::ofstream chartFile;
		chartFile.open("chart.mer");

		chartFile << std::fixed << std::setprecision(6)
			<< "#MUSIC_SCORE_ID 0\n"
			<< "#MUSIC_SCORE_VERSION 0\n"
			<< "#GAME_VERSION \n"
			<< "#MUSIC_FILE_PATH MER_BGM_S00_004 [replace name with actual file name]\n"
			<< "#OFFSET " << theChart.offset << "\n"
			<< "#MOVIEOFFSET " << theChart.movieOffset << "\n"
			<< "#BODY\n";

		for (std::list<PreChartNode>::iterator itr = theChart.PreChart.begin(); itr != theChart.PreChart.end(); itr++) {
			chartFile << std::right << std::fixed << std::setw(4) << (itr)->beat 
					  << std::right << std::fixed << std::setw(5) << (itr)->subBeat
					  << std::right << std::fixed << std::setw(5) << (itr)->type;
			switch ((itr)->type) {
			case 2:
				chartFile << " " << std::right << std::fixed << std::setw(5) << (itr)->BPM;
				break;
			case 3:
				chartFile << std::right << std::fixed << std::setw(5) << (itr)->beatDiv1
						  << std::right << std::fixed << std::setw(5) << (itr)->beatDiv2;
				break;
			case 5:
				chartFile << " " << std::right << std::fixed << std::setw(5) << (itr)->hiSpeed;
				break;
			default:
				chartFile << "";
			}
			chartFile << "\n";
		}

		int line = 0;
		for (std::list<NotesNode>::iterator itr = theChart.Notes.begin(); itr != theChart.Notes.end(); itr++) {
			chartFile << std::right << std::fixed << std::setw(4) << (itr)->beat
					  << std::right << std::fixed << std::setw(5) << (itr)->subBeat
					  << std::right << std::fixed << std::setw(5) << 1
					  << std::right << std::fixed << std::setw(5) << (itr)->noteType
					  << std::right << std::fixed << std::setw(5) << line
					  << std::right << std::fixed << std::setw(5) << (itr)->position
					  << std::right << std::fixed << std::setw(5) << (itr)->size
					  << std::right << std::fixed << std::setw(5) << (itr)->holdChange;
			switch ((itr)->noteType) {
			case 9:
				chartFile << std::right << std::fixed << std::setw(5) << findLine((itr)->nextNode);
				break;
			case 10:
				chartFile << std::right << std::fixed << std::setw(5) << findLine((itr)->nextNode);
				break;
			case 12:
				chartFile << std::right << std::fixed << std::setw(5) << (itr)->BGType;
				break;
			case 13:
				chartFile << std::right << std::fixed << std::setw(5) << (itr)->BGType;
				break;
			default:
				chartFile << "";
			}
			chartFile << "\n";
			line++;
		}

		chartFile.close();
	}
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		theChart.offset = 0.000000;
		theChart.movieOffset = 0.000000;
		theChart.Notes.clear();
		theChart.PreChart.clear();

		std::ifstream chartFile;
		chartFile.open("chart.mer");

		std::string temp;
		while (!chartFile.eof()) {
			if (temp == "#OFFSET") {
				chartFile >> theChart.offset;
				OffsetNum->Value = (System::Decimal)theChart.offset;
			}
			if (temp == "#MOVIEOFFSET") {
				chartFile >> theChart.movieOffset;
				MovieOffsetNum->Value = (System::Decimal)theChart.movieOffset;
			}
			if (temp == "#BODY") {
				break;
			}
			chartFile >> temp;
		}

		int beat;
		int subBeat;
		int type;
		int lineTemp;
		std::map<int, int> Holds;
		NotesNode tempNotes;
		PreChartNode tempPCNode;
		while (!chartFile.eof()) {
			chartFile >> beat >> subBeat >> type;
			if (chartFile.eof()) break;

			switch (type) {
			case 1:
				tempNotes.beat = beat;
				tempNotes.subBeat = subBeat;
				chartFile >> tempNotes.noteType >> lineTemp >> tempNotes.position >> tempNotes.size >> tempNotes.holdChange;
				if (tempNotes.noteType == 12 || tempNotes.noteType == 13) {
					chartFile >> tempNotes.BGType;
				}
				if (tempNotes.noteType == 9 || tempNotes.noteType == 10) {
					chartFile >> Holds[lineTemp];
				}
				theChart.Notes.push_back(tempNotes);
				break;
			case 2:
				tempPCNode.beat = beat;
				tempPCNode.subBeat = subBeat;
				tempPCNode.type = type;
				chartFile >> tempPCNode.BPM;
				theChart.PreChart.push_back(tempPCNode);
				if (beat == 0 && subBeat == 0) {
					InitialBPMNum->Value = (System::Decimal)tempPCNode.BPM;
				}
				break;
			case 3:
				tempPCNode.beat = beat;
				tempPCNode.subBeat = subBeat;
				tempPCNode.type = type;
				chartFile >> tempPCNode.beatDiv1 >> tempPCNode.beatDiv2;
				theChart.PreChart.push_back(tempPCNode);
				if (beat == 0 && subBeat == 0) {
					InitTimeSigNum1->Value = (System::Decimal)tempPCNode.beatDiv1;
					InitTimeSigNum2->Value = (System::Decimal)tempPCNode.beatDiv2;
				}
				break;
			case 5:
				tempPCNode.beat = beat;
				tempPCNode.subBeat = subBeat;
				tempPCNode.type = type;
				chartFile >> tempPCNode.hiSpeed;
				theChart.PreChart.push_back(tempPCNode);
				break;
			default:
				tempPCNode.beat = beat;
				tempPCNode.subBeat = subBeat;
				tempPCNode.type = type;
				theChart.PreChart.push_back(tempPCNode);
			}
		}
		chartFile.close();

		std::map<int, int>::iterator mapitr;
		std::list<NotesNode>::iterator noteitr;
		for (mapitr = Holds.begin(); mapitr != Holds.end(); ++mapitr) {
			lineTemp = 0;
			for (noteitr = theChart.Notes.begin(); noteitr != theChart.Notes.end(); ++noteitr) {
				if (lineTemp == mapitr->first) {
					std::list<NotesNode>::iterator tempitr = noteitr;
					std::advance(tempitr, (mapitr->second - lineTemp));
					(noteitr)->nextNode = tempitr;
					(tempitr)->prevNode = noteitr;
					noteitr = theChart.Notes.end();
					noteitr--;
				}
				lineTemp++;
			}
		}
	}
	private: System::Void saveAsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		saveToolStripMenuItem_Click(sender, e);
	}
	private: System::Void InsertButton_Click(System::Object^ sender, System::EventArgs^ e) {
		NotesNode tempNotesNode;
		PreChartNode tempPreChartNode;

		if (SelectedLineType == 1) {
			tempNotesNode.beat = (int)BeatNum->Value;
			tempNotesNode.subBeat = ((1920 / (int)SubBeat2Num->Value) * (int)SubBeat1Num->Value);
			tempNotesNode.noteType = SelectedNoteType;
			tempNotesNode.position = (int)PosNum->Value;
			tempNotesNode.size = (int)SizeNum->Value;
			tempNotesNode.holdChange = 1;

			switch (SelectedNoteType) {
			case 9:
				if (EndHoldBox->Checked) {
					CurrentObjectText->Text = "Hold End";
				}
				else {
					CurrentObjectText->Text = "Hold Middle";
				}
				SelectedNoteType = 10;
				break;
			case 10:
				if (EndHoldBox->Checked) {
					SelectedNoteType = 11;
					tempNotesNode.noteType = SelectedNoteType;
					break;
				}

				break;
			case 12:
				if (MaskClockwise->Checked) {
					tempNotesNode.BGType = 1;
				}
				else if (MaskCClockwise->Checked) {
					tempNotesNode.BGType = 0;
				}
				else {
					tempNotesNode.BGType = 2;
				}
				break;
			case 13:
				if (MaskClockwise->Checked) {
					tempNotesNode.BGType = 1;
				}
				else if (MaskCClockwise->Checked) {
					tempNotesNode.BGType = 0;
				}
				else {
					tempNotesNode.BGType = 2;
				}
				break;
			case 25:
				if (EndHoldBox->Checked) {
					CurrentObjectText->Text = "Hold End";
				}
				else {
					CurrentObjectText->Text = "Hold Middle";
				}
				SelectedNoteType = 10;
				break;
			}
			theChart.Notes.push_back(tempNotesNode);
			theChart.Notes.sort(sortNotesListByBeat);
			if (SelectedNoteType == 11) {
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 25;
					CurrentObjectText->Text = "Hold Start (Bonus With Flair)";
				}
				else {
					SelectedNoteType = 9;
					CurrentObjectText->Text = "Hold Start (No Bonus)";
				}
			}
		}
		else {
			tempPreChartNode.beat = (int)BeatNum->Value;
			tempPreChartNode.subBeat = ((1920 / (int)SubBeat2Num->Value) * (int)SubBeat1Num->Value);
			tempPreChartNode.type = SelectedLineType;
			if (SelectedLineType == 2) { //BPM Change
				if (tempPreChartNode.beat == 0 && tempPreChartNode.subBeat == 0) {
					InitialBPMNum->Value = BPMChangeNum->Value;
				}
				tempPreChartNode.BPM = (double)BPMChangeNum->Value;
				theChart.PreChart.push_back(tempPreChartNode);
			}
			if (SelectedLineType == 3) { //Time Signature Change
				if (tempPreChartNode.beat == 0 && tempPreChartNode.subBeat == 0) {
					InitTimeSigNum1->Value = TimeSigNum1->Value;
					InitTimeSigNum2->Value = TimeSigNum2->Value;
				}
				tempPreChartNode.beatDiv1 = (int)TimeSigNum1->Value;
				tempPreChartNode.beatDiv2 = (int)TimeSigNum2->Value;
				theChart.PreChart.push_back(tempPreChartNode);
			}
			if (SelectedLineType == 5) { //Hi-speed Change
				tempPreChartNode.hiSpeed = (double)HiSpeedChangeNum->Value;
				theChart.PreChart.push_back(tempPreChartNode);
			}
			if (SelectedLineType == 6) { //Reverse
				theChart.PreChart.push_back(tempPreChartNode);

				tempPreChartNode.beat = (int)ReverseEnd1BNum->Value;
				tempPreChartNode.subBeat = ((1920 / (int)ReverseEnd1SBNum2->Value) * (int)ReverseEnd1SBNum1->Value);
				tempPreChartNode.type = 7;
				theChart.PreChart.push_back(tempPreChartNode);

				tempPreChartNode.beat = (int)ReverseEnd2BNum->Value;
				tempPreChartNode.subBeat = ((1920 / (int)ReverseEnd2SBNum2->Value) * (int)ReverseEnd2SBNum1->Value);
				tempPreChartNode.type = 8;
				theChart.PreChart.push_back(tempPreChartNode);
			}
			if (SelectedLineType == 9) { //Stop
				theChart.PreChart.push_back(tempPreChartNode);

				tempPreChartNode.beat = (int)StopEndBNum->Value;
				tempPreChartNode.subBeat = ((1920 / (int)StopEndSBNum2->Value) * (int)StopEndSBNum1->Value);
				tempPreChartNode.type = 10;
				theChart.PreChart.push_back(tempPreChartNode);
			}
			theChart.PreChart.sort(sortPreChartListByBeat);
		}
	}
	private: System::Void InitialSetSave_Click(System::Object^ sender, System::EventArgs^ e) {
		bool BPMFound = false;
		bool TimeSigFound = false;

		theChart.offset = (double)OffsetNum->Value;
		theChart.movieOffset = (double)MovieOffsetNum->Value;

		std::list<PreChartNode>::iterator itr;
		for (itr = theChart.PreChart.begin(); itr != theChart.PreChart.end(); ++itr) {
			if ((itr)->type == 2 && (itr)->beat == 0 && (itr)->subBeat == 0) {
				(itr)->BPM = (double)InitialBPMNum->Value;
				BPMFound = true;
			}
			if ((itr)->type == 3 && (itr)->beat == 0 && (itr)->subBeat == 0) {
				(itr)->beatDiv1 = (int)InitTimeSigNum1->Value;
				(itr)->beatDiv2 = (int)InitTimeSigNum2->Value;
				TimeSigFound = true;
			}
		}

		PreChartNode tempPreChartNode;
		if (!BPMFound) {
			tempPreChartNode.beat = 0;
			tempPreChartNode.subBeat = 0;
			tempPreChartNode.type = 2;
			tempPreChartNode.BPM = (double)InitialBPMNum->Value;
			theChart.PreChart.push_back(tempPreChartNode);
		}
		if (!TimeSigFound) {
			tempPreChartNode.beat = 0;
			tempPreChartNode.subBeat = 0;
			tempPreChartNode.type = 3;
			tempPreChartNode.beatDiv1 = (int)InitTimeSigNum1->Value;
			tempPreChartNode.beatDiv2 = (int)InitTimeSigNum2->Value;
			theChart.PreChart.push_back(tempPreChartNode);
		}
		theChart.PreChart.sort(sortPreChartListByBeat);
	}
	private: System::Void TapButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusGetRadioButton->Checked) {
				SelectedNoteType = 2;
				CurrentObjectText->Text = "Tap (Bonus Get)";
			}
			else if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 20;
				CurrentObjectText->Text = "Tap (Bonus With Flair)";
			}
			else {
				SelectedNoteType = 1;
				CurrentObjectText->Text = "Tap (No Bonus)";
			}
		}
		SelectedLineType = 1;
	}
	private: System::Void OrangeButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusGetRadioButton->Checked) {
				SelectedNoteType = 6;
				CurrentObjectText->Text = "Orange Swipe (Bonus Get)";
			}
			else if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 23;
				CurrentObjectText->Text = "Orange Swipe (Bonus With Flair)";
			}
			else {
				SelectedNoteType = 5;
				CurrentObjectText->Text = "Orange Swipe (No Bonus)";
			}
			SelectedLineType = 1;
		}
	}
	private: System::Void GreenButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusGetRadioButton->Checked == true) {
				SelectedNoteType = 8;
				CurrentObjectText->Text = "Green Swipe (Bonus Get)";
			}
			else if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 24;
				CurrentObjectText->Text = "Green Swipe (Bonus With Flair)";
			}
			else {
				SelectedNoteType = 7;
				CurrentObjectText->Text = "Green Swipe (No Bonus)";
			}
			SelectedLineType = 1;
		}
	}
	private: System::Void RedButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 21;
				CurrentObjectText->Text = "Red Swipe (Bonus With Flair)";
			}
			else {
				SelectedNoteType = 3;
				CurrentObjectText->Text = "Red Swipe (No Bonus)";
			}
			SelectedLineType = 1;
		}
	}
	private: System::Void BlueButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 22;
				CurrentObjectText->Text = "Blue Swipe (Bonus With Flair)";
			}
			else {
				SelectedNoteType = 4;
				CurrentObjectText->Text = "Blue Swipe (No Bonus)";
			}
			SelectedLineType = 1;
		}
	}
	private: System::Void YellowButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			SelectedNoteType = 16;
			CurrentObjectText->Text = "Yellow Tap";
			SelectedLineType = 1;
		}
	}
	private: System::Void EndChartButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			SelectedNoteType = 14;
			CurrentObjectText->Text = "End of Chart";
			SelectedLineType = 1;
		}
	}
	private: System::Void HoldButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 25;
				CurrentObjectText->Text = "Hold Start (Bonus With Flair)";
			}
			else {
				SelectedNoteType = 9;
				CurrentObjectText->Text = "Hold Start (No Bonus)";
			}
			SelectedLineType = 1;
		}
	}
	private: System::Void Mask_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (AddMask) {
				SelectedNoteType = 12;
				if (MaskClockwise->Checked) {
					CurrentObjectText->Text = "Mask Add (Clockwise)";
				}
				else if (MaskCClockwise->Checked) {
					CurrentObjectText->Text = "Mask Add (Counter-Clockwise)";
				}
				else {
					CurrentObjectText->Text = "Mask Add (From Center)";
				}
			}
			else {
				SelectedNoteType = 13;
				if (MaskClockwise->Checked) {
					CurrentObjectText->Text = "Mask Remove (Clockwise)";
				}
				else if (MaskCClockwise->Checked) {
					CurrentObjectText->Text = "Mask Remove (Counter-Clockwise)";
				}
				else {
					CurrentObjectText->Text = "Mask Remove (To Center)";
				}
			}
			SelectedLineType = 1;
		}
	}
	private: System::Void BPMChange_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "BPM Change";
			SelectedLineType = 2;
		}
	}
	private: System::Void TimeSignature_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "Time Signature Change";
			SelectedLineType = 3;
		}
	}
	private: System::Void Hispeed_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "Hi-Speed Change";
			SelectedLineType = 5;
		}
	}
	private: System::Void Stop_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "Stop";
			SelectedLineType = 9;
		}
	}
	private: System::Void Reverse_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "Reverse";
			SelectedLineType = 6;
		}
	}
	private: System::Void EndHoldBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType == 10) {
			if (EndHoldBox->Checked) {
				CurrentObjectText->Text = "Hold End";
			}
			else {
				CurrentObjectText->Text = "Hold Middle";
			}
		}
	}
	private: System::Void NoBonusRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 2:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 1;
					CurrentObjectText->Text = "Tap (No Bonus)";
				}
				break;
			case 6:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 5;
					CurrentObjectText->Text = "Orange Swipe (No Bonus)";
				}
				break;
			case 8:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 7;
					CurrentObjectText->Text = "Green Swipe (No Bonus)";
				}
				break;
			case 20:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 1;
					CurrentObjectText->Text = "Tap (No Bonus)";
				}
				break;
			case 21:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 3;
					CurrentObjectText->Text = "Red Swipe (No Bonus)";
				}
				break;
			case 22:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 4;
					CurrentObjectText->Text = "Blue Swipe (No Bonus)";
				}
				break;
			case 23:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 5;
					CurrentObjectText->Text = "Orange Swipe (No Bonus)";
				}
				break;
			case 24:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 7;
					CurrentObjectText->Text = "Green Swipe (No Bonus)";
				}
				break;
			case 25:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 9;
					CurrentObjectText->Text = "Hold Start (No Bonus)";
				}
				break;
			}
		}
	}
	private: System::Void BonusGetRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 1:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 2;
					CurrentObjectText->Text = "Tap (Bonus Get)";
				}
				break;
			case 5:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 6;
					CurrentObjectText->Text = "Orange Swipe (Bonus Get)";
				}
				break;
			case 7:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 8;
					CurrentObjectText->Text = "Green Swipe (Bonus Get)";
				}
				break;
			case 20:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 2;
					CurrentObjectText->Text = "Tap (Bonus Get)";
				}
				break;
			case 23:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 6;
					CurrentObjectText->Text = "Orange Swipe (Bonus Get)";
				}
				break;
			case 24:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 8;
					CurrentObjectText->Text = "Green Swipe (Bonus Get)";
				}
				break;
			}
		}
	}
	private: System::Void BonusFlairRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 1:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 20;
					CurrentObjectText->Text = "Tap (Bonus With Flair)";
				}
				break;
			case 2:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 20;
					CurrentObjectText->Text = "Tap (Bonus With Flair)";
				}
				break;
			case 3:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 21;
					CurrentObjectText->Text = "Red Swipe (Bonus With Flair)";
				}
				break;
			case 4:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 22;
					CurrentObjectText->Text = "Blue Swipe (Bonus With Flair)";
				}
				break;
			case 5:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 23;
					CurrentObjectText->Text = "Orange Swipe (Bonus With Flair)";
				}
				break;
			case 6:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 23;
					CurrentObjectText->Text = "Orange Swipe (Bonus With Flair)";
				}
				break;
			case 7:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 24;
					CurrentObjectText->Text = "Green Swipe (Bonus With Flair)";
				}
				break;
			case 8:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 24;
					CurrentObjectText->Text = "Green Swipe (Bonus With Flair)";
				}
				break;
			case 9:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 25;
					CurrentObjectText->Text = "Hold Start (Bonus With Flair)";
				}
				break;
			}
		}
	}
	private: System::Void AddMask_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 13:
				if (AddMask->Checked) {
					SelectedNoteType = 12;
					if (MaskClockwise->Checked) {
						CurrentObjectText->Text = "Mask Add (Clockwise)";
					}
					else if (MaskCClockwise->Checked) {
						CurrentObjectText->Text = "Mask Add (Counter-Clockwise)";
					}
					else {
						CurrentObjectText->Text = "Mask Add (From Center)";
					}
				}
				break;
			}
		}
	}
	private: System::Void RemoveMask_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 12:
				if (RemoveMask->Checked) {
					SelectedNoteType = 13;
					if (MaskClockwise->Checked) {
						CurrentObjectText->Text = "Mask Remove (Clockwise)";
					}
					else if (MaskCClockwise->Checked) {
						CurrentObjectText->Text = "Mask Remove (Counter-Clockwise)";
					}
					else {
						CurrentObjectText->Text = "Mask Remove (To Center)";
					}
				}
				break;
			}
		}
	}
	private: System::Void MaskClockwise_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 12:
				if (MaskClockwise->Checked) {
					CurrentObjectText->Text = "Mask Add (Clockwise)";
				}
				break;
			case 13:
				if (MaskClockwise->Checked) {
					CurrentObjectText->Text = "Mask Remove (Clockwise)";
				}
				break;
			}
		}
	}
	private: System::Void MaskCClockwise_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 12:
				if (MaskCClockwise->Checked) {
					CurrentObjectText->Text = "Mask Add (Counter-Clockwise)";
				}
				break;
			case 13:
				if (MaskCClockwise->Checked) {
					CurrentObjectText->Text = "Mask Remove (Counter-Clockwise)";
				}
				break;
			}
		}
	}
	private: System::Void MaskCenter_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 12:
				if (MaskCenter->Checked) {
					CurrentObjectText->Text = "Mask Add (From Center)";
				}
				break;
			case 13:
				if (MaskCenter->Checked) {
					CurrentObjectText->Text = "Mask Remove (To Center)";
				}
				break;
			}
		}
	}
};
}
