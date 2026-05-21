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

        sf::Vector2f convertToScreen(double x, double y);

    public: 
        Visualizer();

        bool isOpen();
        void handleEvents();
        void clear(); 
        void display();
        void drawPoint(double x, double y, sf::Color color, float radius);
};



#endif 



