/***************************
State Draw_Wall();						//draw a wall
State Draw_Snake();						//draw Snake and food
State Initialization();					//initialize program
State Start_Game();						//start the game
State Rank_List();						//look the rank list
State Print_Info();						//print game information
State Game_Init();						//game initialization
State Ifcoord_Snake(short x, short y);
void Creat_Food();						//creat snake's food
void Add_Body();
void Delete_Body();
char Get_Direction();
State Move_Snake();
BODY *Find_Tail();
****************************/
#include "snake.h"
extern SNAKE *snake;
extern PLAYER player;
State Draw_Wall() {
	//draw wall
	Set_Color(0, 6);
	int x, y;
	for (y = 0; y<HIGH; y++) {
		Gotoxy(FRAMEX, FRAMEY + y);
		if (y == 0 || y == HIGH - 1) {
			//draw■■■■■■■■■■■■■■
			for (x = 0; x<WIDTH; x += 2)
				printf("■");
			printf("\n");
		} else {
			//draw■                ■      ■
			printf("■");
			Gotoxy(WIDTH + FRAMEX - WIDTH2, FRAMEY + y);
			if (y % 5 == 0) {
				int i;
				for (i = 0; i<9; i++)
					printf("■");
			} else {
				printf("■");
				Gotoxy(WIDTH + FRAMEX - 2, FRAMEY + y);
				printf("■\n");
			}
		}
	}
	return Ok;
}//Draw_Wall

