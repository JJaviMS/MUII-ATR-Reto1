#include "generator.hpp"
#include <random>
#include <algorithm>


TemperatureGenerator::TemperatureGenerator(int seed,double noise_strength){
    this->seed = seed;
    std::uniform_real_distribution<> initial_dist = std::uniform_real_distribution<>(0.0, 50.0);
    this->noise_dist = std::normal_distribution<>(0.0, noise_strength);
    this->temp_variation = std::uniform_real_distribution<>(-2.0,2.0);
    std::mt19937 gen(seed);
    this -> gen = gen;
    this -> last_measure = initial_dist(gen);
}


double TemperatureGenerator::get_next_measure(){
    double last_measure = this -> last_measure;

    double new_noise = noise_dist(this->gen);

    double return_temp = last_measure + new_noise;

    double variation = this->temp_variation(this->gen);

    this->last_measure = std::min(std::max(last_measure + variation,0.0),50.0);

    return return_temp;
}