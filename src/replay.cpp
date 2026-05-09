#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <conio.h>


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
    << " | Position (" << " X: " << row.x << ", Y: " << row.y << ", Z: " << row.z << ")"
    << " | Velocity ("    << " Vx: " << row.vx << ", Vy: " << row.vy << ", Vz: " << row.vz << ")"
    << " | Acceleration (" << " Ax: " << row.ax << ", Ay: " << row.ay << ", Az: " << row.az << ")" << endl;
}

int findTimestampIndex(const vector<TelemetryRow> &rows, double timestamp)
{
    for(int i = 0; i < rows.size(); i++)
    {
        if(rows[i].time >= timestamp)
        {
            return i;
        }
    }

    return rows.size() - 1;
}

void replayTelemetry(vector<TelemetryRow> &rows, double playbackSpeed, int startIndex)
{
    bool isPaused = false;

    for(int i = startIndex; i < rows.size(); i++)
    {
        if (_kbhit()) // detets if a key was pressed WITHOUT halting our program
        {
            char key = _getch();
            if(key == 'p' || key == 'P')
            {
                isPaused = true;
                cout << "Playback paused. Press 'r' to resume or 'q' to quit." << endl;
            }
            else if(key == 'q' || key == 'Q')
            {
                cout << "\nExiting playback... " << endl;
                return;
            }
        }

        while(isPaused)
        {
            if (_kbhit())
            {
                char key = _getch();
                if(key == 'r' || key == 'R')
                {
                    isPaused = false;
                    cout << "Resuming playback... " << endl;
                }
                else if(key == 'q' || key == 'Q')
                {
                    cout << "\nExiting playback... " << endl;
                    return;
                }
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        printTelemetryRow(rows[i]);        

        if(i+1 < rows.size())
        {
            double diffTime = rows[i + 1].time - rows[i].time;
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
    double startTime;
    cout << "Controls: Press 'p' to pause, 'r' to resume, 'q' to quit." << endl;
    cout << "Enter start time for playback (e.g., 0 for beginning): ";
    cin >> startTime;
    int startIndex = findTimestampIndex(telemetryData, startTime);  
    cout << "Enter playback speed: (e.g., 1 for real-time, 2 for double speed, 0.5 for half speed): ";
    cin >> playbackSpeed;
    if(playbackSpeed <= 0)
    {
        cout << "Playback speed is invalid, defaulting to 1" << endl;
        playbackSpeed = 1.0;
    }
    replayTelemetry(telemetryData, playbackSpeed, startIndex);

    return 0;
}