// EDATP3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "graphicalFunctions.h"
#include "blob.h"
#include "babyBlob.h"
#include "goodOldBlob.h"
#include "grownBlob.h"

#define MAXBLOBS 10
#define SPEED 3.5


using namespace std;
int main()
{
    srand(time(NULL));
    blob* blobArray = new grownBlob[MAXBLOBS];

    uint i;

    for (i = 0; i < MAXBLOBS; i++)
    {
        blobArray[i].setPosx(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (WIDTH))));
        blobArray[i].setPosy(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (HEIGHT))));
        blobArray[i].setDeathProb(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
        blobArray[i].setfoodCount(0);
        blobArray[i].setDirection(rand() % 360);
        blobArray[i].setPercentSpeed(SPEED);
    }

    for (i = 0; i < MAXBLOBS; i++)
    {
        cout << "x:%f  " << blobArray[i].getPosx() << "y:%f" << blobArray[i].getPosy() << endl;
    }
    for (i = 0; i < MAXBLOBS; i++)
    {
        blobArray[i].moveBlob();
    }
    cout << "AFTER MOVING" << endl;

    for (i = 0; i < MAXBLOBS; i++)
    {
        cout << "x:%f  " << blobArray[i].getPosx() << "y:%f" << blobArray[i].getPosy() << endl;
    }

    delete[] blobArray;
    return 0;
}


