// simple parameter in c++
#include "rclcpp/rclcpp.hpp"
// include ros message
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include <string>
#include <vector>
#include <rcl_interfaces/msg/set_parameters_result.hpp>


class SimpleParameter : public rclcpp::Node
{
public:
  SimpleParameter()
  : Node("simple_parameter")
  {
    // Declare a parameter and set the default value
    declare_parameter<int>("simple_int_param", 0);
    declare_parameter<std::string>("simple_string_param", "hello");

    // get add on callback
    callback_handler = add_on_set_parameters_callback(std::bind(&SimpleParameter::param_callback, this, std::placeholders::_1));
  }

  private:
    OnSetParametersCallbackHandle::SharedPtr callback_handler;

    rcl_interfaces::msg::SetParametersResult param_callback(const std::vector<rclcpp::Parameter> &parameters)
    {
      rcl_interfaces::msg::SetParametersResult result;

      for (const auto &parameter : parameters)
      {
        if (parameter.get_name() == "simple_int_param" && parameter.get_type() == rclcpp::ParameterType::PARAMETER_INTEGER)
        {
          RCLCPP_INFO_STREAM(this->get_logger(), "simple_int_param set to " << parameter.as_int());
          result.successful = true;
        }
        else if (parameter.get_name() == "simple_string_param" && parameter.get_type() == rclcpp::ParameterType::PARAMETER_STRING)
        {
          RCLCPP_INFO_STREAM(this->get_logger(), "simple_string_param set to " << parameter.as_string());
          result.successful = true;
        }
      }
      return result;
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimpleParameter>());
  rclcpp::shutdown();
  return 0;
}