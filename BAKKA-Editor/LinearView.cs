using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing.Drawing2D;

namespace BAKKA_Editor
{
    internal class LinearView
    {
        public SizeF PanelSize { get; private set; }
        public int LaneWidth { get; private set; }
        public int LeftMargin { get; set; }
        public int AllLaneWidth { get; private set; }
        public int BpmMargin { get; private set; }
        public int TimeSigMargin { get; private set; }
        public int HiSpeedMargin { get; private set; }
        public float StartingMeasure { get; set; } = -0.25f;
        public float StartingPoint { 
            get
            {
                return (float)Math.Ceiling((Math.Ceiling(StartingMeasure) - StartingMeasure) * QuarterNoteHeight * 4);
            }
        }
        public float SelectedMeasure { get; set; } = 0.0f;
        public float EndMeasure
        {
            get
            {
                return (float)Math.Ceiling(StartingMeasure + PanelSize.Height / (QuarterNoteHeight * 4));
            }
        }

        public int QuarterNoteHeight { get; set; } = 50;
        public int NumLanes { get; } = 60;

        public Pen MeasurePen { get; } = new Pen(Color.White, 1.0f);
        public Pen MinorLanePen { get; } = new Pen(Color.FromArgb(42, 42, 42), 1.0f);
        public Pen MediumLanePen { get; } = new Pen(Color.FromArgb(80, 80, 80), 1.0f);
        public Pen MajorLanePen { get; } = new Pen(Color.White, 1.0f);
        //public Pen MajorLanePen { get; } = new Pen(Color.FromArgb(100, 100, 100), 1.0f);
        //public Brush LabelBrush { get; } = new SolidBrush(Color.FromArgb(204, 204, 204));
        public Brush LabelBrush { get; } = new SolidBrush(Color.Black);

        public Pen SelectionPen { get; } = new Pen(Color.Red, 1.0f);

        public Pen BpmPen { get; } = new Pen(Color.Lime, 1.0f);
        public Brush BpmBrush { get; } = new SolidBrush(Color.Lime);
        public Pen TimeSigPen { get; } = new Pen(Color.LightBlue, 1.0f);
        public Brush TimeSigBrush { get; } = new SolidBrush(Color.LightBlue);
        public Pen HiSpeedPen { get; } = new Pen(Color.Salmon, 1.0f);
        public Brush HiSpeedBrush { get; } = new SolidBrush(Color.Salmon);

        public Font GimmickFont { get; } = new Font("Arial", 10.0f);
        public StringFormat RightAlign { get; } = new StringFormat() { Alignment = StringAlignment.Far };

        public LinearView(SizeF size)
        {
            Update(size);
        }

        public void Update(SizeF size)
        {
            PanelSize = size;

            LeftMargin = (int)(PanelSize.Width * 0.08f);
            LaneWidth = (int)Math.Max(8, PanelSize.Width * 0.68f / NumLanes);
            AllLaneWidth = LaneWidth * NumLanes;
            BpmMargin = TimeSigMargin = HiSpeedMargin = (int)Math.Max(60, PanelSize.Width * 0.08f);
        }

