using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor
{
    internal static class Utils
    {
        internal static string? GetTag(string input, string tag)
        {
            if(input.Contains(tag))
            {
                return input.Substring(input.IndexOf(tag) + tag.Length);
            }

            return null;
        }

        internal static double DegToRad(double deg)
        {
            return deg * Math.PI / 180.0f;
        }

        internal static Color NoteTypeToColor(NoteType type)
        {
            switch (type)
            {
                case NoteType.TouchNoBonus:
                case NoteType.TouchBonus:
                case NoteType.TouchBonusFlair:
                    return Color.Fuchsia;
                case NoteType.SnapRedNoBonus:
                case NoteType.SnapRedBonusFlair:
                    return Color.Red;
                case NoteType.SnapBlueNoBonus:
                case NoteType.SnapBlueBonusFlair:
                    return Color.Aqua;
                case NoteType.SlideOrangeNoBonus:
                case NoteType.SlideOrangeBonus:
                case NoteType.SlideOrangeBonusFlair:
                    return Color.FromArgb(255, 128, 0);
                case NoteType.SlideGreenNoBonus:
                case NoteType.SlideGreenBonus:
                case NoteType.SlideGreenBonusFlair:
                    return Color.LimeGreen;
                case NoteType.HoldStartNoBonus:
                case NoteType.HoldJoint:
                case NoteType.HoldEnd:
                case NoteType.HoldStartBonusFlair:
                    return Color.Yellow;
                case NoteType.Chain:
                case NoteType.ChainBonusFlair:
                    return Color.FromArgb(204, 190, 45);
                default:
                    return Color.Transparent;
            }
        }

        internal static void InvokeIfRequired(this Control control, MethodInvoker action)
        {
            if (control.InvokeRequired)
            {
                control.Invoke(action);
            }
            else
            {
                action();
            }
        }

        internal static Rectangle ToInt(this RectangleF rect)
        {
            return new Rectangle((int)rect.X, (int)rect.Y, (int)rect.Width, (int)rect.Height);
        }

        internal static int FindGCD(int a, int b)
        {
            if (b == 0)
                return a;
            return FindGCD(b, a & b);
        }

        internal static string ToLabel(this NoteType type)
        {
            switch (type)
            {
                case NoteType.TouchNoBonus:
                    return "Touch";
                case NoteType.TouchBonus:
                    return "Touch [Bonus]";
                case NoteType.SnapRedNoBonus:
                    return "Snap (R)";
                case NoteType.SnapBlueNoBonus:
                    return "Snap (B)";
                case NoteType.SlideOrangeNoBonus:
                    return "Slide (O)";
                case NoteType.SlideOrangeBonus:
                    return "Slide (O) [Bonus]";
                case NoteType.SlideGreenNoBonus:
                    return "Slide (G)";
                case NoteType.SlideGreenBonus:
                    return "Slide (G) [Bonus]";
                case NoteType.HoldStartNoBonus:
                    return "Hold Start";
                case NoteType.HoldJoint:
                    return "Hold Joint";
                case NoteType.HoldEnd:
                    return "Hold End";
                case NoteType.MaskAdd:
                    return "Mask Add";
                case NoteType.MaskRemove:
                    return "Mask Remove";
                case NoteType.EndOfChart:
                    return "End of Chart";
                case NoteType.Chain:
                    return "Chain";
                case NoteType.TouchBonusFlair:
                    return "Touch [R Note]";
                case NoteType.SnapRedBonusFlair:
                    return "Snap (R) [R Note]";
                case NoteType.SnapBlueBonusFlair:
                    return "Snap (B) [R Note]";
                case NoteType.SlideOrangeBonusFlair:
                    return "Slide (O) [R Note]";
                case NoteType.SlideGreenBonusFlair:
                    return "Slide (G) [R Note]";
                case NoteType.HoldStartBonusFlair:
                    return "Hold Start [R Note]";
                case NoteType.ChainBonusFlair:
                    return "Chain [R Note]";
                default:
                    return "Undefined Note Type";
            }
        }

        internal static string ToLabel(this GimmickType type)
        {
            switch (type)
            {
                case GimmickType.BpmChange:
                    return "BPM Change";
                case GimmickType.TimeSignatureChange:
                    return "Time Signature Change";
                case GimmickType.HiSpeedChange:
                    return "Hi-Speed Change";
                case GimmickType.ReverseStart:
                    return "Reverse Start";
                case GimmickType.ReverseMiddle:
                    return "Reverse Middle";
                case GimmickType.ReverseEnd:
                    return "Reverse Stop";
                case GimmickType.StopStart:
                    return "Stop Start";
                case GimmickType.StopEnd:
                    return "Stop End";
                default:
                    return "Undefined Gimmick";
            }
        }

        internal static bool HasDecimal(double num)
        {
            return Math.Ceiling(num) == Math.Floor(num);
        }

        internal static Tuple<int, int> GetQuantization(int val, int min)
        {
            while (!HasDecimal((double)(val * min) / 1920.0))
            {
                min *= 2;
            }
            return new Tuple<int, int>((int)(val * min / 1920.0), min);
        }

        internal static float GetDist(Point a, Point b)
        {
            return (float)Math.Sqrt(Math.Pow(a.X - b.X, 2) + Math.Pow(a.Y - b.Y, 2));
        }
    }
}
