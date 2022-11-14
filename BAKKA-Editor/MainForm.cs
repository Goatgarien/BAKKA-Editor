using System.Drawing.Drawing2D;
using System.Reflection;
using IrrKlang;
using BAKKA_Editor.Operations;
using Tomlyn;

namespace BAKKA_Editor
{
    public partial class MainForm : Form
    {
        // Chart
        Chart chart = new();
        string songFilePath = "";
        bool isNewFile = true;
        bool isRecoveredFile = false;

        // Operations
        OperationManager opManager = new OperationManager();

        // Playfield
        CircleView circleView = new CircleView(new SizeF(611, 611));

        // Note Selection
        NoteType currentNoteType = NoteType.TouchNoBonus;
        GimmickType currentGimmickType = GimmickType.NoGimmick;
        BonusType currentBonusType = BonusType.NoBonus;
        int selectedGimmickIndex = -1;
        int selectedNoteIndex = -1;
        Note lastNote;

        // Music
        ISoundEngine soundEngine = new ISoundEngine();
        ISound currentSong;

        // Control updates
        enum EventSource
        {
            None,
            MouseWheel,
            SongPlaying,
            TrackBar
        };
        EventSource valueTriggerEvent = EventSource.None;

        // Tool Forms
        GimmickForm gimmickForm;
        InitChartSettingsForm initSettingsForm;

        // Program info
        string fileVersion = "";
        UserSettings userSettings;
        string tempFilePath = "";
        string tempStatusPath = "";
        string autosaveFile = "";

        public MainForm()
        {
            InitializeComponent();

            // Extra Forms stuff
            circlePanel.MouseWheel += circlePanel_MouseWheel;

            // Setup graphics
            MainForm_Resize(this, new EventArgs());

            // Force double buffering on circlePanel
            Type controlType = circlePanel.GetType();
            PropertyInfo pi = controlType.GetProperty("DoubleBuffered", BindingFlags.Instance | BindingFlags.NonPublic);
            pi.SetValue(circlePanel, true);

            // Tool Forms
            gimmickForm = new GimmickForm();
            initSettingsForm = new InitChartSettingsForm();

            //Set Initial Song File :)
            SetInitialSong();

            // Operation Manager
            opManager.OperationHistoryChanged += (s, e) =>
            {
                chart.Notes = chart.Notes.OrderBy(x => x.Measure).ToList();
                chart.Gimmicks = chart.Gimmicks.OrderBy(x => x.Measure).ToList();
                if (selectedNoteIndex >= chart.Notes.Count)
                    selectedNoteIndex = chart.Notes.Count - 1;
                else if (selectedNoteIndex == -1 && chart.Notes.Count > 0)
                    selectedNoteIndex = 0;
                UpdateNoteLabels();
                if (selectedGimmickIndex >= chart.Gimmicks.Count)
                    selectedGimmickIndex = chart.Gimmicks.Count - 1;
                else if (selectedGimmickIndex == -1 && chart.Gimmicks.Count > 0)
                    selectedGimmickIndex = 0;
                UpdateGimmickLabels();
                SetText();
                circlePanel.Invalidate();
            };

            // Program info
            var asm = Assembly.GetExecutingAssembly();
            var fvi = System.Diagnostics.FileVersionInfo.GetVersionInfo(asm.Location);
            if (fvi.FileVersion != null)
            {
                fileVersion = fvi.FileVersion;
                SetText();
            }

            // Look for user settings
            if (File.Exists("settings.toml"))
                userSettings = Toml.ToModel<UserSettings>(File.ReadAllText("settings.toml"));
            else
            {
                userSettings = new UserSettings();
                File.WriteAllText("settings.toml", Toml.FromModel(userSettings));
            }
            // Apply settings
            showCursorToolStripMenuItem.Checked = userSettings.ViewSettings.ShowCursor;
            showCursorDuringPlaybackToolStripMenuItem.Checked = userSettings.ViewSettings.ShowCursorDuringPlayback;
            highlightViewedNoteToolStripMenuItem.Checked = userSettings.ViewSettings.HighlightViewedNote;
            autoSaveTimer.Interval = userSettings.SaveSettings.AutoSaveInterval * 60000;
            autoSaveTimer.Enabled = true;
            // Update hotkey labels
            tapButton.AppendHotkey(userSettings.HotkeySettings.TouchHotkey);
            orangeButton.AppendHotkey(userSettings.HotkeySettings.SlideLeftHotkey);
            greenButton.AppendHotkey(userSettings.HotkeySettings.SlideRightHotkey);
            redButton.AppendHotkey(userSettings.HotkeySettings.SnapUpHotkey);
            blueButton.AppendHotkey(userSettings.HotkeySettings.SnapDownHotkey);
            chainButton.AppendHotkey(userSettings.HotkeySettings.ChainHotkey);
            holdButton.AppendHotkey(userSettings.HotkeySettings.HoldHotkey);
            playButton.AppendHotkey(userSettings.HotkeySettings.PlayHotkey);

            // Look for temp files from previous runs
            var tempFile = Directory.GetFiles(Path.GetTempPath(), "*.bakka");
            var oldAutosave = Directory.GetFiles(Path.GetTempPath(), "*.mer");
            if (tempFile.Length > 0)
            {
                tempStatusPath = tempFile[0];
                var statusLines = File.ReadAllLines(tempStatusPath);
                if (statusLines.Length > 0)
                {
                    bool checkAutosave = false;
                    bool.TryParse(statusLines[0], out checkAutosave);
                    if (checkAutosave)
                    {
                        string autosaveTime = ".";
                        if (statusLines.Length > 1)
                            autosaveTime = " from " + statusLines[1] + ".";
                        if (oldAutosave.Length > 0)
                        {
                            autosaveFile = oldAutosave[0];
                            var result = MessageBox.Show($"Auto-save data found{autosaveTime}\n\nLoad?", "Load Auto-Save Data?", MessageBoxButtons.YesNo);
                            if (result == DialogResult.Yes)
                            {
                                openFileDialog.FileName = autosaveFile;
                                isRecoveredFile = true;
                                OpenFile();
                            }
                        }
                    }
                    if (!isRecoveredFile)
                    {
                        DeleteAutosaves();
                    }
                }
            }
            else
            {
                tempStatusPath = Path.GetTempFileName().Replace(".tmp", ".bakka");
                File.WriteAllText(tempStatusPath, "false");
            }
        }

        private void SetText()
        {
            string save = chart.IsSaved ? "" : "*";
            string name = isRecoveredFile ? "Auto-Save Recover" : (isNewFile ? "New File" : saveFileDialog.FileName);
            Text = $"{save}BAKKA Editor {fileVersion} - [{name}]";
        }

        /// <summary>
        /// Prompts for a save if the chart is not currently saved.
        /// </summary>
        /// <returns>TRUE if the calling method should continue, or FALSE if the calling method should return</returns>
        private bool PromptSave()
        {
            var result = chart.IsSaved
                ? DialogResult.No
                : MessageBox.Show("Current chart is unsaved. Do you wish to save your changes?", "Save Changes", MessageBoxButtons.YesNoCancel);

            switch (result)
            {
                case DialogResult.Cancel:
                    return false;
                case DialogResult.Yes:
                    if (SaveFile() == DialogResult.Cancel)
                        return false;
                    break;
            }
            return true;
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!PromptSave())
                return;

            chart = new();
            isNewFile = true;
            isRecoveredFile = false;
            ResetChartTime();
            DeleteAutosaves();
            UpdateNoteLabels(-1);
            UpdateGimmickLabels(-1);
            SetText();
            opManager.Clear();
            circlePanel.Invalidate();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!PromptSave())
                return;

            if (openFileDialog.ShowDialog() == DialogResult.Cancel)
                return;

            if (openFileDialog.FileName == "")
            {
                MessageBox.Show("No file selected.");
                return;
            }

