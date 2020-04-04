// EDATP3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "graphicalFunctions.h"
#include "blob.h"
#include "babyBlob.h"
#include "goodOldBlob.h"
#include "grownBlob.h"
#include "blopping.h"
#include "food.h"
#include <stdio.h>

//tood esto lo definira user
#define SPEED 2     
#define VMAX 5	
#define VMIN 1	
#define MAXBLOBS 700
#define MAXFRUTA 400
#define FOODCOUNT 30
#define MODO1 1 
#define MODO2 0
#define BLOBCOUNT 10

//function nose donde ponerla
int randomVelocity(int vmax, int vmin);

using namespace std;

int main()
{
    srand(time(NULL));
    food* foodArray = new food[MAXFRUTA];
    food::foodTotalCount = FOODCOUNT;      //definida por usuario ??
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
        blobArray[i].setDirection(rand()%360);
        blobArray[i].setPercentSpeed(SPEED);
        blobArray[i].setRadio(BABYRADIO);           //Empiezan todos BABY BLOBS
        blobArray[i].setfoodMax(BABYMAXFOOD);
    }

    for (i = 0; i < FOODCOUNT; i++)
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

   int j = 0;
   do
   {
        for (i = 0; i < blob::blobTotalCount; i++)
        {
           printf("Blob %u - x: %f y: %f            FOOD COUNT:%u\n", i, blobArray[i].getPosx(), blobArray[i].getPosy(), blobArray[i].getfoodCount());
           blobArray[i].moveBlob();
        }

        start_blopping(blobArray, foodArray);

        for (i = 0; i < blob::blobTotalCount; i++)
        {
            printf("Blob %u - x: %f y: %f            FOOD COUNT:%u\n", i, blobArray[i].getPosx(), blobArray[i].getPosy(), blobArray[i].getfoodCount());
            blobArray[i].moveBlob();
        }
                   
        printf("\n");

   } while (++j<40);
    


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

    food* foodArray = new food[MAXFRUTA];
    double x_position;
    double y_position;

    for (i = 0; i < MAXFRUTA; i++)
    {
        foodArray[i].food(x_position,y_position);
    }

*/