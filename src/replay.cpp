#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


using namespace std;

struct TelemetryRow
{
    double time;
    double x;
    double y;   
    double z;
    double vx;
    double vy;
    double vz;
    double ax;
    double ay;
    double az;
};