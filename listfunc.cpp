#include "pch.h"
#include <iostream>
#include "constsize.h"
#include "strutils.h"
#include "basetype.h"
#include "point.h"
#include "listfunc.h"

list2 *list2_create() {
	list2 *item;
	item = (list2 *)malloc(sizeof(struct list2));
	item->btype = NULL;
	item->next = NULL;
	item->prev = NULL;
	return(item);
};

list2 *list2_ins(list2 *list) {
	list2 *item = list2_create(); //создание эл.
	item->prev = list;  // инициализация указателя предыдущего эл-та
	if (NULL != list) {  // преверяем, существует ли предыдущий элемент (пустой список)
		item->next = list->next;
		if (NULL != list->next) { // проверяем, является ли предыдущий эл-т конечным или за ним есть ещё?
			list->next->prev = item;
		}
		list->next = item; // переопределение упредыдущего эл-та указателя следующего на себя
	}
	return(item);
};

void list2_del(list2 *list) {
	if (NULL == list) {
		return;
	}
	list2 *nxt, *prv;
	nxt = list->next;
	prv = list->prev;
	if (NULL != nxt) {   // не является ли элемент конечным в списке? 
		nxt->prev = list->prev;
	}
	if (NULL != prv) {   // не является ли элемент первым в списке?
		prv->next = list->next;
	}
	if (NULL != list->btype) {
		delete list->btype;
	}
	free(list);
};

list2 *list2_gotofirst(list2 *list) {
	list2 *item = list;
	if (NULL != item) {
		while (NULL != item->prev) {
			item = item->prev;
		}
	}
	return (item);
};

list2 *list2_gotolast(list2 *list) {
	list2 *item = list;
	if (NULL != item) {
		while (NULL != item->next) {
			item = item->next;
		}
	}
	return (item);
};

int list2_count(list2 *list) {
	int result = 0;
	list2 *item = list2_gotofirst(list);
	while (NULL != item) {
		result++;
		item = item->next;
	}
	return result;
};


void list2_swap(list2 *item1, list2 *item2) {
	if ((NULL == item1) || (NULL == item2)) {
		return;
	}
	if ((item1->next == item2) && (item2->prev == item1)) { // рядом стоящие элементы
		list2 *next0 = item2->next;
		list2 *prev0 = item1->prev;
		item1->next = next0;
		item1->prev = item2;
		item2->next = item1;
		item2->prev = prev0;
		if (NULL != next0) {
			next0->prev = item1;
		}
		if (NULL != prev0) {
			prev0->next = item2;
		}
	}
	else if ((item2->next == item1) && (item1->prev == item2)) { // рядом стоящие элементы
		list2 *next0 = item1->next;
		list2 *prev0 = item2->prev;
		item1->next = item2;
		item1->prev = prev0;
		item2->next = next0;
		item2->prev = item1;
		if (NULL != next0) {
			next0->prev = item2;
		}
		if (NULL != prev0) {
			prev0->next = item1;
		}
	}
	else { // отстоящие друг от друга элементы
		list2 *next2 = item1->next;
		list2 *prev2 = item1->prev;
		item1->next = item2->next;
		item1->prev = item2->prev;
		item2->next = next2;
		item2->prev = prev2;
		if (NULL != item1->next) {
			item1->next->prev = item1;
		}
		if (NULL != item1->prev) {
			item1->prev->next = item1;
		}
		if (NULL != item2->next) {
			item2->next->prev = item2;
		}
		if (NULL != item2->prev) {
			item2->prev->next = item2;
		}
	}
}

void list2_print(list2 *list) {
	list2 *item = list2_gotofirst(list);
	while (NULL != item) {
		if (NULL != item->btype) {
			item->btype->Print();
		}
		item = item->next;
	}
};

void list2_printtext(list2 *list) {
	list2 *item = list2_gotofirst(list);
	while (NULL != item) {
		if (NULL != item->btype) {
			item->btype->PrintText();
		}
		item = item->next;
	}
};

void list2_clear(list2 *list) {
	list2 *item = list2_gotolast(list);
	while (NULL != item) {
		list2 *delitem = item;
		item = item->prev;
		list2_del(delitem);
	}
}

