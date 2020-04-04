#include "goodOldBlob.h"

goodOldBlob::goodOldBlob() {
	blobPos.x = 0;
	blobPos.y = 0;
	deathProb = 0;
	foodCount = 0;
	blobRadius = 0;
	percentSpeed = 0;
	blobDirection = 0;
	maxFoodCount = 0;
}

goodOldBlob::goodOldBlob(uint ancho, uint alto, double percentSpeed_)
{
	//https://stackoverflow.com/questions/686353/random-float-number-generation 
	blobPos.x = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (ancho)));
	blobPos.y = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (alto)));
	deathProb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	foodCount = 0;
	blobRadius = OLDRADIO;
	percentSpeed = percentSpeed_;
	blobDirection = rand() % 360;
	maxFoodCount = OLDMAXFOOD;
}

void goodOldBlob::blobBirth(goodOldBlob* blobArray)
{
	uint count = blob::increaseCount();
	blobArray[count] = goodOldBlob(WIDTH, HEIGHT, blobArray[0].getPercentSpeed());
}