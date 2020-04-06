#include "blob.h"

#define absolute(arg) ( ((arg) >= 0) ? arg : -arg) 

uint blob::blobTotalCount = 0;

/****************************************
*			CONSTRUCTORES				*
*****************************************/
blob::blob(void){
	blobPos.x =-10;
	blobPos.y = -10;
	deathProb = 0;
	foodCount = 0;
	blobRadius = 0;
	percentSpeed = 0;
	maxFoodCount = 0;
	blobDirection = 0;
	blobVelocity = 0;
	blobMergeDirection = 0;
	mergeFlag = false; 
	isAliveFlag = 0;
	RandomJiggle = 0;
}

blob::blob(double posx_, double posy_ , float deathProb_, double speed_,uint radio_, uint maxFoodCount_ , uint RandomJiggle_)
{
	blobPos.x = posx_;
	blobPos.y = posy_;
	deathProb = deathProb_;
	blobRadius = radio_;
	maxFoodCount = maxFoodCount_;
	blobDirection = rand()%360;
	blobMergeDirection = blobDirection; 
	mergeFlag = false;
	foodCount = 0;
	percentSpeed =speed_;
	isAliveFlag = ALIVE;
	blobVelocity = 0;	//La inicializo pero vamos a escribir sobre ella depsues
	RandomJiggle = RandomJiggle_;

}

/****************************************
*			SETTERS		         		*
*****************************************/
void blob::setDirection(uint blobDirection_){blobDirection = blobDirection_;}
void blob::setDeathProb(float deathProb_) { deathProb = deathProb_; }
void blob::setVelocity(int blobVelocity_) { blobVelocity = blobVelocity_; }
void blob::setPosx(double posx_) { blobPos.x = posx_; }
void blob::setPosy(double posy_) { blobPos.y = posy_; }
void blob::setfoodCount(uint foodCount_) { foodCount = foodCount_; }
void blob::setRadio(uint radio_) { blobRadius = radio_; }
void blob::setblobStatus(uint isAliveFlag_ ) { isAliveFlag = isAliveFlag_; }
void blob::setPercentSpeed(float percentSpeed_) { percentSpeed = percentSpeed_; }
void blob::setfoodMax(uint maxFoodCount_) { maxFoodCount = maxFoodCount_; }
void blob::setMergeFlag(void) { mergeFlag = true; }
void blob::setRandomJiggle(uint RandomJiggle_) { RandomJiggle = RandomJiggle_;  }

/****************************************
*				GETTERS		     		*
*****************************************/
double blob::getPosx(void) { return blobPos.x; }
double blob::getPosy(void) { return blobPos.y; }
uint blob::getblobVelocity(void) { return blobVelocity; }
uint blob::getblobRadius(void) { return blobRadius; }
uint blob::getblobDirection(void) { return blobDirection; }
uint blob::getfoodCount(void) { return foodCount; }
uint blob::getblobStatus(void) { return isAliveFlag; }
uint blob::getRandomJiggle(void) { return RandomJiggle; }
bool blob::getMergeFlag(void) { return mergeFlag; }

/****************************************
*			FUNCIONES					*
*****************************************/
void blob::moveBlob()
{
	double i;
	double tempNextx, tempNexty;

	for (i = 0.0; i < blobVelocity; i++)		//for (i = 0.0; i < (blobVelocity* percent_speed); i++)
	{
		tempNextx = (blobPos.x + sin(PI * (double)blobDirection / 180.0));
		tempNexty = (blobPos.y + cos(PI * (double)blobDirection / 180.0));

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
		printf("(%f,%f) -> (%f,%f)\n", blobPos.x, blobPos.y, tempNextx, tempNexty);
	
		setPosx(tempNextx);
		setPosy(tempNexty);
	}
	printf("MOVE\n");
}

void blob::blobDeath(double user_deathProb)
{
	if (deathProb < user_deathProb)
	{
		isAliveFlag = DEAD;
	}
}

int blob::checkRadius(blob& blob2)		//COMO REFERENCIA?
{
	int checking = (((blobPos.x - blob2.getPosx()) * (blobPos.x - blob2.getPosx()) + (blobPos.y - blob2.getPosy()) * (blobPos.y - blob2.getPosy())) < ((double)blobRadius * 4 * (double)blobRadius)); 
	int ret_Val = NOTCLOSE;																											//hacemos el cuadrado de la suma de los radios, por eso r*r*4
	if (checking == 1) 
	{
		if (blobRadius == blob2.getblobRadius())
		{		//Si tienen el mismo radio son del mismo tipo
			ret_Val = MERGE;
		}
		else
		{
			ret_Val = BLOBSALUDO;
		}
	}
	return ret_Val;
}

int blob::checkFood(food* fruta)		//COMO PUNTERO?
{
	int r = blobRadius + fruta->getfoodRadius();
	int result =0; 

	if (((blobPos.x - fruta->getPosx_f()) * (blobPos.x - fruta->getPosx_f()) + (blobPos.y - fruta->getPosy_f()) * (blobPos.y - fruta->getPosy_f())) < (double)r * (double)r)
	{
		result = 1; //case1 SE ACERCA
	}
	else if (((blobPos.x - fruta->getPosx_f()) * (blobPos.x - fruta->getPosx_f()) + (blobPos.y - fruta->getPosy_f()) * (blobPos.y - fruta->getPosy_f())) < ((double)r* (double)r*0.25))
	{//Estan casi superpuestos
		result = 2; //case2 SE LO COME
	}

	return result;
}

void blob::changeDirection(food* fruta)
{
	uint newDirection;
	double change_x = blobPos.x - fruta->getPosx_f();
	double change_y = blobPos.y - fruta->getPosy_f();

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

void blob::blobFeeding(blob* blobArray)
{
	if(foodCount >= maxFoodCount)
	{
		blobBirth(blobArray);			//EXCEPTION READ ACCESS VIOLATION
	}
}

void blob::blobBirth(blob* blobArray)			//Esta sera sobreescrita en cada tipo de blob. 
												//cparametros seran blob* y tipo_de_blob&
{
	uint count = blob::increaseCount();

	blobArray[count] = blob((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (WIDTH)))),
		(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (HEIGHT)))),
		(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)),
		BLOBSPEED,
		BLOBRADIO,
		BLOBMAXFOOD,
		rand()%360);
}

uint blob::increaseCount(void){return ++blobTotalCount; }

void blob::blobMerge(blob* blobArray, uint* array_of_Directions, int mergeTotal)
{ 
	//crear un nuevo blob de tipo evolucionado
	//direccion: suma del promedio entre los blobs obtenida en merge_new_direction
	//posicion es misma que blob J
	//velocidad: promedio de velocidades

	//se determinan en llamada a constructor:
	//radio -> evolucionado
	//maxFoodcount -> evolucionado
	blob::increaseCount();

}


