#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include <windows.h>

using namespace std;

//Note: This is not part of the project and only serves to make the game more playable (by removing the flashing cursor). Please disregard
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



//Defining delay constant (time between frames)
#define DELAY_CONST 100000



//Initializing gamemechanics pointer and allocating memory for it
GameMechs *gamemechanics = new GameMechs;

//Initializing player character which takes in the gamemechanics pointer as reference
Player playercharacter(gamemechanics); 



//Function headers 
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


    
int main(void)
{
    //Allows for use of non-ascii characters
    SetConsoleOutputCP(CP_UTF8);

    //Initializing necessary items prior to main loop
    Initialize();

    //Checking if the exit flag within gamemechanics has been triggered
    while(!gamemechanics->getExitFlagStatus())  
    {
        //Running primary loop
        MacUILib_clearScreen(); 
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    //Cleaning up screen once game is over
    CleanUp();
}


void Initialize(void)
{
    HideCursor();

    //Ensuring that any randomized item positions within the game are truly randomized
    srand(time(NULL));

    //Setting exit to false (while it is already initialized in gamemechanics, this just ensures it is false)
    gamemechanics->setExit(false);

    //Generating initial food positions within 'foodbucket' by utilizing the players existing position as a blockoff
    gamemechanics->getFood()->generateFoodBucket(*(playercharacter.getPlayerPos()), gamemechanics->getBoardSizeX(), gamemechanics->getBoardSizeY());


    //Checking if initialized spawn position already defined is within the gameboard parameters
    if(playercharacter.getPlayerPos()->getHeadElement().pos->x > gamemechanics->getBoardSizeX() 
    || playercharacter.getPlayerPos()->getHeadElement().pos->x > gamemechanics->getBoardSizeX())
    {
        //Changing parameters to be within game parameters should the above be true
        playercharacter.getPlayerPos()->getHeadElement().pos->x = (gamemechanics->getBoardSizeX())/2;
        playercharacter.getPlayerPos()->getHeadElement().pos->y = (gamemechanics->getBoardSizeY())/2;

    }

    MacUILib_init();   

}

void GetInput(void)
{
    
    //Checking if a character has been inputted within this loop
   if(MacUILib_hasChar())
   {
        //Setting the input within gamemechanics to the input
        gamemechanics->setInput(MacUILib_getChar());
        
   }

   else
   {
        //Setting input to null if nothing has been inputted 
        gamemechanics->clearInput();
   }
}


void RunLogic(void)
{

    //Setting the difficulty if not set
    gamemechanics->setDifficulty();

    //Checking if the input is not null or spacebar (no need to update direction if nothing new is inputted or when exiting)
    playercharacter.updatePlayerDir();
    
    //Moving the player as necessary and as dictated by the movePlayer function
    playercharacter.movePlayer();

    //Clearing the old input as it is no longer needed
    gamemechanics->clearInput(); 


}

void DrawScreen(void)
{ 

    //Storing the variables of the gameboard dimensions, object printing details, 
    int boardSizeY = gamemechanics->getBoardSizeY();
    int boardSizeX = gamemechanics->getBoardSizeX();
    bool object_printed = false;
    playercharacter.checkFoodCollision();
    bool foodCollide = playercharacter.checkFoodCollision();
    

    //Writing out initial text
    MacUILib_printf("\t\t\t𝓢𝓷𝓪𝓴𝓮 𝓖𝓪𝓶𝓮\n");
    MacUILib_printf("\t\t_________________________________\n\n");


    if(gamemechanics->getDifficulty() == GameMechs::Start)
    {
        MacUILib_printf("Choose your difficulty (Press the corrosponding number on your keyboard):\n");
        MacUILib_printf("1. Easy Mode: Win at 200 points\n");
        MacUILib_printf("2. Medium Mode: Win at 500 points\n");
        MacUILib_printf("3. Hard Mode: Win at 1000 points\n");
        MacUILib_printf("4. Impossible Mode: Win once you fill the board\n");
    }

    //Displaying game once difficulty has been properly set
    if(gamemechanics->getDifficulty() != GameMechs::Start)
    {
        MacUILib_printf("\nUse the WASD Keys to navigate and spacebar to exit\n\n");

        //Giving cue to player to begin by pressing WASD    
        if(playercharacter.getPlayerDir() == Player::STOP)
        {
            MacUILib_printf("\nClick any WASD key to start\n\n");
        }
        
        for(int y = 0; y<boardSizeY; y++)
        {
            for(int x = 0; x<boardSizeX; x++)
            {
                object_printed = false; 

                if((y==0||x==0||x==(boardSizeX-1)||y==(boardSizeY-1)) && !object_printed)
                {
                    MacUILib_printf("██");
                }
                        
                else
                {    
                    for(int j = 0; j<playercharacter.getPlayerPos()->getSize(); j++)
                    {
                        if((playercharacter.getPlayerPos()->getElement(j).pos->x == x) && (playercharacter.getPlayerPos()->getElement(j).pos->y == y))
                        {
                            if(playercharacter.getPlayerPos()->getElement(j).symbol == '~')
                            {
                                MacUILib_printf("🡳");
                            }

                            else if(playercharacter.getPlayerPos()->getElement(j).symbol == '>')
                            {
                                MacUILib_printf("🡲");
                            }

                            else if(playercharacter.getPlayerPos()->getElement(j).symbol == '<')
                            {
                                MacUILib_printf("🡰");
                            }

                            else if(playercharacter.getPlayerPos()->getElement(j).symbol == '^')
                            {
                                MacUILib_printf("🡱");
                            }

                            else if(playercharacter.getPlayerPos()->getElement(j).symbol == '*')
                            {
                                MacUILib_printf("⚪");
                            }
                                

                            object_printed = true; 

                        }
                    }
                    
                    if(!foodCollide && !playercharacter.checkSelfCollision())
                    {
                        for(int m = 0; m<gamemechanics->getFood()->getAmountOfFood(); m++)
                        {
                            
                            if(gamemechanics->getFood()->getFoodBucket()->getElement(m).pos->x == x && gamemechanics->getFoodPosition(m).pos->y == y)
                            {

                                if(gamemechanics->getFoodPosition(m).symbol == 'A')
                                {
                                    MacUILib_printf("🍎"); 
                                    object_printed = true;
                                    break;
                                }

                                else if(gamemechanics->getFoodPosition(m).symbol == 'B')
                                {
                                    MacUILib_printf("🍐"); 
                                    object_printed = true;
                                    break;
                                }

                                else if(gamemechanics->getFoodPosition(m).symbol == 'C')
                                {
                                    MacUILib_printf("🍒"); 
                                    object_printed = true;
                                    break;
                                }

                                else if(gamemechanics->getFoodPosition(m).symbol == 'D')
                                {
                                    MacUILib_printf("🔥"); 
                                    object_printed = true;
                                    break;
                                }
                            }
                        }
                    }

                    //If no object is printed, it will print a space
                    if(!object_printed)
                        MacUILib_printf("%2c", ' ');
                }
            }

            //Goes to new line after row completed
            MacUILib_printf("\n");
            

        }
    }

    //Displays Current Score
    MacUILib_printf("\nCurrent Score: %d", gamemechanics->getScore());
    MacUILib_printf("\nCurrent Size: %d", playercharacter.getPlayerPos()->getSize());

    //Displays guide to how items work
    MacUILib_printf("\nFood Guide:\n🍎 = 10 points, Size Increase by 1\n🍐 = 20 points, Size Increase by 2\n🍒 = 30 points, No Size Increase\n🔥 = -30 points, Size Decrease by 3\n");


    //Checks if win condition is true and prints appropriate result
    if(playercharacter.checkWinCondition())
    {
        MacUILib_printf("\nCongratulations on Winning! Here is your reward: 🎂\n");
    }

    //Checks if lose condition is true and prints appropriate results
    else if(gamemechanics->getExitFlagStatus() == true && gamemechanics->getLoseFlagStatus() == true)
    {
        MacUILib_printf("\nCongratulations on Losing!\n");

    }

    else if(gamemechanics->getExitFlagStatus() == true && gamemechanics->getLoseFlagStatus() == false)
    {
        MacUILib_printf("\nThanks for Playing 😁\n");

    }




}

void LoopDelay(void)
{
    //Places delay between frames 
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{  

    MacUILib_uninit();

    //Freeing up memory allocated for gamemechanics
    delete[] gamemechanics;
}





//For all 5 of your elements 
//Is the elements position valid? 
//If yes, continue to the next element
//If no, randomize x and y and check again for the element