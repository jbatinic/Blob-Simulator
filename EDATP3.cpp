// EDATP3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "graphicalFunctions.h"
#include "blob.h"

#define MAXLOBS 20;

int main()
{
    srand(time(NULL));
    blob testBlob = blob(5,20,30,3,5); 

    printf("x: %f y: %f \nradius: %u \ndirection: %u ", testBlob.getPosx(), testBlob.getPosy(), testBlob.getblobRadius(), testBlob.getblobDirection());

}


