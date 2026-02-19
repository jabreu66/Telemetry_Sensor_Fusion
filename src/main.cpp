#include <iostream>
#include <random>
#include "csv_writer.h"
#include "state.h"
#include "sensors.hpp"
#include "est_state.h"
using namespace std;

Writer w("logs.csv");
Writer gw("gps.csv");
Writer gv("vel.csv");
Writer est("estimate.csv");

double R_gps = 4;
double R_vel = 1;

double Q_x = 0.1;
double Q_v = 0.5;
double Q_a = 0.9;

// std::mt19937 rand_gen(22);
std::normal_distribution<double> accelNoise{0, .1};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(1, 100);



int main()
{
    float dt = 0.1; // delta time
    // cout << "Hello World " << endl;
    State state(0, 0, 0, 0, 50, 0, 0, 2, 0, 0);
    estimated_state est_state(0, 50, 2, 4, 1, 4);
    int step = 0;
    bool vel_update = false, gps_update = false;
    for(float i = 0; i < 10; i += dt) // increase time by 0.1 seconds
    {
        
        state.t_s = i;
        if (i < 2) state.a_x = 2.0;
        else if (i >= 2 && i < 6.0 ) state.a_x = 0.0;
        else if (i >= 6 && i < 8.0) state.a_x = -1.0;
        else state.a_x = 0.0;
       
        // std::cout << "i is " << i << " state.t_s is " << state.t_s << std::endl;
        state.a_x += accelNoise(rand_gen);
        state.x_m +=  state.vx_mps*dt + (0.5*state.a_x)*(dt * dt);
        state.vx_mps = state.vx_mps + state.a_x*dt;

        estimated_state new_est_state = est_state.prediction(Q_x, Q_v, Q_a, dt);

        gps_update = (step % 10 == 0);
        int gps_dropoff = distrib(gen);
      
        GPS gpsObject(0,0,0,0);
        if(gps_update){
            if(gps_dropoff >= 1 && gps_dropoff <= 5)
            {
                gps_update = false;
            }
            if(gps_update)
            { 
                gpsObject = gpsSimulator(state);
                gw.writeRowGPS(gpsObject);
            }

        }

        int vel_dropoff = distrib(gen);
        VelocityMeasurement velObject(0,0,0,0);
        vel_update = (step % 2 == 0);
        if(vel_update){
            if(vel_dropoff >= 1 && vel_dropoff <= 5)
            {
                vel_update = false;
            }
            if(vel_update)
            {
                velObject = velocitySimulator(state);
                gv.writeRowVel(velObject);
            }
        }

        step++;

        estimated_state corrected_est_state = new_est_state.correction(new_est_state.x, new_est_state.vx, new_est_state.ax, gpsObject.x, velObject.vx, R_gps, R_vel, gps_update, vel_update);
        est_state = corrected_est_state;

        w.writeRow(state);   
        est.writeRowEst(corrected_est_state);
    }
    return 0;
}