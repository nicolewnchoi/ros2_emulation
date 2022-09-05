from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ap_interfaces',
            executable='player_detection',
            name='player_detection'
        ),
        Node(
            package='ap_interfaces',
            executable='rfid',
            name='rfid'
        ),
        Node(
            package='ap_interfaces',
            executable='unity',
            name='unity'
        ),
        Node(
            package='ap_interfaces',
            executable='ui',
            name='ui'
        ),
        Node(
            package='ap_interfaces',
            executable='button',
            name='button'
        )
    ])