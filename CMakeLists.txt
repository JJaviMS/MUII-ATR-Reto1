cmake_minimum_required(VERSION 3.10)

project(reto1_sensor 
    VERSION 0.1
    LANGUAGES CXX
)

include_directories(include)

add_library(sensor_model STATIC
    src/sensor_model/
)

add_executable(application 
    src/main.cpp
)

target_link_libraries(application PUBLIC sensor_model)