#pragma once

#include "DataCapture.h"
#include <Windows.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

#include <vector>
#include <string>

using namespace msclr::interop;
using namespace System::Drawing;
using namespace System::IO;

namespace FOVEImageCapture {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// <summary>
	// Summary for LandingPage
	// </summary>
	public ref class LandingPage : public System::Windows::Forms::Form
	{
	public:
		LandingPage(void)
		{
			InitializeComponent();
			//
			// TODO: Add the constructor code here
			//
			this->dataCapture = new datacaptureapi::DataCapture();
			this->currentEmo = 0;
			this->dataLocation = "C:\\Users\\kapil\\Documents\\Dataset\\";
			this->folderName = "";
			this->counter = 0;
			this->bufferName = "Subject ";
			this->currentLocation = "";
			this->runtimeState = false;
			this->bufferingLocation = "C:\\Users\\Kapil\\Documents\\Dataset\\buffer.bmp";
			this->threadFlag = true;
			this->currImage = new Fove::SFVR_BitmapImage();
			// this->eyeImageStream = new ImageStream();
			// this->eyePictureBox->ImageLocation = bufferingLocation;
			this->thr = gcnew System::Threading::Thread(
				gcnew System::Threading::ThreadStart(this, &LandingPage::CaptureImagesToLoad));
			this->currThreadState = this->ThreadState[0];
		}

		void UpdateEyePictureBox(void) {
			if (this->eyePictureBox->InvokeRequired) {
				UpdateDelegate^ d = gcnew UpdateDelegate(this, &LandingPage::UpdateEyePictureBox);
				this->eyePictureBox->Invoke(d);
			}
			else {
				// this->eyePictureBox->Load(this->bufferingLocation);
				this->eyePictureBox->Refresh();
			}
		}

	protected:
		// <summary>
		// Clean up any resources being used.
		// </summary>
		~LandingPage()
		{
			if (components)
			{
				delete components;
			}
		}

	public: static datacaptureapi::DataCapture* dataCapture;
	public: delegate void UpdateDelegate(void);

	// private: static IStream* eyeImageStream;
	// private: static ImageStream* eyeImageStream;
	private: static Fove::SFVR_BitmapImage* currImage;
	private: const static array<System::String^>^ ThreadState = gcnew array<System::String^>
		{"PLAY", "SUSPEND", "RESUME"};
	private: static System::String^ currThreadState;
	private: const static array<System::String^>^ emotions = gcnew array<System::String^>
		{"Neutral", "Happy", "Sad", "Anger", "Disgust", "Fear", "Surprise"};
	private: static System::String^ dataLocation;
	private: static System::String^ folderName;
	private: static System::String^ currentLocation;
	private: static System::Int16 currentEmo;
	private: static System::Int64 counter;
	private: static System::String^ bufferName;
	private: static System::Boolean runtimeState;
	private: static System::Boolean threadFlag;
	private: static System::String^ bufferingLocation;
	private: static System::Threading::Thread^ thr;

	private: System::Windows::Forms::GroupBox^  spatialGB;
	private: System::Windows::Forms::GroupBox^  positionGB;
	private: System::Windows::Forms::GroupBox^  orientationGB;
	private: System::Windows::Forms::GroupBox^  eyeGB;
	private: System::Windows::Forms::GroupBox^  rightgazevectorGB;
	private: System::Windows::Forms::GroupBox^  leftgazevectorGB;
	private: System::Windows::Forms::GroupBox^  toolsGB;
	private: System::Windows::Forms::Button^  runtimebtn;

	private: System::Windows::Forms::Button^  calibrate;
	private: System::Windows::Forms::Button^  position;
	private: System::Windows::Forms::Button^  orientation;
	private: System::Windows::Forms::Button^  log;
	private: System::Windows::Forms::Button^  compositor;

	private: System::Windows::Forms::Button^  y_orientation;
	private: System::Windows::Forms::Button^  z_orientation;
	private: System::Windows::Forms::Button^  w_orientation;
	private: System::Windows::Forms::Button^  x_orientation;
	private: System::Windows::Forms::Label^  xorienlabel;
	private: System::Windows::Forms::Label^  zposlabel;
	private: System::Windows::Forms::Label^  yposlabel;

	private: System::Windows::Forms::Button^  z_position;
	private: System::Windows::Forms::Label^  xposlabel;
	private: System::Windows::Forms::Button^  y_position;
	private: System::Windows::Forms::Button^  x_position;

	private: System::Windows::Forms::Label^  yorienlabel;
	private: System::Windows::Forms::Label^  zorienlabel;
	private: System::Windows::Forms::Label^  worienlabel;
	private: System::Windows::Forms::Label^  brgazelabel;

	private: System::Windows::Forms::Label^  zrgazelabel;
	private: System::Windows::Forms::Button^  b_rightgaze;
	private: System::Windows::Forms::Label^  yrgazelabel;
	private: System::Windows::Forms::Button^  z_rightgaze;
	private: System::Windows::Forms::Label^  xrgazelabel;
	private: System::Windows::Forms::Button^  y_rightgaze;

	private: System::Windows::Forms::Label^  blgazelabel;
	private: System::Windows::Forms::Label^  zlgazelabel;
	private: System::Windows::Forms::Button^  b_leftgaze;
	private: System::Windows::Forms::Label^  ylgazelabel;
	private: System::Windows::Forms::Button^  z_leftgaze;
	private: System::Windows::Forms::Label^  xlgazelabel;
	private: System::Windows::Forms::Button^  y_leftgaze;
	private: System::Windows::Forms::Button^  x_leftgaze;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  quitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  configFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  logFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dataDirectoryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::PictureBox^  eyePictureBox;
	private: System::Windows::Forms::GroupBox^  eyeimageGB;
	private: System::Windows::Forms::Button^  captureimagebtn;

	private: System::Windows::Forms::Button^  saveimage;
	private: System::Windows::Forms::Button^  takeposbtn;
	private: System::Windows::Forms::Button^  takeorienbtn;
	private: System::Windows::Forms::Button^  rescalibbtn;
	private: System::Windows::Forms::ToolStripMenuItem^  binaryDirectoryToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  datadetailsGB;
	private: System::Windows::Forms::TextBox^  nametextbox;

	private: System::Windows::Forms::Label^  detnamelabel;
	private: System::Windows::Forms::Button^  nextemobtn;
	private: System::Windows::Forms::Button^  resetemobtn;
	private: System::Windows::Forms::GroupBox^  emotioninfoGB;
	private: System::Windows::Forms::PictureBox^  emopicturebx;
	private: System::Windows::Forms::Button^  submitdetailsbtn;
	private: System::Windows::Forms::Button^  x_rightgaze;
	private: System::Windows::Forms::Button^  cancelimagebtn;

	protected:

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
			this->spatialGB = (gcnew System::Windows::Forms::GroupBox());
			this->takeposbtn = (gcnew System::Windows::Forms::Button());
			this->takeorienbtn = (gcnew System::Windows::Forms::Button());
			this->positionGB = (gcnew System::Windows::Forms::GroupBox());
			this->zposlabel = (gcnew System::Windows::Forms::Label());
			this->yposlabel = (gcnew System::Windows::Forms::Label());
			this->z_position = (gcnew System::Windows::Forms::Button());
			this->xposlabel = (gcnew System::Windows::Forms::Label());
			this->y_position = (gcnew System::Windows::Forms::Button());
			this->x_position = (gcnew System::Windows::Forms::Button());
			this->orientationGB = (gcnew System::Windows::Forms::GroupBox());
			this->yorienlabel = (gcnew System::Windows::Forms::Label());
			this->zorienlabel = (gcnew System::Windows::Forms::Label());
			this->worienlabel = (gcnew System::Windows::Forms::Label());
			this->xorienlabel = (gcnew System::Windows::Forms::Label());
			this->y_orientation = (gcnew System::Windows::Forms::Button());
			this->z_orientation = (gcnew System::Windows::Forms::Button());
			this->w_orientation = (gcnew System::Windows::Forms::Button());
			this->x_orientation = (gcnew System::Windows::Forms::Button());
			this->eyeGB = (gcnew System::Windows::Forms::GroupBox());
			this->rescalibbtn = (gcnew System::Windows::Forms::Button());
			this->rightgazevectorGB = (gcnew System::Windows::Forms::GroupBox());
			this->brgazelabel = (gcnew System::Windows::Forms::Label());
			this->zrgazelabel = (gcnew System::Windows::Forms::Label());
			this->b_rightgaze = (gcnew System::Windows::Forms::Button());
			this->yrgazelabel = (gcnew System::Windows::Forms::Label());
			this->z_rightgaze = (gcnew System::Windows::Forms::Button());
			this->xrgazelabel = (gcnew System::Windows::Forms::Label());
			this->y_rightgaze = (gcnew System::Windows::Forms::Button());
			this->x_rightgaze = (gcnew System::Windows::Forms::Button());
			this->leftgazevectorGB = (gcnew System::Windows::Forms::GroupBox());
			this->blgazelabel = (gcnew System::Windows::Forms::Label());
			this->zlgazelabel = (gcnew System::Windows::Forms::Label());
			this->b_leftgaze = (gcnew System::Windows::Forms::Button());
			this->ylgazelabel = (gcnew System::Windows::Forms::Label());
			this->z_leftgaze = (gcnew System::Windows::Forms::Button());
			this->xlgazelabel = (gcnew System::Windows::Forms::Label());
			this->y_leftgaze = (gcnew System::Windows::Forms::Button());
			this->x_leftgaze = (gcnew System::Windows::Forms::Button());
			this->toolsGB = (gcnew System::Windows::Forms::GroupBox());
			this->calibrate = (gcnew System::Windows::Forms::Button());
			this->position = (gcnew System::Windows::Forms::Button());
			this->orientation = (gcnew System::Windows::Forms::Button());
			this->log = (gcnew System::Windows::Forms::Button());
			this->compositor = (gcnew System::Windows::Forms::Button());
			this->runtimebtn = (gcnew System::Windows::Forms::Button());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->quitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->configFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->logFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dataDirectoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->binaryDirectoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->eyePictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->eyeimageGB = (gcnew System::Windows::Forms::GroupBox());
			this->cancelimagebtn = (gcnew System::Windows::Forms::Button());
			this->captureimagebtn = (gcnew System::Windows::Forms::Button());
			this->saveimage = (gcnew System::Windows::Forms::Button());
			this->datadetailsGB = (gcnew System::Windows::Forms::GroupBox());
			this->submitdetailsbtn = (gcnew System::Windows::Forms::Button());
			this->nametextbox = (gcnew System::Windows::Forms::TextBox());
			this->detnamelabel = (gcnew System::Windows::Forms::Label());
			this->nextemobtn = (gcnew System::Windows::Forms::Button());
			this->resetemobtn = (gcnew System::Windows::Forms::Button());
			this->emotioninfoGB = (gcnew System::Windows::Forms::GroupBox());
			this->emopicturebx = (gcnew System::Windows::Forms::PictureBox());
			this->spatialGB->SuspendLayout();
			this->positionGB->SuspendLayout();
			this->orientationGB->SuspendLayout();
			this->eyeGB->SuspendLayout();
			this->rightgazevectorGB->SuspendLayout();
			this->leftgazevectorGB->SuspendLayout();
			this->toolsGB->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->eyePictureBox))->BeginInit();
			this->eyeimageGB->SuspendLayout();
			this->datadetailsGB->SuspendLayout();
			this->emotioninfoGB->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->emopicturebx))->BeginInit();
			this->SuspendLayout();
			// 
			// spatialGB
			// 
			this->spatialGB->Controls->Add(this->takeposbtn);
			this->spatialGB->Controls->Add(this->takeorienbtn);
			this->spatialGB->Controls->Add(this->positionGB);
			this->spatialGB->Controls->Add(this->orientationGB);
			this->spatialGB->Location = System::Drawing::Point(12, 31);
			this->spatialGB->Name = L"spatialGB";
			this->spatialGB->Size = System::Drawing::Size(288, 193);
			this->spatialGB->TabIndex = 0;
			this->spatialGB->TabStop = false;
			this->spatialGB->Text = L"Spatial";
			this->spatialGB->Enter += gcnew System::EventHandler(this, &LandingPage::spatialGB_Enter);
			// 
			// takeposbtn
			// 
			this->takeposbtn->Location = System::Drawing::Point(166, 155);
			this->takeposbtn->Name = L"takeposbtn";
			this->takeposbtn->Size = System::Drawing::Size(112, 27);
			this->takeposbtn->TabIndex = 10;
			this->takeposbtn->Text = L"Take Position";
			this->takeposbtn->UseVisualStyleBackColor = true;
			// 
			// takeorienbtn
			// 
			this->takeorienbtn->Location = System::Drawing::Point(26, 155);
			this->takeorienbtn->Name = L"takeorienbtn";
			this->takeorienbtn->Size = System::Drawing::Size(112, 27);
			this->takeorienbtn->TabIndex = 3;
			this->takeorienbtn->Text = L"Take Orientation";
			this->takeorienbtn->UseVisualStyleBackColor = true;
			// 
			// positionGB
			// 
			this->positionGB->Controls->Add(this->zposlabel);
			this->positionGB->Controls->Add(this->yposlabel);
			this->positionGB->Controls->Add(this->z_position);
			this->positionGB->Controls->Add(this->xposlabel);
			this->positionGB->Controls->Add(this->y_position);
			this->positionGB->Controls->Add(this->x_position);
			this->positionGB->Location = System::Drawing::Point(147, 19);
			this->positionGB->Name = L"positionGB";
			this->positionGB->Size = System::Drawing::Size(136, 104);
			this->positionGB->TabIndex = 1;
			this->positionGB->TabStop = false;
			this->positionGB->Text = L"Position";
			// 
			// zposlabel
			// 
			this->zposlabel->AutoSize = true;
			this->zposlabel->Location = System::Drawing::Point(4, 78);
			this->zposlabel->Name = L"zposlabel";
			this->zposlabel->Size = System::Drawing::Size(14, 13);
			this->zposlabel->TabIndex = 7;
			this->zposlabel->Text = L"Z";
			// 
			// yposlabel
			// 
			this->yposlabel->AutoSize = true;
			this->yposlabel->Location = System::Drawing::Point(4, 52);
			this->yposlabel->Name = L"yposlabel";
			this->yposlabel->Size = System::Drawing::Size(14, 13);
			this->yposlabel->TabIndex = 9;
			this->yposlabel->Text = L"Y";
			// 
			// z_position
			// 
			this->z_position->Location = System::Drawing::Point(19, 71);
			this->z_position->Name = L"z_position";
			this->z_position->Size = System::Drawing::Size(112, 27);
			this->z_position->TabIndex = 6;
			this->z_position->Text = L"0.000000";
			this->z_position->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->z_position->UseVisualStyleBackColor = true;
			// 
			// xposlabel
			// 
			this->xposlabel->AutoSize = true;
			this->xposlabel->Location = System::Drawing::Point(4, 26);
			this->xposlabel->Name = L"xposlabel";
			this->xposlabel->Size = System::Drawing::Size(14, 13);
			this->xposlabel->TabIndex = 9;
			this->xposlabel->Text = L"X";
			// 
			// y_position
			// 
			this->y_position->Location = System::Drawing::Point(19, 45);
			this->y_position->Name = L"y_position";
			this->y_position->Size = System::Drawing::Size(112, 27);
			this->y_position->TabIndex = 8;
			this->y_position->Text = L"0.000000";
			this->y_position->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->y_position->UseVisualStyleBackColor = true;
			// 
			// x_position
			// 
			this->x_position->Location = System::Drawing::Point(19, 19);
			this->x_position->Name = L"x_position";
			this->x_position->Size = System::Drawing::Size(112, 27);
			this->x_position->TabIndex = 8;
			this->x_position->Text = L"0.000000";
			this->x_position->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->x_position->UseVisualStyleBackColor = true;
			// 
			// orientationGB
			// 
			this->orientationGB->Controls->Add(this->yorienlabel);
			this->orientationGB->Controls->Add(this->zorienlabel);
			this->orientationGB->Controls->Add(this->worienlabel);
			this->orientationGB->Controls->Add(this->xorienlabel);
			this->orientationGB->Controls->Add(this->y_orientation);
			this->orientationGB->Controls->Add(this->z_orientation);
			this->orientationGB->Controls->Add(this->w_orientation);
			this->orientationGB->Controls->Add(this->x_orientation);
			this->orientationGB->Location = System::Drawing::Point(6, 19);
			this->orientationGB->Name = L"orientationGB";
			this->orientationGB->Size = System::Drawing::Size(137, 130);
			this->orientationGB->TabIndex = 0;
			this->orientationGB->TabStop = false;
			this->orientationGB->Text = L"Orientation";
			// 
			// yorienlabel
			// 
			this->yorienlabel->AutoSize = true;
			this->yorienlabel->Location = System::Drawing::Point(5, 52);
			this->yorienlabel->Name = L"yorienlabel";
			this->yorienlabel->Size = System::Drawing::Size(14, 13);
			this->yorienlabel->TabIndex = 8;
			this->yorienlabel->Text = L"Y";
			// 
			// zorienlabel
			// 
			this->zorienlabel->AutoSize = true;
			this->zorienlabel->Location = System::Drawing::Point(5, 76);
			this->zorienlabel->Name = L"zorienlabel";
			this->zorienlabel->Size = System::Drawing::Size(14, 13);
			this->zorienlabel->TabIndex = 7;
			this->zorienlabel->Text = L"Z";
			// 
			// worienlabel
			// 
			this->worienlabel->AutoSize = true;
			this->worienlabel->Location = System::Drawing::Point(2, 104);
			this->worienlabel->Name = L"worienlabel";
			this->worienlabel->Size = System::Drawing::Size(18, 13);
			this->worienlabel->TabIndex = 6;
			this->worienlabel->Text = L"W";
			// 
			// xorienlabel
			// 
			this->xorienlabel->AutoSize = true;
			this->xorienlabel->Location = System::Drawing::Point(5, 26);
			this->xorienlabel->Name = L"xorienlabel";
			this->xorienlabel->Size = System::Drawing::Size(14, 13);
			this->xorienlabel->TabIndex = 5;
			this->xorienlabel->Text = L"X";
			this->xorienlabel->Click += gcnew System::EventHandler(this, &LandingPage::label3_Click);
			// 
			// y_orientation
			// 
			this->y_orientation->Location = System::Drawing::Point(20, 45);
			this->y_orientation->Name = L"y_orientation";
			this->y_orientation->Size = System::Drawing::Size(112, 27);
			this->y_orientation->TabIndex = 4;
			this->y_orientation->Text = L"0.000000";
			this->y_orientation->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->y_orientation->UseVisualStyleBackColor = true;
			// 
			// z_orientation
			// 
			this->z_orientation->Location = System::Drawing::Point(20, 71);
			this->z_orientation->Name = L"z_orientation";
			this->z_orientation->Size = System::Drawing::Size(112, 27);
			this->z_orientation->TabIndex = 3;
			this->z_orientation->Text = L"0.000000";
			this->z_orientation->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->z_orientation->UseVisualStyleBackColor = true;
			// 
			// w_orientation
			// 
			this->w_orientation->Location = System::Drawing::Point(20, 97);
			this->w_orientation->Name = L"w_orientation";
			this->w_orientation->Size = System::Drawing::Size(112, 27);
			this->w_orientation->TabIndex = 2;
			this->w_orientation->Text = L"1.000000";
			this->w_orientation->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->w_orientation->UseVisualStyleBackColor = true;
			// 
			// x_orientation
			// 
			this->x_orientation->Location = System::Drawing::Point(20, 19);
			this->x_orientation->Name = L"x_orientation";
			this->x_orientation->Size = System::Drawing::Size(112, 27);
			this->x_orientation->TabIndex = 1;
			this->x_orientation->Text = L"0.000000";
			this->x_orientation->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->x_orientation->UseVisualStyleBackColor = true;
			this->x_orientation->Click += gcnew System::EventHandler(this, &LandingPage::button1_Click);
			// 
			// eyeGB
			// 
			this->eyeGB->Controls->Add(this->rescalibbtn);
			this->eyeGB->Controls->Add(this->rightgazevectorGB);
			this->eyeGB->Controls->Add(this->leftgazevectorGB);
			this->eyeGB->Location = System::Drawing::Point(300, 31);
			this->eyeGB->Name = L"eyeGB";
			this->eyeGB->Size = System::Drawing::Size(291, 193);
			this->eyeGB->TabIndex = 1;
			this->eyeGB->TabStop = false;
			this->eyeGB->Text = L"Eye";
			this->eyeGB->Enter += gcnew System::EventHandler(this, &LandingPage::eyeGB_Enter);
			// 
			// rescalibbtn
			// 
			this->rescalibbtn->Location = System::Drawing::Point(85, 155);
			this->rescalibbtn->Name = L"rescalibbtn";
			this->rescalibbtn->Size = System::Drawing::Size(112, 27);
			this->rescalibbtn->TabIndex = 11;
			this->rescalibbtn->Text = L"Restart Calibration";
			this->rescalibbtn->UseVisualStyleBackColor = true;
			// 
			// rightgazevectorGB
			// 
			this->rightgazevectorGB->Controls->Add(this->brgazelabel);
			this->rightgazevectorGB->Controls->Add(this->zrgazelabel);
			this->rightgazevectorGB->Controls->Add(this->b_rightgaze);
			this->rightgazevectorGB->Controls->Add(this->yrgazelabel);
			this->rightgazevectorGB->Controls->Add(this->z_rightgaze);
			this->rightgazevectorGB->Controls->Add(this->xrgazelabel);
			this->rightgazevectorGB->Controls->Add(this->y_rightgaze);
			this->rightgazevectorGB->Controls->Add(this->x_rightgaze);
			this->rightgazevectorGB->Location = System::Drawing::Point(146, 19);
			this->rightgazevectorGB->Name = L"rightgazevectorGB";
			this->rightgazevectorGB->Size = System::Drawing::Size(139, 130);
			this->rightgazevectorGB->TabIndex = 1;
			this->rightgazevectorGB->TabStop = false;
			this->rightgazevectorGB->Text = L"Right Gaze Vector";
			// 
			// brgazelabel
			// 
			this->brgazelabel->AutoSize = true;
			this->brgazelabel->Location = System::Drawing::Point(7, 104);
			this->brgazelabel->Name = L"brgazelabel";
			this->brgazelabel->Size = System::Drawing::Size(14, 13);
			this->brgazelabel->TabIndex = 11;
			this->brgazelabel->Text = L"B";
			// 
			// zrgazelabel
			// 
			this->zrgazelabel->AutoSize = true;
			this->zrgazelabel->Location = System::Drawing::Point(7, 78);
			this->zrgazelabel->Name = L"zrgazelabel";
			this->zrgazelabel->Size = System::Drawing::Size(14, 13);
			this->zrgazelabel->TabIndex = 13;
			this->zrgazelabel->Text = L"Z";
			// 
			// b_rightgaze
			// 
			this->b_rightgaze->Location = System::Drawing::Point(22, 97);
			this->b_rightgaze->Name = L"b_rightgaze";
			this->b_rightgaze->Size = System::Drawing::Size(112, 27);
			this->b_rightgaze->TabIndex = 10;
			this->b_rightgaze->Text = L"false";
			this->b_rightgaze->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->b_rightgaze->UseVisualStyleBackColor = true;
			// 
			// yrgazelabel
			// 
			this->yrgazelabel->AutoSize = true;
			this->yrgazelabel->Location = System::Drawing::Point(7, 52);
			this->yrgazelabel->Name = L"yrgazelabel";
			this->yrgazelabel->Size = System::Drawing::Size(14, 13);
			this->yrgazelabel->TabIndex = 15;
			this->yrgazelabel->Text = L"Y";
			// 
			// z_rightgaze
			// 
			this->z_rightgaze->Location = System::Drawing::Point(22, 71);
			this->z_rightgaze->Name = L"z_rightgaze";
			this->z_rightgaze->Size = System::Drawing::Size(112, 27);
			this->z_rightgaze->TabIndex = 12;
			this->z_rightgaze->Text = L"1.000000";
			this->z_rightgaze->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->z_rightgaze->UseVisualStyleBackColor = true;
			this->z_rightgaze->Click += gcnew System::EventHandler(this, &LandingPage::button14_Click);
			// 
			// xrgazelabel
			// 
			this->xrgazelabel->AutoSize = true;
			this->xrgazelabel->Location = System::Drawing::Point(7, 26);
			this->xrgazelabel->Name = L"xrgazelabel";
			this->xrgazelabel->Size = System::Drawing::Size(14, 13);
			this->xrgazelabel->TabIndex = 13;
			this->xrgazelabel->Text = L"X";
			// 
			// y_rightgaze
			// 
			this->y_rightgaze->Location = System::Drawing::Point(22, 45);
			this->y_rightgaze->Name = L"y_rightgaze";
			this->y_rightgaze->Size = System::Drawing::Size(112, 27);
			this->y_rightgaze->TabIndex = 14;
			this->y_rightgaze->Text = L"0.000000";
			this->y_rightgaze->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->y_rightgaze->UseVisualStyleBackColor = true;
			// 
			// x_rightgaze
			// 
			this->x_rightgaze->Location = System::Drawing::Point(22, 19);
			this->x_rightgaze->Name = L"x_rightgaze";
			this->x_rightgaze->Size = System::Drawing::Size(112, 27);
			this->x_rightgaze->TabIndex = 12;
			this->x_rightgaze->Text = L"0.000000";
			this->x_rightgaze->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->x_rightgaze->UseVisualStyleBackColor = true;
			// 
			// leftgazevectorGB
			// 
			this->leftgazevectorGB->Controls->Add(this->blgazelabel);
			this->leftgazevectorGB->Controls->Add(this->zlgazelabel);
			this->leftgazevectorGB->Controls->Add(this->b_leftgaze);
			this->leftgazevectorGB->Controls->Add(this->ylgazelabel);
			this->leftgazevectorGB->Controls->Add(this->z_leftgaze);
			this->leftgazevectorGB->Controls->Add(this->xlgazelabel);
			this->leftgazevectorGB->Controls->Add(this->y_leftgaze);
			this->leftgazevectorGB->Controls->Add(this->x_leftgaze);
			this->leftgazevectorGB->Location = System::Drawing::Point(6, 19);
			this->leftgazevectorGB->Name = L"leftgazevectorGB";
			this->leftgazevectorGB->Size = System::Drawing::Size(136, 130);
			this->leftgazevectorGB->TabIndex = 0;
			this->leftgazevectorGB->TabStop = false;
			this->leftgazevectorGB->Text = L"Left Gaze Vector";
			// 
			// blgazelabel
			// 
			this->blgazelabel->AutoSize = true;
			this->blgazelabel->Location = System::Drawing::Point(4, 104);
			this->blgazelabel->Name = L"blgazelabel";
			this->blgazelabel->Size = System::Drawing::Size(14, 13);
			this->blgazelabel->TabIndex = 15;
			this->blgazelabel->Text = L"B";
			// 
			// zlgazelabel
			// 
			this->zlgazelabel->AutoSize = true;
			this->zlgazelabel->Location = System::Drawing::Point(4, 78);
			this->zlgazelabel->Name = L"zlgazelabel";
			this->zlgazelabel->Size = System::Drawing::Size(14, 13);
			this->zlgazelabel->TabIndex = 17;
			this->zlgazelabel->Text = L"Z";
			// 
			// b_leftgaze
			// 
			this->b_leftgaze->Location = System::Drawing::Point(19, 97);
			this->b_leftgaze->Name = L"b_leftgaze";
			this->b_leftgaze->Size = System::Drawing::Size(112, 27);
			this->b_leftgaze->TabIndex = 14;
			this->b_leftgaze->Text = L"false";
			this->b_leftgaze->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->b_leftgaze->UseVisualStyleBackColor = true;
			this->b_leftgaze->Click += gcnew System::EventHandler(this, &LandingPage::b_leftgaze_Click);
			// 
			// ylgazelabel
			// 
			this->ylgazelabel->AutoSize = true;
			this->ylgazelabel->Location = System::Drawing::Point(4, 52);
			this->ylgazelabel->Name = L"ylgazelabel";
			this->ylgazelabel->Size = System::Drawing::Size(14, 13);
			this->ylgazelabel->TabIndex = 19;
			this->ylgazelabel->Text = L"Y";
			// 
			// z_leftgaze
			// 
			this->z_leftgaze->Location = System::Drawing::Point(19, 71);
			this->z_leftgaze->Name = L"z_leftgaze";
			this->z_leftgaze->Size = System::Drawing::Size(112, 27);
			this->z_leftgaze->TabIndex = 16;
			this->z_leftgaze->Text = L"1.000000";
			this->z_leftgaze->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->z_leftgaze->UseVisualStyleBackColor = true;
			// 
			// xlgazelabel
			// 
			this->xlgazelabel->AutoSize = true;
			this->xlgazelabel->Location = System::Drawing::Point(4, 26);
			this->xlgazelabel->Name = L"xlgazelabel";
			this->xlgazelabel->Size = System::Drawing::Size(14, 13);
			this->xlgazelabel->TabIndex = 21;
			this->xlgazelabel->Text = L"X";
			// 
			// y_leftgaze
			// 
			this->y_leftgaze->Location = System::Drawing::Point(19, 45);
			this->y_leftgaze->Name = L"y_leftgaze";
			this->y_leftgaze->Size = System::Drawing::Size(112, 27);
			this->y_leftgaze->TabIndex = 18;
			this->y_leftgaze->Text = L"0.000000";
			this->y_leftgaze->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->y_leftgaze->UseVisualStyleBackColor = true;
			// 
			// x_leftgaze
			// 
			this->x_leftgaze->Location = System::Drawing::Point(19, 19);
			this->x_leftgaze->Name = L"x_leftgaze";
			this->x_leftgaze->Size = System::Drawing::Size(112, 27);
			this->x_leftgaze->TabIndex = 20;
			this->x_leftgaze->Text = L"0.000000";
			this->x_leftgaze->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->x_leftgaze->UseVisualStyleBackColor = true;
			// 
			// toolsGB
			// 
			this->toolsGB->Controls->Add(this->calibrate);
			this->toolsGB->Controls->Add(this->position);
			this->toolsGB->Controls->Add(this->orientation);
			this->toolsGB->Controls->Add(this->log);
			this->toolsGB->Controls->Add(this->compositor);
			this->toolsGB->Controls->Add(this->runtimebtn);
			this->toolsGB->Location = System::Drawing::Point(591, 31);
			this->toolsGB->Margin = System::Windows::Forms::Padding(2);
			this->toolsGB->Name = L"toolsGB";
			this->toolsGB->Size = System::Drawing::Size(128, 193);
			this->toolsGB->TabIndex = 1;
			this->toolsGB->TabStop = false;
			this->toolsGB->Text = L"Tools";
			// 
			// calibrate
			// 
			this->calibrate->Location = System::Drawing::Point(7, 155);
			this->calibrate->Name = L"calibrate";
			this->calibrate->Size = System::Drawing::Size(112, 27);
			this->calibrate->TabIndex = 5;
			this->calibrate->Text = L"Calibrate";
			this->calibrate->UseVisualStyleBackColor = true;
			// 
			// position
			// 
			this->position->Location = System::Drawing::Point(7, 128);
			this->position->Name = L"position";
			this->position->Size = System::Drawing::Size(112, 27);
			this->position->TabIndex = 4;
			this->position->Text = L"Take Position";
			this->position->UseVisualStyleBackColor = true;
			// 
			// orientation
			// 
			this->orientation->Location = System::Drawing::Point(7, 101);
			this->orientation->Name = L"orientation";
			this->orientation->Size = System::Drawing::Size(112, 27);
			this->orientation->TabIndex = 3;
			this->orientation->Text = L"Take Orientation";
			this->orientation->UseVisualStyleBackColor = true;
			// 
			// log
			// 
			this->log->Location = System::Drawing::Point(7, 74);
			this->log->Name = L"log";
			this->log->Size = System::Drawing::Size(112, 27);
			this->log->TabIndex = 2;
			this->log->Text = L"Show Log";
			this->log->UseVisualStyleBackColor = true;
			// 
			// compositor
			// 
			this->compositor->Location = System::Drawing::Point(7, 47);
			this->compositor->Name = L"compositor";
			this->compositor->Size = System::Drawing::Size(112, 27);
			this->compositor->TabIndex = 1;
			this->compositor->Text = L"Start Compositor";
			this->compositor->UseVisualStyleBackColor = true;
			// 
			// runtimebtn
			// 
			this->runtimebtn->Location = System::Drawing::Point(7, 20);
			this->runtimebtn->Name = L"runtimebtn";
			this->runtimebtn->Size = System::Drawing::Size(112, 27);
			this->runtimebtn->TabIndex = 0;
			this->runtimebtn->Text = L"Start Runtime";
			this->runtimebtn->UseVisualStyleBackColor = true;
			this->runtimebtn->Click += gcnew System::EventHandler(this, &LandingPage::runtime_Click);
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->quitToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// quitToolStripMenuItem
			// 
			this->quitToolStripMenuItem->Name = L"quitToolStripMenuItem";
			this->quitToolStripMenuItem->Size = System::Drawing::Size(97, 22);
			this->quitToolStripMenuItem->Text = L"Quit";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->configFileToolStripMenuItem,
					this->logFileToolStripMenuItem, this->dataDirectoryToolStripMenuItem, this->binaryDirectoryToolStripMenuItem
			});
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->openToolStripMenuItem->Text = L"Open";
			// 
			// configFileToolStripMenuItem
			// 
			this->configFileToolStripMenuItem->Name = L"configFileToolStripMenuItem";
			this->configFileToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->configFileToolStripMenuItem->Text = L"Config File";
			// 
			// logFileToolStripMenuItem
			// 
			this->logFileToolStripMenuItem->Name = L"logFileToolStripMenuItem";
			this->logFileToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->logFileToolStripMenuItem->Text = L"Log File";
			// 
			// dataDirectoryToolStripMenuItem
			// 
			this->dataDirectoryToolStripMenuItem->Name = L"dataDirectoryToolStripMenuItem";
			this->dataDirectoryToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->dataDirectoryToolStripMenuItem->Text = L"Data Directory";
			// 
			// binaryDirectoryToolStripMenuItem
			// 
			this->binaryDirectoryToolStripMenuItem->Name = L"binaryDirectoryToolStripMenuItem";
			this->binaryDirectoryToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->binaryDirectoryToolStripMenuItem->Text = L"Binary Directory";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::HighlightText;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->openToolStripMenuItem, this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1014, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// eyePictureBox
			// 
			this->eyePictureBox->ImageLocation = L"C:\\Program Files\\FOVE\\bin\\assets\\noEyeData.png";
			this->eyePictureBox->Location = System::Drawing::Point(7, 22);
			this->eyePictureBox->Name = L"eyePictureBox";
			this->eyePictureBox->Size = System::Drawing::Size(640, 240);
			this->eyePictureBox->TabIndex = 6;
			this->eyePictureBox->TabStop = false;
			this->eyePictureBox->Click += gcnew System::EventHandler(this, &LandingPage::eyePictureBox_Click);
			// 
			// eyeimageGB
			// 
			this->eyeimageGB->Controls->Add(this->cancelimagebtn);
			this->eyeimageGB->Controls->Add(this->captureimagebtn);
			this->eyeimageGB->Controls->Add(this->saveimage);
			this->eyeimageGB->Controls->Add(this->eyePictureBox);
			this->eyeimageGB->Location = System::Drawing::Point(36, 228);
			this->eyeimageGB->Name = L"eyeimageGB";
			this->eyeimageGB->Size = System::Drawing::Size(655, 300);
			this->eyeimageGB->TabIndex = 7;
			this->eyeimageGB->TabStop = false;
			this->eyeimageGB->Text = L"Eye Image View";
			// 
			// cancelimagebtn
			// 
			this->cancelimagebtn->Location = System::Drawing::Point(506, 267);
			this->cancelimagebtn->Name = L"cancelimagebtn";
			this->cancelimagebtn->Size = System::Drawing::Size(112, 27);
			this->cancelimagebtn->TabIndex = 9;
			this->cancelimagebtn->Text = L"Cancel Image";
			this->cancelimagebtn->UseVisualStyleBackColor = true;
			this->cancelimagebtn->Click += gcnew System::EventHandler(this, &LandingPage::cancelimagebtn_Click);
			// 
			// captureimagebtn
			// 
			this->captureimagebtn->Location = System::Drawing::Point(29, 268);
			this->captureimagebtn->Name = L"captureimagebtn";
			this->captureimagebtn->Size = System::Drawing::Size(112, 27);
			this->captureimagebtn->TabIndex = 8;
			this->captureimagebtn->Text = L"Capture Image";
			this->captureimagebtn->UseVisualStyleBackColor = true;
			this->captureimagebtn->Click += gcnew System::EventHandler(this, &LandingPage::captureimagebtn_Click);
			// 
			// saveimage
			// 
			this->saveimage->Location = System::Drawing::Point(388, 267);
			this->saveimage->Name = L"saveimage";
			this->saveimage->Size = System::Drawing::Size(112, 27);
			this->saveimage->TabIndex = 7;
			this->saveimage->Text = L"Save Image";
			this->saveimage->UseVisualStyleBackColor = true;
			this->saveimage->Click += gcnew System::EventHandler(this, &LandingPage::saveimage_Click);
			// 
			// datadetailsGB
			// 
			this->datadetailsGB->Controls->Add(this->submitdetailsbtn);
			this->datadetailsGB->Controls->Add(this->nametextbox);
			this->datadetailsGB->Controls->Add(this->detnamelabel);
			this->datadetailsGB->Location = System::Drawing::Point(719, 31);
			this->datadetailsGB->Name = L"datadetailsGB";
			this->datadetailsGB->Size = System::Drawing::Size(283, 193);
			this->datadetailsGB->TabIndex = 8;
			this->datadetailsGB->TabStop = false;
			this->datadetailsGB->Text = L"Data Details";
			// 
			// submitdetailsbtn
			// 
			this->submitdetailsbtn->Location = System::Drawing::Point(86, 155);
			this->submitdetailsbtn->Name = L"submitdetailsbtn";
			this->submitdetailsbtn->Size = System::Drawing::Size(112, 27);
			this->submitdetailsbtn->TabIndex = 6;
			this->submitdetailsbtn->Text = L"Submit";
			this->submitdetailsbtn->UseVisualStyleBackColor = true;
			this->submitdetailsbtn->Click += gcnew System::EventHandler(this, &LandingPage::submitdetailsbtn_Click);
			// 
			// nametextbox
			// 
			this->nametextbox->BackColor = System::Drawing::SystemColors::Menu;
			this->nametextbox->Location = System::Drawing::Point(43, 17);
			this->nametextbox->Name = L"nametextbox";
			this->nametextbox->Size = System::Drawing::Size(233, 20);
			this->nametextbox->TabIndex = 1;
			this->nametextbox->TextChanged += gcnew System::EventHandler(this, &LandingPage::textBox1_TextChanged_1);
			// 
			// detnamelabel
			// 
			this->detnamelabel->AutoSize = true;
			this->detnamelabel->Location = System::Drawing::Point(6, 20);
			this->detnamelabel->Name = L"detnamelabel";
			this->detnamelabel->Size = System::Drawing::Size(35, 13);
			this->detnamelabel->TabIndex = 0;
			this->detnamelabel->Text = L"Name";
			this->detnamelabel->Click += gcnew System::EventHandler(this, &LandingPage::label2_Click);
			// 
			// nextemobtn
			// 
			this->nextemobtn->Location = System::Drawing::Point(28, 267);
			this->nextemobtn->Name = L"nextemobtn";
			this->nextemobtn->Size = System::Drawing::Size(112, 27);
			this->nextemobtn->TabIndex = 11;
			this->nextemobtn->Text = L"Next";
			this->nextemobtn->UseVisualStyleBackColor = true;
			this->nextemobtn->Click += gcnew System::EventHandler(this, &LandingPage::nextemobtn_Click);
			// 
			// resetemobtn
			// 
			this->resetemobtn->Location = System::Drawing::Point(146, 267);
			this->resetemobtn->Name = L"resetemobtn";
			this->resetemobtn->Size = System::Drawing::Size(112, 27);
			this->resetemobtn->TabIndex = 12;
			this->resetemobtn->Text = L"Reset";
			this->resetemobtn->UseVisualStyleBackColor = true;
			this->resetemobtn->Click += gcnew System::EventHandler(this, &LandingPage::resetemobtn_Click);
			// 
			// emotioninfoGB
			// 
			this->emotioninfoGB->Controls->Add(this->emopicturebx);
			this->emotioninfoGB->Controls->Add(this->resetemobtn);
			this->emotioninfoGB->Controls->Add(this->nextemobtn);
			this->emotioninfoGB->Location = System::Drawing::Point(691, 228);
			this->emotioninfoGB->Name = L"emotioninfoGB";
			this->emotioninfoGB->Size = System::Drawing::Size(288, 300);
			this->emotioninfoGB->TabIndex = 9;
			this->emotioninfoGB->TabStop = false;
			this->emotioninfoGB->Text = L"Emotion : Neutral";
			// 
			// emopicturebx
			// 
			this->emopicturebx->ImageLocation = L"C:\\Program Files\\FOVE\\bin\\assets\\neutral.png";
			this->emopicturebx->Location = System::Drawing::Point(89, 67);
			this->emopicturebx->Name = L"emopicturebx";
			this->emopicturebx->Size = System::Drawing::Size(115, 142);
			this->emopicturebx->TabIndex = 13;
			this->emopicturebx->TabStop = false;
			this->emopicturebx->Click += gcnew System::EventHandler(this, &LandingPage::emopicturebx_Click);
			// 
			// LandingPage
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Menu;
			this->ClientSize = System::Drawing::Size(1014, 550);
			this->Controls->Add(this->emotioninfoGB);
			this->Controls->Add(this->datadetailsGB);
			this->Controls->Add(this->eyeimageGB);
			this->Controls->Add(this->toolsGB);
			this->Controls->Add(this->eyeGB);
			this->Controls->Add(this->spatialGB);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"LandingPage";
			this->Text = L"ImageCapture Tool";
			this->Load += gcnew System::EventHandler(this, &LandingPage::LandingPage_Load);
			this->spatialGB->ResumeLayout(false);
			this->positionGB->ResumeLayout(false);
			this->positionGB->PerformLayout();
			this->orientationGB->ResumeLayout(false);
			this->orientationGB->PerformLayout();
			this->eyeGB->ResumeLayout(false);
			this->rightgazevectorGB->ResumeLayout(false);
			this->rightgazevectorGB->PerformLayout();
			this->leftgazevectorGB->ResumeLayout(false);
			this->leftgazevectorGB->PerformLayout();
			this->toolsGB->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->eyePictureBox))->EndInit();
			this->eyeimageGB->ResumeLayout(false);
			this->datadetailsGB->ResumeLayout(false);
			this->datadetailsGB->PerformLayout();
			this->emotioninfoGB->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->emopicturebx))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	private: System::Void LandingPage_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void spatialGB_Enter(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void eyeGB_Enter(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void runtime_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!this->runtimeState) {
			if (this->dataCapture->IsHardwareConnected() && this->dataCapture->IsHardwareReady()) {
				this->runtimeState = true;
				this->runtimebtn->Text = "Stop Runtime";
				// Fove::SFVR_BitmapImage image = this->dataCapture->GetEyeImageData();
				// this->dataCapture->SaveImageToDisk(&image, "C:\\Users\\Kapil\\Documents\\Dataset\\buffer.bmp");
				this->eyePictureBox->ImageLocation = "C:\\Users\\Kapil\\Documents\\Dataset\\buffer.bmp";
				
				if (this->currThreadState == this->ThreadState[1]) thr->Resume();
				else thr->Start();
			}
		}
		else {
			thr->Suspend();
			this->currThreadState = this->ThreadState[1];			
			this->runtimeState = false;
			this->runtimebtn->Text = "Start Runtime";
			this->eyePictureBox->ImageLocation = "C:\\Program Files\\FOVE\\bin\\assets\\noEyeData.png";
		}
	}

	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void b_leftgaze_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void captureimagebtn_Click(System::Object^  sender, System::EventArgs^  e) {
		*currImage = this->dataCapture->GetEyeImageData();
		this->thr->Suspend();
	}

	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void emopicturebx_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void eyePictureBox_Click(System::Object^  sender, System::EventArgs^  e) {

	}

	private: System::Void nextemobtn_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->currentEmo == 6) currentEmo = -1;
		++currentEmo;
		this->emopicturebx->ImageLocation = "C:\\Program Files\\FOVE\\bin\\assets\\" + this->emotions[currentEmo] + ".png";
		this->emotioninfoGB->Text = "Emotion : " + this->emotions[currentEmo];
	}

	private: System::Void resetemobtn_Click(System::Object^  sender, System::EventArgs^  e) {
		this->currentEmo = 0;
		this->emopicturebx->ImageLocation = "C:\\Program Files\\FOVE\\bin\\assets\\" + this->emotions[currentEmo] + ".png";
		this->emotioninfoGB->Text = "Emotion : " + this->emotions[currentEmo];
	}

	private: System::Void saveimage_Click(System::Object^  sender, System::EventArgs^  e) {
		marshal_context context;
		this->dataCapture->SaveImageToDisk(this->currImage, \
			context.marshal_as<std::string>(dataLocation) + context.marshal_as<std::string>(folderName) \
			+ "\\" + context.marshal_as<std::string>(this->emotions[currentEmo]) + ".bmp");
		this->thr->Resume();

		if (this->currentEmo == 6) {
			MessageBox::Show("All Images Captured");
			currentEmo = -1;
			this->nametextbox->Text = "";
		}
		else {
			++this->currentEmo;
			this->emopicturebx->ImageLocation = "C:\\Program Files\\FOVE\\bin\\assets\\" + this->emotions[currentEmo] + ".png";
			this->emotioninfoGB->Text = "Emotion : " + this->emotions[this->currentEmo];
		}
	}

	private: System::Void submitdetailsbtn_Click(System::Object^  sender, System::EventArgs^  e) {
		this->currentEmo = 0;
		this->emopicturebx->ImageLocation = "C:\\Program Files\\FOVE\\bin\\assets\\" + this->emotions[currentEmo] + ".png";
		this->emotioninfoGB->Text = "Emotion : " + this->emotions[currentEmo];

		if (this->nametextbox->Text == "") {
			++counter;
			this->folderName = this->bufferName + this->counter;
		}
		else {
			this->folderName = this->nametextbox->Text;
		}

		currentLocation = System::String::Concat(this->dataLocation, this->folderName);
		marshal_context context;

		if (IO::Directory::Exists(currentLocation)) {
			++counter;
			this->folderName = this->bufferName + this->counter;
			currentLocation = System::String::Concat(this->dataLocation, this->folderName);
		}

		CreateDirectory(context.marshal_as<const TCHAR*>(currentLocation), NULL);
	}

	private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {

	}

	private: array<unsigned char>^ VectorToArray(std::vector<unsigned char> image) {
		array<unsigned char>^ imageArray = gcnew array<unsigned char>(image.size());
		for(int i=0; i<image.size(); ++i) {
			imageArray[i] = image[i];
		}

		return imageArray;
	}

	private: System::Void CaptureImagesToLoad() {
		while (true) {
			DeleteFile(L"C:\\Users\\Kapil\\Documents\\Dataset\\buffer.bmp");
			Fove::SFVR_BitmapImage image = this->dataCapture->GetEyeImageData();
			// ULONG bytesRead;
			// this->eyeImageStream->Read(&image.image, image.image.size(), &bytesRead);
			// HBITMAP hbitmap = CreateBitmap(640, 240, 1, 32, image.image.data());
			MemoryStream^ mStream = gcnew MemoryStream();
			mStream->Write(VectorToArray(image.image), 0, image.image.size());
			Bitmap^ bmp = gcnew Bitmap(mStream, false);
			this->eyePictureBox->Image = bmp;
			// mStream->Dispose();
			// this->eyePictureBox->ImageLocation = this->bufferingLocation;
			// this->dataCapture->SaveImageToDisk(&image, "C:\\Users\\Kapil\\Documents\\Dataset\\buffer.bmp");
			this->UpdateEyePictureBox();
			Sleep(100);
		}
	}

	private: System::Void cancelimagebtn_Click(System::Object^  sender, System::EventArgs^  e) {
		this->thr->Resume();
	}
};

	public class ImageStream : public IStream
	{
	public:
		ImageStream(void)
		{

		}

		virtual ~ImageStream()
		{

		}

		void
			Read() {

		}

	};

}