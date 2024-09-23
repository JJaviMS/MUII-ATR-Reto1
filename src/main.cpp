#include "sensor_model/generator.hpp"
#include "sensor_model/sensor_data.hpp"
#include <iostream>

int main(){

    TemperatureGenerator generator = TemperatureGenerator(0123, 0.5);

    /*for (int i = 0; i<1000;i++)
        std::cout << generator.get_next_measure() << std::endl;*/

    SensorData sensor_data = SensorData(generator, 100);

    std::cout << sensor_data;

    std::vector<double> filtered_data = sensor_data.filter_noise(0.5, 2);

    for (std::size_t i = 0; i < filtered_data.size(); ++i) 
        std::cout << filtered_data[i] << '\n';

    return 0;
}