# ros_joy_sfml

## Description :
A simple ROS tool to move a robot with a joystick, it has been tested with an ``Xbox`` controller and a ``PS-5`` controller.
If you don't have a controller connected, you can move your robot with the arrows on your keyboard.

It publishes on the topic ``cmd_vel`` a linear velocity on ``x`` and an angular velocity on ``z``.

You can change the default linear velocity with the ``vit_lin`` parameter and the default angular velocity with the ``vit_ang`` parameter.

## Required :
SFML
```sudo apt-get install libsfml-dev```

## How to start :
```rosrun ros_joy_sfml ros_joy_sfml```

## Usage :
<p align="center"><img src="./Xbox controller.png"></p>
