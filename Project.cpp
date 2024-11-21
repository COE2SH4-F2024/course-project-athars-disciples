#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 50000

GameMechs gamemechanics = GameMechs(30, 30);
Player playercharacter(&gamemechanics); 


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!gamemechanics.getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    gamemechanics.setExit(false);
    playercharacter.setSymbol('@');

    MacUILib_init();   

}

void GetInput(void)
{
   if(MacUILib_hasChar())
   {
        gamemechanics.setInput(MacUILib_getChar());
   }

   else
   {
        gamemechanics.clearInput();
   }
}

void RunLogic(void)
{
    
    if(gamemechanics.getInput() == ' ')
    {
        gamemechanics.setExit(true);
        gamemechanics.setLoseFlag();
    }

    if(gamemechanics.getInput() != 0 && gamemechanics.getInput() != ' ')
    {
        playercharacter.updatePlayerDir();
    }
    
    
    playercharacter.movePlayer();
    gamemechanics.clearInput(); 

}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    int boardSizeY = gamemechanics.getBoardSizeY();
    int boardSizeX = gamemechanics.getBoardSizeX();
    int player_x = playercharacter.getPlayerPos().pos->x;
    int player_y = playercharacter.getPlayerPos().pos->y;
    char symbol = playercharacter.getSymbol();
    

    for(int y = 0; y<boardSizeY; y++)
    {
        for(int x = 0; x<boardSizeX; x++)
        {
            
            if(x == player_x && y == player_y)
            {
                MacUILib_printf("%c", symbol);
            }
            
            else if(y==0||x==0||x==(boardSizeX-1)||y==(boardSizeY-1))
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
      

    if(gamemechanics.getExitFlagStatus() == true && gamemechanics.getLoseFlagStatus() == false)
    {
        MacUILib_printf("Congratulations on Winning!");
    }

    else if(gamemechanics.getExitFlagStatus() == true && gamemechanics.getLoseFlagStatus() == true)
    {
        MacUILib_printf("Congratulations on Losing!");
    }

    else if(gamemechanics.getExitFlagStatus() == false && gamemechanics.getLoseFlagStatus() == true)
    {
        MacUILib_printf("How did you get here?!");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{  

    MacUILib_uninit();
}
