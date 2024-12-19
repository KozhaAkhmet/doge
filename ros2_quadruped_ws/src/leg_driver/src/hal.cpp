#include <unistd.h>
#include "std_msgs/msg/string.hpp"
#include "../include/leg_driver/hal.hpp"

MotorGroup::MotorGroup(/* args */) {
}

// the number_id has to be set since the value will control the corresponded group of servos. Default number_id = -1
void MotorGroup::Setup(int _number_id) {
    this->number_id = _number_id;
}

void MotorGroup::SetFrequency(double hz) {
    pca.set_pwm_freq(hz);
}

// The angles will be set to the according group defined as number_id. Ex: number_id = 0 is for 0,1,2 group of motors; 1 -> 3,4,5 ; 2 -> 6,7,8 ; 3 -> 9,10,11.
void MotorGroup::SetMotorAngles(const robot_interfaces::msg::LegAngles::SharedPtr msg) {
    pca.set_pwm(0 + 3 * number_id, 0, msg->m1_ang);
    pca.set_pwm(1 + 3 * number_id, 0, msg->m2_ang);
    pca.set_pwm(2 + 3 * number_id, 0, msg->m3_ang);
}

MotorGroup::~MotorGroup() {
}

