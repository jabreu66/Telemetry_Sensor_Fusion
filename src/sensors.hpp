#include <random>

struct GPS{
    double time;
    double x;
    double y;
    double z;

    GPS::GPS(double time, double x, double y, double z);
};

std::mt19937 seed(1);

struct VelocityMeasurement
{
    double time;
    double vx;
    double vy;
    double vz;

    VelocityMeasurement::VelocityMeasurement(double time, double vx, double vy, double vz);
};  