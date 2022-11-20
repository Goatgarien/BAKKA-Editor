namespace BAKKA_Editor
{
    partial class LinearViewForm
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
            this.linearPanel = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // linearPanel
            // 
            this.linearPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.linearPanel.Location = new System.Drawing.Point(0, 0);
            this.linearPanel.Name = "linearPanel";
            this.linearPanel.Size = new System.Drawing.Size(800, 450);
            this.linearPanel.TabIndex = 0;
            this.linearPanel.Click += new System.EventHandler(this.linearPanel_Click);
            this.linearPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.linearPanel_Paint);
            this.linearPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.linearPanel_MouseMove);
            // 
            // LinearViewForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.linearPanel);
            this.Name = "LinearViewForm";
            this.ShowIcon = false;
            this.Text = "Linear View";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.LinearViewForm_FormClosing);
            this.Resize += new System.EventHandler(this.LinearViewForm_Resize);
            this.ResumeLayout(false);

        }

        #endregion

        private Panel linearPanel;
    }
}