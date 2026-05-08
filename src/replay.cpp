#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>


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

void replayTelemetry(vector<TelemetryRow> &rows, double playbackSpeed)
{
    for(int i = 0; i < rows.size(); i++)
    {
        printTelemetryRow(rows[i]);

        if(i+1 < rows.size())
        {
            double diffTime = rows[i+1].time - rows[i].time;
            int millisecondDelay = static_cast<int>((diffTime * 1000) / playbackSpeed);
            this_thread::sleep_for(chrono::milliseconds(millisecondDelay));
        }
    }
}

int main()
{
    vector<TelemetryRow> telemetryData = loadTelemetryData("logs.csv");

    if(telemetryData.size() == 0)
    {
        cout << "No telemetry data loaded." << endl;
        return 1;
    }

    cout << "Loaded " << telemetryData.size() << " rows of telemetry data." << endl;

    double playbackSpeed = 1.0; 
    cout << "Enter playback speed: (e.g., 1 for real-time, 2 for double speed, 0.5 for half speed): ";
    cin >> playbackSpeed;
    replayTelemetry(telemetryData, playbackSpeed);

    return 0;
}