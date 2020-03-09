#ifndef GRAPH_H
#define GRAPH_H

#include "basetype.h"
#include"point.h"
#include "edge.h"

struct graph {
	Edge *btype;
	graph *next;
	graph *prev;
};

struct vertex {
	TPoint *btype;
	vertex *next, *prev;
};

graph *graph_create();
graph *graph_add(graph *p1);
graph *graph_gotofirst(graph *list);
void graph_print(graph *list);
int graph_contains(graph *map, short x, short y,short x2,short y2);
graph *graph_findxy(graph *map, short x, short y,short X2, short Y2);
graph *map_add_Edge(graph *map, short x, short y, short X2, short Y2, EdgeType t,
	ConsoleColors color, ConsoleColors bgcolor);
int graph_savetofile(graph *list, const char *filename);
graph *graph_loadfromfile(graph *list, const char *filename);
graph *graph_findxyVert(graph *map, short x, short y);
graph *findNoVisitEdge(graph *edge, short x, short y, short xEnd, short yEnd, short dir,graph *masWay);
graph *graph_gotolast(graph *list);
int directEdge(graph *edge, short orient, short dir, short xFinish, short yFinish);
int find_direct(short xStart, short yStart, short xEnd, short yEnd);


vertex *vertex_create();
vertex *vertex_add(vertex *p1);
vertex *vertex_gotofirst(vertex *list);
void vertex_print(vertex *list);
int vertex_contains(vertex *map, short x, short y);

vertex *vertex_findxy(vertex *map, short x, short y);
vertex *map_add_Vertex(vertex *map, short x, short y,short size, TPointType t,
	ConsoleColors color, ConsoleColors bgcolor);
int vertex_savetofile(vertex *list, const char *filename);
vertex *vertex_loadfromfile(vertex *list, const char *filename);


#endif




