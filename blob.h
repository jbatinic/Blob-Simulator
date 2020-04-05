#ifndef BLOB_H
#define BLOB_H

#define UNIDAD 5

#include <stdio.h>
#include <math.h>
#include <random>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "food.h"

#define WIDTH 60
#define HEIGHT 50
#define PI 3.14159265
#define MERGE 1;
#define BLOBSALUDO 2;
#define NOTCLOSE 0; 
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
	blob(uint ancho, uint alto, uint radio_, float percentSpeed_);

	//static 
	static uint blobTotalCount;
	static uint increaseCount(void);

	//Setters
	void setPosx(double posx_);
	void setPosy(double posy_);
	void setPosxnext(double posxnext_);
	void setPosynext(double posynext_);
	void setDirection(uint Blobdirection_);
	void setDeathProb(float deathProb);
	void setVelocity(int blobVelocity_);
	void setfoodCount(uint foodCount_);
	void setRadio(uint radio_);
	void setPercentSpeed(float percentSpeed_);
	void setfoodMax(uint maxFoodCount_);
//	void setNewMergeDirection(uint blobMergeDirection_);
	void setMergeFlag(void);

	//Getters
	double getPosx(void);
	double getPosy(void);
	double getPosxnext(void);
	double getPosynext(void);
	double getPercentSpeed(void);
	uint getblobRadius(void);
	uint getblobDirection(void);
	uint getfoodCount(void);
	bool getMergeFlag(void);

	//Funciones
	void moveBlob(void);
	int checkRadius(blob& blob2);
	int checkFood(food* fruta);
	void changeDirection(food* fruta);
	void blobFeeding(blob* blobArray);
	virtual void blobBirth(blob* blobArray);
	virtual void blobMerge(blob* blobArray, uint*array_of_Directions, int mergeTotal);


protected:
	position_t blobPos;
	uint blobDirection;
	int blobVelocity;
	uint blobRadius;
	float deathProb;
	uint foodCount;
	double percentSpeed;
	uint maxFoodCount;

	uint blobMergeDirection;
	bool mergeFlag;
};


#endif //BLOB_H

