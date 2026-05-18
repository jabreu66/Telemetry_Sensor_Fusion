#include <iostream>
#include "est_state.h"
#include <cmath>


estimated_state::estimated_state(double initial_state[STATE_SIZE], double initial_variance[STATE_SIZE]) 
{
    for(int i = 0; i < STATE_SIZE; i++)
    {
        state[i] = initial_state[i];
    }

    for(int i = 0; i < STATE_SIZE; i++)
    {
        for(int j = 0; j < STATE_SIZE; j++)
        {
            cov_matrix[i][j] = 0;
        }
    }

   for(int i = 0; i < STATE_SIZE; i++)
   {
        cov_matrix[i][i] = initial_variance[i];
   }

   
}

estimated_state::estimated_state()
{
    for(int i = 0; i < STATE_SIZE; i++)
    {
        state[i] = 0;
    }

    for(int i = 0; i < STATE_SIZE; i++)
    {
        for(int j = 0; j < STATE_SIZE; j++)
        {
            cov_matrix[i][j] = 0;
        }
    }

}

estimated_state estimated_state::prediction(double process_noise[STATE_SIZE], double dt)
{
    double predicted_state[STATE_SIZE] = {};

    // x predictions
    predicted_state[0] = state[0] + state[1] * dt + 0.5 * state[2] * dt * dt;
    predicted_state[1] = state[1] + state[2] * dt;
    predicted_state[2] = state[2];

    // y predicts
    predicted_state[3] = state[3] + state[4] * dt + 0.5 * state[5] * dt * dt;
    predicted_state[4] = state[4] + state[5] * dt;
    predicted_state[5] = state[5];

    // z predicts
    predicted_state[6] = state[6] + state[7] * dt + 0.5 * state[8] * dt * dt;
    predicted_state[7] = state[7] + state[8] * dt;
    predicted_state[8] = state[8];


    double F[STATE_SIZE][STATE_SIZE] = {
    {1, dt, 0.5*dt*dt,  0, 0, 0,     0, 0, 0}, // x 
    {0, 1, dt,          0, 0, 0,     0, 0, 0}, // vx
    {0, 0, 1,           0, 0, 0,     0, 0, 0}, // ax
    {0, 0, 0,       1, dt, 0.5*dt*dt,   0, 0, 0}, // y
    {0, 0, 0,           0, 1, dt,    0, 0, 0}, // vy
    {0, 0, 0,           0, 0, 1,    0, 0, 0}, // ay
    {0, 0, 0,           0, 0, 0,     1, dt, 0.5*dt*dt}, // z
    {0, 0, 0,           0, 0, 0,     0, 1, dt}, // vz 
    {0, 0, 0,           0, 0, 0,     0, 0, 1} // az
}; 

    double Q[STATE_SIZE][STATE_SIZE] = {};

   for (int i = 0; i < STATE_SIZE; i++)
   {
        Q[i][i] = process_noise[i];
   }

    double FP[STATE_SIZE][STATE_SIZE] = {};

    for(int i = 0; i < STATE_SIZE; i++)
    {
        for(int j = 0; j < STATE_SIZE; j++)
        {
            for(int k = 0; k < STATE_SIZE; k++)
            {                
                FP[i][j] +=  F[i][k] * this->cov_matrix[k][j];
            }    
        }
    }

    double FT[STATE_SIZE][STATE_SIZE] = {};

    for(int i = 0; i < STATE_SIZE; i++)
    {
        for(int j = 0; j < STATE_SIZE; j++)
        {
          FT[i][j] = F[j][i];
        }
    }

    double p_pred[STATE_SIZE][STATE_SIZE] = {};

    for(int i = 0; i < STATE_SIZE; i++)
    {
        for(int j = 0; j < STATE_SIZE; j++)
        {
            for(int k = 0; k < STATE_SIZE; k++)
            {
                p_pred[i][j] += FP[i][k] * FT[k][j];
            } 
        }
    }

   for(int i = 0; i < STATE_SIZE; i++)
   {
        for(int j = 0; j < STATE_SIZE; j++)
        {
            p_pred[i][j] += Q[i][j];
        }
   }

   double predicted_variance[STATE_SIZE] = {};

   for(int i = 0; i < STATE_SIZE; i++)
   {
        predicted_variance[i] = p_pred[i][i];
   }

    
    estimated_state est_state(predicted_state, predicted_variance);

    for(int i = 0; i < STATE_SIZE; i++)
    {
        for(int j = 0; j < STATE_SIZE; j++)
        {
           est_state.cov_matrix[i][j] = p_pred[i][j];
        }
    }

    return est_state;
    
}

