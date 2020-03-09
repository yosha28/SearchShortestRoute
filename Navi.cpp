#include "pch.h"
#include <iostream>
#include <conio.h>
#include"strutils.h"
#include"basetype.h"
#include "consolrut.h"
#include "listfunc.h"
#include "point.h"
#include"constsize.h"
#include"graph.h"
#include "edge.h"
#include "naviengine.h"



void routingOnKeyLeft(NaviEngine *Sender)
{
	if ((Sender->Routing->getX() > 1) && (1 == list2_contains(Sender->Road, Sender->Routing->getX() - 1, Sender->Routing->getY())))
		Sender->Routing->setX(Sender->Routing->getX() - 1);
}

void routingOnKeyRight(NaviEngine *Sender)
{
	if ((Sender->Routing->getX() < lengthX) && (1 == list2_contains(Sender->Road, Sender->Routing->getX() + 1, Sender->Routing->getY())))
		Sender->Routing->setX(Sender->Routing->getX() + 1);
}

void routingOnKeyUp(NaviEngine *Sender)
{
	if ((Sender->Routing->getY() > 2) && (1 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY() - 1)))
		Sender->Routing->setY(Sender->Routing->getY() - 1);

}

void routingOnKeyDown(NaviEngine *Sender)
{
	if ((Sender->Routing->getY() < lengthY) && (1 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY() + 1)))
		Sender->Routing->setY(Sender->Routing->getY() + 1);
}

void routingOnKeyF1(NaviEngine *Sender)
{
	if (1 == vertex_contains(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY()))
	{
		Sender->ListVert = vertex_findxy(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY());

		Sender->xStart = Sender->Routing->getX();
		Sender->yStart = Sender->Routing->getY();
		consoleGotoXY(10, 9);
		consoleSetColors(clBlack, clBlack);
		printf("                                                                              ");
	}
	else
	{
		consoleSetColors(clLightRed, clBlack);
		consoleGotoXY(10, 9);
		printf("Выберите точку на перекрестке и нажмите F1\n");

	}

}

void routingOnKeyF2(NaviEngine *Sender)
{

		if (1 == vertex_contains(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY()))
		{
			Sender->xEnd = Sender->Routing->getX();
			Sender->yEnd = Sender->Routing->getY();
			if (Sender->xEnd == Sender->xStart && Sender->yEnd == Sender->yStart)
			{
				consoleGotoXY(10, 9);//что бы скрыть напечатанное ранее
				consoleSetColors(clLightRed, clBlack);
				printf(" Вы стоите на месте.Выберите другую точку на карте                                   ");
			}
			else
			{
				consoleGotoXY(10, 9);//что бы скрыть напечатанное ранее
				consoleSetColors(clBlack, clBlack);
				printf("                                                                                ");
				
			}
		}
		else
		{
			consoleSetColors(clLightRed, clBlack);
			consoleGotoXY(10, 9);
			printf("Выберите точку на перекрестке и нажмите F2\n");
		}

	
}

