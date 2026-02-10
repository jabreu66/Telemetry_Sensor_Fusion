#include <iostream>
#include "state.h"

State::State (float t_s, double x_m, double y_m, double z_m, double vx_mps, double vy_mps, double vz_mps, double a_x, double a_y, double a_z) : t_s(t_s), x_m(x_m), y_m(y_m), z_m(z_m), vx_mps(vx_mps), vy_mps(vy_mps), vz_mps(vz_mps), a_x(a_x), a_y(a_y), a_z(a_z)
{
}