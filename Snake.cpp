#include "Snake.h"
#include "Collectable.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

Snake::Snake(std::string name): m_name(name)
{
    //ctor
    //Constructor not needed as used in child classes
}

Snake::~Snake()
{
    //dtor
}

//Constantly moves in a direction determined by m_direction
void Snake::Move()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(25));

    switch(m_direction)
    {
    case EDirection::eNorth:
        m_position.y -= (m_movementStep * 2);
        break;
    case EDirection::eEast:
        m_position.x += (m_movementStep * 2);
        break;
    case EDirection::eWest:
        m_position.x -= (m_movementStep * 2);
        break;
    case EDirection::eSouth:
        m_position.y += (m_movementStep * 2);
        break;
    case EDirection::eNull:
        break;
    default:
        break;
    }

    //Only remove from back if grow amount is 0
    m_snakeSegments.push_front(m_position);

    if (m_growAmount>0)
        m_growAmount--;
    else
        m_snakeSegments.pop_back();
}

void Snake::Render(sf::RenderWindow& window)
{
    //draw our circle shape to the window
    for (auto& s : m_snakeSegments)
    {
        circle.setPosition(s);
        window.draw(circle);
    }
}

sf::Vector2f Snake::GetPosition()
{
    return m_position;
}

//Change the m_direction variable when requested by player or AI
void Snake::ChangeDirectionVariable(EDirection newDirection)
{
    m_direction = newDirection;
}

EDirection Snake::GetDirection()
{
    return m_direction;
}

//Check if snake is colliding with the wall
void Snake::WallCollisionCheck()
{
    if (m_position.x < 18 || m_position.x > 782 || m_position.y < 18 || m_position.y > 582)
    {
        this->Death();
    }
}

//Check if snake collides with collectables
void Snake::CollectableCollisionCheck(Collectable m_collectables[])
{
    for (int i = 0; i < 5; i++)
    {
        sf::Vector2f getPosition = m_collectables[i].GetPosition();

        if (getPosition == m_position)
        {
            m_collectables[i].SetAliveToFalse();
            m_growAmount = m_collectables[i].GetScore();
            m_finalScore += m_growAmount;
        }
    }
}

//Return whether a snake is colliding with
bool Snake::SegmentCollisionCheck(sf::Vector2f pos)
{
    for (auto& otherSegment : m_snakeSegments)
    {
        if (otherSegment == pos)
            return true;
    }
    return false;
}

//Checks if snake collides with another snake
bool Snake::OtherSnakeCollisionCheck(const Snake& other) const
{
    for (auto& otherSegment : other.m_snakeSegments)
    {
        if (m_snakeSegments.front() == otherSegment)
            return true;

    }
    return false;
}

//Check if snake collides with itself
bool Snake::SelfCollisionCheck() const
{
    //Advance the iterator so it doesn't compare the head against itself
    auto it=m_snakeSegments.begin();
    std::advance(it, 1);

    while (it!=m_snakeSegments.end())
    {
        if (m_snakeSegments.front() == *it)
            return true;

        it++;
    }
    return false;
}

//Checks collision with the sun
void Snake::SunCollisionCheck(Sun m_sun)
{
    sf::Vector2f getPosition = m_sun.GetPosition();

    //Uses Pythagoras' theorem to measure distance between 2 circles
    //If distance is smaller than the sum of the radii then they are overlapping therefore colliding
    int result = sqrt(((m_position.x - getPosition.x)*(m_position.x - getPosition.x)) + ((m_position.y - getPosition.y)*(m_position.y - getPosition.y)));
    if(result < m_movementStep + m_sun.GetSize())
        this->Death();
}

//Checks collision with the planets
void Snake::PlanetCollisionCheck(Planets m_planet)
{
    sf::Vector2f getPosition = m_planet.GetPosition();

    //Uses Pythagoras' theorem to measure distance between 2 circles
    //If distance is smaller than the sum of the radii then they are overlapping therefore colliding
    int result = sqrt(((m_position.x - getPosition.x)*(m_position.x - getPosition.x)) + ((m_position.y - getPosition.y)*(m_position.y - getPosition.y)));
    if(result < m_movementStep + m_planet.GetSize())
        this->Death();
}

//Checks if planets are colliding with any segments that isn't the head
//Segments removed when collision
void Snake::SegmentPlanetCollisionCheck(Planets m_planet)
{
    int i = 1;
    for (auto& segments : m_snakeSegments)
    {

        sf::Vector2f getPosition = m_planet.GetPosition();
        float result = sqrt(((segments.x - getPosition.x)*(segments.x - getPosition.x)) + ((segments.y - getPosition.y)*(segments.y - getPosition.y)));

        if (result < m_movementStep + m_planet.GetSize())
        {
            m_snakeSegments.resize(i);
        }

        i++;

    }
}

//Sets m_alive to false when snake dies
void Snake::Death()
{
    m_alive = false;
}

bool Snake::GetAliveStatus()
{
    return m_alive;
}

int Snake::GetFinalScore()
{
    return m_finalScore;
}

//Displays score
void Snake::DisplayScore(sf::RenderWindow& window)
{
    sf::Text text;
    sf::Font font;

    font.loadFromFile("OpenSans-Semibold.ttf");

    text.setFont(font);

    //Changes position of score depending on if the name is "Player1" or "Player2"
    if (m_name == "Player1")
    {
        text.setString("Player score: " + std::to_string(m_finalScore));
        text.setCharacterSize(20);
        text.setColor(sf::Color::Magenta);
        text.move({100, 50});
    }
    else if (m_name == "Player2")
    {
        text.setString("Computer score: " + std::to_string(m_finalScore));
        text.setCharacterSize(20);
        text.setColor(sf::Color::Magenta);
        text.move({550, 50});
    }

    window.draw(text);
}
