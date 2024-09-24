#include "sensor_model/generator.hpp"
#include "sensor_model/sensor_data.hpp"
#include <iostream>
#include <cassert>

// 2^16 iteraciones
// Forcing a power of 2 may force the compiler to use SIMD
#define N_ITERATIONS 1<<8 

int main(){

    TemperatureCache cache = TemperatureCache(N_ITERATIONS);    
    TemperatureGenerator generator = TemperatureGenerator(0123, 0.5, &cache);

    /*for (int i = 0; i<1000;i++)
        std::cout << generator.get_next_measure() << std::endl;*/

    SensorData sensor_data = SensorData(generator, N_ITERATIONS);

    std::cout << sensor_data;

    std::vector<double> filtered_data = sensor_data.filter_noise(0.5, 2);

    auto original_temperatures = cache.get_original_temperatures();
    

    // Ensure both arrays have the same length
    assert(filtered_data.size() == N_ITERATIONS && original_temperatures.size() == N_ITERATIONS);

    double acc_difference = 0.0;

    for (auto i = 0; i < N_ITERATIONS; i++){
        acc_difference = std::abs(original_temperatures[i] - filtered_data[i]);
    }

    std::cout << "The accumlated error is: " << acc_difference << std::endl;

    /*for (std::size_t i = 0; i < filtered_data.size(); ++i) 
        std::cout << filtered_data[i] << '\n';*/

    return 0;
}