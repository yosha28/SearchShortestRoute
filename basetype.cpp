#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "constsize.h"
#include "strutils.h"
#include "basetype.h"
#include "consolrut.h"

Btype::Btype() {
	x = 0;
	y = 0;
	id = 0;
	symb = ' ';
	color = clBlack;
	bgcolor = clBlack;

}

Btype::~Btype() {
	Erase();
}

int Btype::getX() {
	return x;
};

void Btype::setX(const int X) {
	if (X != x) {
	//	Erase();
		x = X;
	}
};

int Btype::getY() {
	return y;
};

void Btype::setY(const int Y) {
	if (Y != y) {
	//	Erase();
		y = Y;
	}
};

char Btype::getSymb() {
	return symb;
};


void Btype::setSymb(const char SYMB) {
	if (SYMB != symb) {
	//	Erase();
		symb = SYMB;
	}
};

ConsoleColors Btype::getColor() {
	return color;
};

void Btype::setColor(const ConsoleColors COLOR) {
	if (COLOR != color) {
	//	Erase();
		color = COLOR;
	}
};

ConsoleColors Btype::getBgColor() {
	return bgcolor;
};

void Btype::setBgColor(const ConsoleColors BGCOLOR) {
	if (BGCOLOR != bgcolor) {
		//Erase();
		bgcolor = BGCOLOR;
	}
};

void Btype::Print() {
	consoleSetColors(getColor(), getBgColor());
	consoleGotoXY(getX(), getY());
	printf("%c", getSymb());
}

void Btype::PrintText() {
	//consoleSetColors(clWhite, clBrown);
	consoleGotoXY(getX(), getY());
	printf("%d", id);
}


void Btype::Erase() {
	consoleSetColors(clBlack, clBlack);
	consoleGotoXY(getX(), getY());
	printf(" ");
}

int Btype::Contains(const short X, const short Y) {
	int result = 0;
	if ((x == X) && (y == Y)) {
		result = 1;
	}
	return result;
}

void Btype::SaveToFile(FILE *fileHandle) {
	fprintf_s(fileHandle, "TGEOM|%d|%d|%d|%d|%d|%c\n", id, x, y, (int)color, (int)bgcolor, getSymb());
}

int Btype::LoadFromStr(char *buffer) {
	int result = 0;
	char *p_block = (char *)malloc(count * sizeof(char));
	char *parser = buffer;
	parser = parseItem(parser, '|', p_block);
	parser = parseItem(parser, '|', p_block); id = atoi(p_block);
	parser = parseItem(parser, '|', p_block); x = atoi(p_block);
	parser = parseItem(parser, '|', p_block); y = atoi(p_block);
	parser = parseItem(parser, '|', p_block); color = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); bgcolor = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '\n', p_block); symb = *p_block;
	free(p_block);
	return result;
}
