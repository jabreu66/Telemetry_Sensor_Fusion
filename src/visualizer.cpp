#include "visualizer.h"


Visualizer::Visualizer() : window(sf::Videomode({1000u, 800u}, "Telemetry Sensor Fusion"), scale(5.0f), x_offset(100.0f), y_offset(400.0f))
{

}

bool Visualizer::isOpen()
{
    return window.isOpen();
}

void Visualizer::handleEvents()
{
    
}