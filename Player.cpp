#include "Player.h"
//Merge test two

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    // [COPY AND PASTE FROM PPA2] Copy your main logic routine from PPA2 and paste them below

    //Checking if the player has moved
    if(player_move != 0)
    {
        //Switch cases depending on input given
        switch(player_move)
        {                      
            case 'w':
            case 'W':
                if (myDir == LEFT||myDir == RIGHT||myDir == STOP)
                    myDir = UP;
                    break;
                
            case 's':
            case 'S':
                if (myDir == LEFT||myDir == RIGHT||myDir == STOP)
                    myDir = DOWN;
                    break;
                
            case 'a':
            case 'A':
                if (myDir == UP||myDir == DOWN||myDir == STOP)
                    myDir = LEFT;
                    break;

            case 'd':
            case 'D':
                if (myDir == UP||myDir == DOWN||myDir == STOP)
                    myDir = RIGHT;
                    break;

            default:
                break;    
                // Add more key processing here
                // Add more key processing here
                // Add more key processing here    
        }
        player_move = 0;
    }    
}     


void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added