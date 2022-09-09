using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor
{
    internal class BeatInfo
    {
        public int Measure;
        public int Beat;

        public BeatInfo(int measure, int beat)
        {
            Measure = measure;
            Beat = beat;
        }

        public BeatInfo(float measure)
        {
            Measure = (int)Math.Floor(measure);
            Beat = (int)((measure - (float)Measure) * 1920.0f);
        }

        public BeatInfo(BeatInfo info)
        {
            Measure = info.Measure;
            Beat = info.Beat;
        }

        public float MeasureDecimal { get { return (float)Measure + (float)Beat / 1920.0f; } }
    }

    internal class TimeSignature
    {
        public int Upper;
        public int Lower;

        public double Ratio { get { return (double)Upper / (double)Lower; } }

        public TimeSignature()
        {
            Upper = 4;
            Lower = 4;
        }

        public TimeSignature(TimeSignature sig)
        {
            Upper = sig.Upper;
            Lower = sig.Lower;
        }
    }

    internal class NoteBase
    {
        public BeatInfo BeatInfo { get; set; } = new BeatInfo(-1, 0);
        public GimmickType GimmickType { get; set; } = GimmickType.NoGimmick;

        public float Measure { get { return BeatInfo.MeasureDecimal; } }
    }

    internal class Note : NoteBase
    {
        public NoteType NoteType { get; set; } = NoteType.TouchNoBonus;
        public int Position { get; set; }
        public int Size { get; set; }
        [System.ComponentModel.Browsable(false)]
        public bool HoldChange { get; set; }
        [System.ComponentModel.Browsable(false)]
        public MaskType MaskFill { get; set; }
        [System.ComponentModel.Browsable(false)]
        public Note NextNote { get; set; }
        [System.ComponentModel.Browsable(false)]
        public Note PrevNote { get; set; }

        [System.ComponentModel.Browsable(false)]
        public bool IsHold
        {
            get
            {
                switch (NoteType)
                {
                    case NoteType.HoldStartNoBonus:
                    case NoteType.HoldJoint:
                    case NoteType.HoldEnd:
                    case NoteType.HoldStartBonusFlair:
                        return true;
                    default:
                        return false;
                }
            }
        }
        [System.ComponentModel.Browsable(false)]
        public bool IsMask
        {
            get
            {
                switch (NoteType)
                {
                    case NoteType.MaskAdd:
                    case NoteType.MaskRemove:
                        return true;
                    default:
                        return false;
                }
            }
        }
        [System.ComponentModel.Browsable(false)]
        public bool IsBonus
        {
            get
            {
                switch (NoteType)
                {
                    case NoteType.TouchBonus:
                    case NoteType.SlideOrangeBonus:
                    case NoteType.SlideGreenBonus:
                        return true;
                    default:
                        return false; ;
                }
            }
        }
        [System.ComponentModel.Browsable(false)]
        public bool IsFlair
        {
            get
            {
                switch (NoteType)
                {
                    case NoteType.TouchBonusFlair:
                    case NoteType.SnapRedBonusFlair:
                    case NoteType.SnapBlueBonusFlair:
                    case NoteType.SlideOrangeBonusFlair:
                    case NoteType.SlideGreenBonusFlair:
                    case NoteType.HoldStartBonusFlair:
                    case NoteType.ChainBonusFlair:
                        return true;
                    default:
                        return false;
                }
            }
        }
        [System.ComponentModel.Browsable(false)]
        public Color Color
        {
            get
            {
                return Utils.NoteTypeToColor(NoteType);
            }
        }

        public Note() { }
        public Note(BeatInfo info)
        {
            BeatInfo = info;
            GimmickType = GimmickType.NoGimmick;
        }

        public Note(Note baseNote) : this(baseNote.BeatInfo)
        {
            Position = baseNote.Position;
            Size = baseNote.Size;
            NoteType = baseNote.NoteType;
        }
    }

    internal class Gimmick : NoteBase
    {
        public double BPM { get; set; }
        public TimeSignature TimeSig { get; set; } = new();
        public double HiSpeed { get; set; }
        public double StartTime { get; set; }

        public bool IsReverse
        {
            get
            {
                switch (GimmickType)
                {
                    case GimmickType.ReverseStart:
                    case GimmickType.ReverseMiddle:
                    case GimmickType.ReverseEnd:
                        return true;
                    default:
                        return false;
                }
            }
        }

        public bool IsStop
        {
            get
            {
                switch (GimmickType)
                {
                    case GimmickType.StopStart:
                    case GimmickType.StopEnd:
                        return true;
                    default:
                        return false;
                }
            }
        }

        public Gimmick() { }
        public Gimmick(BeatInfo info, GimmickType type)
        {
            BeatInfo = info;
            GimmickType = type;
        }
        public Gimmick(Gimmick baseGimmick) : this(baseGimmick.BeatInfo, baseGimmick.GimmickType)
        {
            switch (GimmickType)
            {
                case GimmickType.BpmChange:
                    HiSpeed = baseGimmick.HiSpeed;
                    break;
                case GimmickType.TimeSignatureChange:
                    TimeSig = new TimeSignature(baseGimmick.TimeSig);
                    break;
                case GimmickType.HiSpeedChange:
                    HiSpeed = baseGimmick.HiSpeed;
                    break;
            }
        }
    }
}
