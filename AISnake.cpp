#include "AISnake.h"
#include <iostream>

AISnake::AISnake(std::string name) : Snake(name)
{
    //ctor
    //Randomise position in the region of the bottom right corner
    m_position.x = rand() % 50 + 660;
    m_position.y = rand() % 50 + 460;

    //Align the position to a grid to make collisions easier
    m_xAligned = m_position.x / (m_movementStep * 2);
    m_xAligned *= (m_movementStep * 2);
    m_yAligned = m_position.y / (m_movementStep * 2);
    m_yAligned *= (m_movementStep * 2);

    m_position.x = m_xAligned;
    m_position.y = m_yAligned;

    m_snakeSegments.push_front(m_position);

    circle.setFillColor(sf::Color::White);

    //Set origin to center of snake
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}

AISnake::~AISnake()
{
    //dtor
}

//Changes direction
void AISnake::PlayerAltersDirection()
{
    //1 in 10 chance of randomly changing direction
    int randomDirection{0};

    if (rand() % 10 == 0)
    {
        randomDirection = rand() % 4;

        switch(randomDirection)
        {
        //change direction as long as they aren't facing the opposite direction
        case 0:
            if (GetDirection() != EDirection::eEast)
                ChangeDirectionVariable(EDirection::eWest);
            break;
        case 1:
            if (GetDirection() != EDirection::eWest)
                ChangeDirectionVariable(EDirection::eEast);
            break;
        case 2:
            if (GetDirection() != EDirection::eSouth)
                ChangeDirectionVariable(EDirection::eNorth);
            break;
        case 3:
            if (GetDirection() != EDirection::eNorth)
                ChangeDirectionVariable(EDirection::eSouth);
            break;
        default:
            break;
        }
    }

    //Turn around if about to collide with wall boundary
    if (m_position.x - (m_movementStep * 4) < 18)
    {
        ChangeDirectionVariable(EDirection(EDirection::eSouth));
        Move();
        ChangeDirectionVariable(EDirection(EDirection::eEast));
    }
    else if (m_position.x + (m_movementStep * 4) > 782)
    {
        ChangeDirectionVariable(EDirection(EDirection::eNorth));
        Move();
        ChangeDirectionVariable(EDirection(EDirection::eWest));
    }
    else if (m_position.y - (m_movementStep * 4) < 18)
    {
        ChangeDirectionVariable(EDirection(EDirection::eWest));
        Move();
        ChangeDirectionVariable(EDirection(EDirection::eSouth));
    }
    else if (m_position.y + (m_movementStep * 4) > 582)
    {
        ChangeDirectionVariable(EDirection(EDirection::eEast));
        Move();
        ChangeDirectionVariable(EDirection(EDirection::eNorth));
    }

//    //Avoid the sun - Not properly working!
//    if (m_position.x - (m_movementStep * 2) > 380  && m_position.y > 280 && m_position.y < 320)
//        ChangeDirectionVariable(EDirection(EDirection::eSouth));
//    else if (m_position.x + (m_movementStep * 2) < 420  && m_position.y > 280 && m_position.y < 320)
//        ChangeDirectionVariable(EDirection(EDirection::eNorth));
//    else if (m_position.y - (m_movementStep * 2) > 280  && m_position.x > 380 && m_position.y < 420)
//        ChangeDirectionVariable(EDirection(EDirection::eWest));
//    else if (m_position.y + (m_movementStep * 2) < 320  && m_position.x > 380 && m_position.y < 420)
//        ChangeDirectionVariable(EDirection(EDirection::eEast));
}
