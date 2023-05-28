#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <array>
#include <fstream>
#include <iostream>
#include "Operations.h"
#include "Trajectory.h"
#include "Classes.h"

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
			pn_line = gcnew Pen(Color::Black, 4);
			printFont = gcnew System::Drawing::Font("Arial Bold Italic", 25);
			gr = Graphics::FromImage(pbPlot->Image);

			knight1 = gcnew Knight1;
			castle = gcnew Castle;
			sphere1 = gcnew Sphere1;
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
	private: System::Windows::Forms::Timer^ timer1;

	private: System::ComponentModel::IContainer^ components;

	protected:
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pbPlot = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
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
			// timer1
			// 
			this->timer1->Interval = 40;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(992, 620);
			this->Controls->Add(this->pbPlot);
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPlot))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		Brush^ br, ^ br_text;
		Pen^ pn_line;
		System::Drawing::Font^ printFont;
		Graphics^ gr;
		bool mouseClick = false;
		const char* curName = "Data\\picf1.txt";
		int curNum = 1;
		int ticks = 0;
		Knight1^ knight1;
		Castle^ castle;
		float radius = 0;
		Sphere1^ sphere1;
		

		void WorkSpace() {
			//restore();
			timer1->Enabled = true;
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
			for (int i = 1; i < 24	/*Convert::ToInt16(tbIn->Text)*/; i++) {
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

			//Scene 1

			//drawSky();
			//drawCastle();
			//drawGround();
			//drawKnight1();
			 
			//Scenes 2, 3
			//drawInside1(); 
			//drawInside2();
			//drawKnight2();
			
			//Scenes 4, 5

			//drawInside3();
			//drawSkeleton1();
			//drawSkeleton2();

			//Scene 6

			//drawInside3();
			//drawHand();

			//Scene 7

			//drawInside3();
			//drawSkeleton3();
			//drawSphere1();
			drawFinale();


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

			/////////////////////////////////////

			array<float, 2>^ M = knight1->Tr->next();

			/////////////////////////////////////
			
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

					///////////////////////

					knight1->add(points);
					for (int i = 0; i < knight1->initial->Length; i++)
						knight1->transformed[i] = apply(knight1->initial[i], M);
					
					///////////////////////

					gr->FillPolygon(br1, knight1->transformed);
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

				knight1->add(points);
				for (int i = 0; i < knight1->initial->Length; i++)
					knight1->transformed[i] = apply(knight1->initial[i], M);

				gr->DrawLines(pn_line, knight1->transformed);
			}
		}

		void drawCastle() {

			/////////////////////////////////////

			array<float, 2>^ M = castle->Tr->next();

			/////////////////////////////////////

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

					///////////////////////

					castle->add(points);
					for (int i = 0; i < castle->initial->Length; i++)
						castle->transformed[i] = apply(castle->initial[i], M);

					///////////////////////

					gr->FillPolygon(br1, castle->transformed);
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

				///////////////////////

				castle->add(points);
				for (int i = 0; i < castle->initial->Length; i++)
					castle->transformed[i] = apply(castle->initial[i], M);

				///////////////////////

				gr->DrawLines(pn_line, castle->transformed);
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
						br1 = gcnew SolidBrush(Color::GhostWhite);
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

		void drawHand() {

			//fills

			{
				String^ fileName = "Hand\\picf1.txt";
				Brush^ br1 = gcnew SolidBrush(Color::LightGray);
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

			//contours

			String^ fileName = "Hand\\pic1.txt";
			for (int i = 1; i < 24; i++) {
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
			}
		}

		//Scene 7

		void drawSkeleton3() {
			//fills

			/////////////////////////////////////

			array<float, 2>^ M = knight1->Tr->next();

			/////////////////////////////////////

			{
				String^ fileName = "Skeleton3\\picf1.txt";
				Brush^ br1;
				for (int i = 1; i < 11; i++) {
					if (i == 1)
						br1 = gcnew SolidBrush(Color::DarkSlateGray);
					if (i == 2)
						br1 = gcnew SolidBrush(Color::Brown);
					if (i == 3)
						br1 = gcnew SolidBrush(Color::GhostWhite);
					if (i == 7)
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

					///////////////////////

					knight1->add(points);
					for (int i = 0; i < knight1->initial->Length; i++)
						knight1->transformed[i] = apply(knight1->initial[i], M);

					///////////////////////

					gr->FillPolygon(br1, knight1->transformed);
				}
			}

			//contours

			String^ fileName = "Skeleton3\\pic1.txt";
			for (int i = 1; i < 24; i++) {
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

				knight1->add(points);
				for (int i = 0; i < knight1->initial->Length; i++)
					knight1->transformed[i] = apply(knight1->initial[i], M);

				gr->DrawLines(pn_line, knight1->transformed);
			}
		}

		void drawLightning(int key) {
			String^ fileName = "Lightning\\pic1.txt";
			for (int i = key; i < 11; i += 2) {
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
				Pen^ lightning = gcnew Pen(Color::BlueViolet, 3);
				gr->DrawLines(lightning, points);
			}
		}

		void drawSphere1() {
			array<float, 2>^ M = sphere1->Tr->next();
			{
				String^ fileName = "Sphere\\pic1.txt";
				Brush^ br1 = gcnew SolidBrush(Color::Blue);
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);

				///////////////////////

				sphere1->add(points);
				for (int i = 0; i < sphere1->initial->Length; i++)
					sphere1->transformed[i] = apply(sphere1->initial[i], M);

				///////////////////////

				gr->FillPolygon(br1, sphere1->transformed);
				
			}
			{
				String^ fileName = "Sphere\\picf1.txt";
				Brush^ br1 = gcnew SolidBrush(Color::BlueViolet);
				char* fName = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				array<PointF>^ points = gcnew array<PointF>(getSize(fName));
				PointF point;
				FILE* fLog = fopen(fName, "r");
				int x, y;
				for (int i = 0; fscanf(fLog, "%d\t%d\n", &x, &y) != EOF; i++) {
					point.X = x;
					point.Y = y;
					points[i] = point;
				}
				fclose(fLog);

				///////////////////////

				sphere1->add(points);
				for (int i = 0; i < sphere1->initial->Length; i++)
					sphere1->transformed[i] = apply(sphere1->initial[i], M);

				///////////////////////

				gr->FillPolygon(br1, sphere1->transformed);

			}
			String^ fileName = "Sphere\\pic1.txt";
			for (int i = 1; i < 9; i++) {
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

				///////////////////////

				sphere1->add(points);
				for (int i = 0; i < sphere1->initial->Length; i++)
					sphere1->transformed[i] = apply(sphere1->initial[i], M);

				///////////////////////

				gr->DrawLines(pn_line, sphere1->transformed);
			}
		}

		void drawInside4() {

			/////////////////////////////////////

			array<float, 2>^ M = castle->Tr->next();

			/////////////////////////////////////

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

					///////////////////////

					castle->add(points);
					for (int i = 0; i < castle->initial->Length; i++)
						castle->transformed[i] = apply(castle->initial[i], M);

					///////////////////////

					gr->FillPolygon(br1, castle->transformed);
					
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

				///////////////////////

				castle->add(points);
				for (int i = 0; i < castle->initial->Length; i++)
					castle->transformed[i] = apply(castle->initial[i], M);

				///////////////////////

				gr->DrawLines(pn_line, castle->transformed);
				Brush^ br2 = gcnew SolidBrush(Color::DarkGray);
				gr->FillRectangle(br2, Convert::ToDouble(apply(PointF(0, 245), M).X), Convert::ToDouble(apply(PointF(0, 245), M).Y), pbPlot->Image->Width, pbPlot->Image->Height);
			}
		}

		void drawFinale() {

			{
				String^ fileName = "Finale\\picf1.txt";
				Brush^ br1 = gcnew SolidBrush(Color::DarkOrange);
				gr->FillRectangle(br1, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
				for (int i = 1; i < 6; i++) {
					if (i == 1)
						br1 = gcnew SolidBrush(Color::Orange);
					if (i == 2)
						br1 = gcnew SolidBrush(Color::OrangeRed);
					if (i == 3)
						br1 = gcnew SolidBrush(Color::PaleVioletRed);
					if (i == 4)
						br1 = gcnew SolidBrush(Color::Gray);
					if (i == 5)
						br1 = gcnew SolidBrush(Color::DarkGray);
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


			String^ fileName = "Finale\\pic1.txt";
			for (int i = 1; i < 30; i++) {
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
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::D1)) {
		drawSky();
		drawCastle();
		drawGround();
		drawKnight1();
		pbPlot->Refresh();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::D2)) {
		drawInside1();
		pbPlot->Refresh();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::D3)) {
		drawInside2();
		drawKnight2();
		pbPlot->Refresh();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::D4)) {
		drawInside3();
		drawSkeleton1();
		pbPlot->Refresh();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::D5)) {
		drawSkeleton2();
		pbPlot->Refresh();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::D6)) {
		drawInside3();
		drawHand();
		pbPlot->Refresh();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::D7)) {
		drawInside3();
		drawSkeleton3();
		pbPlot->Refresh();
	}
	if (Convert::ToInt16(e->KeyChar) == Convert::ToInt16(System::Windows::Forms::Keys::S)) {
		ticks = 1120;
	}
}
private: System::Void pbPlot_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	FILE* fLog = fopen(curName, "a");
	fprintf(fLog, "%d\t%d\n", e->X, e->Y);
	fclose(fLog);
	Draw();
}
private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	ticks++;
	if (ticks < 325) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawSky();
		drawCastle();
		drawGround();
		drawKnight1();
		pbPlot->Refresh();
	}
	if (ticks > 375 && ticks < 425) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawInside1();
		pbPlot->Refresh();
	}
	if (ticks > 425 && ticks < 475) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawInside1();
		drawInside2();
		drawKnight2();
		pbPlot->Refresh();
	}
	if (ticks > 475 && ticks < 525) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawInside3();
		drawSkeleton1();
		pbPlot->Refresh();
	}
	if (ticks > 525 && ticks < 575) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawSkeleton2();
		pbPlot->Refresh();
	}
	if (ticks > 575 && ticks < 600) {
		Brush^ br1 = gcnew SolidBrush(Color::Blue);
		Brush^ br2 = gcnew SolidBrush(Color::BlueViolet);
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawSkeleton2();
		radius += 0.8;


		array<PointF>^ points = gcnew array<PointF>(3);
		points[0] = PointF(343, 277 + 10);
		points[1] = PointF(343, 277 - 10);
		points[2] = PointF(343 - radius * radius, 277);
		gr->FillPolygon(br2, points);
		points[2] = PointF(343 + radius * radius, 277);
		gr->FillPolygon(br2, points);
		points[0] = PointF(343 - 10, 277);
		points[1] = PointF(343 + 10, 277);
		points[2] = PointF(343, 277 - radius * radius);
		gr->FillPolygon(br2, points);
		points[2] = PointF(343, 277 + radius * radius);
		gr->FillPolygon(br2, points);


		gr->FillEllipse(br1, 343 - radius, 277 - radius, 2 * radius, 2 * radius);
		gr->FillEllipse(br1, 466 - radius, 241 - radius, 2 * radius, 2 * radius);
		pbPlot->Refresh();
	}
	if (ticks > 600 && ticks < 675) {
		Brush^ br1 = gcnew SolidBrush(Color::Blue);
		drawSkeleton2();
		gr->FillEllipse(br1, 343 - radius, 277 - radius, 2 * radius, 2 * radius);
		gr->FillEllipse(br1, 466 - radius, 241 - radius, 2 * radius, 2 * radius);
		pbPlot->Refresh();
	}
	if (ticks > 675 && ticks < 700) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawInside3();
		drawHand();
		int key = 1 + ticks % 2;
		drawLightning(key);
		pbPlot->Refresh();
	}
	if (ticks > 700 && ticks < 800) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawInside3();
		drawHand();
		if (ticks < 750) {
			int key = 1 + ticks % 2;
			drawLightning(key);
		}
		drawSphere1();
		pbPlot->Refresh();
	}
	if (ticks == 800) {
		sphere1->Update();
		castle->Update();
		knight1->Update();
	}
	if (ticks > 800 && ticks < 950) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawInside4();
		drawSkeleton3();
		drawSphere1();
		pbPlot->Refresh();
	}
	if (ticks == 950) {
		sphere1->Update1();
		castle->Update1();
	}
	if (ticks > 950 && ticks < 1025) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawInside4();
		drawSphere1();
		pbPlot->Refresh();
	}
	if (ticks > 1025 && ticks < 1053) {
		gr->FillRectangle(br, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		drawInside4();
		drawSphere1();
		array<PointF>^ points = gcnew array<PointF>(2);
		Pen^ pn = gcnew Pen(Color::LightBlue, 4);
		Brush^ br1 = gcnew SolidBrush(Color::LightSkyBlue);
		points[0] = PointF(338, 119);
		points[1] = PointF(323,	129);
		if (ticks > 1027) 
		{
			points = gcnew array<PointF>(3);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
		}
		if (ticks > 1029) 
		{
			points = gcnew array<PointF>(4);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
		}
		if (ticks > 1031)
		{
			points = gcnew array<PointF>(5);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
		}
		if (ticks > 1033) 
		{
			points = gcnew array<PointF>(6);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
			points[5] = PointF(303, 212);
		}
		if (ticks > 1035) 
		{
			points = gcnew array<PointF>(7);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
			points[5] = PointF(303, 212);
			points[6] = PointF(332, 224);
		}
		if (ticks > 1037) 
		{
			points = gcnew array<PointF>(8);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
			points[5] = PointF(303, 212);
			points[6] = PointF(332, 224);
			points[7] = PointF(313, 248);
		}
		if (ticks > 1039) 
		{	
			points = gcnew array<PointF>(9);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
			points[5] = PointF(303, 212);
			points[6] = PointF(332, 224);
			points[7] = PointF(313, 248);
			points[8] = PointF(338, 260);
		}
		if (ticks > 1041) 
		{
			points = gcnew array<PointF>(10);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
			points[5] = PointF(303, 212);
			points[6] = PointF(332, 224);
			points[7] = PointF(313, 248);
			points[8] = PointF(338, 260);
			points[9] = PointF(320, 281);
		}
		if (ticks > 1043) 
		{
			points = gcnew array<PointF>(11);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
			points[5] = PointF(303, 212);
			points[6] = PointF(332, 224);
			points[7] = PointF(313, 248);
			points[8] = PointF(338, 260);
			points[9] = PointF(320, 281);
			points[10] = PointF(342, 296);
		}
		if (ticks > 1045) {
			points = gcnew array<PointF>(6);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(0, 200);
			points[4] = PointF(0, 0);
			points[5] = PointF(200, 0);
			gr->FillPolygon(br1, points);
		}
		if (ticks > 1047) {
			points = gcnew array<PointF>(9);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
			points[5] = PointF(303, 212);
			points[6] = PointF(0, 270);
			points[7] = PointF(0, 0);
			points[8] = PointF(200, 0);
			gr->FillPolygon(br1, points);
		}
		if (ticks > 1049) {
			points = gcnew array<PointF>(11);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
			points[5] = PointF(303, 212);
			points[6] = PointF(332, 224);
			points[7] = PointF(313, 248);
			points[8] = PointF(0, 300);
			points[9] = PointF(0, 0);
			points[10] = PointF(200, 0);
			gr->FillPolygon(br1, points);
		}
		if (ticks > 1051) {
			points = gcnew array<PointF>(15);
			points[0] = PointF(338, 119);
			points[1] = PointF(323, 129);
			points[2] = PointF(341, 148);
			points[3] = PointF(308, 166);
			points[4] = PointF(333, 188);
			points[5] = PointF(303, 212);
			points[6] = PointF(332, 224);
			points[7] = PointF(313, 248);
			points[8] = PointF(338, 260);
			points[9] = PointF(320, 281);
			points[10] = PointF(342, 296);
			points[11] = PointF(100, pbPlot->Image->Height);
			points[12] = PointF(0, pbPlot->Image->Height);
			points[13] = PointF(0, 0);
			points[14] = PointF(200, 0);
			gr->FillPolygon(br1, points);
		}
		gr->DrawLines(pn, points);
		pbPlot->Refresh();
	}
	if (ticks > 1055 && ticks < 1120) {
		Brush^ br1 = gcnew SolidBrush(Color::LightSkyBlue);
		gr->FillRectangle(br1, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		pbPlot->Refresh();
	}
	if (ticks > 1120 && ticks < 1300) {
		Brush^ br1 = gcnew SolidBrush(Color::LightSkyBlue);
		Brush^ br2 = gcnew SolidBrush(Color::BlanchedAlmond);
		gr->FillRectangle(br1, 0, 0, pbPlot->Image->Width, pbPlot->Image->Height);
		gr->DrawString("std::cout << \"The End\";", printFont, br2, PointF((pbPlot->Image->Width) - 345, (pbPlot->Image->Height) - 80));
		gr->DrawString(")))", printFont, br2, PointF((pbPlot->Image->Width) - 345, (pbPlot->Image->Height) - 50));
		pbPlot->Refresh();
	}
	if (ticks > 1300 && ticks < 1400) {
		drawFinale();
		drawSkeleton1();
		Brush^ br2 = gcnew SolidBrush(Color::BlanchedAlmond);
		gr->DrawString("std::cout << \"The End\";", printFont, br2, PointF((pbPlot->Image->Width) - 345, (pbPlot->Image->Height) - 80));
		gr->DrawString(")))", printFont, br2, PointF((pbPlot->Image->Width) - 345, (pbPlot->Image->Height) - 50));
		pbPlot->Refresh();
	}
}
};
}
