#include <iostream>
#include "DataCapture.h"

int main(int argc, char const *argv[])
{
	int a;
	datacaptureapi::DataCapture capture;
	Fove::SFVR_BitmapImage image = capture.GetEyeImageData();

	capture.SaveImageToDisk(&image, "C:\\Users\\kapil\\Desktop\\image.bmp");

	std::cin >> a;

	return 0;
}