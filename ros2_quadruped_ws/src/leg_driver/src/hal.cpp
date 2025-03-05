#include "../include/leg_driver/hal.hpp"

#include <unistd.h>

#include "std_msgs/msg/string.hpp"

int offset_ms_values[4][3]{{0, 20, 10}, {0, 0, -15}, {0, -5, -15}, {0, -10, -15}};

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int angles_to_ms(double angle) {
    return map(angle, 0, 90, 100, 300);
}

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
    pca.set_pwm(0 + 3 * number_id, 0, angles_to_ms(msg->omega * 180 / 3.14) + offset_ms_values[number_id][0]);
    pca.set_pwm(1 + 3 * number_id, 0, angles_to_ms(msg->theta * 180 / 3.14) + offset_ms_values[number_id][1]);
    pca.set_pwm(2 + 3 * number_id, 0, angles_to_ms(msg->phi * 180 / 3.14) + offset_ms_values[number_id][2]);
}

MotorGroup::~MotorGroup() {
}
