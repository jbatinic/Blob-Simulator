#ifndef BABYBLOP_H
#define BABYBLOP_H

#include "blob.h"
#define BABYRADIO 2
#define BABYMAXFOOD 3

class babyBlob :
	public blob
{
public:
	babyBlob();
	babyBlob(uint speed, uint ancho, uint alto, uint radio_, float percentSpeed_);
};

#endif //BABYBLOP_H