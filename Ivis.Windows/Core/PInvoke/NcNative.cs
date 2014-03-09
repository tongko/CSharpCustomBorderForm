using System;
using System.Runtime.InteropServices;
using System.Security;

namespace Ivis.Windows.Forms.PInvoke
{
	// ReSharper disable InconsistentNaming
	[SuppressUnmanagedCodeSecurity]
	internal class NcNative
	{
		#region Constants

		public const int WM_NCCREATE = 129;
		public const int WM_NCDESTROY = 130;
		public const int WM_NCCALCSIZE = 131;
		public const int WM_NCHITTEST = 132;
		public const int WM_NCPAINT = 133;
		public const int WM_NCACTIVATE = 134;
		public const int WM_NCMOUSEMOVE = 160;
		public const int WM_NCMOUSELEAVE = 674;
		public const int WM_NCLBUTTONDOWN = 161;
		public const int WM_NCLBUTTONUP = 162;
		public const int WM_NCLBUTTONDBLCLK = 163;
		public const int WM_NCRBUTTONDOWN = 164;
		public const int WM_NCRBUTTONUP = 165;
		public const int WM_NCRBUTTONDBLCLK = 166;
		public const int WM_NCMBUTTONDOWN = 167;
		public const int WM_NCMBUTTONUP = 168;
		public const int WM_NCMBUTTONDBLCLK = 169;
		public const int WM_NCXBUTTONDOWN = 171;
		public const int WM_NCXBUTTONUP = 172;
		public const int WM_NCXBUTTONDBLCLK = 173;

		public const int SWP_FRAMECHANGED = 32;

		#endregion
	}

	internal class User32
	{
		/// <summary>
		/// Changes the size, position, and Z order of a child, pop-up or top-level window.
		/// </summary>
		/// <param name="hWnd">A handle to the window.</param>
		/// <param name="hWndInsertAfter">A handle to the window to precede the positioned window in the Z order. (HWND value)</param>
		/// <param name="X">The new position of the left side of the window, in client coordinates.</param>
		/// <param name="Y">The new position of the top of the window, in client coordinates.</param>
		/// <param name="W">The new width of the window, in pixels.</param>
		/// <param name="H">The new height of the window, in pixels.</param>
		/// <param name="uFlags">The window sizing and positioning flags. (SWP value)</param>
		/// <returns>Nonzero if function succeeds, zero if function fails.</returns>
		[DllImport("user32.dll", SetLastError = true)]
		public static extern bool SetWindowPos(
			IntPtr hWnd,
			IntPtr hWndInsertAfter,
			int X,
			int Y,
			int W,
			int H,
			uint uFlags);


	}
}
