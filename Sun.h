#ifndef SUN_H
#define SUN_H

#include <SFML/Graphics.hpp>


class Sun
{
public:
    Sun();
    ~Sun();

    //Functions for getting position and size
    sf::Vector2f GetPosition();
    float GetSize();

    void Render(sf::RenderWindow& window);

private:
    float m_size{20.0f};
    sf::CircleShape m_sun{m_size};
    sf::Vector2f m_position{0, 0};

    //Variables for screen dimensions
    int m_screenWidth{800};
    int m_screenHeight{600};
};

#endif // SUN_H