void routingOnKeyF3(NaviEngine *Sender)//вывод коротких путей
{
	int flag = 0;
	graph *p = NULL;

	if (Sender->xStart == NULL && Sender->yStart == NULL || Sender->xEnd == NULL && Sender->yEnd == NULL)
	{
		consoleSetColors(clLightRed, clBlack);
		consoleGotoXY(10, 9);
		printf("Выберите точки начала маршрута и конца на перекрестке\n");
	}
	else
	{
		Sender->direct = find_direct(Sender->xStart, Sender->yStart, Sender->xEnd, Sender->yEnd);

		for (int i = 0; i < 1; i++)
		{
			do {
				if (flag == 0 && Sender->direct != 0)
				{

					Sender->pedge = graph_gotofirst(Sender->ListGraph);
					p = findNoVisitEdge(Sender->pedge, Sender->xStart, Sender->yStart, Sender->xEnd, Sender->yEnd, Sender->direct, Sender->pmasEdge);
					Sender->pmasEdge = graph_gotolast(Sender->pmasEdge);
					Sender->pmasEdge = map_add_Edge(Sender->pmasEdge, p->btype->getX(), p->btype->getY(), p->btype->x2, p->btype->y2, p->btype->getTyp(), p->btype->getColor(), p->btype->getBgColor());
					Sender->pedge = graph_findxy(Sender->pedge, p->btype->getX(), p->btype->getY(), p->btype->x2, p->btype->y2);
					Sender->pedge->btype->setColor(clRed);
					Sender->pedge = graph_gotofirst(Sender->ListGraph);
					flag = 1;
					p = NULL;
				}
				else 
				{

					Sender->pedge = graph_gotofirst(Sender->ListGraph);
					p = findNoVisitEdge(Sender->pedge, Sender->pmasEdge->btype->x2, Sender->pmasEdge->btype->y2, Sender->xEnd, Sender->yEnd, Sender->direct, Sender->pmasEdge);
					Sender->pmasEdge = graph_gotolast(Sender->pmasEdge);
					Sender->pmasEdge = map_add_Edge(Sender->pmasEdge, p->btype->getX(), p->btype->getY(), p->btype->x2, p->btype->y2, p->btype->getTyp(), p->btype->getColor(), p->btype->getBgColor());
					Sender->direct = find_direct(Sender->pmasEdge->btype->x2, Sender->pmasEdge->btype->y2, Sender->xEnd, Sender->yEnd);
					Sender->pedge = graph_findxy(Sender->pedge, p->btype->getX(), p->btype->getY(), p->btype->x2, p->btype->y2);
					Sender->pedge->btype->setColor(clRed);
					Sender->pedge = graph_gotofirst(Sender->ListGraph);
					p = NULL;
				}
			} while (0 != Sender->direct);
			flag = 0;
		}

		graph_print(Sender->pmasEdge);

		Sender->pmasEdge = NULL;
		Sender->Routing->setX(1);
		Sender->Routing->setY(12);

	}


}

void routingOnRunBefore(NaviEngine *Sender) {


	list2_print(Sender->Build);
	list2_print(Sender->Road);
}

void routingOnProcessKeyBefore(NaviEngine *Sender) {

	consoleGotoXY(0, 3);
	consoleSetColors(clLightBlue, clBlack);
	printf("Наведите на стартовую точку и нажмите F1\nНаведите на финишную точку и нажмите F2\nДля нахождения маршрута намжите F3\nДля выхода нажмите ESCAPE");
	if (NULL != Sender->WasOnObject) {
		Sender->WasOnObject->btype->Print();
		Sender->WasOnObject = NULL;
	}

	Sender->Routing->Print();

	consoleGotoXY(Sender->Routing->getX(), Sender->Routing->getY());
	Sender->WasOnObject = list2_findxy(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY());
}

void routingOnRunAfter(NaviEngine *Sender)
{
	
}
void routingOnProcessKeyAfter(NaviEngine *Sender)
{


}

void editorOnKeyLeft(NaviEngine *Sender)
{
	if (Sender->Routing->getX() > 1)
		Sender->Routing->setX(Sender->Routing->getX() - 1);
}

void editorOnKeyRight(NaviEngine *Sender)
{
	if (Sender->Routing->getX() < lengthX)
		Sender->Routing->setX(Sender->Routing->getX() + 1);
}

void editorOnKeyDown(NaviEngine *Sender)
{
	if (Sender->Routing->getY() < lengthY + 11) {
		Sender->Routing->setY(Sender->Routing->getY() + 1);
	}
}

void editorOnKeyUp(NaviEngine *Sender)
{
	if (Sender->Routing->getY() > 12) {
		Sender->Routing->setY(Sender->Routing->getY() - 1);
	}
}

void editorOnKeyF1(NaviEngine *Sender)//создаем начало графа,вносим в список вершину
{
	if (1 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()))
	{
		if (Sender->flagG == 0) {
			if (0 == vertex_contains(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY()))
			{
				Sender->ListVert = map_add_Vertex(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY(), 0, ptCrossroad, clBlack, clBrown);
				Sender->ListVert->btype->id = Sender->numGraph;

				Sender->xG = Sender->Routing->getX();
				Sender->yG = Sender->Routing->getY();
				Sender->numGraph++;
				Sender->flagG = 1;

			}

			else
			{
				Sender->xG = Sender->Routing->getX();
				Sender->yG = Sender->Routing->getY();
				Sender->flagG = 1;

			}

		}

	}
}

