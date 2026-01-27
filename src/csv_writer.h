#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include "state.h"
#include "sensors.hpp"
#include "est_state.h"


class Writer{
    
    public:

        explicit Writer(std::string filename);
        void writeRow(State state);
        void writeRowGPS(GPS state);
        void writeRowVel(VelocityMeasurement state);
        std::ofstream outputFile;
        // std::ifstream file;
        void writeRowEst(estimated_state state);

    

};


#endif