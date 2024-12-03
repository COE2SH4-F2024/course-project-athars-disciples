#include "objPosArrayList.h"
#include <iostream>



// Paste your Tested implementation here.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = 200;
    aList = new objPos[arrayCapacity];
    listSize = 1;
    aList[0].setObjPos(10, 10, '^');
        
}


objPosArrayList::objPosArrayList(int size)
{
    //SetConsoleOutputCP(CP_UTF8);
    arrayCapacity = 200;
    aList = new objPos[arrayCapacity];

    listSize = size;
    
    aList[0].setObjPos(10, 10, '^');

    for(int i = 1; i<listSize; i++)
    {
        aList[i].setObjPos(10, 10 + i, '*');
    }
    
        
}

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
    {
        aList[i] = aList[i-1];

        //Setting all the other elements to the default symbol I chose
        aList[i].setSymbol('*');
    }
    
    listSize++;
    
    aList[0].setObjPos(thisPos.pos->x, thisPos.pos->y, thisPos.getSymbol());
}

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
    aList[i].symbol = temp.symbol;
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