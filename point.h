#ifndef POINT_H
#define POINT_H

#include "basetype.h"

enum TPointType {
	ptUnknown = 0
	, ptBank = 1
	, ptHouse = 2
	, ptCafe = 3
	, ptShop = 4
	, ptTank = 5
	, ptPavement = 6
	, ptTrend = 7
	, ptTree = 8
	, ptCrossroad = 9
};

class TPoint :public Btype {
private:
public:
	short size;
	TPoint();
	virtual ~TPoint();
	virtual TPointType getTyp();
	virtual void setTyp(const TPointType TYP);
	virtual char getSymb();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
	
protected:
	TPointType typ;
};

#endif
