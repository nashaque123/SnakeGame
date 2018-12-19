#include "Game.h"

Game::Game(): m_window(sf::VideoMode(m_screenWidth, m_screenHeight), "C++ Snake ICA : S6061420")
{
    //ctor
    //Add snakes to vector
    player1 = new PlayerSnake("Player1");
    computerPlayer = new AISnake("Player2");

    m_snakes.push_back(player1);
    m_snakes.push_back(computerPlayer);
}

Game::~Game()
{
    //dtor
    //Delete snakes in destructor to ensure no dangling pointers
    delete player1;
    delete computerPlayer;
    player1 = NULL;
    computerPlayer = NULL;
}

void Game::Run()
{
    srand(time(NULL));

    m_planets.push_back(Planets(-80));
    m_planets.push_back(Planets(130));


    // We can still output to the console window
    std::cout << "Starting" << std::endl;



    // Main loop that continues until we call Close()
    while (m_window.isOpen())
    {
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                //Player can change direction as long as they aren't facing the opposite direction
                case sf::Keyboard::Left:
                    if (m_snakes[0]->GetDirection() != EDirection::eEast)
                        m_snakes[0]->ChangeDirectionVariable(EDirection::eWest);
                    break;
                case sf::Keyboard::Right:
                    if (m_snakes[0]->GetDirection() != EDirection::eWest)
                        m_snakes[0]->ChangeDirectionVariable(EDirection::eEast);
                    break;
                case sf::Keyboard::Up:
                    if (m_snakes[0]->GetDirection() != EDirection::eSouth)
                        m_snakes[0]->ChangeDirectionVariable(EDirection::eNorth);
                    break;
                case sf::Keyboard::Down:
                    if (m_snakes[0]->GetDirection() != EDirection::eNorth)
                        m_snakes[0]->ChangeDirectionVariable(EDirection::eSouth);
                    break;
                //Code for a potential second human player if altered
                /*case sf::Keyboard::A:
                if (m_snakes[1].GetDirection() != EDirection::eEast)
                    m_snakes[1].ChangeDirectionVariable(EDirection::eWest);
                    break;
                case sf::Keyboard::D:
                if (m_snakes[1].GetDirection() != EDirection::eWest)
                    m_snakes[1].ChangeDirectionVariable(EDirection::eEast);
                    break;
                case sf::Keyboard::W:
                if (m_snakes[1].GetDirection() != EDirection::eSouth)
                    m_snakes[1].ChangeDirectionVariable(EDirection::eNorth);
                    break;
                case sf::Keyboard::S:
                if (m_snakes[1].GetDirection() != EDirection::eNorth)
                    m_snakes[1].ChangeDirectionVariable(EDirection::eSouth);
                    break;*/
                default:
                    break;
                }
            default:
                break;
            }
        }

        //Call the move functions for the snakes and check if they want to change directions
        for(auto& s : m_snakes)
        {
            s->Move();
            s->PlayerAltersDirection();
        }

        //check for collisions between snakes - as long as it's not checking itself
        for (size_t i = 0; i < m_snakes.size(); i++)
        {
            for (size_t j = 0; j < m_snakes.size(); j++)
            {

                if (i != j && m_snakes[i]->OtherSnakeCollisionCheck(*m_snakes[j]))
                    m_snakes[i]->Death();
            }
        }

        // We must clear the window each time round the loop
        m_window.clear();

        //Check all other collisions for the snakes
        for(auto& s : m_snakes)
        {
            s->CollectableCollisionCheck(m_collectables);
            s->WallCollisionCheck();
            s->SunCollisionCheck(m_sun);

            for(Planets& p : m_planets)
            {
                s->PlanetCollisionCheck(p);
                s->SegmentPlanetCollisionCheck(p);
            }

            if (s->SelfCollisionCheck())
                s->Death();

            if (!s->GetAliveStatus())
                m_window.close();
        }

        //Spawn the collectable if the position is not already occupied
        for(Collectable& c : m_collectables)
        {
            c.IsAlive();

            while (IsPositionOccupied(c))
                c.Spawn();
        }

        for(Planets& p : m_planets)
        {
            p.Move(m_sun);
        }

        //Check if the game is over and display the timer
        WinDetection();
        DisplayTimer(m_window);

        for(Collectable& c : m_collectables)
        {
            c.Render(m_window);
        }

        for(Planets& p : m_planets)
        {
            p.Render(m_window);
        }

        for(auto& s : m_snakes)
        {
            s->Render(m_window);
            s->DisplayScore(m_window);
        }

        m_sun.Render(m_window);

        // Get the window to display its contents
        m_window.display();
    }
    std::cout << "Finished" << std::endl;
}

