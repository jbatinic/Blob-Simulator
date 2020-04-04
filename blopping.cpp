#include "blopping.h"


void start_blopping(blob* blopArray, food* fruitArray_)
{
	blop_smellRadius(blopArray, fruitArray_);

}

/**************************************************************
*															  *
***************************************************************/
void blop_smellRadius(blob* blobArray, food* frutaArray)
{
	uint i, j;
	for (j = 0; j < (blob::blobTotalCount); j++)
	{
		for (i = 0; i < (frutaArray[i].getfoodTotal()); i++)
		{
			switch ((blobArray[j].checkFood(&(frutaArray[i]))))
			{
			case 1:
				blobArray[j].changeDirection(&(frutaArray[i]));
				printf("\nCHANGED DIRECTION of blob %u\n",j);
				break;
			case 2:
				blobArray[j].setfoodCount((blobArray[j].getfoodCount()) + 1);
				blobArray[j].blobFeeding(blobArray);	
				printf("\n CASE EATEN\n");
				//frutaArray[i].byeFruta();				habria que hacer un destructor?
				break;
			default:
				break;
			}
		}
	}
}

/*
blop_smellBlob(blob* blobArray)
{
	uint i, j;
	for (j = 0; j < (blob::blobTotalCount); j++)
	{
		for (i = 0; i < (blob::blobTotalCount); i++)
		{
			if (i != j)			//Si i=j estamos comparando el mismo elemento
			{
				if (blob::checkFood(blobArray[j], blobArray[i]))		//Devuelve 1 si un blob del mismo tipo esta en el radio
				{

				}
			}
		}
	}
}
*/