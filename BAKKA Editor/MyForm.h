#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdio.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include "Chart.h"
#define PI 3.14159265

using std::to_string;
using namespace IrrKlang;

Chart theChart;
std::string songFilePath = "";
std::string chartFilePath = "";
std::string tickFilePath = "se_tick.ogg";
int SelectedLineType = 1;
int SelectedNoteType = 1;
int SelectedNoteTypeVisual = 1;
std::list<NotesNode>::iterator viewNotesITR = theChart.Notes.begin();
std::list<PreChartNode>::iterator viewGimmicksITR = theChart.PreChart.begin();
std::list<NotesNode>::iterator holdNoteitr = theChart.Notes.end();
std::map<float, std::list<std::pair<int, int>>> mapOfMasks; //measure, list of masks
std::map<float, std::list<NotesNode>> mapOfNotes; //measure, list of notes
std::map<float, float> mapOfTimeBetweenMeasures; //current beat, milliseconds beatween beats
std::map<float, float> mapOfBeatAtTime; //milliseconds start time, beat start time
std::map<float, float> mapOfBPMatTime; //measure start time, BPM at time
std::map<float, std::pair<int, int>> mapOfTSatTime; //measure start time, Time Signature at time
bool alreadyRefreshed = false;
bool noteRefresh = false;
bool subnum1changed = false;
int songLength = 0;
const unsigned int update_interval = 4; // update after every 100 milliseconds (1/16th of 100bpm)
const int milInMinute = 60000;
bool scrollBarChanged = false;
float theCurrentMeasure = 0;
// Variables for mouse things
int mouseDownPos = -1;
int lastMousePos = -1;
bool rolloverPos = false;
bool rolloverNeg = false;


int findLine(std::list<NotesNode>::iterator nextNode) {
	int outputLine = 0;

	for (std::list<NotesNode>::iterator itr = theChart.Notes.begin(); itr != theChart.Notes.end(); itr++) {
		if (itr == nextNode)
			break;
		outputLine++;
	}

	return outputLine;
}
bool isHold(int note) {
	switch (note) {
		case 9:
		case 10:
		case 11:
		case 25:
			return true;
		default:
			return false;
	}
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
	return false;
}
bool compareInterval(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs)
{
	return (lhs.first < rhs.first);
}
float findGCD(float a, float b) {
	if (b == 0)
		return a;
	return findGCD(b, (int)a % (int)b);
}

namespace BAKKAEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Threading;
	using namespace System::Reflection;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
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
		ISoundEngine SoundEngine;
		ISound^ currentlyPlayingSong = SoundEngine.Play2D(stdStringToSystemString(songFilePath), true, true);
		ISound^ currentlyPlayingTickSound = SoundEngine.Play2D(stdStringToSystemString(tickFilePath), false, true);
		BufferedGraphicsContext^ bufferedGfxContext;
		BufferedGraphics^ bufferedGfx;
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



	private: System::Windows::Forms::GroupBox^ GimmickBox;
	private: System::Windows::Forms::Button^ MaskButton;
	private: System::Windows::Forms::RadioButton^ RemoveMask;
	private: System::Windows::Forms::RadioButton^ AddMask;
	private: System::Windows::Forms::Button^ Reverse;
	private: System::Windows::Forms::Button^ Stop;
	private: System::Windows::Forms::Button^ Hispeed;
	private: System::Windows::Forms::Button^ TimeSignature;
	private: System::Windows::Forms::Button^ BPMChange;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::NumericUpDown^ BeatNum2;
	private: System::Windows::Forms::NumericUpDown^ BeatNum1;
	private: System::Windows::Forms::NumericUpDown^ MeasureNum;

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
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd2BeatNum2;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd2BeatNum1;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd2MeasureNum;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd1BeatNum2;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd1BeatNum1;
	private: System::Windows::Forms::NumericUpDown^ ReverseEnd1MeasureNum;
	private: System::Windows::Forms::NumericUpDown^ StopEndMeasureNum;
	private: System::Windows::Forms::NumericUpDown^ StopEndBeatNum2;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::NumericUpDown^ StopEndBeatNum1;
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

private: System::Windows::Forms::RadioButton^ BonusFlairRadioButton;
private: System::Windows::Forms::RadioButton^ BonusGetRadioButton;
private: System::Windows::Forms::RadioButton^ NoBonusRadioButton;
private: System::Windows::Forms::Button^ InitialSetSave;
private: System::Windows::Forms::GroupBox^ MaskSettingsBox;
private: System::Windows::Forms::RadioButton^ MaskCenter;
private: System::Windows::Forms::RadioButton^ MaskCClockwise;
private: System::Windows::Forms::RadioButton^ MaskClockwise;

private: System::Windows::Forms::Label^ CurrentObjectText;
private: System::Windows::Forms::GroupBox^ PreChartViewBox;
private: System::Windows::Forms::Button^ NextGimmickButton;
private: System::Windows::Forms::Button^ PrevGimmickButton;


private: System::Windows::Forms::Button^ DeleteGimmickButton;
private: System::Windows::Forms::GroupBox^ NotesViewBox;
private: System::Windows::Forms::Button^ DeleteNoteButton;
private: System::Windows::Forms::Button^ NextNoteButton;

private: System::Windows::Forms::Button^ PrevNoteButton;
private: System::Windows::Forms::Label^ GimmickBeatLabel;

private: System::Windows::Forms::Label^ label22;
private: System::Windows::Forms::Label^ label21;
private: System::Windows::Forms::Label^ label20;
private: System::Windows::Forms::Label^ label19;
private: System::Windows::Forms::Label^ label28;
private: System::Windows::Forms::Label^ label27;
private: System::Windows::Forms::Label^ label26;
private: System::Windows::Forms::Label^ label25;
private: System::Windows::Forms::Label^ label24;
private: System::Windows::Forms::Label^ label23;
private: System::Windows::Forms::Label^ GimmickValueLabel;
private: System::Windows::Forms::Label^ GimmickTypeLabel;
private: System::Windows::Forms::Label^ GimmickSubBeatLabel;
private: System::Windows::Forms::Label^ NotesMaskLabel;
private: System::Windows::Forms::Label^ NotesSizeLabel;
private: System::Windows::Forms::Label^ NotesPosLabel;
private: System::Windows::Forms::Label^ NotesTypeLabel;
private: System::Windows::Forms::Label^ NotesSubBeatLabel;
private: System::Windows::Forms::Label^ NotesBeatLabel;
private: System::Windows::Forms::Label^ MadeByLabel;

private: System::Windows::Forms::Label^ label29;
private: System::Windows::Forms::OpenFileDialog^ openFileDialogChart;
private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;


private: System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;
private: System::Windows::Forms::CheckBox^ MatchTimeCheckBox;
private: System::Windows::Forms::CheckBox^ MatchNoteCheckBox;
private: System::Windows::Forms::Button^ PrevBeatButton;
private: System::Windows::Forms::Button^ NextBeatButton;
private: System::Windows::Forms::Button^ EditNoteButton;
private: System::Windows::Forms::GroupBox^ CurrentNoteBox;
private: System::Windows::Forms::TrackBar^ SizeTrackBar;
private: System::Windows::Forms::TrackBar^ PosTrackBar;
private: System::IO::FileSystemWatcher^ fileSystemWatcher1;
private: System::Windows::Forms::Panel^ CirclePanel;
private: System::Windows::Forms::GroupBox^ VisualSettingsBox;
private: System::Windows::Forms::Label^ label2;
private: System::Windows::Forms::NumericUpDown^ VisualHispeed;
private: System::Windows::Forms::TrackBar^ songTrackSlider;

private: System::Windows::Forms::Button^ PlayButton;

private: System::Windows::Forms::GroupBox^ SongPlaybackBox;

private: System::Windows::Forms::Label^ songFileName;
private: System::Windows::Forms::Button^ selectSongFile;
private: System::Windows::Forms::OpenFileDialog^ openFileDialogSong;
private: System::Windows::Forms::Label^ VolumeLabel;
//private: System::Windows::Forms::Timer^ timer1;
private: System::Windows::Forms::TrackBar^ SongVolume;

private: System::ComponentModel::BackgroundWorker^ backgroundWorkerSong;
private: System::ComponentModel::BackgroundWorker^ backgroundWorkerPaint;
private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
private: System::ComponentModel::BackgroundWorker^ backgroundWorker2;

private: System::Windows::Forms::NumericUpDown^ PlaybackSpeedNum;
private: System::Windows::Forms::Label^ label30;

