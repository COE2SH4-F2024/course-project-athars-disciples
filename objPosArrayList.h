#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList();
        objPosArrayList(int size);
        ~objPosArrayList();

        objPosArrayList(const objPosArrayList &copy);
        objPosArrayList &operator=(const objPosArrayList &copy);
        

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        void setListSize(int x);
        
        void adjustArraySize();
        void setElement(int i, objPos temp);
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
};

#endif