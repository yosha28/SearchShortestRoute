#include "pch.h"
#include "graph.h"
#include "basetype.h"
#include "point.h"
#include "edge.h"
#include "strutils.h"
#include "constsize.h"
#include <iostream>
#include <math.h>


graph *graph_create()
{
	graph *item = NULL;
	item = (graph *)malloc(sizeof(struct graph));
	item->btype = NULL;
	item->next = NULL;
	item->prev = NULL;
	return(item);
};

graph *graph_add(graph *p1)
{

	graph *p2 = graph_create(); //создание эл.
	p2->prev = p1;
	if (NULL != p1) {  // преверяем, существует ли предыдущий элемент (пустой список)
		p2->next = p1->next;
		if (NULL != p1->next) { // проверяем, является ли предыдущий эл-т конечным или за ним есть ещё?
			p1->next->prev = p2;
		}
		p1->next = p2; // 
	}

	return(p2);
};

graph *graph_gotofirst(graph *list) {
	graph *item = list;
	if (NULL != item) {
		while (NULL != item->prev) {
			item = item->prev;
		}
	}
	return (item);
};

void graph_print(graph *list)
{
	graph *item = graph_gotofirst(list);
	while (NULL != item) {
		if (NULL != item->btype) {

			item->btype->Print();
		}
		item = item->next;
	}
};
//наличие ребра в списке
int graph_contains(graph *map, short x, short y, short x2, short y2)
{
	graph *item = graph_gotofirst(map);
	while (NULL != item) {
		if (1 == item->btype->Contains(x, y, x2, y2)) {

			return 1;
		}
		item = item->next;
	}
	return 0;
};

//нахождение ребра в списке
graph *graph_findxy(graph *map, short x, short y, short X2, short Y2)
{
	graph *item = graph_gotofirst(map);
	while (NULL != item) {
		if (1 == item->btype->Contains(x, y, X2, Y2)) {
			return item;
		}
		item = item->next;
	}
	return NULL;
};

graph *map_add_Edge(graph *map, short X, short Y, short X2, short Y2, EdgeType t,
	ConsoleColors color, ConsoleColors bgcolor) {
	Edge *p = new Edge();
	p->setX(X);
	p->setY(Y);
	p->x2 = X2;
	p->y2 = Y2;
	//	p->length = sqrt(pow(p->getX() - p->x2, 2) + pow(p->getY() - p->y2, 2));
	p->setColor(color);
	p->setBgColor(bgcolor);
	p->setTyp(t);
	graph *result = graph_add(map);
	result->btype = p;
	return result;
}

int graph_savetofile(graph *list, const char *filename) {
	FILE *file;
	int result = fopen_s(&file, filename, "r");
	if (0 == result) {
		graph *item = graph_gotofirst(list);
		while (NULL != item) {
			item->btype->SaveToFile(file);
			item = item->next;
		}
		fclose(file);
	}
	return result;
}

graph *graph_loadfromfile(graph *list, const char *filename) {
	graph *item = list;
	FILE *file;
	int result = fopen_s(&file, filename, "r");
	if (0 == result) {
		char *buffer = (char *)malloc(count * sizeof(char));
		char *work = buffer;
		nullStr(buffer, count);
		while (EOF != (*work = fgetc(file))) {
			if ('\n' == *work) {
				item = graph_add(item);

				item->btype = new Edge();

				if (NULL != item->btype) {
					item->btype->LoadFromStr(buffer);
				}
				nullStr(buffer, count);
				work = buffer;
			}
			else {
				work++;
			}
		}
		if ((work != buffer) && (0 < strlen(buffer))) {

			item = graph_add(item);
			item->btype = new Edge();


			if (NULL != item->btype) {
				item->btype->LoadFromStr(buffer);
			}
		}
		free(buffer);
		fclose(file);
	}

	return item;
	//return 0;
}
//нахождение ребра с такой вершиной 
graph *graph_findxyVert(graph *map, short x, short y)
{
	graph *item = graph_gotofirst(map);
	while (NULL != item) {
		if (1 == item->btype->ContainsVertEdge(x, y)) {
			return item;
		}
		item = item->next;
	}
	return NULL;

}




