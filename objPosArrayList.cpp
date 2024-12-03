#include "objPosArrayList.h"
#include <iostream>


//Default constructor for objPosArrayList class
objPosArrayList::objPosArrayList()
{
    //Initializing capacity
    arrayCapacity = 200;
    //allocating memory for the objPosArrayList
    aList = new objPos[arrayCapacity];

    //Initializing the list size
    listSize = 1;

    //Setting the position and symbol for the head
    aList[0].setObjPos(10, 10, '^');
        
}

//Constructor for objPosArrayList class
objPosArrayList::objPosArrayList(int size)
{

    arrayCapacity = 200;
    aList = new objPos[arrayCapacity];

    listSize = size;
    
    aList[0].setObjPos(10, 10, '^');

    //Initializing elements with default body symbol
    for(int i = 1; i<listSize; i++)
    {
        aList[i].setObjPos(10, 10 + i, '*');
    }
    
        
}

//Copy constructor for objPosArrayList class
objPosArrayList::objPosArrayList(const objPosArrayList &copy)
{
    arrayCapacity = copy.arrayCapacity;
    aList = new objPos[arrayCapacity];

    listSize = copy.listSize;

    for(int i = 0; i<listSize; i++)
    {
        aList[i].getObjPos().setSymbol(copy.getElement(i).symbol);
        aList[i].getObjPos().pos->x = copy.getElement(i).pos->x;
        aList[i].getObjPos().pos->y = copy.getElement(i).pos->y;
    }

}

//Copy assignment constructor for objPosArrayList class
objPosArrayList &objPosArrayList::operator=(const objPosArrayList &copy)
{
    delete[] aList;

    arrayCapacity = copy.arrayCapacity;
    aList = new objPos[arrayCapacity];

    listSize = copy.listSize;

    for(int i = 0; i<listSize; i++)
    {
        aList[i] = copy.getElement(i);
    }
}

//Destructor for objPosArrayList class
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

//Getter for the listSize
int objPosArrayList::getSize() const
{
    return listSize;
}

//Sets listSize
void objPosArrayList::setListSize(int x)
{
    listSize = x;
}

//Inserting element at the head of the list
void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        adjustArraySize();
    }

    for(int i = listSize; i>0; i--)
    {
        aList[i] = aList[i-1];

        //Setting all the other elements to the default symbol I chose
        aList[i].setSymbol('*');
    }
    
    listSize++;
    //Setting new head element
    aList[0].setObjPos(thisPos.pos->x, thisPos.pos->y, thisPos.getSymbol());
}

//Inserting element at the tail of the list
void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        adjustArraySize();
    }
    
    aList[listSize++].setObjPos(thisPos.pos->x, thisPos.pos->y, thisPos.getSymbol());
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i<listSize-1; i++)
    {
        aList[i] = aList[i+1];
    }

    listSize--;

}

//Removes tail element
void objPosArrayList::removeTail()
{   
    listSize--;
}
        
// Getter for the HeadElement
objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

//Getter for the TailElement
objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

//Getter for element
objPos objPosArrayList::getElement(int index) const
{
    //Checks if range is valid
    if (index < 0 || index>=listSize) {
        throw std::out_of_range("Out of range index\n");
    }

    return aList[index];
}

//Sets element at a specifed value
void objPosArrayList::setElement(int i, objPos temp)
{   
    aList[i].pos->x = temp.pos->x;
    aList[i].pos->y = temp.pos->y;
    aList[i].symbol = temp.symbol;
}


//Adjusts array size
void objPosArrayList::adjustArraySize()
{
    arrayCapacity*=2; 
    objPos* newList = new objPos[arrayCapacity];
    //Copying to new array
    for(int i = 0; i<listSize; i++)
    {
        newList[i] = aList[i];
    }

    delete[] aList;
    
    aList = newList;
}