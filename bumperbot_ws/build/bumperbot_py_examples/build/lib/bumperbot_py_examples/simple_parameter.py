# import ros libraries
import rclpy
from rclpy.node import Node
# import message types
from std_msgs.msg import String
from std_msgs.msg import Int32
from rcl_interfaces.msg import SetParametersResult
from rclpy.parameter import Parameter

class SimpleParameter(Node):
    def __init__(self):
        super().__init__('simple_parameter')
        # create a parameter
        self.declare_parameter('simple_int_param', 0)
        self.declare_parameter('simple_str_param', 'hello')
        # set parameter callback
        self.add_on_set_parameters_callback(self.parameter_callback)
    
    def parameter_callback(self, params):
        result = SetParametersResult()
        for param in params:
            if param.name == 'simple_int_param' and param.type_ == Parameter.Type.INTEGER:
                self.get_logger().info('Parameter changed to %s: %d' % (param.name, param.value))
                result.successful = True
        
            elif param.name == 'simple_str_param' and param.type_ == Parameter.Type.STRING:
                self.get_logger().info('Parameter changed to %s: %s' % (param.name, param.value))
                result.successful = True
                
        return result

def main(args=None):
    rclpy.init(args=args)
    simple_parameter = SimpleParameter()
    rclpy.spin(simple_parameter)
    simple_parameter.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()