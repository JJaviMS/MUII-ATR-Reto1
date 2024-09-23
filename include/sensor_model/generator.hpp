#ifndef SENSOR_MODEL_GENERATOR_HPP
#define SENSOR_MODEL_GENERATOR_HPP

#include <random>

class TemperatureGenerator {
    public:

        double get_next_measure(); //Hay que ver si podemos modificar esto para que sea const

        TemperatureGenerator(int seed, double noise_strength);

    private:
        int seed;
        std::normal_distribution<> noise_dist; // Distribución de ruido
        double last_measure;
        double last_noise;
        std::mt19937 gen;
        std::uniform_real_distribution<> temp_variation;
};

#endif