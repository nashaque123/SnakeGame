#include "PlayerSnake.h"

PlayerSnake::PlayerSnake(std::string name) : Snake(name)
{
    //ctor
    //Randomise position in the region of the bottom right corner
    m_position.x = rand() % 50 + 50;
    m_position.y = rand() % 50 + 50;

    //Align the position to a grid to make collisions easier
    m_xAligned = m_position.x / (m_movementStep * 2);
    m_xAligned *= (m_movementStep * 2);
    m_yAligned = m_position.y / (m_movementStep * 2);
    m_yAligned *= (m_movementStep * 2);

    m_position.x = m_xAligned;
    m_position.y = m_yAligned;

    m_snakeSegments.push_front(m_position);

    circle.setFillColor(sf::Color::Magenta);
    //Set origin to center of snake
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}

PlayerSnake::~PlayerSnake()
{
    //dtor
}

//Changes direction according to key press switch statement in game class
void PlayerSnake::PlayerAltersDirection()
{

}
