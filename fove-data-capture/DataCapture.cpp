// FOVE Data Example
// This shows how to fetch and output data from the FOVE service in a console program

#include "DataCapture.h"

// Use std namespace for convenience
using namespace std;
using namespace datacaptureapi;

void
DataCapture::TestPrintImage(Fove::SFVR_BitmapImage* eyeImage) {
	vector<unsigned char>::iterator iter;
	cout << "Eye Image : Begin" << endl;
	for (iter = eyeImage->image.begin(); iter != eyeImage->image.end(); iter++) {
		cout << *iter << " ";
	}
	cout << "Eye Image : End" << endl;
}

bool 
DataCapture::SaveImageToDisk(Fove::SFVR_BitmapImage* eyeImage, string filename) {

    /*
	ofstream imageStream(filename);
	if (!imageStream) {
		cerr << "Stream could not be opened" << endl;
		return false;
	}
	
	vector<unsigned char>::iterator iter;
	for (iter = eyeImage->image.begin(); iter != eyeImage->image.end(); iter++) {
		imageStream << *iter;
	}
	*/

	unsigned char* buffer = eyeImage->image.data();
	
	FILE *fd = fopen(filename.c_str(), "wb+");
	if (fd) {
		fprintf(stderr, "Writing image...");
		fwrite(buffer, sizeof(unsigned char), eyeImage->image.size(), fd);
	}
	fclose(fd);
	int a;
	cin >> a;
	
	return true;
}

// Create the IFVRHeadsetResearch object
void
DataCapture::CreateNewResearchHeadset() {
	Fove::IFVRHeadset* headsetBuffer = Fove::GetFVRHeadset();
	this->resHeadset = static_cast<Fove::IFVRHeadsetResearch*> (headsetBuffer);
}

void
DataCapture::CreateNewHeadset() {
	this->headset = Fove::GetFVRHeadset();
}

void
DataCapture::InitializeResearchHeadset() {
    CheckError(this->resHeadset->Initialise(
		Fove::EFVR_ClientCapabilities::Gaze | Fove::EFVR_ClientCapabilities::Orientation | Fove::EFVR_ClientCapabilities::Position ), "Initialise");
}

// setting up required research_capability code from given enum    
void
DataCapture::TurnOnResearchCapability() {
    const Fove::EFVR_ErrorCode eyeRegError = 
        this->resHeadset->RegisterResearchCapabilities(Fove::EFVR_ResearchCapabilities::EyeImage);
    
    switch (eyeRegError) {
        case Fove::EFVR_ErrorCode::None:
            cout << "Eye Registration complete" << endl;
            break;

        case Fove::EFVR_ErrorCode::Connect_NotConnected:
                cerr << "Not connected to service" << endl;
                break;

        case Fove::EFVR_ErrorCode::Data_NoUpdate:
            cerr << "No update" << endl;
            break;

        default:
            // Less common errors are simply logged with their numeric value
            cerr << "Error #" << EnumToUnderlyingValue(eyeRegError) << endl;
            break;
	}


	const Fove::EFVR_ErrorCode posRegError = 
        this->resHeadset->RegisterResearchCapabilities(Fove::EFVR_ResearchCapabilities::PositionImage);
    
    switch (posRegError) {
        case Fove::EFVR_ErrorCode::None:
            cout << "Position Registration complete" << endl;
            break;

        case Fove::EFVR_ErrorCode::Connect_NotConnected:
                cerr << "Not connected to service" << endl;
                break;

        case Fove::EFVR_ErrorCode::Data_NoUpdate:
            cerr << "No update" << endl;
            break;

        default:
            // Less common errors are simply logged with their numeric value
            cerr << "Error #" << EnumToUnderlyingValue(posRegError) << endl;
            break;
	}
}

void
DataCapture::InitializeHeadset() {
    CheckError(this->headset->Initialise(Fove::EFVR_ClientCapabilities::Gaze), "Initialise");
}

void
DataCapture::InitializeImages() {
    this->eyeImage.type = Fove::EFVR_BitmapImageType::StereoEye;
    this->positionImage.type = Fove::EFVR_BitmapImageType::Position;
}

DataCapture::DataCapture() {
    CreateNewResearchHeadset();
    CreateNewHeadset();
    InitializeResearchHeadset();
    TurnOnResearchCapability();
    InitializeHeadset();
    InitializeImages();
}

DataCapture::~DataCapture() {

}

