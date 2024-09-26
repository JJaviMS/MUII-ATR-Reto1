cmake_minimum_required(VERSION 3.10)

project(reto1_sensor 
    VERSION 0.1
    LANGUAGES CXX
)

include_directories(include)

add_library(sensor_model STATIC
    src/sensor_model/generator.cpp
    src/sensor_model/sensor_data.cpp
)

add_executable(comparison_app
    src/comparison.cpp
)
target_link_libraries(comparison_app PUBLIC sensor_model)

#add_executable(measurement_generator_app
#    src/measurement_generator.cpp
#)
#target_link_libraries(measurement_generator_app PUBLIC sensor_model)
#
#add_executable(noise_filtering_app
#    src/noise_filtering.cpp
#)
#target_link_libraries(noise_filtering_app PUBLIC sensor_model)