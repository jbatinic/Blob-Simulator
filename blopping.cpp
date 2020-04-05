#include "blopping.h"


void start_blopping(blob* blopArray, food* fruitArray_)
{
	blop_smellRadius(blopArray, fruitArray_);
	blop_merge();

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

void blop_merge(blob* blobArray);
{
	int x1, x2, y1, y2;
	for (j = 0; j < (blob::blobTotalCount); j++)
	{
		for (i = 0;i < (blob::blobTotalCount);i++) {
			x1 = bloblArray[j].getPosx();
			x2 = bloblArray[i].getPosx();
			y1 = bloblArray[j].getPosy();
			y2 = bloblArray[i].getPosy();
			if (x1 == x2 && y1 == y2) {
				do_blob_merge(blobArray,j,i);
			}
		}
	}
}


void do_blob_merge(blob* blobArray,uint j, uint i){
	if (blobArray[j].getblobRadius() && blobArray[i].getblobRadius()) {
		switch (blobArray[j].getblobRadius()) {
		case BABYRADIO:
			grownBlob.blobBirth();
			break;
		case GROWNRADIO:
			goodOldBlob.blobBirth();
			break;
		case OLDRADIO:
			break;
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