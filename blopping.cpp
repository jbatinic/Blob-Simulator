#include "blopping.h"


void start_blopping(blob* blobArray, food* fruitArray_, float user_deathProb, float v_max, int simulation_mode, int smell_Radius)
{
	int j, i;

	blob_smellRadius(blobArray, fruitArray_);		//Notese que si se superponen dos o mas blobs y fruta, 
														//un bob la comera y luego se mergiaran o saludaran
	blob_smellBlob(blobArray);
	if (simulation_mode == 1)
	{
		for (i = 0; i < 700; i++)             //Seteamos velocidades para todos los existentes y futuros blobs para tenerlos listo en blobBirth
		{
			blobArray[i].setVelocity(v_max);
		}
	}

	for (j = 0; j<(blob::blobTotalCount); j++)
	{
		if (blobArray[j].getblobStatus())
		{
			blobArray[j].moveBlob();
			blobArray[j].blobDeath(user_deathProb);
		}
		
	}
}

/**************************************************************
*															  *
***************************************************************/

void blob_smellRadius(blob* blobArray, food* frutaArray)
{
	uint i, j, blobCount;
	blobCount = blob::blobTotalCount;
	for (j = 0; j < blobCount; j++)
	{
		for (i = 0; i < (frutaArray[i].getfoodTotal()); i++)
		{

			switch ((blobArray[j].checkFood(&(frutaArray[i]))))
			{
			case 1:

				blobArray[j].changeDirection(&(frutaArray[i]));

				break;
			case 2:
				blobArray[j].setfoodCount((blobArray[j].getfoodCount()) + 1);
				blobbingFeeding(blobArray, j);

				//cambiamos el lugar de la fruta recien comida por uno random entre la posicion x e y de donde acaba de ser comida
				frutaArray[i].setPosx_f(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / blobArray[rand() % blobCount].getPosx())));
				frutaArray[i].setPosy_f(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / blobArray[rand() % blobCount].getPosy())));
				break;
			default:
				break;
			}
		}
	}
}

void blobbingFeeding(blob* blobArray, uint j)
{
	if ((blobArray[j].getfoodCount()) >= (blobArray[j].getMaxfoodCount()))
	{
		blob::increaseCount();
		blobArray[blob::blobTotalCount].blobBirth((babyBlob*)blobArray);			
		blobArray[j].setfoodCount(0);
	}

}

void blob_smellBlob(blob* blobArray)
{
	uint i, j, mergeTotal,newMergeDirection, newMergeVelocity;
	//printf("blob::blobTotalCount = %d\n", blob::blobTotalCount);
	uint countTemp = blob::blobTotalCount;
	for (j = 0, mergeTotal=0, newMergeDirection=0, newMergeVelocity=0; j < countTemp; j++)
	{
		for (i = countTemp ; i > 0 ; i--)
		{
			if (i != j)			//Si i=j estamos comparando el mismo elemento
			{
				if (do_blob_merge(&(blobArray[j]), blobArray[i]))		//vemos si hay merge entre el blob J y todosl os demas blobs
				{				//Prepara todo para cuando hagamos merge con funcion blobMerge.
					mergeTotal++;
					newMergeDirection += blobArray[i].getblobDirection();
					newMergeVelocity += blobArray[i].getblobVelocity();
					blobArray[i].setblobStatus(DEAD);//matamos a blob i 
				}
			}
		}

		if ((blobArray[j].getblobStatus() == ALIVE) && (blobArray[j].getMergeFlag() == true))
		{
			blobArray[j].increaseCount();
			newMergeDirection += blobArray[j].getblobDirection();
			newMergeVelocity += blobArray[j].getblobVelocity();

			newMergeDirection = randomJiggle(newMergeDirection, blobArray[j].getRandomJiggle());

			switch (blobArray[j].getblobRadius())
			{
			case BABYRADIO:
				//create new grown blob
				blobArray[blob::blobTotalCount] = grownBlob(blobArray[j].getPosx(), blobArray[j].getPosy(), newMergeDirection, newMergeVelocity / mergeTotal);
				blobArray[j].setblobStatus(DEAD);//Matamos a blob J
				break;
				
			case GROWNRADIO:
				//create new old blob 
				blobArray[blob::blobTotalCount] = goodOldBlob(blobArray[j].getPosx(), blobArray[j].getPosy(), newMergeDirection, newMergeVelocity / mergeTotal);
				blobArray[j].setblobStatus(DEAD);//matamos a blob J
				break;
			default:
				break;
			}
		}
		else
		{ 
			//printf("no merge \n");
		}
			
	}
}

uint randomJiggle(uint newDirection_, uint randomJiggle)
{
	uint newDirection = newDirection_ * randomJiggle / 2;
	if (newDirection > 360)
		newDirection -= 360;
	return newDirection;
}

bool do_blob_merge(blob* blob1, blob& blob2)		
{
	bool return_val = false;
	switch (blob1->checkRadius(blob2))  //Vemos si se superponen los bitmaps
	{ 
	case MERGE:
		if (blob1->getblobRadius() != OLDRADIO)
		{
			blob1->setMergeFlag();
			return_val = true;
		}
		else
		{
		//CALL TO ALLEGRO SALUDO FUNCTION
		}
		break;

	case BLOBSALUDO:
		//CALL TO ALLEGRO SALUDO FUNCTION
		break;

	case NOTCLOSE:
		break;
	}
	return return_val;
}

