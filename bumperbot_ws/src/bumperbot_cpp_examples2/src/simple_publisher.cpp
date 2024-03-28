// create a simple publisher node using cpp class ros2

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using namespace std::chrono_literals;

class SimplePublisher : public rclcpp::Node
{
    public:
    SimplePublisher() : Node("simple_publisher"), count_(0){
        pub_ = create_publisher<std_msgs::msg::String>("chatter", 10);
        timer_ = create_wall_timer(1s, std::bind(&SimplePublisher::timer_callback, this));
        RCLCPP_INFO(get_logger(), "Start node");
    }

    private:
        unsigned int count_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
        rclcpp::TimerBase::SharedPtr timer_;
        void timer_callback(){
            auto message = std_msgs::msg::String();
            message.data = "Hello world" + std::to_string(count_++);
            RCLCPP_INFO(get_logger(), "Publishing: '%s'", message.data.c_str());
            pub_->publish(message);
        }

};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimplePublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
