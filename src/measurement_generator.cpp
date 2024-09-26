#include "sensor_model/generator.hpp"

#include <iostream>
#include <fstream>

static const std::uint64_t N_ITERATIONS = (2 << 16);

int main(int argc, char** argv) {

    std::string file_name = "measures.txt";

    if (argc != 2)
        std::cout << "Arguments not readed assuming file name " << file_name << "\n";
    else
        file_name = argv[1];

    TemperatureCache cache = TemperatureCache(N_ITERATIONS);    
    TemperatureGenerator generator = TemperatureGenerator(999, 0.5, std::chrono::milliseconds(100), &cache);

    std::ofstream file;
    file.open(file_name);

    std::vector<double> original_temperatures = cache.get_original_temperatures();
    
    for (std::size_t i = 0; i < original_temperatures.size(); ++i)
        file << original_temperatures[i] << ";";
    
    file.close();

    return 0;
}