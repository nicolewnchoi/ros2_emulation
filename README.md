# Ros2 Rearchitecture

## Main Branch:

Main branch establish a desired architecture in the future, since we haven't included RFID and UI functions in the code. 

### Overall Structure
![structure](pic1.jpg)
Main components:

1. CV (detecting players)
2. RFID (rectifying the coordinate)
3. Unity (game logic and displaying)

The general process is as follow:
1. The CV part is responsible for detecting each player and sending detected coordinate message. 
2. The RFID get the raw coordinate and process the date to match each coordinate with correct ID and then send this message to the system as well.
3. The unity uses raw coordinate for game logic and render the output to camera. If modifications has been made by RFID, those modifications will be adjusted in Unity as well. 

## IGYM_oldversion Branch:

This branch is used for testing detection code (migrate the old code). It doesn't include the FLIR camera.

## add_FLIR cam Branch:

This branch adds the FLIR camera and is used for real field test.

# Ros2 Highlights

We build a new message type and uses it as the conveying message in our ROS2 system. More info about the message type can be found in source code.

## Multithread
In each node, multithread is used so that processing data and sending data won't intervene each other. For now, manual lock is not used except for those implemented by Ros2 system.

## Unity
More information about how ros2 and unity is integrated can be found on the official [site](https://github.com/Unity-Technologies/Unity-Robotics-Hub). After testing the delays is about 15 ms(under ubuntu, windows systems have some different statistics probably due to different reasons such as unofficial supports or tasks priority):
1. about 50% delays are below 10ms.
2. about 90% delays are below 20ms.

## CV
1, Player_detection part only utilizes the core part of old code and delete the useless part due to the camera

2, In the .cmake file and player_detection node, I use the absolute path. I will change it to relative path in the future 

# Readme Portion from desktop

unity install
based on version that supports ROS-TCP endpoint
archive https://unity3d.com/get-unity/download/archive
2020.3.16f1
Check Microsoft Visual Studio Community 2019
Universal Windows Platform Build Support
Windows Build Support (IL2CPP)
Documentation (default checked)

Question regarding personal license for unity editor.

Visual studio community continued install
Workloads: Desktop development with C++
Game development with Unity
On individual components, make sure no C++ CMake tools are selected.

ros2
Installation problems with ros2 foxy for windows 10 regarding missing QT
https://answers.ros.org/question/370180/cmake-error-when-compiling-ros_tutorials-packages-in-windows-10-ros-2-foxy-fitzroy-patch-release-4/


update opencv to 4.3.0 
https://docs.opencv.org/4.3.0/d3/d52/tutorial_windows_install.html#tutorial_windows_install_prebuilt

failed to find opencv 4.3.0
could not find a configuration file for package 'opencv'is compatible with requested version"4.3.0"

Change a version of ros2 installation(current version):
https://ms-iot.github.io/ROSOnWindows/GettingStarted/SetupRos2.html

Unity:
169.254.47.120

169.254.242.195 camera


Suggested follow
https://ms-iot.github.io/ROSOnWindows/GettingStarted/SetupRos2.html
Ran into issue,
trying to do binary from https://docs.ros.org/en/foxy/Installation/Windows-Install-Binary.html
You may need to upgrade pip with the following command "python -m pip install --upgrade pip"
Seems to be okay. 

Github Desktop install https://desktop.github.com/
Repo https://github.com/ruotongg/ros2_emulation

Flir Camera Software
https://www.flir.com/products/spinnaker-sdk/?vertical=machine%20vision&segment=iis > Download Now > Windows > Latest Spinnaker Full SDK > SpinnakerSDK_FULL_2.7.0.128_x64.exe
or
https://flir.app.boxcn.net/v/SpinnakerSDK/file/982785476681

After download open the installer. Select the  "camera evaluation" option.
On the next page, unselect "Participate in the Spinnaker feedback program".



QT path issue
https://answers.ros.org/question/354707/qtqpaplugin-could-not-find-the-qt-platform-plugin-windows-in/


Hook up camera. Open spinview, configure this camera, close

front-end
nvm: https://github.com/coreybutler/nvm-windows
nvm install latest
install https://github.com/RobotWebTools/ros2-web-bridge


Rememebr to open camera in spinnaker and set frame rate

running procedure:
camera detection part:
#call C:\dev\ros2_foxy\ros2-windows\local_setup.bat(official version)
c:\opt\ros\foxy\x64\setup.bat &&
cd C:\ros2newarch\ros2\ros2_emulation\src 
colcon build --merge-install --packages-select ap_interfaces
call install\setup.bat
ros2 run ap_interfaces player_detection

--
c:\opt\ros\foxy\x64\setup.bat &&cd C:\ros2newarch\ros2\ros2_emulation\src && call install\setup.bat
--
colcon build --merge-install --packages-select ap_interfaces --event-handlers console_direct+ 
-----------

unity-ros bridge:
open a new terminal
c:\opt\ros\foxy\x64\setup.bat
cd C:\ros2newarch\ros2\ros2_emulation\src
call install\setup.bat
ros2 run ros_tcp_endpoint default_server_endpoint --ros-args -p ROS_IP:=169.254.47.120 -p ROS_TCP_PORT:=10000

sometimes need to update the ROS_IP above by finding what the address was assigned to the router.
Use "ipconfig" in a command window and look for the following autoxconfiguration address:
- ----
Ethernet adapter Ethernet 2:

   Connection-specific DNS Suffix  . :
   Link-local IPv6 Address . . . . . : fe80::3360:2caf:8988:70c9%17
   Autoconfiguration IPv4 Address. . : 169.254.47.120
- ----
Further, you will need to update this ip address in unity as well. Click on Robotics>Ros settings and then update the ip.

unity part:
go to C:\ros2newarch\unity\build\test5
open ros test out.exe

code path:
player_detection:
C:\ros2newarch\ros2\ros2_emulation\src\ap_interfaces\src

unity:
open unity hub
open ros test out project

priority:
C:\ros2newarch\ros2\ros2_emulation\src\SetPriority.reg



# how to modify ros message type
make changes to src>ap_interfaces>msg> (whatever msg you are changing)
save changes
colcon build in ros workspace

switch to unity
go to robotics>Generate ROS messages...
fill out the "Ros Message Path" C:\ros2newarch\ros2\ros2_emulation\src\ap_interfaces\msg
Click "Build x msgs" where x is the number of messages from the message path.

you may need to update a testpublisher in unity.
The script is located under the "tester" game object and the Testpublish script.

# how to add new src file to ros env
create new src file and code
modify CMakeLists:
1) modify and add the following actions (dummy is example):
add_executable(dummy src/dummy.cpp)
ament_target_dependencies(dummy rclcpp std_msgs)
rosidl_target_interfaces(dummy
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

2) add program executable name to install target
install(TARGETS
  player_detection
  dummy
  player_detection_clean
  rfid
  button
  ui
  DESTINATION lib/${PROJECT_NAME})

## todo
Make cv code thread safe, currently not protecting message 