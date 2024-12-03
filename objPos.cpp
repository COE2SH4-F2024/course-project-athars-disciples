#include "objPos.h"

//Default constructor for objPos
objPos::objPos()
{
    //memory allocation
    pos = new Pos; 
    //initializing position and symbol
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

//Parameterized constructor objPos
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    //initializing position and symbol
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//Copy assignment operator for objPos
objPos &objPos::operator=(const objPos &copy)
{
    if (this == &copy) 
        return *this;

    delete pos;

    pos = new Pos;
    pos->x = copy.pos->x;
    pos->y = copy.pos->y;
    symbol = copy.symbol;

    return *this;
}

//Copy constructor for objPos
objPos::objPos(const objPos &copy)
{
    pos = new Pos;
    
    pos->x = copy.pos->x;
    pos->y = copy.pos->y;
    symbol = copy.symbol;


}

//Destructor for objPos
objPos::~objPos()
{
    delete pos;
}


//Setting position and symbol based on another objPos object 
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

//Setting position and symbol based on specified values
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//Setting symbol
void objPos::setSymbol(char sym)
{
    symbol = sym;
}

//Getter for position
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

//Getter for symbol
char objPos::getSymbol() const
{
    return symbol;
}

//Checking if the position of obj is same as another objPos
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

//Getter for SymbolIfPosEqual
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos)) //checks if positions are same
        return symbol;
    else
        return 0;
}

