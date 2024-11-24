#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include <windows.h>
#include "Food.h"

using namespace std;

//Note: This is not part of the project and only serves to make the game more playable. Please disregard
void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_CURSOR_INFO cursorInfo;

    // Get the current cursor info
    if (GetConsoleCursorInfo(hConsole, &cursorInfo)) {
        cursorInfo.bVisible = FALSE; 
        SetConsoleCursorInfo(hConsole, &cursorInfo);    
    } else {
        printf("Failed to get console cursor info.\n");
    }
}


#define DELAY_CONST 50000

GameMechs *gamemechanics = new GameMechs();
Player playercharacter(gamemechanics); 



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!gamemechanics->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
    //ShowCursor(true);
}


void Initialize(void)
{
    gamemechanics->setExit(false);
    HideCursor();

    gamemechanics->getFood();

    gamemechanics->getFood()->generateFoodBucket(playercharacter.getPlayerPos()->getHeadElement(), gamemechanics->getBoardSizeX(), gamemechanics->getBoardSizeY());
    //ShowCursor(false);

    MacUILib_init();   

}

void GetInput(void)
{
   if(MacUILib_hasChar())
   {
        gamemechanics->setInput(MacUILib_getChar());
   }

   else
   {
        gamemechanics->clearInput();
   }
}

void RunLogic(void)
{
    
    bool eatFood = false;
    

    for(int j = 0; j<gamemechanics->getFood()->getAmountOfFood(); j++)
    {
        if(playercharacter.checkFoodCollision(j) == true)
        {
            objPos tempFoodItem;
            gamemechanics->getFood()->generateFood(playercharacter.getPlayerPos()->getHeadElement(), &tempFoodItem, gamemechanics->getBoardSizeX(), gamemechanics->getBoardSizeY());
            gamemechanics->getFood()->getFoodBucket()->setElement(j, tempFoodItem);

            eatFood = true;
            break;
        }
    }
    

    if(gamemechanics->getInput() == ' ')
    {
        gamemechanics->setExit(true);
        gamemechanics->setLoseFlag();
    }

    if(eatFood == true)
    {
        gamemechanics->incrementScore();
        objPos newPosition;

        if(playercharacter.getPlayerDir() == Player::RIGHT)
        {
            newPosition.pos->x = playercharacter.getPlayerPos()->getHeadElement().pos->x + 1;
            newPosition.pos->y = playercharacter.getPlayerPos()->getHeadElement().pos->y;
            newPosition.symbol = '*';
        }

        else if(playercharacter.getPlayerDir() == Player::LEFT)
        {
            newPosition.pos->x = playercharacter.getPlayerPos()->getHeadElement().pos->x - 1;
            newPosition.pos->y = playercharacter.getPlayerPos()->getHeadElement().pos->y;
            newPosition.symbol = '*';
        }

        else if(playercharacter.getPlayerDir() == Player::UP|| playercharacter.getPlayerDir() == Player::STOP)
        {
            newPosition.pos->x = playercharacter.getPlayerPos()->getHeadElement().pos->x;
            newPosition.pos->y = playercharacter.getPlayerPos()->getHeadElement().pos->y-1;
            newPosition.symbol = '*';
        }

        else if(playercharacter.getPlayerDir() == Player::DOWN)
        {
            newPosition.pos->x = playercharacter.getPlayerPos()->getHeadElement().pos->x;
            newPosition.pos->y = playercharacter.getPlayerPos()->getHeadElement().pos->y+1;
            newPosition.symbol = '*';
        }

        playercharacter.getPlayerPos()->insertHead(newPosition);
    }

    if(gamemechanics->getInput() != 0 && gamemechanics->getInput() != ' ')
    {
        playercharacter.updatePlayerDir();
    }
    
    
    playercharacter.movePlayer();
    gamemechanics->clearInput(); 

    if(playercharacter.checkSelfCollision() == true)
    {
        gamemechanics->setExit(true);
        gamemechanics->setLoseFlag();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    int boardSizeY = gamemechanics->getBoardSizeY();
    int boardSizeX = gamemechanics->getBoardSizeX();
    bool object_printed = false;
    

    MacUILib_printf("\nUse the WASD Keys to navigate and spacebar to exit\n");
    
    if(playercharacter.getPlayerDir() == Player::STOP)
    {
        MacUILib_printf("Click any WASD key to start\n");
    }

    for(int y = 0; y<boardSizeY; y++)
    {
        for(int x = 0; x<boardSizeX; x++)
        {
            object_printed = false; 
            
            if((y==0||x==0||x==(boardSizeX-1)||y==(boardSizeY-1)) && !object_printed)
            {
                MacUILib_printf("#");
                continue;
            }

                       
            else
            {
                for(int j = 0; j<playercharacter.getPlayerPos()->getSize(); j++)
                {
                    if((playercharacter.getPlayerPos()->getElement(j).pos->x == x) && (playercharacter.getPlayerPos()->getElement(j).pos->y == y))
                    {
                        MacUILib_printf("%c",playercharacter.getPlayerPos()->getElement(j).getSymbol());
                        object_printed = true; 

                    }
                }
            
                for(int m = 0; m<gamemechanics->getFood()->getAmountOfFood(); m++)
                {
                    
                    if(gamemechanics->getFoodPosition(m).pos->x == x && gamemechanics->getFoodPosition(m).pos->y == y)
                    {
                        MacUILib_printf("$");
                        object_printed = true;
                    }
                }

                if(!object_printed)
                    MacUILib_printf(" ");
            }
        }

        MacUILib_printf("\n");
        
    }

    MacUILib_printf("\nCurrent Score: %d", gamemechanics->getScore());
      

    if(gamemechanics->getExitFlagStatus() == true && gamemechanics->getLoseFlagStatus() == false)
    {
        MacUILib_printf("\nCongratulations on Winning!");
    }

    else if(gamemechanics->getExitFlagStatus() == true && gamemechanics->getLoseFlagStatus() == true)
    {
        MacUILib_printf("\nCongratulations on Losing!");
    }

    else if(gamemechanics->getExitFlagStatus() == false && gamemechanics->getLoseFlagStatus() == true)
    {
        MacUILib_printf("\nHow did you get here?!");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{  

    MacUILib_uninit();
    delete gamemechanics;
}
