using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Drawing2D;
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

        // Graphics.
        BufferedGraphicsContext gfxContext = BufferedGraphicsManager.Current;
        BufferedGraphics bufGraphics;

        // Mouse information. Public so other GUI elements can be updated with their values.
        public int mouseDownPos = -1;
        public Point mouseDownPt;
        public int lastMousePos = -1;
        public bool rolloverPos = false;
        public bool rolloverNeg = false;

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

        private ArcInfo GetScaledRect(float objectTime)
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

        private ArcInfo GetArcInfo(Note note)
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

        // Updates the mouse down position within the circle, and returns the new position.
        public void UpdateMouseDown(float xCen, float yCen, Point mousePt)
        {
            float theta = (float)(Math.Atan2(yCen, xCen) * 180.0f / Math.PI);
            if (theta < 0)
                theta += 360.0f;
            // Left click moves the cursor
            mouseDownPos = (int)(theta / 6.0f);
            mouseDownPt = mousePt;
            lastMousePos = -1;
            rolloverPos = false;
            rolloverNeg = false;
        }

        public void UpdateMouseUp()
        {
            if (mouseDownPos <= -1)
            {
                return;
            }

            // Reset position and point.
            mouseDownPos = -1;
            mouseDownPt = new Point();
        }

        // Updates the mouse position and returns the new position in degrees.
        public int UpdateMouseMove(float xCen, float yCen)
        {
            float thetaCalc = (float)(Math.Atan2(yCen, xCen) * 180.0f / Math.PI);
            if (thetaCalc < 0)
                thetaCalc += 360.0f;
            int theta = (int)(thetaCalc / 6.0f);

            int delta = theta - lastMousePos;
            // Handle rollover
            if (delta == -59)
            {
                if (rolloverNeg)
                    rolloverNeg = false;
                else
                    rolloverPos = true;
            }
            else if (delta == 59)
            {
                if (rolloverPos)
                    rolloverPos = false;
                else
                    rolloverNeg = true;
            }
            lastMousePos = theta;

            return theta;
        }

        public void DrawBackground(int width, int height, Color color)
        {
            Rectangle panelRect = new Rectangle(0, 0, width, height);

            // Set drawing mode
            bufGraphics.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighSpeed;
            // Draw background
            bufGraphics.Graphics.FillRectangle(new SolidBrush(color), panelRect);
        }

        public void DrawMasks(Chart chart)
        {
            var masks = chart.Notes.Where(
            x => x.Measure <= CurrentMeasure
            && x.IsMask).ToList();
            foreach (var mask in masks)
            {
                if (mask.NoteType == NoteType.MaskAdd)
                {
                    // Check if there's a MaskRemove that counters the MaskAdd (unless the MaskAdd is later)
                    var rem = masks.FirstOrDefault(x => x.NoteType == NoteType.MaskRemove &&
                                                   x.Position == mask.Position && x.Size == mask.Size);
                    if (rem == null || rem.Measure < mask.Measure)
                        bufGraphics.Graphics.FillPie(MaskBrush, DrawRect.ToInt(), -mask.Position * 6.0f, -mask.Size * 6.0f);
                }
            }
        }

        public void DrawCircle()
        {
            // Switch drawing modes
            bufGraphics.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            // Draw measure circle
            for (float meas = (float)Math.Ceiling(CurrentMeasure); (meas - CurrentMeasure) < TotalMeasureShowNotes; meas += 1.0f)
            {
                var info = GetScaledRect(meas);
                if (info.Rect.Width >= 1)
                {
                    bufGraphics.Graphics.DrawEllipse(BeatPen, info.Rect);
                }
            }

            // Draw base circle
            bufGraphics.Graphics.DrawEllipse(TickMediumPen, DrawRect);
        }

        public void DrawDegreeLines()
        {
            for (int i = 0; i < 360; i += 6)
            {
                PointF startPoint = new PointF(
                   (float)(Radius * Math.Cos(Utils.DegToRad(i))) + CenterPoint.X,
                   (float)(Radius * Math.Sin(Utils.DegToRad(i))) + CenterPoint.Y);
                float tickLength = PanelSize.Width * 10.0f / 285.0f;
                float innerRad = Radius - tickLength;
                Pen activePen;
                if (i % 90 == 0)
                {
                    innerRad = Radius - (tickLength * 3.5f);
                    activePen = TickMajorPen;
                }
                else if (i % 30 == 0)
                {
                    innerRad = Radius - (tickLength * 2.5f);
                    activePen = TickMediumPen;
                }
                else
                {
                    activePen = TickMinorPen;
                }
                PointF endPoint = new PointF(
                    (float)(innerRad * Math.Cos(Utils.DegToRad(i))) + CenterPoint.X,
                   (float)(innerRad * Math.Sin(Utils.DegToRad(i))) + CenterPoint.Y);

                bufGraphics.Graphics.DrawLine(activePen, startPoint, endPoint);
            }
        }

        public void DrawHolds(Chart chart, bool highlightSelectedNote, int selectedNoteIndex)
        {
            ArcInfo currentInfo = GetScaledRect(CurrentMeasure);
            ArcInfo endInfo = GetScaledRect(CurrentMeasure + TotalMeasureShowNotes);

            // First, draw holes that start before the viewpoint and have nodes that end after
            List<Note> holdNotes = chart.Notes.Where(
                x => x.Measure < CurrentMeasure
                && x.NextNote != null
                && x.NextNote.Measure > (CurrentMeasure + TotalMeasureShowNotes)
                && x.IsHold).ToList();
            foreach (var note in holdNotes)
            {
                ArcInfo info = GetArcInfo(note);
                ArcInfo nextInfo = GetArcInfo((Note)note.NextNote);
                //GraphicsPath path = new GraphicsPath();
                //path.AddArc(endInfo.Rect, info.StartAngle, info.ArcLength);
                //path.AddArc(currentInfo.Rect, info.StartAngle + info.ArcLength, -info.ArcLength);
                //bufGraphics.Graphics.FillPath(HoldBrush, path);

                float ratio = (currentInfo.Rect.Width - nextInfo.Rect.Width) / (info.Rect.Width - nextInfo.Rect.Width);
                float startNoteAngle = nextInfo.StartAngle;
                float endNoteAngle = info.StartAngle;
                if (nextInfo.StartAngle > info.StartAngle && (Math.Abs(nextInfo.StartAngle - info.StartAngle) > 180))
                {
                    startNoteAngle -= 360;
                }
                else if (info.StartAngle > nextInfo.StartAngle && (Math.Abs(nextInfo.StartAngle - info.StartAngle) > 180))
                {
                    endNoteAngle -= 360;
                }
                float startAngle = ratio * (endNoteAngle - startNoteAngle) + startNoteAngle;
                float endAngle = ratio * ((endNoteAngle - info.ArcLength) - (startNoteAngle - nextInfo.ArcLength)) +
                    (startNoteAngle - nextInfo.ArcLength);
                float arcLength = startAngle - endAngle;

                float ratio2 = (endInfo.Rect.Width - nextInfo.Rect.Width) / (info.Rect.Width - nextInfo.Rect.Width);
                float startNoteAngle2 = nextInfo.StartAngle;
                float endNoteAngle2 = info.StartAngle;
                if (nextInfo.StartAngle > info.StartAngle && (Math.Abs(nextInfo.StartAngle - info.StartAngle) > 180))
                {
                    startNoteAngle2 -= 360;
                }
                else if (info.StartAngle > nextInfo.StartAngle && (Math.Abs(nextInfo.StartAngle - info.StartAngle) > 180))
                {
                    endNoteAngle2 -= 360;
                }
                float startAngle2 = ratio2 * (endNoteAngle2 - startNoteAngle2) + startNoteAngle2;
                float endAngle2 = ratio2 * ((endNoteAngle2 - info.ArcLength) - (startNoteAngle2 - nextInfo.ArcLength)) +
                    (startNoteAngle2 - nextInfo.ArcLength);
                float arcLength2 = startAngle2 - endAngle2;

                GraphicsPath path = new GraphicsPath();
                path.AddArc(currentInfo.Rect, startAngle, arcLength);
                path.AddArc(endInfo.Rect, startAngle2 + arcLength2, -arcLength2);
                bufGraphics.Graphics.FillPath(HoldBrush, path);
            }

            // Second, draw all the notes on-screen
            holdNotes = chart.Notes.Where(
            x => x.Measure >= CurrentMeasure
               && x.Measure <= (CurrentMeasure + TotalMeasureShowNotes)
               && x.IsHold).ToList();
            foreach (var note in holdNotes)
            {
                ArcInfo info = GetArcInfo(note);

                // If the previous note is off-screen, this case handles that
                if (note.PrevNote != null && note.PrevNote.Measure < CurrentMeasure)
                {
                    ArcInfo prevInfo = GetArcInfo((Note)note.PrevNote);
                    float ratio = (currentInfo.Rect.Width - info.Rect.Width) / (prevInfo.Rect.Width - info.Rect.Width);
                    float startNoteAngle = info.StartAngle;
                    float endNoteAngle = prevInfo.StartAngle;
                    if (info.StartAngle > prevInfo.StartAngle && (Math.Abs(info.StartAngle - prevInfo.StartAngle) > 180))
                    {
                        startNoteAngle -= 360;
                    }
                    else if (prevInfo.StartAngle > info.StartAngle && (Math.Abs(info.StartAngle - prevInfo.StartAngle) > 180))
                    {
                        endNoteAngle -= 360;
                    }
                    float startAngle = ratio * (endNoteAngle - startNoteAngle) + startNoteAngle;
                    float endAngle = ratio * ((endNoteAngle - prevInfo.ArcLength) - (startNoteAngle - info.ArcLength)) +
                        (startNoteAngle - info.ArcLength);
                    float arcLength = startAngle - endAngle;

                    GraphicsPath path = new GraphicsPath();
                    path.AddArc(info.Rect, info.StartAngle, info.ArcLength);
                    path.AddArc(currentInfo.Rect, startAngle + arcLength, -arcLength);
                    bufGraphics.Graphics.FillPath(HoldBrush, path);
                }

                // If the next note is on-screen, this case handles that
                if (note.NextNote != null && note.NextNote.Measure <= (CurrentMeasure + TotalMeasureShowNotes))
                {
                    ArcInfo nextInfo = GetArcInfo((Note)note.NextNote);
                    GraphicsPath path = new GraphicsPath();
                    path.AddArc(info.Rect, info.StartAngle, info.ArcLength);
                    path.AddArc(nextInfo.Rect, nextInfo.StartAngle + nextInfo.ArcLength, -nextInfo.ArcLength);
                    bufGraphics.Graphics.FillPath(HoldBrush, path);
                }

                // If the next note is off-screen, this case handles that
                if (note.NextNote != null && note.NextNote.Measure > (CurrentMeasure + TotalMeasureShowNotes))
                {
                    ArcInfo nextInfo = GetArcInfo((Note)note.NextNote);
                    float ratio = (endInfo.Rect.Width - nextInfo.Rect.Width) / (info.Rect.Width - nextInfo.Rect.Width);
                    float startNoteAngle = nextInfo.StartAngle;
                    float endNoteAngle = info.StartAngle;
                    if (nextInfo.StartAngle > info.StartAngle && (Math.Abs(nextInfo.StartAngle - info.StartAngle) > 180))
                    {
                        startNoteAngle -= 360;
                    }
                    else if (info.StartAngle > nextInfo.StartAngle && (Math.Abs(nextInfo.StartAngle - info.StartAngle) > 180))
                    {
                        endNoteAngle -= 360;
                    }
                    float startAngle = ratio * (endNoteAngle - startNoteAngle) + startNoteAngle;
                    float endAngle = ratio * ((endNoteAngle - info.ArcLength) - (startNoteAngle - nextInfo.ArcLength)) +
                        (startNoteAngle - nextInfo.ArcLength);
                    float arcLength = startAngle - endAngle;

                    GraphicsPath path = new GraphicsPath();
                    path.AddArc(endInfo.Rect, startAngle, arcLength);
                    path.AddArc(info.Rect, info.StartAngle + info.ArcLength, -info.ArcLength);
                    bufGraphics.Graphics.FillPath(HoldBrush, path);
                }

                // Draw note
                if (info.Rect.Width >= 1)
                {
                    bufGraphics.Graphics.DrawArc(GetPen(note), info.Rect, info.StartAngle, info.ArcLength);

                    // Draw bonus
                    if (note.IsFlair)
                        bufGraphics.Graphics.DrawArc(HighlightPen, info.Rect, info.StartAngle + 2, info.ArcLength - 4);

                    // Plot highlighted
                    if (highlightSelectedNote)
                    {
                        if (selectedNoteIndex != -1 && note == chart.Notes[selectedNoteIndex])
                        {
                            bufGraphics.Graphics.DrawArc(HighlightPen, info.Rect, info.StartAngle + 2, info.ArcLength - 4);
                        }
                    }
                }
            }
        }

        public void DrawNotes(Chart chart, bool highlightSelectedNote, int selectedNoteIndex)
        {
            List<Note> drawNotes = chart.Notes.Where(
            x => x.Measure >= CurrentMeasure
            && x.Measure <= (CurrentMeasure + TotalMeasureShowNotes)
            && !x.IsHold && !x.IsMask).ToList();
            foreach (var note in drawNotes)
            {
                ArcInfo info = GetArcInfo(note);

                if (info.Rect.Width >= 1)
                {
                    bufGraphics.Graphics.DrawArc(GetPen(note, info.NoteScale), info.Rect, info.StartAngle, info.ArcLength);
                    if (note.IsFlair)
                    {
                        bufGraphics.Graphics.DrawArc(FlairPen, info.Rect, info.StartAngle + 2, info.ArcLength - 4);
                    }
                    // Plot highlighted
                    if (highlightSelectedNote)
                    {
                        if (selectedNoteIndex != -1 && note == chart.Notes[selectedNoteIndex])
                        {
                            bufGraphics.Graphics.DrawArc(HighlightPen, info.Rect, info.StartAngle + 2, info.ArcLength - 4);
                        }
                    }
                }
            }
        }

        public void DrawCursor(NoteType noteType, float startAngle, float sweepAngle)
        {
            bufGraphics.Graphics.DrawArc(
            GetPen(noteType),
            DrawRect,
            -(float)startAngle * 6.0f,
            -(float)sweepAngle * 6.0f);
        }

        public void Render(Graphics graphics)
        {
            bufGraphics.Render(graphics);
        }

        public void SetBufferedGraphicsContext(int width, int height, Graphics graphics)
        {
            gfxContext.MaximumBuffer = new Size(width + 1, height + 1);
            bufGraphics = gfxContext.Allocate(graphics, new Rectangle(0, 0, width, height));
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
