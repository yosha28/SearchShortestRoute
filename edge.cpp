#include "pch.h"
#include <iostream>
#include "constsize.h"
#include "strutils.h"
#include "basetype.h"
#include "edge.h"
#include "consolrut.h"
#include<math.h>

Edge::Edge() {
	Btype::Btype();
	setSymb('.');
	x2 = 0;
	y2 = 0;
	length = 0;
}

Edge::~Edge()
{
}

EdgeType Edge::getTyp() {
	return typ;
};

void Edge::setTyp(const EdgeType TYP) {
	if (TYP != typ) {
		Erase();
		typ = TYP;
	}
};

char Edge::getSymb() {
	char s = Btype::getSymb();
	switch (getTyp()) {
	case ptStarttoEnd: { s = 'S'; break; }
	case ptRevers: { s = 'R'; break; }

	}
	return s;
};

void Edge::SaveToFile(FILE *fileHandle) {
	fprintf_s(fileHandle, "%d|%d|%d|%d|%d|%d|%d|%c|%d\n", id, getX(), getY(), x2, y2, getColor(), getBgColor(), getSymb(), (int)typ);
}

int Edge::LoadFromStr(char *buffer) {
	int result = 0;
	char *p_block = (char *)malloc(count * sizeof(char));
	char *parser = buffer;
	parser = parseItem(parser, '|', p_block); id = atoi(p_block);
	parser = parseItem(parser, '|', p_block); x = atoi(p_block);
	parser = parseItem(parser, '|', p_block); y = atoi(p_block);
	parser = parseItem(parser, '|', p_block); x2 = atoi(p_block);
	parser = parseItem(parser, '|', p_block); y2 = atoi(p_block);
	parser = parseItem(parser, '|', p_block); color = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); bgcolor = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); symb = *p_block;
	parser = parseItem(parser, '\n', p_block); typ = (EdgeType)atoi(p_block);
	free(p_block);
	return result;
}
int Edge::Contains(const short X, const short Y, const short X2, const short Y2) {//наличие конкретного ребра в списке
	int result = 0;
	if (((x == X) && (y == Y) && (x2 == X2) && (y2 == Y2)) || ((x2 == X) && (y2 == Y) && (x == X2) && (y == Y2))) {
		result = 1;
	}
	return result;
}
int Edge::ContainsVertEdge(const short X, const short Y) {//одна координата на ребере
	int result = 0;
	if (((x == X) && (y == Y)) || ((x2 == X) && (y2 == Y))) {
		result = 1;
	}


	return result;
}
void Edge::Print()
{
	consoleSetColors(clRed, clRed);
	if (x != x2)
	{
		for (int i = x; i < x2; i++)
		{
			consoleGotoXY(i, y);
			consoleSetColors(clRed, clRed);
			printf("%c", getSymb());

		}
		for (int i = x2; i < x; i++)
		{
			consoleGotoXY(i, y);
			consoleSetColors(clRed, clRed);
			printf("%c", getSymb());

		}
	}
	else if (y != y2)
	{
		for (int i = y; i < y2; i++)
		{
			consoleGotoXY(x, i);
			consoleSetColors(clRed, clRed);
			printf("%c", getSymb());

		}
		for (int i = y2; i < y; i++)
		{
			consoleGotoXY(x, i);
			consoleSetColors(clRed, clRed);
			printf("%c", getSymb());

		}
	}

}
