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

vector<TelemetryRow> loadTelemetryData(const string &filename)
{
    vector<TelemetryRow> rows;
    ifstream inputFile(filename);

    if(!inputFile.is_open())
    {
        cout << "Error: unable to open the file" << endl;
        return rows;
    }

    string line;

    while(getline(inputFile, line))
    {
        stringstream ss(line);
        string value;
        vector<double> values;

        while(getline(ss, value, ','))
        {
            values.push_back(stod(value));
        }
        
        if(values.size() >= 10)
        {
            TelemetryRow row;
            row.time = values[0];
            row.x = values[1];
            row.y = values[2];
            row.z = values[3];
            row.vx = values[4];
            row.vy = values[5];
            row.vz = values[6];
            row.ax = values[7];
            row.ay = values[8];
            row.az = values[9];

            rows.push_back(row);
        }
    }
    return rows;
}

void printTelemetryRow(const TelemetryRow &row)
{
    cout << "Time: " << row.time 
    << " | Position (" << ", X: " << row.x << ", Y: " << row.y << ", Z: " << row.z << ")"
    << " | Velocity ("    << ", Vx: " << row.vx << ", Vy: " << row.vy << ", Vz: " << row.vz << ")"
    << " | Acceleration (" << row.ax << ", " << row.ay << ", " << row.az << ")" << endl;
}