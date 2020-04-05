#include "grownBlob.h"

grownBlob::grownBlob() {
	blobPos.x = 0;
	blobPos.y = 0;
	deathProb = 0;
	foodCount = 0;
	blobRadius = 0;
	percentSpeed = 0;
	blobDirection = 0;
	maxFoodCount = 0;
	isAliveFlag = 0;
}

grownBlob::grownBlob(double posx_, double posy_, uint direction_, double Speed_)
{
	//https://stackoverflow.com/questions/686353/random-float-number-generation 
	blobPos.x = posx_;
	blobPos.y = posy_;
	deathProb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	foodCount = 0;
	blobRadius = GROWNRADIO;
	blobVelocity = Speed_;
	blobDirection = direction_;
	maxFoodCount = GROWNMAXFOOD;
	isAliveFlag = ALIVE;
}

//HACE FALTA ESTA FUNCION?
/*
void grownBlob::blobBirth(grownBlob* blobArray)
{
	uint count = blob::increaseCount();
	blobArray[count] = grownBlob(blobArray[0].getPercentSpeed());
}
*/
