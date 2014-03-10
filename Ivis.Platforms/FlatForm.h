#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using CP = System::Windows::Forms::CreateParams;

namespace Ivis { namespace Windows { namespace Forms {

	public ref class FlatForm : public Form
	{
	public:		//	Constructor
		FlatForm();
		~FlatForm();

	protected:	//	Overrides
		void			WndProc(Message %m) override;

	protected:	//	Operations
		virtual void	PaintCustomCaption(IntPtr handle, IntPtr handleDc);
		virtual void	AppWndProc(Message %m);
		virtual Boolean	CustomCaptionProc(Message %m);

	private:	//	Operations
		LRESULT			HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};


}}}