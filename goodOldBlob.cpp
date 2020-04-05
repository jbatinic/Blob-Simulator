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

goodOldBlob::goodOldBlob(double posx_, double posy_, uint direction_, double percentSpeed_)
{
	//https://stackoverflow.com/questions/686353/random-float-number-generation 
	blobPos.x = posx_;
	blobPos.y = posy_;
	deathProb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	foodCount = 0;
	blobRadius = OLDRADIO;
	percentSpeed = percentSpeed_;
	blobDirection = direction_;
	maxFoodCount = OLDMAXFOOD;
}

//HACE FALTA ESTA FUNCION??
/*
void goodOldBlob::blobBirth(goodOldBlob* blobArray)
{
	uint count = blob::increaseCount();
	blobArray[count] = goodOldBlob(WIDTH, HEIGHT, blobArray[0].getPercentSpeed());
}
*/