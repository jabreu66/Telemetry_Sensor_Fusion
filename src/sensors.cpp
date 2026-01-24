#include <iostream>
#include "sensors.hpp"


GPS::GPS(double time, double x, double y, double z) : time(time), x(x), y(y), z(z) {}

VelocityMeasurement::VelocityMeasurement(double time, double vx, double vy, double vz) : time(time), vx(vx), vy(vy), vz(vz) {}

