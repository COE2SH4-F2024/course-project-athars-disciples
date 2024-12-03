#include "GameMechs.h"
#include "MacUILib.h"


//Default constructor for GameMechs class
GameMechs::GameMechs()
{
    //Defining board size
    boardSizeX = 30;
    boardSizeY = 15;
    //Initilaizing game variables
    score = 0;
    exitFlag = false;
    loseFlag = false;
    winFlag = false;
    //Creating new food object
    foodObject = new Food(); 
    //Setting the difficulty
    diff = Start;  
}

//Parameterized constructor for GameMechs class
GameMechs::GameMechs(int boardX, int boardY)
{
    //Defining board
    boardSizeX = boardX;
    boardSizeY = boardY;
    //Initilaizing game variables
    score = 0;
    exitFlag = false;
    loseFlag = false;
    winFlag = false;
    //Creating new food object
    foodObject = new Food(); 
    //Setting the difficulty
    diff = Start;
}

//Destructor for GameMechs class
GameMechs::~GameMechs()
{
    delete foodObject;
}

//Getter for the exitFlag
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

//Getter for the loseFlag 
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

//Getter for the winFlag
bool GameMechs::getWinFlagStatus() const
{   
    return winFlag;
}
    
//Getter for the input
char GameMechs::getInput() const
{
    return input;
}

//Getter for the score
int GameMechs::getScore() const
{
    return score;
}

//Increment score by a number (scoreAdd)
void GameMechs::incrementScore(int scoreAdd)
{
    score+=scoreAdd;
}

//Getter for the X dimension
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

//Getter for the Y dimension
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

//Getter for foodPosition
objPos GameMechs::getFoodPosition(int i)
{
    return foodObject->getFoodBucket()->getElement(i);
}

//Getter for the foodObject
Food* GameMechs::getFood()
{
    return foodObject;
}

//Setting exitFlag to a value
void GameMechs::setExit(bool value)
{
    if(value)
        exitFlag = true;
    
    else if(!value)
        exitFlag = false;
    
}

//Setting loseFlag to true
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

//Setting input
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

//Clearing input
void GameMechs::clearInput()
{
    input = '\0';
}

//Updating difficulty based on the input
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

//Getter for diffulty
GameMechs::Difficulty GameMechs::getDifficulty()
{
    return diff;
}

