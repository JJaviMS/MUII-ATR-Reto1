#include "sensor_model/generator.hpp"
#include <random>
#include <algorithm>
#include <vector>


TemperatureGenerator::TemperatureGenerator(int seed, double noise_strength, TemperatureCache* cache){
    this->seed = seed;
    std::uniform_real_distribution<> initial_dist = std::uniform_real_distribution<>(0.0, 50.0);
    this->noise_dist = std::normal_distribution<>(0.0, noise_strength);
    this->temp_variation = std::uniform_real_distribution<>(-2.0,2.0);
    std::mt19937 gen(seed);
    this -> gen = gen;
    this -> last_measure = initial_dist(gen);
    this -> cache = cache;
}



double TemperatureGenerator::get_next_measure(){
    double last_measure = this -> last_measure;

    double new_noise = noise_dist(this->gen);

    double return_temp = last_measure + new_noise;

    if (this -> cache != NULL){
        (this -> cache)->add_temperature(last_measure, new_noise);
    }

    double variation = this->temp_variation(this->gen);

    this->last_measure = std::min(std::max(last_measure + variation,0.0),50.0);

    return return_temp;
}


TemperatureCache::TemperatureCache(int size_hint){
    this ->stored_temperatures = std::vector<TemperatureEntry>();
    this -> stored_temperatures.reserve(size_hint);
}

TemperatureCache::TemperatureCache(){
    this ->stored_temperatures = std::vector<TemperatureEntry>();
}

void TemperatureCache::add_temperature(const double original, const double noise) {
    TemperatureEntry entry;
    entry.noise = noise;
    entry.temperature = original;
    (this -> stored_temperatures).push_back(entry);
}

std::vector<double> TemperatureCache::get_original_temperatures(){
    auto result = std::vector<double>();
    result.reserve(this->stored_temperatures.size());
    std::transform((this->stored_temperatures).begin(), (this->stored_temperatures).end(),std::back_inserter(result),[](TemperatureEntry d) -> double { return d.temperature;});
    return result;
}


std::vector<double> TemperatureCache::get_noise(){
    auto result = std::vector<double>();
    result.reserve(this->stored_temperatures.size());
    std::transform((this->stored_temperatures).begin(), (this->stored_temperatures).end(),std::back_inserter(result),[](TemperatureEntry d) -> double { return d.noise;});
    return result;
}
