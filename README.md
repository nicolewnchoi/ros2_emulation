## Ros2 Rearchitecture

### Overall Structure
![structure](pic1.jpg)
Main components:
1. CV (detecting players)
2. RFID (rectifying the coordinate)
3. Unity (game logic and displaying)

The general process is as follow:
1. The CV part is responsible for detecting each player and sending detected coordinate to the Ros2 system. 
2. The RFID get the sparse coordinate and process the date to associate each coordinate with correct ID and then send this info to the system as well.
3. The unity uses sparse coordinate for game logic and render the output to camera. If modifications has been made by RFID, those modifications will be adjusted in Unity as well. 

### Ros2 Highlights
Firstly, we build a new message type and uses it as the conveying message in our ROS2 system. More info about the message type can be found in sourcecode.

#### Multithread
In each node, multithread is used so that processing data and sending data won't intervene each other. For now, manual lock is not used except for those implemented by Ros2 system.

#### Unity
More information about how ros2 and unity is integrated can be found on the official [site](https://github.com/Unity-Technologies/Unity-Robotics-Hub). After testing the delays is about 15 ms(under ubuntu, windows systems have some different statistics probably due to different reasons such as unofficial supports or tasks priority):
1. about 50% delays are below 10ms.
2. about 90% delays are below 20ms.

#### CV
Finished integrating old codes into this repo. 
