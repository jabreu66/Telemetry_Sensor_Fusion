#include <iostream>
#include "sensors.hpp"
#include <random>

std::mt19937 rand_gen(42);
std::normal_distribution<double> gpsNoise{0, 1.2};
std::normal_distribution<double> velNoise{0, 0.5};



GPS::GPS(double time, double x, double y, double z) : time(time), x(x), y(y), z(z) {}

GPS::GPS(const State &state) : time(state.t_s), x(state.x_m), y(state.y_m), z(state.z_m) 
{
}

GPS gpsSimulator(const State &truthState)
{
    GPS gps(truthState);
    double x_noise = gpsNoise(rand_gen);
    gps.x += x_noise;

    double y_noise = gpsNoise(rand_gen);
    gps.y += y_noise;

    double z_noise = gpsNoise(rand_gen);
    gps.z += z_noise;

    return gps;
}

VelocityMeasurement::VelocityMeasurement(double time, double vx, double vy, double vz) : time(time), vx(vx), vy(vy), vz(vz) {}

VelocityMeasurement::VelocityMeasurement(const State &state) : time(state.t_s), vx(state.vx_mps), vy(state.vy_mps), vz(state.vz_mps) {}
    
// VelocityMeasurement::VelocityMeasurement(){}


VelocityMeasurement velocitySimulator(const State &truthState)
{
    VelocityMeasurement vel(truthState);

    double vx_noise = velNoise(rand_gen);
    vel.vx += vx_noise;

    double vy_noise = velNoise(rand_gen);
    vel.vy += vy_noise;

    double vz_noise = velNoise(rand_gen);
    vel.vz += vz_noise;

    return vel;
}

AccelerationMeasurement::AccelerationMeasurement(double time, double ax, double ay, double az) : time(time), ax(ax), ay(ay), az(az) {}

AccelerationMeasurement::AccelerationMeasurement(const State &state) : time(state.t_s), ax(state.a_x), ay(state.a_y), az(state.a_z) {}

// AccelerationMeasurement::AccelerationMeasurement(){}


AccelerationMeasurement accelerationSimulator(const State &truthState)
{
    AccelerationMeasurement acc(truthState);

    double ax_noise = velNoise(rand_gen);
    acc.ax += ax_noise;

    double ay_noise = velNoise(rand_gen);
    acc.ay += ay_noise;

    double az_noise = velNoise(rand_gen);
    acc.az += az_noise;

    return acc;
}