int list2_savetofile(list2 *list, const char *filename) {
	FILE *file;
	int result = fopen_s(&file, filename, "r");
	if (0 == result) {
		list2 *item = list2_gotofirst(list);
		while (NULL != item) {
			item->btype->SaveToFile(file);
			item = item->next;
		}
	
		fclose(file);
	}
	return result;
}


list2 *list2_loadfromfile(list2 *list, const char *filename) {
	list2 *item = list;
	FILE *file;
	int result = fopen_s(&file, filename, "r");
	if (0 == result) {

	//	char *objname = (char *)malloc(count * sizeof(char));
		char *buffer = (char *)malloc(count * sizeof(char));
		char *work = buffer;
		nullStr(buffer, count);
		while (EOF != (*work = fgetc(file))) {
			if ('\n' == *work) {
				//parseItem(buffer, '|', objname);
				item = list2_ins(item);
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
			//parseItem(buffer, '|', objname);
			item = list2_ins(item);
			
			if (NULL != item->btype) {
				item->btype->LoadFromStr(buffer);
			}
		}
		free(buffer);
		//free(objname);
		fclose(file);
	}
	return item;
}

int list2_contains(list2 *map, short x, short y) {
	list2 *item = list2_gotofirst(map);
	while (NULL != item) {
		if (1 == item->btype->Contains(x, y)) {
			return 1;
		}
		item = item->next;
	}
	return 0;
};

list2 *list2_findxy(list2 *map, short x, short y) {
	list2 *item = list2_gotofirst(map);
	while (NULL != item) {
		if (1 == item->btype->Contains(x, y)) {
			return item;
		}
		item = item->next;
	}
	return NULL;
};

void list2_sortby_y(list2 *list) {
	int swapCount = 0;
	list2 *p = NULL;
	do {
		swapCount = 0;
		p = list2_gotofirst(list);
		while (NULL != p) {
			if (NULL != p->next) {
				if (p->btype->getY() > p->next->btype->getY()) {
					list2_swap(p, p->next);
					swapCount++;
				}
			}
			p = p->next;
		}
	} while (swapCount != 0);
}



list2 *map_add_TPoint(list2 *map, short x, short y, TPointType t,
	ConsoleColors color, ConsoleColors bgcolor) {
	TPoint *p = new TPoint();
	p->setX(x);
	p->setY(y);
	p->setColor(color);
	p->setBgColor(bgcolor);
	p->setTyp(t);

	list2 *result = list2_ins(map);
	result->btype = p;
	return result;
}
void map_del_Tpoint(list2 * map, short x, short y)
{
		list2 *p = list2_gotofirst(map);
		while (NULL != p)
		{
			if (1 == p->btype->Contains(x, y))
			{
				list2 *ptemp = p->next;
				if (p == list2_gotofirst(map)) {
					map = list2_gotolast(map);
				}
				if (p == list2_gotolast(map)) {
					map = list2_gotofirst(map);
				}
				if (1 == list2_count(map)) {
					map = NULL;
				}
				list2_del(p);
				p = ptemp;
				return;
			}
			else {
				p = p->next;
			}
		}
	
}
void printStatus1(short x, short y, short Left, short Top,list2 *item) {
	consoleGotoXY(Left, Top);
	char *s = (char *)malloc(500 * sizeof(char));
	nullStr(s, 500);
	strcpy_s(s, 500, "F1-Сохранение координат для создания перекрестка\nF2-Выгружает сохранненые координаты.Создаем перекресток и двусторонюю дорогу\n\
F3-Выгружает сохранненые координаты.Создаем односторонюю дорогу двигаясь по ней\n\
F4--Выгружает сохранненые координаты.Создаем односторонюю дорогу проезжая под кирпич\n\
F5-Создаем дом\nF6-Создаем дерево\nF7-Создаем дорогу\nF8-Ставим метку кирпич\nF9-сохраняем карту\n DEL-удаляем не нужный элемент ");
	consoleSetColors(clWhite, clBlack);

	printf("%s", s);
	//printf("x:%3d y:%3d      %s", x, y, s);
	free(s);
}