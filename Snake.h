#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "Collectable.h"
#include "Sun.h"
#include "Planets.h"

enum class EDirection
{
    eNorth,
    eEast,
    eSouth,
    eWest,
    eNull
};

class Snake
{
public:
    Snake(std::string name);
    virtual ~Snake();

    //Prototypes for functions moving the snake
    void Move();
    void ChangeDirectionVariable(EDirection newDirection);

    //Pure function for the child classes to override
    virtual void PlayerAltersDirection() = 0;
    EDirection GetDirection();

    //Functions for checking collisions
    sf::Vector2f GetPosition();
    bool SegmentCollisionCheck(sf::Vector2f pos);
    void WallCollisionCheck();
    void CollectableCollisionCheck(Collectable m_collectables[]);
    bool OtherSnakeCollisionCheck(const Snake& other) const;
    bool SelfCollisionCheck() const;
    void SunCollisionCheck(Sun m_sun);
    void PlanetCollisionCheck(Planets m_planet);
    void SegmentPlanetCollisionCheck(Planets m_planet);

    //Functions handling death and win conditions
    void Death();
    bool GetAliveStatus();

    //Handle score and return it to the game class
    int GetFinalScore();
    void DisplayScore(sf::RenderWindow& window);

    void Render(sf::RenderWindow& window);

protected:
    std::string m_name;
    std::list <sf::Vector2f> m_snakeSegments;

    const float m_movementStep{9.0f};
    int m_growAmount{0};
    EDirection m_direction{EDirection::eNull};
    bool m_alive{true};

    // Create an instance of the SFML CircleShape and initialise it so radius is movementStep
    sf::CircleShape circle{m_movementStep};

    sf::Vector2f m_position{0, 0};
    int m_xAligned;
    int m_yAligned;

    int m_finalScore{0};
    sf::Text text;
    sf::Font font;
};

#endif // SNAKE_H