auto
DataCapture::GetGazeVectorData(bool ifResearch) {
	Fove::EFVR_ErrorCode gazeError;
    if(ifResearch) {
		gazeError = this->resHeadset->GetGazeVectors(&this->leftGaze, &this->rightGaze);        
    }
    else {
		gazeError = this->headset->GetGazeVectors(&this->leftGaze, &this->rightGaze);        
    }
    switch (gazeError) {
		case Fove::EFVR_ErrorCode::None:
			// If there was no error, we are allowed to access the other members of the struct
			cout << "Left Gaze Vector: (" << fixed << setprecision(3)
			     << setw(6) << leftGaze.vector.x << ", "
			     << setw(6) << leftGaze.vector.y << ", "
			     << setw(6) << leftGaze.vector.z << ')' << endl;
			cout << "Right Gaze Vector: (" << fixed << setprecision(3)
			     << setw(6) << rightGaze.vector.x << ", "
			     << setw(6) << rightGaze.vector.y << ", "
			     << setw(6) << rightGaze.vector.z << ')' << endl;
			break;

		case Fove::EFVR_ErrorCode::Connect_NotConnected:
			cerr << "Not connected to service" << endl;
			break;

		case Fove::EFVR_ErrorCode::Data_NoUpdate:
			cerr << "No update" << endl;
			break;

		default:
			// Less common errors are simply logged with their numeric value
			cerr << "Error #" << EnumToUnderlyingValue(gazeError) << endl;
			break;
    }
}

Fove::SFVR_BitmapImage
DataCapture::GetEyeImageData() {
    const Fove::EFVR_ErrorCode eyeError = this->resHeadset->GetEyeImageData(&(this->eyeImage));
    switch (eyeError) {
        case Fove::EFVR_ErrorCode::None:
            cout << "[+] No Errors, Image Received" << endl;
            break;
        
        case Fove::EFVR_ErrorCode::Connect_NotConnected:
            cerr << "Not connected to service" << endl;
            break;

        case Fove::EFVR_ErrorCode::Data_NoUpdate:
            cerr << "No update" << endl;
            break;

        default:
            // Less common errors are simply logged with their numeric value
            cerr << "Error #" << EnumToUnderlyingValue(eyeError) << endl;
            // cout << static_cast<underlying_type<Fove::EFVR_ErrorCode>::type>(Fove::EFVR_ErrorCode::None) << endl;
            break;
    }

    return this->eyeImage;
}

auto 
DataCapture::GetPositionImageData() {
	const Fove::EFVR_ErrorCode posError = this->resHeadset->GetPositionImageData(&this->positionImage);
    switch(posError) {
        case Fove::EFVR_ErrorCode::None:
            cout << "Got my image : Dont know how to print it out !!" << endl;
            break;
        
        case Fove::EFVR_ErrorCode::Connect_NotConnected:
            cerr << "Not connected to service" << endl;
            break;

        case Fove::EFVR_ErrorCode::Data_NoUpdate:
            cerr << "No update" << endl;
            break;

        default:
            // Less common errors are simply logged with their numeric value
            cerr << "Error #" << EnumToUnderlyingValue(posError) << endl;
            // cout << static_cast<underlying_type<Fove::EFVR_ErrorCode>::type>(Fove::EFVR_ErrorCode::None) << endl;
            break;
    }
}

auto
DataCapture::GetPupilRadiusData() {
    const Fove::EFVR_ErrorCode pupilError = this->resHeadset->GetPupilRadius(&this->leftPupil, &this->rightPupil);
    switch(pupilError) {
		case Fove::EFVR_ErrorCode::None:
			cout << "Left Pupil Radius : " << leftPupil << endl;
			cout << "Right Pupil Radius : " << rightPupil << endl;
			break;
		
		case Fove::EFVR_ErrorCode::Connect_NotConnected:
			cerr << "Not connected to service" << endl;
			break;

		case Fove::EFVR_ErrorCode::Data_NoUpdate:
			cerr << "No update" << endl;
			break;

		default:
			// Less common errors are simply logged with their numeric value
			cerr << "Error #" << EnumToUnderlyingValue(pupilError) << endl;
			// cout << static_cast<underlying_type<Fove::EFVR_ErrorCode>::type>(Fove::EFVR_ErrorCode::None) << endl;
			break;
    }
}

bool
DataCapture::IsHardwareConnected() {
    bool ifConnected;
    this->headset->IsHardwareConnected(&ifConnected);
    return ifConnected;
}

bool
DataCapture::IsHardwareConnectedResearch() {
    bool ifConnected;
    this->resHeadset->IsHardwareConnected(&ifConnected);
    return ifConnected;
}

bool
DataCapture::IsHardwareReady() {
    bool ifReady;
    this->headset->IsHardwareReady(&ifReady);
    return ifReady;
}

bool
DataCapture::IsHardwareReadyResearch() {
    bool ifReady;
    this->resHeadset->IsHardwareReady(&ifReady);
    return ifReady;
}