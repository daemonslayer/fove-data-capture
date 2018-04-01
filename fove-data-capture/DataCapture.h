#ifndef __DATA_CAPTURE_H__
#define __DATA_CAPTURE_H__

#include "IFVRHeadset.h"
#include "IFVRHeadsetResearch.h"
#include "FoveResearchTypes.h"
#include "Util.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
// #include <thread>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cstdio>


namespace datacaptureapi {
	class DataCapture {
        public:
            DataCapture();
            virtual ~DataCapture();

            void CreateNewResearchHeadset();
            void CreateNewHeadset();

            void InitializeResearchHeadset();
            void TurnOnResearchCapability();
            void InitializeHeadset();
            void InitializeImages();

            auto GetGazeVectorData(bool);
            // Research Capability
            Fove::SFVR_BitmapImage GetEyeImageData();
            auto GetPositionImageData();
            auto GetPupilRadiusData();

            bool IsHardwareConnected();
            bool IsHardwareConnectedResearch();
            bool IsHardwareReady();
            bool IsHardwareReadyResearch();

            bool SaveImageToDisk(Fove::SFVR_BitmapImage*, std::string);
            void TestPrintImage(Fove::SFVR_BitmapImage*);

        private:
            Fove::IFVRHeadsetResearch* resHeadset;
            Fove::IFVRHeadset* headset;

            Fove::SFVR_BitmapImage eyeImage;
            Fove::SFVR_BitmapImage positionImage;

            float leftPupil, rightPupil;
            Fove::SFVR_GazeVector leftGaze, rightGaze;
            Fove::SFVR_GazeVector leftGazeRes, rightGazeRes;
    };
}

#endif // __DATA_CAPTURE_H__