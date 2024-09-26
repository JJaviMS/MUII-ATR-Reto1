#include "sensor_model/generator.hpp"
#include "sensor_model/sensor_data.hpp"
#include <iostream>
//#include <cassert>

// 2^16 iteraciones
// Forcing a power of 2 may force the compiler to use SIMD
#define N_ITERATIONS (1<<16)

int main(int argc, char** argv) {

    TemperatureCache cache = TemperatureCache(N_ITERATIONS);    

    // Sensor and noise model. Factor of 1 second
    TemperatureGenerator generator = TemperatureGenerator(999, 0.5, std::chrono::milliseconds(100), &cache);

    //Sensor data: noise filter
    SensorData sensor_data = SensorData(generator, N_ITERATIONS, 0.1);
    std::vector<double> data = sensor_data.get_data();
    std::vector<double> filtered_data = sensor_data.filter_noise();
    
    auto original_temperatures = cache.get_original_temperatures();

    double acc_diff_original_filtered = 0.0;
    double acc_diff_original_noisy = 0.0;

    for (auto i = 0; i < N_ITERATIONS; i++) {
        acc_diff_original_filtered += std::abs(original_temperatures[i] - filtered_data[i]);
        acc_diff_original_noisy += std::abs(original_temperatures[i] - data[i]);
    }

    std::cout << "The accumlated error due to the noise is: " << acc_diff_original_noisy << " celsius degrees in " << N_ITERATIONS << " measurements\n";
    std::cout << "The average error due to the noise is: " << acc_diff_original_noisy/N_ITERATIONS << " celsius degrees in " << N_ITERATIONS << " measurements\n";

    std::cout << std::endl;

    std::cout << "The accumlated error after filtering is: " << acc_diff_original_filtered << " celsius degrees in " << N_ITERATIONS << " measurements\n";
    std::cout << "The average error after filtering is: " << acc_diff_original_filtered/N_ITERATIONS << " celsius degrees in " << N_ITERATIONS << " measurements\n";

    return 0;
}