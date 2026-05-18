cmake_minimum_required(VERSION 3.16)
project(tele_sensor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)


add_executable(tele_sensor
 src/main.cpp src/csv_writer.cpp src/state.cpp src/sensors.cpp src/est_state.cpp src/visualizer.cpp)


target_link_libraries(tele_sensor PRIVATE SFML::Graphics SFML::Window SFML::System)

 add_executable(replay
    src/replay.cpp)