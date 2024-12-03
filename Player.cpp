#include "Player.h"

//Player constructor with Gamemechanics reference
Player::Player(GameMechs* thisGMRef)
{
    //Assigning the Player class gamemechs pointer to the input gamemechs pointer
    mainGameMechsRef = thisGMRef;
    
    //Assigning memory for the player position with an initial listSize of 1
    playerPosList = new objPosArrayList(1);
    
    //Defining the initial x and y position of the snake
    playerPosList->getHeadElement().pos->x = (mainGameMechsRef->getBoardSizeX())/2;
    playerPosList->getHeadElement().pos->y = (mainGameMechsRef->getBoardSizeY())/2;
    playerPosList->getHeadElement().setSymbol('^');

    
    //Setting initial direction to stopped
    myDir = STOP;

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

    //Checking if the player has moved
    char input = mainGameMechsRef->getInput();
    

    if(input != 0 && mainGameMechsRef->getDifficulty() != mainGameMechsRef->Start)
    {
        //Switch cases depending on input given
        switch(input)
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
            
            case ' ':
                mainGameMechsRef->setExit(true);
            

            default:
                break;    
        }

    }


}     


void Player::insertPlayerTail()
{
    int size = getPlayerPos()->getSize();
    int tail_x = playerPosList->getTailElement().pos->x;
    int tail_y = playerPosList->getTailElement().pos->y;
    objPos compare;

    //Adding tail if you onlt have the starting character
    if(size == 1)
    {
        if(myDir == UP)
        {
            playerPosList->insertTail(objPos(tail_x, tail_y+1, '*'));
        }
        else if(myDir == DOWN){
            playerPosList->insertTail(objPos(tail_x, tail_y-1, '*'));
        }
        else if(myDir == LEFT){
            playerPosList->insertTail(objPos(tail_x+1, tail_y, '*'));
        }
        else if(myDir == RIGHT){
            playerPosList->insertTail(objPos(tail_x-1, tail_y, '*'));
        }
        
    }

    else
    {
        if(tail_x == playerPosList->getElement(size-2).pos->x
        && tail_y == playerPosList->getElement(size-2).pos->y-1)
        {
            compare = objPos(tail_x, tail_y-1, '*');
            playerPosList->insertTail(compare);
    
        }
        else if(tail_x == playerPosList->getElement(size-2).pos->x
        && tail_y == playerPosList->getElement(size-2).pos->y+1)
        {
            playerPosList->insertTail(objPos(tail_x, tail_y+1, '*'));
        }

        else if(tail_x == playerPosList->getElement(size-2).pos->x-1
        && tail_y == playerPosList->getElement(size-2).pos->y)
        {
            playerPosList->insertTail(objPos(tail_x-1, tail_y, '*'));
        }

        else if(tail_x == playerPosList->getElement(size-2).pos->x+1
        && tail_y == playerPosList->getElement(size-2).pos->y)
        {
            playerPosList->insertTail(objPos(tail_x+1, tail_y, '*'));
        }
    }

    mainGameMechsRef->getFood()->generateFoodBucket(*playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());
    
}


void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int upper_limit_x = mainGameMechsRef->getBoardSizeX();
    int upper_limit_y = mainGameMechsRef->getBoardSizeY();
    
    objPos newHeadPosition;
    newHeadPosition.pos->x = playerPosList->getHeadElement().pos->x;
    newHeadPosition.pos->y = playerPosList->getHeadElement().pos->y;
    playerPosList->getHeadElement().setSymbol('*');

    switch(myDir)
    {
        case UP:
            --newHeadPosition.pos->y;
            if(newHeadPosition.pos->y<1)
            {
                newHeadPosition.pos->y = upper_limit_y-2;

            }
            newHeadPosition.setSymbol('^');
            playerPosList->insertHead(newHeadPosition);
            playerPosList->removeTail();
            break;
        
        case DOWN:
            ++newHeadPosition.pos->y;
            if(newHeadPosition.pos->y>upper_limit_y-2)
            {
                newHeadPosition.pos->y = 1;
            }
            newHeadPosition.setSymbol('^');
            playerPosList->insertHead(newHeadPosition);
            playerPosList->removeTail();
            break;

        case RIGHT:
            ++newHeadPosition.pos->x;
            if(newHeadPosition.pos->x>upper_limit_x-2)
            {

                newHeadPosition.pos->x = 1;
            
            }
            newHeadPosition.setSymbol('^');
            playerPosList->insertHead(newHeadPosition);
            playerPosList->removeTail();
            break;

        case LEFT:
            --newHeadPosition.pos->x;
            if(newHeadPosition.pos->x<1)
            {
                newHeadPosition.pos->x = upper_limit_x-2;

            }
            newHeadPosition.setSymbol('^');
            playerPosList->insertHead(newHeadPosition);
            playerPosList->removeTail();
            break;
        
        case STOP:
        default:
            break;
            
    }

    //Checking if the player collided with itself
    checkSelfCollision();

    //Checking if the player satisfied the win condition
    checkWinCondition();
    
}