private: System::Windows::Forms::ToolStripMenuItem^ viewToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ showCursorToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ showCursorDuringPlaybackToolStripMenuItem;
private: System::Windows::Forms::GroupBox^ CurrentObjectBox;
private: System::Windows::Forms::ToolStripMenuItem^ aboutBAKKAEditorToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ highlightViewedNoteToolStripMenuItem;






























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
			this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showCursorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showCursorDuringPlaybackToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->highlightViewedNoteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutBAKKAEditorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->VisualHispeed = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->PlaybackSpeedNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->EditNoteButton = (gcnew System::Windows::Forms::Button());
			this->MaskButton = (gcnew System::Windows::Forms::Button());
			this->InsertButton = (gcnew System::Windows::Forms::Button());
			this->PosLabel = (gcnew System::Windows::Forms::Label());
			this->posInfo = (gcnew System::Windows::Forms::Label());
			this->SizeNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->SizeInfo = (gcnew System::Windows::Forms::Label());
			this->SizeLabel = (gcnew System::Windows::Forms::Label());
			this->PosNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->BeatNum2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->BeatNum1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->MeasureNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->Beat = (gcnew System::Windows::Forms::Label());
			this->GimmickBox = (gcnew System::Windows::Forms::GroupBox());
			this->RemoveMask = (gcnew System::Windows::Forms::RadioButton());
			this->AddMask = (gcnew System::Windows::Forms::RadioButton());
			this->GimmickSettingsBox = (gcnew System::Windows::Forms::GroupBox());
			this->ReverseEnd2BeatNum2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->ReverseEnd2BeatNum1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->ReverseEnd2MeasureNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->ReverseEnd1BeatNum2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->ReverseEnd1BeatNum1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->ReverseEnd1MeasureNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->StopEndMeasureNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->StopEndBeatNum2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->StopEndBeatNum1 = (gcnew System::Windows::Forms::NumericUpDown());
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
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->MaskSettingsBox = (gcnew System::Windows::Forms::GroupBox());
			this->MaskCenter = (gcnew System::Windows::Forms::RadioButton());
			this->MaskCClockwise = (gcnew System::Windows::Forms::RadioButton());
			this->MaskClockwise = (gcnew System::Windows::Forms::RadioButton());
			this->CurrentObjectText = (gcnew System::Windows::Forms::Label());
			this->PreChartViewBox = (gcnew System::Windows::Forms::GroupBox());
			this->GimmickValueLabel = (gcnew System::Windows::Forms::Label());
			this->GimmickTypeLabel = (gcnew System::Windows::Forms::Label());
			this->GimmickSubBeatLabel = (gcnew System::Windows::Forms::Label());
			this->GimmickBeatLabel = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->NextGimmickButton = (gcnew System::Windows::Forms::Button());
			this->PrevGimmickButton = (gcnew System::Windows::Forms::Button());
			this->DeleteGimmickButton = (gcnew System::Windows::Forms::Button());
			this->NotesViewBox = (gcnew System::Windows::Forms::GroupBox());
			this->PrevBeatButton = (gcnew System::Windows::Forms::Button());
			this->NextBeatButton = (gcnew System::Windows::Forms::Button());
			this->MatchNoteCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->MatchTimeCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->NotesMaskLabel = (gcnew System::Windows::Forms::Label());
			this->NotesSizeLabel = (gcnew System::Windows::Forms::Label());
			this->NotesPosLabel = (gcnew System::Windows::Forms::Label());
			this->NotesTypeLabel = (gcnew System::Windows::Forms::Label());
			this->NotesSubBeatLabel = (gcnew System::Windows::Forms::Label());
			this->NotesBeatLabel = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->NextNoteButton = (gcnew System::Windows::Forms::Button());
			this->PrevNoteButton = (gcnew System::Windows::Forms::Button());
			this->DeleteNoteButton = (gcnew System::Windows::Forms::Button());
			this->MadeByLabel = (gcnew System::Windows::Forms::Label());
			this->openFileDialogChart = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->CurrentNoteBox = (gcnew System::Windows::Forms::GroupBox());
			this->SizeTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->PosTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->fileSystemWatcher1 = (gcnew System::IO::FileSystemWatcher());
			this->CirclePanel = (gcnew System::Windows::Forms::Panel());
			this->VisualSettingsBox = (gcnew System::Windows::Forms::GroupBox());
			this->PlayButton = (gcnew System::Windows::Forms::Button());
			this->songTrackSlider = (gcnew System::Windows::Forms::TrackBar());
			this->selectSongFile = (gcnew System::Windows::Forms::Button());
			this->SongPlaybackBox = (gcnew System::Windows::Forms::GroupBox());
			this->VolumeLabel = (gcnew System::Windows::Forms::Label());
			this->SongVolume = (gcnew System::Windows::Forms::TrackBar());
			this->songFileName = (gcnew System::Windows::Forms::Label());
			this->openFileDialogSong = (gcnew System::Windows::Forms::OpenFileDialog());
			this->backgroundWorkerSong = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorkerPaint = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->CurrentObjectBox = (gcnew System::Windows::Forms::GroupBox());
			this->menuStrip->SuspendLayout();
			this->NoteTypeBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VisualHispeed))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PlaybackSpeedNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SizeNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PosNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BeatNum2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BeatNum1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MeasureNum))->BeginInit();
			this->GimmickBox->SuspendLayout();
			this->GimmickSettingsBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2BeatNum2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2BeatNum1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2MeasureNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1BeatNum2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1BeatNum1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1MeasureNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndMeasureNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndBeatNum2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndBeatNum1))->BeginInit();
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
			this->MaskSettingsBox->SuspendLayout();
			this->PreChartViewBox->SuspendLayout();
			this->NotesViewBox->SuspendLayout();
			this->CurrentNoteBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SizeTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PosTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher1))->BeginInit();
			this->CirclePanel->SuspendLayout();
			this->VisualSettingsBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->songTrackSlider))->BeginInit();
			this->SongPlaybackBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SongVolume))->BeginInit();
			this->CurrentObjectBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			resources->ApplyResources(this->menuStrip, L"menuStrip");
			this->menuStrip->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->viewToolStripMenuItem, this->aboutToolStripMenuItem
			});
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
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exitToolStripMenuItem_Click);
			// 
			// viewToolStripMenuItem
			// 
			this->viewToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->showCursorToolStripMenuItem,
					this->showCursorDuringPlaybackToolStripMenuItem, this->highlightViewedNoteToolStripMenuItem
			});
			this->viewToolStripMenuItem->Name = L"viewToolStripMenuItem";
			resources->ApplyResources(this->viewToolStripMenuItem, L"viewToolStripMenuItem");
			// 
			// showCursorToolStripMenuItem
			// 
			this->showCursorToolStripMenuItem->Checked = true;
			this->showCursorToolStripMenuItem->CheckOnClick = true;
			this->showCursorToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->showCursorToolStripMenuItem->Name = L"showCursorToolStripMenuItem";
			resources->ApplyResources(this->showCursorToolStripMenuItem, L"showCursorToolStripMenuItem");
			this->showCursorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::showCursorToolStripMenuItem_Click);
			// 
			// showCursorDuringPlaybackToolStripMenuItem
			// 
			this->showCursorDuringPlaybackToolStripMenuItem->CheckOnClick = true;
			this->showCursorDuringPlaybackToolStripMenuItem->Name = L"showCursorDuringPlaybackToolStripMenuItem";
			resources->ApplyResources(this->showCursorDuringPlaybackToolStripMenuItem, L"showCursorDuringPlaybackToolStripMenuItem");
			// 
			// highlightViewedNoteToolStripMenuItem
			// 
			this->highlightViewedNoteToolStripMenuItem->Checked = true;
			this->highlightViewedNoteToolStripMenuItem->CheckOnClick = true;
			this->highlightViewedNoteToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->highlightViewedNoteToolStripMenuItem->Name = L"highlightViewedNoteToolStripMenuItem";
			resources->ApplyResources(this->highlightViewedNoteToolStripMenuItem, L"highlightViewedNoteToolStripMenuItem");
			this->highlightViewedNoteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::highlightViewedNoteToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutBAKKAEditorToolStripMenuItem });
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			resources->ApplyResources(this->aboutToolStripMenuItem, L"aboutToolStripMenuItem");
			// 
			// aboutBAKKAEditorToolStripMenuItem
			// 
			this->aboutBAKKAEditorToolStripMenuItem->Name = L"aboutBAKKAEditorToolStripMenuItem";
			resources->ApplyResources(this->aboutBAKKAEditorToolStripMenuItem, L"aboutBAKKAEditorToolStripMenuItem");
			this->aboutBAKKAEditorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::aboutBAKKAEditorToolStripMenuItem_Click);
			// 
			// TapButton
			// 
			resources->ApplyResources(this->TapButton, L"TapButton");
			this->TapButton->BackColor = System::Drawing::Color::Fuchsia;
			this->TapButton->Name = L"TapButton";
			this->TapButton->UseVisualStyleBackColor = false;
			this->TapButton->Click += gcnew System::EventHandler(this, &MyForm::TapButton_Click);
			// 
			// OrangeButton
			// 
			resources->ApplyResources(this->OrangeButton, L"OrangeButton");
			this->OrangeButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->OrangeButton->Name = L"OrangeButton";
			this->OrangeButton->UseVisualStyleBackColor = false;
			this->OrangeButton->Click += gcnew System::EventHandler(this, &MyForm::OrangeButton_Click);
			// 
			// GreenButton
			// 
			resources->ApplyResources(this->GreenButton, L"GreenButton");
			this->GreenButton->BackColor = System::Drawing::Color::Lime;
			this->GreenButton->Name = L"GreenButton";
			this->GreenButton->UseVisualStyleBackColor = false;
			this->GreenButton->Click += gcnew System::EventHandler(this, &MyForm::GreenButton_Click);
			// 
			// RedButton
			// 
			resources->ApplyResources(this->RedButton, L"RedButton");
			this->RedButton->BackColor = System::Drawing::Color::Red;
			this->RedButton->ForeColor = System::Drawing::Color::White;
			this->RedButton->Name = L"RedButton";
			this->RedButton->UseVisualStyleBackColor = false;
			this->RedButton->Click += gcnew System::EventHandler(this, &MyForm::RedButton_Click);
			// 
			// BlueButton
			// 
			resources->ApplyResources(this->BlueButton, L"BlueButton");
			this->BlueButton->BackColor = System::Drawing::Color::Aqua;
			this->BlueButton->Name = L"BlueButton";
			this->BlueButton->UseVisualStyleBackColor = false;
			this->BlueButton->Click += gcnew System::EventHandler(this, &MyForm::BlueButton_Click);
			// 
			// YellowButton
			// 
			resources->ApplyResources(this->YellowButton, L"YellowButton");
			this->YellowButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(204)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->YellowButton->Name = L"YellowButton";
			this->YellowButton->UseVisualStyleBackColor = false;
			this->YellowButton->Click += gcnew System::EventHandler(this, &MyForm::YellowButton_Click);
			// 
			// HoldButton
			// 
			resources->ApplyResources(this->HoldButton, L"HoldButton");
			this->HoldButton->BackColor = System::Drawing::Color::Yellow;
			this->HoldButton->Name = L"HoldButton";
			this->ToolTip->SetToolTip(this->HoldButton, resources->GetString(L"HoldButton.ToolTip"));
			this->HoldButton->UseVisualStyleBackColor = false;
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
			// VisualHispeed
			// 
			this->VisualHispeed->BackColor = System::Drawing::SystemColors::Window;
			this->VisualHispeed->DecimalPlaces = 2;
			this->VisualHispeed->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 131072 });
			resources->ApplyResources(this->VisualHispeed, L"VisualHispeed");
			this->VisualHispeed->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->VisualHispeed->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 131072 });
			this->VisualHispeed->Name = L"VisualHispeed";
			this->ToolTip->SetToolTip(this->VisualHispeed, resources->GetString(L"VisualHispeed.ToolTip"));
			this->VisualHispeed->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->VisualHispeed->ValueChanged += gcnew System::EventHandler(this, &MyForm::VisualHispeed_ValueChanged);
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->Name = L"label2";
			this->ToolTip->SetToolTip(this->label2, resources->GetString(L"label2.ToolTip"));
			// 
			// label30
			// 
			resources->ApplyResources(this->label30, L"label30");
			this->label30->Name = L"label30";
			this->ToolTip->SetToolTip(this->label30, resources->GetString(L"label30.ToolTip"));
			// 
			// PlaybackSpeedNum
			// 
			this->PlaybackSpeedNum->BackColor = System::Drawing::SystemColors::Window;
			this->PlaybackSpeedNum->DecimalPlaces = 2;
			this->PlaybackSpeedNum->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			resources->ApplyResources(this->PlaybackSpeedNum, L"PlaybackSpeedNum");
			this->PlaybackSpeedNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->PlaybackSpeedNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->PlaybackSpeedNum->Name = L"PlaybackSpeedNum";
			this->ToolTip->SetToolTip(this->PlaybackSpeedNum, resources->GetString(L"PlaybackSpeedNum.ToolTip"));
			this->PlaybackSpeedNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PlaybackSpeedNum->ValueChanged += gcnew System::EventHandler(this, &MyForm::PlaybackSpeedNum_ValueChanged);
			// 
			// EditNoteButton
			// 
			resources->ApplyResources(this->EditNoteButton, L"EditNoteButton");
			this->EditNoteButton->Name = L"EditNoteButton";
			this->ToolTip->SetToolTip(this->EditNoteButton, resources->GetString(L"EditNoteButton.ToolTip"));
			this->EditNoteButton->UseVisualStyleBackColor = true;
			this->EditNoteButton->Click += gcnew System::EventHandler(this, &MyForm::EditNoteButton_Click);
			// 
			// MaskButton
			// 
			resources->ApplyResources(this->MaskButton, L"MaskButton");
			this->MaskButton->Name = L"MaskButton";
			this->MaskButton->UseVisualStyleBackColor = true;
			this->MaskButton->Click += gcnew System::EventHandler(this, &MyForm::MaskButton_Click);
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
			this->SizeNum->ValueChanged += gcnew System::EventHandler(this, &MyForm::SizeNum_ValueChanged);
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
			this->PosNum->ValueChanged += gcnew System::EventHandler(this, &MyForm::PosNum_ValueChanged);
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->Name = L"label1";
			// 
			// BeatNum2
			// 
			resources->ApplyResources(this->BeatNum2, L"BeatNum2");
			this->BeatNum2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1920, 0, 0, 0 });
			this->BeatNum2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->BeatNum2->Name = L"BeatNum2";
			this->BeatNum2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 16, 0, 0, 0 });
			this->BeatNum2->ValueChanged += gcnew System::EventHandler(this, &MyForm::BeatNum2_ValueChanged);
			// 
			// BeatNum1
			// 
			resources->ApplyResources(this->BeatNum1, L"BeatNum1");
			this->BeatNum1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1919, 0, 0, 0 });
			this->BeatNum1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->BeatNum1->Name = L"BeatNum1";
			this->BeatNum1->ValueChanged += gcnew System::EventHandler(this, &MyForm::BeatNum1_ValueChanged);
			// 
			// MeasureNum
			// 
			resources->ApplyResources(this->MeasureNum, L"MeasureNum");
			this->MeasureNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->MeasureNum->Name = L"MeasureNum";
			this->MeasureNum->ValueChanged += gcnew System::EventHandler(this, &MyForm::MeasureNum_ValueChanged);
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
			this->GimmickBox->Controls->Add(this->MaskButton);
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
			// GimmickSettingsBox
			// 
			resources->ApplyResources(this->GimmickSettingsBox, L"GimmickSettingsBox");
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd2BeatNum2);
			this->GimmickSettingsBox->Controls->Add(this->label12);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd2BeatNum1);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd2MeasureNum);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd1BeatNum2);
			this->GimmickSettingsBox->Controls->Add(this->label11);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd1BeatNum1);
			this->GimmickSettingsBox->Controls->Add(this->ReverseEnd1MeasureNum);
			this->GimmickSettingsBox->Controls->Add(this->StopEndMeasureNum);
			this->GimmickSettingsBox->Controls->Add(this->StopEndBeatNum2);
			this->GimmickSettingsBox->Controls->Add(this->label10);
			this->GimmickSettingsBox->Controls->Add(this->StopEndBeatNum1);
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
			this->GimmickSettingsBox->Name = L"GimmickSettingsBox";
			this->GimmickSettingsBox->TabStop = false;
			// 
			// ReverseEnd2BeatNum2
			// 
			resources->ApplyResources(this->ReverseEnd2BeatNum2, L"ReverseEnd2BeatNum2");
			this->ReverseEnd2BeatNum2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 192, 0, 0, 0 });
			this->ReverseEnd2BeatNum2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->ReverseEnd2BeatNum2->Name = L"ReverseEnd2BeatNum2";
			this->ReverseEnd2BeatNum2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// label12
			// 
			resources->ApplyResources(this->label12, L"label12");
			this->label12->Name = L"label12";
			// 
			// ReverseEnd2BeatNum1
			// 
			resources->ApplyResources(this->ReverseEnd2BeatNum1, L"ReverseEnd2BeatNum1");
			this->ReverseEnd2BeatNum1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 191, 0, 0, 0 });
			this->ReverseEnd2BeatNum1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->ReverseEnd2BeatNum1->Name = L"ReverseEnd2BeatNum1";
			this->ReverseEnd2BeatNum1->ValueChanged += gcnew System::EventHandler(this, &MyForm::ReverseEnd2BeatNum1_ValueChanged);
			// 
			// ReverseEnd2MeasureNum
			// 
			resources->ApplyResources(this->ReverseEnd2MeasureNum, L"ReverseEnd2MeasureNum");
			this->ReverseEnd2MeasureNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->ReverseEnd2MeasureNum->Name = L"ReverseEnd2MeasureNum";
			// 
			// ReverseEnd1BeatNum2
			// 
			resources->ApplyResources(this->ReverseEnd1BeatNum2, L"ReverseEnd1BeatNum2");
			this->ReverseEnd1BeatNum2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 192, 0, 0, 0 });
			this->ReverseEnd1BeatNum2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->ReverseEnd1BeatNum2->Name = L"ReverseEnd1BeatNum2";
			this->ReverseEnd1BeatNum2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// label11
			// 
			resources->ApplyResources(this->label11, L"label11");
			this->label11->Name = L"label11";
			// 
			// ReverseEnd1BeatNum1
			// 
			resources->ApplyResources(this->ReverseEnd1BeatNum1, L"ReverseEnd1BeatNum1");
			this->ReverseEnd1BeatNum1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 191, 0, 0, 0 });
			this->ReverseEnd1BeatNum1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->ReverseEnd1BeatNum1->Name = L"ReverseEnd1BeatNum1";
			this->ReverseEnd1BeatNum1->ValueChanged += gcnew System::EventHandler(this, &MyForm::ReverseEnd1BeatNum1_ValueChanged);
			// 
			// ReverseEnd1MeasureNum
			// 
			resources->ApplyResources(this->ReverseEnd1MeasureNum, L"ReverseEnd1MeasureNum");
			this->ReverseEnd1MeasureNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->ReverseEnd1MeasureNum->Name = L"ReverseEnd1MeasureNum";
			// 
			// StopEndMeasureNum
			// 
			resources->ApplyResources(this->StopEndMeasureNum, L"StopEndMeasureNum");
			this->StopEndMeasureNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->StopEndMeasureNum->Name = L"StopEndMeasureNum";
			// 
			// StopEndBeatNum2
			// 
			resources->ApplyResources(this->StopEndBeatNum2, L"StopEndBeatNum2");
			this->StopEndBeatNum2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 192, 0, 0, 0 });
			this->StopEndBeatNum2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->StopEndBeatNum2->Name = L"StopEndBeatNum2";
			this->StopEndBeatNum2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// label10
			// 
			resources->ApplyResources(this->label10, L"label10");
			this->label10->Name = L"label10";
			// 
			// StopEndBeatNum1
			// 
			resources->ApplyResources(this->StopEndBeatNum1, L"StopEndBeatNum1");
			this->StopEndBeatNum1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 191, 0, 0, 0 });
			this->StopEndBeatNum1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->StopEndBeatNum1->Name = L"StopEndBeatNum1";
			this->StopEndBeatNum1->ValueChanged += gcnew System::EventHandler(this, &MyForm::StopEndBeatNum1_ValueChanged);
			// 
			// HiSpeedChangeNum
			// 
			this->HiSpeedChangeNum->DecimalPlaces = 6;
			resources->ApplyResources(this->HiSpeedChangeNum, L"HiSpeedChangeNum");
			this->HiSpeedChangeNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
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
			resources->ApplyResources(this->InitialSettingsPane, L"InitialSettingsPane");
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
			// label29
			// 
			resources->ApplyResources(this->label29, L"label29");
			this->label29->Name = L"label29";
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
			// CurrentObjectText
			// 
			resources->ApplyResources(this->CurrentObjectText, L"CurrentObjectText");
			this->CurrentObjectText->Name = L"CurrentObjectText";
			// 
			// PreChartViewBox
			// 
			resources->ApplyResources(this->PreChartViewBox, L"PreChartViewBox");
			this->PreChartViewBox->Controls->Add(this->GimmickValueLabel);
			this->PreChartViewBox->Controls->Add(this->GimmickTypeLabel);
			this->PreChartViewBox->Controls->Add(this->GimmickSubBeatLabel);
			this->PreChartViewBox->Controls->Add(this->GimmickBeatLabel);
			this->PreChartViewBox->Controls->Add(this->label22);
			this->PreChartViewBox->Controls->Add(this->label21);
			this->PreChartViewBox->Controls->Add(this->label20);
			this->PreChartViewBox->Controls->Add(this->label19);
			this->PreChartViewBox->Controls->Add(this->NextGimmickButton);
			this->PreChartViewBox->Controls->Add(this->PrevGimmickButton);
			this->PreChartViewBox->Controls->Add(this->DeleteGimmickButton);
			this->PreChartViewBox->Name = L"PreChartViewBox";
			this->PreChartViewBox->TabStop = false;
			// 
			// GimmickValueLabel
			// 
			resources->ApplyResources(this->GimmickValueLabel, L"GimmickValueLabel");
			this->GimmickValueLabel->Name = L"GimmickValueLabel";
			// 
			// GimmickTypeLabel
			// 
			resources->ApplyResources(this->GimmickTypeLabel, L"GimmickTypeLabel");
			this->GimmickTypeLabel->Name = L"GimmickTypeLabel";
			// 
			// GimmickSubBeatLabel
			// 
			resources->ApplyResources(this->GimmickSubBeatLabel, L"GimmickSubBeatLabel");
			this->GimmickSubBeatLabel->Name = L"GimmickSubBeatLabel";
			// 
			// GimmickBeatLabel
			// 
			resources->ApplyResources(this->GimmickBeatLabel, L"GimmickBeatLabel");
			this->GimmickBeatLabel->Name = L"GimmickBeatLabel";
			// 
			// label22
			// 
			resources->ApplyResources(this->label22, L"label22");
			this->label22->Name = L"label22";
			// 
			// label21
			// 
			resources->ApplyResources(this->label21, L"label21");
			this->label21->Name = L"label21";
			// 
			// label20
			// 
			resources->ApplyResources(this->label20, L"label20");
			this->label20->Name = L"label20";
			// 
			// label19
			// 
			resources->ApplyResources(this->label19, L"label19");
			this->label19->Name = L"label19";
			// 
			// NextGimmickButton
			// 
			resources->ApplyResources(this->NextGimmickButton, L"NextGimmickButton");
			this->NextGimmickButton->Name = L"NextGimmickButton";
			this->NextGimmickButton->UseVisualStyleBackColor = true;
			this->NextGimmickButton->Click += gcnew System::EventHandler(this, &MyForm::NextGimmickButton_Click);
			// 
			// PrevGimmickButton
			// 
			resources->ApplyResources(this->PrevGimmickButton, L"PrevGimmickButton");
			this->PrevGimmickButton->Name = L"PrevGimmickButton";
			this->PrevGimmickButton->UseVisualStyleBackColor = true;
			this->PrevGimmickButton->Click += gcnew System::EventHandler(this, &MyForm::PrevGimmickButton_Click);
			// 
			// DeleteGimmickButton
			// 
			resources->ApplyResources(this->DeleteGimmickButton, L"DeleteGimmickButton");
			this->DeleteGimmickButton->Name = L"DeleteGimmickButton";
			this->DeleteGimmickButton->UseVisualStyleBackColor = true;
			this->DeleteGimmickButton->Click += gcnew System::EventHandler(this, &MyForm::DeleteGimmickButton_Click);
			// 
			// NotesViewBox
			// 
			resources->ApplyResources(this->NotesViewBox, L"NotesViewBox");
			this->NotesViewBox->Controls->Add(this->EditNoteButton);
			this->NotesViewBox->Controls->Add(this->PrevBeatButton);
			this->NotesViewBox->Controls->Add(this->NextBeatButton);
			this->NotesViewBox->Controls->Add(this->MatchNoteCheckBox);
			this->NotesViewBox->Controls->Add(this->MatchTimeCheckBox);
			this->NotesViewBox->Controls->Add(this->NotesMaskLabel);
			this->NotesViewBox->Controls->Add(this->NotesSizeLabel);
			this->NotesViewBox->Controls->Add(this->NotesPosLabel);
			this->NotesViewBox->Controls->Add(this->NotesTypeLabel);
			this->NotesViewBox->Controls->Add(this->NotesSubBeatLabel);
			this->NotesViewBox->Controls->Add(this->NotesBeatLabel);
			this->NotesViewBox->Controls->Add(this->label28);
			this->NotesViewBox->Controls->Add(this->label27);
			this->NotesViewBox->Controls->Add(this->label26);
			this->NotesViewBox->Controls->Add(this->label25);
			this->NotesViewBox->Controls->Add(this->label24);
			this->NotesViewBox->Controls->Add(this->label23);
			this->NotesViewBox->Controls->Add(this->NextNoteButton);
			this->NotesViewBox->Controls->Add(this->PrevNoteButton);
			this->NotesViewBox->Controls->Add(this->DeleteNoteButton);
			this->NotesViewBox->Name = L"NotesViewBox";
			this->NotesViewBox->TabStop = false;
			// 
			// PrevBeatButton
			// 
			resources->ApplyResources(this->PrevBeatButton, L"PrevBeatButton");
			this->PrevBeatButton->Name = L"PrevBeatButton";
			this->PrevBeatButton->UseVisualStyleBackColor = true;
			this->PrevBeatButton->Click += gcnew System::EventHandler(this, &MyForm::PrevBeatButton_Click);
			// 
			// NextBeatButton
			// 
			resources->ApplyResources(this->NextBeatButton, L"NextBeatButton");
			this->NextBeatButton->Name = L"NextBeatButton";
			this->NextBeatButton->UseVisualStyleBackColor = true;
			this->NextBeatButton->Click += gcnew System::EventHandler(this, &MyForm::NextBeatButton_Click);
			// 
			// MatchNoteCheckBox
			// 
			resources->ApplyResources(this->MatchNoteCheckBox, L"MatchNoteCheckBox");
			this->MatchNoteCheckBox->BackColor = System::Drawing::Color::Transparent;
			this->MatchNoteCheckBox->Name = L"MatchNoteCheckBox";
			this->MatchNoteCheckBox->UseVisualStyleBackColor = false;
			this->MatchNoteCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::MatchNoteCheckBox_CheckedChanged);
			// 
			// MatchTimeCheckBox
			// 
			resources->ApplyResources(this->MatchTimeCheckBox, L"MatchTimeCheckBox");
			this->MatchTimeCheckBox->Name = L"MatchTimeCheckBox";
			this->MatchTimeCheckBox->UseVisualStyleBackColor = true;
			this->MatchTimeCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::MatchTimeCheckBox_CheckedChanged);
			// 
			// NotesMaskLabel
			// 
			resources->ApplyResources(this->NotesMaskLabel, L"NotesMaskLabel");
			this->NotesMaskLabel->Name = L"NotesMaskLabel";
			// 
			// NotesSizeLabel
			// 
			resources->ApplyResources(this->NotesSizeLabel, L"NotesSizeLabel");
			this->NotesSizeLabel->Name = L"NotesSizeLabel";
			// 
			// NotesPosLabel
			// 
			resources->ApplyResources(this->NotesPosLabel, L"NotesPosLabel");
			this->NotesPosLabel->Name = L"NotesPosLabel";
			// 
			// NotesTypeLabel
			// 
			resources->ApplyResources(this->NotesTypeLabel, L"NotesTypeLabel");
			this->NotesTypeLabel->Name = L"NotesTypeLabel";
			// 
			// NotesSubBeatLabel
			// 
			resources->ApplyResources(this->NotesSubBeatLabel, L"NotesSubBeatLabel");
			this->NotesSubBeatLabel->Name = L"NotesSubBeatLabel";
			// 
			// NotesBeatLabel
			// 
			resources->ApplyResources(this->NotesBeatLabel, L"NotesBeatLabel");
			this->NotesBeatLabel->Name = L"NotesBeatLabel";
			// 
			// label28
			// 
			resources->ApplyResources(this->label28, L"label28");
			this->label28->Name = L"label28";
			// 
			// label27
			// 
			resources->ApplyResources(this->label27, L"label27");
			this->label27->Name = L"label27";
			// 
			// label26
			// 
			resources->ApplyResources(this->label26, L"label26");
			this->label26->Name = L"label26";
			// 
			// label25
			// 
			resources->ApplyResources(this->label25, L"label25");
			this->label25->Name = L"label25";
			// 
			// label24
			// 
			resources->ApplyResources(this->label24, L"label24");
			this->label24->Name = L"label24";
			// 
			// label23
			// 
			resources->ApplyResources(this->label23, L"label23");
			this->label23->Name = L"label23";
			// 
			// NextNoteButton
			// 
			resources->ApplyResources(this->NextNoteButton, L"NextNoteButton");
			this->NextNoteButton->Name = L"NextNoteButton";
			this->NextNoteButton->UseVisualStyleBackColor = true;
			this->NextNoteButton->Click += gcnew System::EventHandler(this, &MyForm::NextNoteButton_Click);
			// 
			// PrevNoteButton
			// 
			resources->ApplyResources(this->PrevNoteButton, L"PrevNoteButton");
			this->PrevNoteButton->Name = L"PrevNoteButton";
			this->PrevNoteButton->UseVisualStyleBackColor = true;
			this->PrevNoteButton->Click += gcnew System::EventHandler(this, &MyForm::PrevNoteButton_Click);
			// 
			// DeleteNoteButton
			// 
			resources->ApplyResources(this->DeleteNoteButton, L"DeleteNoteButton");
			this->DeleteNoteButton->ForeColor = System::Drawing::Color::Red;
			this->DeleteNoteButton->Name = L"DeleteNoteButton";
			this->DeleteNoteButton->UseVisualStyleBackColor = true;
			this->DeleteNoteButton->Click += gcnew System::EventHandler(this, &MyForm::DeleteNoteButton_Click);
			// 
			// MadeByLabel
			// 
			resources->ApplyResources(this->MadeByLabel, L"MadeByLabel");
			this->MadeByLabel->Name = L"MadeByLabel";
			// 
			// openFileDialogChart
			// 
			resources->ApplyResources(this->openFileDialogChart, L"openFileDialogChart");
			this->openFileDialogChart->RestoreDirectory = true;
			this->openFileDialogChart->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"mer";
			resources->ApplyResources(this->saveFileDialog1, L"saveFileDialog1");
			this->saveFileDialog1->RestoreDirectory = true;
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveFileDialog_FileOk);
			// 
			// CurrentNoteBox
			// 
			this->CurrentNoteBox->Controls->Add(this->BeatNum2);
			this->CurrentNoteBox->Controls->Add(this->label1);
			this->CurrentNoteBox->Controls->Add(this->Beat);
			this->CurrentNoteBox->Controls->Add(this->BeatNum1);
			this->CurrentNoteBox->Controls->Add(this->MeasureNum);
			this->CurrentNoteBox->Controls->Add(this->SizeTrackBar);
			this->CurrentNoteBox->Controls->Add(this->PosTrackBar);
			this->CurrentNoteBox->Controls->Add(this->posInfo);
			this->CurrentNoteBox->Controls->Add(this->PosLabel);
			this->CurrentNoteBox->Controls->Add(this->PosNum);
			this->CurrentNoteBox->Controls->Add(this->SizeLabel);
			this->CurrentNoteBox->Controls->Add(this->SizeInfo);
			this->CurrentNoteBox->Controls->Add(this->SizeNum);
			resources->ApplyResources(this->CurrentNoteBox, L"CurrentNoteBox");
			this->CurrentNoteBox->Name = L"CurrentNoteBox";
			this->CurrentNoteBox->TabStop = false;
			// 
			// SizeTrackBar
			// 
			resources->ApplyResources(this->SizeTrackBar, L"SizeTrackBar");
			this->SizeTrackBar->Maximum = 60;
			this->SizeTrackBar->Minimum = 1;
			this->SizeTrackBar->Name = L"SizeTrackBar";
			this->SizeTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
			this->SizeTrackBar->Value = 1;
			this->SizeTrackBar->ValueChanged += gcnew System::EventHandler(this, &MyForm::SizeTrackBar_ValueChanged);
			// 
			// PosTrackBar
			// 
			resources->ApplyResources(this->PosTrackBar, L"PosTrackBar");
			this->PosTrackBar->Maximum = 59;
			this->PosTrackBar->Name = L"PosTrackBar";
			this->PosTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
			this->PosTrackBar->ValueChanged += gcnew System::EventHandler(this, &MyForm::PosTrackBar_ValueChanged);
			// 
			// fileSystemWatcher1
			// 
			this->fileSystemWatcher1->EnableRaisingEvents = true;
			this->fileSystemWatcher1->SynchronizingObject = this;
			// 
			// CirclePanel
			// 
			this->CirclePanel->BackColor = System::Drawing::Color::Transparent;
			this->CirclePanel->Controls->Add(this->MadeByLabel);
			resources->ApplyResources(this->CirclePanel, L"CirclePanel");
			this->CirclePanel->Name = L"CirclePanel";
			this->CirclePanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::CirclePanel_Paint);
			this->CirclePanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::CirclePanel_MouseDown);
			this->CirclePanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::CirclePanel_MouseMove);
			this->CirclePanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::CirclePanel_MouseUp);
			// 
			// VisualSettingsBox
			// 
			resources->ApplyResources(this->VisualSettingsBox, L"VisualSettingsBox");
			this->VisualSettingsBox->Controls->Add(this->label2);
			this->VisualSettingsBox->Controls->Add(this->VisualHispeed);
			this->VisualSettingsBox->Name = L"VisualSettingsBox";
			this->VisualSettingsBox->TabStop = false;
			// 
			// PlayButton
			// 
			resources->ApplyResources(this->PlayButton, L"PlayButton");
			this->PlayButton->Name = L"PlayButton";
			this->PlayButton->UseVisualStyleBackColor = true;
			this->PlayButton->Click += gcnew System::EventHandler(this, &MyForm::PlayButton_Click);
			// 
			// songTrackSlider
			// 
			resources->ApplyResources(this->songTrackSlider, L"songTrackSlider");
			this->songTrackSlider->Name = L"songTrackSlider";
			this->songTrackSlider->TickStyle = System::Windows::Forms::TickStyle::None;
			this->songTrackSlider->Scroll += gcnew System::EventHandler(this, &MyForm::songTrackSlider_Scroll);
			// 
			// selectSongFile
			// 
			resources->ApplyResources(this->selectSongFile, L"selectSongFile");
			this->selectSongFile->Name = L"selectSongFile";
			this->selectSongFile->UseVisualStyleBackColor = true;
			this->selectSongFile->Click += gcnew System::EventHandler(this, &MyForm::selectSongFile_Click);
			// 
			// SongPlaybackBox
			// 
			resources->ApplyResources(this->SongPlaybackBox, L"SongPlaybackBox");
			this->SongPlaybackBox->Controls->Add(this->PlaybackSpeedNum);
			this->SongPlaybackBox->Controls->Add(this->VolumeLabel);
			this->SongPlaybackBox->Controls->Add(this->label30);
			this->SongPlaybackBox->Controls->Add(this->SongVolume);
			this->SongPlaybackBox->Controls->Add(this->songFileName);
			this->SongPlaybackBox->Controls->Add(this->PlayButton);
			this->SongPlaybackBox->Controls->Add(this->label29);
			this->SongPlaybackBox->Controls->Add(this->songTrackSlider);
			this->SongPlaybackBox->Controls->Add(this->selectSongFile);
			this->SongPlaybackBox->Name = L"SongPlaybackBox";
			this->SongPlaybackBox->TabStop = false;
			// 
			// VolumeLabel
			// 
			resources->ApplyResources(this->VolumeLabel, L"VolumeLabel");
			this->VolumeLabel->Name = L"VolumeLabel";
			// 
			// SongVolume
			// 
			resources->ApplyResources(this->SongVolume, L"SongVolume");
			this->SongVolume->Maximum = 100;
			this->SongVolume->Name = L"SongVolume";
			this->SongVolume->SmallChange = 5;
			this->SongVolume->TickFrequency = 10;
			this->SongVolume->Value = 100;
			this->SongVolume->Scroll += gcnew System::EventHandler(this, &MyForm::SongVolume_Scroll);
			// 
			// songFileName
			// 
			resources->ApplyResources(this->songFileName, L"songFileName");
			this->songFileName->Name = L"songFileName";
			// 
			// openFileDialogSong
			// 
			resources->ApplyResources(this->openFileDialogSong, L"openFileDialogSong");
			// 
			// backgroundWorkerSong
			// 
			this->backgroundWorkerSong->WorkerReportsProgress = true;
			this->backgroundWorkerSong->WorkerSupportsCancellation = true;
			this->backgroundWorkerSong->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorkerSong_DoWork);
			this->backgroundWorkerSong->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorkerSong_ProgressChanged);
			this->backgroundWorkerSong->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorkerSong_RunWorkerCompleted);
			// 
			// backgroundWorkerPaint
			// 
			this->backgroundWorkerPaint->WorkerReportsProgress = true;
			this->backgroundWorkerPaint->WorkerSupportsCancellation = true;
			this->backgroundWorkerPaint->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorkerPaint_DoWork);
			this->backgroundWorkerPaint->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorkerPaint_ProgressChanged);
			this->backgroundWorkerPaint->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorkerPaint_RunWorkerCompleted);
			// 
			// CurrentObjectBox
			// 
			this->CurrentObjectBox->Controls->Add(this->CurrentObjectText);
			resources->ApplyResources(this->CurrentObjectBox, L"CurrentObjectBox");
			this->CurrentObjectBox->Name = L"CurrentObjectBox";
			this->CurrentObjectBox->TabStop = false;
			// 
			// MyForm
			// 
			this->AllowDrop = true;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->Controls->Add(this->NotesViewBox);
			this->Controls->Add(this->VisualSettingsBox);
			this->Controls->Add(this->CurrentObjectBox);
			this->Controls->Add(this->GimmickBox);
			this->Controls->Add(this->NoteTypeBox);
			this->Controls->Add(this->SongPlaybackBox);
			this->Controls->Add(this->CirclePanel);
			this->Controls->Add(this->CurrentNoteBox);
			this->Controls->Add(this->PreChartViewBox);
			this->Controls->Add(this->MaskSettingsBox);
			this->Controls->Add(this->InitialSettingsPane);
			this->Controls->Add(this->GimmickSettingsBox);
			this->Controls->Add(this->InsertButton);
			this->Controls->Add(this->menuStrip);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->NoteTypeBox->ResumeLayout(false);
			this->NoteTypeBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VisualHispeed))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PlaybackSpeedNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SizeNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PosNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BeatNum2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BeatNum1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MeasureNum))->EndInit();
			this->GimmickBox->ResumeLayout(false);
			this->GimmickBox->PerformLayout();
			this->GimmickSettingsBox->ResumeLayout(false);
			this->GimmickSettingsBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2BeatNum2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2BeatNum1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd2MeasureNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1BeatNum2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1BeatNum1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReverseEnd1MeasureNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndMeasureNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndBeatNum2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StopEndBeatNum1))->EndInit();
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
			this->MaskSettingsBox->ResumeLayout(false);
			this->MaskSettingsBox->PerformLayout();
			this->PreChartViewBox->ResumeLayout(false);
			this->PreChartViewBox->PerformLayout();
			this->NotesViewBox->ResumeLayout(false);
			this->NotesViewBox->PerformLayout();
			this->CurrentNoteBox->ResumeLayout(false);
			this->CurrentNoteBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SizeTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PosTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher1))->EndInit();
			this->CirclePanel->ResumeLayout(false);
			this->CirclePanel->PerformLayout();
			this->VisualSettingsBox->ResumeLayout(false);
			this->VisualSettingsBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->songTrackSlider))->EndInit();
			this->SongPlaybackBox->ResumeLayout(false);
			this->SongPlaybackBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SongVolume))->EndInit();
			this->CurrentObjectBox->ResumeLayout(false);
			this->CurrentObjectBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	System::String^ stdStringToSystemString(std::string input) {
		return gcnew String(input.data());
	}
	std::string SystemStringTostdString(System::String^ input) {
		using namespace Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(input)).ToPointer();
		std::string os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
		return os;
	}
	void mergeIntervals(std::list<std::pair<int, int>> theList) {
		// sort the intervals in increasing order of start position
		theList.sort(compareInterval);

		std::list<std::pair<int, int>>::iterator listITRprev = theList.begin();
		std::list<std::pair<int, int>>::iterator listITR = theList.begin();

		for (listITR++; listITR != theList.end(); listITR++) {
			// If this is not first Interval and overlaps
			// with the previous one
			if (listITRprev->second >= listITR->first) {
				// Merge previous and current Intervals
				listITRprev->second = std::max(listITRprev->second, listITR->second);
			}
			else {
				listITRprev++;
				listITRprev->first = listITR->first;
				listITRprev->second = listITR->second;
			}
		}
	}
	void refreshMapofMasks() {
		mapOfMasks.clear();
		std::pair<int, int> zero(0, 0);
		mapOfMasks[0].push_back(zero);

		for (std::list<NotesNode>::iterator viewMasksITR = theChart.Notes.begin(); viewMasksITR != theChart.Notes.end(); viewMasksITR++) {
			if (viewMasksITR->noteType == 12 || viewMasksITR->noteType == 13) {
				float currentTime = (float)viewMasksITR->beat + ((float)viewMasksITR->subBeat / 1920.f);
				int maskStart, maskEnd;
				maskStart = viewMasksITR->position;
				maskEnd = viewMasksITR->position + viewMasksITR->size;

				//copy previous mask layout to current time if current time is empty
				if (mapOfMasks.find(currentTime) == mapOfMasks.end()) {
					std::map<float, std::list<std::pair<int, int>>>::iterator itr = mapOfMasks.lower_bound(currentTime);
					if (itr != mapOfMasks.end()) {
						if (itr != mapOfMasks.begin()) {
							itr--;
						}
						if (itr->first < currentTime) {
							for (std::list<std::pair<int, int>>::iterator currentListitr = itr->second.begin(); currentListitr != itr->second.end(); currentListitr++) {
								std::pair<int, int> temppair(currentListitr->first, currentListitr->second);
								mapOfMasks[currentTime].push_back(temppair);
							}
						}
					}
					else {
						itr = mapOfMasks.end();
						if (!mapOfMasks.empty()) {
							itr--;
							for (std::list<std::pair<int, int>>::iterator currentListitr = itr->second.begin(); currentListitr != itr->second.end(); currentListitr++) {
								std::pair<int, int> temppair(currentListitr->first, currentListitr->second);
								mapOfMasks[currentTime].push_back(temppair);
							}
						}
					}
				}

				if (viewMasksITR->noteType == 12) {
					if (maskEnd > 60) {
						int differenceEnd = maskEnd - 60;
						int differenceStart = 0;
						maskEnd = 60;
						std::pair<int, int> intervalA(maskStart, maskEnd);
						std::pair<int, int> intervalB(differenceStart, differenceEnd);
						mapOfMasks[currentTime].push_back(intervalA);
						mapOfMasks[currentTime].push_back(intervalB);
					}
					else {
						std::pair<int, int> intervalA(maskStart, maskEnd);
						mapOfMasks[currentTime].push_back(intervalA);
					}
				}

				if (viewMasksITR->noteType == 13) {
					if (maskEnd > 60) {
						int differenceEnd = maskEnd - 60;
						int differenceStart = 0;
						maskEnd = 60;
						std::pair<int, int> intervalA(maskStart, maskEnd);
						std::pair<int, int> intervalB(differenceStart, differenceEnd);
						for (std::list<std::pair<int, int>>::iterator currentMaskITR = mapOfMasks[currentTime].begin(); currentMaskITR != mapOfMasks[currentTime].end(); currentMaskITR++) {
							if (maskStart <= currentMaskITR->first && maskEnd >= currentMaskITR->first) { //mask to delete overlaps start of pre-existing mask
								if (maskEnd <= currentMaskITR->second) {
									currentMaskITR->first = maskEnd;
								}
								else { ////mask to delete overlaps all of pre-existing mask
									currentMaskITR->first = 0;
									currentMaskITR->second = 0;
								}
							}
							else if (maskStart > currentMaskITR->first && maskEnd < currentMaskITR->second) { //mask to delete in the middle pre-existing mask
								std::pair<int, int> newPair(maskEnd, currentMaskITR->second);
								mapOfMasks[currentTime].push_back(newPair);
								currentMaskITR->second = maskStart;
							}
							else if (maskStart < currentMaskITR->second && maskEnd >= currentMaskITR->second) { //mask to delete overlaps end of pre-existing mask
								currentMaskITR->second = maskStart;
							}
							if (differenceStart <= currentMaskITR->first && differenceEnd >= currentMaskITR->first) { //mask to delete overlaps start of pre-existing mask
								if (differenceEnd <= currentMaskITR->second) {
									currentMaskITR->first = differenceEnd;
								}
								else { ////mask to delete overlaps all of pre-existing mask
									currentMaskITR->first = 0;
									currentMaskITR->second = 0;
								}
							}
							else if (differenceStart > currentMaskITR->first && differenceEnd < currentMaskITR->second) { //mask to delete in the middle pre-existing mask
								std::pair<int, int> newPair(differenceEnd, currentMaskITR->second);
								mapOfMasks[currentTime].push_back(newPair);
								currentMaskITR->second = differenceStart;
							}
							else if (differenceStart < currentMaskITR->second && differenceEnd >= currentMaskITR->second) { //mask to delete overlaps end of pre-existing mask
								currentMaskITR->second = differenceStart;
							}
						}
					}
					else {
						std::pair<int, int> intervalA(maskStart, maskEnd);
						for (std::list<std::pair<int, int>>::iterator currentMaskITR = mapOfMasks[currentTime].begin(); currentMaskITR != mapOfMasks[currentTime].end(); currentMaskITR++) {
							if (maskStart <= currentMaskITR->first && maskEnd >= currentMaskITR->first) { //mask to delete overlaps start of pre-existing mask
								if (maskEnd <= currentMaskITR->second) {
									currentMaskITR->first = maskEnd;
								}
								else { ////mask to delete overlaps all of pre-existing mask
									currentMaskITR->first = 0;
									currentMaskITR->second = 0;
								}
							}
							else if (maskStart > currentMaskITR->first && maskEnd < currentMaskITR->second) { //mask to delete in the middle pre-existing mask
								std::pair<int, int> newPair(maskEnd, currentMaskITR->second);
								mapOfMasks[currentTime].push_back(newPair);
								currentMaskITR->second = maskStart;
								break;
							}
							else if (maskStart < currentMaskITR->second && maskEnd >= currentMaskITR->second) { //mask to delete overlaps end of pre-existing mask
								currentMaskITR->second = maskStart;
							}
						}
					}
				}
				mergeIntervals(mapOfMasks[currentTime]);
			}
		}
	}
	void refreshMapofNotes() {
		mapOfNotes.clear();
		for (std::list<NotesNode>::iterator NotesITR = theChart.Notes.begin(); NotesITR != theChart.Notes.end(); NotesITR++) {
			float currentTime = (float)NotesITR->beat + ((float)NotesITR->subBeat / 1920.f);
			if (NotesITR->noteType != 12 || NotesITR->noteType != 13) {
				NotesNode tempnode;
				tempnode.beat = NotesITR->beat;
				tempnode.subBeat = NotesITR->subBeat;
				tempnode.noteType = NotesITR->noteType;
				tempnode.position = NotesITR->position;
				tempnode.size = NotesITR->size;
				mapOfNotes[currentTime].push_back(tempnode);
			}
		}
	}
	void refreshMapOfTime() {
		mapOfTimeBetweenMeasures.clear(); 
		mapOfBPMatTime.clear();
		mapOfTSatTime.clear();
		//tempo - X bpm - (eg.:120).
		//time signature - Y / Z - (eg.: 4 / 4).
		//(60,000 / X) = time of 1/4th of measure, so multiply Time Signiture by 4
		//(60,000 / X) * (Y / Z) * 4 = time per measure (milliseconds)
		float oneFourthMultiplier = 4.f;
		float TS = (float)InitTimeSigNum1->Value / (float)InitTimeSigNum2->Value;
		// if nothing exists yet then make measure 0 match initial values
		// PreChart list should overwrite this if it has anything
		mapOfTimeBetweenMeasures[0] = ((float)milInMinute / (float)InitialBPMNum->Value) * oneFourthMultiplier * TS;

		if (!theChart.PreChart.empty()) {
			for (std::list<PreChartNode>::iterator viewGimmicksITR = theChart.PreChart.begin(); viewGimmicksITR != theChart.PreChart.end(); viewGimmicksITR++) {
				float currentTime = (float)viewGimmicksITR->beat + ((float)viewGimmicksITR->subBeat / 1920.f);
				if (viewGimmicksITR->type == 2 || viewGimmicksITR->type == 3) { // First run through fills maps of BPMs and Time Signatures
					//make current time values in maps current to what the PreChart list is saying
					if(viewGimmicksITR->type == 2)
						mapOfBPMatTime[currentTime] = (float)viewGimmicksITR->BPM;
					if (viewGimmicksITR->type == 3) {
						std::pair<int, int> tempTS(viewGimmicksITR->beatDiv1, viewGimmicksITR->beatDiv2);
						mapOfTSatTime[currentTime] = tempTS;
					}

					//put the previous BPM into map of time at any point a time signature happens and there's no BPM at current time
					if (mapOfBPMatTime.find(currentTime) == mapOfBPMatTime.end()) {
						std::map<float, float>::iterator BPMitr = mapOfBPMatTime.lower_bound(currentTime);
						if (BPMitr != mapOfBPMatTime.end()) {
							if (BPMitr != mapOfBPMatTime.begin()) {
								BPMitr--;
							}
							if (BPMitr->first < currentTime) {
								mapOfBPMatTime[currentTime] = BPMitr->second;
							}
						}
						else {
							BPMitr = mapOfBPMatTime.end();
							if (!mapOfBPMatTime.empty()) {
								BPMitr--;
								mapOfBPMatTime[currentTime] = BPMitr->second;
							}
						}
					}
					//put the previous time signature into map of BPMs at any point a BPM happens and there's no BPM at current time
					if (mapOfTSatTime.find(currentTime) == mapOfTSatTime.end()) {
						std::map<float, std::pair<int, int>>::iterator TSitr = mapOfTSatTime.lower_bound(currentTime);
						if (TSitr != mapOfTSatTime.end()) {
							if (TSitr != mapOfTSatTime.begin()) {
								TSitr--;
							}
							if (TSitr->first < currentTime) {
								mapOfTSatTime[currentTime] = TSitr->second;
							}
						}
						else {
							TSitr = mapOfTSatTime.end();
							if (!mapOfTSatTime.empty()) {
								TSitr--;
								mapOfTSatTime[currentTime] = TSitr->second;
							}
						}
					}
				}
			}
			//Put values into map of time between measures
			//this itr could be map of time signatures too, doesnt matter
			for (std::map<float, float>::iterator itr = mapOfBPMatTime.begin(); itr != mapOfBPMatTime.end(); itr++) {
				float TS = (float)mapOfTSatTime[itr->first].first / (float)mapOfTSatTime[itr->first].second;
				mapOfTimeBetweenMeasures[itr->first] = ((float)milInMinute / (float)mapOfBPMatTime[itr->first]) * oneFourthMultiplier * TS;
			}
		}
		refreshMapOfBeatAtTime();
	}
	void refreshMapOfBeatAtTime() {
		mapOfBeatAtTime.clear();
		std::map<float, float>::iterator itr = mapOfTimeBetweenMeasures.begin();
		int startTime = (theChart.offset * 1000.f); //convert off from seconds to milliseconds
		mapOfBeatAtTime[startTime] = 0; //millisecond 0 of song starts at measure 0 of song;
		if (itr != mapOfTimeBetweenMeasures.end()) {
			float prevTimeMil = startTime;
			float prevTimeBeats = itr->first;
			float prevTimePerMeasure = itr->second;
			for (itr++; itr != mapOfTimeBetweenMeasures.end(); itr++) {
				float differenceBetweenMeasures = itr->first - prevTimeBeats;
				float millisecondsFromLastChange = differenceBetweenMeasures * prevTimePerMeasure;
				float nextTime = millisecondsFromLastChange + prevTimeMil;
				mapOfBeatAtTime[nextTime] = itr->first; //millisecond nextTime of song starts at measure itr->first of song

				prevTimeMil = nextTime;
				prevTimeBeats = itr->first;
				prevTimePerMeasure = itr->second;
			}
		}
	}
	void refreshGimmickView() {
		if (!theChart.PreChart.empty()) {
			GimmickBeatLabel->Text = ((viewGimmicksITR)->beat).ToString();

			int num1 = (viewGimmicksITR)->subBeat;
			int num2 = 1920;
			std::string subBeatString = subBeatValueDisplay(num1, num2);
			GimmickSubBeatLabel->Text = stdStringToSystemString(subBeatString);

			switch ((viewGimmicksITR)->type) {
			case 2:
				GimmickTypeLabel->Text = "BPM Change";
				GimmickValueLabel->Text = stdStringToSystemString(to_string((viewGimmicksITR)->BPM));
				break;
			case 3:
				GimmickTypeLabel->Text = "Time Signature Change";
				GimmickValueLabel->Text = stdStringToSystemString(to_string((viewGimmicksITR)->beatDiv1))
					+ "/" + stdStringToSystemString(to_string((viewGimmicksITR)->beatDiv2));
				break;
			case 5:
				GimmickTypeLabel->Text = "Hi-Speed Change";
				GimmickValueLabel->Text = stdStringToSystemString(to_string((viewGimmicksITR)->hiSpeed));
				break;
			case 6:
				GimmickTypeLabel->Text = "Reverse Start";
				GimmickValueLabel->Text = "N/A";
				break;
			case 7:
				GimmickTypeLabel->Text = "Reverse Middle";
				GimmickValueLabel->Text = "N/A";
				break;
			case 8:
				GimmickTypeLabel->Text = "Reverse End";
				GimmickValueLabel->Text = "N/A";
				break;
			case 9:
				GimmickTypeLabel->Text = "Stop Start";
				GimmickValueLabel->Text = "N/A";
				break;
			case 10:
				GimmickTypeLabel->Text = "Stop End";
				GimmickValueLabel->Text = "N/A";
				break;
			}
		}
		else {
			GimmickBeatLabel->Text = "List Empty";
			GimmickSubBeatLabel->Text = "List Empty";
			GimmickTypeLabel->Text = "List Empty";
			GimmickValueLabel->Text = "N/A";
		}
	}
	std::string refreshCurrentNoteLabel(int currentNoteType) {
		//CurrentObjectText->ForeColor = returnColor(currentNoteType);
		switch (currentNoteType) {
		case 1:
			return "Touch [No Bonus]";
		case 2:
			return "Touch [Bonus Get]";
		case 3:
			return "Snap (R) [No Bonus]";
		case 4:
			return "Snap (B) [No Bonus]";
		case 5:
			return "Slide (O) [No Bonus]";
		case 6:
			return "Slide (O) [Bonus Get]";
		case 7:
			return "Slide (G) [No Bonus]";
		case 8:
			return "Slide (G) [Bonus Get]";
		case 9:
			return "Hold Start [No Bonus]";
		case 10:
			if (EndHoldBox->Checked) {
				return "Hold End";
			}
			else {
				return "Hold Middle";
			}
		case 11:
			return "Hold End";
		case 12:
			if (MaskClockwise->Checked) {
				return "Mask Add (Clockwise)";
			}
			else if (MaskCClockwise->Checked) {
				return "Mask Add (Counter-Clockwise)";
			}
			else {
				return "Mask Add (From Center)";
			}
		case 13:
			if (MaskClockwise->Checked) {
				return "Mask Remove (Clockwise)";
			}
			else if (MaskCClockwise->Checked) {
				return "Mask Remove (Counter-Clockwise)";
			}
			else {
				return "Mask Remove (To Center)";
			}
		case 14:
			return "End Of Chart";
		case 16:
			return "Chain";
		case 20:
			return "Touch [R Note]";
		case 21:
			return "Snap (R) [R Note]";
		case 22:
			return "Snap (B) [R Note]";
		case 23:
			return "Slide (O) [R Note]";
		case 24:
			return "Slide (G) [R Note]";
		case 25:
			return "Hold Start [R Note]";
		case 26:
			return "Chain [R Note]";
		}
		return "None Selected";
	}
	std::string refreshCurrentNoteViewLabel(int currentNoteType) {
		switch (currentNoteType) {
		case 1:
			return "Touch [No Bonus]";
		case 2:
			return "Touch [Bonus Get]";
		case 3:
			return "Snap (R) [No Bonus]";
		case 4:
			return "Snap (B) [No Bonus]";
		case 5:
			return "Slide (O) [No Bonus]";
		case 6:
			return "Slide (O) [Bonus Get]";
		case 7:
			return "Slide (G) [No Bonus]";
		case 8:
			return "Slide (G) [Bonus Get]";
		case 9:
			return "Hold Start [No Bonus]";
		case 10:
			return "Hold Middle";
		case 11:
			return "Hold End";
		case 12:
			return "Mask Add";
		case 13:
			return "Mask Remove";
		case 14:
			return "End Of Chart";
		case 16:
			return "Chain";
		case 20:
			return "Touch [R Note]";
		case 21:
			return "Snap (R) [R Note]";
		case 22:
			return "Snap (B) [R Note]";
		case 23:
			return "Slide (O) [R Note]";
		case 24:
			return "Slide (G) [R Note]";
		case 25:
			return "Hold Start [R Note]";
		case 26:
			return "Chain [R Note]";
		}
		return "List Empty";
	}
	void refreshNotesView() {
		if (!theChart.Notes.empty()) {
			NotesBeatLabel->Text = ((viewNotesITR)->beat).ToString();

			float num1 = (viewNotesITR)->subBeat;
			float num2 = 1920;
			std::string subBeatString = subBeatValueDisplay(num1, num2);
			NotesSubBeatLabel->Text = stdStringToSystemString(subBeatString);
			bool refreshThePaint = false;

			if (MatchNoteCheckBox->Checked) {
				PosNum->Value = viewNotesITR->position;
				SizeNum->Value = viewNotesITR->size;
				SelectedNoteTypeVisual = viewNotesITR->noteType;
				if (SelectedNoteTypeVisual != 10 && SelectedNoteTypeVisual != 11 && SelectedNoteTypeVisual != 9 && SelectedNoteTypeVisual != 25) {
					SelectedLineType = 1;
					SelectedNoteType = viewNotesITR->noteType;
				}
				CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			}
			if (MatchTimeCheckBox->Checked) {
				noteRefresh = true;
				MeasureNum->Value = viewNotesITR->beat;
				BeatNum2->Value = (int)subBeatValue2(num1, num2); //change 2 first so that 1 doesnt become larger and make it round up to the next beat
				BeatNum1->Value = (int)subBeatValue1(num1, num2);
				noteRefresh = false;
				refreshThePaint = true;
			}
			if (highlightViewedNoteToolStripMenuItem->Checked) {
				refreshThePaint = true;
			}
			if (refreshThePaint) {
				RefreshPaint();
			}

			NotesPosLabel->Text = stdStringToSystemString(to_string((viewNotesITR)->position));
			NotesSizeLabel->Text = stdStringToSystemString(to_string((viewNotesITR)->size));
			NotesMaskLabel->Text = "N/A";

			NotesTypeLabel->Text = stdStringToSystemString(refreshCurrentNoteViewLabel((viewNotesITR)->noteType));
			if ((viewNotesITR)->noteType == 12) {
				switch ((viewNotesITR)->BGType) {
				case 0:
					NotesMaskLabel->Text = "Counter-Clockwise";
					break;
				case 1:
					NotesMaskLabel->Text = "Clockwise";
					break;
				case 2:
					NotesMaskLabel->Text = "From Center";
					break;
				}
			}
			if ((viewNotesITR)->noteType == 13) {
				switch ((viewNotesITR)->BGType) {
				case 0:
					NotesMaskLabel->Text = "Counter-Clockwise";
					break;
				case 1:
					NotesMaskLabel->Text = "Clockwise";
					break;
				case 2:
					NotesMaskLabel->Text = "To Center";
					break;
				}
			}
		}
		else {
			NotesBeatLabel->Text = "List Empty";
			NotesSubBeatLabel->Text = "List Empty";
			NotesTypeLabel->Text = "List Empty";
			NotesPosLabel->Text = "N/A";
			NotesSizeLabel->Text = "N/A";
			NotesMaskLabel->Text = "N/A";
		}
	}
	std::string subBeatValueDisplay(float num1, float num2) {
		float denom = findGCD(num1, num2);
		num1 /= denom;
		num2 /= denom;
		switch ((int)num2) {
		case 0:
			num1 *= 16;
			num2 = 16;
			break;
		case 1:
			num1 *= 16;
			num2 = 16;
			break;
		case 2:
			num1 *= 8;
			num2 = 16;
			break;
		case 3:
			num1 *= 4;
			num2 = 12;
			break;
		case 4:
			num1 *= 4;
			num2 = 16;
			break;
		case 6:
			num1 *= 2;
			num2 = 12;
			break;
		case 8:
			num1 *= 2;
			num2 = 16;
			break;
		}

		return to_string((int)num1) + "/" + to_string((int)num2);
	}
	float subBeatValue1(float num1, float num2) {
		float denom = findGCD(num1, num2);
		num1 /= denom;
		num2 /= denom;
		switch ((int)num2) {
		case 0:
			num1 *= 16;
			break;
		case 1:
			num1 *= 16;
			break;
		case 2:
			num1 *= 8;
			break;
		case 3:
			num1 *= 4;
			break;
		case 4:
			num1 *= 4;
			break;
		case 6:
			num1 *= 2;
			break;
		case 8:
			num1 *= 2;
			break;
		}

		return num1;
	}
	float subBeatValue2(float num1, float num2) {
		float denom = findGCD(num1, num2);
		num1 /= denom;
		num2 /= denom;
		switch ((int)num2) {
		case 0:
			return 16;
		case 1:
			return 16;
		case 2:
			return 16;
		case 3:
			return 12;
		case 4:
			return 16;
		case 6:
			return 12;
		case 8:
			return 16;
		}
		return num2;
	}
	private: System::Void newToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		theChart.offset = 0.000000;
		theChart.movieOffset = 0.000000;
		theChart.Notes.clear();
		theChart.PreChart.clear();
		refreshGimmickView();
		refreshMapofMasks();
		refreshMapofNotes();
		refreshNotesView();
		RefreshPaint();
	}
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		exit(0);
	}
	void saveFile() {
		theChart.PreChart.sort(sortPreChartListByBeat);
		theChart.Notes.sort(sortNotesListByBeat);

		std::ofstream chartFile;
		chartFile.open(chartFilePath);


		chartFile << std::fixed << std::setprecision(6)
			<< "#MUSIC_SCORE_ID 0\n"
			<< "#MUSIC_SCORE_VERSION 0\n"
			<< "#GAME_VERSION \n"
			<< "#MUSIC_FILE_PATH " << theChart.songFileName << "\n"
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
			case 25:
				chartFile << std::right << std::fixed << std::setw(5) << findLine((itr)->nextNode);
				break;
			default:
				chartFile << "";
			}
			chartFile << "\n";
			line++;
		}

		chartFile.close();
	}
	private: System::Void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (chartFilePath != "") {
			saveFile();
		}
		else {
			saveAsToolStripMenuItem_Click(sender, e);
		}
	}
	private: System::Void saveAsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			chartFilePath = SystemStringTostdString(saveFileDialog1->FileName);
		}
		if (chartFilePath != "") {
			saveFile();
		}
	}
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		theChart.offset = 0.000000;
		theChart.movieOffset = 0.000000;
		theChart.Notes.clear();
		theChart.PreChart.clear();

		std::ifstream chartFile;
		if (openFileDialogChart->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			chartFilePath = SystemStringTostdString(openFileDialogChart->FileName);
		}
		if (chartFilePath != "") {
			chartFile.open(chartFilePath);
		}

		std::string temp;
		while (!chartFile.eof()) {
			if (temp == "#MUSIC_FILE_PATH") {
				chartFile >> theChart.songFileName;
				temp = theChart.songFileName;
				//songFileName->Text = stdStringToSystemString(theChart.songFileName);
				if (temp == "#OFFSET") {
					songFileName->Text = "Select File (.ogg)";
					theChart.songFileName = "[Replace with name of file]";
				}
			}
			if (temp == "#OFFSET") {
				chartFile >> theChart.offset;
				temp = theChart.offset;
				OffsetNum->Value = (System::Decimal)theChart.offset;
				if (temp == "#BODY") {
					OffsetNum->Value = 0;
					theChart.offset = 0;
				}
			}
			if (temp == "#MOVIEOFFSET") {
				chartFile >> theChart.movieOffset;
				temp = theChart.movieOffset;
				MovieOffsetNum->Value = (System::Decimal)theChart.movieOffset;
				if (temp == "#BODY") {
					MovieOffsetNum->Value = 0;
					theChart.movieOffset = 0;
				}
			}
			if (temp == "#BODY") {
				break;
			}
			chartFile >> temp;
		}
		if (theChart.offset < 0.0) {
			songTrackSlider->Minimum = (int)(theChart.offset * 1000.f);
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
				if (tempNotes.noteType == 9 || tempNotes.noteType == 10 || tempNotes.noteType == 25) {
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

		viewNotesITR = theChart.Notes.begin();
		viewGimmicksITR = theChart.PreChart.begin();
		refreshGimmickView();
		refreshNotesView();
		refreshMapofMasks();
		refreshMapofNotes();
		RefreshPaint();
		refreshMapOfTime();
	}
	private: System::Void InsertButton_Click(System::Object^ sender, System::EventArgs^ e) {
		InsertObject();
	}
	System::Void InsertObject() {
		NotesNode tempNotesNode;
		PreChartNode tempPreChartNode;

		if (SelectedLineType == 1) {
			tempNotesNode.beat = (int)MeasureNum->Value;
			tempNotesNode.subBeat = std::round((1920.f / (float)BeatNum2->Value) * (float)BeatNum1->Value);
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
			if (SelectedNoteType == 11) {
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 25;
					CurrentObjectText->Text = "Hold Start [R Note]";
				}
				else {
					SelectedNoteType = 9;
					CurrentObjectText->Text = "Hold Start [No Bonus]";
				}
			}

			theChart.Notes.push_back(tempNotesNode);
			float currentTime = (float)tempNotesNode.beat + ((float)tempNotesNode.subBeat / 1920);
			mapOfNotes[currentTime].push_back(tempNotesNode);
			if (!theChart.Notes.empty()) {
				viewNotesITR = theChart.Notes.end();
				viewNotesITR--;
				switch (viewNotesITR->noteType) {
				case 9:
					viewNotesITR->prevNode = theChart.Notes.end();
					viewNotesITR->nextNode = theChart.Notes.end();
					holdNoteitr = viewNotesITR;
					break;
				case 10:
					viewNotesITR->prevNode = holdNoteitr;
					viewNotesITR->prevNode->nextNode = viewNotesITR;
					viewNotesITR->nextNode = theChart.Notes.end();
					holdNoteitr = viewNotesITR;
					break;
				case 11:
					viewNotesITR->prevNode = holdNoteitr;
					viewNotesITR->prevNode->nextNode = viewNotesITR;
					viewNotesITR->nextNode = theChart.Notes.end();
					holdNoteitr = theChart.Notes.end();
					break;
				case 25:
					viewNotesITR->prevNode = theChart.Notes.end();
					viewNotesITR->nextNode = theChart.Notes.end();
					holdNoteitr = viewNotesITR;
					break;
				}
			}
			SelectedNoteTypeVisual = viewNotesITR->noteType;
			theChart.Notes.sort(sortNotesListByBeat);
			if (SelectedNoteType == 12 || SelectedNoteType == 13) {
				refreshMapofMasks();
			}
			refreshNotesView();
		}
		else {
			tempPreChartNode.beat = (int)MeasureNum->Value;
			tempPreChartNode.subBeat = std::round((1920.f / (float)BeatNum2->Value) * (float)BeatNum1->Value);
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

				tempPreChartNode.beat = (int)ReverseEnd1MeasureNum->Value;
				tempPreChartNode.subBeat = std::round((1920.f / (float)ReverseEnd1BeatNum2->Value) * (float)ReverseEnd1BeatNum1->Value);
				tempPreChartNode.type = 7;
				theChart.PreChart.push_back(tempPreChartNode);

				tempPreChartNode.beat = (int)ReverseEnd2MeasureNum->Value;
				tempPreChartNode.subBeat = std::round((1920.f / (float)ReverseEnd2BeatNum2->Value) * (float)ReverseEnd2BeatNum1->Value);
				tempPreChartNode.type = 8;
				theChart.PreChart.push_back(tempPreChartNode);
			}
			if (SelectedLineType == 9) { //Stop
				theChart.PreChart.push_back(tempPreChartNode);

				tempPreChartNode.beat = (int)StopEndMeasureNum->Value;
				tempPreChartNode.subBeat = std::round((1920.f / (float)StopEndBeatNum2->Value) * (float)StopEndBeatNum1->Value);
				tempPreChartNode.type = 10;
				theChart.PreChart.push_back(tempPreChartNode);
			}
			if (!theChart.PreChart.empty()) {
				viewGimmicksITR = theChart.PreChart.end();
				viewGimmicksITR--;
			}
			theChart.PreChart.sort(sortPreChartListByBeat);
			refreshGimmickView();
			refreshMapOfTime();
		}
		RefreshPaint();
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
			viewGimmicksITR = theChart.PreChart.end();
			viewGimmicksITR--;
		}
		if (!TimeSigFound) {
			tempPreChartNode.beat = 0;
			tempPreChartNode.subBeat = 0;
			tempPreChartNode.type = 3;
			tempPreChartNode.beatDiv1 = (int)InitTimeSigNum1->Value;
			tempPreChartNode.beatDiv2 = (int)InitTimeSigNum2->Value;
			theChart.PreChart.push_back(tempPreChartNode);
			viewGimmicksITR = theChart.PreChart.end();
			viewGimmicksITR--;
		}
		theChart.PreChart.sort(sortPreChartListByBeat);
		if (theChart.offset < 0.0) {
			songTrackSlider->Minimum = (int)(theChart.offset * 1000.f);
		}
		refreshGimmickView();
		refreshMapOfTime();
		saveToolStripMenuItem_Click(sender, e);
	}
	private: System::Void TapButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusGetRadioButton->Checked) {
				SelectedNoteType = 2;
			}
			else if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 20;
			}
			else {
				SelectedNoteType = 1;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
		}
		SelectedLineType = 1;
		RefreshPaint();
	}
	private: System::Void OrangeButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusGetRadioButton->Checked) {
				SelectedNoteType = 6;
			}
			else if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 23;
			}
			else {
				SelectedNoteType = 5;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
			SelectedLineType = 1;
		}
		RefreshPaint();
	}
	private: System::Void GreenButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusGetRadioButton->Checked == true) {
				SelectedNoteType = 8;
			}
			else if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 24;
			}
			else {
				SelectedNoteType = 7;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
			SelectedLineType = 1;
		}
		RefreshPaint();
	}
	private: System::Void RedButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 21;
			}
			else {
				SelectedNoteType = 3;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
			SelectedLineType = 1;
		}
		RefreshPaint();
	}
	private: System::Void BlueButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 22;
			}
			else {
				SelectedNoteType = 4;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
			SelectedLineType = 1;
		}
		RefreshPaint();
	}
	private: System::Void YellowButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 26;
			}
			else {
				SelectedNoteType = 16;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
			SelectedLineType = 1;
		}
		RefreshPaint();
	}
	private: System::Void EndChartButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			SelectedNoteType = 14;
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
			SelectedLineType = 1;
		}
		RefreshPaint();
	}
	private: System::Void HoldButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (BonusFlairRadioButton->Checked) {
				SelectedNoteType = 25;
			}
			else {
				SelectedNoteType = 9;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
			SelectedLineType = 1;
		}
		RefreshPaint();
	}
	private: System::Void MaskButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			if (AddMask->Checked) {
				SelectedNoteType = 12;
			}
			else {
				SelectedNoteType = 13;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
			SelectedLineType = 1;
		}
		RefreshPaint();
	}
	private: System::Void BPMChange_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "BPM Change";
			SelectedLineType = 2;
		}
		RefreshPaint();
	}
	private: System::Void TimeSignature_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "Time Signature Change";
			SelectedLineType = 3;
		}
		RefreshPaint();
	}
	private: System::Void Hispeed_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "Hi-Speed Change";
			SelectedLineType = 5;
		}
		RefreshPaint();
	}
	private: System::Void Stop_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "Stop";
			SelectedLineType = 9;
		}
		RefreshPaint();
	}
	private: System::Void Reverse_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType != 10) {
			CurrentObjectText->Text = "Reverse";
			SelectedLineType = 6;
		}
		RefreshPaint();
	}
	private: System::Void EndHoldBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedNoteType == 10) {
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
		}
		RefreshPaint();
	}
	private: System::Void NoBonusRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 2:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 1;
				}
				break;
			case 6:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 5;
				}
				break;
			case 8:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 7;
				}
				break;
			case 20:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 1;
				}
				break;
			case 21:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 3;
				}
				break;
			case 22:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 4;
				}
				break;
			case 23:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 5;
				}
				break;
			case 24:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 7;
				}
				break;
			case 25:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 9;
				}
				break;
			case 26:
				if (NoBonusRadioButton->Checked) {
					SelectedNoteType = 16;
				}
				break;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
		}
	}
	private: System::Void BonusGetRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 1:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 2;
				}
				break;
			case 5:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 6;
				}
				break;
			case 7:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 8;
				}
				break;
			case 20:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 2;
				}
				break;
			case 23:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 6;
				}
				break;
			case 24:
				if (BonusGetRadioButton->Checked) {
					SelectedNoteType = 8;
				}
				break;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
		}
	}
	private: System::Void BonusFlairRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			switch (SelectedNoteType) {
			case 1:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 20;
				}
				break;
			case 2:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 20;
				}
				break;
			case 3:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 21;
				}
				break;
			case 4:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 22;
				}
				break;
			case 5:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 23;
				}
				break;
			case 6:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 23;
				}
				break;
			case 7:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 24;
				}
				break;
			case 8:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 24;
				}
				break;
			case 9:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 25;
				}
				break;
			case 16:
				if (BonusFlairRadioButton->Checked) {
					SelectedNoteType = 26;
				}
				break;
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
		}
	}
	private: System::Void AddMask_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (AddMask->Checked) {
			MaskCenter->Text = "From Center";
		}
		if (SelectedLineType == 1) {
			if (SelectedNoteType == 13) {
				if (AddMask->Checked) {
					SelectedNoteType = 12;
				}
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
		}
		RefreshPaint();
	}
	private: System::Void RemoveMask_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (RemoveMask->Checked) {
			MaskCenter->Text = "To Center";
		}
		if (SelectedLineType == 1) {
			if (SelectedNoteType == 12) {
				if (RemoveMask->Checked) {
					SelectedNoteType = 13;
				}
			}
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
			SelectedNoteTypeVisual = SelectedNoteType;
		}
		RefreshPaint();
	}
	private: System::Void MaskClockwise_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
		}
	}
	private: System::Void MaskCClockwise_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
		}
	}
	private: System::Void MaskCenter_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedLineType == 1) {
			CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
		}
	}
	private: System::Void ReverseEnd1BeatNum1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (ReverseEnd1BeatNum1->Value >= ReverseEnd1BeatNum2->Value) {
			ReverseEnd1BeatNum1->Value = 0;
			ReverseEnd1MeasureNum->Value++;
		}
		if (ReverseEnd1BeatNum1->Value < 0) {
			if (ReverseEnd1MeasureNum->Value > 0) {
				int temp = (int)ReverseEnd1BeatNum2->Value - 1;
				ReverseEnd1BeatNum1->Value = (System::Decimal)temp;
				ReverseEnd1MeasureNum->Value--;
			}
			else {
				ReverseEnd1BeatNum1->Value = 0;
			}
		}
	}
	private: System::Void ReverseEnd2BeatNum1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (ReverseEnd2BeatNum1->Value >= ReverseEnd2BeatNum2->Value) {
			ReverseEnd2BeatNum1->Value = 0;
			ReverseEnd2MeasureNum->Value++;
		}
		if (ReverseEnd2BeatNum1->Value < 0) {
			if (ReverseEnd2MeasureNum->Value > 0) {
				int temp = (int)ReverseEnd2BeatNum2->Value - 1;
				ReverseEnd2BeatNum1->Value = (System::Decimal)temp;
				ReverseEnd2MeasureNum->Value--;
			}
			else {
				ReverseEnd2BeatNum1->Value = 0;
			}
		}
	}
	private: System::Void StopEndBeatNum1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (StopEndBeatNum1->Value >= StopEndBeatNum2->Value) {
			StopEndBeatNum1->Value = 0;
			StopEndMeasureNum->Value++;
		}
		if (StopEndBeatNum1->Value < 0) {
			if (StopEndMeasureNum->Value > 0) {
				int temp = (int)StopEndBeatNum2->Value - 1;
				StopEndBeatNum1->Value = (System::Decimal)temp;
				StopEndMeasureNum->Value--;
			}
			else {
				StopEndBeatNum1->Value = 0;
			}
		}
	}
	private: System::Void PrevGimmickButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!theChart.PreChart.empty()) {
			if (viewGimmicksITR != theChart.PreChart.begin()) {
				viewGimmicksITR--;
			}
			else {
				viewGimmicksITR = theChart.PreChart.end();
				viewGimmicksITR--;
			}
			refreshGimmickView();
		}
	}
	private: System::Void NextGimmickButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!theChart.PreChart.empty()) {
			viewGimmicksITR++;
			if (viewGimmicksITR == theChart.PreChart.end()) {
				viewGimmicksITR = theChart.PreChart.begin();
			}
			refreshGimmickView();
		}
	}
	private: System::Void DeleteGimmickButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!theChart.PreChart.empty()) {
			std::list<PreChartNode>::iterator viewGimmicksITRtemp = viewGimmicksITR;
			if (viewGimmicksITR == theChart.PreChart.begin()) {
				viewGimmicksITR++;
			}
			else {
				viewGimmicksITR--;
			}
			theChart.PreChart.erase(viewGimmicksITRtemp);
			refreshGimmickView();
		}
	}
	private: System::Void PrevNoteButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!theChart.Notes.empty()) {
			if (viewNotesITR != theChart.Notes.begin()) {
				viewNotesITR--;
			}
			else {
				viewNotesITR = theChart.Notes.end();
				viewNotesITR--;
			}
			refreshNotesView();
		}
	}
	private: System::Void NextNoteButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!theChart.Notes.empty()) {
			viewNotesITR++;
			if (viewNotesITR == theChart.Notes.end()) {
				viewNotesITR = theChart.Notes.begin();
			}
			refreshNotesView();
		}
	}
	private: System::Void DeleteNoteButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!theChart.Notes.empty()) {
			bool holdDelete = false;
			do {
				std::list<NotesNode>::iterator viewNotesITRtemp = viewNotesITR;
				if (viewNotesITRtemp->noteType == 9 || viewNotesITRtemp->noteType == 25) { //deletes hold from start until it's all gone
					holdDelete = true;
					while (holdDelete) {
						if (viewNotesITRtemp->noteType == 11) {
							if (viewNotesITR == theChart.Notes.begin()) {
								viewNotesITR++;
							}
							else {
								viewNotesITR--;
							}
							theChart.Notes.erase(viewNotesITRtemp);
							holdDelete = false;
						}
						else {
							if (viewNotesITRtemp->nextNode != theChart.Notes.end()) {
								viewNotesITR = viewNotesITRtemp->nextNode;
								theChart.Notes.erase(viewNotesITRtemp);
								viewNotesITRtemp = viewNotesITR;
								viewNotesITRtemp->prevNode = theChart.Notes.end();
							}
							else {
								if (viewNotesITR == theChart.Notes.begin()) {
									viewNotesITR++;
								}
								else {
									viewNotesITR--;
								}
								SelectedNoteType = 9;
								if (BonusFlairRadioButton->Checked)
									SelectedNoteType = 25;
								CurrentObjectText->Text = stdStringToSystemString(refreshCurrentNoteLabel(SelectedNoteType));
								theChart.Notes.erase(viewNotesITRtemp);
								holdDelete = false;
							}
						}
					}
					holdDelete = false;
				}
				else if (viewNotesITRtemp->noteType == 10) {
					holdDelete = true;
					viewNotesITRtemp = viewNotesITRtemp->prevNode;
					viewNotesITR = viewNotesITRtemp;
				}
				else if (viewNotesITRtemp->noteType == 11) {
					holdDelete = true;
					viewNotesITRtemp = viewNotesITRtemp->prevNode;
					viewNotesITR = viewNotesITRtemp;
				}
				else {
					if (viewNotesITR == theChart.Notes.begin()) {
						viewNotesITR++;
					}
					else {
						viewNotesITR--;
					}
					theChart.Notes.erase(viewNotesITRtemp);
					holdDelete = false;
				}
			} while (holdDelete);
			refreshNotesView();
			refreshMapofNotes();
		}
		RefreshPaint();
	}
	private: System::Void openFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}
	private: System::Void saveFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}
	Color returnColor(int noteType) {
		switch (noteType) {
		case 1:
			return TapButton->BackColor;
		case 2:
			return TapButton->BackColor;
		case 3:
			return RedButton->BackColor;
		case 4:
			return BlueButton->BackColor;
		case 5:
			return OrangeButton->BackColor;
		case 6:
			return OrangeButton->BackColor;
		case 7:
			return GreenButton->BackColor;
		case 8:
			return GreenButton->BackColor;
		case 9:
			return HoldButton->BackColor;
		case 10:
			return HoldButton->BackColor;
		case 11:
			return HoldButton->BackColor;
		case 16:
			return YellowButton->BackColor;
		case 20:
			return TapButton->BackColor;
		case 21:
			return RedButton->BackColor;
		case 22:
			return BlueButton->BackColor;
		case 23:
			return OrangeButton->BackColor;
		case 24:
			return GreenButton->BackColor;
		case 25:
			return HoldButton->BackColor;
		case 26:
			return YellowButton->BackColor;
		}
		return Color::Transparent;
	}
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		/* MOVED TO PANEL PAINT
		//Note graphics
		Graphics^ notesGraphics = e->Graphics;
		//Circle location and size
		int xPos = InitialSettingsPane->Left;
		int yPos = InitialSettingsPane->Bottom + 6;
		int sizeOfRect = InitialSettingsPane->Width;
		Point noteViewPos = NotesViewBox->Location;
		Point InitSetBoxPos = InitialSettingsPane->Location;
		if (noteViewPos.Y < (sizeOfRect + InitSetBoxPos.Y + InitialSettingsPane->Height)) {
			sizeOfRect = noteViewPos.Y - InitialSettingsPane->Height - InitSetBoxPos.Y - 6;
		}
		//Circle info
		float circleRadius = (sizeOfRect / 2);
		float xCenterOfCircle = circleRadius + xPos;
		float yCenterOfCircle = circleRadius + yPos;
		//Selected object values
		float startAngle = -((float)PosNum->Value * 6);
		float arcLength = -((float)SizeNum->Value * 6);
		//Rectangle the visualization is in
		System::Drawing::Point location(xPos, yPos);
		System::Drawing::Size size(sizeOfRect, sizeOfRect);
		System::Drawing::Rectangle Rect(location, size);
		//Pens for drawing parts of circle
		float widthOfNotePen = 5;
		Pen^ CircleBasePen = gcnew Pen(Color::Black, 3);
		Pen^ CircleLinesPen = gcnew Pen(Color::Black, 2);
		Pen^ CircleNotePen = gcnew Pen(Color::Transparent, widthOfNotePen);
		//Drawing mode
		notesGraphics->SmoothingMode = Drawing2D::SmoothingMode::Default;

		//pre-existing mask values
		float maskStartAngle;
		float maskArcLength;
		//Draw pre-existing mask
		float currentTime = (float)MeasureNum->Value + ((float)BeatNum1->Value / (float)BeatNum2->Value);
		std::map<float, std::list<std::pair<int, int>>>::iterator mapitr = mapOfMasks.lower_bound(currentTime);
		if (mapOfMasks.find(currentTime) == mapOfMasks.end() && Rect.Width >= 1) {
			if (mapitr != mapOfMasks.end()) {
				if (mapitr != mapOfMasks.begin()) {
					mapitr--;
				}
				if (mapitr->first < currentTime) {
					for (std::list<std::pair<int, int>>::iterator listITR = mapitr->second.begin(); listITR != mapitr->second.end(); listITR++) {
						maskStartAngle = -((float)listITR->first * 6);
						maskArcLength = -(((float)listITR->second - (float)listITR->first) * 6);
						notesGraphics->FillPie(Brushes::Silver, Rect, maskStartAngle, maskArcLength);
					}
				}
			}
			else {
				mapitr = mapOfMasks.end();
				if (!mapOfMasks.empty()) {
					mapitr--;
					for (std::list<std::pair<int, int>>::iterator listITR = mapitr->second.begin(); listITR != mapitr->second.end(); listITR++) {
						maskStartAngle = -((float)listITR->first * 6);
						maskArcLength = -(((float)listITR->second - (float)listITR->first) * 6);
						notesGraphics->FillPie(Brushes::Silver, Rect, maskStartAngle, maskArcLength);
					}
				}
			}
		}
		else {
			if (Rect.Width >= 1) {
				for (std::list<std::pair<int, int>>::iterator listITR = mapitr->second.begin(); listITR != mapitr->second.end(); listITR++) {
					maskStartAngle = -((float)listITR->first * 6);
					maskArcLength = -(((float)listITR->second - (float)listITR->first) * 6);
					notesGraphics->FillPie(Brushes::Silver, Rect, maskStartAngle, maskArcLength);
				}
			}
		}

		//Draw selected mask
		if (SelectedLineType == 1 && Rect.Width >= 1) {
			if (SelectedNoteTypeVisual == 12) {
				notesGraphics->FillPie(Brushes::Silver, Rect, startAngle, arcLength);
			}
			if (SelectedNoteTypeVisual == 13) {
				notesGraphics->FillPie(Brushes::White, Rect, startAngle, arcLength);
			}
		}

		if (!alreadyDrawn) {
			Graphics^ circleGraphics = e->Graphics;

			//Draw base circle
			circleGraphics->DrawEllipse(CircleBasePen, Rect);

			//Draw Degree Lines
			for (int i = 0; i < 360; i += 6) { //i is the angle n degrees
				float xStart, yStart, xEnd, yEnd;
				float degToRad = (float)i * PI / 180.0; //i to Radians
				xStart = (circleRadius * cos(degToRad)) + xCenterOfCircle;
				yStart = (circleRadius * sin(degToRad)) + yCenterOfCircle;
				PointF coordPointStart(xStart, yStart);

				float innerRadius = circleRadius - 10;
				CircleLinesPen->Width = 1;
				if (i % 90 == 0) {
					innerRadius = circleRadius - 35.0;
					CircleLinesPen->Width = 4;
				}
				else if (i % 30 == 0) {
					innerRadius = circleRadius - 25.0;
					CircleLinesPen->Width = 2;
				}
				xEnd = (innerRadius * cos(degToRad)) + xCenterOfCircle;
				yEnd = (innerRadius * sin(degToRad)) + yCenterOfCircle;
				PointF coordPointEnd(xEnd, yEnd);

				circleGraphics->DrawLine(CircleLinesPen, coordPointStart, coordPointEnd);
			}
			alreadyDrawn = true;
		}

		//future stuff
		float futStartAngle;
		float futArcLength;
		float xPosFut;
		float yPosFut;
		float sizeOfRectFut;
		float circleRadiusFut;
		float totalTimeShowNotes = 0.5;
		//Draw future holds
		for (std::map<float, std::list<NotesNode>>::iterator notemapitr = mapOfNotes.lower_bound(currentTime); notemapitr != mapOfNotes.end(); notemapitr++) {
			float timeAtITR = notemapitr->first;
			if (timeAtITR <= (currentTime + totalTimeShowNotes)) {
				for (std::list<NotesNode>::iterator listofNotesitr = notemapitr->second.begin(); listofNotesitr != notemapitr->second.end(); listofNotesitr++) {
					if (isHold(listofNotesitr->noteType)) {
						//Future hold values
						futStartAngle = -((float)listofNotesitr->position * 6);
						futArcLength = -((float)listofNotesitr->size * 6);
						CircleNotePen->Color = returnColor(listofNotesitr->noteType);
						//modify rectangle to scale with how long until the note appears
						float NoteScale = 1 - ((timeAtITR - currentTime) * (1 / totalTimeShowNotes)); //0-1 = 0-100%
						sizeOfRectFut = sizeOfRect * NoteScale;
						circleRadiusFut = (sizeOfRectFut / 2);
						xPosFut = InitialSettingsPane->Left + (circleRadius - circleRadiusFut) + 1;
						yPosFut = InitialSettingsPane->Bottom + 6 + (circleRadius - circleRadiusFut) + 1;
						CircleNotePen->Width = widthOfNotePen * NoteScale + 2;

						System::Drawing::Point locationFut(xPosFut, yPosFut);
						System::Drawing::Size sizeFut(sizeOfRectFut, sizeOfRectFut);
						System::Drawing::Rectangle RectFut(locationFut, sizeFut);
						if (RectFut.Width >= 1) {
							notesGraphics->DrawArc(CircleNotePen, RectFut, futStartAngle, futArcLength);
						}
					}
				}
			}
			else {
				notemapitr = mapOfNotes.end();
				notemapitr--;
			}
		}

		//Draw future notes
		for (std::map<float, std::list<NotesNode>>::iterator notemapitr = mapOfNotes.lower_bound(currentTime); notemapitr != mapOfNotes.end(); notemapitr++) {
			float timeAtITR = notemapitr->first;
			if (timeAtITR <= (currentTime + totalTimeShowNotes)) {
				for (std::list<NotesNode>::iterator listofNotesitr = notemapitr->second.begin(); listofNotesitr != notemapitr->second.end(); listofNotesitr++) {
					if (!isHold(listofNotesitr->noteType)) {
						//Future note values
						futStartAngle = -((float)listofNotesitr->position * 6);
						futArcLength = -((float)listofNotesitr->size * 6);
						CircleNotePen->Color = returnColor(listofNotesitr->noteType);
						//modify rectangle to scale with how long until the note appears
						float NoteScale = 1 - ((timeAtITR - currentTime) * (1 / totalTimeShowNotes)); //0-1 = 0-100%
						sizeOfRectFut = sizeOfRect * NoteScale;
						circleRadiusFut = (sizeOfRectFut / 2);
						xPosFut = InitialSettingsPane->Left + (circleRadius - circleRadiusFut) + 1;
						yPosFut = InitialSettingsPane->Bottom + 6 + (circleRadius - circleRadiusFut) + 1;
						CircleNotePen->Width = widthOfNotePen * NoteScale;

						System::Drawing::Point locationFut(xPosFut, yPosFut);
						System::Drawing::Size sizeFut(sizeOfRectFut, sizeOfRectFut);
						System::Drawing::Rectangle RectFut(locationFut, sizeFut);
						if (RectFut.Width >= 1) {
							notesGraphics->DrawArc(CircleNotePen, RectFut, futStartAngle, futArcLength);
						}
					}
				}
			}
			else {
				notemapitr = mapOfNotes.end();
				notemapitr--;
			}
		}


		//Draw selected note
		if (SelectedLineType == 1 && Rect.Width >= 1) {
			CircleNotePen->Color = returnColor(SelectedNoteTypeVisual);
			CircleNotePen->Width = 4;
			notesGraphics->DrawArc(CircleNotePen, Rect, startAngle, arcLength);
		}
		*/
	}
	private: System::Void PosNum_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		RefreshPaint();
	}
	private: System::Void SizeNum_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		RefreshPaint();
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		int paddingFromEdge = 28;
		int paddingBetweenObjects = 6;
		int leftPos = GimmickBox->Right + paddingBetweenObjects;
		int rightPos = PreChartViewBox->Left - paddingBetweenObjects;
		int topPos = GimmickBox->Top;
		int botPos = SongPlaybackBox->Top - paddingBetweenObjects;
		int width = rightPos - leftPos;
		int height = botPos - topPos;
		/*
		if (width < (InitialSettingsPane->Left - leftPos)) {
			topPos = InitialSettingsPane->Top;
			width = (InitialSettingsPane->Left - paddingBetweenObjects) - leftPos;
			height = (NotesViewBox->Top - paddingBetweenObjects) - InitialSettingsPane->Top;
		}
		*/
		Point position(leftPos, topPos);
		CirclePanel->Location = position;
		if (width > height) {
			CirclePanel->Width = height;
			CirclePanel->Height = height;
		}
		else {
			CirclePanel->Width = width;
			CirclePanel->Height = width;
		}
		//InitialSettingsPane->Width = (this->Width - NoteTypeBox->Width - 36);
		//Point position(NoteTypeBox->Width + 12, 27);
		//InitialSettingsPane->Location = position;

		// Update BufferedGraphics size
		bufferedGfxContext->MaximumBuffer = Drawing::Size(CirclePanel->Width + 1, CirclePanel->Height + 1);
		bufferedGfx = bufferedGfxContext->Allocate(CirclePanel->CreateGraphics(),
			Drawing::Rectangle(0, 0, CirclePanel->Width, CirclePanel->Height));
		//DrawToGraphics(bufferedGfx->Graphics);

		RefreshPaint();
	}
	private: System::Void MeasureNum_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		refreshScrollBarFromMeasureNum();
		RefreshPaint();
	}
	private: System::Void BeatNum1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (BeatNum1->Value >= BeatNum2->Value) {
			alreadyRefreshed = true;
			BeatNum1->Value = 0;
			alreadyRefreshed = true;
			MeasureNum->Value++;
		}
		if (BeatNum1->Value < 0) {
			if (MeasureNum->Value > 0) {
				int temp = (int)BeatNum2->Value - 1;
				alreadyRefreshed = true;
				BeatNum1->Value = (System::Decimal)temp;
				alreadyRefreshed = true;
				MeasureNum->Value--;
			}
			else {
				alreadyRefreshed = true;
				BeatNum1->Value = 0;
			}
		}
		refreshScrollBarFromMeasureNum();
		RefreshPaint();
	}
	private: System::Void BeatNum2_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		refreshScrollBarFromMeasureNum();
		RefreshPaint();
	}
	void refreshScrollBarFromMeasureNum() {
		if (!mapOfTimeBetweenMeasures.empty()) {
			float currentMeasure = (float)MeasureNum->Value + ((float)BeatNum1->Value / (float)BeatNum2->Value); //in measures
			float lastTime = 0;
			float timeBetweenBeats;
			float lastMeasure;
			if (mapOfTimeBetweenMeasures.find(currentMeasure) == mapOfTimeBetweenMeasures.end()) {
				std::map<float, float>::iterator itr = mapOfTimeBetweenMeasures.lower_bound(currentMeasure);
				if (itr != mapOfTimeBetweenMeasures.end()) {
					if (itr != mapOfTimeBetweenMeasures.begin()) {
						itr--;
					}
				}
				else {
					itr = mapOfTimeBetweenMeasures.end();
					if (!mapOfTimeBetweenMeasures.empty()) {
						itr--;
					}
				}
				lastMeasure = itr->first;
				timeBetweenBeats = itr->second;
			}
			else {
				lastMeasure = currentMeasure;
				timeBetweenBeats = mapOfTimeBetweenMeasures[currentMeasure]; //use current measure to find last "milliseconds per measure"
			}
			for (std::map<float, float>::iterator itrBaT = mapOfBeatAtTime.begin(); itrBaT != mapOfBeatAtTime.end(); itrBaT++) {
				if (itrBaT->second == lastMeasure) { //use itr->first value in first map to search for itr->second in second map,
					lastTime = itrBaT->first;
					break;
				}
			}
			float differenceInTimeMeasures = currentMeasure - lastMeasure;
			float currentTimeMil = (differenceInTimeMeasures * timeBetweenBeats) + lastTime; //itr->first in second map + ("milliseconds per measure" * time)

			if (currentlyPlayingSong != nullptr) {
				if (currentlyPlayingSong->Paused) {
					scrollBarChanged = true;
					if (currentTimeMil < songTrackSlider->Maximum) {
						songTrackSlider->Value = currentTimeMil;
					}
					else
						songTrackSlider->Value = songTrackSlider->Maximum;
				}
			}
			theCurrentMeasure = currentMeasure;
			scrollBarChanged = false;
		}
	}
	private: System::Void MatchNoteCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		refreshNotesView();
	}
	private: System::Void NextBeatButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!theChart.Notes.empty()) {
			int initialBeat = viewNotesITR->beat;
			while (viewNotesITR->beat == initialBeat) {
				viewNotesITR++;
				if (viewNotesITR == theChart.Notes.end()) {
					viewNotesITR = theChart.Notes.begin();
					break;
				}
			}
			refreshNotesView();
		}
	}
	private: System::Void PrevBeatButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!theChart.Notes.empty()) {
			int initialBeat = viewNotesITR->beat;
			while (viewNotesITR->beat == initialBeat) {
				if (viewNotesITR != theChart.Notes.begin()) {
					viewNotesITR--;
				}
				else {
					viewNotesITR = theChart.Notes.end();
					viewNotesITR--;
					break;
				}
			}
			refreshNotesView();
		}
	}
	private: System::Void MatchTimeCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		refreshNotesView();
	}
	private: System::Void EditNoteButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!isHold(SelectedNoteType)) {
			viewNotesITR->beat = (int)MeasureNum->Value;
			viewNotesITR->subBeat = ((1920 / (int)BeatNum2->Value) * (int)BeatNum1->Value);
			viewNotesITR->noteType = SelectedNoteType;
			viewNotesITR->position = (int)PosNum->Value;
			viewNotesITR->size = (int)SizeNum->Value;
			refreshNotesView();
			refreshMapofNotes();
		}
	}
	private: System::Void SizeTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		SizeNum->Value = SizeTrackBar->Value;
	}
	private: System::Void PosTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		PosNum->Value = PosTrackBar->Value;
	}
	void RefreshPaint() {
		if (!alreadyRefreshed && !noteRefresh) {
			CirclePanel->Refresh();
		}
		else {
			alreadyRefreshed = false;
		}
	}
	private: System::Void CirclePanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		System::Drawing::Rectangle PanelRect(0, 0, CirclePanel->Width, CirclePanel->Height);
		//Pens for drawing parts of circle
		float widthOfBasePen = (float)CirclePanel->Width * (4.f / 600.f); //sizes are essentially the pixel width if the box is 600x600
		float widthOfLinesPen = (float)CirclePanel->Width * (2.f / 600.f);
		float widthOfNotePen = (float)CirclePanel->Width * (8.f / 600.f);
		float widthOfCurrentNotePen = (float)CirclePanel->Width * (4.f / 600.f);
		float widthOfMeasurePen = (float)CirclePanel->Width * (1.f / 600.f);
		float highlightWidth = (float)CirclePanel->Width * (5.f / 600.f);
		float baseLineLength = (float)CirclePanel->Width * (10.f / 285.f); //10 pixels if box is 285x285
		float baseLineWidth = (float)CirclePanel->Width * (1.f / 285.f);
		int BonusTransparency = 75; //0 is full transparent, 255 is max
		int SelectedTransparency = 110;
		Color BonusColor = Color(Color::FromArgb(BonusTransparency, Color::Yellow));
		Color HighlightColor = Color(Color::FromArgb(SelectedTransparency, Color::LightPink));
		Pen^ CircleBasePen = gcnew Pen(Color::Black, widthOfBasePen);
		Pen^ CircleLinesPen = gcnew Pen(Color::Black, widthOfLinesPen);
		Pen^ CircleNotePen = gcnew Pen(Color::Transparent, widthOfNotePen);
		Pen^ CircleBeatPen = gcnew Pen(Color::White, widthOfMeasurePen);
		SolidBrush^ MaskBrush = gcnew SolidBrush(Color::DimGray);
		SolidBrush^ MaskRemoveBrush = gcnew SolidBrush(Color::White);
		//Circle location and size
		float xPos = widthOfNotePen*2;
		float yPos = widthOfNotePen*2;
		float sizeOfRect = CirclePanel->Width - (widthOfNotePen*4);
		//Circle info
		float circleRadius = ((float)sizeOfRect / 2);
		float xCenterOfCircle = circleRadius + xPos;
		float yCenterOfCircle = circleRadius + yPos;
		//Selected object values
		float startAngle = -((float)PosNum->Value * 6);
		float arcLength = -((float)SizeNum->Value * 6);
		//Rectangle the visualization is in
		System::Drawing::Point location(xPos, yPos);
		System::Drawing::Size size(sizeOfRect, sizeOfRect);
		System::Drawing::Rectangle Rect(location, size);
		//Drawing mode
		bufferedGfx->Graphics->SmoothingMode = Drawing2D::SmoothingMode::HighSpeed;
		//Current time
		float currentTime;
		if (scrollBarChanged) {
			currentTime = theCurrentMeasure;
		}
		else {
			currentTime = (float)MeasureNum->Value + ((float)BeatNum1->Value / (float)BeatNum2->Value);
		}
		//How many measures/beats in the future to show notes
		float totalTimeShowNotes = (float)VisualHispeed->Value;
		//future stuff
		float futStartAngle;
		float futArcLength;
		float xPosFut;
		float yPosFut;
		float sizeOfRectFut;
		float circleRadiusFut;
		//pre-existing mask values
		float maskStartAngle;
		float maskArcLength;

		//Make Background Transparent
		SolidBrush^ backgroundBrush = gcnew SolidBrush(this->BackColor);
		bufferedGfx->Graphics->FillRectangle(backgroundBrush, PanelRect);

		//Draw pre-existing mask
		std::map<float, std::list<std::pair<int, int>>>::iterator mapitr = mapOfMasks.lower_bound(currentTime);
		if (mapOfMasks.find(currentTime) == mapOfMasks.end() && Rect.Width >= 1) {
			if (mapitr != mapOfMasks.end()) {
				if (mapitr != mapOfMasks.begin()) {
					mapitr--;
				}
				if (mapitr->first < currentTime) {
					for (std::list<std::pair<int, int>>::iterator listITR = mapitr->second.begin(); listITR != mapitr->second.end(); listITR++) {
						maskStartAngle = -((float)listITR->first * 6);
						maskArcLength = -(((float)listITR->second - (float)listITR->first) * 6);
						bufferedGfx->Graphics->FillPie(MaskBrush, Rect, maskStartAngle, maskArcLength);
					}
				}
			}
			else {
				mapitr = mapOfMasks.end();
				if (!mapOfMasks.empty()) {
					mapitr--;
					for (std::list<std::pair<int, int>>::iterator listITR = mapitr->second.begin(); listITR != mapitr->second.end(); listITR++) {
						maskStartAngle = -((float)listITR->first * 6);
						maskArcLength = -(((float)listITR->second - (float)listITR->first) * 6);
						bufferedGfx->Graphics->FillPie(MaskBrush, Rect, maskStartAngle, maskArcLength);
					}
				}
			}
		}
		else {
			if (Rect.Width >= 1) {
				for (std::list<std::pair<int, int>>::iterator listITR = mapitr->second.begin(); listITR != mapitr->second.end(); listITR++) {
					maskStartAngle = -((float)listITR->first * 6);
					maskArcLength = -(((float)listITR->second - (float)listITR->first) * 6);
					bufferedGfx->Graphics->FillPie(MaskBrush, Rect, maskStartAngle, maskArcLength);
				}
			}
		}

		//Draw selected mask
		if (SelectedLineType == 1 && Rect.Width >= 1) {
			if (SelectedNoteTypeVisual == 12) {
				bufferedGfx->Graphics->FillPie(MaskBrush, Rect, startAngle, arcLength);
			}
			if (SelectedNoteTypeVisual == 13) {
				bufferedGfx->Graphics->FillPie(MaskRemoveBrush, Rect, startAngle, arcLength);
			}
		}

		//Switch Drawing mode
		bufferedGfx->Graphics->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;

		//Draw measure circle
		float nearestMeasure = std::ceil(currentTime);
		for (float nearestMeasure = std::ceil(currentTime); (nearestMeasure - currentTime) < totalTimeShowNotes; nearestMeasure += 1.0) {
			//modify rectangle to scale with how long until the measure appears
			float NoteScaleInitial = 1 - ((nearestMeasure - currentTime) * (1 / totalTimeShowNotes)); //0-1 = 0-100%
			float NoteScale = (std::pow(10.f, NoteScaleInitial)) / 10.f;
			sizeOfRectFut = sizeOfRect * NoteScale;
			circleRadiusFut = (sizeOfRectFut / 2);
			xPosFut = xPos + (circleRadius - circleRadiusFut);
			yPosFut = yPos + (circleRadius - circleRadiusFut);

			System::Drawing::Point locationFut(xPosFut, yPosFut);
			System::Drawing::Size sizeFut(sizeOfRectFut, sizeOfRectFut);
			System::Drawing::Rectangle RectFut(locationFut, sizeFut);
			if (RectFut.Width >= 1) {
				bufferedGfx->Graphics->DrawEllipse(CircleBeatPen, RectFut);
			}
		}


		//Draw base circle
		bufferedGfx->Graphics->DrawEllipse(CircleBasePen, Rect);

		//Draw Degree Lines
		for (int i = 0; i < 360; i += 6) { //i is the angle n degrees
			float xStart, yStart, xEnd, yEnd;
			float degToRad = (float)i * PI / 180.0; //i to Radians
			xStart = (circleRadius * cos(degToRad)) + xCenterOfCircle;
			yStart = (circleRadius * sin(degToRad)) + yCenterOfCircle;
			PointF coordPointStart(xStart, yStart);

			float innerRadius = circleRadius - baseLineLength;
			CircleLinesPen->Width = baseLineWidth;
			if (i % 90 == 0) {
				innerRadius = circleRadius - (baseLineLength * 3.5);
				CircleLinesPen->Width = (baseLineWidth * 3.5);
			}
			else if (i % 30 == 0) {
				innerRadius = circleRadius - (baseLineLength * 2.5);
				CircleLinesPen->Width = (baseLineWidth * 2);
			}
			xEnd = (innerRadius * cos(degToRad)) + xCenterOfCircle;
			yEnd = (innerRadius * sin(degToRad)) + yCenterOfCircle;
			PointF coordPointEnd(xEnd, yEnd);

			bufferedGfx->Graphics->DrawLine(CircleLinesPen, coordPointStart, coordPointEnd);
		}

		//Draw future holds
		for (std::map<float, std::list<NotesNode>>::iterator notemapitr = mapOfNotes.lower_bound(currentTime); notemapitr != mapOfNotes.end(); notemapitr++) {
			float timeAtITR = notemapitr->first;
			if (timeAtITR <= (currentTime + totalTimeShowNotes)) {
				for (std::list<NotesNode>::iterator listofNotesitr = notemapitr->second.begin(); listofNotesitr != notemapitr->second.end(); listofNotesitr++) {
					if (isHold(listofNotesitr->noteType)) {
						//Future hold values
						futStartAngle = -((float)listofNotesitr->position * 6);
						futArcLength = -((float)listofNotesitr->size * 6);
						if (futArcLength != -360) { //increase size for highlight slightly decrease size to better match ingame
							futStartAngle -= 2;
							futArcLength += 4;
						}
						CircleNotePen->Color = returnColor(listofNotesitr->noteType);
						//modify rectangle to scale with how long until the note appears
						float NoteScaleInitial = 1 - ((timeAtITR - currentTime) * (1 / totalTimeShowNotes)); //0-1 = 0-100%
						float NoteScale = (std::pow(10.f, NoteScaleInitial)) / 10.f;
						sizeOfRectFut = sizeOfRect * NoteScale;
						circleRadiusFut = (sizeOfRectFut / 2);
						xPosFut = xPos + (circleRadius - circleRadiusFut);
						yPosFut = yPos + (circleRadius - circleRadiusFut);
						CircleNotePen->Width = widthOfNotePen * NoteScale + 2;

						System::Drawing::Point locationFut(xPosFut, yPosFut);
						System::Drawing::Size sizeFut(sizeOfRectFut, sizeOfRectFut);
						System::Drawing::Rectangle RectFut(locationFut, sizeFut);
						if (RectFut.Width >= 1) {
							bufferedGfx->Graphics->DrawArc(CircleNotePen, RectFut, futStartAngle, futArcLength); //Draw hold

							if (listofNotesitr->noteType == 25) { //If bonus hold
								CircleNotePen->Color = BonusColor;
								CircleNotePen->Width += highlightWidth;
								futStartAngle += 2; //increase size for highlight
								futArcLength -= 4;
								bufferedGfx->Graphics->DrawArc(CircleNotePen, RectFut, futStartAngle, futArcLength); //Draw highlight
							}
							if (highlightViewedNoteToolStripMenuItem->Checked) {
								if (islistITREqualToViewITR(listofNotesitr)) {
									CircleNotePen->Color = HighlightColor;
									CircleNotePen->Width += highlightWidth;
									futStartAngle += 2; //increase size for highlight
									futArcLength -= 4;
									bufferedGfx->Graphics->DrawArc(CircleNotePen, RectFut, futStartAngle, futArcLength); //Draw highlight
								}
							}
						}
					}
				}
			}
			else {
				notemapitr = mapOfNotes.end();
				notemapitr--;
			}
		}

		//Draw future notes
		for (std::map<float, std::list<NotesNode>>::iterator notemapitr = mapOfNotes.lower_bound(currentTime); notemapitr != mapOfNotes.end(); notemapitr++) {
			float timeAtITR = notemapitr->first;
			if (timeAtITR <= (currentTime + totalTimeShowNotes)) {
				for (std::list<NotesNode>::iterator listofNotesitr = notemapitr->second.begin(); listofNotesitr != notemapitr->second.end(); listofNotesitr++) {
					if (!isHold(listofNotesitr->noteType) && listofNotesitr->noteType != 12 && listofNotesitr->noteType != 13) {
						//Future note values
						futStartAngle = -((float)listofNotesitr->position * 6);
						futArcLength = -((float)listofNotesitr->size * 6);
						if (futArcLength != -360) { //increase size for highlight slightly decrease size to better match ingame
							futStartAngle -= 2;
							futArcLength += 4;
						}
						CircleNotePen->Color = returnColor(listofNotesitr->noteType);
						//modify rectangle to scale with how long until the note appears
						float NoteScaleInitial = 1 - ((timeAtITR - currentTime) * (1 / totalTimeShowNotes)); //0-1 = 0-100%
						float NoteScale = (std::pow(10.f, NoteScaleInitial)) / 10.f;
						sizeOfRectFut = sizeOfRect * NoteScale;
						circleRadiusFut = (sizeOfRectFut / 2);
						xPosFut = xPos + (circleRadius - circleRadiusFut);
						yPosFut = yPos + (circleRadius - circleRadiusFut);
						CircleNotePen->Width = widthOfNotePen * NoteScale;

						System::Drawing::Point locationFut(xPosFut, yPosFut);
						System::Drawing::Size sizeFut(sizeOfRectFut, sizeOfRectFut);
						System::Drawing::Rectangle RectFut(locationFut, sizeFut);
						if (RectFut.Width >= 1) {
							bufferedGfx->Graphics->DrawArc(CircleNotePen, RectFut, futStartAngle, futArcLength); //Draw note

							if (listofNotesitr->noteType >= 20) { //If bonus note
								CircleNotePen->Color = BonusColor;
								CircleNotePen->Width += highlightWidth;
								futStartAngle += 2; //increase size for highlight
								futArcLength -= 4;
								bufferedGfx->Graphics->DrawArc(CircleNotePen, RectFut, futStartAngle, futArcLength); //Draw highlight
							}
							if (highlightViewedNoteToolStripMenuItem->Checked) {
								if (islistITREqualToViewITR(listofNotesitr)) {
									CircleNotePen->Color = HighlightColor;
									CircleNotePen->Width += highlightWidth;
									futStartAngle += 2; //increase size for highlight
									futArcLength -= 4;
									bufferedGfx->Graphics->DrawArc(CircleNotePen, RectFut, futStartAngle, futArcLength); //Draw highlight
								}
							}
						}
					}
				}
			}
			else {
				notemapitr = mapOfNotes.end();
				notemapitr--;
			}
		}
		
		// Generate flag for showing cursor
		bool showCursor = showCursorToolStripMenuItem->Checked || mouseDownPos != -1;
		if (currentlyPlayingSong != nullptr) {
			if (!currentlyPlayingSong->Paused) {
				showCursor = showCursorDuringPlaybackToolStripMenuItem->Checked;
			}
		}

		//Draw selected note
		if (SelectedLineType == 1 && Rect.Width >= 1 && showCursor) {
			CircleNotePen->Color = Color(Color::FromArgb(SelectedTransparency, returnColor(SelectedNoteTypeVisual)));
			float spacing = widthOfNotePen + widthOfCurrentNotePen;
			CircleNotePen->Width = spacing * 2.f;
			//Rectangle innerRect(Rect.X + spacing, Rect.Y + spacing, Rect.Width - spacing * 2, Rect.Height - spacing * 2);
			//Rectangle outerRect(Rect.X - spacing, Rect.Y - spacing, Rect.Width + spacing * 2, Rect.Height + spacing * 2);
			bufferedGfx->Graphics->DrawArc(CircleNotePen, Rect, startAngle, arcLength);
			//bufferedGfx->Graphics->DrawArc(CircleNotePen, outerRect, startAngle, arcLength);
		}

		//Render
		bufferedGfx->Render(e->Graphics);
	}
	bool islistITREqualToViewITR(std::list<NotesNode>::iterator listITR) {
		if (listITR->beat != viewNotesITR->beat)
			return false;
		if (listITR->subBeat != viewNotesITR->subBeat)
			return false;
		if (listITR->noteType != viewNotesITR->noteType)
			return false;
		if (listITR->position != viewNotesITR->position)
			return false;
		if (listITR->size != viewNotesITR->size)
			return false;
		return true;
	}
	private: System::Void backgroundWorkerPaint_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
		//unused
		int j = 0;
		while (true) {
			backgroundWorkerPaint->ReportProgress(j);
			if (j == 1)
				j = 0;
			else
				j = 1;
			Thread::Sleep(50);
		}
	}
	private: System::Void backgroundWorkerPaint_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) {
		//unused
		if (!alreadyRefreshed && !noteRefresh) {
			CirclePanel->Refresh();
		}
		else {
			alreadyRefreshed = false;
		}
	}
	private: System::Void backgroundWorkerPaint_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
		//unused
	}
	private: System::Void VisualHispeed_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		RefreshPaint();
	}
	private: System::Void selectSongFile_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialogSong->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			songFilePath = SystemStringTostdString(openFileDialogSong->FileName);
		}
		if (songFilePath != "") {
			theChart.songFileName = songFilePath;
			songFileName->Text = stdStringToSystemString(songFilePath);
			currentlyPlayingSong = SoundEngine.Play2D(stdStringToSystemString(songFilePath), true, true);
			songTrackSlider->Value = 0;
			songTrackSlider->Maximum = currentlyPlayingSong->PlayLength;
			refreshMapOfTime();
		}
	}
	private: System::Void PlayButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (songFilePath != "" && currentlyPlayingSong != nullptr) {
			currentlyPlayingSong->PlayPosition = songTrackSlider->Value;
			currentlyPlayingSong->PlaybackSpeed = (float)PlaybackSpeedNum->Value;
			currentlyPlayingSong->Paused = !currentlyPlayingSong->Paused;
			if (currentlyPlayingSong->Paused) {
				PlayButton->Text = "Play (P)";
				if (backgroundWorkerSong->IsBusy) {
					backgroundWorkerSong->CancelAsync();
				}
				RefreshPaint();
			}
			else {
				PlayButton->Text = "Pause (P)";
				backgroundWorkerSong->RunWorkerAsync();
			}
		}
	}
	private: System::Void backgroundWorkerSong_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
		int i = 0;
		while (!currentlyPlayingSong->Paused) {
			backgroundWorkerSong->ReportProgress(i);
			i++;
			Thread::Sleep(update_interval);
		}
		backgroundWorkerSong->CancelAsync();
	}
	private: System::Void backgroundWorkerSong_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) {
		songTrackSlider->Value = currentlyPlayingSong->PlayPosition;
		refreshVisualFromSongScroll();
	}
	private: System::Void backgroundWorkerSong_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {

	}
	void refreshVisualFromSongScroll() {
		/*   trackBar Value = current time (milliseconds)
			find last millisecond start time which will tell you the "last measure start time"
			use last measure to find "milliseconds per measure" since then
			(current time - last measure start time) / (milliseconds per measure) = measures from last measure
			last measure start time + measures from last measure = current measure   */
		float currentTime = songTrackSlider->Value; //in milliseconds
		float currentMeasure = 0;
		float timeBetweenMeasures;
		if (mapOfBeatAtTime.find(currentTime) == mapOfBeatAtTime.end()) {
			std::map<float, float>::iterator itr = mapOfBeatAtTime.lower_bound(currentTime);
			float lastMeasure;
			if (itr != mapOfBeatAtTime.end()) {
				if (itr != mapOfBeatAtTime.begin()) {
					itr--;
				}
				if (itr->first < currentTime) {
					lastMeasure = itr->second; //find last millisecond start time which will tell you the "last measure start time"
				}
			}
			else {
				itr = mapOfBeatAtTime.end();
				if (!mapOfBeatAtTime.empty()) {
					itr--;
					lastMeasure = itr->second; //find last millisecond start time which will tell you the "last measure start time"
				}
			}
			timeBetweenMeasures = mapOfTimeBetweenMeasures[lastMeasure]; // use last measure to find "milliseconds per measure" since then
			float measuresFromLastMeasure = (currentTime - itr->first) / timeBetweenMeasures; //(current time - last measure start time) / (milliseconds per measure) = measures from last measure
			currentMeasure = lastMeasure + measuresFromLastMeasure; //last measure + measures from last measure = current measure
		}
		else {
			currentMeasure = mapOfBeatAtTime[currentTime];
		}

		noteRefresh = true;
		scrollBarChanged = true;
		theCurrentMeasure = currentMeasure;
		if (currentMeasure >= 0) {
			MeasureNum->Value = (Decimal)std::floor(currentMeasure);
			float currentSubMeasure = currentMeasure - std::floor(currentMeasure);
			BeatNum1->Value = (Decimal)(std::floor(currentSubMeasure * (float)BeatNum2->Value));
		}
		noteRefresh = false;
		RefreshPaint();
		scrollBarChanged = false;
		/*
		//Play note tick if a note is within range and song is playing
		bool playTickSoundBool = false;
		//Convert update_interval time to how many measures it takes up
		float updateIntToMeasure = ((float)update_interval / timeBetweenMeasures) * (float)PlaybackSpeedNum->Value;
		//Find notes near current time
		std::list<NotesNode> listOfNotesAtCurrentMeasure;
		if (mapOfNotes.find(currentMeasure) == mapOfNotes.end()) {
			std::map<float, std::list<NotesNode>>::iterator itr = mapOfNotes.lower_bound(currentMeasure);
			if (itr != mapOfNotes.end()) {
				if (itr != mapOfNotes.begin()) {
					itr--;
				}
				if (itr->first < currentMeasure) {
					listOfNotesAtCurrentMeasure = itr->second; //find last millisecond start time which will tell you the "last measure start time"
				}
			}
			else {
				itr = mapOfNotes.end();
				if (!mapOfNotes.empty()) {
					itr--;
					listOfNotesAtCurrentMeasure = itr->second; //find last millisecond start time which will tell you the "last measure start time"
				}
			}
		}
		else {
			listOfNotesAtCurrentMeasure = mapOfNotes[currentMeasure];
		}
		if (!listOfNotesAtCurrentMeasure.empty()) {
			float measureAtListTime = listOfNotesAtCurrentMeasure.begin()->beat + (listOfNotesAtCurrentMeasure.begin()->subBeat / 1920.f);
			if (measureAtListTime <= currentMeasure && measureAtListTime >= (currentMeasure - updateIntToMeasure)) {
				for (std::list<NotesNode>::iterator listofNotesitr = listOfNotesAtCurrentMeasure.begin(); listofNotesitr != listOfNotesAtCurrentMeasure.end(); listofNotesitr++) {
					switch (listofNotesitr->noteType) {
					case 10:
						break;
					case 11:
						break;
					case 12:
						break;
					case 13:
						break;
					default:
						playTickSoundBool = true;
					}
				}
			}
		}
		if (currentlyPlayingSong != nullptr) {
			if (currentlyPlayingSong->Paused == false && playTickSoundBool == true) {
				PlayTickSound();
			}
		}
		*/
	}
	private: System::Void songTrackSlider_Scroll(System::Object^ sender, System::EventArgs^ e) {
		if (currentlyPlayingSong != nullptr) {
			currentlyPlayingSong->PlayPosition = songTrackSlider->Value;
			refreshVisualFromSongScroll();
		}
	}
	private: System::Void SongVolume_Scroll(System::Object^ sender, System::EventArgs^ e) {
		if (currentlyPlayingSong != nullptr) {
			currentlyPlayingSong->Volume = SongVolume->Value / (float)100.0;
		}
	}
	private: System::Void TickVolume_Scroll(System::Object^ sender, System::EventArgs^ e) {
		/*
		if (currentlyPlayingTickSound != nullptr) {
			currentlyPlayingTickSound->Volume = TickVolume->Value / (float)100.0;
		}
		*/
	}
	void PlayTickSound() {
		/*
		currentlyPlayingTickSound = SoundEngine.Play2D(stdStringToSystemString(tickFilePath), false, true);
		if (currentlyPlayingTickSound != nullptr) {
			currentlyPlayingTickSound->Volume = TickVolume->Value / (float)100.0;
			currentlyPlayingTickSound->Paused = !currentlyPlayingTickSound->Paused;
		}
		*/
	}
	private: System::Void PlaybackSpeedNum_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (songFilePath != "" && currentlyPlayingSong != nullptr) {
			currentlyPlayingSong->PlaybackSpeed = (float)PlaybackSpeedNum->Value;
		}
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		//backgroundWorkerPaint->RunWorkerAsync();
		SetStyle(ControlStyles::OptimizedDoubleBuffer, true);
		SetStyle(ControlStyles::UserPaint, true);
		SetStyle(ControlStyles::AllPaintingInWmPaint, true);

		// Initialize BufferedGraphics
		bufferedGfxContext = BufferedGraphicsManager::Current;
		bufferedGfxContext->MaximumBuffer = Drawing::Size(CirclePanel->Width + 1, CirclePanel->Height + 1);
		bufferedGfx = bufferedGfxContext->Allocate(CirclePanel->CreateGraphics(),
			Drawing::Rectangle(0, 0, CirclePanel->Width, CirclePanel->Height));
		//DrawToGraphics(bufferedGfx->Graphics);
		RefreshPaint();

		// Force double buffering on CirlcePanel
		Type^ controlType = CirclePanel->GetType();
		PropertyInfo^ pi = controlType->GetProperty("DoubleBuffered", BindingFlags::Instance | BindingFlags::NonPublic);
		pi->SetValue(CirclePanel, true);

		// Add MouseWheel event to CirclePanel
		CirclePanel->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::CirclePanel_MouseWheel);
	}
	private: System::Void CirclePanel_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (Control::ModifierKeys == Keys::Alt) { 
			// Shift beat division by standard musical quantizations
			// TODO: take into account time signature?
			if (BeatNum2->Value < 2) {
				if (e->Delta > 0) {
					BeatNum2->Value = 2;
				}
				return;
			}
			else if (BeatNum2->Value == 2 && e->Delta < 0) {
				BeatNum2->Value = 1;
				return;
			}
			
			int low = 0;
			int high = 1;

			while (!(BeatNum2->Value >= (1 << low) && BeatNum2->Value <= (1 << high))) {
				low++;
				high++;
			}
			if (e->Delta < 0) {
				BeatNum2->Value = (1 << low);
			}
			else {
				if (high < 10) {
					BeatNum2->Value = (1 << (high + 1));
				}
			}
		}
		else if (Control::ModifierKeys == Keys::Shift) {

		}
		else if (Control::ModifierKeys == Keys::Control) {

		}
		else {
			// Scroll by one beat at a time
			if (e->Delta > 0) {
				BeatNum1->Value++;
			}
			else {
				BeatNum1->Value--;
			}
		}
	}
	private: System::Void MyForm_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		wchar_t keyPressed = std::toupper(e->KeyChar);
		switch (keyPressed) {
		case 'T': //Touch
			TapButton_Click(sender, e);
			TapButton->Focus();
			e->Handled = true;
			break;
		case 'O': //Orange Slide
			OrangeButton_Click(sender, e);
			OrangeButton->Focus();
			e->Handled = true;
			break;
		case 'G': //Green Slide
			GreenButton_Click(sender, e);
			GreenButton->Focus();
			e->Handled = true;
			break;
		case 'R': //Red Snap
			RedButton_Click(sender, e);
			RedButton->Focus();
			e->Handled = true;
			break;
		case 'B': //Blue Snap
			BlueButton_Click(sender, e);
			BlueButton->Focus();
			e->Handled = true;
			break;
		case 'Y': //Chain
			YellowButton_Click(sender, e);
			YellowButton->Focus();
			e->Handled = true;
			break;
		case 'H': //Hold
			HoldButton_Click(sender, e);
			HoldButton->Focus();
			e->Handled = true;
			break;
		case 'M': //Mask
			MaskButton_Click(sender, e);
			MaskButton->Focus();
			e->Handled = true;
			break;
		case 'I': //Insert
			InsertButton_Click(sender, e);
			InsertButton->Focus();
			e->Handled = true;
			break;
		case 'P': //Play/Pause
			PlayButton_Click(sender, e);
			PlayButton->Focus();
			e->Handled = true;
			break;
		}
	}
	private: System::Void highlightViewedNoteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		RefreshPaint();
	}
	/*
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		DrawToGraphics(bufferedGfx->Graphics);
	}
	*/
