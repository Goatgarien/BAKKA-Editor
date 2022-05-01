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
	HoldMiddle = 10,
	HoldEnd = 11,
	MaskAdd = 12,
	MaskRemove = 13,
	EndOfChart = 14,
	Chain = 16,
	TouchBonusFlair = 20,
	SnapRedBonusFlair = 21,
	SnapBlueBonusFlair = 22,
	SlideOrangeBonusFlair = 23,
	SlideGreenBonusFlair = 24,
	HoldStartBonusFlair = 25,
	ChainBonusFlair = 26,
};

struct NotesNode {
	int beat;
	int subBeat;
	NoteType noteType;
	int position;
	int size;
	int holdChange;
	int BGType;
	std::list<NotesNode>::iterator nextNode;
	std::list<NotesNode>::iterator prevNode;
};

struct PreChartNode {
	int beat;
	int subBeat;
	int type;
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