using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor.Operations
{
    internal interface IOperation
    {
        string Description { get; }

        void Undo();

        void Redo();
    }
}
