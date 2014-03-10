using System;
using System.Runtime.InteropServices;

namespace TestForm
{
	// ReSharper disable InconsistentNaming
	internal class Native
	{
		public const int WM_NCCALCSIZE = 0x0083;

		[StructLayout(LayoutKind.Sequential)]
		public struct WINDOWPOS
		{
			public IntPtr hwnd;
			public IntPtr hwndInsertAfter;
			public int x;
			public int y;
			public int cx;
			public int cy;
			public uint flags;

			public static readonly WINDOWPOS Empty = new WINDOWPOS
			{
				hwnd = IntPtr.Zero,
				hwndInsertAfter = IntPtr.Zero,
				x = 0,
				y = 0,
				cx = 0,
				cy = 0,
				flags = 0
			};
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct RECT
		{
			public int left;
			public int top;
			public int right;
			public int bottom;

			public static readonly RECT Empty = new RECT { bottom = 0, left = 0, right = 0, top = 0 };
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct NCCALCSIZE_PARAMS : IDisposable
		{
			public RECT rcNewWindow;
			public RECT rcOldwindow;
			public RECT rcClient;
			public IntPtr lppos;

			public WINDOWPOS Windowpos
			{
				get
				{
					return lppos == IntPtr.Zero ? WINDOWPOS.Empty : Marshal.PtrToStructure<WINDOWPOS>(lppos);
				}
				set
				{
					if (lppos == IntPtr.Zero)
						lppos = Marshal.AllocHGlobal(Marshal.SizeOf(value));
					Marshal.StructureToPtr(value, lppos, true);
				}
			}

			public static readonly NCCALCSIZE_PARAMS Empty = new NCCALCSIZE_PARAMS
			{
				rcNewWindow = RECT.Empty,
				rcOldwindow = RECT.Empty,
				rcClient = RECT.Empty,
				lppos = IntPtr.Zero
			};

			public void Dispose()
			{
				if (lppos != IntPtr.Zero)
				{
					Marshal.DestroyStructure<WINDOWPOS>(lppos);
					Marshal.FreeHGlobal(lppos);
				}
			}
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct MARGINS
		{
			public int cxLeftWidth;
			public int cxRightWidth;
			public int cyTopHeight;
			public int cyBottomHeight;
		}

		[DllImport("user32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, SWP uFlags);

		[DllImport("user32.dll")]
		public static extern bool GetWindowRect(HandleRef hwnd, out RECT lpRect);

		[DllImport("dwmapi.dll")]
		public static extern bool DwmDefWindowProc(IntPtr hWnd, int msg, IntPtr wParam, IntPtr lParam, ref IntPtr plResult);

		[DllImport("dwmapi.dll", PreserveSig = false)]
		public static extern void DwmExtendFrameIntoClientArea(IntPtr hwnd, ref MARGINS margins);

		[DllImport("dwmapi.dll", PreserveSig = false)]
		private static extern void DwmIsCompositionEnabled(out bool enabled);

		public static bool AeroEnable()
		{
			if (Environment.OSVersion.Version.Major < 6) return false;
			bool result;
			DwmIsCompositionEnabled(out result);

			return result;
		}
	}
}
// ReSharper restore InconsistentNaming