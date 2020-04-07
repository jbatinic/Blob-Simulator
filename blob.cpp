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
	blobPos.x = WIDTH;
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
void blob::setVelocity(double blobVelocity_) { blobVelocity = blobVelocity_; }
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
double blob::getblobVelocity(void) { return blobVelocity; }
uint blob::getblobRadius(void) { return blobRadius; }
uint blob::getblobDirection(void) { return blobDirection; }
uint blob::getfoodCount(void) { return foodCount; }
uint blob::getblobStatus(void) { return isAliveFlag; }
uint blob::getRandomJiggle(void) { return RandomJiggle; }
bool blob::getMergeFlag(void) { return mergeFlag; }
uint blob::getbitmapSize(void) { return bitmapSize; }

/****************************************
*			FUNCIONES					*
*****************************************/
void blob::moveBlob()
{
	double i;
	double tempNextx, tempNexty;
		
		//intf("%f \n", blobVelocity);
		tempNextx = (blobPos.x + cos(PI * ((double)blobDirection / 180.0)) * blobVelocity * percentSpeed);
		tempNexty = (blobPos.y + sin(PI * ((double)blobDirection / 180.0)) * blobVelocity * percentSpeed);

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
		//printf("\n\nDIRECCION DEL BLOB\n");
		//printf("(%f,%f) -> (%f,%f)\n", blobPos.x, blobPos.y, tempNextx, tempNexty);
		
	
		setPosx(tempNextx);
		setPosy(tempNexty);
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
	int blobsRadius = bitmapSize + blob2.getbitmapSize(); 

	int checking = (((blobPos.x - blob2.getPosx()) * (blobPos.x - blob2.getPosx()) + (blobPos.y - blob2.getPosy()) * (blobPos.y - blob2.getPosy())) < ((double)(blobsRadius*blobsRadius))); 
	int ret_Val = NOTCLOSE;																											//hacemos el cuadrado de la suma de los radios, por eso r*r*4
	if (checking == 1) 
	{
		if (blobRadius == blob2.getblobRadius())
		{		//Si tienen el mismo radio son del mismo tipo
			printf("MERGE\n");
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

	if (((blobPos.x - fruta->getPosx_f()) * (blobPos.x - fruta->getPosx_f()) + (blobPos.y - fruta->getPosy_f()) * (blobPos.y - fruta->getPosy_f())) < ((double)r* (double)r*0.15))
	{//Estan casi superpuestos
		result = 2; //case2 SE LO COME
	}
	else if (((blobPos.x - fruta->getPosx_f()) * (blobPos.x - fruta->getPosx_f()) + (blobPos.y - fruta->getPosy_f()) * (blobPos.y - fruta->getPosy_f())) < (double)r * (double)r)
	{
		result = 1; //case1 SE ACERCA
	}


	return result;
}

void blob::changeDirection(food* fruta)
{
	float newDirection;
	double change_x = blobPos.x - fruta->getPosx_f();
	double change_y = blobPos.y - fruta->getPosy_f();


	newDirection = atan2(change_y , change_x);	

	newDirection = ( (newDirection * (float)180 ) / PI );

	newDirection += 180;
	
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




