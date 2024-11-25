#include "GameMechs.h"
#include "MacUILib.h"



GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    foodObject = new Food(); 
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    foodObject = new Food(); 

    //Defining board

}

// do you need a destructor?
GameMechs::~GameMechs()
{
    delete foodObject;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}


void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


objPos GameMechs::getFoodPosition(int i)
{
    return foodObject->getFoodBucket()->getElement(i);
}


Food* GameMechs::getFood()
{
    return foodObject;
}

void GameMechs::setExit(bool value)
{
    if(value)
        exitFlag = true;
    
    else if(!value)
        exitFlag = false;
    
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

// More methods should be added here