State Print_Info() {
	Set_Color(3, 0);
	int x, y;
	for (y = 0; y<HIGH; y++) {
		if (y % 5 == 2) {
			Gotoxy(WIDTH + FRAMEX - 14, FRAMEY + y);
			switch (y / 5) {
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
		if (y % 5 == 3) {
			Gotoxy(WIDTH + FRAMEX - 12, FRAMEY + y);
			switch (y / 5) {
				case 0: {
					printf("%2s", player.name);
					break;
				}
				case 1: {
					printf("%2dkm/h", snake->speed);
					break;
				}
				case 2: {
					printf("%02d:%02d", ((snake->finish-snake->start)/CLOCKS_PER_SEC/60), ((snake->finish-snake->start)/CLOCKS_PER_SEC%60));
					break;
				}
				case 3: {
					printf("%4d分", snake->score);
					break;
				}
				case 4: {
					printf("%2d米", snake->length);
					break;
				}
			}
		}
	}
	Set_Color(7, 0);
	return Ok;
}

State Game_Init() {
	snake->start = clock();
	snake->direction = 'd';
	snake->length = 0;
	snake->life = Ok;
	snake->score = 0;
	snake->speed = 500;
	snake->flag = 0;
	snake->body = (BODY *)malloc(WIDTH*HIGH*sizeof(BODY));
	for(int i=0; i<3; i++)
		Add_Body(FRAMEX+12-2*i, FRAMEY+HIGH-4);
	Creat_Food();
}

State Draw_Snake() {
	snake->finish = clock();
	Set_Color(7, 0);
	Gotoxy(snake->pre.X, snake->pre.Y);
	printf("  ");
	Gotoxy(snake->food.X, snake->food.Y);
	printf("●");
	for(int i=0; i<snake->length; i++) {
		Gotoxy(snake->body[i].coord.X, snake->body[i].coord.Y);
		if(i == 0)
			printf("●");
		else if(i == snake->length-1)
			printf("◎");
		else
			printf("○");
	}
	return Ok;
}

void Add_Body(int x , int y) {
	++snake->length;
	snake->body[snake->length -1].coord.X = x;
	snake->body[snake->length -1].coord.Y = y;
}

void Delete_Body() {
	Gotoxy(snake->body[snake->length-1].coord.X, snake->body[snake->length-1].coord.Y);
	printf("  ");
	snake->length--;
	snake->score -= 100;
}
void Time_Event() {
	int times = (snake->finish-snake->start)/CLOCKS_PER_SEC/30;
	if(((snake->finish-snake->start)/CLOCKS_PER_SEC%60 == 0) && ((snake->finish-snake->flag > 999))) {
		for(int i=0; i<times; i++) {
			Delete_Body();
			snake->flag = clock();
		}
	}


}
void Creat_Food() {
	short x, y;
	int flag = Ok;
	do {
		srand(time(NULL));
		x = rand()%(WIDTH - WIDTH2 -2)/2*2+FRAMEX+2;
		y = rand()%(HIGH-2)+FRAMEY+1;
		for(int i=0; i<snake->length; i++) {
			if(snake->body[i].coord.X == x && snake->body[i].coord.Y == y) {
				flag = False;
				break;
			}
		}
		if(flag) {
			snake->food.X = x;
			snake->food.Y = y;
			break;
		}
	} while(1);
}

void Eat_Food() {
	if(snake->body[0].coord.X == snake->food.X && snake->body[0].coord.Y == snake->food.Y) {
		Add_Body(snake->body[snake->length-1].coord.X, snake->body[snake->length-1].coord.Y);
		Creat_Food();
		snake->score += 100;
	}
}
State Snake_Life() {
	//snake die or not
	if(snake->length < 2)	return False;
	if(snake->body[0].coord.X<=FRAMEX || snake->body[0].coord.X>=FRAMEX+WIDTH-WIDTH2 || snake->body[0].coord.Y<=FRAMEY || snake->body[0].coord.Y>=FRAMEY+HIGH-1)
		return False;
	for(int i=4; i<snake->length; i++) {
		if((snake->body[i].coord.X == snake->body[0].coord.X) && (snake->body[i].coord.Y == snake->body[0].coord.Y))
			return False;
	}
	return Ok;
}

State Get_Direction() {
	snake->speed = 500;
	char temp;
	if(kbhit()) {
		temp = getch();
		if(temp == 'a' || temp == 's' || temp == 'd' || temp == 'w') {
			switch(temp) {
				case 'w': {
					if(temp == snake->direction)
						snake->speed += 200;
					if(snake->direction == 's')
						snake->direction = 's';
					else snake->direction = temp;
					break;
				}
				case 'a': {
					if(temp == snake->direction)
						snake->speed += 200;
					if(snake->direction == 'd')
						snake->direction = 'd';
					else snake->direction = temp;
					break;
				}
				case 's': {
					if(temp == snake->direction)
						snake->speed += 200;
					if(snake->direction == 'w')
						snake->direction = 'w';
					else snake->direction = temp;
					break;
				}
				case 'd': {
					if(temp == snake->direction)
						snake->speed += 200;
					if(snake->direction == 'a')
						snake->direction = 'a';
					else snake->direction = temp;
					break;
				}
			}

		} else if(temp == 'p') {
			Gotoxy(FRAMEX, FRAMEY+HIGH+4);
			printf("游戏已暂停,请按任意键继续 . . .");
			Gotoxy(FRAMEX, FRAMEY+HIGH+5);
			system("pause");
			for(int i=4; i<=5; i++) {
				Gotoxy(FRAMEX, FRAMEY+HIGH+4);
				for(int j=0; j<WIDTH; j++)
					printf("  ");
			}

		} else if(temp == 27)
			return False;
	}
	return Ok;
}
State Move_Snake() {
	//move snake
	for(int i=snake->length-1; i>0; i--) {
		if(i == snake->length-1)
			snake->pre = snake->body[i].coord;
		snake->body[i].coord = snake->body[i-1].coord;
	}
	switch(snake->direction) {
		case 'a':
			snake->body[0].coord.X -= 2;
			break;
		case 'd':
			snake->body[0].coord.X += 2;
			break;
		case 'w':
			snake->body[0].coord.Y -= 1;
			break;
		case 's':
			snake->body[0].coord.Y += 1;
			break;
	}
	return Ok;
}

State Game_Over() {
	system("cls");
	Draw_Frame();
	Gotoxy(FRAMEX+WIDTH/2-2, FRAMEY+HIGH/2-2);
	printf("游戏结束");
	Sleep(1500);
	Player_Save();
	return Ok;
}

State Start_Game() {
	system("cls");
	Game_Init();
	Draw_Wall();
	Print_Info();
	Hide_Cursor();
	while(1) {
		Draw_Wall();
		Print_Info();
		if(!Get_Direction()) {
			Game_Over();
			return False;
		}
		Move_Snake();
		Draw_Snake();
		Eat_Food();
		Time_Event();
		if(!Snake_Life()) {
			Game_Over();
			return False;
		}
		Sleep(800-snake->speed);
	}
}