            OpenFile();
        }

        private void OpenFile()
        {
            chart = new();
            if (!chart.ParseFile(openFileDialog.FileName))
            {
                MessageBox.Show("Failed to parse file. Ensure it is not corrupted.");
                chart = new();
            }
            else
            {
                // Successful parse
                var initGimmicks = chart.Gimmicks.Where(x => x.StartTime == 0);
                var initBpm = initGimmicks.FirstOrDefault(x => x.GimmickType == GimmickType.BpmChange);
                double bpm = initBpm != null ? initBpm.BPM : 120.0;
                var initTimeSig = initGimmicks.FirstOrDefault(x => x.GimmickType == GimmickType.TimeSignatureChange);
                int timeSigUpper = initTimeSig != null ? initTimeSig.TimeSig.Upper : 4;
                int timeSigLower = initTimeSig != null ? initTimeSig.TimeSig.Lower : 4;
                initSettingsForm.SetValues(bpm, timeSigUpper, timeSigLower, chart.Offset, chart.MovieOffset);
                ResetChartTime();
                UpdateNoteLabels(chart.Notes.Count > 0 ? 0 : -1);
                UpdateGimmickLabels(chart.Gimmicks.Count > 0 ? 0 : -1);
                saveFileDialog.FileName = openFileDialog.FileName;
                chart.IsSaved = true;
                isNewFile = false;
                SetText();
            }
            circlePanel.Invalidate();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFile(isNewFile || isRecoveredFile);
        }

        private DialogResult SaveFile(bool prompt = true)
        {
            var result = prompt ? saveFileDialog.ShowDialog() : DialogResult.OK;

            if (result == DialogResult.OK)
            {
                chart.WriteFile(saveFileDialog.FileName);
                isNewFile = false;
                if (isRecoveredFile)
                {
                    DeleteAutosaves();
                    autosaveFile = "";
                }
                isRecoveredFile = false;
                File.WriteAllText(tempStatusPath, "false");
                SetText();
            }
            return result;
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFile(true);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!PromptSave())
                return;

            Application.Exit();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            var result = chart.IsSaved
                ? DialogResult.No
                : MessageBox.Show("Current chart is unsaved. Do you wish to save your changes?", "Save Changes", MessageBoxButtons.YesNoCancel);

            switch (result)
            {
                case DialogResult.Cancel:
                    e.Cancel = true;
                    return;
                case DialogResult.Yes:
                    if (SaveFile() == DialogResult.Cancel)
                    {
                        e.Cancel = true;
                        return;
                    }
                    break;
                case DialogResult.No:
                    break;
                default:
                    break;
            }
            if (tempStatusPath != "")
                File.Delete(tempStatusPath);
            if (tempFilePath != "")
                File.Delete(tempFilePath);
        }

        private void SetSelectedObject(NoteType type)
        {
            currentNoteType = type;
            switch (type)
            {
                case NoteType.TouchNoBonus:
                    updateLabel("Touch");
                    break;
                case NoteType.TouchBonus:
                    updateLabel("Touch [Bonus]");
                    break;
                case NoteType.SnapRedNoBonus:
                    updateLabel("Snap (R)");
                    break;
                case NoteType.SnapBlueNoBonus:
                    updateLabel("Snap (B)");
                    break;
                case NoteType.SlideOrangeNoBonus:
                    updateLabel("Slide (O)");
                    break;
                case NoteType.SlideOrangeBonus:
                    updateLabel("Slide (O) [Bonus]");
                    break;
                case NoteType.SlideGreenNoBonus:
                    updateLabel("Slide (G)");
                    break;
                case NoteType.SlideGreenBonus:
                    updateLabel("Slide (G) [Bonus]");
                    break;
                case NoteType.HoldStartNoBonus:
                    updateLabel("Hold Start");
                    break;
                case NoteType.HoldJoint:
                    if (endHoldCheck.Checked)
                    {
                        updateLabel("Hold End");
                        currentNoteType = NoteType.HoldEnd;
                    }
                    else
                        updateLabel("Hold Middle");
                    break;
                case NoteType.HoldEnd:
                    updateLabel("Hold End");
                    break;
                case NoteType.MaskAdd:
                    if (clockwiseMaskRadio.Checked)
                        updateLabel("Mask Add (Clockwise)");
                    else if (cClockwiseMaskRadio.Checked)
                        updateLabel("Mask Add (Counter-Clockwise)");
                    else
                        updateLabel("Mask Add (From Center)");
                    break;
                case NoteType.MaskRemove:
                    if (clockwiseMaskRadio.Checked)
                        updateLabel("Mask Remove (Clockwise)");
                    else if (cClockwiseMaskRadio.Checked)
                        updateLabel("Mask Remove (Counter-Clockwise)");
                    else
                        updateLabel("Mask Remove (From Center)");
                    break;
                case NoteType.EndOfChart:
                    updateLabel("End of Chart");
                    break;
                case NoteType.Chain:
                    updateLabel("Chain");
                    break;
                case NoteType.TouchBonusFlair:
                    updateLabel("Touch [R Note]");
                    break;
                case NoteType.SnapRedBonusFlair:
                    updateLabel("Snap (R) [R Note]");
                    break;
                case NoteType.SnapBlueBonusFlair:
                    updateLabel("Snap (B) [R Note]");
                    break;
                case NoteType.SlideOrangeBonusFlair:
                    updateLabel("Slide (O) [R Note]");
                    break;
                case NoteType.SlideGreenBonusFlair:
                    updateLabel("Slide (G) [R Note]");
                    break;
                case NoteType.HoldStartBonusFlair:
                    updateLabel("Hold Start [R Note]");
                    break;
                case NoteType.ChainBonusFlair:
                    updateLabel("Chain [R Note]");
                    break;
                default:
                    updateLabel("None Selected");
                    break;
            }
            circlePanel.Invalidate();
        }

        private void SetSelectedObject(GimmickType gimmick)
        {
            currentGimmickType = gimmick;
            updateLabel(gimmick.ToLabel());
        }

        void updateLabel(string text)
        {
            currentSelectionLabel.InvokeIfRequired(() => { currentSelectionLabel.Text = text; });
        }

        private void touchToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetSelectedObject(NoteType.TouchNoBonus);
        }

        private void touchBonusToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetSelectedObject(NoteType.TouchBonus);
        }

        private void touchFlairToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetSelectedObject(NoteType.TouchBonusFlair);
        }

        private void circlePanel_MouseWheel(object? sender, MouseEventArgs e)
        {
            if (Control.ModifierKeys == Keys.Alt)
            {
                // Shift beat division by standard musical quantization
                // TODO: Take time signature into account?
                if (beat2Numeric.Value < 2)
                {
                    if (e.Delta > 0)
                        beat2Numeric.Value = 2;
                    return;
                }
                else if (beat2Numeric.Value == 2 && e.Delta < 0)
                {
                    beat2Numeric.Value = 1;
                    return;
                }
                int low = 0;
                int high = 1;
                while (!(beat2Numeric.Value >= (1 << low) && beat2Numeric.Value <= (1 << high)))
                {
                    low++;
                    high++;
                }
                if (e.Delta < 0)
                    beat2Numeric.Value = (1 << low);
                else
                {
                    if (high < 10)
                        beat2Numeric.Value = (1 << (high + 1));
                }
            }
            else if (Control.ModifierKeys == Keys.Shift)
            {

            }
            else if (Control.ModifierKeys == Keys.Control)
            {

            }
            else
            {
                valueTriggerEvent = EventSource.MouseWheel;
                if (e.Delta > 0)
                    beat1Numeric.Value++;
                else
                    beat1Numeric.Value--;

                circlePanel.Invalidate();
            }
        }

        private void circlePanel_Paint(object sender, PaintEventArgs e)
        {
            // Draw background
            circleView.DrawBackground(circlePanel.Width, circlePanel.Height, this.BackColor);

            // Draw masks
            circleView.DrawMasks(chart);

            // Draw base and measure circle.
            circleView.DrawCircle();

            // Draw degree lines
            circleView.DrawDegreeLines();

            // Draw holds
            circleView.DrawHolds(chart, highlightViewedNoteToolStripMenuItem.Checked, selectedNoteIndex);

            // Draw notes
            circleView.DrawNotes(chart, highlightViewedNoteToolStripMenuItem.Checked, selectedNoteIndex);

            // Determine if cursor should be showing
            bool showCursor = showCursorToolStripMenuItem.Checked || circleView.mouseDownPos != -1;
            if (currentSong != null && !currentSong.Paused)
            {
                showCursor = showCursorDuringPlaybackToolStripMenuItem.Checked;
            }

            // Draw cursor
            if (showCursor)
            {
                circleView.DrawCursor(currentNoteType, (float)positionNumeric.Value, (float)sizeNumeric.Value);
            }

            // Everything has been drawn, render it.
            circleView.Render(e.Graphics);
        }

        private void measureNumeric_ValueChanged(object sender, EventArgs e)
        {
            updateTime();
        }

        private void beat1Numeric_ValueChanged(object sender, EventArgs e)
        {
            if (beat1Numeric.Value >= beat2Numeric.Value)
            {
                measureNumeric.Value++;
                beat1Numeric.Value = 0;
            }
            else if (beat1Numeric.Value < 0)
            {
                if (measureNumeric.Value > 0)
                {
                    measureNumeric.Value--;
                    beat1Numeric.Value = beat2Numeric.Value - 1;
                }
                else if (measureNumeric.Value == 0)
                {
                    beat1Numeric.Value = 0;
                }
            }
            updateTime();
            if (currentSong != null && !IsSongPlaying() && valueTriggerEvent != EventSource.TrackBar)
                songTrackBar.Value = chart.GetTime(new BeatInfo((int)measureNumeric.Value, (int)beat1Numeric.Value * 1920 / (int)beat2Numeric.Value));

            valueTriggerEvent = EventSource.None;
        }

        private void beat2Numeric_ValueChanged(object sender, EventArgs e)
        {
            updateTime();
        }

        private void updateTime()
        {
            if (currentSong == null || (currentSong != null && currentSong.Paused))
            {
                circleView.CurrentMeasure = (float)measureNumeric.Value + ((float)beat1Numeric.Value / (float)beat2Numeric.Value);
                circlePanel.Invalidate();
            }

            if (currentNoteType == NoteType.HoldJoint || currentNoteType == NoteType.HoldEnd)
            {
                if (lastNote.BeatInfo.MeasureDecimal >= circleView.CurrentMeasure)
                    insertButton.Enabled = false;
                else
                    insertButton.Enabled = true;
            }
            else if (currentSong != null && !currentSong.Paused)
            {
                insertButton.Enabled = false;
            }
            else
            { 
                insertButton.Enabled = true;
            }
        }

        private void positionNumeric_ValueChanged(object sender, EventArgs e)
        {
            positionTrackBar.Value = (int)positionNumeric.Value;
            circlePanel.Invalidate();
        }

        private void positionTrackBar_ValueChanged(object sender, EventArgs e)
        {
            positionNumeric.Value = positionTrackBar.Value;
            circlePanel.Invalidate();
        }

        private void sizeNumeric_ValueChanged(object sender, EventArgs e)
        {
            sizeTrackBar.Value = (int)sizeNumeric.Value;
            circlePanel.Invalidate();
        }

        private void sizeTrackBar_ValueChanged(object sender, EventArgs e)
        {
            sizeNumeric.Value = sizeTrackBar.Value;
            circlePanel.Invalidate();
        }

        private void tapButton_Click(object sender, EventArgs e)
        {
            if (noBonusRadio.Checked)
                SetSelectedObject(NoteType.TouchNoBonus);
            else if (bonusRadio.Checked)
                SetSelectedObject(NoteType.TouchBonus);
            else if (flairRadio.Checked)
                SetSelectedObject(NoteType.TouchBonusFlair);

            currentGimmickType = GimmickType.NoGimmick;
        }

        private void orangeButton_Click(object sender, EventArgs e)
        {
            if (noBonusRadio.Checked)
                SetSelectedObject(NoteType.SlideOrangeNoBonus);
            else if (bonusRadio.Checked)
                SetSelectedObject(NoteType.SlideOrangeBonus);
            else if (flairRadio.Checked)
                SetSelectedObject(NoteType.SlideOrangeBonusFlair);

            currentGimmickType = GimmickType.NoGimmick;
        }

        private void greenButton_Click(object sender, EventArgs e)
        {
            if (noBonusRadio.Checked)
                SetSelectedObject(NoteType.SlideGreenNoBonus);
            else if (bonusRadio.Checked)
                SetSelectedObject(NoteType.SlideGreenBonus);
            else if (flairRadio.Checked)
                SetSelectedObject(NoteType.SlideGreenBonusFlair);

            currentGimmickType = GimmickType.NoGimmick;
        }

        private void redButton_Click(object sender, EventArgs e)
        {
            if (noBonusRadio.Checked)
                SetSelectedObject(NoteType.SnapRedNoBonus);
            else if (bonusRadio.Checked)
            {
                flairRadio.InvokeIfRequired(() => { flairRadio.Checked = true; });
                SetSelectedObject(NoteType.SnapRedBonusFlair);
            }
            else if (flairRadio.Checked)
                SetSelectedObject(NoteType.SnapRedBonusFlair);

            currentGimmickType = GimmickType.NoGimmick;
        }

        private void blueButton_Click(object sender, EventArgs e)
        {
            if (noBonusRadio.Checked)
                SetSelectedObject(NoteType.SnapBlueNoBonus);
            else if (bonusRadio.Checked)
            {
                flairRadio.InvokeIfRequired(() => { flairRadio.Checked = true; });
                SetSelectedObject(NoteType.SnapBlueBonusFlair);
            }
            else if (flairRadio.Checked)
                SetSelectedObject(NoteType.SnapBlueBonusFlair);

            currentGimmickType = GimmickType.NoGimmick;
        }

        private void chainButton_Click(object sender, EventArgs e)
        {
            if (noBonusRadio.Checked)
                SetSelectedObject(NoteType.Chain);
            else if (bonusRadio.Checked)
            {
                flairRadio.InvokeIfRequired(() => { flairRadio.Checked = true; });
                SetSelectedObject(NoteType.ChainBonusFlair);
            }
            else if (flairRadio.Checked)
                SetSelectedObject(NoteType.ChainBonusFlair);

            currentGimmickType = GimmickType.NoGimmick;
        }

        private void holdButton_Click(object sender, EventArgs e)
        {
            holdButtonClicked();
        }

        private void holdButtonClicked()
        {
            if (noBonusRadio.Checked)
                SetSelectedObject(NoteType.HoldStartNoBonus);
            else if (bonusRadio.Checked)
            {
                flairRadio.InvokeIfRequired(() => { flairRadio.Checked = true; });
                SetSelectedObject(NoteType.HoldStartBonusFlair);
            }
            else if (flairRadio.Checked)
                SetSelectedObject(NoteType.HoldStartBonusFlair);

            currentGimmickType = GimmickType.NoGimmick;
        }

        private void endChartButton_Click(object sender, EventArgs e)
        {
            SetSelectedObject(NoteType.EndOfChart);
            currentGimmickType = GimmickType.NoGimmick;
        }

        private void endHoldCheck_CheckedChanged(object sender, EventArgs e)
        {
            if(endHoldCheck.Checked && currentNoteType == NoteType.HoldJoint)
            {
                SetSelectedObject(NoteType.HoldEnd);
            }
            if (!endHoldCheck.Checked && currentNoteType == NoteType.HoldEnd)
            {
                SetSelectedObject(NoteType.HoldJoint);
            }
        }

        private void BonusRadioCheck(object sender, EventArgs e)
        {
            if (noBonusRadio.Checked)
                currentBonusType = BonusType.NoBonus;
            else if (bonusRadio.Checked)
                currentBonusType = BonusType.Bonus;
            else
                currentBonusType = BonusType.Flair;
            UpdateSelectedNote();
        }

        private void UpdateSelectedNote()
        {
            switch (currentNoteType)
            {
                case NoteType.TouchNoBonus:
                case NoteType.TouchBonus:
                case NoteType.TouchBonusFlair:
                    switch (currentBonusType)
                    {
                        case BonusType.NoBonus:
                            SetSelectedObject(NoteType.TouchNoBonus);
                            break;
                        case BonusType.Bonus:
                            SetSelectedObject(NoteType.TouchBonus);
                            break;
                        case BonusType.Flair:
                            SetSelectedObject(NoteType.TouchBonusFlair);
                            break;
                        default:
                            break;
                    }
                    break;
                case NoteType.SnapRedNoBonus:
                case NoteType.SnapRedBonusFlair:
                    switch (currentBonusType)
                    {
                        case BonusType.NoBonus:
                            SetSelectedObject(NoteType.SnapRedNoBonus);
                            break;
                        case BonusType.Bonus:
                            flairRadio.Checked = true;
                            SetSelectedObject(NoteType.SnapRedBonusFlair);
                            break;
                        case BonusType.Flair:
                            SetSelectedObject(NoteType.SnapRedBonusFlair);
                            break;
                        default:
                            break;
                    }
                    break;
                case NoteType.SnapBlueNoBonus:
                case NoteType.SnapBlueBonusFlair:
                    switch (currentBonusType)
                    {
                        case BonusType.NoBonus:
                            SetSelectedObject(NoteType.SnapBlueNoBonus);
                            break;
                        case BonusType.Bonus:
                            flairRadio.Checked = true;
                            SetSelectedObject(NoteType.SnapBlueBonusFlair);
                            break;
                        case BonusType.Flair:
                            SetSelectedObject(NoteType.SnapBlueBonusFlair);
                            break;
                        default:
                            break;
                    }
                    break;
                case NoteType.SlideOrangeNoBonus:
                case NoteType.SlideOrangeBonus:
                case NoteType.SlideOrangeBonusFlair:
                    switch (currentBonusType)
                    {
                        case BonusType.NoBonus:
                            SetSelectedObject(NoteType.SlideOrangeNoBonus);
                            break;
                        case BonusType.Bonus:
                            SetSelectedObject(NoteType.SlideOrangeBonus);
                            break;
                        case BonusType.Flair:
                            SetSelectedObject(NoteType.SlideOrangeBonusFlair);
                            break;
                        default:
                            break;
                    }
                    break;
                case NoteType.SlideGreenNoBonus:
                case NoteType.SlideGreenBonus:
                case NoteType.SlideGreenBonusFlair:
                    switch (currentBonusType)
                    {
                        case BonusType.NoBonus:
                            SetSelectedObject(NoteType.SlideGreenNoBonus);
                            break;
                        case BonusType.Bonus:
                            SetSelectedObject(NoteType.SlideGreenBonus);
                            break;
                        case BonusType.Flair:
                            SetSelectedObject(NoteType.SlideGreenBonusFlair);
                            break;
                        default:
                            break;
                    }
                    break;
                case NoteType.HoldStartNoBonus:
                case NoteType.HoldStartBonusFlair:
                    switch (currentBonusType)
                    {
                        case BonusType.NoBonus:
                            SetSelectedObject(NoteType.HoldStartNoBonus);
                            break;
                        case BonusType.Bonus:
                            flairRadio.Checked = true;
                            SetSelectedObject(NoteType.HoldStartBonusFlair);
                            break;
                        case BonusType.Flair:
                            SetSelectedObject(NoteType.HoldStartBonusFlair);
                            break;
                        default:
                            break;
                    }
                    break;
                case NoteType.HoldJoint:
                    break;
                case NoteType.HoldEnd:
                    break;
                case NoteType.MaskAdd:
                    break;
                case NoteType.MaskRemove:
                    break;
                case NoteType.EndOfChart:
                    break;
                case NoteType.Chain:
                case NoteType.ChainBonusFlair:
                    switch (currentBonusType)
                    {
                        case BonusType.NoBonus:
                            SetSelectedObject(NoteType.Chain);
                            break;
                        case BonusType.Bonus:
                            flairRadio.Checked = true;
                            SetSelectedObject(NoteType.ChainBonusFlair);
                            break;
                        case BonusType.Flair:
                            SetSelectedObject(NoteType.ChainBonusFlair);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        private void SetInitialSong()
        {
            // :)
            songFilePath = Path.Combine(System.AppDomain.CurrentDomain.BaseDirectory, "ERROR.ogg");
            currentSong = soundEngine.Play2D(songFilePath, true, true);
            if (currentSong != null)
            {
                /* Volume is represented as a float from 0-1. */
                currentSong.Volume = (float)trackBarVolume.Value / (float)trackBarVolume.Maximum;

                songTrackBar.Value = 0;
                songTrackBar.Maximum = (int)currentSong.PlayLength;
            }
            else
            {
                playButton.Enabled = false;
            }
        }
        private void selectSongButton_Click(object sender, EventArgs e)
        {
            if (openSongDialog.ShowDialog() != DialogResult.Cancel)
            {
                songFilePath = openSongDialog.FileName;
                songFileLabel.Text = songFilePath;
                currentSong = soundEngine.Play2D(songFilePath, true, true);
                if (currentSong != null)
                {
                    /* Volume is represented as a float from 0-1. */
                    currentSong.Volume = (float)trackBarVolume.Value / (float)trackBarVolume.Maximum;

                    songTrackBar.Value = 0;
                    songTrackBar.Maximum = (int)currentSong.PlayLength;
                    playButton.Enabled = true;
                }
            }
        }

        private void playButton_Click(object sender, EventArgs e)
        {
            if (currentSong != null)
            {
                if (!chart.HasInitEvents)
                {
                    MessageBox.Show("Set Initial Chart Settings (from Chart Menu).", "Warning!");
                    return;
                }

                currentSong.PlayPosition = (uint)songTrackBar.Value;
                currentSong.Paused = !currentSong.Paused;
                if (currentSong.Paused)
                {
                    playButton.Text = "Play";
                    updateTimer.Enabled = false;
                }
                else
                {
                    playButton.Text = "Pause";
                    updateTimer.Enabled = true;
                }
                playButton.AppendHotkey(userSettings.HotkeySettings.PlayHotkey);
            }
        }

        private bool IsSongPlaying()
        {
            if (currentSong != null && !currentSong.Paused)
                return true;
            else
                return false;
        }

        private void updateTimer_Tick(object sender, EventArgs e)
        {
            songTrackBar.Value = (int)currentSong.PlayPosition;
            var info = chart.GetBeat(currentSong.PlayPosition);
            if (info != null && info.Measure != -1)
            {
                measureNumeric.Value = info.Measure;
                beat1Numeric.Value = (int)((float)info.Beat / 1920.0f * (float)beat2Numeric.Value);
                circleView.CurrentMeasure = info.MeasureDecimal;

                // TODO Fix hi-speed (it needs to be able to display multiple hi-speeds in the circle view at once)
                //// Change hi-speed, if applicable
                //var hispeed = chart.Gimmicks.Where(x => x.Measure <= info.Measure && x.GimmickType == GimmickType.HiSpeedChange).LastOrDefault();
                //if (hispeed != null && hispeed.HiSpeed != circleView.TotalMeasureShowNotes)
                //{
                //    visualHispeedNumeric.Value = (decimal)hispeed.HiSpeed;
                //}
            }
            circlePanel.Invalidate();
        }

        private void songTrackBar_ValueChanged(object sender, EventArgs e)
        {
            if (currentSong == null)
                return;
            if (IsSongPlaying())
                return;

            currentSong.PlayPosition = (uint)songTrackBar.Value;
            var info = chart.GetBeat(currentSong.PlayPosition);
            if (info != null && info.Measure != -1 && valueTriggerEvent != EventSource.MouseWheel)
            {
                valueTriggerEvent = EventSource.TrackBar;
                measureNumeric.Value = info.Measure;
                beat1Numeric.Value = (int)((float)info.Beat / 1920.0f * (float)beat2Numeric.Value);
                circleView.CurrentMeasure = info.MeasureDecimal;
            }
            circlePanel.Invalidate();
            valueTriggerEvent = EventSource.None;
        }

        private void circlePanel_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left)
            {
                return;
            }

            // X and Y are relative to the upper left of the panel
            float xCen = e.X - (circlePanel.Width / 2);
            float yCen = -(e.Y - (circlePanel.Height / 2));
            // Update the location of mouse click inside the circle
            circleView.UpdateMouseDown(xCen, yCen, e.Location);
            positionNumeric.Value = circleView.mouseDownPos;
            circlePanel.Invalidate();
        }

        private void circlePanel_MouseUp(object sender, MouseEventArgs e)
        {
            // Mouse down position wasn't within the window or wasn't a left click, do nothing.
            if (e.Button != MouseButtons.Left || circleView.mouseDownPos <= -1)
            {
                return;
            }

            var dist = Utils.GetDist(e.Location, circleView.mouseDownPt);
            if (dist > 5.0f)
                InsertObject();
            circleView.UpdateMouseUp();
            circlePanel.Invalidate();
        }

        private void circlePanel_MouseMove(object sender, MouseEventArgs e)
        {
            // Mouse down position wasn't within the window or wasn't a left click, do nothing.
            if (e.Button != MouseButtons.Left || circleView.mouseDownPos <= -1)
            {
                return;
            }

            // X and Y are relative to the upper left of the panel
            float xCen = e.X - (circlePanel.Width / 2);
            float yCen = -(e.Y - (circlePanel.Height / 2));
            // Update the location of mouse click inside the circle.
            int theta = circleView.UpdateMouseMove(xCen, yCen);
            // Left click will alter the note width and possibly position depending on which direction we move
            if (theta == circleView.mouseDownPos)
            {
                positionNumeric.Value = circleView.mouseDownPos;
                sizeNumeric.Value = 1;
            }
            else if ((theta > circleView.mouseDownPos || circleView.rolloverPos) && !circleView.rolloverNeg)
            {
                positionNumeric.Value = circleView.mouseDownPos;
                if (circleView.rolloverPos)
                    sizeNumeric.Value = (int)Math.Min(theta + 60 - circleView.mouseDownPos + 1, 60);
                else
                    sizeNumeric.Value = theta - circleView.mouseDownPos + 1;
            }
            else if (theta < circleView.mouseDownPos || circleView.rolloverNeg)
            {
                positionNumeric.Value = theta;
                if (circleView.rolloverNeg)
                    sizeNumeric.Value = (int)Math.Min(circleView.mouseDownPos + 60 - theta + 1, 60);
                else
                    sizeNumeric.Value = circleView.mouseDownPos - theta + 1;
            }

            circlePanel.Invalidate();
        }

        private void visualHispeedNumeric_ValueChanged(object sender, EventArgs e)
        {
            circleView.TotalMeasureShowNotes = (float)visualHispeedNumeric.Value;
            circlePanel.Invalidate();
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            InsertObject();
        }

        private void InsertObject()
        {
            if (!insertButton.Enabled)
                return;

            var currentBeat = new BeatInfo((int)measureNumeric.Value, (int)beat1Numeric.Value * 1920 / (int)beat2Numeric.Value);

            if (currentGimmickType == GimmickType.NoGimmick)
            {
                Note tempNote = new Note()
                {
                    BeatInfo = currentBeat,
                    NoteType = currentNoteType,
                    Position = (int)positionNumeric.Value,
                    Size = (int)sizeNumeric.Value,
                    HoldChange = true
                };
                switch (currentNoteType)
                {
                    case NoteType.HoldStartNoBonus:
                    case NoteType.HoldStartBonusFlair:
                        SetSelectedObject(NoteType.HoldJoint);
                        lastNote = tempNote;
                        SetNonHoldButtonState(false);
                        break;
                    case NoteType.HoldJoint:
                    case NoteType.HoldEnd:
                        tempNote.PrevNote = lastNote;
                        tempNote.PrevNote.NextNote = tempNote;
                        if (endHoldCheck.Checked)
                        {
                            tempNote.NoteType = NoteType.HoldEnd;
                            SetNonHoldButtonState(true);
                            endHoldCheck.Checked = false;
                            holdButtonClicked();
                        }
                        else
                            lastNote = tempNote;
                        break;
                    case NoteType.MaskAdd:
                    case NoteType.MaskRemove:
                        if (clockwiseMaskRadio.Checked)
                            tempNote.MaskFill = MaskType.Clockwise;
                        else if (cClockwiseMaskRadio.Checked)
                            tempNote.MaskFill = MaskType.CounterClockwise;
                        else
                            tempNote.MaskFill = MaskType.Center;
                        break;
                    default:
                        break;
                }
                chart.Notes.Add(tempNote);
                chart.IsSaved = false;
                switch (currentNoteType)
                {
                    case NoteType.HoldStartNoBonus:
                    case NoteType.HoldStartBonusFlair:
                    case NoteType.HoldJoint:
                    case NoteType.HoldEnd:
                        opManager.Push(new InsertHoldNote(chart, tempNote));
                        break;
                    default:
                        opManager.Push(new InsertNote(chart, tempNote));
                        break;
                }
            }
        }

        private void SetNonHoldButtonState(bool state)
        {
            tapButton.Enabled = state;
            orangeButton.Enabled = state;
            greenButton.Enabled = state;
            redButton.Enabled = state;
            blueButton.Enabled = state;
            chainButton.Enabled = state;
            endChartButton.Enabled = state;

            maskButton.Enabled = state;
            bpmChangeButton.Enabled = state;
            timeSigButton.Enabled = state;
            hiSpeedButton.Enabled = state;
            stopButton.Enabled = state;
            reverseButton.Enabled = state;
        }

        private void maskButton_Click(object sender, EventArgs e)
        {
            if (addMaskRadio.Checked)
                SetSelectedObject(NoteType.MaskAdd);
            else
                SetSelectedObject(NoteType.MaskRemove);
            SetSelectedObject(GimmickType.NoGimmick);
        }

        private void bpmChangeButton_Click(object sender, EventArgs e)
        {
            var result = gimmickForm.Show(
                new Gimmick()
                {
                    BeatInfo = new BeatInfo((int)measureNumeric.Value, (int)beat1Numeric.Value * 1920 / (int)beat2Numeric.Value),
                    GimmickType = GimmickType.BpmChange
                }, GimmickForm.FormReason.New);
            if (result == DialogResult.OK)
            {
                InsertGimmick(gimmickForm.Gimmicks);
            }
        }

        private void timeSigButton_Click(object sender, EventArgs e)
        {
            var result = gimmickForm.Show(
                new Gimmick()
                {
                    BeatInfo = new BeatInfo((int)measureNumeric.Value, (int)beat1Numeric.Value * 1920 / (int)beat2Numeric.Value),
                    GimmickType = GimmickType.TimeSignatureChange
                }, GimmickForm.FormReason.New);
            if (result == DialogResult.OK)
            {
                InsertGimmick(gimmickForm.Gimmicks);
            }
        }

        private void hiSpeedButton_Click(object sender, EventArgs e)
        {
            var result = gimmickForm.Show(
                new Gimmick()
                {
                    BeatInfo = new BeatInfo((int)measureNumeric.Value, (int)beat1Numeric.Value * 1920 / (int)beat2Numeric.Value),
                    GimmickType = GimmickType.HiSpeedChange
                }, GimmickForm.FormReason.New);
            if (result == DialogResult.OK)
            {
                InsertGimmick(gimmickForm.Gimmicks);
            }
        }

        private void stopButton_Click(object sender, EventArgs e)
        {
            var result = gimmickForm.Show(
                new Gimmick()
                {
                    BeatInfo = new BeatInfo((int)measureNumeric.Value, (int)beat1Numeric.Value * 1920 / (int)beat2Numeric.Value),
                    GimmickType = GimmickType.StopStart
                }, GimmickForm.FormReason.New);
            if (result == DialogResult.OK)
            {
                InsertGimmick(gimmickForm.Gimmicks);
            }
        }

        private void reverseButton_Click(object sender, EventArgs e)
        {
            var result = gimmickForm.Show(
                new Gimmick()
                {
                    BeatInfo = new BeatInfo((int)measureNumeric.Value, (int)beat1Numeric.Value * 1920 / (int)beat2Numeric.Value),
                    GimmickType = GimmickType.ReverseStart
                }, GimmickForm.FormReason.New);
            if (result == DialogResult.OK)
            {
                InsertGimmick(gimmickForm.Gimmicks);
            }
        }

        private void InsertGimmick(List<Gimmick> gimmicks)
        {
            var operations = new List<InsertGimmick>();
            foreach (var gim in gimmicks)
            {
                chart.Gimmicks.Add(gim);
                operations.Add(new Operations.InsertGimmick(chart, gim));
            }
            chart.IsSaved = false;
            opManager.Push(new CompositeOperation(operations[0].Description, operations));
        }

        private void maskRatio_CheckChanged(object sender, EventArgs e)
        {
            if (currentNoteType == NoteType.MaskAdd || currentNoteType == NoteType.MaskRemove)
                maskButton_Click(this, new EventArgs());
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show(
                $"Authors: Goatgarien and VeroxZik\n" +
                $"Contributions: Yellowberry, Farex-GH\n" +
                $"Icon: IPIhypster", 
                $"BAKKA Editor {fileVersion}");
        }

        private void initialChartSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ShowInitialSettings();   
        }

        private void ShowInitialSettings()
        {
            if (initSettingsForm.ShowDialog() == DialogResult.OK)
            {
                var initBpm = chart.Gimmicks.FirstOrDefault(x => x.Measure == 0.0f && x.GimmickType == GimmickType.BpmChange);
                if (initBpm != null)
                    initBpm.BPM = initSettingsForm.Bpm;
                else
                    chart.Gimmicks.Add(new Gimmick() { BPM = initSettingsForm.Bpm, BeatInfo = new BeatInfo(0, 0), GimmickType = GimmickType.BpmChange });

                var initTimSig = chart.Gimmicks.FirstOrDefault(x => x.Measure == 0.0f && x.GimmickType == GimmickType.TimeSignatureChange);
                if (initTimSig != null)
                {
                    initTimSig.TimeSig.Upper = initSettingsForm.TimeSigUpper;
                    initTimSig.TimeSig.Lower = initSettingsForm.TimeSigLower;
                }
                else
                    chart.Gimmicks.Add(
                        new Gimmick()
                        {
                            TimeSig = new TimeSignature() { Upper = initSettingsForm.TimeSigUpper, Lower = initSettingsForm.TimeSigLower },
                            BeatInfo = new BeatInfo(0, 0),
                            GimmickType = GimmickType.TimeSignatureChange
                        });
                chart.Offset = initSettingsForm.Offset;
                chart.MovieOffset = initSettingsForm.MovieOffset;

                if (selectedGimmickIndex == -1)
                    selectedGimmickIndex = 0;
                UpdateGimmickLabels();
                chart.Gimmicks = chart.Gimmicks.OrderBy(x => x.Measure).ToList();
                chart.RecalcTime();
            }
        }

        private void showCursorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            circlePanel.Invalidate();
        }

        private void gimmickPrevButton_Click(object sender, EventArgs e)
        {
            if (chart.Gimmicks.Count == 0)
                return;

            if (selectedGimmickIndex == 0)
                selectedGimmickIndex = chart.Gimmicks.Count - 1;
            else
                selectedGimmickIndex -= 1;

            UpdateGimmickLabels();
        }

        private void gimmickNextButton_Click(object sender, EventArgs e)
        {
            if (chart.Gimmicks.Count == 0)
                return;

            if (selectedGimmickIndex == chart.Gimmicks.Count - 1)
                selectedGimmickIndex = 0;
            else
                selectedGimmickIndex += 1;

            UpdateGimmickLabels();
        }

        private void gimmickEditButton_Click(object sender, EventArgs e)
        {
            if (selectedGimmickIndex == -1)
                return;

            var gimmick = chart.Gimmicks[selectedGimmickIndex];
            Gimmick? gim1 = null;
            Gimmick? gim2 = null;
            if (gimmick.Measure == 0 && (gimmick.GimmickType == GimmickType.BpmChange || gimmick.GimmickType == GimmickType.TimeSignatureChange))
                ShowInitialSettings();
            else
            {
                switch (gimmick.GimmickType)
                {
                    case GimmickType.ReverseStart:
                        gim1 = chart.Gimmicks.FirstOrDefault(x => x.Measure > gimmick.Measure && x.GimmickType == GimmickType.ReverseMiddle);
                        gim2 = chart.Gimmicks.FirstOrDefault(x => x.Measure > gimmick.Measure && x.GimmickType == GimmickType.ReverseEnd);
                        break;
                    case GimmickType.ReverseMiddle:
                        gim1 = chart.Gimmicks.LastOrDefault(x => x.Measure < gimmick.Measure && x.GimmickType == GimmickType.ReverseStart);
                        gim2 = chart.Gimmicks.FirstOrDefault(x => x.Measure > gimmick.Measure && x.GimmickType == GimmickType.ReverseEnd);
                        break;
                    case GimmickType.ReverseEnd:
                        gim1 = chart.Gimmicks.LastOrDefault(x => x.Measure < gimmick.Measure && x.GimmickType == GimmickType.ReverseStart);
                        gim2 = chart.Gimmicks.LastOrDefault(x => x.Measure < gimmick.Measure && x.GimmickType == GimmickType.ReverseMiddle);
                        break;
                    case GimmickType.StopStart:
                        gim1 = chart.Gimmicks.FirstOrDefault(x => x.Measure > gimmick.Measure && x.GimmickType == GimmickType.StopEnd);
                        break;
                    case GimmickType.StopEnd:
                        gim1 = chart.Gimmicks.LastOrDefault(x => x.Measure < gimmick.Measure && x.GimmickType == GimmickType.StopStart);
                        break;
                    default:
                        break;
                }

                if (gimmickForm.Show(gimmick, GimmickForm.FormReason.Edit, gim1, gim2) == DialogResult.OK)
                {
                    var opList = new List<EditGimmick>();

                    switch (gimmick.GimmickType)
                    {
                        case GimmickType.BpmChange:
                        case GimmickType.TimeSignatureChange:
                        case GimmickType.HiSpeedChange:
                            opList.Add(new EditGimmick(gimmick, gimmickForm.Gimmicks[0]));
                            break;
                        case GimmickType.ReverseStart:
                            opList.Add(new EditGimmick(gimmick, gimmickForm.Gimmicks[0]));
                            opList.Add(new EditGimmick(gim1, gimmickForm.Gimmicks[1]));
                            opList.Add(new EditGimmick(gim2, gimmickForm.Gimmicks[2]));
                            break;
                        case GimmickType.ReverseMiddle:
                            opList.Add(new EditGimmick(gim1, gimmickForm.Gimmicks[0]));
                            opList.Add(new EditGimmick(gimmick, gimmickForm.Gimmicks[1]));
                            opList.Add(new EditGimmick(gim2, gimmickForm.Gimmicks[2]));
                            break;
                        case GimmickType.ReverseEnd:
                            opList.Add(new EditGimmick(gim1, gimmickForm.Gimmicks[0]));
                            opList.Add(new EditGimmick(gim2, gimmickForm.Gimmicks[1]));
                            opList.Add(new EditGimmick(gimmick, gimmickForm.Gimmicks[2]));
                            break;
                        case GimmickType.StopStart:
                            opList.Add(new EditGimmick(gimmick, gimmickForm.Gimmicks[0]));
                            opList.Add(new EditGimmick(gim1, gimmickForm.Gimmicks[1]));
                            break;
                        case GimmickType.StopEnd:
                            opList.Add(new EditGimmick(gim1, gimmickForm.Gimmicks[0]));
                            opList.Add(new EditGimmick(gimmick, gimmickForm.Gimmicks[1]));
                            break;
                        default:
                            break;
                    }
                    opManager.InvokeAndPush(new CompositeOperation(opList[0].Description, opList));
                    UpdateGimmickLabels();
                }
            }
        }

        private void gimmickDeleteButton_Click(object sender, EventArgs e)
        {
            if (selectedGimmickIndex == -1)
                return;

            float measure = chart.Gimmicks[selectedGimmickIndex].Measure;
            var type = chart.Gimmicks[selectedGimmickIndex].GimmickType;
            var gimmicks = new List<Gimmick>();
            gimmicks.Add(chart.Gimmicks[selectedGimmickIndex]);
            chart.Gimmicks.RemoveAt(selectedGimmickIndex);
            switch (type)
            {
                case GimmickType.ReverseStart:
                    gimmicks.Add(chart.Gimmicks.First(x => x.Measure > measure && x.GimmickType == GimmickType.ReverseMiddle));
                    gimmicks.Add(chart.Gimmicks.First(x => x.Measure > measure && x.GimmickType == GimmickType.ReverseEnd));
                    break;
                case GimmickType.ReverseMiddle:
                    gimmicks.Add(chart.Gimmicks.Last(x => x.Measure < measure && x.GimmickType == GimmickType.ReverseStart));
                    gimmicks.Add(chart.Gimmicks.First(x => x.Measure > measure && x.GimmickType == GimmickType.ReverseEnd));
                    break;
                case GimmickType.ReverseEnd:
                    gimmicks.Add(chart.Gimmicks.Last(x => x.Measure < measure && x.GimmickType == GimmickType.ReverseStart));
                    gimmicks.Add(chart.Gimmicks.Last(x => x.Measure < measure && x.GimmickType == GimmickType.ReverseMiddle));
                    break;
                case GimmickType.StopStart:
                    gimmicks.Add(chart.Gimmicks.First(x => x.Measure > measure && x.GimmickType == GimmickType.StopEnd));
                    break;
                case GimmickType.StopEnd:
                    gimmicks.Add(chart.Gimmicks.Last(x => x.Measure < measure && x.GimmickType == GimmickType.StopStart));
                    break;
                default:
                    break;
            }
            var ops = new List<RemoveGimmick>();
            foreach (var gim in gimmicks)
                ops.Add(new RemoveGimmick(chart, gim));
            opManager.InvokeAndPush(new CompositeOperation(ops[0].Description, ops));
            if (selectedGimmickIndex >= chart.Gimmicks.Count)
                selectedGimmickIndex = chart.Gimmicks.Count - 1;
            UpdateGimmickLabels();
        }

        private void UpdateGimmickLabels(int val = -2)
        {
            if (val != -2 && val < chart.Gimmicks.Count)
                selectedGimmickIndex = val;
            if (selectedGimmickIndex == -1)
            {
                gimmickMeasureLabel.Text = "None";
                gimmickBeatLabel.Text = "None";
                gimmickTypeLabel.Text = "None";
                gimmickValueLabel.Text = "None";
                return;
            }

            var gimmick = chart.Gimmicks[selectedGimmickIndex];

            gimmickMeasureLabel.Text = gimmick.BeatInfo.Measure.ToString();
            var quant = Utils.GetQuantization(gimmick.BeatInfo.Beat, 16);
            gimmickBeatLabel.Text = $"{quant.Item1} / {quant.Item2}";
            gimmickTypeLabel.Text = gimmick.GimmickType.ToLabel();
            switch (gimmick.GimmickType)
            {
                case GimmickType.BpmChange:
                    gimmickValueLabel.Text = gimmick.BPM.ToString("F6");
                    break;
                case GimmickType.TimeSignatureChange:
                    gimmickValueLabel.Text = gimmick.TimeSig.Upper.ToString() + " / " + gimmick.TimeSig.Lower.ToString();
                    break;
                case GimmickType.HiSpeedChange:
                    gimmickValueLabel.Text = gimmick.HiSpeed.ToString("F6");
                    break;
                case GimmickType.NoGimmick:
                case GimmickType.ReverseStart:
                case GimmickType.ReverseMiddle:
                case GimmickType.ReverseEnd:
                case GimmickType.StopStart:
                case GimmickType.StopEnd:
                default:
                    gimmickValueLabel.Text = "No value";
                    break;
            }

            // Prevent deletetion of initial BPM and time signature
            if (chart.Gimmicks.Count == 0 
                || (gimmick.Measure == 0 && (gimmick.GimmickType == GimmickType.BpmChange || gimmick.GimmickType == GimmickType.TimeSignatureChange)))
            {
                gimmickDeleteButton.Enabled = false;
            }
            else
            {
                gimmickDeleteButton.Enabled = true;
            }
        }

        private void UpdateNoteLabels(int val = -2)
        {
            if (val != -2)
                selectedNoteIndex = val;
            if(selectedNoteIndex == -1)
            {
                noteMeasureLabel.Text = "None";
                noteBeatLabel.Text = "None";
                noteTypeLabel.Text = "None";
                notePositionLabel.Text = "None";
                noteSizeLabel.Text = "None";
                noteMaskLabel.Text = "N/A";
                return;
            }

            var note = chart.Notes[selectedNoteIndex];

            noteMeasureLabel.Text = note.BeatInfo.Measure.ToString();
            var quant = Utils.GetQuantization(note.BeatInfo.Beat, 16);
            noteBeatLabel.Text = $"{quant.Item1} / {quant.Item2}";
            noteTypeLabel.Text = note.NoteType.ToLabel();
            notePositionLabel.Text = note.Position.ToString();
            noteSizeLabel.Text = note.Size.ToString();
            if (!note.IsMask)
                noteMaskLabel.Text = "N/A";
            else
            {
                switch (note.MaskFill)
                {
                    case MaskType.Clockwise:
                        noteMaskLabel.Text = "Clockwise";
                        break;
                    case MaskType.CounterClockwise:
                        noteMaskLabel.Text = "C-Clockwise";
                        break;
                    case MaskType.Center:
                        noteMaskLabel.Text = "From Center";
                        break;
                    default:
                        break;
                }
            }
        }

        private void ResetChartTime()
        {
            measureNumeric.Value = beat1Numeric.Value = 0;
            positionNumeric.Value = 0;
            sizeNumeric.Value = 1;
            updateTime();
        }

        private void notePrevButton_Click(object sender, EventArgs e)
        {
            if (chart.Notes.Count == 0)
                return;

            if (selectedNoteIndex == 0)
                selectedNoteIndex = chart.Notes.Count - 1;
            else
                selectedNoteIndex -= 1;

            circlePanel.Invalidate();
            UpdateNoteLabels();
        }

        private void noteNextButton_Click(object sender, EventArgs e)
        {
            if (chart.Notes.Count == 0)
                return;

            if (selectedNoteIndex == chart.Notes.Count - 1)
                selectedNoteIndex = 0;
            else
                selectedNoteIndex += 1;

            circlePanel.Invalidate();
            UpdateNoteLabels();
        }

        private void notePrevMeasureButton_Click(object sender, EventArgs e)
        {
            if (chart.Notes.Count == 0)
                return;

            int lastMeasure = chart.Notes[selectedNoteIndex].BeatInfo.Measure;
            var note = chart.Notes.LastOrDefault(x => x.BeatInfo.Measure < lastMeasure);
            if (note != null)
            {
                selectedNoteIndex = chart.Notes.IndexOf(note);
            }
            else
            {
                note = chart.Notes.LastOrDefault(x => x.BeatInfo.Measure > lastMeasure);
                if (note != null)
                {
                    selectedNoteIndex = chart.Notes.IndexOf(note);
                }
            }
            circlePanel.Invalidate();
            UpdateNoteLabels();
        }

        private void noteNextMeasureButton_Click(object sender, EventArgs e)
        {
            if (chart.Notes.Count == 0)
                return;

            int lastMeasure = chart.Notes[selectedNoteIndex].BeatInfo.Measure;
            var note = chart.Notes.FirstOrDefault(x => x.BeatInfo.Measure > lastMeasure);
            if (note != null)
            {
                selectedNoteIndex = chart.Notes.IndexOf(note);
            }
            else
            {
                note = chart.Notes.FirstOrDefault(x => x.BeatInfo.Measure < lastMeasure);
                if (note != null)
                {
                    selectedNoteIndex = chart.Notes.IndexOf(note);
                }
            }
            circlePanel.Invalidate();
            UpdateNoteLabels();
        }

        private void noteEditSelectedButton_Click(object sender, EventArgs e)
        {
            if (selectedNoteIndex == -1)
                return;
            var currentNote = chart.Notes[selectedNoteIndex];

            if (currentNote.NoteType == NoteType.EndOfChart)
                return;

            var newNote = new Note()
            {
                BeatInfo = currentNote.BeatInfo,
                Position = (int)positionNumeric.Value,
                Size = (int)sizeNumeric.Value
            };
            opManager.InvokeAndPush(new EditNote(currentNote, newNote));
            circlePanel.Invalidate();
            UpdateNoteLabels();
        }

        private void noteDeleteSelectedButton_Click(object sender, EventArgs e)
        {
            if (selectedNoteIndex == -1)
                return;

            int delIndex = selectedNoteIndex;
            NoteOperation op = chart.Notes[selectedNoteIndex].IsHold ? new RemoveHoldNote(chart, chart.Notes[selectedNoteIndex]) : new RemoveNote(chart, chart.Notes[selectedNoteIndex]);
            opManager.InvokeAndPush(op);
            UpdateControlsFromOperation(op, OperationDirection.Redo);
            if (selectedNoteIndex == delIndex)
            {
                UpdateNoteLabels(delIndex - 1);
                circlePanel.Invalidate();
            }
        }
        private void playbackVolumeChange(bool increase)
        {
            int val = trackBarVolume.LargeChange;
            /* Bounds check. */
            if (increase && (trackBarVolume.Value + val > trackBarVolume.Maximum))
            {
                val = trackBarVolume.Maximum - trackBarVolume.Value;
            }
            else if (!increase && (trackBarVolume.Value - val<trackBarVolume.Minimum))
            {
                val = trackBarVolume.Value - trackBarVolume.Minimum;
            }
            if (!increase)
            {
                val *= -1;
            }
            /*
             * Updating the trackbar volume will call the trackBarVolume_Changed
             * callback, which will update the current song volume.
             */
            trackBarVolume.Value += val;
            trackBarVolume.Focus();
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            var sender = this;
            var e = new EventArgs();

            switch (keyData)
            {
                case Keys.I:
                    if (insertButton.Enabled)
                        insertButton_Click(sender, e);
                    insertButton.Focus();
                    return true;
                case Keys.Up | Keys.Shift:
                    /* Fallthrough */
                case Keys.Down | Keys.Shift:
                    keyData &= ~Keys.Shift;
                    playbackVolumeChange(keyData == Keys.Up);
                    return true;
                default:
                    if (keyData == (Keys)userSettings.HotkeySettings.TouchHotkey)
                    {
                        if (tapButton.Enabled)
                            tapButton_Click(sender, e);
                        tapButton.Focus();
                        return true;
                    }
                    else if (keyData == (Keys)userSettings.HotkeySettings.SlideLeftHotkey)
                    {
                        if (orangeButton.Enabled)
                            orangeButton_Click(sender, e);
                        orangeButton.Focus();
                        return true;
                    }
                    else if (keyData == (Keys)userSettings.HotkeySettings.SlideRightHotkey)
                    {
                        if (greenButton.Enabled)
                            greenButton_Click(sender, e);
                        greenButton.Focus();
                        return true;
                    }
                    else if (keyData == (Keys)userSettings.HotkeySettings.SnapUpHotkey)
                    {
                        if (redButton.Enabled)
                            redButton_Click(sender, e);
                        redButton.Focus();
                        return true;
                    }
                    else if (keyData == (Keys)userSettings.HotkeySettings.SnapDownHotkey)
                    {
                        if (blueButton.Enabled)
                            blueButton_Click(sender, e);
                        blueButton.Focus();
                        return true;
                    }
                    else if (keyData == (Keys)userSettings.HotkeySettings.ChainHotkey)
                    {
                        if (chainButton.Enabled)
                            chainButton_Click(sender, e);
                        chainButton.Focus();
                        return true;
                    }
                    else if (keyData == (Keys)userSettings.HotkeySettings.HoldHotkey)
                    {
                        if (holdButton.Enabled)
                            holdButton_Click(sender, e);
                        holdButton.Focus();
                        return true;
                    }
                    else if (keyData == (Keys)userSettings.HotkeySettings.PlayHotkey)
                    {
                        if (playButton.Enabled)
                            playButton_Click(sender, e);
                        playButton.Focus();
                        return true;
                    }
                    break;
            }

            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void undoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (opManager.CanUndo)
            {
                var op = opManager.Undo();
                if (op != null)
                {
                    UpdateControlsFromOperation(op, OperationDirection.Undo);
                }
            }
        }

        private void redoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (opManager.CanRedo)
            {
                var op = opManager.Redo();
                if (op != null)
                {
                    UpdateControlsFromOperation(op, OperationDirection.Redo);
                }
            }
        }

        private void UpdateControlsFromOperation(IOperation op, OperationDirection dir)
        {
            if (dir == OperationDirection.Undo)
            {
                bool isInsertHold = op.GetType() == typeof(InsertHoldNote);
                bool isRemoveHold = op.GetType() == typeof(RemoveHoldNote);
                var note = op.GetType().IsSubclassOf(typeof(NoteOperation)) ? (op as NoteOperation).Note : null;
                if (note != null)
                {
                    if (note.NoteType == NoteType.HoldStartNoBonus || note.NoteType == NoteType.HoldStartBonusFlair)
                    {
                        if (isInsertHold)
                        {
                            SetNonHoldButtonState(true);
                            SetSelectedObject(note.NoteType);
                        }
                        if (isRemoveHold)
                        {
                            if (note.NextNote == null)
                            {
                                SetNonHoldButtonState(true);
                                SetSelectedObject(note.NoteType);
                            }
                        }
                    }
                    else if (note.NoteType == NoteType.HoldJoint)
                    {
                        if (isInsertHold)
                        {
                            lastNote = note.PrevNote;
                        }
                    }
                    else if (note.NoteType == NoteType.HoldEnd)
                    {
                        if (isInsertHold)
                        {
                            SetNonHoldButtonState(false);
                            SetSelectedObject(note.NoteType);
                            lastNote = note.PrevNote;
                        }
                    }
                    updateTime();
                }
            }
            else
            {
                bool isInsertHold = op.GetType() == typeof(InsertHoldNote);
                bool isRemoveHold = op.GetType() == typeof(RemoveHoldNote);
                var note = op.GetType().IsSubclassOf(typeof(NoteOperation)) ? (op as NoteOperation).Note : null;
                if (note != null)
                {
                    if (note.NoteType == NoteType.HoldStartNoBonus || note.NoteType == NoteType.HoldStartBonusFlair)
                    {
                        if (isInsertHold)
                        {
                            SetNonHoldButtonState(true);
                            SetSelectedObject(NoteType.HoldJoint);
                        }
                        if (isRemoveHold)
                        {
                            SetNonHoldButtonState(true);
                            SetSelectedObject(note.NoteType);
                        }
                    }
                    else if (note.NoteType == NoteType.HoldJoint)
                    {
                        if (isInsertHold)
                        {
                            lastNote = note;
                        }
                    }
                    else if (note.NoteType == NoteType.HoldEnd)
                    {
                        if (isInsertHold)
                        {
                            SetNonHoldButtonState(true);
                            SetSelectedObject(flairRadio.Checked ? NoteType.HoldStartBonusFlair : NoteType.HoldStartNoBonus);
                            lastNote = note;
                        }
                    }
                    updateTime();
                }
            }
        }

        
        private void trackBarVolume_ValueChanged(object sender, EventArgs e)
        {
            /* No song, nothing to do. */
            if (currentSong == null)
            {
                return;
            }
            /* Volume is represented as a float from 0-1. */
            currentSong.Volume = (float) trackBarVolume.Value / (float) trackBarVolume.Maximum;
            circlePanel.Invalidate();
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            var zoneWidth = noteViewGroupBox.Left - gimmickTypeGroupBox.Right - 12;
            var zoneHeight = playbackGroupBox.Top - gimmickTypeGroupBox.Top - 6;
            if (zoneWidth > zoneHeight)
            {
                circlePanel.Width = zoneHeight;
                circlePanel.Height = zoneHeight;
            }
            else
            {
                circlePanel.Width = zoneWidth;
                circlePanel.Height = zoneWidth;
            }
            int paddingLeft = (zoneWidth - circlePanel.Width) / 2;
            circlePanel.Left = gimmickTypeGroupBox.Right + 6 + paddingLeft;
            circleView.SetBufferedGraphicsContext(circlePanel.Width, circlePanel.Height, circlePanel.CreateGraphics());
            circleView.Update(circlePanel.Size);
            circlePanel.Invalidate();
        }

        private void autoSaveTimer_Tick(object sender, EventArgs e)
        {
            if (tempFilePath == "")
                tempFilePath = Path.GetTempFileName().Replace(".tmp", ".mer");

            if ((chart.Notes.Count > 0 || chart.Gimmicks.Count > 0) && !chart.IsSaved)
            {
                chart.WriteFile(tempFilePath, false);
                File.WriteAllLines(tempStatusPath, new string[] { "true", DateTime.Now.ToString("yyyy-MM-dd HH:mm") });
            }
            else
            {
                DeleteAutosaves(tempFilePath);
            }
        }

        private void DeleteAutosaves(string keep = "")
        {
            var oldAutosave = Directory.GetFiles(Path.GetTempPath(), "*.mer");
            foreach (var file in oldAutosave)
            {
                if (file != keep)
                    File.Delete(file);
            }
        }

        private void songTrackBar_MouseDown(object sender, MouseEventArgs e)
        {
            float val = ((float)e.Location.X / (float)songTrackBar.Width) *
                        (songTrackBar.Maximum - songTrackBar.Minimum);
            songTrackBar.Value = (int)val;
        }

        private void trackBarVolume_MouseDown(object sender, MouseEventArgs e)
        {
            float val = ((float)e.Location.X / (float)trackBarVolume.Width) *
                        (trackBarVolume.Maximum - trackBarVolume.Minimum);
            trackBarVolume.Value = (int)val;
        }

        private void trackBarSpeed_ValueChanged(object sender, EventArgs e)
        {
            /* No song, nothing to do. */
            if (currentSong == null)
            {
                return;
            }
            currentSong.PlaybackSpeed = (trackBarSpeed.Value / (float)trackBarSpeed.Maximum);
            labelSpeed.Text = $"Speed (x{currentSong.PlaybackSpeed:0.00})";
        }
    }
}