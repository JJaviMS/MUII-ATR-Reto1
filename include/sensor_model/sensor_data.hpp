#ifndef SENSOR_MODEL_SENSOR_DATA_HPP
#define SENSOR_MODEL_SENSOR_DATA_HPP

#include "generator.hpp"

#include <vector>


class SensorData {
private:
    std::vector<double> m_data;

public:
    SensorData(): m_data() {}
    explicit SensorData(const std::vector<double>& data) : m_data(data) {}
    explicit SensorData(TemperatureGenerator& generator, std::size_t n_measurements);
    
    std::vector<double> filter_noise(const double time_interval_seconds, const unsigned int linear_segment_size = 1) const;

    friend std::ostream& operator<< (std::ostream& out, const SensorData& sensor_data);
};

#endif