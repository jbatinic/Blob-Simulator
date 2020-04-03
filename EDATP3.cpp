// EDATP3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "graphicalFunctions.h"
#include "blob.h"
#include "babyBlob.h"
#include "goodOldBlob.h"
#include "grownBlob.h"
#include "blopping.h"
#include "food.h"

//tood esto lo definira user
#define SPEED 3.5
#define VMAX 5	
#define VMIN 1	
#define MAXBLOBS 10
#define FRUTATOTAL 10
#define MODO1 1 
#define MODO2 0
#define BLOBCOUNT 10

//function nose donde ponerla
int randomVelocity(int vmax, int vmin);

using namespace std;
int main()
{
    srand(time(NULL));
    food* foodArray = new food[FRUTATOTAL];

    blob* blobArray = new babyBlob[MAXBLOBS];
    blob::blobTotalCount = BLOBCOUNT; //definida por usuario

    uint i;
    
    for (i = 0; i < BLOBCOUNT; i++)          //Este es BLOBCOUNT, blobs definidos por usuario para empezar
    {
        //https://stackoverflow.com/questions/686353/random-float-number-generation  

        blobArray[i].setPosx(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (WIDTH))));
        blobArray[i].setPosy(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (HEIGHT))));
        blobArray[i].setDeathProb(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
        blobArray[i].setfoodCount(0);
        blobArray[i].setDirection(rand() % 360);
        blobArray[i].setPercentSpeed(SPEED);
        blobArray[i].setRadio(BABYRADIO);           //Empiezan todos BABY BLOBS
        blobArray[i].setfoodMax(BABYMAXFOOD);
    }

    for (i = 0; i < FRUTATOTAL; i++)
    {
        foodArray[i].setPosx_f(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (WIDTH))));
        foodArray[i].setPosy_f(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (HEIGHT))));
    }

    
    if (MODO1)
    {
        for (i = 0; i < MAXBLOBS; i++)             //Seteamos velocidades para todos los existentes y futuros blobs para tenerlos listo en blobBirth
        {
            blobArray[i].setVelocity(VMAX);
        }
    }
    else if (MODO2)
    {
        for (i = 0; i < MAXBLOBS; i++)
        {
            blobArray[i].setVelocity(randomVelocity(VMAX, VMIN));
        }
    }
    

   start_blopping(blobArray, foodArray);

    


    delete[] blobArray;
    delete[] foodArray;
    return 0;
}



int randomVelocity(int vmax, int vmin)
{
    return rand() % (vmax - vmin + 1) + vmin;
}


/*
preguntar pq esto no funcionaria
    for (i = 0; i < FRUTATOTAL; i++)
    {
        foodArray[i].food(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (WIDTH))), static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (HEIGHT))));
    }

*/