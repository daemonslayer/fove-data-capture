// FOVE Data Example
// This shows how to fetch and output data from the FOVE service in a console program

#include "IFVRHeadset.h"
#include "IFVRHeadsetResearch.h"
#include "FoveResearchTypes.h"
#include "Util.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <fstream>
#include <iterator>
#include <algorithm>

// Use std namespace for convenience
using namespace std;

void
PrintImage(Fove::SFVR_BitmapImage* eyeImage) {
	vector<unsigned char>::iterator iter;
	cout << "Eye Image : Begin" << endl;
	for (iter = eyeImage->image.begin(); iter != eyeImage->image.end(); iter++) {
		cout << *iter << " ";
	}
	cout << "Eye Image : End" << endl;
}

bool 
SaveImageToDisk(Fove::SFVR_BitmapImage* eyeImage, string filename) {

	unsigned char* buffer = eyeImage->image.data();
	
	FILE *fd = fopen(filename.c_str(), "wb");
	if (fd) {
		fprintf(stderr, "Writing image...");
		fwrite(buffer, sizeof(unsigned char), eyeImage->image.size(), fd);
	} 
	else (!fd) {
		return false;
	}

	fclose(fd);
	return true;
}

// Create the IFVRHeadset object
// This is managed by unique_ptr so it will be automatically deleted
// This program never exits (except possibly by exception), but RAII should always be used for safety
auto CreateNewHeadset() {
	return const unique_ptr<Fove::IFVRHeadset> headset{ Fove::GetFVRHeadset() };
}

auto InitializeHeadset() {

}

// Create the IFVRHeadsetResearch object
auto CreateNewHeadsetResearch() {
	// creating a headsetResearch ptr
	Fove::IFVRHeadset* imageGrabbingBuffer = Fove::GetFVRHeadset();
	Fove::IFVRHeadsetResearch* imageGrabbingHeadset;
	// static cast a IFVRHeadset to IFVRResearchHeadset
	imageGrabbingHeadset = static_cast<Fove::IFVRHeadsetResearch*> (imageGrabbingBuffer);

	return imageGrabbingHeadset;
}

auto InitializeHeadsetResearch(auto imageGrabbingHeadset) {
	// Initialise the headset
	// This allows us to declare what capabilities we would like enabled
	// Doing so may enable hardware or software, and thus consume resources, so it's important to only use capabilities that you know you need
	CheckError(imageGrabbingHeadset->Initialise(
		Fove::EFVR_ClientCapabilities::Gaze | Fove::EFVR_ClientCapabilities::Orientation | Fove::EFVR_ClientCapabilities::Position ), "Initialise");
	// setting up required research_capability code from given enum
	const Fove::EFVR_ErrorCode eyeRegError = imageGrabbingHeadset->RegisterResearchCapabilities(Fove::EFVR_ResearchCapabilities::EyeImage);
	const Fove::EFVR_ErrorCode posRegError = imageGrabbingHeadset->RegisterResearchCapabilities(Fove::EFVR_ResearchCapabilities::PositionImage);

	switch (eyeRegError) {
	
	case Fove::EFVR_ErrorCode::None:
		cout << "Eye Registration complete" << endl;
		break;

	case Fove::EFVR_ErrorCode::Connect_NotConnected:
		cerr << "Not connected to service" << endl;
		throw eyeRegError;
		break;

	case Fove::EFVR_ErrorCode::Data_NoUpdate:
		cerr << "No update" << endl;
		throw eyeRegError;
		break;

	default:
		// Less common errors are simply logged with their numeric value
		cerr << "Error #" << EnumToUnderlyingValue(eyeRegError) << endl;
		throw eyeRegError;
		break;
	}

	switch (posRegError) {
	
	case Fove::EFVR_ErrorCode::None:
		cout << "Position Registration complete" << endl;
		break;

	case Fove::EFVR_ErrorCode::Connect_NotConnected:
		cerr << "Not connected to service" << endl;
		throw posRegError;
		break;

	case Fove::EFVR_ErrorCode::Data_NoUpdate:
		cerr << "No update" << endl;
		throw posRegError;
		break;

	default:
		// Less common errors are simply logged with their numeric value
		cerr << "Error #" << EnumToUnderlyingValue(posRegError) << endl;
		throw posRegError;
		break;
	}
}

auto GetDataResearch(imageGrabbingHeadset) {
	Fove::SFVR_BitmapImage eyeImage;
	vector<unsigned char> eyeBuffer;
	eyeImage.type = Fove::EFVR_BitmapImageType::StereoEye;
	eyeImage.image = eyeBuffer;
	Fove::SFVR_BitmapImage posImage;
	vector<unsigned char> posBuffer;
	posImage.type = Fove::EFVR_BitmapImageType::Position;
	posImage.image = posBuffer;
	float leftPupil, rightPupil;

	const Fove::EFVR_ErrorCode eyeError = imageGrabbingHeadset->GetEyeImageData(&eyeImage);
	const Fove::EFVR_ErrorCode posError = imageGrabbingHeadset->GetPositionImageData(&posImage);
}

int 
main() try {

	imageGrabbingHeadset = CreateNewHeadsetResearch();
	InitializeHeadsetResearch(imageGrabbingHeadset);
	GetDataResearch(imageGrabbingHeadset);

	if (!SaveImageToDisk(&eyeImage, "eyeimage.bmp")) {
		cout << "Image could not be saved" << endl;
	}
	else {
		cout << "Image Saved" << endl;
	}
	
	if (!SaveImageToDisk(&posImage, "posimage.bmp")) {
		cout << "Image could not be saved" << endl;
	}
	else {
		cout << "Image Saved" << endl;
	}

} catch (const exception& e) {

	// If an exception is thrown for any reason, log it and exit
	// The FOVE api is designed not to throw externally, but the standard library can
	cerr << "Error: " << e.what() << endl;
	return EXIT_FAILURE;
	
}