estimated_state estimated_state::correction(double gps_measurement[3], double vel_measurement[3], double gps_variance, double vel_variance, bool has_gps, bool has_vel)
{
    
    estimated_state corrected;

    for(int i = 0; i < STATE_SIZE; i++)
    {
        corrected.state[i] = this->state[i];

        for(int j = 0; j < STATE_SIZE; j++)
        {
            corrected.cov_matrix[i][j] = this->cov_matrix[i][j];    
        }
    }

    corrected.has_gps = has_gps;
    corrected.has_vel = has_vel;

//    this->cov_matrix;
if(has_gps){

    // x
   double gps_x_innovation = gps_measurement[0] - corrected.state[0];

    if(std::abs(gps_x_innovation) <= 50)
    {
        double total_uncertainty = corrected.cov_matrix[0][0] + gps_variance;

        double K[STATE_SIZE] = {};
        
      for(int i = 0; i < STATE_SIZE; i++)
      {
        K[i] = corrected.cov_matrix[i][0] / total_uncertainty;
      }

      for(int i = 0; i < STATE_SIZE; i++)
      {
        corrected.state[i] = corrected.state[i] + K[i] * gps_x_innovation;
      }

    
      double measurement_row[STATE_SIZE] = {};

      for(int j = 0; j < STATE_SIZE; j++)
      {
        measurement_row[j] = corrected.cov_matrix[0][j];
      }

        for(int i = 0; i < STATE_SIZE; i++)
        {
            for(int j = 0; j < STATE_SIZE; j++)
            {
               corrected.cov_matrix[i][j] = corrected.cov_matrix[i][j] - K[i] * measurement_row[j];
            }
        }
    }

    // y
    double gps_y_innovation = gps_measurement[1] - corrected.state[3];

   if(std::abs(gps_y_innovation) <= 50){
        
        double total_uncertainty = corrected.cov_matrix[3][3] + gps_variance;

        double K[STATE_SIZE] = {};
        
      for(int i = 0; i < STATE_SIZE; i++)
      {
        K[i] = corrected.cov_matrix[i][3] / total_uncertainty;
      }

      for(int i = 0; i < STATE_SIZE; i++)
      {
        corrected.state[i] = corrected.state[i] + K[i] * gps_y_innovation;
      }

    
      double measurement_row[STATE_SIZE] = {};

      for(int j = 0; j < STATE_SIZE; j++)
      {
        measurement_row[j] = corrected.cov_matrix[3][j];
      }

        for(int i = 0; i < STATE_SIZE; i++)
        {
            for(int j = 0; j < STATE_SIZE; j++)
            {
               corrected.cov_matrix[i][j] = corrected.cov_matrix[i][j] - K[i] * measurement_row[j];
            }
        }
    }

    // z
    double gps_z_innovation = gps_measurement[2] - corrected.state[6];

    if(std::abs(gps_z_innovation) <= 50)
    {
        double total_uncertainty = corrected.cov_matrix[6][6] + gps_variance;

        double K[STATE_SIZE] = {};
        
      for(int i = 0; i < STATE_SIZE; i++)
      {
        K[i] = corrected.cov_matrix[i][6] / total_uncertainty;
      }

      for(int i = 0; i < STATE_SIZE; i++)
      {
        corrected.state[i] = corrected.state[i] + K[i] * gps_z_innovation;
      }

    
      double measurement_row[STATE_SIZE] = {};

      for(int j = 0; j < STATE_SIZE; j++)
      {
        measurement_row[j] = corrected.cov_matrix[6][j];
      }

        for(int i = 0; i < STATE_SIZE; i++)
        {
            for(int j = 0; j < STATE_SIZE; j++)
            {
               corrected.cov_matrix[i][j] = corrected.cov_matrix[i][j] - K[i] * measurement_row[j];
            }
        }
    }
    
}   
   // vel sec
if(has_vel){

    double vel_x_innovation = vel_measurement[0] - corrected.state[1];

    if(std::abs(vel_x_innovation) <= 20)
    {
        double total_uncertainty = corrected.cov_matrix[1][1] + vel_variance;
        double K[STATE_SIZE] = {};

        for(int i = 0; i < STATE_SIZE; i++)
        {
            K[i] = corrected.cov_matrix[i][1] / total_uncertainty;
        }

        for(int i = 0; i < STATE_SIZE; i++)
        {
            corrected.state[i] = corrected.state[i] + K[i] * vel_x_innovation;
        }

        double measurement_row[STATE_SIZE] = {};

        for(int j = 0; j < STATE_SIZE; j++)
        {
            measurement_row[j] = corrected.cov_matrix[1][j];
        }

        for(int i = 0; i < STATE_SIZE; i++)
        {
                for(int j = 0; j < STATE_SIZE; j++)
                {
                    corrected.cov_matrix[i][j] -= K[i] * measurement_row[j]; 
                }
        }
    }

    double vel_y_innovation = vel_measurement[1] - corrected.state[4];

    if(std::abs(vel_y_innovation) <= 20)
    {
        double total_uncertainty = corrected.cov_matrix[4][4] + vel_variance;
        double K[STATE_SIZE] = {};

        for(int i = 0; i < STATE_SIZE; i++)
        {
            K[i] = corrected.cov_matrix[i][4] / total_uncertainty;
        }

        for(int i = 0; i < STATE_SIZE; i++)
        {
            corrected.state[i] = corrected.state[i] + K[i] * vel_y_innovation;
        }

        double measurement_row[STATE_SIZE] = {};

        for(int j = 0; j < STATE_SIZE; j++)
        {
            measurement_row[j] = corrected.cov_matrix[4][j];
        }

        for(int i = 0; i < STATE_SIZE; i++)
        {
                for(int j = 0; j < STATE_SIZE; j++)
                {
                    corrected.cov_matrix[i][j] -= K[i] * measurement_row[j]; 
                }
        }
    }

    double vel_z_innovation = vel_measurement[2] - corrected.state[7];

    if(std::abs(vel_z_innovation) <= 20)
    {
        double total_uncertainty = corrected.cov_matrix[7][7] + vel_variance;
        double K[STATE_SIZE] = {};

        for(int i = 0; i < STATE_SIZE; i++)
        {
            K[i] = corrected.cov_matrix[i][7] / total_uncertainty;
        }

        for(int i = 0; i < STATE_SIZE; i++)
        {
            corrected.state[i] = corrected.state[i] + K[i] * vel_z_innovation;
        }

        double measurement_row[STATE_SIZE] = {};

        for(int j = 0; j < STATE_SIZE; j++)
        {
            measurement_row[j] = corrected.cov_matrix[7][j];
        }

        for(int i = 0; i < STATE_SIZE; i++)
        {
                for(int j = 0; j < STATE_SIZE; j++)
                {
                    corrected.cov_matrix[i][j] -= K[i] * measurement_row[j]; 
                }
        }
    }
}

//    estimated_state corrected(x_pred, vx_pred, ax_pred, this->cov_matrix[0][0], this->cov_matrix[1][1], this->cov_matrix[2][2]);

   return corrected;
   
}