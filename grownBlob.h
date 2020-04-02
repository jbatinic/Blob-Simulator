#ifndef GROWNBLOB
#define GROWNBLOB

#include "blob.h"
#define GROWNRADIO 3
#define GROWNMAXFOOD 3 //nO ME acuerdo estos max values

class grownBlob :
	public blob
{
public:
	grownBlob();
	grownBlob(uint speed, uint ancho, uint alto, uint radio_, float percentSpeed_);

};

#endif //GROWNBLOB_

