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
}

grownBlob::grownBlob(uint ancho, uint alto,double percentSpeed_)
{
	//https://stackoverflow.com/questions/686353/random-float-number-generation 
	blobPos.x = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (ancho)));
	blobPos.y = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (alto)));
	deathProb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	foodCount = 0;
	blobRadius = GROWNRADIO;
	percentSpeed = percentSpeed_;
	blobDirection = rand() % 360;
	maxFoodCount = GROWNMAXFOOD;
}

void grownBlob::blobBirth(grownBlob* blobArray)
{
	uint count = blob::increaseCount();
	blobArray[count] = grownBlob(WIDTH, HEIGHT, blobArray[0].getPercentSpeed());
}