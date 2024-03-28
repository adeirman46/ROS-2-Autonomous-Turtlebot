# create ros2 subscriber in python
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class SimpleSubcriber(Node):
    def __init__(self):
        super().__init__('simple_subscriber')
        self.sub_ = self.create_subscription(String, 'chatter', self.msg_callback, 10)
        self.get_logger().info('Simple Subscriber has been started')

    def msg_callback(self, msg):
        self.get_logger().info('I heard: [%s]' % msg.data)


def main():
    rclpy.init()
    sub = SimpleSubcriber()
    rclpy.spin(sub)
    sub.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