//Function to check if position is occupied before spawning the collectable
bool Game::IsPositionOccupied(Collectable& c)
{

    //Compare collectables to snake positions
    for (unsigned int j = 0; j < m_snakes.size(); j++)
    {
        if (m_snakes[j]->SegmentCollisionCheck(c.GetPosition()))
            return true;
    }

    //Compare against other collectables
    for (int j = 0; j < 5; j++)
    {
        if (&c != &m_collectables[j] && c.GetPosition() == m_collectables[j].GetPosition())
            return true;
    }

    //Compare against the sun's position
    {
        sf::Vector2f getPosition = m_sun.GetPosition();
        int result = sqrt(((c.GetPosition().x - getPosition.x)*(c.GetPosition().x - getPosition.x)) + ((c.GetPosition().y - getPosition.y)*(c.GetPosition().y - getPosition.y)));
        if(result < c.GetSize() + m_sun.GetSize())
            return true;
    }

    //Compare against planets, however can be problematic as planets move position constantly
    /* for (int j = 0; j < m_planets.size(); j++)
     {
         sf::Vector2f getPosition = m_planets[j].GetPosition();
         int result = sqrt(((c.GetPosition().x - getPosition.x)*(c.GetPosition().x - getPosition.x)) + ((c.GetPosition().y - getPosition.y)*(c.GetPosition().y - getPosition.y)));
         if(result < c.GetSize() + m_planets[j].GetSize())
             return true;
     }*/

    return false;
}

//Function to display a timer counting down from 90
void Game::DisplayTimer(sf::RenderWindow& window)
{
    int m_time = timerClock.getElapsedTime().asSeconds();
    int m_timeRemaining = 90 - m_time;

    sf::Text text;
    sf::Font font;

    font.loadFromFile("OpenSans-Semibold.ttf");

    text.setFont(font);

    text.setString("Time remaining: " + std::to_string(m_timeRemaining));
    text.setCharacterSize(15);
    text.setColor(sf::Color::Magenta);
    text.move({330, 30});

    //Check who wins the game if the time runs out
    if (m_timeRemaining <= 0)
    {
        std::cout << "Time's up!\n";
        std::cout << "The final score was\n";
        std::cout << "Player: " << m_snakes[0]->GetFinalScore() << " - " << m_snakes[1]->GetFinalScore() << " :Computer" << std::endl;

        if (m_snakes[0]->GetFinalScore() > m_snakes[1]->GetFinalScore())
            std::cout << "You win!" << std::endl;
        else if (m_snakes[0]->GetFinalScore() < m_snakes[1]->GetFinalScore())
            std::cout << "You lose!"<< std::endl;
        else
            std::cout << "It's a draw!" << std::endl;

        m_window.close();
    }

    window.draw(text);
}

//Checks whether any snakes have died and outputs who wins
void Game::WinDetection()
{
    if (!(m_snakes[0]->GetAliveStatus()) && m_snakes[1]->GetAliveStatus())
    {
        std::cout << "You died!\n";
        std::cout << "The computer wins!\n";
    }
    else if (m_snakes[0]->GetAliveStatus() && !(m_snakes[1]->GetAliveStatus()))
    {
        std::cout << "The computer died!\n";
        std::cout << "You win!\n";
    }
    else if (!(m_snakes[0]->GetAliveStatus()) && !(m_snakes[1]->GetAliveStatus()))
    {
        std::cout << "Both players died!\n";
        std::cout << "The final score was\n";
        std::cout << "Player: " << m_snakes[0]->GetFinalScore() << " - " << m_snakes[1]->GetFinalScore() << " :Computer" << std::endl;

        if (m_snakes[0]->GetFinalScore() > m_snakes[1]->GetFinalScore())
            std::cout << "You win!" << std::endl;
        else if (m_snakes[0]->GetFinalScore() < m_snakes[1]->GetFinalScore())
            std::cout << "You lose!"<< std::endl;
        else
            std::cout << "It's a draw!" << std::endl;

        m_window.close();
    }
}
