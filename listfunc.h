#ifndef LISTFUNC_H
#define LISTFUNC_H

#include "basetype.h"
#include "point.h"

struct list2 {
	Btype *btype;
	list2 *next;
	list2 *prev;
};

list2 *list2_create();
list2 *list2_ins(list2 *list);
list2 *list2_gotofirst(list2 *list);
list2 *list2_gotolast(list2 *list);
void list2_del(list2 *list);
void list2_print(list2 *list);
void list2_printtext(list2 *list);
void list2_clear(list2 *list);
int list2_count(list2 *list);
int list2_savetofile(list2 *list, const char *filename);
list2 *list2_loadfromfile(list2 *list, const char *filename);
int list2_contains(list2 *map, short x, short y);
list2 *list2_findxy(list2 *map, short x, short y);
void list2_swap(list2 *item1, list2 *item2);
void list2_sortby_y(list2 *list);
list2 *map_add_TPoint(list2 *map, short x, short y, TPointType t,
	ConsoleColors color, ConsoleColors bgcolor);
void map_del_Tpoint(list2 *map, short x, short y);
void printStatus1(short x, short y, short Left, short Top,list2 *item);
#endif
