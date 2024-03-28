#simple publisher ros2 python

import numpy as np
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class SimplePublisher(Node):
    def __init__(self):
        super().__init__('simple_publisher')
        self.pub_ = self.create_publisher(String, 'chatter', 10)
        self.counter_ = 0
        self.num_ = np.random.randn(1, 1)
        self.freq_ = 1 #1 hz/1s
        self.get_logger().info('Simple Publisher has been started')
        self.timer_ = self.create_timer(1.0 / self.freq_, self.timer_callback)

    def timer_callback(self):
        msg = String()
        msg.data = "Hello ROS2 - counter: %f " % self.num_
        self.pub_.publish(msg)
        self.counter_ += 1
        self.num_ = np.random.randn(1, 1)
        
def main():
    rclpy.init()
    simple_publisher = SimplePublisher()
    rclpy.spin(simple_publisher)
    simple_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
