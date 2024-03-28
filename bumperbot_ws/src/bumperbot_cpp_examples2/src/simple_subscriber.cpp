// simple subscriber ros2 in cpp
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class SimpleSubscriber : public rclcpp::Node
{
    public: 
    SimpleSubscriber() : Node("simple_subscriber"){
        sub_ = create_subscription<std_msgs::msg::String>("chatter", 10,
         std::bind(&SimpleSubscriber::topic_callback, this, std::placeholders::_1));
    }

    private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
    void topic_callback(const std_msgs::msg::String::SharedPtr msg){
        RCLCPP_INFO(get_logger(), "I heard: '%s'", msg->data.c_str());
    }
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}