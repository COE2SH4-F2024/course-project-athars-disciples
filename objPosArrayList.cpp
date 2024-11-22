#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = 200;
    listSize = 0;
    aList = new objPos[arrayCapacity];
    
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        adjustArraySize();
    }

    listSize++;

    for(int i = listSize-1; i>0; i--)
        aList[i] = aList[i-1];
    
    aList[0].setObjPos(thisPos.pos->x, thisPos.pos->y, '@');
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        adjustArraySize();
    }
    
    listSize++;
    aList[listSize].setObjPos(thisPos.pos->x, thisPos.pos->y, '@');
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
    return aList[listSize];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
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