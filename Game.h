#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "Snake.h"
#include "Collectable.h"
#include "Sun.h"
#include "Planets.h"

#include "PlayerSnake.h"
#include "AISnake.h"

class Game
{
public:
    Game();
    ~Game();

    void Run();
    bool IsPositionOccupied(Collectable& c);
    void DisplayTimer(sf::RenderWindow& window);
    void WinDetection();

private:
    //Create dimensions of window
    int m_screenWidth{800};
    int m_screenHeight{600};

    //Create clocks for delays and timer for game mechanic
    sf::Clock clock;
    sf::Clock timerClock;

    //Create instances of the child classes
    //One player snake and one AI snake
    PlayerSnake *player1;
    AISnake *computerPlayer;

    //Create vectors to hold snakes, use pointers as different types of child classes
    std::vector<Snake*> m_snakes;

    Collectable m_collectables[5];
    Sun m_sun;
    std::vector<Planets> m_planets;

    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text
    sf::RenderWindow m_window;
};

#endif // GAME_H
