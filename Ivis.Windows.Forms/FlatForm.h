#pragma once

namespace Ivis { namespace Windows { namespace Forms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FlatForm
	/// </summary>
	public ref class FlatForm : public System::Windows::Forms::Form
	{
	public:
		FlatForm(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FlatForm();

	protected:		//	Methods Overrides
		virtual void		WndProc(Message % m) override;
		virtual void		OnHandleCreated(EventArgs ^ e) override;

	protected:		//	Methods
		virtual Void		OnNcHitTest(NcHitTestEventArgs ^% e);

	protected:		//	Properties Override
		property System::Windows::Forms::CreateParams^ CreateParams {
			System::Windows::Forms::CreateParams^ get(Void) override;
			Void set(System::Windows::Forms::CreateParams^ cp) override;
		}

	private:		//	Member Fields
		HWND				m_hWnd;
		NcParams			m_ncParams;

#pragma region Generated Codes

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(300,300);
			this->Text = L"FlatForm";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
#pragma endregion
	};

}}}