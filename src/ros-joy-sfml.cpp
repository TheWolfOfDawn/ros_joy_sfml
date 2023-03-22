#include <SFML/Graphics.hpp>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv) {
    ros::init(argc,argv,"ros-joy-sfml");
    ros::NodeHandle nh;

    ros::Rate loop_rate(10);

    ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);

    sf::RenderWindow window(sf::VideoMode(300, 300), "My game", sf::Style::Close);


    float vit_lin = 0.3; // 0.3m/sec
    float vit_ang = 0.7; //0.5rad/sec
    if(!nh.hasParam("/vit_lin")) {
        nh.setParam("/vit_lin", vit_lin);
    }

    if(!nh.hasParam("/vit_ang")) {
        nh.setParam("/vit_ang", vit_ang);
    }

    float dead_zone = 10; // 10%
    if(!nh.hasParam("/dead_zone")) {
        nh.setParam("/dead_zone", dead_zone);
    }
    

    while (ros::ok() && window.isOpen()) {
        ros::spinOnce();
        loop_rate.sleep();

        sf::Event event;

        bool can_move = false;

        while(window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed :
                    window.close();
                    break;
            }
        }

        if(sf::Joystick::isButtonPressed(0, 0)) {
            can_move = true;
        }


        if(!nh.getParam("/vit_lin", vit_lin)) {
            ROS_INFO_STREAM("Failed to get parram '/vit_lin'\n");
        }

        if(!nh.getParam("/vit_ang", vit_ang)) {
            ROS_INFO_STREAM("Failed to get parram '/vit_ang'\n");
        }

        geometry_msgs::Twist msg;

        if(sf::Joystick::isConnected(0)) {
            float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
            float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
            
            x = (x >= dead_zone || x <= -dead_zone) ? x-dead_zone : 0;
            y = (y >= dead_zone || y <= -dead_zone) ? y-dead_zone : 0;

            if(x!=0 || y!=0) {
                x /= 90.0;
                y /= 90.0;

                if(can_move == true) {
                    msg.linear.x = -y * vit_lin;
                    msg.angular.z = -x * vit_ang;
                }
                else {
                    ROS_INFO_STREAM("Press button \"A\" to enable controll !");
                }
            }
        }
        else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                msg.linear.x = vit_lin;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                msg.linear.x = -vit_lin;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                msg.angular.z = vit_ang;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                msg.angular.z = -vit_ang;
            }
        }

        pub.publish(msg);
    }

    geometry_msgs::Twist msg;
    pub.publish(msg);

    return 0;
}
