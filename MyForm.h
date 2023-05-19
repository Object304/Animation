#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <array>
#include <fstream>
#include <iostream>

namespace Graphic {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			pbPlot->Image = gcnew Bitmap(pbPlot->Width, pbPlot->Height);
			br = gcnew SolidBrush(Color::White);
			br_text = gcnew SolidBrush(Color::Black);
			pn_axes = gcnew Pen(Color::Black, 3);
			pn_line = gcnew Pen(Color::Blue, 3);
			pn_grid = gcnew Pen(Color::Gray, 1);
			printFont = gcnew System::Drawing::Font("Arial", 8);
			br_poly = gcnew SolidBrush(Color::Aquamarine);
			gr = Graphics::FromImage(pbPlot->Image);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pbPlot;
	protected:
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pbPlot = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPlot))->BeginInit();
			this->SuspendLayout();
			// 
			// pbPlot
			// 
			this->pbPlot->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pbPlot->Location = System::Drawing::Point(12, 12);
			this->pbPlot->Name = L"pbPlot";
			this->pbPlot->Size = System::Drawing::Size(1000, 900);
			this->pbPlot->TabIndex = 0;
			this->pbPlot->TabStop = false;
			this->pbPlot->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pbPlot_MouseDown);
			this->pbPlot->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pbPlot_MouseMove);
			this->pbPlot->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pbPlot_MouseUp);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1488, 954);
			this->Controls->Add(this->pbPlot);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPlot))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		Brush^ br, ^ br_text, ^ br_poly;
		Pen^ pn_axes, ^ pn_line, ^ pn_grid;
		System::Drawing::Font^ printFont;
		Graphics^ gr;
		bool mouseClick = false;
		const char* curName = "Data\\pic1.txt";
		int curNum = 0;

		void updateName() {
			String^ str = gcnew String(curName);
			str = str->Substring(0, 8);
			curNum++;
			curName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str + curNum + ".txt");
		}

		int getSize(const char* name) {
			int size = 0;
			FILE* fLog = fopen(name, "r");
			int a, b;
			while (fscanf(fLog, "%d\t%d\n", &a, &b) != EOF)
				size++;
			fclose(fLog);
			return size;
		}

		void Draw() {
			array<PointF>^ points = gcnew array<PointF>(getSize(curName));
			if (points->Length < 2)
				return;
			PointF point;
			FILE* fLog = fopen(curName, "r");
			int x, y;
			for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
				point.X = x;
				point.Y = y;
				points[i] = point;
			}
			fclose(fLog);
			gr->DrawLines(pn_line, points);
			pbPlot->Refresh();
		}

		void Clear() {
			gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
			pbPlot->Refresh();
		}

private: System::Void MyForm_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::C))
		Clear();
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::D)) {
		system("rd /s /q \"C:\\Users\\Zhon1\\Desktop\\ОБУЧЕНИЕ\\Инфа\\2 семестр\\CLI\\Анимация\\Animation\\Data\"");
		system("md \"C:\\Users\\Zhon1\\Desktop\\ОБУЧЕНИЕ\\Инфа\\2 семестр\\CLI\\Анимация\\Animation\\Data\"");
		curNum = 0;
		Clear();
		pbPlot->Refresh();
	}		
}
private: System::Void pbPlot_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (mouseClick == false)
		return;
	FILE* fLog = fopen(curName, "a");
	fprintf(fLog, "%d\t%d\n", e->X, e->Y);
	fclose(fLog);
	Draw();
}
private: System::Void pbPlot_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	mouseClick = true;
	updateName();
}
private: System::Void pbPlot_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	mouseClick = false;
}
};
}
