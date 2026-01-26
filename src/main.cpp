#include <iostream>
#include "csv_writer.h"
#include "state.h"
#include "sensors.hpp"
#include "est_state.h"
using namespace std;

Writer w("logs.csv");
Writer gw("gps.csv");
Writer gv("vel.csv");
Writer est("estimate.csv");

int main()
{
    float dt = 0.1; // delta time
    // cout << "Hello World " << endl;
    State state(0, 0, 0, 0, 50, 0, 0);
    estimated_state est_state(0, 50);
    est_state.prediction(0,50, 0);
    
    for(float i = 0; i < 10; i += dt) // increase time by 0.1 seconds
    {
        state.t_s = i;
        // std::cout << "i is " << i << " state.t_s is " << state.t_s << std::endl;
        state.x_m += state.vx_mps * dt;
        GPS gpsObject = gpsSimulator(state);
        VelocityMeasurement velObject = velocitySimulator(state);
        w.writeRow(state);   
        gw.writeRowGPS(gpsObject);
        gv.writeRowVel(velObject);
    }
    return 0;
}