        public void DrawNote(Graphics g, Note note, float startingPoint)
        {
            float measureOffset = note.Measure - (float)Math.Ceiling(StartingMeasure);
            float notePoint = (float)Math.Ceiling(measureOffset * QuarterNoteHeight * 4);

            var noteInfo = new NoteInfo(note.Position, note.Size);

            if (note.IsHold && note.NextNote != null)
            {
                float nextOffset = note.NextNote.Measure - (float)Math.Ceiling(StartingMeasure);
                float nextPoint = (float)Math.Ceiling(nextOffset * QuarterNoteHeight * 4);

                var nextInfo = new NoteInfo(note.NextNote.Position, note.NextNote.Size);

                bool crossedBoundary = noteInfo.StartLane2 != null || nextInfo.StartLane2 != null;
                bool bothValid = noteInfo.StartLane2 != null && nextInfo.StartLane2 != null;

                if (!crossedBoundary || bothValid)
                {
                    g.FillPolygon(
                        PlotBrush.HoldBrush,
                        new PointF[] {
                        new PointF(LeftMargin + LaneWidth * noteInfo.StartLane + 1.0f, PanelSize.Height - startingPoint - notePoint - 3.0f),
                        new PointF(LeftMargin + LaneWidth * (noteInfo.StartLane + noteInfo.Size) - 1.0f, PanelSize.Height - startingPoint - notePoint - 3.0f),
                        new PointF(LeftMargin + LaneWidth * (nextInfo.StartLane + nextInfo.Size) - 1.0f, PanelSize.Height - startingPoint - nextPoint - 3.0f),
                        new PointF(LeftMargin + LaneWidth * nextInfo.StartLane + 1.0f, PanelSize.Height - startingPoint - nextPoint - 3.0f)
                        });

                    if (bothValid)
                    {
                        g.FillPolygon(
                        PlotBrush.HoldBrush,
                        new PointF[] {
                        new PointF(LeftMargin + LaneWidth * (float)noteInfo.StartLane2 + 1.0f, PanelSize.Height - startingPoint - notePoint - 3.0f),
                        new PointF(LeftMargin + LaneWidth * ((float)noteInfo.StartLane2 + (float)noteInfo.Size2) - 1.0f, PanelSize.Height - startingPoint - notePoint - 3.0f),
                        new PointF(LeftMargin + LaneWidth * ((float)nextInfo.StartLane2 + (float)nextInfo.Size2) - 1.0f, PanelSize.Height - startingPoint - nextPoint - 3.0f),
                        new PointF(LeftMargin + LaneWidth * (float)nextInfo.StartLane2 + 1.0f, PanelSize.Height - startingPoint - nextPoint - 3.0f)
                        });
                    }
                }
                else
                {
                    
                }
            }

            g.FillRectangle(
                new SolidBrush(note.Color),
                LeftMargin + LaneWidth * noteInfo.StartLane + 1.0f,
                PanelSize.Height - startingPoint - notePoint - 3.0f,
                LaneWidth * noteInfo.Size - 2.0f,
                6.0f);

            if (noteInfo.StartLane2 != null && noteInfo.Size2 != null)
            {
                g.FillPolygon(
                    new SolidBrush(note.Color),
                    new PointF[] {
                            new PointF(LeftMargin - 8.0f, PanelSize.Height - startingPoint - notePoint + 1.0f),
                            new PointF(LeftMargin - 8.0f, PanelSize.Height - startingPoint - notePoint - 2.0f),
                            new PointF(LeftMargin + 1.0f, PanelSize.Height - startingPoint - notePoint - 4.0f),
                            new PointF(LeftMargin + 1.0f, PanelSize.Height - startingPoint - notePoint + 3.0f)
                    });

                g.FillRectangle(
                    new SolidBrush(note.Color),
                    LeftMargin + LaneWidth * (int)noteInfo.StartLane2 + 1.0f,
                    PanelSize.Height - startingPoint - notePoint - 3.0f,
                    LaneWidth * (int)noteInfo.Size2 - 2.0f,
                    6.0f);

                g.FillPolygon(
                    new SolidBrush(note.Color),
                    new PointF[] {
                            new PointF(LeftMargin + AllLaneWidth + 8.0f, PanelSize.Height - startingPoint - notePoint + 1.0f),
                            new PointF(LeftMargin + AllLaneWidth + 8.0f, PanelSize.Height - startingPoint - notePoint - 2.0f),
                            new PointF(LeftMargin + AllLaneWidth - 1.0f, PanelSize.Height - startingPoint - notePoint - 4.0f),
                            new PointF(LeftMargin + AllLaneWidth - 1.0f, PanelSize.Height - startingPoint - notePoint + 3.0f)
                    });
            }
        }

        public RectangleF[] GetNoteRect(Note note)
        {
            List<RectangleF> rects = new List<RectangleF>();

            float measureOffset = note.Measure - (float)Math.Ceiling(StartingMeasure);
            float notePoint = (float)Math.Ceiling(measureOffset * QuarterNoteHeight * 4);

            int endLane = (14 - note.Position) < 0 ? (14 - note.Position) + 60 : (14 - note.Position);
            int size = note.Size;
            int startLane = (endLane - size + 1);
            int? startLane2 = null;
            int? size2 = null;
            if (startLane < 0)
            {
                startLane2 = startLane + 60;
                startLane = 0;
                size = endLane + 1;
                size2 = 60 - startLane2;
            }

            rects.Add(new RectangleF(
                LeftMargin + LaneWidth * startLane + 1.0f,
                PanelSize.Height - StartingPoint - notePoint - 3.0f,
                LaneWidth * size - 2.0f,
                6.0f));

            if (startLane2 != null && size2 != null)
            {
                rects.Add(new RectangleF(
                    LeftMargin + LaneWidth * (int)startLane2 + 1.0f,
                    PanelSize.Height - StartingPoint - notePoint - 3.0f,
                    LaneWidth * (int)size2 - 2.0f,
                    6.0f));
            }

            return rects.ToArray();
        }
    }
}
