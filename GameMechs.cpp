#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    boardSizeX = 20;
    boardSizeY = 10;
    //Defining board
    for(int y = 0; y<boardSizeY; y++)
    {
        for(int x = 0; x<boardSizeX; x++)
        {
            
            /*if(x == position.x && y == position.y)
            {
                MacUILib_printf("%c", position.symbol);
            }
            */
            if(y==0||x==0||x==(boardSizeX-1)||y==(boardSizeY-1))
            {
                MacUILib_printf("#");
            }
           
            else
            {
                MacUILib_printf(" ");
            }

        }

        MacUILib_printf("\n");
        
    }
    MacUILib_clearScreen();    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    //Defining board
    for(int y = 0; y<boardSizeY; y++)
    {
        for(int x = 0; x<boardSizeX; x++)
        {
            
            /*if(x == position.x && y == position.y)
            {
                MacUILib_printf("%c", position.symbol);
            }
            */
            if(y==0||x==0||x==(boardSizeX-1)||y==(boardSizeY-1))
            {
                MacUILib_printf("#");
            }
           
            else
            {
                MacUILib_printf(" ");
            }

        }

        MacUILib_printf("\n");
        
    }
    MacUILib_clearScreen();    
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
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
    
}

int GameMechs::getBoardSizeX() const
{

}

int GameMechs::getBoardSizeY() const
{

}


void GameMechs::setExitTrue()
{

}

void GameMechs::setLoseFlag()
{
    
}

void GameMechs::setInput(char this_input)
{

}

void GameMechs::clearInput()
{

}

// More methods should be added here