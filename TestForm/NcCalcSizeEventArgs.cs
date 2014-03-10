using System;
using System.Drawing;

namespace TestForm
{
	public class NcCalcSizeEventArgs : EventArgs
	{
		public bool IndicateValidClientArea { get; private set; }

		public Rectangle OldWindowSize { get; private set; }

		public Rectangle NewWindowSize { get; private set; }

		public Rectangle ClientSize { get; private set; }


	}
}
