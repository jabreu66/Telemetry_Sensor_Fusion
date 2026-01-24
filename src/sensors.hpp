#include <random>
#include "state.h"

struct GPS{
    double time;
    double x;
    double y;
    double z;

    GPS();
    GPS(double time, double x, double y, double z);
    GPS(const State &state);
};

GPS gpsSimulator(const State &truthState);

std::mt19937 rand_gen(22);
std::normal_distribution<double> gpsNoise{0, 1.2};

struct VelocityMeasurement
{
    double time;
    double vx;
    double vy;
    double vz;

    VelocityMeasurement(double time, double vx, double vy, double vz);
    VelocityMeasurement(const State &state);
    VelocityMeasurement();
};  

VelocityMeasurement velocitySimulator(const State &truthState);

std::normal_distribution<double> velNoise{0, 0.5};