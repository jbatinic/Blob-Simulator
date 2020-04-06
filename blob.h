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

#define BLOBSPEED 1.0
#define BLOBRADIO 5
#define BLOBMAXFOOD 5

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
	void setVelocity(int blobVelocity_);
	void setfoodCount(uint foodCount_);
	void setRadio(uint radio_);
	void setPercentSpeed(float percentSpeed_);
	void setfoodMax(uint maxFoodCount_);
//	void setNewMergeDirection(uint blobMergeDirection_);
	void setMergeFlag(void);
	void setblobStatus(uint isAliveFlag);
	void setRandomJiggle(uint RandomJiggle_);

	//Getters
	double getPosx(void);
	double getPosy(void);
	uint getblobVelocity(void);
	uint getblobRadius(void);
	uint getblobDirection(void);
	uint getblobStatus(void);
	uint getfoodCount(void);
	uint getRandomJiggle(void);
	bool getMergeFlag(void);
	

	//Funciones
	void moveBlob(void);
	int checkRadius(blob& blob2);
	int checkFood(food* fruta);
	void changeDirection(food* fruta);
	void blobFeeding(blob* blobArray);
	virtual void blobBirth(blob* blobArray);
	void blobMerge(blob* blobArray, uint*array_of_Directions, int mergeTotal);
	void blobDeath(double userDeathProb);

protected:
	position_t blobPos;
	uint blobDirection;
	int blobVelocity;
	uint blobRadius;
	uint isAliveFlag;
	double deathProb;
	uint foodCount;
	double percentSpeed;
	uint maxFoodCount;
	uint blobMergeDirection;
	bool mergeFlag;
	uint RandomJiggle; 
};


#endif //BLOB_H

