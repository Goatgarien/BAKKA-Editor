using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor
{
    internal class CircleView
    {
        public SizeF PanelSize { get; private set; }
        public RectangleF DrawRect { get; private set; }
        public PointF TopCorner { get; private set; }
        public PointF CenterPoint { get; private set; }
        public float Radius { get; private set; }
        public float CurrentMeasure { get; set; }
        /// <summary>
        /// Number of measures in the future that are visible
        /// </summary>
        public float TotalMeasureShowNotes { get; set; } = 0.5f;

        // Pens and Brushes
        public Pen BasePen { get; set; }
        public Pen BeatPen { get; set; }
        public Pen TickMinorPen { get; set; }
        public Pen TickMediumPen { get; set; }
        public Pen TickMajorPen { get; set; }
        public SolidBrush HoldBrush { get; set; } = new SolidBrush(Color.FromArgb(170, Color.Yellow));
        public SolidBrush MaskBrush { get; set; } = new SolidBrush(Color.DimGray);
        public Pen HighlightPen { get; set; }
        public Pen FlairPen { get; set; }
        private int CursorTransparency = 110;
        private int SelectTransparency = 110;
        private int FlairTransparency = 75;

        public CircleView(SizeF size)
        {
            Update(size);
        }

        public void Update(SizeF size)
        {
            PanelSize = size;
            float basePenWidth = PanelSize.Width * 4.0f / 600.0f;
            TopCorner = new PointF(basePenWidth * 4, basePenWidth * 4);
            DrawRect = new RectangleF(
                TopCorner.X,
                TopCorner.Y,
                PanelSize.Width - basePenWidth * 8,
                PanelSize.Height - basePenWidth * 8);
            Radius = DrawRect.Width / 2.0f;
            CenterPoint = new PointF(TopCorner.X + Radius, TopCorner.Y + Radius);

            // Pens
            BasePen = new Pen(Color.Black, basePenWidth);
            BeatPen = new Pen(Color.White, PanelSize.Width * 1.0f / 600.0f);
            TickMinorPen = new Pen(Color.Black, PanelSize.Width * 2.0f / 600.0f);
            TickMediumPen = new Pen(Color.Black, PanelSize.Width * 4.0f / 600.0f);
            TickMajorPen = new Pen(Color.Black, PanelSize.Width * 7.0f / 600.0f);
            HighlightPen = new Pen(Color.FromArgb(SelectTransparency, Color.LightPink), PanelSize.Width * 8.0f / 600.0f);
            FlairPen = new Pen(Color.FromArgb(FlairTransparency, Color.Yellow), PanelSize.Width * 8.0f / 600.0f);
        }

        public ArcInfo GetScaledRect(float objectTime)
        {
            ArcInfo info = new();
            float notescaleInit = 1 - ((objectTime - CurrentMeasure) * (1 / TotalMeasureShowNotes));  // Scale from 0-1
            info.NoteScale = (float)Math.Pow(10.0f, notescaleInit) / 10.0f;
            float scaledRectSize = DrawRect.Width * info.NoteScale;
            float scaledRadius = scaledRectSize / 2.0f;
            info.Rect = new RectangleF(
                new PointF(
                    CenterPoint.X - scaledRadius,
                    CenterPoint.Y - scaledRadius),
                new SizeF(scaledRectSize, scaledRectSize));
            return info;
        }

        public ArcInfo GetArcInfo(Note note)
        {
            ArcInfo info = GetScaledRect(note.Measure);
            info.StartAngle = -note.Position * 6;
            info.ArcLength = -note.Size * 6;
            if(info.ArcLength != -360)
            {
                info.StartAngle -= 2;
                info.ArcLength += 4;
            }
            return info;
        }

        public Pen GetPen(Note note, float noteScale = 1.0f)
        {
            return new Pen(note.Color, PanelSize.Width * 8.0f * noteScale / 600.0f);
        }

        public Pen GetPen(NoteType noteType)
        {
            return new Pen(Color.FromArgb(CursorTransparency, Utils.NoteTypeToColor(noteType)), PanelSize.Width * 24.0f / 600.0f);
        }
    }

    internal struct ArcInfo
    {
        public float StartAngle;
        public float ArcLength;
        public RectangleF Rect;
        public float NoteScale;
    }
}