void editorOnKeyF2(NaviEngine *Sender)//создаем конец графа,вносим в список вершину
{
	if (1 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()))
	{
		if (Sender->flagG == 1)
		{
			if (0 == vertex_contains(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY()))
			{
				Sender->ListVert = map_add_Vertex(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY(), 1, ptCrossroad, clBlack, clBrown);
				Sender->ListVert->btype->id = Sender->numGraph;
				Sender->ListGraph = map_add_Edge(Sender->ListGraph, Sender->xG, Sender->yG, Sender->Routing->getX(), Sender->Routing->getY(), ptRevers, clBlack, clMagenta);
				Sender->ListGraph->btype->id = Sender->numEdge;
				Sender->ListVert = vertex_findxy(Sender->ListVert, Sender->xG, Sender->yG);
				Sender->ListVert->btype->size++;

				Sender->numEdge++;
				Sender->numGraph++;
				Sender->flagG = 0;
				
			}

			else
			{//проверка на существование ребра,и предотвращение повторных нажатий кнопок на одной вершине
				if (0 == graph_contains(Sender->ListGraph, Sender->xG, Sender->yG, Sender->Routing->getX(), Sender->Routing->getY()) && (Sender->xG != Sender->Routing->getX() || Sender->yG != Sender->Routing->getY()))
				{
					Sender->ListGraph = map_add_Edge(Sender->ListGraph, Sender->xG, Sender->yG, Sender->Routing->getX(), Sender->Routing->getY(), ptRevers, clBlack, clMagenta);
					Sender->ListVert->btype->id = Sender->numEdge;

					Sender->ListVert = vertex_findxy(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY());
					Sender->ListVert->btype->size++;
					Sender->ListVert = vertex_findxy(Sender->ListVert, Sender->xG, Sender->yG);
					Sender->ListVert->btype->size++;

					Sender->numEdge++;
					Sender->flagG = 0;
				
				}

			}

		}

	}
}

void editorOnKeyF3(NaviEngine *Sender)//двигаясь по односторонке
{
	if (1 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()))
	{
		if (Sender->flagG == 1)
		{
			if (0 == vertex_contains(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY()))
			{
				Sender->ListVert = map_add_Vertex(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY(), 0, ptCrossroad, clBlack, clBrown);
				Sender->ListVert->btype->id = Sender->numGraph;
				Sender->ListGraph = map_add_Edge(Sender->ListGraph, Sender->xG, Sender->yG, Sender->Routing->getX(), Sender->Routing->getY(), ptStarttoEnd, clBlack, clMagenta);
				Sender->ListGraph->btype->id = Sender->numEdge;
				Sender->ListVert = vertex_findxy(Sender->ListVert, Sender->xG, Sender->yG);
				Sender->ListVert->btype->size++;

				Sender->numEdge++;
				Sender->numGraph++;
				Sender->flagG = 0;

			}

			else
			{//проверка на существование ребра,и предотвращения выгрузки координат в точку загрузки.F3 сразу после F1 в ту же точку. 
				if (0 == graph_contains(Sender->ListGraph, Sender->xG, Sender->yG, Sender->Routing->getX(), Sender->Routing->getY()) && (Sender->xG != Sender->Routing->getX() || Sender->yG != Sender->Routing->getY()))
				{
					Sender->ListGraph = map_add_Edge(Sender->ListGraph, Sender->xG, Sender->yG, Sender->Routing->getX(), Sender->Routing->getY(), ptStarttoEnd, clBlack, clMagenta);
					Sender->ListGraph->btype->id = Sender->numEdge;
					Sender->ListVert = vertex_findxy(Sender->ListVert, Sender->xG, Sender->yG);
					Sender->ListVert->btype->size++;

					Sender->numEdge++;
					Sender->numGraph++;
					Sender->flagG = 0;

				}
			}

		}

	}

}

void editorOnKeyF4(NaviEngine *Sender)
{
	if (1 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()))
	{
		if (Sender->flagG == 1)
		{
			if (0 == vertex_contains(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY()))
			{
				Sender->ListVert = map_add_Vertex(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY(), 1, ptCrossroad, clBlack, clBrown);
				Sender->ListVert->btype->id = Sender->numGraph;
				Sender->ListGraph = map_add_Edge(Sender->ListGraph, Sender->Routing->getX(), Sender->Routing->getY(), Sender->xG, Sender->yG, ptStarttoEnd, clBlack, clMagenta);
				Sender->ListGraph->btype->id = Sender->numEdge;
				

				Sender->numEdge++;
				Sender->numGraph++;
				Sender->flagG = 0;

			}

			else 
			{
				if (0 == graph_contains(Sender->ListGraph, Sender->xG, Sender->yG, Sender->Routing->getX(), Sender->Routing->getY()) && (Sender->xG != Sender->Routing->getX() || Sender->yG != Sender->Routing->getY()))
				{
					Sender->ListGraph = map_add_Edge(Sender->ListGraph, Sender->Routing->getX(), Sender->Routing->getY(), Sender->xG, Sender->yG, ptStarttoEnd, clBlack, clMagenta);
					Sender->ListGraph->btype->id = Sender->numEdge;
					Sender->ListVert = vertex_findxy(Sender->ListVert, Sender->Routing->getX(), Sender->Routing->getY());
					Sender->ListVert->btype->size++;
					Sender->numEdge++;
					Sender->numGraph++;
					Sender->flagG = 0;

				}
			}

		}

	}
}

