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

#define MAXBLOBS 700
#define MAXFRUTA 400
#define VMIN 1
//tood esto lo definira user ANTES DE INICIAR   
#define SPEED 2     
#define VMAX 5	            //DEPENDE MODO 1 O 2    
#define FOODCOUNT 30
#define MODO1 1 
#define MODO2 0
#define BLOBCOUNT 10
#define RANDOMJIGGLE 2   //ENTRE 0 Y 360

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
        //Empiezan todos BABY BLOBS
        /*      
         blobArray[i]= blob(random_position_x,
                            random_position_y,
                            random_deathProb,
                            speed,
                            radio,
                            max_food_count,
                            randomjiggle);

        */
                                      //https://stackoverflow.com/questions/686353/random-float-number-generation  
         blobArray[i]= blob((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (WIDTH)))),
                            (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (HEIGHT)))),
                            (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)),
                             SPEED,
                             BABYRADIO,
                             BABYMAXFOOD,
                             RANDOMJIGGLE);
    
    }

    for (i = 0; i < FOODCOUNT; i++)
    {
        foodArray[i] = food((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / WIDTH))), (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / HEIGHT))));
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




    delete[] blobArray;
    delete[] foodArray;
    return 0;
}



int randomVelocity(int vmax, int vmin)
{
    return rand() % (vmax - vmin + 1) + vmin;
}
