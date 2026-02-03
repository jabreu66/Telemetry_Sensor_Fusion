#include <iostream>
#include <string>

#ifndef STATE_H
#define STATE_H

struct State{
      
    float t_s; // time
    double x_m, y_m, z_m; // position
    double vx_mps, vy_mps, vz_mps; // velocity
    double a_x, a_y, a_z;

    State(float t_s, double x_m, double y_m, double z_m, double vx_mps, double vy_mps, double vz_mps, double a_x, double a_y, double a_z);
};

#endif