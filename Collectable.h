#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>

class Collectable
{
public:
    Collectable();
    ~Collectable();

    //Functions of determining when and where to spawn
    bool IsAlive();
    void Spawn();
    void SetAliveToFalse();

    //Returning values for comparison in the game class
    sf::Vector2f GetPosition();
    int GetScore();
    float GetSize();

    void Render(sf::RenderWindow& window);

private:
    float m_size{9.0f};
    sf::CircleShape m_item{m_size};
    sf::Vector2f m_position{0, 0};

    int m_xAligned;
    int m_yAligned;

    int m_score;
    bool m_alive = false;
};

#endif // COLLECTABLE_H
