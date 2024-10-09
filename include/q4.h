#ifndef Q4_H
#define Q4_H
#include <vector>
namespace q4{
struct Vector2D
{
double x{};
double y{}; 
};

struct Sensor
{
	Vector2D pos;
	double accuracy;    
};

Vector2D kalman_filter(std::vector<Sensor> sensors);
}

using namespace q4;
inline Vector2D q4::kalman_filter(std::vector<Sensor> sensors)
{
    double weighted_sum_x = 0.0;
    double weighted_sum_y = 0.0;
    double total_weight = 0.0;
    size_t sensor_count=sensors.size();
    for (size_t i = 0; i < sensor_count; ++i) {
        const Sensor& sensor = sensors[i];
        double weight =sensor.accuracy; 
        weighted_sum_x += sensor.pos.x * weight;
        weighted_sum_y += sensor.pos.y * weight;
        total_weight += weight;
    }
    if (total_weight > 0) {
        return Vector2D(weighted_sum_x / total_weight, weighted_sum_y / total_weight);
    } else {
        return Vector2D(0.0, 0.0); 
    }
}
#endif //Q4_H