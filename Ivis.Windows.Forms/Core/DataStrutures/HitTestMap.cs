using System;
using System.Drawing;

namespace Ivis.Windows.Forms.DataStrutures
{
	internal class HitTestMap
	{
		#region Constructor

		public HitTestMap(Rectangle bounds, int x, int y)
			: this(bounds, x, y, 1, 1)
		{
		}

		public HitTestMap(Rectangle bounds, int x, int y, int result, int onBorderResult)
		{
			SetMap(bounds, x, y, result, onBorderResult);
		}

		#endregion


		#region Fields

		private int _x;
		private int _y;
		private HitTestMap[] _maps;

		#endregion


		#region Properties

		public Rectangle Bounds { get; set; }

		public int Result { get; set; }

		public int ResultOnBorder { get; set; }

		#endregion


		#region Methods

		public void AddMap(HitTestMap map)
		{
			if (map == null) throw new ArgumentNullException("map");

			var isLeft = false;
			var isTop = false;

			if (map.Bounds.Left < _y)
			{
				if (map.Bounds.Right == _y)
					isLeft = true;
				else
					throw new ArgumentOutOfRangeException("map", "Map bounds out of range: Right != Y");
			}
			else if (map.Bounds.Left != _y)
				throw new ArgumentOutOfRangeException("map", "Map bounds out of range: Left != Y");

			if (map.Bounds.Top < _x)
			{
				if (map.Bounds.Bottom == _x)
					isTop = true;
				else
					throw new ArgumentOutOfRangeException("map", "Map bounds out of range: Bottom != X");
			}
			else if (map.Bounds.Top != _y)
				throw new ArgumentOutOfRangeException("map", "Map bounds out of range: Top != X");

			if (isLeft && isTop)

		}

		public void SetMap(Rectangle bounds, int x, int y, int result, int onBorderResult)
		{
			Bounds = bounds;
			_x = x;
			_y = y;
			Result = result;
			ResultOnBorder = onBorderResult;
		}

		public int GetHitTestResult(Point location)
		{

		}

		#endregion
	}
}
