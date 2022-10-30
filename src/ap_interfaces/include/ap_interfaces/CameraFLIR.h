//
// CameraFLIR.h
// Declaration of the CameraFLIR class.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <deque>
#include <iostream>
#include <iomanip>
#include <map>

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;

#define MAX_CAMERAS 4


/// <summary>
/// Contains functionality for an iGYM FLIR Camera.
/// </summary>

class CameraFLIR
{
   public:
      CameraFLIR();
      ~CameraFLIR();

      int Initialize();
      void Release();

      cv::Mat GrabFrame(int index);
      cv::Mat ConvertToMat(ImagePtr& imagePtr);

   private:
      unsigned int mNumCameras;

      CameraPtr   mpCam[MAX_CAMERAS];
      SystemPtr   mSystem;
      CameraList  mCamList;

      ImagePtr mConvertedMatImage;
};


