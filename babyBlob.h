#ifndef BABYBLOP_H
#define BABYBLOP_H

#include "blob.h"
#define BABYRADIO 4
#define BABYMAXFOOD 3

class babyBlob :
	public blob
{
public:
	babyBlob();
	babyBlob(uint ancho, uint alto, double percentSpeed_);
//	virtual void blobMerge(babyBlob* blobArray, uint* array_of_Directions, int mergeTotal);
	virtual void blobBirth(babyBlob* blob);

};

#endif //BABYBLOP_H