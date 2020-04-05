#ifndef GROWNBLOB
#define GROWNBLOB

#include "blob.h"
#define GROWNRADIO 16
#define GROWNMAXFOOD 4 

class grownBlob :
	public blob
{
public:
	grownBlob();
	grownBlob(double posx_, double posy_, uint direction_, double percentSpeed_);
//	virtual void blobMerge(grownBlob* blobArray, uint* array_of_Directions, int mergeTotal);
//	virtual void blobBirth(grownBlob* blob);
};

#endif //GROWNBLOB_

