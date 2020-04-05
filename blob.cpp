#include "blob.h"

#define absolute(arg) ( ((arg) >= 0) ? arg : -arg) 

uint blob::blobTotalCount = 0;

/****************************************
*			CONSTRUCTORES				*
*****************************************/
blob::blob(void){
	blobPos.x =0;
	blobPos.y = 0;
	deathProb = 0;
	foodCount = 0;
	blobRadius = 0;
	percentSpeed = 0;
	maxFoodCount = 0;
	blobDirection = 0;
	blobVelocity = 0;
}

blob::blob(uint ancho, uint alto, uint radio_, float percentSpeed_)
{
	blobPos.x = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (ancho)));
	blobPos.y = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (alto)));
	deathProb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	foodCount = 0;
	blobRadius = radio_;
	percentSpeed = percentSpeed_;
	blobDirection = rand()%360;
	blobMergeDirection = blobDirection; 
	mergeFlag = false;
}

/****************************************
*			SETTERS		         		*
*****************************************/
void blob::setDirection(uint blobDirection_){blobDirection = blobDirection_;}
void blob::setDeathProb(float deathProb_) { deathProb = deathProb_; }
void blob::setVelocity(int blobVelocity_) { blobVelocity = blobVelocity_; }
void blob::setPosx(double posx_) { blobPos.x = posx_; }
void blob::setPosy(double posy_) { blobPos.y = posy_; }
void blob::setPosxnext(double posxnext_) { blobPos.xnext = posxnext_; }
void blob::setPosynext(double posynext_) { blobPos.ynext = posynext_; }
void blob::setfoodCount(uint foodCount_) { foodCount = foodCount_; }
void blob::setRadio(uint radio_) { blobRadius = radio_; }
void blob::setPercentSpeed(float percentSpeed_) { percentSpeed = percentSpeed_; }
void blob::setfoodMax(uint maxFoodCount_) { maxFoodCount = maxFoodCount_; }
///void blob::setNewMergeDirection(uint blobMergeDirection_) { blobMergeDirection = ????? }
void blob::setMergeFlag(void) { mergeFlag = true; }

/****************************************
*				GETTERS		     		*
*****************************************/
double blob::getPosx(void) { return blobPos.x; }
double blob::getPosy(void) { return blobPos.y; }
double blob::getPosxnext(void) { return blobPos.xnext; }
double blob::getPosynext(void) { return blobPos.ynext; }
double blob::getPercentSpeed(void) { return percentSpeed; }
uint blob::getblobRadius(void) { return blobRadius; }
uint blob::getblobDirection(void) { return blobDirection; }
uint blob::getfoodCount(void) { return foodCount; }
bool blob::getMergeFlag(void) { return mergeFlag; }

/****************************************
*			FUNCIONES					*
*****************************************/
void blob::moveBlob()
{
	int i;
	double tempNextx = 0, tempNexty = 0;

	for (i = 0; i < blobVelocity; i++)
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
	setPosx(tempNextx);
	setPosy(tempNexty);
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
//	blobArray[count] = blob::blob(WIDTH, HEIGHT,blobArray[0].getblobRadius,blobArray[0].getPercentSpeed());
}

uint blob::increaseCount(void)
{
	blobTotalCount++;
	return blobTotalCount;
}

void blobMerge(blob* blobArray, uint* array_of_Directions, int mergeTotal)
{ 
	//crear un nuevo blob de tipo evolucionado
	//direccion: suma del promedio entre los blobs obtenida en merge_new_direction
	//posicion es misma que blob J
	//velocidad: promedio de velocidades

	blob::increaseCount();

}


