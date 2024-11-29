#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include <windows.h>

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
    //ShowCursor(true);
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

    //Setting a boolean value checking whether the snake ate food to false initially
    int index = 0;

    //Checking every food object within the foodbuckets position against every player object position
    

    //Section where necessary changes are made depending on eatFood condition
    if((playercharacter.checkFoodCollision()) && (playercharacter.getPlayerDir() != Player::STOP))
    {
        index = playercharacter.getFoodIndex();
        //Incrementing the score to account for player capturing food
        switch(gamemechanics->getFood()->getFoodBucket()->getElement(index).symbol)
        {
            case 'A':
                gamemechanics->incrementScore(10);
                break;
            case 'B':
                gamemechanics->incrementScore(20);
                break;
            case 'C':
                gamemechanics->incrementScore(30);
                break;
            case 'D':
                gamemechanics->incrementScore(-30);
                break;

            default:
                break;
        }

        //Regenerating the foodbucket depending on the new player object positions
        objPosArrayList temp = *(playercharacter.getPlayerPos());
        gamemechanics->getFood()->generateFoodBucket(temp, gamemechanics->getBoardSizeX(), gamemechanics->getBoardSizeY());

        //Defining a temporary new object position  
        objPos newPosition;

        //Checking if the current direction of the player character is right
        if(playercharacter.getPlayerDir() == Player::RIGHT)
        {
            //Changing the new positions x and y variables to match the existing direction and increase in direction of food eaten
            newPosition.pos->x = playercharacter.getPlayerPos()->getHeadElement().pos->x + 1;
            newPosition.pos->y = playercharacter.getPlayerPos()->getHeadElement().pos->y;
            newPosition.symbol = '>';
        }

        //Checking if the current direction of the player character is left
        else if(playercharacter.getPlayerDir() == Player::LEFT)
        {
            //Changing the new positions x and y variables to match the existing direction and increase in direction of food eaten
            newPosition.pos->x = playercharacter.getPlayerPos()->getHeadElement().pos->x - 1;
            newPosition.pos->y = playercharacter.getPlayerPos()->getHeadElement().pos->y;
            newPosition.symbol = '<';
        }

        //Checking if the current direction of the player character is up or stop (player is assumed to be pointing up at beginning)
        else if(playercharacter.getPlayerDir() == Player::UP|| playercharacter.getPlayerDir() == Player::STOP)
        {
            //Changing the new positions x and y variables to match the existing direction and increase in direction of food eaten
            newPosition.pos->x = playercharacter.getPlayerPos()->getHeadElement().pos->x;
            newPosition.pos->y = playercharacter.getPlayerPos()->getHeadElement().pos->y-1;
            newPosition.symbol = '^';
        }

        //Checking if the current direction of the player character is down
        else if(playercharacter.getPlayerDir() == Player::DOWN)
        {
            //Changing the new positions x and y variables to match the existing direction and increase in direction of food eaten
            newPosition.pos->x = playercharacter.getPlayerPos()->getHeadElement().pos->x;
            newPosition.pos->y = playercharacter.getPlayerPos()->getHeadElement().pos->y+1;
            newPosition.symbol = '@';
        }

        //Insearting a new head using the new parameters stored in the newPosition objPos 
        playercharacter.getPlayerPos()->insertHead(newPosition);

    }
    //Checking if the input is not null or spacebar (no need to update direction if nothing new is inputted or when exiting)
    if(gamemechanics->getInput() != 0)
    {
        playercharacter.updatePlayerDir();
    }
    
    //Moving the player as necessary and as dictated by the movePlayer function
    playercharacter.movePlayer();

    //Clearing the old input as it is no longer needed
    gamemechanics->clearInput(); 

    //Checking if the player collided with itself
    if(playercharacter.checkSelfCollision() == true)
    {
        //Setting the exit flag and loseFlag to true within gamemechanics if self collision is detected
        gamemechanics->setExit(true);
        gamemechanics->setLoseFlag();

        //Removing the head so that the board does not attempt to print two parts of the body on the same position
        playercharacter.getPlayerPos()->removeHead();
    }
}

void DrawScreen(void)
{ 
    //Initially clearing the previous scr

    //Storing the variables of 
    int boardSizeY = gamemechanics->getBoardSizeY();
    int boardSizeX = gamemechanics->getBoardSizeX();
    bool object_printed = false;
    bool temp = false;
    int var = 0;
    
    MacUILib_printf("               𝓨𝓸𝓾𝓼𝓼𝓮𝓯'𝓼 𝓢𝓷𝓪𝓴𝓮 𝓖𝓪𝓶𝓮\n");
    MacUILib_printf("        _________________________________\n\n");

    MacUILib_printf("\nUse the WASD Keys to navigate and spacebar to exit\n");
    
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
                        MacUILib_printf("%2c", '@');
                        object_printed = true; 

                    }
                }
                
                if(!playercharacter.checkFoodCollision() && !playercharacter.checkSelfCollision())
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

                if(!object_printed)
                    MacUILib_printf("%2c", ' ');
            }
        }

        MacUILib_printf("\n");
        

    }

    MacUILib_printf("\nCurrent Score: %d", gamemechanics->getScore());
    MacUILib_printf("\nFood Guide:\n🍎 = 10 points\n🍐 = 20 points\n🍒 = 30 points\n🔥 = -30 points\n");

    if(gamemechanics->getExitFlagStatus() == true && gamemechanics->getLoseFlagStatus() == false)
    {
        MacUILib_printf("\nCongratulations on Winning!");
    }

    else if(gamemechanics->getExitFlagStatus() == true && gamemechanics->getLoseFlagStatus() == true)
    {
        MacUILib_printf("\nCongratulations on Losing!");

    }


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{  

    MacUILib_uninit();
    delete[] gamemechanics;
}
