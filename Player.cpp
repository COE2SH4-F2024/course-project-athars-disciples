#include "Player.h"
//Merge test two

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPos.pos->x = (mainGameMechsRef->getBoardSizeX())/2;
    playerPos.pos->y = (mainGameMechsRef->getBoardSizeY())/2;
    myDir = STOP;
    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPos;
}

char Player::getSymbol()
{
    return symbol;
}


void Player::setSymbol(char letter)
{
    symbol = letter;
}


void Player::setPlayerPos(int x, int y)
{
    playerPos.pos->x = x;
    playerPos.pos->y = y;
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

    }


}     


void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    
    int x = getPlayerPos().pos->x;
    int y = getPlayerPos().pos->y;
    int upper_limit_x = mainGameMechsRef->getBoardSizeX();
    int upper_limit_y = mainGameMechsRef->getBoardSizeY();
    

    switch(myDir)
    {
        case UP:
            setPlayerPos(x, --y);
            if(getPlayerPos().pos->y<1)
            {
                setPlayerPos(x, upper_limit_y-2);
            }
            break;
        
        case DOWN:
            setPlayerPos(x, ++y);
            if(getPlayerPos().pos->y>upper_limit_y-2)
            {
                setPlayerPos(x, 1);
            }
            break;

        case RIGHT:
            setPlayerPos(++x, y);
            if(getPlayerPos().pos->x>upper_limit_x-2)
            {
                setPlayerPos(1, y);
            }
            break;

        case LEFT:
            setPlayerPos(--x, y);
            if(getPlayerPos().pos->x<1)
            {
                setPlayerPos(upper_limit_x-2, y);
            }
            break;
        default:
            break;
            
    }
    

}

// More methods to be added