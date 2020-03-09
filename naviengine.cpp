#include "pch.h"
#include <iostream>
#include <conio.h>
#include "graph.h"
#include "basetype.h"
#include "point.h"
#include "edge.h"
#include "strutils.h"
#include "constsize.h"
#include "listfunc.h"
#include "naviengine.h"

NaviEngine::NaviEngine()
{
	onKeyLeft = NULL;
	onKeyRight = NULL;
	onKeyDown = NULL;
	onKeyUp = NULL;
	onKeyF1 = NULL;
	onKeyF2 = NULL;
	onKeyF3 = NULL;
	onKeyF4 = NULL;
	onKeyF5 = NULL;
	onKeyF6 = NULL;
	onKeyEscape = NULL;
	onKeyDelete = NULL;
	onRunBefore = NULL;
	onProcessKeyBefore = NULL;
	flagExit = 0;
	Running = 0;
	Build = NULL;
	Road = NULL;
	ListVert = NULL;
	ListGraph = NULL;
	pmasEdge = NULL;
	pedge = NULL;
	WasOnObject = NULL;
	Routing = new TPoint();
	Routing->setX(1);
	Routing->setY(12);
	Routing->setTyp(ptPavement);
	Routing->setColor(clBlack);
	Routing->setBgColor(clWhite);
	flagG = 0;
	numGraph = 1;
	numEdge = 1;
	xG = 0;
	yG = 0;
	xStart = 0;
	yStart = 0;
	xEnd = 0;
	yEnd = 0;
	direct = 0;

	menuSelected = 0;
	maxLengthMenuItem = 0;

};

NaviEngine::~NaviEngine() {
	delete Build;
	delete ListGraph;
	delete ListVert;
	delete Routing;
	consoleSetColors(clWhite, clBlack);
};

void NaviEngine::Run() {
	doRunBefore();
	Running = 1;
	while (0 != Running) {
		doProcessKeyBefore();
		doProcessKey(_getch());
		doProcessKeyAfter();
	}
	doRunAfter();
};

void NaviEngine::doRunBefore() {
	if (NULL != onRunBefore)
	{
		onRunBefore(this);
	}
};

void NaviEngine::doRunAfter() {
	if (NULL != onRunAfter)
	{
		onRunAfter(this);
	}

};

void NaviEngine::doProcessKeyBefore() {
	if (NULL != onProcessKeyBefore) {
		onProcessKeyBefore(this);
	}
};

void NaviEngine::doProcessKeyAfter() {
	if (NULL != onProcessKeyAfter)
	{
		onProcessKeyAfter(this);
	}
};


void NaviEngine::doProcessKey(int pressedKey) {
	switch (pressedKey) {
	case KEY_ESCAPE: {doKeyEscape(); break; }
	case KEY_DELETE: {doKeyDelete(); break; }
	case KEY_LEFT: {doKeyLeft(); break; }
	case KEY_RIGHT: {doKeyRight(); break; }
	case KEY_UP: {doKeyUp(); break; }
	case KEY_DOWN: {doKeyDown(); break; }
	case KEY_F1: {doKeyF1(); break; }
	case KEY_F2: {doKeyF2(); break; }
	case KEY_F3: {doKeyF3(); break; }
	case KEY_F4: {doKeyF4(); break; }
	case KEY_F5: {doKeyF5(); break; }
	case KEY_F6: {doKeyF6(); break; }
	case KEY_F7: {doKeyF7(); break; }
	case KEY_F8: {doKeyF8(); break; }
	case KEY_F9: {doKeyF9(); break; }
	case KEY_F10: {doKeyF10(); break; }
	
	}

};

void NaviEngine::doKeyEscape() {
	Running = 0;
	if (NULL != onKeyEscape)
	{
		onKeyEscape(this, Running);

	}

};
void NaviEngine::doKeyDelete() {
	if (NULL != onKeyDelete)
	{
		onKeyDelete(this);
	}

};

void NaviEngine::doKeyLeft() {
	if (NULL != onKeyLeft)
	{
		onKeyLeft(this);
	}

};

void NaviEngine::doKeyRight() {
	if (NULL != onKeyRight)
	{
		onKeyRight(this);
	}

};

void NaviEngine::doKeyUp() {
	if (NULL != onKeyUp)
	{
		onKeyUp(this);
	}

};

void NaviEngine::doKeyDown() {
	if (NULL != onKeyDown)
	{
		onKeyDown(this);
	}

};

void NaviEngine::doKeyF1() {
	if (NULL != onKeyF1)
	{
		onKeyF1(this);
	}
};

void NaviEngine::doKeyF2() {
	if (NULL != onKeyF2)
	{
		onKeyF2(this);
	}
};

void NaviEngine::doKeyF3() {
	if (NULL != onKeyF3)
	{
		onKeyF3(this);
	}

};

void NaviEngine::doKeyF4() {
	if (NULL != onKeyF4)
	{
		onKeyF4(this);
	}

};

void NaviEngine::doKeyF5() {
	if (NULL != onKeyF5)
	{
		onKeyF5(this);
	}
};

void NaviEngine::doKeyF6() {
	if (NULL != onKeyF6)
	{
		onKeyF6(this);
	}
};

void NaviEngine::doKeyF7() {
	if (NULL != onKeyF7)
	{
		onKeyF7(this);
	}
};

void NaviEngine::doKeyF8() {
	if (NULL != onKeyF8)
	{
		onKeyF8(this);
	}
};

void NaviEngine::doKeyF9() {
	if (NULL != onKeyF9)
	{
		onKeyF9(this);
	}
};

void NaviEngine::doKeyF10() {

};


void NaviEngine::doKeyEnter() {
	if (NULL != onKeyEnter)
	{
		onKeyEnter(this);
	}
};
int NaviEngine::getRunning() {
	return Running;
};

void NaviEngine::setRunning(const int value) {
	if (value != Running) {
		Running = value;
	}
}
void NaviEngine::printMenu()
{
	const char *menu[] = {
		"       Меню:         \n"
	,"1.Создать карту и граф\n"
   ,"2.Найти кратчайший маршрут между заданными точками\n"
   ,"3.Выход\n"
	};

	maxx = lengthX;
	maxy = lengthY;


	int i;
	for (i = 0; i < menuCount; i++) {
		if (strlen(menu[i]) > maxLengthMenuItem) {
			maxLengthMenuItem = strlen(menu[i]);
		}
	}
	short menuX = maxy / 2;
	short menuY = 2;
	for (i = 0; i < menuCount; i++) {
		if (i == menuSelected) {
			consoleSetColors(clWhite, clRed);
		}
		else {
			consoleSetColors(clWhite, clBlack);
		}
		consoleGotoXY(menuX, (menuY + i));
		printf("%s", menu[i]);

	}
};