graph *findNoVisitEdge(graph *pedge, short x, short y, short xEnd, short yEnd, short dir, graph *masWay)
{

		short xTemp = 0;
		short yTemp = 0;

		pedge = graph_gotofirst(pedge);
		graph *edge = pedge;
	

		while (edge != NULL)
		{
			if (1 == edge->btype->ContainsVertEdge(x, y))
			{
				short orient = 0;
				short tempDir = 0;

				//ребро прилегает началом
				if (edge->btype->getX() == x && edge->btype->getY() == y/* && edge->btype->getTyp() != ptStarttoEnd*/)//ребро прилегает началом
				{
					orient = 1;
					tempDir = directEdge(edge, orient, dir, xEnd, yEnd);
					//не пройдено и подходит направление -передаем его 
					if (edge->btype->getColor() != clRed)
					{
						if (1 == tempDir)
						{
							xTemp = edge->btype->x2;
							yTemp = edge->btype->y2;
							break;
						}
						if (2 == tempDir)
						{
							xTemp = edge->btype->x2;
							yTemp = edge->btype->y2;
						}
						if (0 == tempDir)
						{
							if (0 == xTemp && 0 == yTemp)
							{
								xTemp = edge->btype->x2;
								yTemp = edge->btype->y2;
							}

						}
					}

					else//ребро уже пройденно в других маршрутах
					{
						if (0 == graph_contains(masWay, x, y, edge->btype->x2, edge->btype->y2))//не пройденно в этом маршруте
						{
							if (1 == tempDir)
							{
								xTemp = edge->btype->x2;
								yTemp = edge->btype->y2;
								break;
							}
							if (2 == tempDir)
							{
								xTemp = edge->btype->x2;
								yTemp = edge->btype->y2;
							}
							if (0 == tempDir)
							{
								if (0 == xTemp && 0 == yTemp)
								{
									xTemp = edge->btype->x2;
									yTemp = edge->btype->y2;
								}

							}
						}

					}
				
				}
				//ребро прилегает концом
				else if (edge->btype->x2 == x && edge->btype->y2 == y/* && edge->btype->getTyp() != ptStarttoEnd*/)//ребро прилегает концом
				{
					orient = 2;
					tempDir = directEdge(edge, orient, dir, xEnd, yEnd);
					//не пройдено и подходит направление -передаем его 
					if (edge->btype->getColor() != clRed)
					{
						if (1 == tempDir)
						{
							xTemp = edge->btype->getX();
							yTemp = edge->btype->getY();
							break;
						}
						if (2 == tempDir)
						{
							xTemp = edge->btype->getX();
							yTemp = edge->btype->getY();
						}
						if (0 == tempDir)
						{
							if (0 == xTemp && 0 == yTemp)
							{
								xTemp = edge->btype->getX();
								yTemp = edge->btype->getY();
							}

						}
					
					}
					

					else
					{
						if (0 == graph_contains(masWay, x, y, edge->btype->getX(), edge->btype->getY()))
						{
							if (1 == tempDir)
							{
								xTemp = edge->btype->getX();
								yTemp = edge->btype->getY();
								break;
							}
							if (2 == tempDir)
							{
								xTemp = edge->btype->getX();
								yTemp = edge->btype->getY();
							}
							if (0 == tempDir)
							{
								if (0 == xTemp && 0 == yTemp)
								{
									xTemp = edge->btype->getX();
									yTemp = edge->btype->getY();
								}

							}
							
						}

					}

				}

			}

			edge = edge->next;

		}

		edge = graph_findxy(pedge, x, y, xTemp, yTemp);
		masWay = map_add_Edge(masWay, x, y, xTemp, yTemp, edge->btype->getTyp(), clRed, clRed);//ошибка edge=NULL!!!
		
	return masWay;

}




graph *graph_gotolast(graph *list) {
	graph *item = list;
	if (NULL != item) {
		while (NULL != item->next) {
			item = item->next;
		}
	}
	return (item);
};

int directEdge(graph *edge, short orient, short dir, short xFinish, short yFinish)//передаем ребро,проверяем в нужном ли направлении оно направленно
//в зависимости от флага назначаем стартовые и конечные координаты
{
	short xStart, yStart, xEnd, yEnd;
	if (orient == 1)//напрвление ребра от начала к концу
	{
		xStart = edge->btype->getX();
		yStart = edge->btype->getY();
		xEnd = edge->btype->x2;
		yEnd = edge->btype->y2;
	}
	else if (orient == 2)
	{//направление ребра от конца к началу

		xStart = edge->btype->x2;
		yStart = edge->btype->y2;
		xEnd = edge->btype->getX();
		yEnd = edge->btype->getY();

	}
	
	if (yStart > yEnd && ((dir == 1) || (dir == 8) || (dir == 7)))
	{
		if (yEnd < yFinish)//что б не идти в обход,не переехать, при нужном направлении ребра
		{
			return 2;
		}
		else
			return 1;
	}
	else if (yStart < yEnd && ((dir == 5) || (dir == 2) || (dir == 6)))
	{
		if (yEnd > yFinish)
		{
			return 2;
		}
		else
			return 1;

	}
	else if (xStart > xEnd && ((dir == 3) || (dir == 8) || (dir == 5)))
	{
		if (xEnd < xFinish)
		{
			return 2;
		}
		else
			return 1;
	}
	else if (xStart < xEnd && ((dir == 4) || (dir == 6) || (dir == 7)))
	{
		if (xEnd > xFinish)
		{
			return 2;
		}
		else
			return 1;
	}


	return 0;
}

