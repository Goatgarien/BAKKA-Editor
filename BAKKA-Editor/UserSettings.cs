using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor
{

        internal class UserSettings
        {
                public ViewSettings ViewSettings { get; set; } = new();
                public SaveSettings SaveSettings { get; set; } = new();
                public HotkeySettings HotkeySettings { get; set; } = new();
        }

        internal class ViewSettings
        {
                public bool ShowCursor { get; set; } = true;
                public bool ShowCursorDuringPlayback { get; set; } = false;
                public bool HighlightViewedNote { get; set; } = true;
                public bool SelectLastInsertedNote { get; set; } = true;
                public bool ShowGimmicks { get; set; } = true;
                public float HispeedSetting { get; set; } = 1.5f;
                public int Volume { get; set; } = 100;
        }

        internal class SaveSettings
        {
                /// <summary>
                /// How frequently autosave occurs (in minutes)
                /// </summary>
                public int AutoSaveInterval { get; set; } = 1;
        }

        internal class HotkeySettings
        {
                private static readonly CultureInfo _defaultParsingCulture = CultureInfo.InvariantCulture;
                public int TouchHotkey { get; set; } = Convert.ToInt32(Keys.D1, _defaultParsingCulture);
                public int SlideLeftHotkey { get; set; } = Convert.ToInt32(Keys.D2, _defaultParsingCulture);
                public int SlideRightHotkey { get; set; } = Convert.ToInt32(Keys.D3, _defaultParsingCulture);
                public int SnapUpHotkey { get; set; } = Convert.ToInt32(Keys.D4, _defaultParsingCulture);
                public int SnapDownHotkey { get; set; } = Convert.ToInt32(Keys.D5, _defaultParsingCulture);
                public int ChainHotkey { get; set; } = Convert.ToInt32(Keys.D6, _defaultParsingCulture);
                public int HoldHotkey { get; set; } = Convert.ToInt32(Keys.D7, _defaultParsingCulture);
                public int PlayHotkey { get; set; } = Convert.ToInt32(Keys.Space, _defaultParsingCulture);
        }
}
