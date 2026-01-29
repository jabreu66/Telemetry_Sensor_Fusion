#include <iostream>
#include "est_state.h"

estimated_state::estimated_state(double pos, double vel, double p_var, double v_var) : x(pos), vx(vel), pos_variance(p_var), vel_variance(v_var) {}

estimated_state::estimated_state() : x(0), vx(0), pos_variance(0), vel_variance(0)
{

}

estimated_state estimated_state::prediction(double x_hat, double vx_hat, double Q_x, double Q_v, double dt)
{
    // estimated_state est;
    double x = x_hat + (vx_hat * dt);
    double vx = vx_hat;
    double pos_variance_pred = pos_variance + Q_x;
    double vel_variance_pred = vel_variance + Q_v;
    estimated_state est(x, vx, Q_x, Q_v);
    return est;
    
}

estimated_state estimated_state::correction(double x_pred, double vx_pred, double x_gps, double vx_meas, double tru_weight)
{
    if(tru_weight > 1)
    {
        tru_weight = 1;
    }
    else if(tru_weight < 0)
    {
        tru_weight = 0;
    }

    double w_x_pred = tru_weight;
    double w_v_pred = tru_weight;

    double w_x_sensor = 1 - w_x_pred;
    double w_v_sensor = 1 - w_v_pred;

    double blended_pos = (x_pred * w_x_pred) + (x_gps * w_x_sensor);
    double blended_vel = (vx_pred * w_v_pred) + (vx_meas * w_v_sensor);

    estimated_state est(blended_pos, blended_vel);
    return est;
}