int find_direct(short xStart, short yStart, short xEnd, short yEnd)//определяем направление движения со старта
{
	
	if (xStart == xEnd && yStart > yEnd)
	{
		return 1;
	}
	else if (xStart == xEnd && yStart < yEnd)
	{
		return 2;
	}
	else if (xStart > xEnd && yStart == yEnd)
	{
		return 3;
	}
	else if (xStart < xEnd && yStart == yEnd)
	{
		return 4;
	}
	else if (xStart > xEnd && yStart < yEnd)
	{
		return 5;
	}
	else if (xStart < xEnd && yStart < yEnd)
	{
		return 6;
	}
	else if (xStart < xEnd && yStart > yEnd)
	{
		return 7;
	}
	else if (xStart > xEnd && yStart > yEnd)
	{
		return 8;
	}
	return 0;
}

vertex *vertex_create()
{
	vertex *item = NULL;
	item = (vertex *)malloc(sizeof(struct vertex));
	item->btype = NULL;
	item->next = NULL;
	item->prev = NULL;
	return(item);
};

vertex *vertex_add(vertex *p1)
{
	vertex *p2 = vertex_create(); //создание эл.
	p2->prev = p1;
	if (NULL != p1) {  // преверяем, существует ли предыдущий элемент (пустой список)
		p2->next = p1->next;
		if (NULL != p1->next) { // проверяем, является ли предыдущий эл-т конечным или за ним есть ещё?
			p1->next->prev = p2;
		}
		p1->next = p2; // 
	}

	return(p2);
};

vertex *vertex_gotofirst(vertex *list) {
	vertex *item = list;
	if (NULL != item) {
		while (NULL != item->prev) {
			item = item->prev;
		}
	}
	return (item);
};

void vertex_print(vertex *list)
{
	vertex *item = vertex_gotofirst(list);
	while (NULL != item) {
		if (NULL != item->btype) {

			item->btype->PrintText();
		}
		item = item->next;
	}
};

int vertex_contains(vertex *list, short x, short y)
{
	vertex *item = vertex_gotofirst(list);
	while (NULL != item) {
		if (1 == item->btype->Contains(x, y)) {
			return 1;
		}
		item = item->next;
	}
	return 0;
};

vertex *vertex_findxy(vertex *list, short x, short y)
{
	vertex *item = vertex_gotofirst(list);
	while (NULL != item) {
		if (1 == item->btype->Contains(x, y)) {
			return item;
		}
		item = item->next;
	}
	return NULL;
};

vertex *map_add_Vertex(vertex *map, short X, short Y, short size, TPointType t,
	ConsoleColors color, ConsoleColors bgcolor) {
	TPoint *p = new TPoint();
	p->setX(X);
	p->setY(Y);
	p->setColor(color);
	p->setBgColor(bgcolor);
	p->setTyp(t);
	p->size = size;
	vertex *result = vertex_add(map);
	result->btype = p;
	return result;
}

int vertex_savetofile(vertex *list, const char *filename) {
	FILE *file;
	int result = fopen_s(&file, filename, "r");
	if (0 == result) {
		vertex *item = vertex_gotofirst(list);
		while (NULL != item) {

			item->btype->SaveToFile(file);

			item = item->next;
		}
		fclose(file);
	}
	return result;
}

vertex *vertex_loadfromfile(vertex *list, const char *filename) {
	vertex *item = list;
	FILE *file;
	int result = fopen_s(&file, filename, "r");
	if (0 == result) {
		char *buffer = (char *)malloc(count * sizeof(char));
		char *work = buffer;

		nullStr(buffer, count);
		while (EOF != (*work = fgetc(file))) {
			if ('\n' == *work) {
				item = vertex_add(item);
				item->btype = new TPoint();
				if (NULL != item->btype) {
					item->btype->LoadFromStr(buffer);
				}
				nullStr(buffer, count);
				work = buffer;
			}
			else {
				work++;
			}
		}
		if ((work != buffer) && (0 < strlen(buffer))) {

			item = vertex_add(item);
			item->btype = new TPoint();

			if (NULL != item->btype) {
				item->btype->LoadFromStr(buffer);
			}
		}

		free(buffer);
		fclose(file);
	}



	return item;
}

