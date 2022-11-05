using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor.Operations
{
    internal abstract class NoteOperation : IOperation
    {
        public Note Note { get; }
        protected Chart Chart { get; }
        public abstract string Description { get; }

        public NoteOperation(Chart chart, Note item)
        {
            Chart = chart;
            Note = item;
        }

        public abstract void Redo();

        public abstract void Undo();
    }

    internal class InsertNote : NoteOperation
    {
        public override string Description => "Insert note";

        public InsertNote(Chart chart, Note item) : base(chart, item)
        { }

        public override void Redo()
        {
            Chart.Notes.Add(Note);
        }

        public override void Undo()
        {
            Chart.Notes.Remove(Note);
        }
    }

    internal class RemoveNote : NoteOperation
    {
        public override string Description => "Remove note";

        public RemoveNote(Chart chart, Note item) : base(chart, item)
        { }

        public override void Redo()
        {
            Chart.Notes.Remove(Note);
        }

        public override void Undo()
        {
            Chart.Notes.Add(Note);
        }
    }

    internal class EditNote : IOperation
    {
        public string Description => "Edit note";

        protected Note Base { get; }
        protected Note OldNote { get; }
        protected Note NewNote { get; }

        public EditNote(Note baseNote, Note newNote)
        {
            Base = baseNote;
            OldNote = new Note(baseNote);
            NewNote = new Note(newNote);
        }

        public void Redo()
        {
            Base.BeatInfo = new BeatInfo(NewNote.BeatInfo);
            Base.Position = NewNote.Position;
            Base.Size = NewNote.Size;
        }

        public void Undo()
        {
            Base.BeatInfo = new BeatInfo(OldNote.BeatInfo);
            Base.Position = OldNote.Position;
            Base.Size = OldNote.Size;
        }
    }

    internal class InsertHoldNote : NoteOperation
    {
        public override string Description => "Insert hold note";
        private Note prevNote;

        public InsertHoldNote(Chart chart, Note item) : base(chart, item)
        {
            prevNote = item.PrevNote;
        }

        public override void Redo()
        {
            if (Note.PrevNote != null)
                Note.PrevNote.NextNote = Note;
            Chart.Notes.Add(Note);
        }

        public override void Undo()
        {
            if (Note.PrevNote != null)
                Note.PrevNote.NextNote = null;
            Chart.Notes.Remove(Note);
        }
    }

    internal class RemoveHoldNote : NoteOperation
    {
        public override string Description => "Remove hold note";
        private Note prevNote;
        private NoteType prevNoteType;
        private Note nextNote;
        private NoteType nextNoteType;

        public RemoveHoldNote(Chart chart, Note item) : base(chart, item)
        {
            prevNote = item.PrevNote;
            if (prevNote != null)
                prevNoteType = prevNote.NoteType;
            nextNote = item.NextNote;
            if (nextNote != null)
                nextNoteType = nextNote.NoteType;
        }

        public override void Redo()
        {
            switch (Note.NoteType)
            {
                case NoteType.HoldStartNoBonus:
                case NoteType.HoldStartBonusFlair:
                    nextNote.PrevNote = null;
                    nextNote.NoteType = Note.NoteType;
                    break;
                case NoteType.HoldJoint:
                    prevNote.NextNote = nextNote;
                    nextNote.PrevNote = prevNote;
                    break;
                case NoteType.HoldEnd:
                    prevNote.NextNote = null;
                    prevNote.NoteType = NoteType.HoldEnd;
                    break;
                default:
                    break;
            }
            Chart.Notes.Remove(Note);
        }

        public override void Undo()
        {
            switch (Note.NoteType)
            {
                case NoteType.HoldStartNoBonus:
                case NoteType.HoldStartBonusFlair:
                    nextNote.PrevNote = Note;
                    nextNote.NoteType = nextNoteType;
                    break;
                case NoteType.HoldJoint:
                    prevNote.NextNote = Note;
                    nextNote.PrevNote = Note;
                    break;
                case NoteType.HoldEnd:
                    prevNote.NextNote = Note;
                    prevNote.NoteType = prevNoteType;
                    break;
                default:
                    break;
            }
            Chart.Notes.Add(Note);
        }
    }
}
