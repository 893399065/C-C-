#pragma once
/*  head file */
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
/* macro definition */
#define FRAMEX 25
#define FRAMEY 10
#define WIDTH2 18
#define HIGH 26
#define WIDTH 100
#define State int
#define Ok 1
#define False 0
#define Error -1

/*  struct of snake head */
typedef struct Snake_Head {
	COORD food;		//food coordin
	COORD pre;
	int speed;		//snake speed
	int length;		//snake length
	char direction;	//snake's direction
	int score;		//game score
	short life;		//if die or not
	clock_t start;	//game start time
	clock_t finish;	//game end	time
	clock_t flag;
	struct Snake_Body *body;
} SNAKE;

/* struct of snake body */
typedef struct Snake_Body {
	COORD coord;	//body coordin
} BODY;

/* struct of player information*/
typedef struct Player_Info {
	char name[10];		//player's name
	char password[10];	//player's password
	int score;			//best score
} PLAYER;

/* -----------------------------*/
/* --  function declaration   --*/
/* -----------------------------*/
/* about game */

State Draw_Wall();						//draw a wall
State Draw_Snake();						//draw Snake and food
State Print_Info();						//print game information
State Game_Init();						//game initialization
void Creat_Food();						//creat snake's food
void Add_Body(int x, int y);
void Delete_Body();
State Get_Direction();
void Eat_Food();
State Move_Snake();
State Snake_Life();
void Time_Event();
State Game_Over();
/* about menu */
State Menu();							//menu of program
State Player_Management();
/* about file */
void Rank_List();
State Player_Login();					//login
State Player_Register();				//register
State Player_Save();					//save player information
/* about public */
void Set_Color(unsigned short ForeColor,unsigned short BackGroundColor);
State Gotoxy(short x, short y);			//move cursor to (x,y)
void Hide_Cursor();						//hide console's cursor
void Show_Cursor();
State Draw_Frame();						//draw the game frame
State Start_Game();
/* -----------------------------*/
/* -----------end---------------*/
/* -----------------------------*/

/* global variable */

