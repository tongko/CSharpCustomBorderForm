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
			_maps = new HitTestMap[4];
			_hasChildren = false;
			SetMap(bounds, x, y, result, onBorderResult);
		}

		#endregion


		#region Fields

		private int _x;
		private int _y;
		private bool _hasChildren;
		private readonly HitTestMap[] _maps;

		#endregion


		#region Properties

		public Rectangle Bounds { get; set; }

		public int Result { get; set; }

		public int ResultOnBorder { get; set; }

		public HitTestMap this[MapLocation location]
		{
			get { return _maps[(int)location]; }
			set { _maps[(int)location] = value; }
		}

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
				_maps[0] = map;
			else if (isTop)
				_maps[1] = map;
			else if (isLeft)
				_maps[2] = map;
			else
				_maps[3] = map;

			_hasChildren = true;
		}

		public int HitTest(Point location)
		{
			if (!_hasChildren) return Result;

			var isLeft = false;
			var isTop = false;

			if (location.X < _y)
				isLeft = true;
			if (location.Y < _x)
				isTop = true;

			HitTestMap map;
			if (isLeft && isTop)
				map = _maps[0];
			else if (isTop)
				map = _maps[1];
			else if (isLeft)
				map = _maps[2];
			else
				map = _maps[3];

			return map.HitTest(location);
		}

		public void SetMap(Rectangle bounds, int x, int y, int result, int onBorderResult)
		{
			Bounds = bounds;
			_x = x;
			_y = y;
			Result = result;
			ResultOnBorder = onBorderResult;
		}

		#endregion
	}
}
