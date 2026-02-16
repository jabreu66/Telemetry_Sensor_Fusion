#include <iostream>
#include "est_state.h"
#include <cmath>


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
    double x_pred = this->x + this->vx*dt + (0.5*this->ax)*(dt * dt);
    double vx_pred = this->vx + this->ax*dt;
    double ax_pred = this->ax;
    double F[3][3] = {{1, dt, 0.5*dt*dt}, {0, 1, dt}, {0, 0, 1}};

    double Q[3][3] = {};
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

    double FP[3][3] = {};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {                
                FP[i][j] +=  F[i][k] * this->cov_matrix[k][j];
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

    
    estimated_state est_state(x_pred, vx_pred, ax_pred, p_pred[0][0], p_pred[1][1], p_pred[2][2]);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
           est_state.cov_matrix[i][j] = p_pred[i][j];
        }
    }

    return est_state;
    
}

estimated_state estimated_state::correction(double x_pred, double vx_pred, double ax_pred, double x_gps, double vx_meas, double R_gps, double R_vel, bool has_gps, bool has_vel)
{
    double total_uncertainty = 0;
    double Kx = 0;
    double Kv = 0;
    double Ka = 0;
//    this->cov_matrix;
if(has_gps){
   double gps_innovation = x_gps - x_pred;

   if(std::abs(gps_innovation) > 50){
        has_gps = false;
   }

   if(has_gps){
        total_uncertainty = this->cov_matrix[0][0] + R_gps;
        
        Kx = this->cov_matrix[0][0] / total_uncertainty;
        Kv = this->cov_matrix[1][0] / total_uncertainty; 
        Ka = this->cov_matrix[2][0] / total_uncertainty;

        x_pred = x_pred + Kx * gps_innovation;
        vx_pred = vx_pred + Kv * gps_innovation;
        ax_pred = ax_pred + Ka * gps_innovation;

        double row0[3] = {this->cov_matrix[0][0], this->cov_matrix[0][1], this->cov_matrix[0][2]};
        double K[3] = {Kx, Kv, Ka};

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                this->cov_matrix[i][j] -= K[i] * row0[j]; 
            }
        }
    }
}   
   // vel sec
if(has_vel){
    double vel_innovation = vx_meas - vx_pred;
    if(std::abs(vel_innovation) > 20)
    {
        has_vel = false;
    }
            if(has_vel){
            total_uncertainty = this->cov_matrix[1][1] + R_vel;
        
            Kx = this->cov_matrix[0][1] / total_uncertainty;
            Kv = this->cov_matrix[1][1] / total_uncertainty;
            Ka = this->cov_matrix[2][1] / total_uncertainty;

        x_pred = x_pred + Kx * vel_innovation;
        vx_pred = vx_pred + Kv * vel_innovation;
        ax_pred = ax_pred + Ka * vel_innovation;

        double row1[3] = {this->cov_matrix[1][0], this->cov_matrix[1][1], this->cov_matrix[1][2]};
        double vK[3] = {Kx, Kv, Ka};

        for(int i = 0; i < 3; i++)
        {
                for(int j = 0; j < 3; j++)
                {
                    this->cov_matrix[i][j] -= vK[i] * row1[j]; 
                }
        }
    }
}

   estimated_state corrected(x_pred, vx_pred, ax_pred, this->cov_matrix[0][0], this->cov_matrix[1][1], this->cov_matrix[2][2]);

   for(int i = 0; i < 3; i++)
   {
        for(int j = 0; j < 3; j++)
        {
            corrected.cov_matrix[i][j] = this->cov_matrix[i][j];
        }
   }
   return corrected;
   
    // return estimated_state(x_new, v_new, P_x_new, P_v_new, P_A_new);
}