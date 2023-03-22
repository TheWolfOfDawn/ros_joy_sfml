cmake_minimum_required(VERSION 3.0.2)
project(ros-joy-sfml)

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(
# include
${catkin_INCLUDE_DIRS}
)

add_executable(ros-joy-sfml src/ros-joy-sfml.cpp)
target_link_libraries(ros-joy-sfml ${catkin_LIBRARIES})

#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR /usr/include/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(/usr/include/SFML)
target_link_libraries(ros-joy-sfml sfml-system sfml-window sfml-graphics sfml-audio)
