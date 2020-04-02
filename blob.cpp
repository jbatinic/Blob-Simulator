#include "blob.h"

/****************************************
*			CONSTRUCTORES				*
*****************************************/

blob::blob(uint speed, uint ancho, uint alto, uint radio_, float percentSpeed_)
{
	//https://stackoverflow.com/questions/686353/random-float-number-generation 
	blobPos.x = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (ancho)));
	blobPos.y = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (alto)));
	deathProb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	foodCount = 0;
	blobRadius = radio_;
	percentSpeed = percentSpeed_;
	blobDirection = rand() % 360;
}

/****************************************
*			SETTERS		         		*
*****************************************/
void blob::setDirection(double blobDirection_)
{
	blobDirection = blobDirection_;
	blobPos.xnext = blobPos.x + sin(PI * blobDirection_ / 180);
	blobPos.ynext = blobPos.y + cos(PI * blobDirection_ / 180);
}

void blob::setDeathProb(float deathProb_) { deathProb = deathProb_; }
void blob::setVelocity(int blobVelocity_) { blobVelocity = blobVelocity_; }
void blob::setPosx(double posx_) { blobPos.x = posx_; }
void blob::setPosy(double posy_) { blobPos.y = posy_; }
void blob::setPosxnext(double posxnext_) { blobPos.xnext = posxnext_; }
void blob::setPosynext(double posynext_) { blobPos.ynext = posynext_; }


/****************************************
*				GETTERS		     		*
*****************************************/
double blob::getPosx(void) { return blobPos.x; }
double blob::getPosy(void) { return blobPos.y; }
double blob::getPosxnext(void) { return blobPos.xnext; }
double blob::getPosynext(void) { return blobPos.ynext; }
uint blob::getblobRadius(void) { return blobRadius; }
uint blob::getblobDirection(void) { return blobDirection; }

/****************************************
*			FUNCIONES					*
*****************************************/
void blob::moveBlob()
{
	double tempNextx = getPosx() + sin(PI * getblobDirection() / 180);
	double tempNexty = getPosy() + cos(PI * getblobDirection() / 180);

	if (tempNextx < 0)
	{
		tempNextx += WIDTH;
	}

	if (tempNextx > WIDTH)
	{
		tempNextx -= WIDTH;
	}

	if (tempNexty < 0)
	{
		tempNexty += HEIGHT;
	}

	if (tempNexty > HEIGHT)
	{
		tempNexty -= HEIGHT;
	}

	setPosx(tempNextx);
	setPosy(tempNexty);
}

double blob::checkRadius(blob& blob2)		//Antes verificar que sean del mismo tipo (mismo radius)
{
	return ((blobPos.x - blob2.getPosx()) * (blobPos.x - blob2.getPosx()) + (blobPos.y - blob2.getPosy()) * (blobPos.y - blob2.getPosy())) < (blobRadius * 2) * (blobRadius * 2);
}

double blob::checkFood(Food& fruta)
{
	int r = blobRadius + fruta.foodRadius;

	return ((blobPos.x - fruta.foodPosx) * (blobPos.x - fruta.foodPosx) + (blobPos.y - fruta.foodPosy) * (blobPos.y - fruta.foodPosy)) < r * r;
}

