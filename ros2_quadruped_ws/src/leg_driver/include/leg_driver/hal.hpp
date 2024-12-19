#include <PiPCA9685/PCA9685.h>
#include "robot_interfaces/msg/leg_angles.hpp"

#ifndef LEG_DRIVER_HAL_HPP
#define LEG_DRIVER_HAL_HPP

class MotorGroup {
   private:
    PiPCA9685::PCA9685 pca;
    int number_id = -1;

   public:
    MotorGroup();
    void Setup(int _number_id = 0);
    void SetFrequency(double hz);
    void SetMotorAngles(const robot_interfaces::msg::LegAngles::SharedPtr msg);
    ~MotorGroup();
};

#endif  // MOTOR_DRIVER_HAL_HPP