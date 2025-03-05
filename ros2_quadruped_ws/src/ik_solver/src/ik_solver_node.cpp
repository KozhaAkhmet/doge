#include <iostream>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "robot_interfaces/msg/leg_angles.hpp"
#include "robot_interfaces/msg/leg_pos.hpp"
#include "std_msgs/msg/string.hpp"

// Defining Constants

#define A 28.4
#define E 51.0
#define F 61.0

#define GR 35.5/16.5

class IKSolverNode : public rclcpp::Node {
   public:
    IKSolverNode()
        : Node("ik_solver_node") {
        for (int i = 0; i < 4; i++) {
            leg_ang_pubs_.emplace_back(this->create_publisher<robot_interfaces::msg::LegAngles>("leg_angles_" + std::to_string(i), 10));
            leg_pos_subs_.emplace_back(this->create_subscription<robot_interfaces::msg::LegPos>("leg_pos_" + std::to_string(i), 10, [this, i](const robot_interfaces::msg::LegPos::SharedPtr msg) { this->position_command_callback(msg, i); }));
        }
    }

   private:
    void position_command_callback(const robot_interfaces::msg::LegPos::SharedPtr msg, int index_i) {
        RCLCPP_INFO(this->get_logger(), " message is sending to %d", index_i);
        leg_ang_pubs_[index_i]->publish(solve_IK(msg));
    }

    robot_interfaces::msg::LegAngles solve_IK(const robot_interfaces::msg::LegPos::SharedPtr msg) {
        robot_interfaces::msg::LegAngles leg_angle_;

        // Y and Z plane
        double D = sqrt(msg->y * msg->y + (msg->z - A) * (msg->z - A));
        double alpha = atan(msg->y / A);
        leg_angle_.omega = GR * atan(msg->y / A) 
                                + asin(sin(alpha) * msg->z / D);

        // X and Y plane
        double G = sqrt(D * D + msg->x * msg->x);
        leg_angle_.phi = acos((G * G - E * E - F * F) / (-2 * E * F));

        leg_angle_.theta = atan(msg->x / D) + asin(F * sin(leg_angle_.phi) / G);

        return leg_angle_;
    }

    std::vector<rclcpp::Publisher<robot_interfaces::msg::LegAngles>::SharedPtr> leg_ang_pubs_;
    std::vector<rclcpp::Subscription<robot_interfaces::msg::LegPos>::SharedPtr> leg_pos_subs_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<IKSolverNode>());

    rclcpp::shutdown();
    return 0;
}
