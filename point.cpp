#include "pch.h"
#include <iostream>
#include "constsize.h"
#include "strutils.h"
#include "basetype.h"
#include "point.h"
#include "consolrut.h"

TPoint::TPoint() {
	Btype::Btype();
	setSymb('.');
	size = 0;
//	strcpy_s(name, 20, "TPoint");
	
}

TPoint::~TPoint()
{
}

TPointType TPoint::getTyp() {
	return typ;
};

void TPoint::setTyp(const TPointType TYP) {
	if (TYP != typ) {
		Erase();
		typ = TYP;
	}
};

char TPoint::getSymb() {
	char s = Btype::getSymb();
	switch (getTyp()) {
	case ptBank: { s = 'B';color= clBlack, bgcolor = clBlue; break; }
	case ptHouse: { s = 'H'; break; }
	case ptCafe: { s = 'C'; break; }
	case ptShop: { s = 'S'; break; }
	case ptTank: { s = 'T'; break; }
	case ptPavement: { s = 'R'; break; }
	case ptTrend: { s = '-'; break; }
	case ptTree: {s = 'W'; break; }
	case ptCrossroad: {s = '+'; break; }
	}
	return s;
};

void TPoint::SaveToFile(FILE *fileHandle) {

	fprintf_s(fileHandle, "%d|%d|%d|%d|%d|%c|%d|%d\n", id, getX(), getY(), getColor(), getBgColor(), getSymb(), (int)typ, size);
	
}


int TPoint::LoadFromStr(char *buffer) {
	int result = 0;
	char *p_block = (char *)malloc(count * sizeof(char));
	char *parser = buffer;
//	parser = parseItem(parser, '|', p_block);
	parser = parseItem(parser, '|', p_block); id = atoi(p_block);
	parser = parseItem(parser, '|', p_block); x = atoi(p_block);
	parser = parseItem(parser, '|', p_block); y = atoi(p_block);
	parser = parseItem(parser, '|', p_block); color = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); bgcolor = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); symb = *p_block;
	parser = parseItem(parser, '|', p_block); typ = (TPointType)atoi(p_block);
	parser = parseItem(parser, '\n', p_block); size = atoi(p_block);
	
	free(p_block);
	return result;
}


