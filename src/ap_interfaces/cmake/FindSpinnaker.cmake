# Find the Spinnaker library
#
#  Spinnaker_FOUND        - True if Spinnaker was found.
#  Spinnaker_LIBRARIES2    - The libraries needed to use Spinnaker
#  Spinnaker_INCLUDE_DIRS - Location of Spinnaker.h

unset(Spinnaker_FOUND)
unset(Spinnaker_INCLUDE_DIRS)
unset(Spinnaker_LIBRARIES1)
unset(Spinnaker_LIBRARIES2)
unset(Spinnaker_LIBRARIES3)
unset(Spinnaker_LIBRARIES4)
unset(Spinnaker_LIBRARIES5)
unset(Spinnaker_LIBRARIES6)
unset(Spinnaker_LIBRARIES7)
unset(Spinnaker_LIBRARIES8)
unset(Spinnaker_LIBRARIES9)
unset(Spinnaker_LIBRARIES10)
unset(Spinnaker_LIBRARIES11)
unset(Spinnaker_LIBRARIES12)
unset(Spinnaker_LIBRARIES13)


find_path(Spinnaker_INCLUDE_DIRS NAMES
  Spinnaker.h
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces
  )

find_library(Spinnaker_LIBRARIES1 NAMES 
  AdapterConfig_v140
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES2 NAMES 
  Spinnaker_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES3 NAMES 
  SpinnakerC_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES4 NAMES 
  SpinnakerCd_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES5 NAMES 
  Spinnakerd_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES6 NAMES 
  SpinnakerGUI_WPF_v140
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES7 NAMES 
  SpinnakerGUI_WPFd_v140
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES8 NAMES 
  SpinnakerGUISelector_WPF_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES9 NAMES 
  SpinUpdate_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES10 NAMES 
  SpinVideo_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES11 NAMES 
  SpinVideoC_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES12 NAMES 
  SpinVideoCd_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)
find_library(Spinnaker_LIBRARIES13 NAMES 
  SpinVideod_v140 
  PATHS
  D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/include/ap_interfaces/lib/vs2015
)


if(NOT Spinnaker_INCLUDE_DIRS OR NOT Spinnaker_LIBRARIES2)
  message(STATUS "Couldnt find Spinnaker.QAQ")

endif()
if (Spinnaker_INCLUDE_DIRS)
  message(STATUS "Find Spinnaker.h")
endif()

if (Spinnaker_INCLUDE_DIRS AND Spinnaker_LIBRARIES1 AND Spinnaker_LIBRARIES2 AND Spinnaker_LIBRARIES3 AND Spinnaker_LIBRARIES4 AND Spinnaker_LIBRARIES5 AND Spinnaker_LIBRARIES6 AND Spinnaker_LIBRARIES7 AND Spinnaker_LIBRARIES8 AND Spinnaker_LIBRARIES9 AND Spinnaker_LIBRARIES10 AND Spinnaker_LIBRARIES11 AND Spinnaker_LIBRARIES12 AND Spinnaker_LIBRARIES13)
  message(STATUS "Spinnaker found in the system^_^")
  set(Spinnaker_FOUND 1)
endif (Spinnaker_INCLUDE_DIRS AND Spinnaker_LIBRARIES1 AND Spinnaker_LIBRARIES2 AND Spinnaker_LIBRARIES3 AND Spinnaker_LIBRARIES4 AND Spinnaker_LIBRARIES5 AND Spinnaker_LIBRARIES6 AND Spinnaker_LIBRARIES7 AND Spinnaker_LIBRARIES8 AND Spinnaker_LIBRARIES9 AND Spinnaker_LIBRARIES10 AND Spinnaker_LIBRARIES11 AND Spinnaker_LIBRARIES12 AND Spinnaker_LIBRARIES13)
