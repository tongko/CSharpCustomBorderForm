using System.Windows.Forms;

namespace TestForm
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		protected override void WndProc(ref Message m)
		{
			base.WndProc(ref m);
		}
	}
}
