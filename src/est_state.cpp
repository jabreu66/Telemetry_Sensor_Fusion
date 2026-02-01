#include <iostream>
#include "est_state.h"

estimated_state::estimated_state(double pos, double vel, double p_var, double v_var, double a_var) : x(pos), vx(vel), pos_variance(p_var), vel_variance(v_var), acc_variance(a_var) {}

estimated_state::estimated_state() : x(0), vx(0), pos_variance(0), vel_variance(0)
{

}

estimated_state estimated_state::prediction(double Q_x, double Q_v, double Q_a, double dt)
{
    // estimated_state est;
    double x = this->x + (this->vx * dt);
    double vx = this->vx;
    double ax = this->ax;
    double pos_variance_pred = this->pos_variance + Q_x;
    double vel_variance_pred = this->vel_variance + Q_v;
    double acc_variance_pred = this->acc_variance + Q_a;
    estimated_state est(x, vx, pos_variance_pred, vel_variance_pred, acc_variance_pred);
    return est;
    
}

estimated_state estimated_state::correction(double x_pred, double vx_pred, double x_gps, double vx_meas, double R_gps, double R_vel)
{
   
    double Kx = this->pos_variance/(this->pos_variance + R_gps);
    double Kv = this->vel_variance/(this->vel_variance + R_vel);

    double pos_innovation = x_gps - x_pred;
    double vel_innovation = vx_meas - vx_pred;

    double x_new = x_pred + Kx * pos_innovation;
    double v_new = vx_pred + Kv * vel_innovation;

    double P_x_new = (1 - Kx) * this->pos_variance;
    double P_v_new = (1 - Kv) * this->vel_variance;
   
    return estimated_state(x_new, v_new, P_x_new, P_v_new);
}