#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;
using namespace System::Drawing;

namespace Ivis { namespace Windows { namespace Forms {

	/// <summary>
	/// Summary for WindowFrame
	/// </summary>
	public ref class WindowFrame :  public System::ComponentModel::Component
	{
	public:
		WindowFrame(FlatForm^ target) :
			m_form(target)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		WindowFrame(System::ComponentModel::IContainer ^container) :
			m_form(nullptr)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WindowFrame()
		{
			if (components)
			{
				delete components;
			}
		}

	public:
		void Render(IntPtr hrgnClip);

	public:
		property FlatForm^ TargetForm { FlatForm^ get(void) { return m_form; } }

	private:
		FlatForm ^ m_form;

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
			components = gcnew System::ComponentModel::Container();
		}
#pragma endregion
	};

}}}