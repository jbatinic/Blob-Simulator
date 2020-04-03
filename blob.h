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
	blob(uint speed, uint ancho, uint alto, uint radio_, float percentSpeed_);

	//static 
	static uint blobTotalCount;

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

	//Getters
	double getPosx(void);
	double getPosy(void);
	double getPosxnext(void);
	double getPosynext(void);
	uint getblobRadius(void);
	uint getblobDirection(void);

	//Funciones
	void moveBlob(void);
	double checkRadius(blob* blob2);
	double checkFood(food* fruta);
	void changeDirection(food* fruta);
	


protected:
	position_t blobPos;
	uint blobDirection;
	int blobVelocity;
	uint blobRadius;
	float deathProb;
	uint foodCount;
	float percentSpeed;
	uint maxFoodCount;
//	uint blobGroup;

};


#endif //BLOB_H

