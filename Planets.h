#ifndef PLANETS_H
#define PLANETS_H

#include "SFML/Graphics.hpp"
#include "Sun.h"

class Planets
{
public:
    //Takes a distance from sun when created
    //This allows creation of multiple planets with individual distances from the sun
    Planets(float distFromSun);
    ~Planets();

    //Function to move according to suns position
    void Move(Sun m_sun);

    //Returns position and size
    sf::Vector2f GetPosition();
    float GetSize();

    void Render(sf::RenderWindow& window);

private:
    //Uses clock to lower speed of movement
    sf::Clock clock;

    float m_size{15.0f};
    sf::CircleShape m_planet{m_size};
    sf::Vector2f m_position{0, 0};

    float m_distFromSun;

    //Angle for movement
    const float m_angle = 0.2f;

    int m_screenWidth{800};
    int m_screenHeight{600};
};

#endif // PLANETS_H
