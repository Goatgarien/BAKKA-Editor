using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor
{
	internal enum NoteType
	{
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
		// MaskSameTime = 15,
		Chain = 16,
		// MaskLane = 17,
		// TutorialTag = 18,
		// BarLine = 19,
		TouchBonusFlair = 20,
		SnapRedBonusFlair = 21,
		SnapBlueBonusFlair = 22,
		SlideOrangeBonusFlair = 23,
		SlideGreenBonusFlair = 24,
		HoldStartBonusFlair = 25,
		ChainBonusFlair = 26,
	}

	internal enum GimmickType
	{
		NoGimmick = 1,
		BpmChange = 2,
		TimeSignatureChange = 3,
		// Stop = 4,
		HiSpeedChange = 5,
		ReverseStart = 6,
		ReverseMiddle = 7,
		ReverseEnd = 8,
		StopStart = 9,
		StopEnd = 10,
	};

	internal enum MaskType
    {
		Clockwise = 0,
		CounterClockwise = 1,
		Center = 2
    }

	internal enum BonusType
    {
		NoBonus = 0,
		Bonus = 1,
		Flair = 2
    }
}
