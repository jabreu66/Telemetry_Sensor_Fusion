#include "visualizer.h"
#include <optional>

Visualizer::Visualizer() : window(sf::VideoMode({1000u, 800u}), "Telemetry Sensor Fusion"), scale(0.5f), x_offset(50.0f), y_offset(700.0f)
{

}

bool Visualizer::isOpen()
{
    return window.isOpen();
}

void Visualizer::handleEvents()
{
    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

void Visualizer::clear()
{
    window.clear(sf::Color::Black);
}

void Visualizer::display()
{
    window.display();
}

sf::Vector2f Visualizer::convertToScreen(double x, double y)
{
    float screen_x = x_offset + static_cast<float>(x) * scale;
    float screen_y = y_offset - static_cast<float>(y) * scale;

    return sf::Vector2f(screen_x, screen_y);
}

void Visualizer::drawPoint(double x, double y, sf::Color color, float radius)
{
    sf::CircleShape point(radius);
    point.setFillColor(color);

    sf::Vector2f screen_pos = convertToScreen(x, y);

    point.setPosition({screen_pos.x - radius, screen_pos.y - radius});

    window.draw(point);
}