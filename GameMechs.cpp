#include "GameMechs.h"
#include "MacUILib.h"



GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    winFlag = false;
    foodObject = new Food(); 
    diff = Start;
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    winFlag = false;
    foodObject = new Food(); 
    diff = Start;

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

bool GameMechs::getWinFlagStatus() const
{   
    return winFlag;
}
    
char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore(int scoreAdd)
{
    score+=scoreAdd;
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

void GameMechs::setDifficulty()
{
    if(diff == Start)
    {
        if(input == 49)
        {
            diff = Easy;
        }
        else if(input == 50)
        {
            diff = Medium;
        }
        else if(input == 51)
        {
            diff = Hard;
        }
        else if(input == 52)
        {
            diff = Impossible;
        }
    }
}

GameMechs::Difficulty GameMechs::getDifficulty()
{
    return diff;
}

// More methods should be added here