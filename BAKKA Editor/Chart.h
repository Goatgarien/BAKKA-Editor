#pragma once
#include <iostream>
#include <iterator>
#include <list>

enum NoteType {
	TouchNoBonus = 1,
	TouchBonus = 2,
	SnapRedNoBonus = 3,
	SnapBlueNoBonus = 4,
	SlideOrangeNoBonus = 5,
	SlideOrangeBonus = 6,
	SlideGreenNoBonus = 7,
	SlideGreenBonus = 8,
	HoldStartNoBonus = 9,
	HoldJoint = 10,
	HoldEnd = 11,
	MaskAdd = 12,
	MaskRemove = 13,
	EndOfChart = 14,
	//MaskSameTime = 15,
	Chain = 16,
	//MaskLane = 17,
	//TutorialTag = 18,
	//BarLine = 19,
	TouchBonusFlair = 20,
	SnapRedBonusFlair = 21,
	SnapBlueBonusFlair = 22,
	SlideOrangeBonusFlair = 23,
	SlideGreenBonusFlair = 24,
	HoldStartBonusFlair = 25,
	ChainBonusFlair = 26,
};

struct NotesNode {
	int measure;
	int beat;
	NoteType noteType;
	int position;
	int size;
	int holdChange;
	int BGType;
	std::list<NotesNode>::iterator nextNode;
	std::list<NotesNode>::iterator prevNode;
};

enum GimmickType {
	NoGimmick = 1,
	BpmChange = 2,
	TimeSignatureChange = 3,
	HiSpeedChange = 5,
	ReverseStart = 6,
	ReverseMiddle = 7,
	ReverseEnd = 8,
	StopStart = 9,
	StopEnd = 10,
};

struct PreChartNode {
	int measure;
	int beat;
	GimmickType type;
	double BPM;		//2
	int beatDiv1;	//3
	int beatDiv2;	//3
	double hiSpeed; //5
	//6-10 have no extra info
};

struct Chart {
	std::list<NotesNode> Notes;
	std::list<PreChartNode> PreChart;
	double offset;
	double movieOffset;
	std::string songFileName;
};