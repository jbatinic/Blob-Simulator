#include "blob.h"

#define absolute(arg) ( ((arg) >= 0) ? arg : -arg) 

uint blob::blobTotalCount = 0;

/****************************************
*			CONSTRUCTORES				*
*****************************************/
blob::blob(){
	blobPos.x =0;
	blobPos.y = 0;
	deathProb = 0;
	foodCount = 0;
	blobRadius = 0;
	percentSpeed = 0;
	blobDirection = 0;
}

blob::blob(uint speed, uint ancho, uint alto, uint radio_, float percentSpeed_)
{
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
void blob::setDirection(uint blobDirection_)
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
void blob::setfoodCount(uint foodCount_) { foodCount = foodCount_; }
void blob::setRadio(uint radio_) { blobRadius = radio_; }
void blob::setPercentSpeed(float percentSpeed_) { percentSpeed = percentSpeed_; }

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

double blob::checkRadius(blob& blob2)		
{
	if (blobRadius == blob2.getblobRadius())			//Si tienen el mismo radio son del mismo tipo
		return (((blobPos.x - blob2.getPosx()) * (blobPos.x - blob2.getPosx()) + (blobPos.y - blob2.getPosy()) * (blobPos.y- blob2.getPosy())) < ((blobRadius * 2) * (blobRadius *2 )));
	else
		return 0;
}

double blob::checkFood(food& fruta)
{
	int r = blobRadius + fruta.getfoodRadius();
	int result =0; 

	if (((blobPos.x - fruta.getfoodPosx()) * (blobPos.x - fruta.getfoodPosx()) + (blobPos.y - fruta.getfoodPosy()) * (blobPos.y - fruta.getfoodPosy())) < r * r)
		result = 1; //case1
	else if (((blobPos.x - fruta.getfoodPosx()) * (blobPos.x - fruta.getfoodPosx()) + (blobPos.y - fruta.getfoodPosy()) * (blobPos.y - fruta.getfoodPosy())) < (r / 2))				//Estan casi superpuestos
		result = 2; //case2

	return result;
}

void blob::changeDirection(food& fruta)
{
	uint newDirection;
	double change_x = blobPos.x - fruta.getfoodPosx();
	double change_y = blobPos.y - fruta.getfoodPosy();

	if (change_y > 0)
	{
		newDirection = (uint) atan(change_y / (absolute(change_y)));			//fruta abajo de blob
		if (change_x > 0)
			newDirection += 180;
		else
			newDirection = 180 - newDirection;
	}
	else                                                             //Fruta encima de blob
	{
		newDirection = (uint) atan(absolute(change_x) / (change_y * (-1)));
		if (change_x > 0)
			newDirection = 360 - newDirection;
	}
	setDirection(newDirection);
}


/*

double blob::checkRadius(blob& blob1, blob& blob2)
{
	if (blob1.getblobRadius() == blob2.getblobRadius)			//Si tienen el mismo radio son del mismo tipo
		return (((blob1.getPosx() - blob2.getPosx()) * (blob1.getPosx() - blob2.getPosx()) + (blob1.getPosy() - blob2.getPosy()) * (blob1.getPosx() - blob2.getPosy())) < ((blob1.getblobRadius() * 2) * (blob1.getblobRadius() * 2)));
	else
		return 0;
}

double blob::checkFood(food& fruta, blob& blob1)
{
	int r = blob1.getblobRadius() + fruta.getfoodRadius();
	return ((blob1.getPosx() - fruta.getfoodPosx) * (blob1.getPosx() - fruta.getfoodPosx) + (blob1.getPosy() - fruta.getfoodPosy) * (blob1.getPosy() - fruta.getfoodPosy)) < r * r;
}

*/