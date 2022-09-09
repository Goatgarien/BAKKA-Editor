using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor.Operations
{
    internal class OperationManager
    {
        public event EventHandler? OperationHistoryChanged;
        public event EventHandler? ChangesCommitted;

        protected Stack<IOperation> UndoStack { get; } = new Stack<IOperation>();
        protected Stack<IOperation> RedoStack { get; } = new Stack<IOperation>();

        private IOperation? LastCommittedOperation { get; set; } = null;

        public IEnumerable<string> UndoOperationsDescription
        {
            get { return UndoStack.Select(p => p.Description); }
        }

        public IEnumerable<string> RedoOperationsDescription
        {
            get { return RedoStack.Select(p => p.Description); }
        }

        public bool CanUndo { get { return UndoStack.Count > 0; } }

        public bool CanRedo { get { return RedoStack.Count > 0; } }

        public void Push(IOperation op)
        {
            UndoStack.Push(op);
            RedoStack.Clear();
            OperationHistoryChanged?.Invoke(this, EventArgs.Empty);
        }

        public void InvokeAndPush(IOperation op)
        {
            op.Redo();
            Push(op);
        }

        public void Undo()
        {
            IOperation op = UndoStack.Pop();
            op.Undo();
            RedoStack.Push(op);
            OperationHistoryChanged?.Invoke(this, EventArgs.Empty);
        }

        public void Redo()
        {
            IOperation op = RedoStack.Pop();
            op.Redo();
            UndoStack.Push(op);
            OperationHistoryChanged?.Invoke(this, EventArgs.Empty);
        }

        public void Clear()
        {
            UndoStack.Clear();
            RedoStack.Clear();
            LastCommittedOperation = null;
            OperationHistoryChanged?.Invoke(this, EventArgs.Empty);
        }
    }
}
