#ifndef AISNAKE_H
#define AISNAKE_H

#include "Snake.h"

class AISnake : public Snake
{
public:
    AISnake(std::string name);
    virtual ~AISnake();

    //Function to override the base classes function
    void PlayerAltersDirection() override;
};

#endif // AISNAKE_H
