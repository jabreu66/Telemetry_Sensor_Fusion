#ifndef SENSORS_H
#define SENSORS_H

#include "state.h"

struct GPS{
    double time;
    double x;
    double y;
    double z;

    // GPS();
    GPS(double time, double x, double y, double z);
    GPS(const State &state);
};

GPS gpsSimulator(const State &truthState);

struct VelocityMeasurement
{
    double time;
    double vx;
    double vy;
    double vz;

    VelocityMeasurement(double time, double vx, double vy, double vz);
    VelocityMeasurement(const State &state);
    // VelocityMeasurement();
};  

VelocityMeasurement velocitySimulator(const State &truthState);

#endif
