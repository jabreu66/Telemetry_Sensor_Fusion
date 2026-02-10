#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "csv_writer.h"



Writer::Writer(std::string filename)
{
    // std::ifstream file(filename); -- Make the ifstream object a member of the class
    outputFile.open(filename);

    if(!outputFile.is_open())
    {
        std::cout << "Error: unable to open the file" << std::endl;
        return;
    }
    else
    {
        // std::cout << "file is opened " << std::endl;
    }
}

void Writer::writeRow(State state)
{
    
    // std::ofstream outputFile(filename); //declare an ofstream object and write to the file
    // outputFile("logs.csv");
    if(outputFile.is_open())
    {
        outputFile << state.t_s << ", " << state.x_m  << ", " << state.y_m  << ", " << state.z_m  << ", " << state.vx_mps << ", " << state.vy_mps << ", " << state.vz_mps;
        outputFile << "\n";
        // outputFile.close();
    }
}

void Writer::writeRowGPS(GPS state)
{
    if(outputFile.is_open())
    {
        outputFile << state.time << ", " << state.x  << ", " << state.y  << ", " << state.z;
        outputFile << "\n";
    }
}

void Writer::writeRowVel(VelocityMeasurement state)
{
    if(outputFile.is_open())
    {
        outputFile << state.time << ", " << state.vx << ", " << state.vy << ", " << state.vz;
        outputFile << "\n";
    }
}

void Writer::writeRowEst(estimated_state state)
{
    if(outputFile.is_open())
    {
        outputFile  << state.x  << ", " << state.vx << ", " << state.ax;
        outputFile << "\n";
    }
}

