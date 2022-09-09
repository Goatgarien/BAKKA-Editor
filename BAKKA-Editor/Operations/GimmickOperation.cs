using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor.Operations
{
    internal abstract class GimmickOperation : IOperation
    {
        protected Gimmick Gimmick { get; }
        protected Chart Chart { get; }
        public abstract string Description { get; }

        public GimmickOperation(Chart chart, Gimmick item)
        {
            Chart = chart;
            Gimmick = item;
        }

        public abstract void Redo();

        public abstract void Undo();
    }

    internal class InsertGimmick : GimmickOperation
    {
        public override string Description => "Insert gimmick";

        public InsertGimmick(Chart chart, Gimmick item) : base(chart, item)
        { }

        public override void Redo()
        {
            Chart.Gimmicks.Add(Gimmick);
        }

        public override void Undo()
        {
            Chart.Gimmicks.Remove(Gimmick);
        }
    }

    internal class RemoveGimmick : GimmickOperation
    {
        public override string Description => "Remove gimmick";

        public RemoveGimmick(Chart chart, Gimmick item) : base(chart, item)
        { }

        public override void Redo()
        {
            Chart.Gimmicks.Remove(Gimmick);
        }

        public override void Undo()
        {
            Chart.Gimmicks.Add(Gimmick);
        }
    }

    internal class EditGimmick : IOperation
    {
        public string Description => "Edit gimmick";

        protected Gimmick Base { get; }
        protected Gimmick OldGimmick { get; }
        protected Gimmick NewGimmick { get; }

        public EditGimmick(Gimmick baseGimmick, Gimmick newGimmick)
        {
            Base = baseGimmick;
            OldGimmick = new Gimmick(baseGimmick);
            NewGimmick = new Gimmick(newGimmick);
        }

        public void Redo()
        {
            Base.BeatInfo = new BeatInfo(NewGimmick.BeatInfo);
            switch (Base.GimmickType)
            {
                case GimmickType.BpmChange:
                    Base.BPM = NewGimmick.BPM;
                    break;
                case GimmickType.TimeSignatureChange:
                    Base.TimeSig = new TimeSignature(NewGimmick.TimeSig);
                    break;
                case GimmickType.HiSpeedChange:
                    Base.HiSpeed = NewGimmick.HiSpeed;
                    break;
            }
        }

        public void Undo()
        {
            Base.BeatInfo = new BeatInfo(OldGimmick.BeatInfo);
            switch (Base.GimmickType)
            {
                case GimmickType.BpmChange:
                    Base.BPM = OldGimmick.BPM;
                    break;
                case GimmickType.TimeSignatureChange:
                    Base.TimeSig = new TimeSignature(OldGimmick.TimeSig);
                    break;
                case GimmickType.HiSpeedChange:
                    Base.HiSpeed = OldGimmick.HiSpeed;
                    break;
            }
        }
    }
}
