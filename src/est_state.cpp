#include <iostream>
#include "est_state.h"

estimated_state::estimated_state(double pos, double vel, double acc, double p_var, double v_var, double a_var) : x(pos), vx(vel), ax(acc) 
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cov_matrix[i][j] = 0;
        }
    }

    cov_matrix[0][0] = p_var;
    cov_matrix[1][1] = v_var;
    cov_matrix[2][2] = a_var;
}

estimated_state::estimated_state() : x(0), vx(0), ax(0)
{

}

estimated_state estimated_state::prediction(double Q_x, double Q_v, double Q_a, double dt)
{
    // estimated_state est;
    double x = this->x + vx*dt + (0.5*ax)*(dt * dt);
    double vx = this->vx + this->ax*dt;
    double ax = this->ax;
    double F[3][3] = {{1, dt, 0.5*dt*dt}, {0, 1, dt}, {0, 0, 1}};

    double Q[3][3];
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            Q[i][j] = 0;
        }
    }

    Q[0][0] = Q_x;
    Q[1][1] = Q_v;
    Q[2][2] = Q_a;

    double FP[3][3];

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {                
                FP[i][j] +=  F[k][j] * this->cov_matrix[i][k];
            }    
        }
    }

    double FT[3][3] = {};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
          FT[i][j] = F[j][i];
        }
    }

    double p_pred[3][3] = {};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                p_pred[i][j] += FP[i][k] * FT[k][j];
            } 
        }
    }

   for(int i = 0; i < 3; i++)
   {
        for(int j = 0; j < 3; j++)
        {
            p_pred[i][j] += Q[i][j];
        }
   }

    
    estimated_state est_state(x, vx, ax, p_pred[0][0], p_pred[1][1], p_pred[2][2]);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            this->cov_matrix[i][j] = p_pred[i][j];
        }
    }

    return est_state;
    
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
    double P_A_new = 0;
   
    return estimated_state(x_new, v_new, P_x_new, P_v_new, P_A_new);
}