#ifndef EDGE_H
#define EDGE_H

#include "basetype.h"

enum EdgeType {
	ptStarttoEnd = 0
	, ptRevers = 2
	
};

class Edge :public Btype {
private:
	
public:
	short x2;
	short y2;
	int length;
	Edge();
	virtual ~Edge();
	virtual EdgeType getTyp();
	virtual void setTyp(const EdgeType TYP);
	virtual char getSymb();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
	virtual int Contains(const short X, const short Y, const short X2, const short Y2);
	 virtual int ContainsVertEdge(const short X, const short Y);
	 virtual void Print();
protected:
	//virtual int ContainsEd(const short X, const short Y, const short X2, const short Y2);
	EdgeType typ;
};

#endif
