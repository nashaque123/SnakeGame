#ifndef PLAYERSNAKE_H
#define PLAYERSNAKE_H

#include "Snake.h"

class PlayerSnake : public Snake
{
public:
    PlayerSnake(std::string name);
    virtual ~PlayerSnake();

    //Function to override the base classes function
    void PlayerAltersDirection() override;
};

#endif // PLAYERSNAKE_H
