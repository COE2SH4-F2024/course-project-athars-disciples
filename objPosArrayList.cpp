#include "objPosArrayList.h"
#include <iostream>

// Paste your Tested implementation here.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = 200;
    aList = new objPos[arrayCapacity];

    listSize = 3;
    
    for(int i = 0; i<listSize; i++)
    {
        aList[i].setObjPos(10, 10 + i, '*');
    }
    
        
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::setListSize(int x)
{
    listSize = x;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        adjustArraySize();
    }

    for(int i = listSize; i>0; i--)
        aList[i] = aList[i-1];
    
    listSize++;
    
    aList[0].setObjPos(thisPos.pos->x, thisPos.pos->y, '*');
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        adjustArraySize();
    }
    
    listSize++;
    aList[listSize-1].setObjPos(thisPos.pos->x, thisPos.pos->y, '*');
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i<listSize-1; i++)
    {
        aList[i] = aList[i+1];
    }

    listSize--;

}

void objPosArrayList::removeTail()
{   
    listSize--;
}
        
objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index>=listSize) {
        throw std::out_of_range("Out of range index\n");
    }

    return aList[index];
}

void objPosArrayList::setElement(int i, objPos temp)
{   
    aList[i].pos->x = temp.pos->x;
    aList[i].pos->y = temp.pos->y;
}



void objPosArrayList::adjustArraySize()
{
    arrayCapacity*=2;
    objPos* newList = new objPos[arrayCapacity];

    for(int i = 0; i<listSize; i++)
    {
        newList[i] = aList[i];
    }

    delete[] aList;
    
    aList = newList;

}