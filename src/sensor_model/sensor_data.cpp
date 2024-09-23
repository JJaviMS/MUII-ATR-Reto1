#include "sensor_model/sensor_data.hpp"

#include <iostream>
#include <algorithm>
#include <numeric>

struct slr_params {
    double b0;
    double b1;
};

SensorData::SensorData(TemperatureGenerator& generator, std::size_t n_measurements): m_data(n_measurements) {
    //Ver por qué no funciona std::generate(m_data.begin(), m_data.end(), generator.get_next_measure());
    for (std::size_t i = 0; i < n_measurements; ++i)
        m_data[i] = generator.get_next_measure();
}

slr_params simple_linear_regresion_parameters(const std::vector<double>& X, const std::vector<double>& Y) {
    std::size_t length = X.size();
    
    if(length != Y.size())
        throw ""; //TODO: Implement proper exception
    
    slr_params params = {0};

    double n = static_cast<double>(length); //TODO: Check if the cast is necessary
    double x_mean = std::accumulate(X.begin(), X.end(), 0.0) / n; 
    double y_mean = std::accumulate(Y.begin(), Y.end(), 0.0) / n;

    params.b1 = (std::inner_product(X.begin(), X.end(), Y.begin(), params.b0) - n*x_mean*y_mean) /
                (n*std::inner_product(X.begin(), X.end(), X.begin(), params.b0) - (n*x_mean));

    params.b0 = y_mean - params.b1 * x_mean;

    return params;
}

std::vector<double> SensorData::filter_noise(const double time_interval_seconds, const unsigned int linear_segment_size) const {

    const std::size_t n_measurements = m_data.size();

    //Filtered data
    std::vector<double> filtered_data;
    filtered_data.reserve(n_measurements);

    //Time vector
    std::vector<double> time(1, 0.0);
    time.reserve(n_measurements);
    for (std::size_t i = 0; i < n_measurements - 1; ++i)
        time.push_back(time[i] + time_interval_seconds);

    //Calculating size of subvectors where it will be applied the slr
    const std::size_t slr_size = static_cast<std::size_t>(linear_segment_size / time_interval_seconds);

    if (slr_size <= 1 )
        throw ""; //TODO: Implement proper exception
    
    std:size_t first = 0;
    while (first + slr_size < n_measurements) {
        slr_params slr = simple_linear_regresion_parameters(std::vector<double>(&time[first], &time[first + slr_size]),
                                                            std::vector<double>(&m_data[first], &m_data[first + slr_size]));
        for (std::size_t i = 0; i < slr_size; ++i)
            filtered_data.push_back(slr.b0 + time[first + i]*slr.b1);
        first += slr_size;
    }

    while (first < n_measurements) {
        filtered_data.push_back(m_data[first]);
        ++first;
    }

    return filtered_data; //Not sure if this will return a copy (I have to check move constructors)
}

std::ostream& operator<<(std::ostream& out, const SensorData& sensor_data) {

    for (std::size_t i = 0; i < sensor_data.m_data.size(); ++i)
        out << sensor_data.m_data[i] <<  " C\n";

    return out;
}