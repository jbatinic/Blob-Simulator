#ifndef GOODOLDBLOB_H
#define GOODOLDBLOB_H

#include "blob.h"
#define OLDRADIO 5
#define OLDMAXFOOD 5 //nO ME acuerdo estos max values

class goodOldBlob :
	public blob
{
public:
	goodOldBlob();
	goodOldBlob(uint speed, uint ancho, uint alto, uint radio_, float percentSpeed_);

};

#endif //GOODOLDBLOB_h
