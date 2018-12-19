#include "Planets.h"

Planets::Planets(float distFromSun): m_distFromSun(distFromSun)
{
    //ctor
    m_planet.setFillColor(sf::Color::Blue);

    //Sets origin to center
    m_planet.setOrigin(7.5, 7.5);

    //Position is equal to sun's position + distance passed when instance is created
    m_position.x = (m_screenWidth / 2) + m_distFromSun;
    m_position.y = (m_screenHeight / 2) + m_distFromSun;
}

Planets::~Planets()
{
    //dtor
}

//Function to move planets according to sun's position
void Planets::Move(Sun m_sun)
{
    sf::Vector2f m_sunPosition = m_sun.GetPosition();

    sf::Vector2f zeroPos = m_position - m_sunPosition;

    m_position.x = (zeroPos.x * cos(m_angle)) - (zeroPos.y * sin(m_angle));
    m_position.y = (zeroPos.y * cos(m_angle)) + (zeroPos.x * sin(m_angle));

    m_position += m_sunPosition;

    while (clock.getElapsedTime().asMilliseconds() < 80);
    clock.restart();
}

void Planets::Render(sf::RenderWindow& window)
{
    m_planet.setPosition(m_position);
    window.draw(m_planet);
}

sf::Vector2f Planets::GetPosition()
{
    return m_position;
}

float Planets::GetSize()
{
    return m_size;
}
