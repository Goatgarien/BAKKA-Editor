using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor.Operations
{
    internal class CompositeOperation : IOperation
    {
        public string Description { get; }

        protected IEnumerable<IOperation> Operations { get; }

        public CompositeOperation(string description, IEnumerable<IOperation> operations)
        {
            Description = description;
            Operations = operations;
        }

        public void Redo()
        {
            foreach (var op in Operations)
            {
                op.Redo();
            }
        }

        public void Undo()
        {
            foreach (var op in Operations)
            {
                op.Undo();
            }
        }
    }
}
