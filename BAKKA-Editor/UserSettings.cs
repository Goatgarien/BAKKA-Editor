using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor
{
    internal class UserSettings
    {
        public ViewSettings ViewSettings { get; set; } = new();
        public SaveSettings SaveSettings { get; set; } = new();
    }

    internal class ViewSettings
    {
        public bool ShowCursor { get; set; } = true;
        public bool ShowCursorDuringPlayback { get; set; } = false;
        public bool HighlightViewedNote { get; set; } = true;
    }

    internal class SaveSettings
    {
        /// <summary>
        /// How frequently autosave occurs (in minutes)
        /// </summary>
        public int AutoSaveInterval { get; set; } = 1;
    }
}
