namespace BAKKA_Editor
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            openFileDialog = new OpenFileDialog();
            saveFileDialog = new SaveFileDialog();
            circlePanel = new Panel();
            groupBox1 = new GroupBox();
            label4 = new Label();
            beat2Numeric = new NumericUpDown();
            beat1Numeric = new NumericUpDown();
            measureNumeric = new NumericUpDown();
            label3 = new Label();
            sizeTrackBar = new TrackBar();
            sizeNumeric = new NumericUpDown();
            label2 = new Label();
            positionTrackBar = new TrackBar();
            positionNumeric = new NumericUpDown();
            label1 = new Label();
            groupBox2 = new GroupBox();
            flairRadio = new RadioButton();
            bonusRadio = new RadioButton();
            noBonusRadio = new RadioButton();
            endHoldCheck = new CheckBox();
            endChartButton = new Button();
            holdButton = new Button();
            chainButton = new Button();
            blueButton = new Button();
            redButton = new Button();
            greenButton = new Button();
            orangeButton = new Button();
            tapButton = new Button();
            gimmickTypeGroupBox = new GroupBox();
            removeMaskRadio = new RadioButton();
            reverseButton = new Button();
            addMaskRadio = new RadioButton();
            stopButton = new Button();
            hiSpeedButton = new Button();
            timeSigButton = new Button();
            bpmChangeButton = new Button();
            maskButton = new Button();
            groupBox4 = new GroupBox();
            centerMaskRadio = new RadioButton();
            clockwiseMaskRadio = new RadioButton();
            cClockwiseMaskRadio = new RadioButton();
            groupBox5 = new GroupBox();
            currentSelectionLabel = new Label();
            playbackGroupBox = new GroupBox();
            songFileLabel = new Label();
            labelSpeed = new Label();
            trackBarSpeed = new TrackBar();
            trackBarVolume = new TrackBar();
            labelVolume = new Label();
            label20 = new Label();
            songTrackBar = new TrackBar();
            selectSongButton = new Button();
            playButton = new Button();
            openSongDialog = new OpenFileDialog();
            updateTimer = new System.Windows.Forms.Timer(components);
            groupBox9 = new GroupBox();
            label21 = new Label();
            visualHispeedNumeric = new NumericUpDown();
            insertButton = new Button();
            fileToolStripMenuItem = new ToolStripMenuItem();
            newToolStripMenuItem = new ToolStripMenuItem();
            openToolStripMenuItem = new ToolStripMenuItem();
            saveToolStripMenuItem = new ToolStripMenuItem();
            saveAsToolStripMenuItem = new ToolStripMenuItem();
            exitToolStripMenuItem = new ToolStripMenuItem();
            viewToolStripMenuItem = new ToolStripMenuItem();
            showCursorToolStripMenuItem = new ToolStripMenuItem();
            showCursorDuringPlaybackToolStripMenuItem = new ToolStripMenuItem();
            highlightViewedNoteToolStripMenuItem = new ToolStripMenuItem();
            selectLastInsertedNoteToolStripMenuItem = new ToolStripMenuItem();
            showGimmicksInCircleViewToolStripMenuItem = new ToolStripMenuItem();
            showGimmicksDuringPlaybackToolStripMenuItem = new ToolStripMenuItem();
            chartToolStripMenuItem = new ToolStripMenuItem();
            initialChartSettingsToolStripMenuItem = new ToolStripMenuItem();
            aboutToolStripMenuItem = new ToolStripMenuItem();
            menuStrip = new MenuStrip();
            editToolStripMenuItem = new ToolStripMenuItem();
            undoToolStripMenuItem = new ToolStripMenuItem();
            redoToolStripMenuItem = new ToolStripMenuItem();
            groupBox6 = new GroupBox();
            gimmickJumpToCurrTimeButton = new Button();
            gimmickDeleteButton = new Button();
            gimmickEditButton = new Button();
            gimmickBeatLabel = new Label();
            gimmickValueLabel = new Label();
            gimmickTypeLabel = new Label();
            gimmickMeasureLabel = new Label();
            label8 = new Label();
            label7 = new Label();
            label6 = new Label();
            label5 = new Label();
            gimmickNextButton = new Button();
            gimmickPrevButton = new Button();
            noteViewGroupBox = new GroupBox();
            noteMaskLabel = new Label();
            label9 = new Label();
            noteSizeLabel = new Label();
            label17 = new Label();
            noteJumpToCurrTimeButton = new Button();
            noteDeleteSelectedButton = new Button();
            noteEditSelectedButton = new Button();
            noteBeatLabel = new Label();
            notePositionLabel = new Label();
            noteTypeLabel = new Label();
            noteMeasureLabel = new Label();
            label13 = new Label();
            label14 = new Label();
            label15 = new Label();
            label16 = new Label();
            noteNextButton = new Button();
            notePrevButton = new Button();
            autoSaveTimer = new System.Windows.Forms.Timer(components);
            groupBox3 = new GroupBox();
            notesOnBeat = new ListView();
            Type = new ColumnHeader();
            Position = new ColumnHeader();
            Size = new ColumnHeader();
            groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)beat2Numeric).BeginInit();
            ((System.ComponentModel.ISupportInitialize)beat1Numeric).BeginInit();
            ((System.ComponentModel.ISupportInitialize)measureNumeric).BeginInit();
            ((System.ComponentModel.ISupportInitialize)sizeTrackBar).BeginInit();
            ((System.ComponentModel.ISupportInitialize)sizeNumeric).BeginInit();
            ((System.ComponentModel.ISupportInitialize)positionTrackBar).BeginInit();
            ((System.ComponentModel.ISupportInitialize)positionNumeric).BeginInit();
            groupBox2.SuspendLayout();
            gimmickTypeGroupBox.SuspendLayout();
            groupBox4.SuspendLayout();
            groupBox5.SuspendLayout();
            playbackGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)trackBarSpeed).BeginInit();
            ((System.ComponentModel.ISupportInitialize)trackBarVolume).BeginInit();
            ((System.ComponentModel.ISupportInitialize)songTrackBar).BeginInit();
            groupBox9.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)visualHispeedNumeric).BeginInit();
            menuStrip.SuspendLayout();
            groupBox6.SuspendLayout();
            noteViewGroupBox.SuspendLayout();
            groupBox3.SuspendLayout();
            SuspendLayout();
            // 
            // openFileDialog
            // 
            openFileDialog.Filter = "MER files|*.mer";
            openFileDialog.Title = "Select chart file to open";
            // 
            // saveFileDialog
            // 
            saveFileDialog.DefaultExt = "*.mer";
            saveFileDialog.Filter = "MER files|*.mer";
            // 
            // circlePanel
            // 
            circlePanel.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            circlePanel.Location = new Point(257, 40);
            circlePanel.Name = "circlePanel";
            circlePanel.Size = new Size(611, 524);
            circlePanel.TabIndex = 2;
            circlePanel.Paint += circlePanel_Paint;
            circlePanel.MouseDown += circlePanel_MouseDown;
            circlePanel.MouseMove += circlePanel_MouseMove;
            circlePanel.MouseUp += circlePanel_MouseUp;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(label4);
            groupBox1.Controls.Add(beat2Numeric);
            groupBox1.Controls.Add(beat1Numeric);
            groupBox1.Controls.Add(measureNumeric);
            groupBox1.Controls.Add(label3);
            groupBox1.Controls.Add(sizeTrackBar);
            groupBox1.Controls.Add(sizeNumeric);
            groupBox1.Controls.Add(label2);
            groupBox1.Controls.Add(positionTrackBar);
            groupBox1.Controls.Add(positionNumeric);
            groupBox1.Controls.Add(label1);
            groupBox1.Location = new Point(12, 446);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(239, 160);
            groupBox1.TabIndex = 3;
            groupBox1.TabStop = false;
            groupBox1.Text = "Current Note Settings";
            // 
            // label4
            // 
            label4.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            label4.AutoSize = true;
            label4.Location = new Point(175, 131);
            label4.Name = "label4";
            label4.Size = new Size(12, 15);
            label4.TabIndex = 10;
            label4.Text = "/";
            // 
            // beat2Numeric
            // 
            beat2Numeric.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            beat2Numeric.Location = new Point(193, 129);
            beat2Numeric.Maximum = new decimal(new int[] { 1920, 0, 0, 0 });
            beat2Numeric.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            beat2Numeric.Name = "beat2Numeric";
            beat2Numeric.Size = new Size(38, 23);
            beat2Numeric.TabIndex = 9;
            beat2Numeric.Value = new decimal(new int[] { 16, 0, 0, 0 });
            beat2Numeric.ValueChanged += beat2Numeric_ValueChanged;
            // 
            // beat1Numeric
            // 
            beat1Numeric.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            beat1Numeric.Location = new Point(131, 129);
            beat1Numeric.Maximum = new decimal(new int[] { 1920, 0, 0, 0 });
            beat1Numeric.Minimum = new decimal(new int[] { 1, 0, 0, int.MinValue });
            beat1Numeric.Name = "beat1Numeric";
            beat1Numeric.Size = new Size(38, 23);
            beat1Numeric.TabIndex = 8;
            beat1Numeric.ValueChanged += beat1Numeric_ValueChanged;
            // 
            // measureNumeric
            // 
            measureNumeric.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            measureNumeric.Location = new Point(6, 129);
            measureNumeric.Maximum = new decimal(new int[] { 9999, 0, 0, 0 });
            measureNumeric.Name = "measureNumeric";
            measureNumeric.Size = new Size(119, 23);
            measureNumeric.TabIndex = 7;
            measureNumeric.ValueChanged += measureNumeric_ValueChanged;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(6, 111);
            label3.Name = "label3";
            label3.Size = new Size(55, 15);
            label3.TabIndex = 6;
            label3.Text = "Measure:";
            // 
            // sizeTrackBar
            // 
            sizeTrackBar.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            sizeTrackBar.Location = new Point(50, 81);
            sizeTrackBar.Maximum = 60;
            sizeTrackBar.Minimum = 4;
            sizeTrackBar.Name = "sizeTrackBar";
            sizeTrackBar.Size = new Size(183, 45);
            sizeTrackBar.TabIndex = 5;
            sizeTrackBar.TickStyle = TickStyle.None;
            sizeTrackBar.Value = 4;
            sizeTrackBar.ValueChanged += sizeTrackBar_ValueChanged;
            // 
            // sizeNumeric
            // 
            sizeNumeric.Location = new Point(6, 81);
            sizeNumeric.Maximum = new decimal(new int[] { 60, 0, 0, 0 });
            sizeNumeric.Minimum = new decimal(new int[] { 4, 0, 0, 0 });
            sizeNumeric.Name = "sizeNumeric";
            sizeNumeric.Size = new Size(38, 23);
            sizeNumeric.TabIndex = 4;
            sizeNumeric.Value = new decimal(new int[] { 4, 0, 0, 0 });
            sizeNumeric.ValueChanged += sizeNumeric_ValueChanged;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(6, 63);
            label2.Name = "label2";
            label2.Size = new Size(30, 15);
            label2.TabIndex = 3;
            label2.Text = "Size:";
            // 
            // positionTrackBar
            // 
            positionTrackBar.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            positionTrackBar.Location = new Point(50, 37);
            positionTrackBar.Maximum = 59;
            positionTrackBar.Name = "positionTrackBar";
            positionTrackBar.Size = new Size(183, 45);
            positionTrackBar.TabIndex = 2;
            positionTrackBar.TickStyle = TickStyle.None;
            positionTrackBar.ValueChanged += positionTrackBar_ValueChanged;
            // 
            // positionNumeric
            // 
            positionNumeric.Location = new Point(6, 37);
            positionNumeric.Maximum = new decimal(new int[] { 59, 0, 0, 0 });
            positionNumeric.Name = "positionNumeric";
            positionNumeric.Size = new Size(38, 23);
            positionNumeric.TabIndex = 1;
            positionNumeric.ValueChanged += positionNumeric_ValueChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(6, 19);
            label1.Name = "label1";
            label1.Size = new Size(53, 15);
            label1.TabIndex = 0;
            label1.Text = "Position:";
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(flairRadio);
            groupBox2.Controls.Add(bonusRadio);
            groupBox2.Controls.Add(noBonusRadio);
            groupBox2.Controls.Add(endHoldCheck);
            groupBox2.Controls.Add(endChartButton);
            groupBox2.Controls.Add(holdButton);
            groupBox2.Controls.Add(chainButton);
            groupBox2.Controls.Add(blueButton);
            groupBox2.Controls.Add(redButton);
            groupBox2.Controls.Add(greenButton);
            groupBox2.Controls.Add(orangeButton);
            groupBox2.Controls.Add(tapButton);
            groupBox2.Location = new Point(12, 27);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(109, 358);
            groupBox2.TabIndex = 4;
            groupBox2.TabStop = false;
            groupBox2.Text = "Note Types";
            // 
            // flairRadio
            // 
            flairRadio.AutoSize = true;
            flairRadio.Location = new Point(6, 329);
            flairRadio.Name = "flairRadio";
            flairRadio.Size = new Size(94, 19);
            flairRadio.TabIndex = 16;
            flairRadio.Text = "R Note (Flair)";
            flairRadio.UseVisualStyleBackColor = true;
            flairRadio.CheckedChanged += BonusRadioCheck;
            // 
            // bonusRadio
            // 
            bonusRadio.AutoSize = true;
            bonusRadio.Location = new Point(6, 304);
            bonusRadio.Name = "bonusRadio";
            bonusRadio.Size = new Size(79, 19);
            bonusRadio.TabIndex = 15;
            bonusRadio.Text = "Bonus Get";
            bonusRadio.UseVisualStyleBackColor = true;
            bonusRadio.CheckedChanged += BonusRadioCheck;
            // 
            // noBonusRadio
            // 
            noBonusRadio.AutoSize = true;
            noBonusRadio.Checked = true;
            noBonusRadio.Location = new Point(6, 279);
            noBonusRadio.Name = "noBonusRadio";
            noBonusRadio.Size = new Size(77, 19);
            noBonusRadio.TabIndex = 14;
            noBonusRadio.TabStop = true;
            noBonusRadio.Text = "No Bonus";
            noBonusRadio.UseVisualStyleBackColor = true;
            noBonusRadio.CheckedChanged += BonusRadioCheck;
            // 
            // endHoldCheck
            // 
            endHoldCheck.AutoSize = true;
            endHoldCheck.Location = new Point(6, 254);
            endHoldCheck.Name = "endHoldCheck";
            endHoldCheck.Size = new Size(75, 19);
            endHoldCheck.TabIndex = 13;
            endHoldCheck.Text = "End Hold";
            endHoldCheck.UseVisualStyleBackColor = true;
            endHoldCheck.CheckedChanged += endHoldCheck_CheckedChanged;
            // 
            // endChartButton
            // 
            endChartButton.BackColor = Color.Black;
            endChartButton.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point);
            endChartButton.ForeColor = Color.White;
            endChartButton.Location = new Point(6, 225);
            endChartButton.Name = "endChartButton";
            endChartButton.Size = new Size(97, 23);
            endChartButton.TabIndex = 12;
            endChartButton.Text = "End of Chart";
            endChartButton.UseVisualStyleBackColor = false;
            endChartButton.Click += endChartButton_Click;
            // 
            // holdButton
            // 
            holdButton.BackColor = Color.Yellow;
            holdButton.Location = new Point(6, 196);
            holdButton.Name = "holdButton";
            holdButton.Size = new Size(97, 23);
            holdButton.TabIndex = 11;
            holdButton.Text = "Hold";
            holdButton.UseVisualStyleBackColor = false;
            holdButton.Click += holdButton_Click;
            // 
            // chainButton
            // 
            chainButton.BackColor = Color.FromArgb(204, 190, 45);
            chainButton.Location = new Point(6, 167);
            chainButton.Name = "chainButton";
            chainButton.Size = new Size(97, 23);
            chainButton.TabIndex = 10;
            chainButton.Text = "Chain";
            chainButton.UseVisualStyleBackColor = false;
            chainButton.Click += chainButton_Click;
            // 
            // blueButton
            // 
            blueButton.BackColor = Color.Cyan;
            blueButton.ForeColor = SystemColors.ControlText;
            blueButton.Location = new Point(6, 138);
            blueButton.Name = "blueButton";
            blueButton.Size = new Size(97, 23);
            blueButton.TabIndex = 9;
            blueButton.Text = "↓ Snap";
            blueButton.UseVisualStyleBackColor = false;
            blueButton.Click += blueButton_Click;
            // 
            // redButton
            // 
            redButton.BackColor = Color.Red;
            redButton.ForeColor = Color.White;
            redButton.Location = new Point(6, 109);
            redButton.Name = "redButton";
            redButton.Size = new Size(97, 23);
            redButton.TabIndex = 8;
            redButton.Text = "↑ Snap";
            redButton.UseVisualStyleBackColor = false;
            redButton.Click += redButton_Click;
            // 
            // greenButton
            // 
            greenButton.BackColor = Color.Lime;
            greenButton.Location = new Point(6, 80);
            greenButton.Name = "greenButton";
            greenButton.Size = new Size(97, 23);
            greenButton.TabIndex = 7;
            greenButton.Text = "⤿ Slide";
            greenButton.UseVisualStyleBackColor = false;
            greenButton.Click += greenButton_Click;
            // 
            // orangeButton
            // 
            orangeButton.BackColor = Color.Orange;
            orangeButton.Location = new Point(6, 51);
            orangeButton.Name = "orangeButton";
            orangeButton.Size = new Size(97, 23);
            orangeButton.TabIndex = 6;
            orangeButton.Text = "⤾ Slide";
            orangeButton.UseVisualStyleBackColor = false;
            orangeButton.Click += orangeButton_Click;
            // 
            // tapButton
            // 
            tapButton.BackColor = Color.Fuchsia;
            tapButton.Location = new Point(6, 22);
            tapButton.Name = "tapButton";
            tapButton.Size = new Size(97, 23);
            tapButton.TabIndex = 5;
            tapButton.Text = "Touch";
            tapButton.UseVisualStyleBackColor = false;
            tapButton.Click += tapButton_Click;
            // 
            // gimmickTypeGroupBox
            // 
            gimmickTypeGroupBox.Controls.Add(removeMaskRadio);
            gimmickTypeGroupBox.Controls.Add(reverseButton);
            gimmickTypeGroupBox.Controls.Add(addMaskRadio);
            gimmickTypeGroupBox.Controls.Add(stopButton);
            gimmickTypeGroupBox.Controls.Add(hiSpeedButton);
            gimmickTypeGroupBox.Controls.Add(timeSigButton);
            gimmickTypeGroupBox.Controls.Add(bpmChangeButton);
            gimmickTypeGroupBox.Controls.Add(maskButton);
            gimmickTypeGroupBox.Location = new Point(127, 27);
            gimmickTypeGroupBox.Name = "gimmickTypeGroupBox";
            gimmickTypeGroupBox.Size = new Size(124, 252);
            gimmickTypeGroupBox.TabIndex = 5;
            gimmickTypeGroupBox.TabStop = false;
            gimmickTypeGroupBox.Text = "Gimmick Types";
            // 
            // removeMaskRadio
            // 
            removeMaskRadio.AutoSize = true;
            removeMaskRadio.Location = new Point(6, 222);
            removeMaskRadio.Name = "removeMaskRadio";
            removeMaskRadio.Size = new Size(99, 19);
            removeMaskRadio.TabIndex = 18;
            removeMaskRadio.Text = "Remove Mask";
            removeMaskRadio.UseVisualStyleBackColor = true;
            removeMaskRadio.CheckedChanged += maskRatio_CheckChanged;
            // 
            // reverseButton
            // 
            reverseButton.Location = new Point(6, 167);
            reverseButton.Name = "reverseButton";
            reverseButton.Size = new Size(112, 23);
            reverseButton.TabIndex = 5;
            reverseButton.Text = "Reverse";
            reverseButton.UseVisualStyleBackColor = true;
            reverseButton.Click += reverseButton_Click;
            // 
            // addMaskRadio
            // 
            addMaskRadio.AutoSize = true;
            addMaskRadio.Checked = true;
            addMaskRadio.Location = new Point(6, 197);
            addMaskRadio.Name = "addMaskRadio";
            addMaskRadio.Size = new Size(78, 19);
            addMaskRadio.TabIndex = 17;
            addMaskRadio.TabStop = true;
            addMaskRadio.Text = "Add Mask";
            addMaskRadio.UseVisualStyleBackColor = true;
            addMaskRadio.CheckedChanged += maskRatio_CheckChanged;
            // 
            // stopButton
            // 
            stopButton.Location = new Point(6, 138);
            stopButton.Name = "stopButton";
            stopButton.Size = new Size(112, 23);
            stopButton.TabIndex = 4;
            stopButton.Text = "Stop";
            stopButton.UseVisualStyleBackColor = true;
            stopButton.Click += stopButton_Click;
            // 
            // hiSpeedButton
            // 
            hiSpeedButton.Location = new Point(6, 109);
            hiSpeedButton.Name = "hiSpeedButton";
            hiSpeedButton.Size = new Size(112, 23);
            hiSpeedButton.TabIndex = 3;
            hiSpeedButton.Text = "Hi-Speed";
            hiSpeedButton.UseVisualStyleBackColor = true;
            hiSpeedButton.Click += hiSpeedButton_Click;
            // 
            // timeSigButton
            // 
            timeSigButton.Location = new Point(6, 80);
            timeSigButton.Name = "timeSigButton";
            timeSigButton.Size = new Size(112, 23);
            timeSigButton.TabIndex = 2;
            timeSigButton.Text = "Time Signature";
            timeSigButton.UseVisualStyleBackColor = true;
            timeSigButton.Click += timeSigButton_Click;
            // 
            // bpmChangeButton
            // 
            bpmChangeButton.Location = new Point(6, 51);
            bpmChangeButton.Name = "bpmChangeButton";
            bpmChangeButton.Size = new Size(112, 23);
            bpmChangeButton.TabIndex = 1;
            bpmChangeButton.Text = "BPM Change";
            bpmChangeButton.UseVisualStyleBackColor = true;
            bpmChangeButton.Click += bpmChangeButton_Click;
            // 
            // maskButton
            // 
            maskButton.Location = new Point(6, 22);
            maskButton.Name = "maskButton";
            maskButton.Size = new Size(112, 23);
            maskButton.TabIndex = 0;
            maskButton.Text = "Mask";
            maskButton.UseVisualStyleBackColor = true;
            maskButton.Click += maskButton_Click;
            // 
            // groupBox4
            // 
            groupBox4.Controls.Add(centerMaskRadio);
            groupBox4.Controls.Add(clockwiseMaskRadio);
            groupBox4.Controls.Add(cClockwiseMaskRadio);
            groupBox4.Location = new Point(127, 285);
            groupBox4.Name = "groupBox4";
            groupBox4.Size = new Size(124, 100);
            groupBox4.TabIndex = 19;
            groupBox4.TabStop = false;
            groupBox4.Text = "Mask Setting";
            // 
            // centerMaskRadio
            // 
            centerMaskRadio.AutoSize = true;
            centerMaskRadio.Location = new Point(6, 72);
            centerMaskRadio.Name = "centerMaskRadio";
            centerMaskRadio.Size = new Size(91, 19);
            centerMaskRadio.TabIndex = 19;
            centerMaskRadio.Text = "From Center";
            centerMaskRadio.UseVisualStyleBackColor = true;
            centerMaskRadio.CheckedChanged += maskRatio_CheckChanged;
            // 
            // clockwiseMaskRadio
            // 
            clockwiseMaskRadio.AutoSize = true;
            clockwiseMaskRadio.Checked = true;
            clockwiseMaskRadio.Location = new Point(6, 22);
            clockwiseMaskRadio.Name = "clockwiseMaskRadio";
            clockwiseMaskRadio.Size = new Size(78, 19);
            clockwiseMaskRadio.TabIndex = 17;
            clockwiseMaskRadio.TabStop = true;
            clockwiseMaskRadio.Text = "Clockwise";
            clockwiseMaskRadio.UseVisualStyleBackColor = true;
            clockwiseMaskRadio.CheckedChanged += maskRatio_CheckChanged;
            // 
            // cClockwiseMaskRadio
            // 
            cClockwiseMaskRadio.AutoSize = true;
            cClockwiseMaskRadio.Location = new Point(6, 47);
            cClockwiseMaskRadio.Name = "cClockwiseMaskRadio";
            cClockwiseMaskRadio.Size = new Size(91, 19);
            cClockwiseMaskRadio.TabIndex = 18;
            cClockwiseMaskRadio.Text = "C-Clockwise";
            cClockwiseMaskRadio.UseVisualStyleBackColor = true;
            cClockwiseMaskRadio.CheckedChanged += maskRatio_CheckChanged;
            // 
            // groupBox5
            // 
            groupBox5.Controls.Add(currentSelectionLabel);
            groupBox5.Location = new Point(12, 392);
            groupBox5.Name = "groupBox5";
            groupBox5.Size = new Size(239, 48);
            groupBox5.TabIndex = 20;
            groupBox5.TabStop = false;
            groupBox5.Text = "Current Selection";
            // 
            // currentSelectionLabel
            // 
            currentSelectionLabel.AutoSize = true;
            currentSelectionLabel.Font = new Font("Segoe UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            currentSelectionLabel.Location = new Point(6, 19);
            currentSelectionLabel.Name = "currentSelectionLabel";
            currentSelectionLabel.Size = new Size(48, 20);
            currentSelectionLabel.TabIndex = 21;
            currentSelectionLabel.Text = "Touch";
            // 
            // playbackGroupBox
            // 
            playbackGroupBox.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            playbackGroupBox.Controls.Add(songFileLabel);
            playbackGroupBox.Controls.Add(labelSpeed);
            playbackGroupBox.Controls.Add(trackBarSpeed);
            playbackGroupBox.Controls.Add(trackBarVolume);
            playbackGroupBox.Controls.Add(labelVolume);
            playbackGroupBox.Controls.Add(label20);
            playbackGroupBox.Controls.Add(songTrackBar);
            playbackGroupBox.Controls.Add(selectSongButton);
            playbackGroupBox.Controls.Add(playButton);
            playbackGroupBox.Location = new Point(12, 657);
            playbackGroupBox.Name = "playbackGroupBox";
            playbackGroupBox.Size = new Size(736, 118);
            playbackGroupBox.TabIndex = 32;
            playbackGroupBox.TabStop = false;
            playbackGroupBox.Text = "Playback";
            // 
            // songFileLabel
            // 
            songFileLabel.AutoSize = true;
            songFileLabel.Location = new Point(98, 81);
            songFileLabel.Name = "songFileLabel";
            songFileLabel.Size = new Size(134, 15);
            songFileLabel.TabIndex = 33;
            songFileLabel.Text = "Select File (*.ogg, *.wav)";
            // 
            // labelSpeed
            // 
            labelSpeed.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            labelSpeed.AutoSize = true;
            labelSpeed.Location = new Point(311, 51);
            labelSpeed.Margin = new Padding(2, 0, 2, 0);
            labelSpeed.Name = "labelSpeed";
            labelSpeed.Size = new Size(77, 15);
            labelSpeed.TabIndex = 36;
            labelSpeed.Text = "Speed (x1.00)";
            // 
            // trackBarSpeed
            // 
            trackBarSpeed.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            trackBarSpeed.LargeChange = 1;
            trackBarSpeed.Location = new Point(392, 52);
            trackBarSpeed.Margin = new Padding(2);
            trackBarSpeed.Maximum = 4;
            trackBarSpeed.Minimum = 1;
            trackBarSpeed.Name = "trackBarSpeed";
            trackBarSpeed.Size = new Size(137, 45);
            trackBarSpeed.TabIndex = 35;
            trackBarSpeed.Value = 4;
            trackBarSpeed.ValueChanged += trackBarSpeed_ValueChanged;
            // 
            // trackBarVolume
            // 
            trackBarVolume.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            trackBarVolume.Location = new Point(588, 51);
            trackBarVolume.Margin = new Padding(2);
            trackBarVolume.Maximum = 100;
            trackBarVolume.Name = "trackBarVolume";
            trackBarVolume.Size = new Size(137, 45);
            trackBarVolume.TabIndex = 34;
            trackBarVolume.TickFrequency = 50;
            trackBarVolume.Value = 100;
            trackBarVolume.ValueChanged += trackBarVolume_ValueChanged;
            trackBarVolume.MouseDown += trackBarVolume_MouseDown;
            // 
            // labelVolume
            // 
            labelVolume.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            labelVolume.AutoSize = true;
            labelVolume.Location = new Point(537, 51);
            labelVolume.Margin = new Padding(2, 0, 2, 0);
            labelVolume.Name = "labelVolume";
            labelVolume.Size = new Size(47, 15);
            labelVolume.TabIndex = 0;
            labelVolume.Text = "Volume";
            // 
            // label20
            // 
            label20.AutoSize = true;
            label20.Font = new Font("Segoe UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            label20.Location = new Point(6, 77);
            label20.Name = "label20";
            label20.Size = new Size(73, 20);
            label20.TabIndex = 33;
            label20.Text = "Song File:";
            // 
            // songTrackBar
            // 
            songTrackBar.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            songTrackBar.Location = new Point(98, 22);
            songTrackBar.Name = "songTrackBar";
            songTrackBar.Size = new Size(627, 45);
            songTrackBar.TabIndex = 2;
            songTrackBar.TickStyle = TickStyle.None;
            songTrackBar.ValueChanged += songTrackBar_ValueChanged;
            songTrackBar.MouseDown += songTrackBar_MouseDown;
            // 
            // selectSongButton
            // 
            selectSongButton.Location = new Point(6, 51);
            selectSongButton.Name = "selectSongButton";
            selectSongButton.Size = new Size(86, 23);
            selectSongButton.TabIndex = 1;
            selectSongButton.Text = "Select Song";
            selectSongButton.UseVisualStyleBackColor = true;
            selectSongButton.Click += selectSongButton_Click;
            // 
            // playButton
            // 
            playButton.Location = new Point(6, 22);
            playButton.Name = "playButton";
            playButton.Size = new Size(86, 23);
            playButton.TabIndex = 0;
            playButton.Text = "Play";
            playButton.UseVisualStyleBackColor = true;
            playButton.Click += playButton_Click;
            // 
            // openSongDialog
            // 
            openSongDialog.Filter = "Audio Files (*.ogg;*.wav)|*.ogg;*.wav|All Files (*.*)|*.*";
            // 
            // updateTimer
            // 
            updateTimer.Interval = 20;
            updateTimer.Tick += updateTimer_Tick;
            // 
            // groupBox9
            // 
            groupBox9.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            groupBox9.Controls.Add(label21);
            groupBox9.Controls.Add(visualHispeedNumeric);
            groupBox9.Location = new Point(754, 657);
            groupBox9.Name = "groupBox9";
            groupBox9.Size = new Size(114, 118);
            groupBox9.TabIndex = 0;
            groupBox9.TabStop = false;
            groupBox9.Text = "Visual Settings";
            // 
            // label21
            // 
            label21.AutoSize = true;
            label21.Location = new Point(6, 19);
            label21.Name = "label21";
            label21.Size = new Size(59, 15);
            label21.TabIndex = 11;
            label21.Text = "Hi-Speed:";
            // 
            // visualHispeedNumeric
            // 
            visualHispeedNumeric.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            visualHispeedNumeric.DecimalPlaces = 1;
            visualHispeedNumeric.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            visualHispeedNumeric.Increment = new decimal(new int[] { 1, 0, 0, 65536 });
            visualHispeedNumeric.Location = new Point(6, 37);
            visualHispeedNumeric.Maximum = new decimal(new int[] { 500, 0, 0, 0 });
            visualHispeedNumeric.Minimum = new decimal(new int[] { 1, 0, 0, 65536 });
            visualHispeedNumeric.Name = "visualHispeedNumeric";
            visualHispeedNumeric.Size = new Size(102, 29);
            visualHispeedNumeric.TabIndex = 11;
            visualHispeedNumeric.TextAlign = HorizontalAlignment.Center;
            visualHispeedNumeric.Value = new decimal(new int[] { 15, 0, 0, 65536 });
            visualHispeedNumeric.ValueChanged += visualHispeedNumeric_ValueChanged;
            // 
            // insertButton
            // 
            insertButton.Font = new Font("Segoe UI", 11F, FontStyle.Regular, GraphicsUnit.Point);
            insertButton.Location = new Point(12, 612);
            insertButton.Name = "insertButton";
            insertButton.Size = new Size(239, 39);
            insertButton.TabIndex = 12;
            insertButton.Text = "Insert Object (I)";
            insertButton.UseVisualStyleBackColor = true;
            insertButton.Click += insertButton_Click;
            // 
            // fileToolStripMenuItem
            // 
            fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { newToolStripMenuItem, openToolStripMenuItem, saveToolStripMenuItem, saveAsToolStripMenuItem, exitToolStripMenuItem });
            fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            fileToolStripMenuItem.Size = new Size(37, 20);
            fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            newToolStripMenuItem.Name = "newToolStripMenuItem";
            newToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.N;
            newToolStripMenuItem.Size = new Size(186, 22);
            newToolStripMenuItem.Text = "New";
            newToolStripMenuItem.Click += newToolStripMenuItem_Click;
            // 
            // openToolStripMenuItem
            // 
            openToolStripMenuItem.Name = "openToolStripMenuItem";
            openToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.O;
            openToolStripMenuItem.Size = new Size(186, 22);
            openToolStripMenuItem.Text = "Open";
            openToolStripMenuItem.Click += openToolStripMenuItem_Click;
            // 
            // saveToolStripMenuItem
            // 
            saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            saveToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.S;
            saveToolStripMenuItem.Size = new Size(186, 22);
            saveToolStripMenuItem.Text = "Save";
            saveToolStripMenuItem.Click += saveToolStripMenuItem_Click;
            // 
            // saveAsToolStripMenuItem
            // 
            saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            saveAsToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.Shift | Keys.S;
            saveAsToolStripMenuItem.Size = new Size(186, 22);
            saveAsToolStripMenuItem.Text = "Save As";
            saveAsToolStripMenuItem.Click += saveAsToolStripMenuItem_Click;
            // 
            // exitToolStripMenuItem
            // 
            exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            exitToolStripMenuItem.Size = new Size(186, 22);
            exitToolStripMenuItem.Text = "Exit";
            exitToolStripMenuItem.Click += exitToolStripMenuItem_Click;
            // 
            // viewToolStripMenuItem
            // 
            viewToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { showCursorToolStripMenuItem, showCursorDuringPlaybackToolStripMenuItem, highlightViewedNoteToolStripMenuItem, selectLastInsertedNoteToolStripMenuItem, showGimmicksInCircleViewToolStripMenuItem, showGimmicksDuringPlaybackToolStripMenuItem });
            viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            viewToolStripMenuItem.Size = new Size(44, 20);
            viewToolStripMenuItem.Text = "View";
            // 
            // showCursorToolStripMenuItem
            // 
            showCursorToolStripMenuItem.Checked = true;
            showCursorToolStripMenuItem.CheckOnClick = true;
            showCursorToolStripMenuItem.CheckState = CheckState.Checked;
            showCursorToolStripMenuItem.Name = "showCursorToolStripMenuItem";
            showCursorToolStripMenuItem.Size = new Size(248, 22);
            showCursorToolStripMenuItem.Text = "Show Cursor";
            showCursorToolStripMenuItem.Click += showCursorToolStripMenuItem_Click;
            // 
            // showCursorDuringPlaybackToolStripMenuItem
            // 
            showCursorDuringPlaybackToolStripMenuItem.Name = "showCursorDuringPlaybackToolStripMenuItem";
            showCursorDuringPlaybackToolStripMenuItem.Size = new Size(248, 22);
            showCursorDuringPlaybackToolStripMenuItem.Text = "Show Cursor During Playback";
            // 
            // highlightViewedNoteToolStripMenuItem
            // 
            highlightViewedNoteToolStripMenuItem.Checked = true;
            highlightViewedNoteToolStripMenuItem.CheckOnClick = true;
            highlightViewedNoteToolStripMenuItem.CheckState = CheckState.Checked;
            highlightViewedNoteToolStripMenuItem.Name = "highlightViewedNoteToolStripMenuItem";
            highlightViewedNoteToolStripMenuItem.Size = new Size(248, 22);
            highlightViewedNoteToolStripMenuItem.Text = "Highlight Viewed Note";
            // 
            // selectLastInsertedNoteToolStripMenuItem
            // 
            selectLastInsertedNoteToolStripMenuItem.Checked = true;
            selectLastInsertedNoteToolStripMenuItem.CheckOnClick = true;
            selectLastInsertedNoteToolStripMenuItem.CheckState = CheckState.Checked;
            selectLastInsertedNoteToolStripMenuItem.Name = "selectLastInsertedNoteToolStripMenuItem";
            selectLastInsertedNoteToolStripMenuItem.Size = new Size(248, 22);
            selectLastInsertedNoteToolStripMenuItem.Text = "Select Last Inserted Note";
            // 
            // showGimmicksInCircleViewToolStripMenuItem
            // 
            showGimmicksInCircleViewToolStripMenuItem.Checked = true;
            showGimmicksInCircleViewToolStripMenuItem.CheckOnClick = true;
            showGimmicksInCircleViewToolStripMenuItem.CheckState = CheckState.Checked;
            showGimmicksInCircleViewToolStripMenuItem.Name = "showGimmicksInCircleViewToolStripMenuItem";
            showGimmicksInCircleViewToolStripMenuItem.Size = new Size(248, 22);
            showGimmicksInCircleViewToolStripMenuItem.Text = "Show Gimmicks In Circle View";
            showGimmicksInCircleViewToolStripMenuItem.Click += showGimmicksInCircleViewToolStripMenuItem_Click;
            // 
            // showGimmicksDuringPlaybackToolStripMenuItem
            // 
            showGimmicksDuringPlaybackToolStripMenuItem.CheckOnClick = true;
            showGimmicksDuringPlaybackToolStripMenuItem.Name = "showGimmicksDuringPlaybackToolStripMenuItem";
            showGimmicksDuringPlaybackToolStripMenuItem.Size = new Size(248, 22);
            showGimmicksDuringPlaybackToolStripMenuItem.Text = "Show Gimmicks During Playback";
            showGimmicksDuringPlaybackToolStripMenuItem.Click += showGimmicksDuringPlaybackToolStripMenuItem_Click;
            // 
            // chartToolStripMenuItem
            // 
            chartToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { initialChartSettingsToolStripMenuItem });
            chartToolStripMenuItem.Name = "chartToolStripMenuItem";
            chartToolStripMenuItem.Size = new Size(48, 20);
            chartToolStripMenuItem.Text = "Chart";
            // 
            // initialChartSettingsToolStripMenuItem
            // 
            initialChartSettingsToolStripMenuItem.Name = "initialChartSettingsToolStripMenuItem";
            initialChartSettingsToolStripMenuItem.Size = new Size(180, 22);
            initialChartSettingsToolStripMenuItem.Text = "Initial Chart Settings";
            initialChartSettingsToolStripMenuItem.Click += initialChartSettingsToolStripMenuItem_Click;
            // 
            // aboutToolStripMenuItem
            // 
            aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            aboutToolStripMenuItem.Size = new Size(52, 20);
            aboutToolStripMenuItem.Text = "About";
            aboutToolStripMenuItem.Click += aboutToolStripMenuItem_Click;
            // 
            // menuStrip
            // 
            menuStrip.BackColor = SystemColors.ControlDark;
            menuStrip.Font = new Font("Segoe UI", 9F, FontStyle.Regular, GraphicsUnit.Point);
            menuStrip.ImageScalingSize = new Size(24, 24);
            menuStrip.Items.AddRange(new ToolStripItem[] { fileToolStripMenuItem, editToolStripMenuItem, viewToolStripMenuItem, chartToolStripMenuItem, aboutToolStripMenuItem });
            menuStrip.Location = new Point(0, 0);
            menuStrip.Name = "menuStrip";
            menuStrip.Size = new Size(1142, 24);
            menuStrip.TabIndex = 0;
            menuStrip.Text = "menuStrip1";
            // 
            // editToolStripMenuItem
            // 
            editToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { undoToolStripMenuItem, redoToolStripMenuItem });
            editToolStripMenuItem.Name = "editToolStripMenuItem";
            editToolStripMenuItem.Size = new Size(39, 20);
            editToolStripMenuItem.Text = "Edit";
            // 
            // undoToolStripMenuItem
            // 
            undoToolStripMenuItem.Name = "undoToolStripMenuItem";
            undoToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.Z;
            undoToolStripMenuItem.Size = new Size(144, 22);
            undoToolStripMenuItem.Text = "Undo";
            undoToolStripMenuItem.Click += undoToolStripMenuItem_Click;
            // 
            // redoToolStripMenuItem
            // 
            redoToolStripMenuItem.Name = "redoToolStripMenuItem";
            redoToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.Y;
            redoToolStripMenuItem.Size = new Size(144, 22);
            redoToolStripMenuItem.Text = "Redo";
            redoToolStripMenuItem.Click += redoToolStripMenuItem_Click;
            // 
            // groupBox6
            // 
            groupBox6.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            groupBox6.Controls.Add(gimmickJumpToCurrTimeButton);
            groupBox6.Controls.Add(gimmickDeleteButton);
            groupBox6.Controls.Add(gimmickEditButton);
            groupBox6.Controls.Add(gimmickBeatLabel);
            groupBox6.Controls.Add(gimmickValueLabel);
            groupBox6.Controls.Add(gimmickTypeLabel);
            groupBox6.Controls.Add(gimmickMeasureLabel);
            groupBox6.Controls.Add(label8);
            groupBox6.Controls.Add(label7);
            groupBox6.Controls.Add(label6);
            groupBox6.Controls.Add(label5);
            groupBox6.Controls.Add(gimmickNextButton);
            groupBox6.Controls.Add(gimmickPrevButton);
            groupBox6.Location = new Point(874, 602);
            groupBox6.Name = "groupBox6";
            groupBox6.Size = new Size(256, 173);
            groupBox6.TabIndex = 33;
            groupBox6.TabStop = false;
            groupBox6.Text = "Gimmick View";
            // 
            // gimmickJumpToCurrTimeButton
            // 
            gimmickJumpToCurrTimeButton.Location = new Point(7, 48);
            gimmickJumpToCurrTimeButton.Name = "gimmickJumpToCurrTimeButton";
            gimmickJumpToCurrTimeButton.Size = new Size(243, 23);
            gimmickJumpToCurrTimeButton.TabIndex = 14;
            gimmickJumpToCurrTimeButton.Text = "Jump To Nearest Gimmick @ Current Time";
            gimmickJumpToCurrTimeButton.UseVisualStyleBackColor = true;
            gimmickJumpToCurrTimeButton.Click += gimmickJumpToCurrTimeButton_Click;
            // 
            // gimmickDeleteButton
            // 
            gimmickDeleteButton.ForeColor = Color.Red;
            gimmickDeleteButton.Location = new Point(134, 139);
            gimmickDeleteButton.Name = "gimmickDeleteButton";
            gimmickDeleteButton.Size = new Size(113, 23);
            gimmickDeleteButton.TabIndex = 11;
            gimmickDeleteButton.Text = "Delete Gimmick";
            gimmickDeleteButton.UseVisualStyleBackColor = true;
            gimmickDeleteButton.Click += gimmickDeleteButton_Click;
            // 
            // gimmickEditButton
            // 
            gimmickEditButton.Location = new Point(6, 139);
            gimmickEditButton.Name = "gimmickEditButton";
            gimmickEditButton.Size = new Size(113, 23);
            gimmickEditButton.TabIndex = 10;
            gimmickEditButton.Text = "Edit Gimmick";
            gimmickEditButton.UseVisualStyleBackColor = true;
            gimmickEditButton.Click += gimmickEditButton_Click;
            // 
            // gimmickBeatLabel
            // 
            gimmickBeatLabel.AutoSize = true;
            gimmickBeatLabel.Location = new Point(173, 78);
            gimmickBeatLabel.Name = "gimmickBeatLabel";
            gimmickBeatLabel.Size = new Size(36, 15);
            gimmickBeatLabel.TabIndex = 9;
            gimmickBeatLabel.Text = "None";
            // 
            // gimmickValueLabel
            // 
            gimmickValueLabel.AutoSize = true;
            gimmickValueLabel.Location = new Point(76, 120);
            gimmickValueLabel.Name = "gimmickValueLabel";
            gimmickValueLabel.Size = new Size(36, 15);
            gimmickValueLabel.TabIndex = 8;
            gimmickValueLabel.Text = "None";
            // 
            // gimmickTypeLabel
            // 
            gimmickTypeLabel.AutoSize = true;
            gimmickTypeLabel.Location = new Point(76, 99);
            gimmickTypeLabel.Name = "gimmickTypeLabel";
            gimmickTypeLabel.Size = new Size(36, 15);
            gimmickTypeLabel.TabIndex = 7;
            gimmickTypeLabel.Text = "None";
            // 
            // gimmickMeasureLabel
            // 
            gimmickMeasureLabel.AutoSize = true;
            gimmickMeasureLabel.Location = new Point(76, 78);
            gimmickMeasureLabel.Name = "gimmickMeasureLabel";
            gimmickMeasureLabel.Size = new Size(36, 15);
            gimmickMeasureLabel.TabIndex = 6;
            gimmickMeasureLabel.Text = "None";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label8.Location = new Point(128, 76);
            label8.Name = "label8";
            label8.Size = new Size(39, 17);
            label8.TabIndex = 5;
            label8.Text = "Beat:";
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label7.Location = new Point(24, 118);
            label7.Name = "label7";
            label7.Size = new Size(46, 17);
            label7.TabIndex = 4;
            label7.Text = "Value:";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label6.Location = new Point(29, 97);
            label6.Name = "label6";
            label6.Size = new Size(41, 17);
            label6.TabIndex = 3;
            label6.Text = "Type:";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label5.Location = new Point(6, 76);
            label5.Name = "label5";
            label5.Size = new Size(64, 17);
            label5.TabIndex = 2;
            label5.Text = "Measure:";
            // 
            // gimmickNextButton
            // 
            gimmickNextButton.Location = new Point(134, 19);
            gimmickNextButton.Name = "gimmickNextButton";
            gimmickNextButton.Size = new Size(116, 23);
            gimmickNextButton.TabIndex = 1;
            gimmickNextButton.Text = "Next Gimmick";
            gimmickNextButton.UseVisualStyleBackColor = true;
            gimmickNextButton.Click += gimmickNextButton_Click;
            // 
            // gimmickPrevButton
            // 
            gimmickPrevButton.Location = new Point(6, 19);
            gimmickPrevButton.Name = "gimmickPrevButton";
            gimmickPrevButton.Size = new Size(116, 23);
            gimmickPrevButton.TabIndex = 0;
            gimmickPrevButton.Text = "Previous Gimmick";
            gimmickPrevButton.UseVisualStyleBackColor = true;
            gimmickPrevButton.Click += gimmickPrevButton_Click;
            // 
            // noteViewGroupBox
            // 
            noteViewGroupBox.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            noteViewGroupBox.Controls.Add(noteMaskLabel);
            noteViewGroupBox.Controls.Add(label9);
            noteViewGroupBox.Controls.Add(noteSizeLabel);
            noteViewGroupBox.Controls.Add(label17);
            noteViewGroupBox.Controls.Add(noteJumpToCurrTimeButton);
            noteViewGroupBox.Controls.Add(noteDeleteSelectedButton);
            noteViewGroupBox.Controls.Add(noteEditSelectedButton);
            noteViewGroupBox.Controls.Add(noteBeatLabel);
            noteViewGroupBox.Controls.Add(notePositionLabel);
            noteViewGroupBox.Controls.Add(noteTypeLabel);
            noteViewGroupBox.Controls.Add(noteMeasureLabel);
            noteViewGroupBox.Controls.Add(label13);
            noteViewGroupBox.Controls.Add(label14);
            noteViewGroupBox.Controls.Add(label15);
            noteViewGroupBox.Controls.Add(label16);
            noteViewGroupBox.Controls.Add(noteNextButton);
            noteViewGroupBox.Controls.Add(notePrevButton);
            noteViewGroupBox.Location = new Point(874, 389);
            noteViewGroupBox.Name = "noteViewGroupBox";
            noteViewGroupBox.Size = new Size(256, 207);
            noteViewGroupBox.TabIndex = 34;
            noteViewGroupBox.TabStop = false;
            noteViewGroupBox.Text = "Note View";
            // 
            // noteMaskLabel
            // 
            noteMaskLabel.AutoSize = true;
            noteMaskLabel.Location = new Point(173, 139);
            noteMaskLabel.Name = "noteMaskLabel";
            noteMaskLabel.Size = new Size(29, 15);
            noteMaskLabel.TabIndex = 17;
            noteMaskLabel.Text = "N/A";
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label9.Location = new Point(85, 137);
            label9.Name = "label9";
            label9.Size = new Size(82, 17);
            label9.TabIndex = 16;
            label9.Text = "Mask Value:";
            // 
            // noteSizeLabel
            // 
            noteSizeLabel.AutoSize = true;
            noteSizeLabel.Location = new Point(173, 118);
            noteSizeLabel.Name = "noteSizeLabel";
            noteSizeLabel.Size = new Size(36, 15);
            noteSizeLabel.TabIndex = 15;
            noteSizeLabel.Text = "None";
            // 
            // label17
            // 
            label17.AutoSize = true;
            label17.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label17.Location = new Point(131, 116);
            label17.Name = "label17";
            label17.Size = new Size(36, 17);
            label17.TabIndex = 14;
            label17.Text = "Size:";
            // 
            // noteJumpToCurrTimeButton
            // 
            noteJumpToCurrTimeButton.Location = new Point(7, 48);
            noteJumpToCurrTimeButton.Name = "noteJumpToCurrTimeButton";
            noteJumpToCurrTimeButton.Size = new Size(243, 23);
            noteJumpToCurrTimeButton.TabIndex = 13;
            noteJumpToCurrTimeButton.Text = "Jump To Nearest Note @ Current Time";
            noteJumpToCurrTimeButton.UseVisualStyleBackColor = true;
            noteJumpToCurrTimeButton.Click += noteJumpToCurrTimeButton_Click;
            // 
            // noteDeleteSelectedButton
            // 
            noteDeleteSelectedButton.ForeColor = Color.Red;
            noteDeleteSelectedButton.Location = new Point(134, 157);
            noteDeleteSelectedButton.Name = "noteDeleteSelectedButton";
            noteDeleteSelectedButton.Size = new Size(113, 43);
            noteDeleteSelectedButton.TabIndex = 11;
            noteDeleteSelectedButton.Text = "Delete Selected Note";
            noteDeleteSelectedButton.UseVisualStyleBackColor = true;
            noteDeleteSelectedButton.Click += noteDeleteSelectedButton_Click;
            // 
            // noteEditSelectedButton
            // 
            noteEditSelectedButton.Location = new Point(6, 157);
            noteEditSelectedButton.Name = "noteEditSelectedButton";
            noteEditSelectedButton.Size = new Size(113, 43);
            noteEditSelectedButton.TabIndex = 10;
            noteEditSelectedButton.Text = "Edit Selected Note";
            noteEditSelectedButton.UseVisualStyleBackColor = true;
            noteEditSelectedButton.Click += noteEditSelectedButton_Click;
            // 
            // noteBeatLabel
            // 
            noteBeatLabel.AutoSize = true;
            noteBeatLabel.Location = new Point(173, 76);
            noteBeatLabel.Name = "noteBeatLabel";
            noteBeatLabel.Size = new Size(36, 15);
            noteBeatLabel.TabIndex = 9;
            noteBeatLabel.Text = "None";
            // 
            // notePositionLabel
            // 
            notePositionLabel.AutoSize = true;
            notePositionLabel.Location = new Point(76, 118);
            notePositionLabel.Name = "notePositionLabel";
            notePositionLabel.Size = new Size(36, 15);
            notePositionLabel.TabIndex = 8;
            notePositionLabel.Text = "None";
            // 
            // noteTypeLabel
            // 
            noteTypeLabel.AutoSize = true;
            noteTypeLabel.Location = new Point(76, 97);
            noteTypeLabel.Name = "noteTypeLabel";
            noteTypeLabel.Size = new Size(36, 15);
            noteTypeLabel.TabIndex = 7;
            noteTypeLabel.Text = "None";
            // 
            // noteMeasureLabel
            // 
            noteMeasureLabel.AutoSize = true;
            noteMeasureLabel.Location = new Point(76, 76);
            noteMeasureLabel.Name = "noteMeasureLabel";
            noteMeasureLabel.Size = new Size(36, 15);
            noteMeasureLabel.TabIndex = 6;
            noteMeasureLabel.Text = "None";
            // 
            // label13
            // 
            label13.AutoSize = true;
            label13.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label13.Location = new Point(128, 74);
            label13.Name = "label13";
            label13.Size = new Size(39, 17);
            label13.TabIndex = 5;
            label13.Text = "Beat:";
            // 
            // label14
            // 
            label14.AutoSize = true;
            label14.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label14.Location = new Point(7, 116);
            label14.Name = "label14";
            label14.Size = new Size(63, 17);
            label14.TabIndex = 4;
            label14.Text = "Position:";
            // 
            // label15
            // 
            label15.AutoSize = true;
            label15.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label15.Location = new Point(29, 95);
            label15.Name = "label15";
            label15.Size = new Size(41, 17);
            label15.TabIndex = 3;
            label15.Text = "Type:";
            // 
            // label16
            // 
            label16.AutoSize = true;
            label16.Font = new Font("Segoe UI", 9.75F, FontStyle.Bold, GraphicsUnit.Point);
            label16.Location = new Point(6, 74);
            label16.Name = "label16";
            label16.Size = new Size(64, 17);
            label16.TabIndex = 2;
            label16.Text = "Measure:";
            // 
            // noteNextButton
            // 
            noteNextButton.Location = new Point(134, 19);
            noteNextButton.Name = "noteNextButton";
            noteNextButton.Size = new Size(116, 23);
            noteNextButton.TabIndex = 1;
            noteNextButton.Text = "Next Note >";
            noteNextButton.UseVisualStyleBackColor = true;
            noteNextButton.Click += noteNextButton_Click;
            // 
            // notePrevButton
            // 
            notePrevButton.Location = new Point(6, 19);
            notePrevButton.Name = "notePrevButton";
            notePrevButton.Size = new Size(116, 23);
            notePrevButton.TabIndex = 0;
            notePrevButton.Text = "< Previous Note";
            notePrevButton.UseVisualStyleBackColor = true;
            notePrevButton.Click += notePrevButton_Click;
            // 
            // autoSaveTimer
            // 
            autoSaveTimer.Tick += autoSaveTimer_Tick;
            // 
            // groupBox3
            // 
            groupBox3.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            groupBox3.Controls.Add(notesOnBeat);
            groupBox3.Location = new Point(874, 223);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(256, 160);
            groupBox3.TabIndex = 35;
            groupBox3.TabStop = false;
            groupBox3.Text = "Notes on Beat";
            // 
            // notesOnBeat
            // 
            notesOnBeat.Columns.AddRange(new ColumnHeader[] { Type, Position, Size });
            notesOnBeat.FullRowSelect = true;
            notesOnBeat.HeaderStyle = ColumnHeaderStyle.Nonclickable;
            notesOnBeat.Location = new Point(7, 22);
            notesOnBeat.Name = "notesOnBeat";
            notesOnBeat.Size = new Size(240, 130);
            notesOnBeat.TabIndex = 0;
            notesOnBeat.Tag = "Type";
            notesOnBeat.UseCompatibleStateImageBehavior = false;
            notesOnBeat.View = View.Details;
            notesOnBeat.SelectedIndexChanged += notesOnBeat_SelectedIndexChanged;
            // 
            // Type
            // 
            Type.Tag = "Type";
            Type.Text = "Type";
            Type.Width = 100;
            // 
            // Position
            // 
            Position.Tag = "Position";
            Position.Text = "Position";
            Position.Width = 65;
            // 
            // Size
            // 
            Size.Tag = "Size";
            Size.Text = "Size";
            Size.Width = 50;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.ControlDark;
            ClientSize = new Size(1142, 787);
            Controls.Add(groupBox3);
            Controls.Add(noteViewGroupBox);
            Controls.Add(groupBox6);
            Controls.Add(insertButton);
            Controls.Add(groupBox9);
            Controls.Add(playbackGroupBox);
            Controls.Add(groupBox5);
            Controls.Add(groupBox4);
            Controls.Add(gimmickTypeGroupBox);
            Controls.Add(groupBox2);
            Controls.Add(groupBox1);
            Controls.Add(circlePanel);
            Controls.Add(menuStrip);
            Icon = (Icon)resources.GetObject("$this.Icon");
            MainMenuStrip = menuStrip;
            MinimumSize = new Size(1158, 826);
            Name = "MainForm";
            Text = "BAKKA Editor - [New File]";
            FormClosing += MainForm_FormClosing;
            Resize += MainForm_Resize;
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)beat2Numeric).EndInit();
            ((System.ComponentModel.ISupportInitialize)beat1Numeric).EndInit();
            ((System.ComponentModel.ISupportInitialize)measureNumeric).EndInit();
            ((System.ComponentModel.ISupportInitialize)sizeTrackBar).EndInit();
            ((System.ComponentModel.ISupportInitialize)sizeNumeric).EndInit();
            ((System.ComponentModel.ISupportInitialize)positionTrackBar).EndInit();
            ((System.ComponentModel.ISupportInitialize)positionNumeric).EndInit();
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            gimmickTypeGroupBox.ResumeLayout(false);
            gimmickTypeGroupBox.PerformLayout();
            groupBox4.ResumeLayout(false);
            groupBox4.PerformLayout();
            groupBox5.ResumeLayout(false);
            groupBox5.PerformLayout();
            playbackGroupBox.ResumeLayout(false);
            playbackGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)trackBarSpeed).EndInit();
            ((System.ComponentModel.ISupportInitialize)trackBarVolume).EndInit();
            ((System.ComponentModel.ISupportInitialize)songTrackBar).EndInit();
            groupBox9.ResumeLayout(false);
            groupBox9.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)visualHispeedNumeric).EndInit();
            menuStrip.ResumeLayout(false);
            menuStrip.PerformLayout();
            groupBox6.ResumeLayout(false);
            groupBox6.PerformLayout();
            noteViewGroupBox.ResumeLayout(false);
            noteViewGroupBox.PerformLayout();
            groupBox3.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private OpenFileDialog openFileDialog;
        private SaveFileDialog saveFileDialog;
        private Panel circlePanel;
        private GroupBox groupBox1;
        private Label label4;
        private NumericUpDown beat2Numeric;
        private NumericUpDown beat1Numeric;
        private NumericUpDown measureNumeric;
        private Label label3;
        private TrackBar sizeTrackBar;
        private NumericUpDown sizeNumeric;
        private Label label2;
        private TrackBar positionTrackBar;
        private NumericUpDown positionNumeric;
        private Label label1;
        private GroupBox groupBox2;
        private RadioButton flairRadio;
        private RadioButton bonusRadio;
        private RadioButton noBonusRadio;
        private CheckBox endHoldCheck;
        private Button endChartButton;
        private Button holdButton;
        private Button chainButton;
        private Button blueButton;
        private Button redButton;
        private Button greenButton;
        private Button orangeButton;
        private Button tapButton;
        private GroupBox gimmickTypeGroupBox;
        private RadioButton removeMaskRadio;
        private Button reverseButton;
        private RadioButton addMaskRadio;
        private Button stopButton;
        private Button hiSpeedButton;
        private Button timeSigButton;
        private Button bpmChangeButton;
        private Button maskButton;
        private GroupBox groupBox4;
        private RadioButton centerMaskRadio;
        private RadioButton clockwiseMaskRadio;
        private RadioButton cClockwiseMaskRadio;
        private GroupBox groupBox5;
        private Label currentSelectionLabel;
        private GroupBox playbackGroupBox;
        private Label songFileLabel;
        private Label label20;
        private TrackBar songTrackBar;
        private Button selectSongButton;
        private Button playButton;
        private OpenFileDialog openSongDialog;
        private System.Windows.Forms.Timer updateTimer;
        private GroupBox groupBox9;
        private Label label21;
        private NumericUpDown visualHispeedNumeric;
        private Button insertButton;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem newToolStripMenuItem;
        private ToolStripMenuItem openToolStripMenuItem;
        private ToolStripMenuItem saveToolStripMenuItem;
        private ToolStripMenuItem saveAsToolStripMenuItem;
        private ToolStripMenuItem exitToolStripMenuItem;
        private ToolStripMenuItem viewToolStripMenuItem;
        private ToolStripMenuItem showCursorToolStripMenuItem;
        private ToolStripMenuItem showCursorDuringPlaybackToolStripMenuItem;
        private ToolStripMenuItem highlightViewedNoteToolStripMenuItem;
        private ToolStripMenuItem selectLastInsertedNoteToolStripMenuItem;
        private ToolStripMenuItem chartToolStripMenuItem;
        private ToolStripMenuItem initialChartSettingsToolStripMenuItem;
        private ToolStripMenuItem aboutToolStripMenuItem;
        private MenuStrip menuStrip;
        private GroupBox groupBox6;
        private Button gimmickDeleteButton;
        private Button gimmickEditButton;
        private Label gimmickBeatLabel;
        private Label gimmickValueLabel;
        private Label gimmickTypeLabel;
        private Label gimmickMeasureLabel;
        private Label label8;
        private Label label7;
        private Label label6;
        private Label label5;
        private Button gimmickNextButton;
        private Button gimmickPrevButton;
        private GroupBox noteViewGroupBox;
        private Label noteMaskLabel;
        private Label label9;
        private Label noteSizeLabel;
        private Label label17;
        private Button noteJumpToCurrTimeButton;
        private Button noteDeleteSelectedButton;
        private Button noteEditSelectedButton;
        private Label noteBeatLabel;
        private Label notePositionLabel;
        private Label noteTypeLabel;
        private Label noteMeasureLabel;
        private Label label13;
        private Label label14;
        private Label label15;
        private Label label16;
        private Button noteNextButton;
        private Button notePrevButton;
        private ToolStripMenuItem editToolStripMenuItem;
        private ToolStripMenuItem undoToolStripMenuItem;
        private ToolStripMenuItem redoToolStripMenuItem;
        private System.Windows.Forms.Timer autoSaveTimer;
        private Label labelVolume;
        private TrackBar trackBarVolume;
        private Label labelSpeed;
        private TrackBar trackBarSpeed;
        private Button gimmickJumpToCurrTimeButton;
        private ToolStripMenuItem showGimmicksInCircleViewToolStripMenuItem;
        private ToolStripMenuItem showGimmicksDuringPlaybackToolStripMenuItem;
        private GroupBox groupBox3;
        private ListView notesOnBeat;
        private ColumnHeader Type;
        private ColumnHeader Position;
        private ColumnHeader Size;
    }
}