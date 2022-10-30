//
// CameraFLIR.cpp
// Implementation of the CameraFLIR class.
//

#include "CameraFLIR.h"
#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;
using namespace cv;
using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;

/// <summary>
/// Constructor
/// </summary>

CameraFLIR::CameraFLIR() 
   
{
   
   cout << "start constructor of CameraFLIR" << endl;
   mNumCameras = mCamList.GetSize();
   cout << mNumCameras << endl;
   for (int i = 0; i < MAX_CAMERAS; i++)
   {
      mpCam[i] = nullptr;
   }
}

/// <summary>
/// Destructor
/// </summary>
CameraFLIR::~CameraFLIR()
{
   for (int i = 0; i < MAX_CAMERAS; i++)
   {
      mpCam[i] = nullptr;
   }

   // Clear camera list before releasing system
   mCamList.Clear();
   // Release system
   mSystem->ReleaseInstance();

}

/// <summary>
/// Initialize the camera(s)
/// </summary>
int CameraFLIR::Initialize()
{
   mSystem = System::GetInstance();
   const LibraryVersion spinnakerLibraryVersion = mSystem->GetLibraryVersion();
   cout << "Spinnaker library version: " << spinnakerLibraryVersion.major << "." << spinnakerLibraryVersion.minor
      << "." << spinnakerLibraryVersion.type << "." << spinnakerLibraryVersion.build << endl
      << endl
      << endl;
   mCamList = mSystem->GetCameras();
   mNumCameras = mCamList.GetSize();
   cout << "detected device number: " << mNumCameras << endl;

   for (int index = 0; index < mNumCameras; index++)
   {
      mpCam[index] = mCamList.GetByIndex(index);

      // Retrieve TL device nodemap and print device information
      INodeMap& mNodeMapTLDevice = mpCam[index]->GetTLDeviceNodeMap();
      // Initialize camera
      mpCam[index]->Init();
      // Retrieve GenICam nodemap
      INodeMap& mNodeMap = mpCam[index]->GetNodeMap();

      // Retrieve enumeration node from nodemap
      CEnumerationPtr ptrAcquisitionMode = mNodeMap.GetNode("AcquisitionMode");
      if (!IsAvailable(ptrAcquisitionMode) || !IsWritable(ptrAcquisitionMode))
      {
         cout << "Unable to set acquisition mode to continuous (enum retrieval). Aborting..." << endl << endl;
         return 0;
      }
      // Retrieve entry node from enumeration node
      CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous");
      if (!IsAvailable(ptrAcquisitionModeContinuous) || !IsReadable(ptrAcquisitionModeContinuous))
      {
         cout << "Unable to set acquisition mode to continuous (entry retrieval). Aborting..." << endl << endl;
         return 0;
      }
      // Retrieve integer value from entry node
      const int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();
      // Set integer value from entry node as new value of enumeration node
      //MSH ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);

      mpCam[index]->BeginAcquisition();

      cout << "Acquiring images..." << endl;
      //
      // Retrieve device serial number for filename
      //
      // *** NOTES ***
      // The device serial number is retrieved in order to keep cameras from
      // overwriting one another. Grabbing image IDs could also accomplish
      // this.
      //
      gcstring deviceSerialNumber("");
      CStringPtr ptrStringSerial = mNodeMapTLDevice.GetNode("DeviceSerialNumber");
      if (IsAvailable(ptrStringSerial) && IsReadable(ptrStringSerial))
      {
         deviceSerialNumber = ptrStringSerial->GetValue();
         cout << "Device serial number retrieved as " << deviceSerialNumber << "..." << endl;
      }
   }

   return mNumCameras;
}

/// <summary>
/// Release the camera(s)
/// </summary>
void CameraFLIR::Release()
{
   // Ending acquisition appropriately helps ensure that devices clean up
   // properly and do not need to be power-cycled to maintain integrity.
   //
   for (int i = 0; i < mNumCameras; i++)
   {
      mpCam[i]->EndAcquisition();
      mpCam[i]->DeInit();
   }
}

/// <summary>
/// Grab frame from the camera(s)
/// </summary>
cv::Mat CameraFLIR::GrabFrame(int index)
{
   cv::Mat lMat;

   try
   {
      ImagePtr pResultImage = mpCam[index]->GetNextImage();

      //MSH : do we really need to convert this image?
      ImagePtr convertedImage = pResultImage->Convert(PixelFormat_Mono8, HQ_LINEAR);

      //cout<< "start converting to mat"<<endl;
      lMat = ConvertToMat(convertedImage);
      //cout<<"successfully convert to mat"<<endl;

      //MSH : do we really need this if we're converting?
      pResultImage->Release();
   }
   catch (Spinnaker::Exception& e)
   {
      cout << "Error: " << e.what() << endl;
      return cv::Mat();
   }

   return lMat;
}

/// <summary>
/// Conmvert FLIR format to OpenCV
/// </summary>
cv::Mat CameraFLIR::ConvertToMat(ImagePtr& imagePtr)
{
   mConvertedMatImage = imagePtr->Convert(PixelFormat_BGR8, NEAREST_NEIGHBOR);
   //cout << "convert from BGR8 to Mat"<<endl;
   //image data contains padding. When allocating Mat container size, you need to account for the X,Y image data padding. 
   return cv::Mat(static_cast<int>(mConvertedMatImage->GetHeight()) + static_cast<int>(mConvertedMatImage->GetYPadding()),
                  static_cast<int>(mConvertedMatImage->GetWidth()) + static_cast<int>(mConvertedMatImage->GetXPadding()),
                  CV_8UC3, mConvertedMatImage->GetData(), mConvertedMatImage->GetStride()).clone();
}
