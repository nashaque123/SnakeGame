#include "Collectable.h"
#include <iostream>

Collectable::Collectable()
{
    //ctor

    //Set origin to center
    m_item.setOrigin(m_item.getRadius(), m_item.getRadius());

    // Set the items fill colour according to their randomly assigned score
    m_score = rand() % 3 + 1;

    switch(m_score)
    {
    case 1:
        m_item.setFillColor(sf::Color::Red);
        break;
    case 2:
        m_item.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        m_item.setFillColor(sf::Color::Green);
        break;
    default:
        m_item.setFillColor(sf::Color::White);
        break;
    }
}

Collectable::~Collectable()
{
    //dtor
}

//Spawn when m_alive becomes true
bool Collectable::IsAlive()
{
    if(m_alive==false)
    {
        if (rand() % 50 == 0)
        {
            this->Spawn();
            m_alive = true;
        }
    }
    return m_alive;
}

void Collectable::Render(sf::RenderWindow& window)
{
    //draw our item shape to the window
    if (m_alive==true)
        window.draw(m_item);
}

void Collectable::Spawn()
{
    //Randomly give a position to the collectable to spawn
    m_position.x = rand() % 700 + 50;
    m_position.y = rand() % 500 + 50;

    //Align position to same grid as snake for collisions
    m_xAligned = m_position.x / 18;
    m_xAligned *= 18;
    m_yAligned = m_position.y / 18;
    m_yAligned *= 18;

    m_position.x = m_xAligned;
    m_position.y = m_yAligned;

    m_item.setPosition(m_position);
}

sf::Vector2f Collectable::GetPosition()
{
    return m_position;
}

int Collectable::GetScore()
{
    return m_score;
}

float Collectable::GetSize()
{
    return m_size;
}

void Collectable::SetAliveToFalse()
{
    this->m_alive = false;
}