void editorOnKeyF5(NaviEngine *Sender)
{
	if ((0 == list2_contains(Sender->Build, Sender->Routing->getX(), Sender->Routing->getY())) && (0 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()))) {
		Sender->Build = map_add_TPoint(Sender->Build, Sender->Routing->getX(), Sender->Routing->getY(), ptHouse, clWhite, clBrown);
	}
}

void editorOnKeyF6(NaviEngine *Sender)
{
	if ((0 == list2_contains(Sender->Build, Sender->Routing->getX(), Sender->Routing->getY())) && (0 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()))) {
		Sender->Build = map_add_TPoint(Sender->Build, Sender->Routing->getX(), Sender->Routing->getY(), ptTree, clGreen, clGreen);
	}
}

void editorOnKeyF7(NaviEngine *Sender)
{
	if ((0 == list2_contains(Sender->Build, Sender->Routing->getX(), Sender->Routing->getY())) && (0 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()))) {
		Sender->Road = map_add_TPoint(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY(), ptPavement, clBlack, clBrown);
	}
}

void editorOnKeyF8(NaviEngine *Sender)
{
	if ((0 == list2_contains(Sender->Build, Sender->Routing->getX(), Sender->Routing->getY())) && (0 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()))) {
		Sender->Road = map_add_TPoint(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY(), ptTrend, clWhite, clBrown);
	}
}

void editorOnKeyF9(NaviEngine *Sender)
{

	list2_savetofile(Sender->Build, "d:\\build.txt");

	list2_savetofile(Sender->Road, "d:\\road.txt");

	graph_savetofile(Sender->ListGraph, "d:\\edge.txt");

	vertex_savetofile(Sender->ListVert, "d:\\vert.txt");

}

void editorOnKeyDelete(NaviEngine *Sender)
{
	if (1 == list2_contains(Sender->Build, Sender->Routing->getX(), Sender->Routing->getY()))
	{
		if (NULL != Sender->Build) {
			list2 *p = list2_gotofirst(Sender->Build);
			while (NULL != p) {
				if (1 == p->btype->Contains(Sender->Routing->getX(), Sender->Routing->getY())) {
					list2 *ptemp = p->next;
					if (p == list2_gotofirst(Sender->Build)) {
						Sender->Build = list2_gotolast(Sender->Build);
					}
					if (p == list2_gotolast(Sender->Build)) {
						Sender->Build = list2_gotofirst(Sender->Build);
					}
					if (1 == list2_count(Sender->Build)) {
						Sender->Build = NULL;
					}
					list2_del(p);
					p = ptemp;
				}
				else
				{
					p = p->next;
				}
			}
		}
	}
	else if (1 == list2_contains(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()))
	{
		if (NULL != Sender->Road) {
			list2 *p = list2_gotofirst(Sender->Road);
			while (NULL != p) {
				if (1 == p->btype->Contains(Sender->Routing->getX(), Sender->Routing->getY())) {
					list2 *ptemp = p->next;
					if (p == list2_gotofirst(Sender->Road)) {
						Sender->Road = list2_gotolast(Sender->Road);
					}
					if (p == list2_gotolast(Sender->Road)) {
						Sender->Road = list2_gotofirst(Sender->Road);
					}
					if (1 == list2_count(Sender->Road)) {
						Sender->Road = NULL;
					}
					list2_del(p);
					p = ptemp;
				}
				else {
					p = p->next;
				}
			}
		}
	}

}

void editorOnRunBefore(NaviEngine *Sender)
{
	printStatus1(Sender->Routing->getX(), Sender->Routing->getY(), 0, lengthY + 12, list2_findxy(Sender->Road, Sender->Routing->getX(), Sender->Routing->getY()));

}

