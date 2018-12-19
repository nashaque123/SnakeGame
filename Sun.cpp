#include "Sun.h"

Sun::Sun()
{
    //ctor
    m_sun.setFillColor(sf::Color::Yellow);

    //Places origin of sun in the center and places sun in the center of the screen
    m_sun.setOrigin(10, 10);

    m_position.x = m_screenWidth / 2;
    m_position.y = m_screenHeight / 2;
}

Sun::~Sun()
{
    //dtor
}

void Sun::Render(sf::RenderWindow& window)
{
    m_sun.setPosition(m_position);
    window.draw(m_sun);
}

sf::Vector2f Sun::GetPosition()
{
    return m_position;
}

float Sun::GetSize()
{
    return m_size;
}
