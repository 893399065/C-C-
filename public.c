/****************************************************
State Draw_Frame();			//draw the game frame
void Set_Color(unsigned short ForeColor, unsigned short BackGroundColor)
State Gotoxy(short x, short y)
void Hide_Cursor(void)
****************************************************/

#include "snake.h"
extern SNAKE *snake;
extern PLAYER player;
void Set_Color(unsigned short ForeColor,unsigned short BackGroundColor) {
	//set console color
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//get currently standard handle
	SetConsoleTextAttribute(handle,ForeColor+BackGroundColor*0x10);//set console color
}

void Hide_Cursor() {
	//hide console cursor
	CONSOLE_CURSOR_INFO cci = { 1, 0 };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cci);
}

void Show_Cursor() {
	//hide console cursor
	CONSOLE_CURSOR_INFO cci = { 1, 1 };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cci);
}
State Gotoxy(short x, short y) {
	//move cursor to(x,y)
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, coord);
	return Ok;
}//Gotoxy
State Draw_Frame() {
	int x, y;
	for (y = 0; y<HIGH; y++) {
		Gotoxy(FRAMEX, FRAMEY + y);
		if (y == 0 || y == HIGH - 1) {
			//draw■■■■■■■■■■■■■■
			for (x = 0; x<WIDTH; x += 2)
				printf("■");
			printf("\n");
		} else {
			printf("■\n");
			Gotoxy(WIDTH + FRAMEX - 2, FRAMEY + y);
			printf("■\n");
		}
	}
	return Ok;
}


