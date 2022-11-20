using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace BAKKA_Editor
{
    internal static class PlotBrush
    {
        public static SolidBrush HoldBrush { get; } = new SolidBrush(Color.FromArgb(170, Color.Yellow));
        public static SolidBrush MaskBrush { get; set; } = new SolidBrush(Color.DimGray);
    }
}
