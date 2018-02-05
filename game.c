/***************************
State Gotoxy(int x, int y)
State Print_Wall(COORD coord)
void Hide_Cursor(void)
****************************/
#include "snake.h"
State Gotoxy(int x, int y) {
	
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, coord);
}

State Draw_Wall() {
	
	int x, y;
	for(y=0; y<HIGH; y++) {
		Gotoxy(FRAMEX, FRAMEY+y);
		if(y==0 || y==HIGH-1) {
		
			for(x=0; x<WIDTH; x+=2)
				printf("■");
			printf("\n");
		} else {
		
			printf("■");
			Gotoxy(WIDTH+FRAMEX-18, FRAMEY+y);
			if(y%5 == 0) {
				int i;
				for(i=0; i<9; i++)
					printf("■");
			} else	{
				printf("■");
				Gotoxy(WIDTH+FRAMEX-2, FRAMEY+y);
				printf("■\n");
			}
		}
	}

}

State Print_Info() {
	int x, y;
	for(y=0; y<HIGH; y++) {
		
		if(y%5 == 2) {
			Gotoxy(WIDTH+FRAMEX-14, FRAMEY+y);
			switch(y/5) {
				case 0: {
					printf("玩家名称:");
					break;
				}
				case 1: {
					printf("移动速度:");
					break;
				}
				case 2: {
					printf("游戏时间: ");
					break;
				}
				case 3: {
					printf("游戏分数: ");
					break;
				}
				case 4: {
					printf("蛇的长度: ");
					break;
				}
			}
		}
		if(y%5 == 3) {
			Gotoxy(WIDTH+FRAMEX-10, FRAMEY+y);
			switch(y/5) {
				case 0: {
					printf("%s", player.name);
					break;
				}
				case 1: {
					printf("%d", head.speed);
					break;
				}
				case 2: {
					printf("%d", head.date);
					break;
				}
				case 3: {
					printf("%d", head.score);
					break;
				}
				case 4: {
					printf("%d", head.length);
					break;
				}
			}
		}
	}
}

void Hide_Cursor(void) {
	
	CONSOLE_CURSOR_INFO cci= {1, 0};
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cci);
}
