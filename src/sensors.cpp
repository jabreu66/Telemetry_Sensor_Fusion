#include <iostream>
#include "sensors.hpp"


GPS::GPS(double time, double x, double y, double z) : time(time), x(x), y(y), z(z) {}

GPS::GPS(State state) : time(state.t_s), x(state.x_m), y(state.y_m), z(state.z_m) 
{
}

VelocityMeasurement::VelocityMeasurement(double time, double vx, double vy, double vz) : time(time), vx(vx), vy(vy), vz(vz) {}

