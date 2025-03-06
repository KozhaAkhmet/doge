# Simple Quadruped Robot with ROS2 
This repository is about creating accessible, convenient robot dog. It made of 3D Printed parts. 

The project developed on **Ubuntu 22.04** with **ROS2 Humble** and executed in **Raspberry Pi Zero 2W**.

TODO: Add a preview foto
## The Goals
| Status | Task                                   |
| :----: | -------------------------------------- |
|   ✔    | Completed 3D printed parts             |
|   ✔    | Implemented servo driver node          |
|        | Implement IK Node                      |
|        | Found or implemented a testing sofware |
|        | Fine tuned servos                      |
|        | Trot Gait                              |
|        | Control With Gamepad                   |



## Hardware and Mics
The 3D printed parts are available [at thingiverse](https://www.thingiverse.com/thing:4822059). The original author of the parts is [Gleb Devyatkin](https://www.thingiverse.com/sovgvd/designs).

TODO: Add a link to the modified custom parts.

TODO: Circuit scheme

There is quite basic stack of required hardware such as:
- Rapberry Pi Zero 2W
- PCA9685
- 4C15 DC-DC step down converter
- Twelve SG90 servos 
- Two 18650 Li-ion barreries

## Software

### Installation

Raspberry Pi Zero 2W has only 512 MB RAM which will require the least emulated/backgroud executed processes. Since that, the ROS2 Humble has to be installed directly to the environment, so not by using Docker. Also, you should do the compiling or developement in a better arm64 device or by cross-compiling on your computer device. 

To control the servo driver, you should install the PCA9685 library before proceding.  

Here you can follow the instructions for both, ROS2 humble and PCA9685 library:
- [ROS2 Humble on Raspberry Pi installation guide](https://roboticsbackend.com/install-ros2-on-raspberry-pi/)
- [PiPCA9685 library](https://github.com/barulicm/PiPCA9685)

TODO: Add ros_graph

## Licence*

## References
https://www.youtube.com/watch?v=4rc8N1xuWvc
https://www.youtube.com/watch?v=Cr1ZshV-gqw
https://www.youtube.com/watch?v=mwpIMD-3udw