void editorOnRunAfter(NaviEngine *Sender)
{

}

void editorOnProcessKeyBefore(NaviEngine *Sender) {

	consoleGotoXY(0, 12);
	list2_print(Sender->Build);
	list2_print(Sender->Road);
	graph_print(Sender->ListGraph);
	vertex_print(Sender->ListVert);
	consoleGotoXY(Sender->Routing->getX(), Sender->Routing->getY());


}

//void editorOnKeyEscape(NaviEngine *Sender, int _running)
//{
//	_running = 1;
//	
//}


//argc-количество аргументов переданных
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");

	NaviEngine *Navi = new NaviEngine();
	int flagExit = 0;
	int keyPressed = 0;
	do {
		consoleSetColors(clWhite, clBlack);
		system("cls");
		consoleGotoXY(0, 3);
		consoleSetColors(clWhite, clBlack);
		Navi->printMenu();
		keyPressed = _getch();
		switch (keyPressed)
		{
		case KEY_DOWN:
			if ((menuCount - 1) == Navi->menuSelected)
			{
				Navi->menuSelected = 0;
			}
			else Navi->menuSelected++;
			break;
		case KEY_UP:
			if (0 == Navi->menuSelected)
			{
				Navi->menuSelected = (menuCount - 1);
			}
			else {
				Navi->menuSelected--;
			}
			break;

		case KEY_ENTER:
			system("cls");
			consoleSetColors(clWhite, clBlack);
			consoleGotoXY(0, 0);
			if (1 == Navi->menuSelected)
			{
				Navi->Routing->setTyp(ptPavement);
				Navi->onKeyLeft = &editorOnKeyLeft;
				Navi->onKeyRight = &editorOnKeyRight;
				Navi->onKeyDown = &editorOnKeyDown;
				Navi->onKeyUp = &editorOnKeyUp;
				Navi->onKeyF1 = &editorOnKeyF1;
				Navi->onKeyF2 = &editorOnKeyF2;
				Navi->onKeyF3 = &editorOnKeyF3;
				Navi->onKeyF4 = &editorOnKeyF4;
				Navi->onKeyF5 = &editorOnKeyF5;
				Navi->onKeyF6 = &editorOnKeyF6;
				Navi->onKeyF7 = &editorOnKeyF7;
				Navi->onKeyF8 = &editorOnKeyF8;
				Navi->onKeyF9 = &editorOnKeyF9;
				Navi->onKeyDelete = &editorOnKeyDelete;
				Navi->onProcessKeyBefore = &editorOnProcessKeyBefore;
				Navi->onRunBefore = &editorOnRunBefore;
				Navi->onRunAfter = &editorOnRunAfter;

				Navi->Run();


				break;

			}
			if (2 == Navi->menuSelected)
			{
				Navi->Routing->setTyp(ptPavement);
				Navi->Build = list2_loadfromfile(NULL, "d:\\build.txt");
				Navi->Road = list2_loadfromfile(NULL, "d:\\road.txt");
				Navi->ListGraph = graph_loadfromfile(NULL, "d:\\edge.txt");
				Navi->ListVert = vertex_loadfromfile(NULL, "d:\\vert.txt");
				Navi->onProcessKeyBefore = &routingOnProcessKeyBefore;
				Navi->onRunBefore = &routingOnRunBefore;
				Navi->onKeyLeft = &routingOnKeyLeft;
				Navi->onKeyRight = &routingOnKeyRight;
				Navi->onKeyDown = &routingOnKeyDown;
				Navi->onKeyUp = &routingOnKeyUp;
				Navi->onKeyF1 = &routingOnKeyF1;
				Navi->onKeyF2 = &routingOnKeyF2;
				Navi->onKeyF3 = &routingOnKeyF3;
				Navi->onRunAfter = &routingOnRunAfter;
				Navi->onProcessKeyAfter = &routingOnProcessKeyAfter;

				Navi->Run();
				break;

			}
			if (3 == Navi->menuSelected)
			{
				flagExit = 2;
				break;
			}
			break;

		}


	} while (flagExit != 2);

	delete Navi;
	consoleSetColors(clWhite, clBlack);
	system("cls");
	consoleSetColors(clWhite, clBlack);
	consoleGotoXY(0, 30);
	return 0;
}



