#include "snake.h"
extern SNAKE *snake;
extern PLAYER player;
State Player_Management() {
	int choice;
	system("cls");
	Draw_Frame();
	Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-4);
	printf("1. 玩家注册");
	Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-2);
	printf("2. 玩家登陆");
	Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2);
	scanf("%d", &choice);
	system("cls");
	Draw_Frame();
	switch(choice) {
		case 1: {
			while(1) {
				if(Player_Register()) {
					break;
				} else {
					Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2+2);
					printf("玩家名已存在请重新输入!\n");
					Sleep(1000);
				}
			}
			break;
		}
		case 2: {
			while(1) {
				if(Player_Login())	break;
				else {
				}
			}
			break;
		}
		default: {
			Gotoxy(FRAMEX+WIDTH/2, FRAMEY+HIGH/2+2);
			printf("输入有误, 请从新输入!");
			Sleep(1000);
			return False;
			break;
		}
	}
	return Ok;
}
State Menu() {
	int choice;
	Draw_Frame();
	Show_Cursor();
		Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-4);
	printf("1. 开始游戏\n");
		Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-2);
	printf("2. 排行榜\n");
		Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2);
	printf("3. 玩家管理\n");
		Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2+2);
	printf("4. 退出游戏\n");
		Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2+4);
	fflush(stdin);
	scanf("%d", &choice);
	switch(choice) {
		case 1: {
			Start_Game();
			break;
		}
		case 2: {
			Rank_List();
			break;
		}
		case 3:{
			Player_Management();
			break;
		}
		case 4: {
			system("cls");
			exit(Ok);
			break;
		}
		default:{
			Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2+6);
			printf("输入有误,请重新输入!");
			break;
		}
	}
	return Ok;
}

