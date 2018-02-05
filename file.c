/**********************************
State Player_Login()
State Player_Register()
State Save_Player()
**********************************/
#include "snake.h"
extern SNAKE *snake;
extern PLAYER player;
State Player_Login() {
	//only the player's name and password is right can be login
	system("cls");
	Draw_Frame();
	PLAYER temp;
	FILE *fp;
	int flag1 = False;
	fp = fopen("playerinfo.txt", "r");
	Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-2);
	printf("请输入用户名: ");
	scanf("%s", player.name);
	if (!fp) {
		//make sure file is opened
		Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-1);
		printf("打开文件失败!\n");
		exit(Error);
	}
	while (!feof(fp)) {
		//if the name is in file
		fread(&temp, sizeof(PLAYER), 1, fp);
		if (strcmp(temp.name, player.name) == 0) {
			flag1 = Ok;
			break;
		}
	}
	if (flag1 == Ok) {
		do {
			Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-1);
			//if the password is right
			printf("请输入密码: ");
			scanf("%s", player.password);
		} while (strcmp(temp.password, player.password) != 0);	//break when password is right
		player = temp;
		fclose(fp);
		return Ok;
	} else {
		Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-1);
		printf("用户名输入错误请重试!\n");
		fclose(fp);
		return False;
	}
}//Player_Login

State Player_Register() {
	system("cls");
	Draw_Frame();
	int flag1 = Ok;
	PLAYER temp;
	FILE *fp;
	Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-2);
	printf("请输入注册名: ");
	scanf("%s", player.name);
	if ((fp = fopen("playerinfo.txt", "r")) != NULL) {
		//if the name is exsist
		while (!feof(fp)) {
			fread(&temp, sizeof(PLAYER), 1, fp);
			if (strcmp(temp.name, player.name) == 0) {
				Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2);
				return False;
			}
		}
	} else {
		if((fp = fopen("playerinfo.txt", "w")) == NULL) {
			Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2);
			printf("新建文件失败!\n");
			return Error;
		}
	}
	fclose(fp);
	Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2);
	printf("请输入密码: ");
	scanf("%s", player.password);
	Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2+2);
	printf("注册成功!\n");
	Sleep(1000);
	return Ok;
}

State Player_Save() {
	//save player information
	FILE *fin;
	FILE *fout;
	PLAYER ptemp;
	if (((fin = fopen("playerinfo.txt", "r") )== NULL)|| ((fout = fopen("temp.txt", "w")) == NULL )) {
		fin = fopen("playerinfo.txt", "w");
		fclose(fin);
		fin = fopen("playerinfo.txt", "r");
		return Error;
	}
	while(!feof(fin)) {
		fread(&ptemp, sizeof(PLAYER), 1, fin);
		if(strcmp(ptemp.name, player.name)) {
			fwrite(&ptemp, sizeof(PLAYER), 1, fout);
		}
	}
	fclose(fin);
	fclose(fout);
	remove("playerinfo.txt");
	rename("temp.txt", "playerinfo.txt");
	if((fin = fopen("playerinfo.txt", "a+"))==NULL ) {
		printf("追加文件失败!\n");
		return Error;
	}
	fseek(fin, 0L, SEEK_SET);
	while(!feof(fin)) {
		fread(&ptemp, sizeof(PLAYER), 1, fin);
		if(ptemp.score > player.score) break;
	}
	fseek(fin, -(sizeof(PLAYER)), SEEK_CUR);
	fwrite(&player, sizeof(PLAYER), 1, fin);
	fclose(fin);
	return Ok;
}

void Rank_List() {
	system("cls");
	
	FILE *fp;
	fp = fopen("playerinfo.txt", "r");
	if(!fp) {
		printf("读取文件失败!\n");
	}
	PLAYER ptemp;
	int i=-2;
	while(!feof(fp)) {
		fread(&ptemp, sizeof(PLAYER), 1, fp);
		Gotoxy(FRAMEX+WIDTH/2-4, FRAMEY+HIGH/2-(i+=2));
		printf("%s\t%d", ptemp.name, ptemp.score);
	}
	fclose(fp);
	getch();
}
