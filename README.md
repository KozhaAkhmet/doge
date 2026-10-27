# Simple Quadruped Robot with ROS2

This repository is about creating an accessible, convenient robot dog. It's made of 3D printed parts.

The project is developed on **Ubuntu 22.04** with **ROS2 Humble** and runs on a **Raspberry Pi Zero 2W**.

TODO: Add a preview photo

## The Goals

| Status | Task                                |
| :----: | ------------------------------------ |
|   ✔    | Completed 3D printed parts           |
|   ✔    | Implemented servo driver node        |
|   ✔    | Implement IK node                    |
|        | Find or implement testing software   |
|        | Fine tune servos                     |
|        | Trot gait                            |
|        | Control with gamepad                 |

The IK node's math is written up in detail in [Kinematics.md](Kinematics.md) — it walks through solving each leg's servo angles from a target foot position, plane by plane.

## Hardware and Misc

The 3D printed parts are available [at thingiverse](https://www.thingiverse.com/thing:4822059). The original author of the parts is [Gleb Devyatkin](https://www.thingiverse.com/sovgvd/designs).

TODO: Add a link to the modified custom parts.

TODO: Circuit scheme

There is a fairly basic stack of required hardware:
- Raspberry Pi Zero 2W
- PCA9685
- 4C15 DC-DC step-down converter
- Twelve SG90 servos
- Two 18650 Li-ion batteries

## Software

### Installation

The Raspberry Pi Zero 2W has only 512 MB of RAM, which means background/emulated processes need to be kept to a minimum. Because of that, ROS2 Humble has to be installed directly on the host rather than through Docker. You should also do the actual compiling/development on a more powerful arm64 device, or by cross-compiling on your own computer.

To control the servo driver, install the PCA9685 library before proceeding.

Here you can follow the installation instructions for both ROS2 Humble and the PCA9685 library:
- [ROS2 Humble on Raspberry Pi installation guide](https://roboticsbackend.com/install-ros2-on-raspberry-pi/)
- [PiPCA9685 library](https://github.com/barulicm/PiPCA9685)

TODO: Add ros_graph

## License

No license file is included yet — TBD.

## References
- https://www.youtube.com/watch?v=4rc8N1xuWvc
- https://www.youtube.com/watch?v=Cr1ZshV-gqw
- https://www.youtube.com/watch?v=mwpIMD-3udw
