#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include "Chart.h"

Chart theChart;
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



	private: System::Windows::Forms::CheckBox^ BonusBox;
	private: System::Windows::Forms::Button^ RedButton;
	private: System::Windows::Forms::Button^ BlueButton;
	private: System::Windows::Forms::Button^ YellowButton;
	private: System::Windows::Forms::Button^ HoldButton;
	private: System::Windows::Forms::Button^ BGButton;
	private: System::Windows::Forms::GroupBox^ NoteTypesButtons;



	private: System::Windows::Forms::ToolTip^ ToolTip;
	private: System::Windows::Forms::CheckBox^ BGBox;
	private: System::Windows::Forms::CheckBox^ EndHoldBox;
	private: System::Windows::Forms::Button^ InsertButton;
	private: System::Windows::Forms::Label^ PosLabel;
	private: System::Windows::Forms::Label^ posInfo;
	private: System::Windows::Forms::NumericUpDown^ SizeNum;
	private: System::Windows::Forms::Label^ SizeInfo;
	private: System::Windows::Forms::Label^ SizeLabel;
	private: System::Windows::Forms::NumericUpDown^ PosNum;
	private: System::Windows::Forms::Panel^ panel1;




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
			this->BonusBox = (gcnew System::Windows::Forms::CheckBox());
			this->RedButton = (gcnew System::Windows::Forms::Button());
			this->BlueButton = (gcnew System::Windows::Forms::Button());
			this->YellowButton = (gcnew System::Windows::Forms::Button());
			this->HoldButton = (gcnew System::Windows::Forms::Button());
			this->BGButton = (gcnew System::Windows::Forms::Button());
			this->NoteTypesButtons = (gcnew System::Windows::Forms::GroupBox());
			this->BGBox = (gcnew System::Windows::Forms::CheckBox());
			this->EndHoldBox = (gcnew System::Windows::Forms::CheckBox());
			this->ToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->InsertButton = (gcnew System::Windows::Forms::Button());
			this->PosLabel = (gcnew System::Windows::Forms::Label());
			this->posInfo = (gcnew System::Windows::Forms::Label());
			this->SizeNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->SizeInfo = (gcnew System::Windows::Forms::Label());
			this->SizeLabel = (gcnew System::Windows::Forms::Label());
			this->PosNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->menuStrip->SuspendLayout();
			this->NoteTypesButtons->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SizeNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PosNum))->BeginInit();
			this->panel1->SuspendLayout();
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
			// 
			// OrangeButton
			// 
			resources->ApplyResources(this->OrangeButton, L"OrangeButton");
			this->OrangeButton->Name = L"OrangeButton";
			this->OrangeButton->UseVisualStyleBackColor = true;
			// 
			// GreenButton
			// 
			resources->ApplyResources(this->GreenButton, L"GreenButton");
			this->GreenButton->Name = L"GreenButton";
			this->GreenButton->UseVisualStyleBackColor = true;
			// 
			// BonusBox
			// 
			resources->ApplyResources(this->BonusBox, L"BonusBox");
			this->BonusBox->Name = L"BonusBox";
			this->ToolTip->SetToolTip(this->BonusBox, resources->GetString(L"BonusBox.ToolTip"));
			this->BonusBox->UseVisualStyleBackColor = true;
			// 
			// RedButton
			// 
			resources->ApplyResources(this->RedButton, L"RedButton");
			this->RedButton->Name = L"RedButton";
			this->RedButton->UseVisualStyleBackColor = true;
			// 
			// BlueButton
			// 
			resources->ApplyResources(this->BlueButton, L"BlueButton");
			this->BlueButton->Name = L"BlueButton";
			this->BlueButton->UseVisualStyleBackColor = true;
			// 
			// YellowButton
			// 
			resources->ApplyResources(this->YellowButton, L"YellowButton");
			this->YellowButton->Name = L"YellowButton";
			this->YellowButton->UseVisualStyleBackColor = true;
			// 
			// HoldButton
			// 
			resources->ApplyResources(this->HoldButton, L"HoldButton");
			this->HoldButton->Name = L"HoldButton";
			this->ToolTip->SetToolTip(this->HoldButton, resources->GetString(L"HoldButton.ToolTip"));
			this->HoldButton->UseVisualStyleBackColor = true;
			// 
			// BGButton
			// 
			resources->ApplyResources(this->BGButton, L"BGButton");
			this->BGButton->Name = L"BGButton";
			this->BGButton->UseVisualStyleBackColor = true;
			// 
			// NoteTypesButtons
			// 
			this->NoteTypesButtons->Controls->Add(this->BGBox);
			this->NoteTypesButtons->Controls->Add(this->EndHoldBox);
			this->NoteTypesButtons->Controls->Add(this->BGButton);
			this->NoteTypesButtons->Controls->Add(this->TapButton);
			this->NoteTypesButtons->Controls->Add(this->BonusBox);
			this->NoteTypesButtons->Controls->Add(this->HoldButton);
			this->NoteTypesButtons->Controls->Add(this->OrangeButton);
			this->NoteTypesButtons->Controls->Add(this->YellowButton);
			this->NoteTypesButtons->Controls->Add(this->GreenButton);
			this->NoteTypesButtons->Controls->Add(this->BlueButton);
			this->NoteTypesButtons->Controls->Add(this->RedButton);
			resources->ApplyResources(this->NoteTypesButtons, L"NoteTypesButtons");
			this->NoteTypesButtons->Name = L"NoteTypesButtons";
			this->NoteTypesButtons->TabStop = false;
			// 
			// BGBox
			// 
			resources->ApplyResources(this->BGBox, L"BGBox");
			this->BGBox->Name = L"BGBox";
			this->ToolTip->SetToolTip(this->BGBox, resources->GetString(L"BGBox.ToolTip"));
			this->BGBox->UseVisualStyleBackColor = true;
			// 
			// EndHoldBox
			// 
			resources->ApplyResources(this->EndHoldBox, L"EndHoldBox");
			this->EndHoldBox->Name = L"EndHoldBox";
			this->ToolTip->SetToolTip(this->EndHoldBox, resources->GetString(L"EndHoldBox.ToolTip"));
			this->EndHoldBox->UseVisualStyleBackColor = true;
			// 
			// InsertButton
			// 
			resources->ApplyResources(this->InsertButton, L"InsertButton");
			this->InsertButton->Name = L"InsertButton";
			this->InsertButton->UseVisualStyleBackColor = true;
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
			// panel1
			// 
			this->panel1->Controls->Add(this->PosNum);
			this->panel1->Controls->Add(this->SizeLabel);
			this->panel1->Controls->Add(this->SizeInfo);
			this->panel1->Controls->Add(this->PosLabel);
			this->panel1->Controls->Add(this->posInfo);
			this->panel1->Controls->Add(this->SizeNum);
			resources->ApplyResources(this->panel1, L"panel1");
			this->panel1->Name = L"panel1";
			// 
			// MyForm
			// 
			this->AllowDrop = true;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->InsertButton);
			this->Controls->Add(this->NoteTypesButtons);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"MyForm";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->NoteTypesButtons->ResumeLayout(false);
			this->NoteTypesButtons->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SizeNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PosNum))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
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
			}
			if (temp == "#MOVIEOFFSET") {
				chartFile >> theChart.movieOffset;
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
				break;
			case 3:
				tempPCNode.beat = beat;
				tempPCNode.subBeat = subBeat;
				tempPCNode.type = type;
				chartFile >> tempPCNode.beatDiv1 >> tempPCNode.beatDiv2;
				theChart.PreChart.push_back(tempPCNode);
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
};
}
