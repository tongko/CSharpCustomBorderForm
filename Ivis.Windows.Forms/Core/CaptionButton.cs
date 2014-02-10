using System.Drawing;

namespace Ivis.Windows.Forms
{
	internal enum CaptionButtonImageType
	{
		Normal = 0,
		Hover = 1,
		Cliked
	}

	internal class CaptionButton
	{
		#region Ctor

		public CaptionButton()
		{
			_images = new Image[3];
		}

		#endregion


		#region Fields

		private readonly Image[] _images;

		#endregion


		#region Properties

		public Image this[CaptionButtonImageType imageType]
		{
			get { return _images[(int)imageType]; }
			set { _images[(int)imageType] = value; }
		}

		public Rectangle Bounds { get; set; }

		public bool Visible { get; set; }

		public bool Enabled { get; set; }

		public string ToolTips { get; set; }

		#endregion


		#region Methods

		#endregion
	}
}