private: System::Void showCursorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	RefreshPaint();
}
private: System::Void CirclePanel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	// Determine location of mouse click in the circle
	// X and Y are relative to upper left of image
	float xCen = e->X - (CirclePanel->Width / 2);
	float yCen = -(e->Y - (CirclePanel->Height / 2));
	float theta = Math::Atan2(yCen, xCen) * 180.0f / PI;
	if (theta < 0)
		theta += 360.0f;
	// Left click moves the cursor
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		PosNum->Value = (int)(theta / 6.0f);
		mouseDownPos = (int)PosNum->Value;
		lastMousePos = -1;
		rolloverPos = false;
		rolloverNeg = false;
	}
}
private: System::Void CirclePanel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	// Only Left Click should create notes
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		mouseDownPos = -1;
		InsertObject();
	}
}
private: System::Void CirclePanel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	// Calculate angle
	float xCen = e->X - (CirclePanel->Width / 2);
	float yCen = -(e->Y - (CirclePanel->Height / 2));
	float thetaCalc = Math::Atan2(yCen, xCen) * 180.0f / PI;
	if (thetaCalc < 0)
		thetaCalc += 360.0f;
	int theta = thetaCalc / 6.0f;
	// Left click will alter the note width and possibly the position depending on which direction is being turned
	if (e->Button == System::Windows::Forms::MouseButtons::Left && mouseDownPos != -1) {
		int delta = theta - lastMousePos;
		// Handle rollover
		if (delta == -59) {
			if (rolloverNeg) {
				rolloverNeg = false;
			}
			else {
				rolloverPos = true;
			}
		}
		else if (delta == 59) {
			if (rolloverPos) {
				rolloverPos = false;
			}
			else {
				rolloverNeg = true;
			}
		}
		if (theta == mouseDownPos) {
			PosNum->Value = mouseDownPos;
			SizeNum->Value = 1;
		}
		else if ((theta > mouseDownPos || rolloverPos) && !rolloverNeg) {
			PosNum->Value = mouseDownPos;
			if (rolloverPos) {
				
				SizeNum->Value = Math::Min(theta + 60 - mouseDownPos + 1, 60);
			}
			else {
				SizeNum->Value = theta - mouseDownPos + 1;
			}
		}
		else if (theta < mouseDownPos || rolloverNeg) {
			if (rolloverNeg) {
				PosNum->Value = theta;
				SizeNum->Value = Math::Min(mouseDownPos + 60 - theta + 1, 60);
			}
			else {
				PosNum->Value = theta;
				SizeNum->Value = mouseDownPos - theta + 1;
			}
		}
		lastMousePos = theta;
	}
}
private: System::Void aboutBAKKAEditorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show(this->Text + "\n\nCredits:\nGoatgarien - Initial editor and idea\nZoids - Various fixes\nYellowberry - UI redesign", "About BAKKA Editor");
}
};
}
