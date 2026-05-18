#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SFML/Graphics.hpp>

class Visualizer
{
    private:
        sf::RenderWindow window;

        float scale;
        float x_offset;
        float y_offset;

    public: 
        Visualizer();

        bool isOpen();
        void handleEvents();
}



#endif VISUALIZER_H



