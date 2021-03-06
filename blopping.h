#ifndef BLOPPING_H
#define BLOPPING_H

#include "blob.h"
#include "babyBlob.h"
#include "goodOldBlob.h"
#include "grownBlob.h"
#include "food.h"

void start_blopping(blob* blopArray, food* foodArray);

void blop_smellRadius(blob* blobArray, food* frutaArray);

void blob_smellBlob(blob* blobArray);

bool do_blob_merge(blob* blob1 , blob& blob2 );		

uint randomJiggle(uint newDirection_, uint randomJiggle);

#endif //BLOPPING_H