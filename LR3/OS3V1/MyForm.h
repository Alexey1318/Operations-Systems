#pragma once
#include "windows.h" 
#include "TStr.h"
#include <time.h>
#include <cstdlib>

namespace OS3V1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			gr = pictureBox1->CreateGraphics();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::Label^  label3;


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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button1->Location = System::Drawing::Point(12, 450);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(199, 31);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Резервирование области";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button2->Location = System::Drawing::Point(217, 450);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(184, 31);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Выделение физ.памяти";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button3->Location = System::Drawing::Point(407, 450);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(201, 31);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Освобождение области";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button4->Location = System::Drawing::Point(614, 450);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(133, 31);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Сборка мусора";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(759, 421);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(38, 427);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(178, 17);
			this->label1->TabIndex = 6;
			this->label1->Text = L"- содержимое равно нулю";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->pictureBox2->BackColor = System::Drawing::Color::Blue;
			this->pictureBox2->Location = System::Drawing::Point(13, 427);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(19, 17);
			this->pictureBox2->TabIndex = 9;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->pictureBox3->BackColor = System::Drawing::SystemColors::Info;
			this->pictureBox3->Location = System::Drawing::Point(303, 427);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(19, 17);
			this->pictureBox3->TabIndex = 11;
			this->pictureBox3->TabStop = false;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(328, 427);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(133, 17);
			this->label2->TabIndex = 10;
			this->label2->Text = L"- зарезервировано";
			// 
			// pictureBox4
			// 
			this->pictureBox4->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->pictureBox4->BackColor = System::Drawing::SystemColors::Desktop;
			this->pictureBox4->Location = System::Drawing::Point(535, 427);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(19, 17);
			this->pictureBox4->TabIndex = 13;
			this->pictureBox4->TabStop = false;
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(560, 427);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(187, 17);
			this->label3->TabIndex = 12;
			this->label3->Text = L"- содержимое больше нуля";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(759, 493);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void*p;
		int n = 0;
		TStr* tstr;
		Color color; 
		Graphics^gr;
		int lenX = 10;
		int lenY = 10;

	private: void Repaint() {
		//создаем кисть для отрисовки
		Brush^brush;
		Pen^myPen = gcnew Pen(Color::DarkGray);
		myPen->Width = 2;

		TStr*adr = (TStr*)p; //создадим указатель на объект Tstr для работы с памятью
		MEMORY_BASIC_INFORMATION mbi; //переменная для получения информации о памяти
		gr->Clear(SystemColors::Control);

		int cX = 5, cY = 5;
		int sizeX = (pictureBox1->Width - 10) / lenX,
			sizeY = (pictureBox1->Height - 10) / lenY;
		for (int i = 0; i < lenX; i++) {
			for (int j = 0; j < lenY; j++) {
				//получаем информацию о диапазоне страниц виртуального адресного пространства 
				VirtualQuery((void*)adr, &mbi, sizeof(mbi)); 

				if (mbi.State == MEM_COMMIT) {  //если страницы выделены для работы с ними
					if (adr->n > 0) {
						// черный - если страница выделена и ее содержимое больше нуля
						color = Color::Black;
					}
					else {
						// синий - если страница выделена, но ее содержимое ноль
						color = Color::Blue;
					}
				}
				else {
					// бежевый - если страница просто зарезервирована
					color = Color::Beige;
				}

				brush = gcnew SolidBrush(color);
				if (cX < pictureBox1->Width - 5) {
					System::Drawing::Rectangle rect(cX, cY, sizeX, sizeY);
					gr->DrawRectangle(myPen, rect);
					gr->FillRectangle(brush, rect);
					cX += sizeX;
				}
				if (p != NULL) {
					adr++;
				}
			}
			cX = 5;
			cY += sizeY;
		}
	}

		//резервирование области памяти
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		// резервиуем пямать начиная с адреса р
		p = VirtualAlloc(NULL, sizeof(TStr) * lenX * lenY, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		//выполняем резервирование диапазона адресов
		Repaint();
	}
		//выделение физ. памяти
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		TStr* s = (TStr*)p;
		srand(time(NULL));
		// выделяем треть от всей доступной нам памяти
		for (int i = 0; i < (lenX*lenY) / 3; i++) {
			// тут указываем, в адрес какой ячейки от начала адресации что-то записать 
			s += rand() % (lenX*lenY);
			// выделение памяти начиная по адресу s размером sizeof(TStr)
			VirtualAlloc(s, sizeof(TStr), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (s->n == 0) {
				s->n = 1 + rand()%10;
			}
			else { 
				i--; 
			}
			s = (TStr*)p;
		}
		Repaint();
	}
		//освобождение области
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		VirtualFree(p, 0, MEM_RELEASE);   //освобождаем память
		//заново резервием память
		p = VirtualAlloc(NULL, sizeof(TStr) * lenX * lenY, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		Repaint();
		//заново резервируем свободные ячейки памяти
	}
		//чистка мусора
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		MEMORY_BASIC_INFORMATION ms;
		TStr *s = (TStr*)p;
		bool f = false;
		while (n != 0) n--;
		for (int i = 0; i < (lenX*lenY)/4; i++)
		{
			f = false;
			for (int j = 0; j < 4; j++)
			{
				VirtualQuery(s, &ms, sizeof(ms));
				//получаем информацию о памяти
				if (ms.State == MEM_COMMIT)  //если ячейки используются
				{
					if (s->n > 1) {
						f = true;   //проверяем их состояние
					}
					if (s->n > 0) {
						s->n--;
					}
				}
				s++;
			}
			if (f == false)
			{
				VirtualFree(s, sizeof(TStr), MEM_DECOMMIT); 
			}
		}
		Repaint();
	}
	};
}
