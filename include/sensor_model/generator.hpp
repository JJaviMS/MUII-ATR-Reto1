#ifndef SENSOR_MODEL_GENERATOR_HPP
#define SENSOR_MODEL_GENERATOR_HPP

#include <random>
#include <vector>

struct TemperatureEntry {
    double temperature;
    double noise;
};

/// @brief Helps allocating the temperatures
class TemperatureCache {
    private:
        std::vector<TemperatureEntry> stored_temperatures;

    public:
        /// @brief Creates the temperature cache using a hint to allocate the space
        /// @param size_hint Hint of the number of temperatures that will be stored
        TemperatureCache(int size_hint);

        /// @brief Creates a temperature cache using the default vector size
        TemperatureCache();

        /// @brief Adds the given temperature to the cache
        /// @param original Original temperature without noise
        /// @param with_noise Noise of the temperature
        void add_temperature(const double original, const double noise);

        /// @brief Returns the stored temperatures
        /// @return Vector containing the temperatures without noise
        std::vector<double> get_original_temperatures();

        /// @brief Returns the stored noise
        /// @return Vector containing the noises
        std::vector<double> get_noise();
};

class TemperatureGenerator {
    public:

        double get_next_measure(); //Hay que ver si podemos modificar esto para que sea const

        TemperatureGenerator(int seed, double noise_strength, TemperatureCache* cache = NULL);

    private:
        int seed;
        std::normal_distribution<> noise_dist; // Distribución de ruido
        double last_measure;
        double last_noise;
        std::mt19937 gen;
        std::uniform_real_distribution<> temp_variation;
        TemperatureCache *cache;
};

#endif