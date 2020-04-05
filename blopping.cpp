#include "blopping.h"


void start_blopping(blob* blobArray, food* fruitArray_)
{
	blop_smellRadius(blobArray, fruitArray_);		//Notese que si se superponen dos o mas blobs y fruta, 
														//un bob la comera y luego se mergiaran o saludaran
//	blop_smellBlob(blobArray);

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

void blob_smellBlob(blob* blobArray)
{
	uint i, j, mergeTotal, newMergeDirection;
	uint* array_of_Directions = (uint*)malloc(sizeof(uint) * blob::blobTotalCount);  //Un array de las direcciones de los blobs con los que el Blob j se mergiara
																							//Sera utilizado para hallar la nueva direccion promedio
	uint* p_2_Directions = array_of_Directions;		//Con este me manejo para guardar las direcciones y el otro lo dejo como esta 
															//para poder hacer free despues

	//PREGUNTAR SI HAY FORMA MAS LINDA DE HACER ESO^

	for (j = 0, mergeTotal = 0, newMergeDirection=0; j < (blob::blobTotalCount); j++)
	{
		p_2_Directions = array_of_Directions;	//Sobreescribimos las direcciones ya guardadas en este array 

		for (i = 0; i < (blob::blobTotalCount); i++)
		{
			if (i != j)			//Si i=j estamos comparando el mismo elemento
			{
				if (do_blob_merge(&(blobArray[j]), blobArray[i]))		//vemos si hay merge entre el blob J y todosl os demas blobs
				{				//Prepara todo para cuando hagamos merge con funcion blobMerge.
					mergeTotal++;		//Con cuantos blobs se va a merge			
					*p_2_Directions++ = blobArray[i].getblobDirection();			//Agrega nueva direccion al array y puntero queda apuntando a proximo elemento de array
					//DESTROY BLOB i 
				}
			}
		}
		if (blobArray[j].getMergeFlag())
		{
			switch (blobArray[j].getblobRadius())
			{
			case BABYRADIO:
				//create new grown blob
				blobArray[j].increaseCount();
				newMergeDirection = 4; //ACA LLAMAR A FUNCION RADOM JIGGLE CON ARRAY OF DIRECTIONS Y MERGE TOTAL PARA SACAR PROMEDIO
				blobArray[blob::blobTotalCount] = grownBlob(blobArray[j].getPosx(), blobArray[j].getPosy(), newMergeDirection, blobArray[j].getPercentSpeed());
				//DESTROY BLOB J
				break;

			case GROWNRADIO:
				//create new old blob 
				blobArray[j].increaseCount();
				newMergeDirection = 4; //ACA LLAMAR A FUNCION RADOM JIGGLE CON ARRAY OF DIRECTIONS Y MERGE TOTAL PARA SACAR PROMEDIO
				blobArray[blob::blobTotalCount] = goodOldBlob(blobArray[j].getPosx(), blobArray[j].getPosy(), newMergeDirection, blobArray[j].getPercentSpeed());
				//DESTROY BLOB J
				break;
			default:
				break;
			}
		}
	}

	free(array_of_Directions);
}

bool do_blob_merge(blob* blob1, blob& blob2)		//DUDA puedo destruir clase si la paso por referencia?
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
