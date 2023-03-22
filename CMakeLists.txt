cmake_minimum_required(VERSION 3.0.2)
project(ros_joy_sfml)

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(
# include
${catkin_INCLUDE_DIRS}
)

add_executable(ros_joy_sfml src/ros_joy_sfml.cpp)
target_link_libraries(ros_joy_sfml ${catkin_LIBRARIES})

#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR /usr/include/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(/usr/include/SFML)
target_link_libraries(ros_joy_sfml sfml-system sfml-window sfml-graphics sfml-audio)
