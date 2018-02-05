/**********************************
*程序名称：贪吃蛇游戏             *
*编译环境: dev c++ 5.11 		  *
*作    者: Mozzie                 *
*     <miaoyi893399065@gmail.com> *
*最后修改:2017/11/18              *
**********************************/
#include "snake.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
SNAKE a;								//snake head
SNAKE *snake = &a;
PLAYER player = {"Guest", "Guest", 200};							//player information
int main(int argc, char *argv[]) {
	system("title 贪吃蛇");
	system("mode con:cols=150 lines=50");
	while(!Player_Management());
	system("cls");
	while(1) {
		Menu();
	}

	return 0;
}
