using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BAKKA_Editor
{
    public partial class LinearViewForm : Form
    {
        // Chart
        Chart _chart;
        internal Chart Chart
        {
            get => _chart;
            set
            {
                _chart = value;
                linearPanel.Invalidate();
            }
        }

        // Graphics
        BufferedGraphicsContext gfxContext;
        BufferedGraphics bufGraphics;
        LinearView linearView;

        public LinearViewForm()
        {
            InitializeComponent();

            // Form events
            linearPanel.MouseWheel += LinearPanel_MouseWheel;

            // Setup graphics
            gfxContext = BufferedGraphicsManager.Current;
            SetBufferedGraphicsContext();
            linearView = new LinearView(linearPanel.Size);

            // Force double buffering on linearPanel
            Type controlType = linearPanel.GetType();
            PropertyInfo pi = controlType.GetProperty("DoubleBuffered", BindingFlags.Instance | BindingFlags.NonPublic);
            pi.SetValue(linearPanel, true);
        }

        private void SetBufferedGraphicsContext()
        {
            if (linearPanel.Width == 0 || linearPanel.Height == 0)
                return;

            gfxContext.MaximumBuffer = new Size(linearPanel.Width + 1, linearPanel.Height + 1);
            bufGraphics = gfxContext.Allocate(linearPanel.CreateGraphics(),
                new Rectangle(0, 0, linearPanel.Width, linearPanel.Height));
        }

        public void Update()
        {
            linearPanel.Invalidate(true);
        }

        private void linearPanel_Paint(object sender, PaintEventArgs e)
        {
            Rectangle panelRect = new Rectangle(0, 0, linearPanel.Width, linearPanel.Height);

            // Set drawing mode
            bufGraphics.Graphics.SmoothingMode = SmoothingMode.HighSpeed;

            // Draw background
            bufGraphics.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(160, 160, 160)), panelRect);

            // Ref Points
            float startingRemainder = (float)Math.Ceiling(linearView.StartingMeasure) - linearView.StartingMeasure;
            float startingPoint = startingRemainder * linearView.QuarterNoteHeight * 4;

            // Draw Masks
            var masks = Chart.Notes.Where(x => x.IsMask && x.NoteType == NoteType.MaskAdd && x.Measure < linearView.EndMeasure);
            foreach (var mask in masks)
            {
                float measureOffset = mask.Measure - (float)Math.Ceiling(linearView.StartingMeasure);
                float maskPoint = measureOffset * linearView.QuarterNoteHeight * 4;
                float endPoint = 0;

                var addNote = new NoteInfo(mask.Position, mask.Size);

                var removeNote = Chart.Notes.FirstOrDefault(x => x.NoteType == NoteType.MaskRemove && x.Measure > mask.Measure && x.Position == mask.Position && x.Size == mask.Size);
                if (removeNote != null)
                {
                    endPoint = linearView.PanelSize.Height - startingPoint - (removeNote.Measure - (float)Math.Ceiling(linearView.StartingMeasure)) * linearView.QuarterNoteHeight * 4;
                    if (endPoint < 0)
                        endPoint = 0;
                }

                bufGraphics.Graphics.FillRectangle(
                    new SolidBrush(mask.Color),
                    linearView.LeftMargin + linearView.LaneWidth * addNote.StartLane + 1.0f,
                    endPoint,
                    linearView.LaneWidth * addNote.Size - 1.0f,
                    linearView.PanelSize.Height - startingPoint - maskPoint);

                if (addNote.StartLane2 != null && addNote.Size2 != null)
                {
                    bufGraphics.Graphics.FillRectangle(
                    new SolidBrush(mask.Color),
                    linearView.LeftMargin + linearView.LaneWidth * (int)addNote.StartLane2 + 1.0f,
                    endPoint,
                    linearView.LaneWidth * (int)addNote.Size2 - 1.0f,
                    linearView.PanelSize.Height - startingPoint - maskPoint);
                }
            }

            // Draw Lanes
            for (int i = 0; i < (linearView.NumLanes + 1); i++)
            {
                Pen lanePen;
                if (i % 15 == 0)
                    lanePen = linearView.MajorLanePen;
                else if (i % 5 == 0)
                    lanePen = linearView.MediumLanePen;
                else
                    lanePen = linearView.MinorLanePen;

                bufGraphics.Graphics.DrawLine(
                    lanePen,
                    linearView.LeftMargin + i * linearView.LaneWidth,
                    0,
                    linearView.LeftMargin + i * linearView.LaneWidth,
                    linearView.PanelSize.Height);
            }

            // Draw Measure Lines
            for (int i = 0; i <= (int)(linearView.EndMeasure - linearView.StartingMeasure); i++)
            {
                bufGraphics.Graphics.DrawLine(
                    linearView.MeasurePen,
                    linearView.LeftMargin,
                    linearView.PanelSize.Height - startingPoint - i * linearView.QuarterNoteHeight * 4,
                    linearView.LeftMargin + linearView.AllLaneWidth,
                    linearView.PanelSize.Height - startingPoint - i * linearView.QuarterNoteHeight * 4);

                bufGraphics.Graphics.DrawString(
                    $"{(Math.Ceiling(linearView.StartingMeasure) + i):F0}",
                    linearView.GimmickFont,
                    linearView.LabelBrush,
                    linearView.LeftMargin - 8.0f,
                    linearView.PanelSize.Height - startingPoint - i * linearView.QuarterNoteHeight * 4 - 18.0f,
                    linearView.RightAlign);
            }

            // Draw Hi-Speed
            var hispeed = Chart.Gimmicks.Where(
                x => x.GimmickType == GimmickType.HiSpeedChange 
                && x.Measure >= linearView.StartingMeasure 
                && x.Measure <= linearView.EndMeasure);
            foreach (var evt in hispeed)
            {
                float measureOffset = evt.Measure - (float)Math.Ceiling(linearView.StartingMeasure);
                float eventPoint = measureOffset * linearView.QuarterNoteHeight * 4;

                bufGraphics.Graphics.DrawLine(
                    linearView.HiSpeedPen,
                    linearView.LeftMargin + linearView.AllLaneWidth,
                    linearView.PanelSize.Height - startingPoint - eventPoint,
                    linearView.LeftMargin + linearView.AllLaneWidth + linearView.BpmMargin + linearView.TimeSigMargin + linearView.HiSpeedMargin,
                    linearView.PanelSize.Height - startingPoint - eventPoint);

                bufGraphics.Graphics.DrawString(
                    $"x {evt.HiSpeed:F3}",
                    linearView.GimmickFont,
                    linearView.HiSpeedBrush,
                    linearView.LeftMargin + linearView.AllLaneWidth + linearView.BpmMargin + linearView.TimeSigMargin + 8.0f,
                    linearView.PanelSize.Height - startingPoint - eventPoint - 18.0f);
            }

            // Draw Time Signature
            var timesig = Chart.Gimmicks.Where(
                x => x.GimmickType == GimmickType.TimeSignatureChange 
                && x.Measure >= linearView.StartingMeasure 
                && x.Measure <= linearView.EndMeasure);
            foreach (var evt in timesig)
            {
                float measureOffset = evt.Measure - (float)Math.Ceiling(linearView.StartingMeasure);
                float eventPoint = measureOffset * linearView.QuarterNoteHeight * 4;

                bufGraphics.Graphics.DrawLine(
                    linearView.TimeSigPen,
                    linearView.LeftMargin + linearView.AllLaneWidth,
                    linearView.PanelSize.Height - startingPoint - eventPoint,
                    linearView.LeftMargin + linearView.AllLaneWidth + linearView.BpmMargin + linearView.TimeSigMargin,
                    linearView.PanelSize.Height - startingPoint - eventPoint);

                bufGraphics.Graphics.DrawString(
                    $"{evt.TimeSig.Upper}/{evt.TimeSig.Lower}",
                    linearView.GimmickFont,
                    linearView.TimeSigBrush,
                    linearView.LeftMargin + linearView.AllLaneWidth + linearView.BpmMargin + 8.0f,
                    linearView.PanelSize.Height - startingPoint - eventPoint - 18.0f);
            }

            // Draw BPM
            var bpm = Chart.Gimmicks.Where(
                x => x.GimmickType == GimmickType.BpmChange 
                && x.Measure >= linearView.StartingMeasure 
                && x.Measure <= linearView.EndMeasure);
            foreach (var evt in bpm)
            {
                float measureOffset = evt.Measure - (float)Math.Ceiling(linearView.StartingMeasure);
                float eventPoint = measureOffset * linearView.QuarterNoteHeight * 4;

                bufGraphics.Graphics.DrawLine(
                    linearView.BpmPen,
                    linearView.LeftMargin + linearView.AllLaneWidth,
                    linearView.PanelSize.Height - startingPoint - eventPoint,
                    linearView.LeftMargin + linearView.AllLaneWidth + linearView.BpmMargin,
                    linearView.PanelSize.Height - startingPoint - eventPoint);

                bufGraphics.Graphics.DrawString(
                    evt.BPM.ToString("F2"),
                    linearView.GimmickFont,
                    linearView.BpmBrush,
                    linearView.LeftMargin + linearView.AllLaneWidth + 8.0f,
                    linearView.PanelSize.Height - startingPoint - eventPoint - 18.0f);
            }

            // Draw Selection Line
            float selectionOffset = linearView.SelectedMeasure - (float)Math.Ceiling(linearView.StartingMeasure);
            float selectionPoint = selectionOffset * linearView.QuarterNoteHeight * 4;

            bufGraphics.Graphics.DrawLine(
                linearView.SelectionPen,
                linearView.LeftMargin - 10.0f,
                linearView.PanelSize.Height - startingPoint - selectionPoint,
                linearView.LeftMargin + linearView.AllLaneWidth,
                linearView.PanelSize.Height - startingPoint - selectionPoint);

            // Draw Holds
            // First, draw holds that start before the viewpoint and end after

            // Second, draw all notes on-screen
            var holdNotes = Chart.Notes.Where(
                x => x.Measure >= linearView.StartingMeasure
                && x.Measure <= linearView.EndMeasure
                && x.IsHold).ToList();
            foreach (var note in holdNotes)
            {
                linearView.DrawNote(bufGraphics.Graphics, note, startingPoint);
            }

            // Draw Notes
            var drawNotes = Chart.Notes.Where(
                x => x.Measure >= linearView.StartingMeasure
                && x.Measure <= linearView.EndMeasure
                && !x.IsHold
                && !x.IsMask).ToList();
            foreach (var note in drawNotes)
            {
                linearView.DrawNote(bufGraphics.Graphics, note, startingPoint);
            }

            bufGraphics.Render(e.Graphics);
        }

        private void LinearViewForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                Hide();
                e.Cancel = true;
            }
        }

        private void linearPanel_Click(object sender, EventArgs e)
        {
            linearPanel.Invalidate();
        }

        private void LinearViewForm_Resize(object sender, EventArgs e)
        {
            SetBufferedGraphicsContext();
            linearView.Update(linearPanel.Size);
            linearPanel.Invalidate();
        }

        private void LinearPanel_MouseWheel(object? sender, MouseEventArgs e)
        {
            if (Control.ModifierKeys == Keys.Control)
            {
                if (e.Delta > 0)
                    linearView.QuarterNoteHeight += 50;
                else if (linearView.QuarterNoteHeight > 50)
                    linearView.QuarterNoteHeight -= 50;
                linearPanel.Invalidate();
            }
            else if (Control.ModifierKeys == Keys.Alt)
            { }
            else if (Control.ModifierKeys == Keys.Shift)
            { }
            else
            {
                if (e.Delta > 0)
                {
                    linearView.StartingMeasure += 0.25f * (50.0f / linearView.QuarterNoteHeight);
                }
                else
                {
                    if (linearView.StartingMeasure > -0.25f)
                        linearView.StartingMeasure = Math.Max(-0.25f, linearView.StartingMeasure - 0.25f * ( 50.0f / linearView.QuarterNoteHeight));
                }
            }
            linearPanel.Invalidate();
        }

        private void linearPanel_MouseMove(object sender, MouseEventArgs e)
        {
            // Check all notes to determine if we are over one
        }
    }
}
