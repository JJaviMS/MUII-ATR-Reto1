#ifndef SENSOR_MODEL_SENSOR_DATA_HPP
#define SENSOR_MODEL_SENSOR_DATA_HPP

#include "generator.hpp"

#include <vector>


class SensorData {
private:
    std::vector<double> m_data;
    const double m_time_interval;
public:
    SensorData() = delete;
    /**
     * @brief Initialize the member std::vector<double> m_data with the doubles inside data
     * 
     * @param data std::vector of doubles used to initialize de SensorData data
     * @param time_interval_seconds interval of time between two measures
     */
    explicit SensorData(const std::vector<double>& data, const double time_interval_seconds)
        : m_data(data), m_time_interval(time_interval_seconds) {}
    /**
     * @brief Initialize data of SensorData with a provided generator
     * 
     * @param generator TemperatureGenerator used to fill the data vector
     * @param n_measurements Number of measurements generated by generator and stored in m_data
     */
    explicit SensorData(TemperatureGenerator& generator, std::size_t n_measurements, const double time_interval_seconds);

    std::vector<double> get_data() { return m_data; }
    
    /**
     * @brief Apply linear regresion in blocks of fixed size to filter the noise stored in SensorData.
     * @return std::vector<double> filled with the filtered measures
     * 
     * @param window_size_seconds size of the block in wich linear regresion will be applied
     */
    std::vector<double> filter_noise(const double window_size_seconds = 60.0) const;

    friend std::ostream& operator<<(std::ostream& out, const SensorData& sensor_data);
};

#endif