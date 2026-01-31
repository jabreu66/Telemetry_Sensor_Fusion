#include <iostream>
#include <string>

#ifndef STATE_H
#define STATE_H

struct State{
      
    float t_s; // time
    int x_m, y_m, z_m; // position
    int vx_mps, vy_mps, vz_mps; // velocity
    double a_x, a_y, a_z;

    State(float t_s, int x_m, int y_m, int z_m, int vx_mps, int vy_mps, int vz_mps, double a_x, double a_y, double a_z);
};

#endif