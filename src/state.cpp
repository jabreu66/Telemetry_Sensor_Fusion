#include <iostream>
#include "state.h"

State::State (float t_s, int x_m, int y_m, int z_m, int vx_mps, int vy_mps, int vz_mps, double a_x, double a_y, double a_z) : t_s(t_s), x_m(x_m), y_m(y_m), z_m(z_m), vx_mps(vx_mps), vy_mps(vy_mps), vz_mps(vz_mps), a_x(a_x), a_y(a_y), a_z(a_z)
{
}