#include "pch.h"
#include <conio.h>
#include <Windows.h>
#include "consolrut.h"

void consoleSetColors(ConsoleColors textColor, ConsoleColors backgroundColor) {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCons, (WORD)((backgroundColor << 4) | textColor));

}

short consoleWhereX() {
	short x = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	_CONSOLE_SCREEN_BUFFER_INFO scrInfo;
	if (true == GetConsoleScreenBufferInfo(hCons, &scrInfo)) {
		x = scrInfo.dwCursorPosition.X;
	}
	return x;
}

short consoleWhereY() {
	short y = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO *)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		y = scrInfo->dwCursorPosition.Y;
	}
	free(scrInfo);
	return y;
}

short consoleBuffSizeX() {
	short x = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO *)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		x = scrInfo->dwSize.X;
	}
	free(scrInfo);
	return x;
}

short consoleBuffSizeY() {
	short y = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO *)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		y = scrInfo->dwSize.Y;
	}
	free(scrInfo);
	return y;
}

short consoleSizeX() {
	short x = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO *)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		x = scrInfo->dwMaximumWindowSize.X;
	}
	free(scrInfo);
	return x;
}

short consoleSizeY() {
	short y = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO *)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		y = scrInfo->dwMaximumWindowSize.Y;
	}
	free(scrInfo);
	return y;
}

void consoleGotoXY(short x, short y) {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hCons, position);
}

void consoleGotoX(short x) {
	consoleGotoXY(x, consoleWhereY());
}

void consoleGotoY(short y) {
	consoleGotoXY(consoleWhereX(), y);
}

void consoleClear() {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO CSI;
	DWORD written;
	DWORD dwConSize;
	COORD P;
	P.X = 0;
	P.Y = 0;
	GetConsoleScreenBufferInfo(hCons, &CSI);
	dwConSize = CSI.dwSize.X * CSI.dwSize.Y;
	FillConsoleOutputCharacterA(hCons, ' ', dwConSize, P, &written);
	GetConsoleScreenBufferInfo(hCons, &CSI);
	FillConsoleOutputAttribute(hCons, CSI.wAttributes, dwConSize, P, &written);
}
