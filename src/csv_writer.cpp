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
        outputFile << state.t_s << ", " << state.x_m  << ", " << state.y_m  << ", " << state.z_m  << ", " << state.vx_mps << ", " << state.vy_mps << ", " << state.vz_mps  << ", " << state.a_x << ", " << state.a_y << ", " << state.a_z;
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

void Writer::writeRowEst(const estimated_state &est_state)
{
    if(outputFile.is_open())
    {
        outputFile  << est_state.state[0]  << ", " << est_state.state[1] << ", " << est_state.state[2] <<
        ", " << est_state.state[3] << ", " << est_state.state[4] << ", " << est_state.state[5] <<
        ", " << est_state.state[6] << ", " << est_state.state[7] << ", " << est_state.state[8];
        outputFile << "\n";
    }
}

