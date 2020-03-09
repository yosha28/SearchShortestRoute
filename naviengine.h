#ifndef NAVIENGINE_H
#define NAVIENGINE_H

#include "pch.h"
#include "graph.h"
#include "basetype.h"
#include "point.h"
#include "edge.h"
#include "strutils.h"
#include "constsize.h"
#include "listfunc.h"
#include <iostream>

class NaviEngine;
typedef void(*funcOnKey)(NaviEngine *Sender);
typedef void(*funcOnEscape)(NaviEngine *Sender, int _running);

class NaviEngine {

private:
	int Running;



public:

	TPoint *Routing;
	list2 *Build;
	list2 *Road;
	list2 *WasOnObject;
	graph *ListGraph, *pmasEdge, *pedge;
	vertex *ListVert;

	
	int flagG;
	short xG, yG, numGraph, numEdge,xStart,xEnd,yStart,yEnd;
	int menuSelected;
	int flagExit;
	int maxLengthMenuItem;
	int direct;
	short maxx, maxy;
	const char *menu[menuCount];
	NaviEngine();
	~NaviEngine();
	void Run();
	int  getRunning();
	void setRunning(const int value);
	void printMenu();
	funcOnKey onRunAfter;
	funcOnKey onRunBefore;
	funcOnKey onProcessKeyBefore;
	funcOnKey onProcessKeyAfter;
	funcOnKey onKeyLeft;
	funcOnKey onKeyRight;
	funcOnKey onKeyDown;
	funcOnKey onKeyUp;
	funcOnKey onKeyF1;
	funcOnKey onKeyF2;
	funcOnKey onKeyF3;
	funcOnKey onKeyF4;
	funcOnKey onKeyF5;
	funcOnKey onKeyF6;
	funcOnKey onKeyF7;
	funcOnKey onKeyF8;
	funcOnKey onKeyF9;
	funcOnKey onKeyF10;
	funcOnKey onKeyDelete;
	funcOnKey onKeyEnter;
	funcOnEscape onKeyEscape;

protected:
	virtual void doRunBefore();
	virtual void doRunAfter();
	virtual void doProcessKeyBefore();
	virtual void doProcessKeyAfter();
	virtual void doProcessKey(int pressedKey);
	virtual void doKeyEscape();
	virtual void doKeyEnter();
	virtual void doKeyDelete();
	virtual void doKeyLeft();
	virtual void doKeyRight();
	virtual void doKeyUp();
	virtual void doKeyDown();
	virtual void doKeyF1();
	virtual void doKeyF2();
	virtual void doKeyF3();
	virtual void doKeyF4();
	virtual void doKeyF5();
	virtual void doKeyF6();
	virtual void doKeyF7();
	virtual void doKeyF8();
	virtual void doKeyF9();
	virtual void doKeyF10();
	
};

#endif