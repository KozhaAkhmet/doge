#include <iostream>
#include <memory>
#include <string>

#include "../include/leg_driver/hal.hpp"
#include "rclcpp/rclcpp.hpp"
#include "robot_interfaces/msg/leg_angles.hpp"
#include "std_msgs/msg/string.hpp"

class LegDriverNode : public rclcpp::Node {
   public:
    LegDriverNode()
        : Node("leg_driver_node") {
        this->declare_parameter("number_id", 0);
        int number_id_ = this->get_parameter("number_id").as_int();

        std::string sub_name = "leg_angles_" + std::to_string(number_id_);
        subscription_ = this->create_subscription<robot_interfaces::msg::LegAngles>(
            sub_name, 10,
            std::bind(&LegDriverNode::motor_command_callback, this, std::placeholders::_1));

        // Initialize motors (this can be an interface to actual hardware)
        motor_group.Setup(number_id_);
        motor_group.SetFrequency(60.0);
        RCLCPP_INFO(this->get_logger(), "Leg Driver Node %d Initialized", number_id_);
    }

   private:
    MotorGroup motor_group;
    void motor_command_callback(const robot_interfaces::msg::LegAngles::SharedPtr msg) {
        // Simulate controlling the motors
        // Here you would control the actual hardware, but we will just print the values
        RCLCPP_INFO(this->get_logger(), "Received Motor Commands: ");
        RCLCPP_INFO(this->get_logger(), "Motor 1 Position: %f", msg->omega);
        RCLCPP_INFO(this->get_logger(), "Motor 2 Position: %f", msg->theta);
        RCLCPP_INFO(this->get_logger(), "Motor 3 Position: %f", msg->phi);

        motor_group.SetMotorAngles(msg);

        // ros2 topic pub -r 10 /leg_angles_0 robot_interfaces/msg/LegAngles "{m1_ang: 90 , m2_ang: 90 , m3_ang: 90}"
    }

    rclcpp::Subscription<robot_interfaces::msg::LegAngles>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LegDriverNode>());

    rclcpp::shutdown();
    return 0;
}
