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
	babyBlob(uint ancho, uint alto, float percentSpeed_);
	virtual void blobBirth(babyBlob* blob);

};

#endif //BABYBLOP_H