//Defining Member function checking for self collision
bool Player::checkSelfCollision()
{

    //If the size if 1 we cannot collide with ourselves, so returning false
    if(playerPosList->getSize() == 1)
    {
        return false;
    }

    
    
    for(int i = 0; i<getPlayerPos()->getSize(); i++)
    {
        for(int j = 0; j<getPlayerPos()->getSize(); j++)
        {
            if(i!=j)
            {
                if((getPlayerPos()->getElement(i).pos->x == getPlayerPos()->getElement(j).pos->x) 
                && (getPlayerPos()->getElement(i).pos->y == getPlayerPos()->getElement(j).pos->y))
                {
                    //Setting the exit flag and loseFlag to true within gamemechanics if self collision is detected
                    mainGameMechsRef->setExit(true);
                    mainGameMechsRef->setLoseFlag();

                    //Removing the head so that the board does not attempt to print two parts of the body on the same position
                    playerPosList->removeHead();
                    return true;
                    
                }
            }
        }
    }
}


void Player::checkFoodCollision()
{
    int size = getPlayerPos()->getSize();

    for(int i = 0; i<getPlayerPos()->getSize(); i++)
    {   
        for(int j = 0; j<mainGameMechsRef->getFood()->getAmountOfFood(); j++)
        {

            if(getPlayerPos()->getElement(i).pos->x == mainGameMechsRef->getFood()->getFoodBucket()->getElement(j).pos->x
            && getPlayerPos()->getElement(i).pos->y == mainGameMechsRef->getFood()->getFoodBucket()->getElement(j).pos->y)
            {
                    //Setting a boolean value checking whether the snake ate food to false initially
                int index = 0;

                //Section where necessary changes are made depending on eatFood condition
                if(getPlayerDir() != STOP)
                {

                    //Doing the given effects depending on the item hit
                    switch(mainGameMechsRef->getFood()->getFoodBucket()->getElement(j).symbol)
                    {
                        case 'A':
                            mainGameMechsRef->incrementScore(10);
                            insertPlayerTail();
                            break;
                        case 'B':
                            mainGameMechsRef->incrementScore(20);
                            insertPlayerTail();
                            insertPlayerTail();
                            break;
                        case 'C':
                            mainGameMechsRef->incrementScore(30);
                            break;
                        case 'D':
                            mainGameMechsRef->incrementScore(-100);
                            for(int l = 0; l<3; l++)
                            {
                                if(playerPosList->getSize() > 1)
                                    playerPosList->removeTail();
                            }
                            break;

                        default:
                            break;
                    }

                    //Regenerating the foodbucket depending on the new player object positions

                    //Creating new foodBucket depending on new position of character (to avoid it continuously colliding)
                    mainGameMechsRef->getFood()->generateFoodBucket(*playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());

                }
            }
        }
    }
}


bool Player::checkWinCondition()
{
    if(mainGameMechsRef->getDifficulty() == mainGameMechsRef->Easy)
    {
        if(mainGameMechsRef->getScore() == 200)
        {
            mainGameMechsRef->setExit(true);
            return true;
        }

        else
            return false;
    }

    else if(mainGameMechsRef->getDifficulty() == mainGameMechsRef->Medium)
    {
        if(mainGameMechsRef->getScore() == 500)
        {
            mainGameMechsRef->setExit(true);
            return true;
        }

        else
            return false;
    }

    else if(mainGameMechsRef->getDifficulty() == mainGameMechsRef->Hard)
    {
        if(mainGameMechsRef->getScore() == 1000)
        {
            mainGameMechsRef->setExit(true);
            return true;
        }

        else
            return false;
    }

    else if(mainGameMechsRef->getDifficulty() == mainGameMechsRef->Impossible)
    {
        int area = mainGameMechsRef->getBoardSizeX()*mainGameMechsRef->getBoardSizeY() - (2*mainGameMechsRef->getBoardSizeX() + 2*mainGameMechsRef->getBoardSizeY());
        
        if(playerPosList->getSize() == area)
        {
            mainGameMechsRef->setExit(true);
            return true;
        }

        else
            return false;
    }

    return false;
}