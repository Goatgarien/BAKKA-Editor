namespace BAKKA_Editor
{
    partial class InitChartSettingsForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.initSaveSettingsButton = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.initMovieOffsetNumeric = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.initOffsetNumeric = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.initTimeSig2Numeric = new System.Windows.Forms.NumericUpDown();
            this.initTimeSig1Numeric = new System.Windows.Forms.NumericUpDown();
            this.initBpmNumeric = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.initMovieOffsetNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.initOffsetNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.initTimeSig2Numeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.initTimeSig1Numeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.initBpmNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // initSaveSettingsButton
            // 
            this.initSaveSettingsButton.Location = new System.Drawing.Point(12, 128);
            this.initSaveSettingsButton.Name = "initSaveSettingsButton";
            this.initSaveSettingsButton.Size = new System.Drawing.Size(218, 23);
            this.initSaveSettingsButton.TabIndex = 30;
            this.initSaveSettingsButton.Text = "Save Settings";
            this.initSaveSettingsButton.UseVisualStyleBackColor = true;
            this.initSaveSettingsButton.Click += new System.EventHandler(this.initSaveSettingsButton_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(46, 101);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(78, 15);
            this.label9.TabIndex = 29;
            this.label9.Text = "Movie Offset:";
            // 
            // initMovieOffsetNumeric
            // 
            this.initMovieOffsetNumeric.DecimalPlaces = 6;
            this.initMovieOffsetNumeric.Location = new System.Drawing.Point(130, 99);
            this.initMovieOffsetNumeric.Maximum = new decimal(new int[] {
            9999,
            0,
            0,
            0});
            this.initMovieOffsetNumeric.Name = "initMovieOffsetNumeric";
            this.initMovieOffsetNumeric.Size = new System.Drawing.Size(100, 23);
            this.initMovieOffsetNumeric.TabIndex = 28;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(82, 74);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(42, 15);
            this.label8.TabIndex = 27;
            this.label8.Text = "Offset:";
            // 
            // initOffsetNumeric
            // 
            this.initOffsetNumeric.DecimalPlaces = 6;
            this.initOffsetNumeric.Location = new System.Drawing.Point(130, 70);
            this.initOffsetNumeric.Maximum = new decimal(new int[] {
            9999,
            0,
            0,
            0});
            this.initOffsetNumeric.Name = "initOffsetNumeric";
            this.initOffsetNumeric.Size = new System.Drawing.Size(100, 23);
            this.initOffsetNumeric.TabIndex = 26;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(35, 43);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(89, 15);
            this.label7.TabIndex = 25;
            this.label7.Text = "Time Signature:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(174, 43);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(12, 15);
            this.label6.TabIndex = 13;
            this.label6.Text = "/";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(89, 14);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 15);
            this.label5.TabIndex = 24;
            this.label5.Text = "BPM:";
            // 
            // initTimeSig2Numeric
            // 
            this.initTimeSig2Numeric.Location = new System.Drawing.Point(192, 41);
            this.initTimeSig2Numeric.Maximum = new decimal(new int[] {
            1920,
            0,
            0,
            0});
            this.initTimeSig2Numeric.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.initTimeSig2Numeric.Name = "initTimeSig2Numeric";
            this.initTimeSig2Numeric.Size = new System.Drawing.Size(38, 23);
            this.initTimeSig2Numeric.TabIndex = 12;
            this.initTimeSig2Numeric.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            // 
            // initTimeSig1Numeric
            // 
            this.initTimeSig1Numeric.Location = new System.Drawing.Point(130, 41);
            this.initTimeSig1Numeric.Maximum = new decimal(new int[] {
            191,
            0,
            0,
            0});
            this.initTimeSig1Numeric.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.initTimeSig1Numeric.Name = "initTimeSig1Numeric";
            this.initTimeSig1Numeric.Size = new System.Drawing.Size(38, 23);
            this.initTimeSig1Numeric.TabIndex = 11;
            this.initTimeSig1Numeric.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            // 
            // initBpmNumeric
            // 
            this.initBpmNumeric.DecimalPlaces = 6;
            this.initBpmNumeric.Location = new System.Drawing.Point(130, 12);
            this.initBpmNumeric.Maximum = new decimal(new int[] {
            9999,
            0,
            0,
            0});
            this.initBpmNumeric.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.initBpmNumeric.Name = "initBpmNumeric";
            this.initBpmNumeric.Size = new System.Drawing.Size(100, 23);
            this.initBpmNumeric.TabIndex = 23;
            this.initBpmNumeric.Value = new decimal(new int[] {
            120,
            0,
            0,
            0});
            // 
            // InitChartSettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(242, 164);
            this.Controls.Add(this.initSaveSettingsButton);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.initBpmNumeric);
            this.Controls.Add(this.initMovieOffsetNumeric);
            this.Controls.Add(this.initTimeSig1Numeric);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.initTimeSig2Numeric);
            this.Controls.Add(this.initOffsetNumeric);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "InitChartSettingsForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Initial Chart Settings";
            ((System.ComponentModel.ISupportInitialize)(this.initMovieOffsetNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.initOffsetNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.initTimeSig2Numeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.initTimeSig1Numeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.initBpmNumeric)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Button initSaveSettingsButton;
        private Label label9;
        private NumericUpDown initMovieOffsetNumeric;
        private Label label8;
        private NumericUpDown initOffsetNumeric;
        private Label label7;
        private Label label6;
        private Label label5;
        private NumericUpDown initTimeSig2Numeric;
        private NumericUpDown initTimeSig1Numeric;
        private NumericUpDown initBpmNumeric;
    }
}