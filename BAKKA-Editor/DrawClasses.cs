using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor
{
    internal class DrawClasses
    {
    }

    internal class NoteInfo
    {
        public int StartLane { get; }
        public int EndLane { get; }
        public int? StartLane2 { get; }
        public int Size { get; }
        public int? Size2 { get; }

        public NoteInfo(int position, int size)
        {
            StartLane = (position - 15) < 0 ? (position - 15) + 60 : position - 15;
            Size = size;
            EndLane = StartLane + size + 1;
            StartLane2 = null;
            Size2 = null;
            if (EndLane >= 60)
            {
                StartLane2 = StartLane;
                StartLane = 0;
                Size = EndLane - 60;
                Size2 = 60 - StartLane2;
            }
        }
    }
}
