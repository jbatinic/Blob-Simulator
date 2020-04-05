#ifndef GOODOLDBLOB_H
#define GOODOLDBLOB_H

#include "blob.h"
#define OLDRADIO 8
#define OLDMAXFOOD 5

class goodOldBlob :
	public blob
{
public:
	goodOldBlob();
	goodOldBlob(double posx_, double posy_, uint direction_, double percentSpeed_);
//	virtual void blobBirth(goodOldBlob* blob);
};


#endif //GOODOLDBLOB_h
