Plutonium2014
=============

Skunkworks 2014 Aerial Assist

BeagleBone
=======================

A small rectangle tracker written in OpenCV, tuned to recognize the green light of Live Wire Robotics' Ring of Fire.  Also contains functions to grab sensor data for I2C, then push all of the information to the cRIO on TCP Port 1180.

### Compile Instructions
This project requires OpenCV and Posix-Threads to compile.
The gcc linker flags are -lopencv_core -lopencv_imgproc -lopencv_highgui -lpthread

Flower3DAnimation
======================
A dashboard visualization of Skunk Works' 2014 robot Flower, as a 3D model that synchronizes its state with the robot use network tables.  Requires LWJGL and networktables libraries to compile.  Model files not included, but the skeleton specification is in model/mesh.skl.
