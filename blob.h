#ifndef BLOB_H
#define BLOB_H

#define UNIDAD 5

#include <stdio.h>
#include <math.h>
#include <random>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "food.h"

#define WIDTH 1280
#define HEIGHT 720
#define PI 3.14159265
#define MERGE 1
#define BLOBSALUDO 2
#define NOTCLOSE 0

#define DEAD 0 
#define ALIVE 1

#define SEARCHING 2 
#define GOING 3

#define BLOBSPEED 1.0
#define BLOBRADIO 4
#define BLOBMAXFOOD 3

typedef struct
{
	double x;
	double y;
	double xnext;
	double ynext;
}position_t;

typedef unsigned int uint;

class blob 
{
public:
	//Constructores
	blob();
	blob(double posx_, double posy_, float deathProb_, double speed_, uint radio_, uint maxFoodCount_, uint RandomJiggle_);
	
	//static 
	static uint blobTotalCount;
	static uint increaseCount(void);

	//Setters
	void setPosx(double posx_);
	void setPosy(double posy_);
	void setDirection(uint Blobdirection_);
	void setDeathProb(float deathProb);
	void setVelocity(double blobVelocity_);
	void setfoodCount(uint foodCount_);
	void setRadio(uint radio_);
	void setPercentSpeed(float percentSpeed_);
//	void setMaxfoodCount(uint maxFoodCount_);
//	void setNewMergeDirection(uint blobMergeDirection_);
	void setMergeFlag(void);
	void setblobStatus(uint isAliveFlag);
	void setRandomJiggle(uint RandomJiggle_);

	//Getters
	double getPosx(void);
	double getPosy(void);
	double getblobVelocity(void);
	uint getblobRadius(void);
	uint getblobDirection(void);
	uint getblobStatus(void);
	uint getfoodCount(void);
	uint getRandomJiggle(void);
	bool getMergeFlag(void);
	uint getbitmapSize(void);
	uint getMaxfoodCount(void);
	float getpercentSpeed(void);

	//Funciones
	void moveBlob(void);
	int checkRadius(blob& blob2);
	int checkFood(food* fruta);
	void changeDirection(food* fruta);
	//void blobFeeding(blob* blobArray);
	virtual void blobBirth(blob* blobArray);
	void blobDeath(float userDeathProb);

protected:
	position_t blobPos;
	uint blobDirection;
	double blobVelocity;
	uint blobRadius;
	uint isAliveFlag;
	float deathProb;
	uint foodCount;
	double percentSpeed;
	uint maxFoodCount;
	uint blobMergeDirection;
	bool mergeFlag;
	uint RandomJiggle; 
	uint bitmapSize;
};


#endif //BLOB_H

