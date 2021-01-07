# Virtual Screen Painter
Virtual Screen Painter is an OpenCV-C++ project that uses mouse as a virtual pen and eraser.
  Operations Available:
* Changing the brush color
* Increase/Decrease thickness of the brush
* Erase operation
* Clear Screen

# Prerequisites
* [Ubuntu 20.04 Focal Fossa](https://releases.ubuntu.com/20.04/)
* [OpenCV 4.2.0](https://linuxize.com/post/how-to-install-opencv-on-ubuntu-20-04/) 

   Make sure you have installed OpenCV properly in your system. You can install default opencv in Ubuntu using following command
```bash
sudo apt install libopencv-dev
```
* [Build Essential](https://linuxize.com/post/how-to-install-gcc-on-ubuntu-20-04/)
```bash
   sudo apt install build-essential
```   
* [cmake](https://cmake.org/install/)
```bash
   sudo apt install cmake
```
# How to Build

After installing OpenCV, you can follow the step to build this project
```bash
git clone https://github.com/aleenalentin/virtual_screen_painter.git
cd virtual_screen_painter
mkdir build
cd build
cmake ..
make
./main
```
# Demo 

Click on the following image to see the video

[![Introduction Video](https://img.youtube.com/vi/d6cZk5gdIPc/0.jpg)](https://youtu.be/d6cZk5gdIPck)


# Acknowledgment
[Lentin Joseph](https://lentinjoseph.com/) and  [ROS Developer Learning Path](https://robocademy.com/2020/06/25/enroll-in-robot-operating-system-learning-path-by-lentin-joseph/)


