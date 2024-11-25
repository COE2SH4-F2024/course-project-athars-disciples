#include "Player.h"
//Merge test two

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    
    playerPosList = new objPosArrayList();
    
    playerPosList->getHeadElement().pos->x = (mainGameMechsRef->getBoardSizeX())/2;
    playerPosList->getHeadElement().pos->y = (mainGameMechsRef->getBoardSizeY())/2;
    myDir = STOP;


    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
    delete[] playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPosList;
}


Player::Dir Player::getPlayerDir()
{
    return myDir;
}


void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    // [COPY AND PASTE FROM PPA2] Copy your main logic routine from PPA2 and paste them below
    //Checking if the player has moved
    char input = mainGameMechsRef->getInput();
    

    if(input != 0)
    {
        //Switch cases depending on input given
        switch(input)
        {                      
            case 'w':
            case 'W':
            //case 72:
                if (myDir == LEFT||myDir == RIGHT||myDir == STOP)
                    myDir = UP;
                    break;
                
            case 's':
            case 'S':
            //case 80:
                if (myDir == LEFT||myDir == RIGHT||myDir == STOP)
                    myDir = DOWN;
                    break;
                
            case 'a':
            case 'A':
            //case 75:
                if (myDir == UP||myDir == DOWN||myDir == STOP)
                    myDir = LEFT;
                    break;

            case 'd':
            case 'D':
            //case 77:
                if (myDir == UP||myDir == DOWN||myDir == STOP)
                    myDir = RIGHT;
                    break;
            

            default:
                break;    
        }

    }


}     


void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int upper_limit_x = mainGameMechsRef->getBoardSizeX();
    int upper_limit_y = mainGameMechsRef->getBoardSizeY();
    
    objPos newHeadPosition;
    newHeadPosition.pos->x = playerPosList->getHeadElement().pos->x;
    newHeadPosition.pos->y = playerPosList->getHeadElement().pos->y;

    switch(myDir)
    {
        case UP:
            --newHeadPosition.pos->y;
            if(newHeadPosition.pos->y<1)
            {
                newHeadPosition.pos->y = upper_limit_y-2;

            }
            playerPosList->insertHead(newHeadPosition);
            playerPosList->removeTail();
            break;
        
        case DOWN:
            ++newHeadPosition.pos->y;
            if(newHeadPosition.pos->y>upper_limit_y-2)
            {
                newHeadPosition.pos->y = 1;
            }
            playerPosList->insertHead(newHeadPosition);
            playerPosList->removeTail();
            break;

        case RIGHT:
            ++newHeadPosition.pos->x;
            if(newHeadPosition.pos->x>upper_limit_x-2)
            {

                newHeadPosition.pos->x = 1;
            
            }
            playerPosList->insertHead(newHeadPosition);
            playerPosList->removeTail();
            break;

        case LEFT:
            --newHeadPosition.pos->x;
            if(newHeadPosition.pos->x<1)
            {
                newHeadPosition.pos->x = upper_limit_x-2;

            }
            
            playerPosList->insertHead(newHeadPosition);
            playerPosList->removeTail();
            break;
        
        case STOP:
        default:
            break;
            
    }
    
}

// More methods to be added

bool Player::checkSelfCollision()
{
    for(int i = 0; i<getPlayerPos()->getSize(); i++)
    {
        for(int j = 0; j<getPlayerPos()->getSize(); j++)
        {
            if(i!=j)
            {
                if((getPlayerPos()->getElement(i).pos->x == getPlayerPos()->getElement(j).pos->x) 
                && (getPlayerPos()->getElement(i).pos->y == getPlayerPos()->getElement(j).pos->y))
                {
                    return true;
                }
            }
        }
    }

    return false;
    
}


bool Player::checkFoodCollision()
{

    for(int i = 0; i<getPlayerPos()->getSize(); i++)
    {   
        for(int j = 0; j<mainGameMechsRef->getFood()->getAmountOfFood(); j++)
        {

            if(getPlayerPos()->getElement(i).pos->x == mainGameMechsRef->getFood()->getFoodBucket()->getElement(j).pos->x
            && getPlayerPos()->getElement(i).pos->y == mainGameMechsRef->getFood()->getFoodBucket()->getElement(j).pos->y)
            {
                return true;
            }
        }
    }

    return false;
}
