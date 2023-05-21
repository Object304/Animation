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
			pn_line = gcnew Pen(Color::Black, 3);
			pn_grid = gcnew Pen(Color::Gray, 1);
			printFont = gcnew System::Drawing::Font("Arial", 8);
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
	private: System::Windows::Forms::TextBox^ tbIn;
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
			this->tbIn = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPlot))->BeginInit();
			this->SuspendLayout();
			// 
			// pbPlot
			// 
			this->pbPlot->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pbPlot->Location = System::Drawing::Point(8, 8);
			this->pbPlot->Margin = System::Windows::Forms::Padding(2);
			this->pbPlot->Name = L"pbPlot";
			this->pbPlot->Size = System::Drawing::Size(667, 586);
			this->pbPlot->TabIndex = 0;
			this->pbPlot->TabStop = false;
			this->pbPlot->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pbPlot_MouseClick);
			// 
			// tbIn
			// 
			this->tbIn->Location = System::Drawing::Point(716, 261);
			this->tbIn->Name = L"tbIn";
			this->tbIn->Size = System::Drawing::Size(100, 20);
			this->tbIn->TabIndex = 1;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(992, 620);
			this->Controls->Add(this->tbIn);
			this->Controls->Add(this->pbPlot);
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPlot))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		Brush^ br, ^ br_text;
		Pen^ pn_axes, ^ pn_line, ^ pn_grid;
		System::Drawing::Font^ printFont;
		Graphics^ gr;
		bool mouseClick = false;
		const char* curName = "Data\\picf1.txt";
		int curNum = 1;

		void WorkSpace() {
			restore();
		}

		void updateName() {
			String^ str = gcnew String(curName);
			str = str->Substring(0, 9);
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
			curName = "Data\\pic1.txt";
			curNum = 1;
			pbPlot->Refresh();
		}

		void restore() {
			gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
			curNum = 1;
			String^ fileName = "Data\\pic1.txt";
			for (int i = 1; i < Convert::ToInt16(tbIn->Text); i++) {
				fileName = fileName->Substring(0, 8);
				fileName += i + ".txt";
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				if (points->Length < 2)
					return;
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);
				gr->DrawLines(pn_line, points);
				curNum = i;
			}
			updateName();
			pbPlot->Refresh();
		}

		void GO() {
			/*drawSky();
			drawCastle();
			drawGround();
			drawKnight1();
			drawInside1();
			drawInside2();
			drawKnight2();
			*/
			//drawInside3();
			drawSkeleton2();
			pbPlot->Refresh();
		}

		//Scene 1

		void drawGround() {
			String^ fileName = "Ground\\pic1.txt";
			char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
			array<PointF>^ points = gcnew array<PointF>(getSize(fName) + 2);
			if (points->Length < 2)
				return;
			PointF point;
			FILE* fLog = fopen(fName, "r");
			int x, y;
			for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
				point.X = x;
				point.Y = y;
				points[i] = point;
			}
			point.X = pbPlot->Image->Width;
			point.Y = pbPlot->Image->Width;
			points[17] = point;
			point.X = 0;
			point.Y = pbPlot->Image->Height;
			points[18] = point;
			fclose(fLog);
			Brush^ br1 = gcnew SolidBrush(Color::Green);
			gr->FillPolygon(br1, points);
			
		}

		void drawSky() {
			Brush^ br1 = gcnew SolidBrush(Color::DarkOrange);
			gr->FillRectangle(br1, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		}

		void drawKnight1() {

			//fills

			{
				String^ fileName = "Knight1\\picf1.txt";
				Brush^ br1;
				for (int i = 1; i < 6; i++) {
					if (i == 1)
						br1 = gcnew SolidBrush(Color::Gray);
					if (i == 2)
						br1 = gcnew SolidBrush(Color::DarkGray);
					if (i == 3)
						br1 = gcnew SolidBrush(Color::Orange);
					if (i == 5 || i == 4)
						br1 = gcnew SolidBrush(Color::Gray);
					/*if (i == 6)
						br1 = gcnew SolidBrush(Color::Gray);*/
					fileName = fileName->Substring(0, 12);
					fileName += i + ".txt";
					char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
					array<PointF>^ points = gcnew array<PointF>(getSize(fName));
					if (points->Length < 2)
						return;
					PointF point;
					FILE* fLog = fopen(fName, "r");
					int x, y;
					for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
						point.X = x;
						point.Y = y;
						points[i] = point;
					}
					fclose(fLog);
					gr->FillPolygon(br1, points);
				}
			}

			//contours

			String^ fileName = "Knight1\\pic1.txt";
			for (int i = 1; i < 77; i++) {
				fileName = fileName->Substring(0, 11);
				fileName += i + ".txt";
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				if (points->Length < 2)
					return;
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);
				gr->DrawLines(pn_line, points);
			}
		}

		void drawCastle() {

			{
				String^ fileName = "Castle\\picf1.txt";
				Brush^ br1;
				for (int i = 1; i < 24; i++) {
					if (i == 1)
						br1 = gcnew SolidBrush(Color::DarkGreen);
					if (i == 2)
						br1 = gcnew SolidBrush(Color::Gray);
					if (i == 3)
						br1 = gcnew SolidBrush(Color::Orange);
					fileName = fileName->Substring(0, 11);
					fileName += i + ".txt";
					char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
					array<PointF>^ points = gcnew array<PointF>(getSize(fName));
					if (points->Length < 2)
						return;
					PointF point;
					FILE* fLog = fopen(fName, "r");
					int x, y;
					for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
						point.X = x;
						point.Y = y;
						points[i] = point;
					}
					fclose(fLog);
					gr->FillPolygon(br1, points);
				}
			}

			String^ fileName = "Castle\\pic1.txt";
			for (int i = 1; i < 78; i++) {
				fileName = fileName->Substring(0, 10);
				fileName += i + ".txt";
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				if (points->Length < 2)
					return;
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);
				gr->DrawLines(pn_line, points);
			}
		}

		//Scenes 2, 3

		void drawInside1() {

			{
				String^ fileName = "Inside1\\picf1.txt";
				Brush^ br1 = gcnew SolidBrush(Color::DarkGray);
				gr->FillRectangle(br1, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
				for (int i = 1; i < 11; i++) {
					if (i == 1)
						br1 = gcnew SolidBrush(Color::Gray);
					if (i == 2)
						br1 = gcnew SolidBrush(Color::Gray);
					if (i == 3 || i == 4)
						br1 = gcnew SolidBrush(Color::Black);
					if (i == 5)
						br1 = gcnew SolidBrush(Color::DarkOrange);
					fileName = fileName->Substring(0, 12);
					fileName += i + ".txt";
					char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
					array<PointF>^ points = gcnew array<PointF>(getSize(fName));
					if (points->Length < 2)
						return;
					PointF point;
					FILE* fLog = fopen(fName, "r");
					int x, y;
					for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
						point.X = x;
						point.Y = y;
						points[i] = point;
					}
					fclose(fLog);
					gr->FillPolygon(br1, points);
				}
			}


			String^ fileName = "Inside1\\pic1.txt";
			for (int i = 1; i < 30; i++) {
				fileName = fileName->Substring(0, 11);
				fileName += i + ".txt";
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				if (points->Length < 2)
					return;
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);
				gr->DrawLines(pn_line, points);
			}
		}

		void drawInside2() {
			{
				String^ fileName = "Inside2\\picf1.txt";
				Brush^ br1 = gcnew SolidBrush(Color::DarkGray);
				gr->FillRectangle(br1, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
				for (int i = 1; i < 13; i++) {
					if (i == 1)
						br1 = gcnew SolidBrush(Color::Gray);
					if (i == 2)
						br1 = gcnew SolidBrush(Color::DarkOrange);
					if (i == 3 || i == 4)
						br1 = gcnew SolidBrush(Color::Gray);
					if (i == 5)
						br1 = gcnew SolidBrush(Color::DarkOrange);
					if (i == 11)
						br1 = gcnew SolidBrush(Color::Black);
					fileName = fileName->Substring(0, 12);
					fileName += i + ".txt";
					char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
					array<PointF>^ points = gcnew array<PointF>(getSize(fName));
					if (points->Length < 2)
						return;
					PointF point;
					FILE* fLog = fopen(fName, "r");
					int x, y;
					for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
						point.X = x;
						point.Y = y;
						points[i] = point;
					}
					fclose(fLog);
					gr->FillPolygon(br1, points);
				}
			}


			String^ fileName = "Inside2\\pic1.txt";
			for (int i = 1; i < 31; i++) {
				fileName = fileName->Substring(0, 11);
				fileName += i + ".txt";
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				if (points->Length < 2)
					return;
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);
				gr->DrawLines(pn_line, points);
			}
		}

		void drawKnight2() {
			//fills

			{
				String^ fileName = "Knight2\\picf1.txt";
				Brush^ br1;
				for (int i = 1; i < 5; i++) {
					if (i == 1)
						br1 = gcnew SolidBrush(Color::DarkGray);
					if (i == 2)
						br1 = gcnew SolidBrush(Color::Gray);
					if (i == 3)
						br1 = gcnew SolidBrush(Color::Gray);
					if (i == 4)
						br1 = gcnew SolidBrush(Color::Orange);
					fileName = fileName->Substring(0, 12);
					fileName += i + ".txt";
					char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
					array<PointF>^ points = gcnew array<PointF>(getSize(fName));
					if (points->Length < 2)
						return;
					PointF point;
					FILE* fLog = fopen(fName, "r");
					int x, y;
					for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
						point.X = x;
						point.Y = y;
						points[i] = point;
					}
					fclose(fLog);
					gr->FillPolygon(br1, points);
				}
			}

			//contours

			String^ fileName = "Knight2\\pic1.txt";
			for (int i = 1; i < 61; i++) {
				fileName = fileName->Substring(0, 11);
				fileName += i + ".txt";
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				if (points->Length < 2)
					return;
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);
				gr->DrawLines(pn_line, points);
			}
		}

		//Scenes 4, 5

		void drawInside3() {
			drawInside1();
			Brush^ br1 = gcnew SolidBrush(Color::DarkGray);
			gr->FillRectangle(br1, 0, 245, pbPlot->Image->Width, pbPlot->Image->Height);
		}

		void drawSkeleton1() {
			//fills

			{
				String^ fileName = "Skeleton1\\picf1.txt";
				Brush^ br1;
				for (int i = 1; i < 6; i++) {
					if (i == 1)
						br1 = gcnew SolidBrush(Color::White);
					if (i == 4)
						br1 = gcnew SolidBrush(Color::DarkSlateGray);
					if (i == 5)
						br1 = gcnew SolidBrush(Color::Brown);
					fileName = fileName->Substring(0, 14);
					fileName += i + ".txt";
					char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
					array<PointF>^ points = gcnew array<PointF>(getSize(fName));
					if (points->Length < 2)
						return;
					PointF point;
					FILE* fLog = fopen(fName, "r");
					int x, y;
					for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
						point.X = x;
						point.Y = y;
						points[i] = point;
					}
					fclose(fLog);
					gr->FillPolygon(br1, points);
				}
			}

			//contours

			String^ fileName = "Skeleton1\\pic1.txt";
			for (int i = 1; i < 4; i++) {
				fileName = fileName->Substring(0, 13);
				fileName += i + ".txt";
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				if (points->Length < 2)
					return;
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);
				gr->DrawLines(pn_line, points);
			}
		}

		void drawSkeleton2() {
			//fills

			Brush^ br2 = gcnew SolidBrush(System::Drawing::Color::Black);
			gr->FillRectangle(br2, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
			{
				String^ fileName = "Skeleton2\\picf1.txt";
				Brush^ br1;
				for (int i = 1; i < 8; i++) {
					if (i == 1)
						br1 = gcnew SolidBrush(Color::DarkGray);
					if (i == 2)
						br1 = gcnew SolidBrush(Color::Black);
					if (i == 3)
						br1 = gcnew SolidBrush(Color::Gray);
					fileName = fileName->Substring(0, 14);
					fileName += i + ".txt";
					char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
					array<PointF>^ points = gcnew array<PointF>(getSize(fName));
					if (points->Length < 2)
						return;
					PointF point;
					FILE* fLog = fopen(fName, "r");
					int x, y;
					for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
						point.X = x;
						point.Y = y;
						points[i] = point;
					}
					fclose(fLog);
					gr->FillPolygon(br1, points);
				}
			}

			//contours

			String^ fileName = "Skeleton2\\pic1.txt";
			for (int i = 1; i < 34; i++) {
				fileName = fileName->Substring(0, 13);
				fileName += i + ".txt";
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				if (points->Length < 2)
					return;
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);
				gr->DrawLines(pn_line, points);
			}



			//another fill

			fileName = "Skeleton2\\picf8.txt";
			Brush^ br1 = gcnew SolidBrush(Color::Brown);
			char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
			array<PointF>^ points = gcnew array<PointF>(getSize(fName));
			if (points->Length < 2)
				return;
			PointF point;
			FILE* fLog = fopen(fName, "r");
			int x, y;
			for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
				point.X = x;
				point.Y = y;
				points[i] = point;
			}
			fclose(fLog);
			gr->FillPolygon(br1, points);

			//another contour

			fileName = "Skeleton2\\picAdd.txt";
			fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
			points = gcnew array<PointF>(getSize(fName));
			if (points->Length < 2)
				return;
			fLog = fopen(fName, "r");
			for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
				point.X = x;
				point.Y = y;
				points[i] = point;
			}
			fclose(fLog);
			gr->DrawLines(pn_line, points);
		}

		//Scene 6

		

private: System::Void MyForm_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::C))
		Clear();
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::D)) {
		system("rd /s /q \"C:\\Users\\Zhon1\\Desktop\\ОБУЧЕНИЕ\\Инфа\\2 семестр\\CLI\\Анимация\\Animation\\Data\"");
		system("md \"C:\\Users\\Zhon1\\Desktop\\ОБУЧЕНИЕ\\Инфа\\2 семестр\\CLI\\Анимация\\Animation\\Data\"");
		curNum = 1;
		Clear();
		pbPlot->Refresh();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::Enter)) {
		WorkSpace();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::Space)) {
		updateName();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::G)) {
		GO();
	}
}
private: System::Void pbPlot_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	FILE* fLog = fopen(curName, "a");
	fprintf(fLog, "%d\t%d\n", e->X, e->Y);
	fclose(fLog);
	Draw();
}
};
}
