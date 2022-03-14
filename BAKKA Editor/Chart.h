#pragma once
#include <iostream>
#include <iterator>
#include <list>

struct NotesNode {
	int beat;
	int subBeat;
	int noteType;
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
};