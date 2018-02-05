#include "snake.h"
State Player_Login() {
	PLAYER temp;
	FILE *fp;
	int flag1 = False;
	fp = fopen("playerinfo", "r+");
	printf("请输入用户名: ");
	scanf("%s", player.name);
	if(!fp) {
		
		printf("打开文件失败!\n");
		exit(Error);
	}
	while(!feof(fp)) {
		fread(&temp, sizeof(PLAYER), 1, fp);
		if(strcmp(temp.name, player.name) == 0) {
			flag1 = Ok;
			break;
		}
	}
	if(flag1 == Ok) {
		do {
			printf("请输入密码: ");
			scanf("%s", player.password);
			system("clear");
		} while(strcmp(temp.password, player.password) != 0);
		fclose(fp);
		return Ok;
	} else {
		printf("用户名输入错误请重试!\n");
		fclose(fp);
		return False;
	}
}

State Player_Register() {
	int flag1 = Ok;
	PLAYER temp;
	FILE *fp;
	printf("请输入注册名: ");
	scanf("%s", player.name);
	if((fp = fopen("playerinfo.txt", "r")) != NULL) {
		
		while(!feof(fp)) {
			fread(&temp, sizeof(PLAYER), 1, fp);
			if(strcmp(temp.name, player.name) == 0) {
				flag1 = False;
				break;
			}
		}
	} else {
		if((fp = fopen("playerinfo.txt", "w")) == NULL) {
			printf("新建文件失败!\n");
			exit(Error);
		}
	}
	fclose(fp);
	if(flag1 == Ok) {
		if((fp = fopen("playerinfo.txt", "a")) == NULL) {
			printf("追加文件失败!\n");
			exit(Error);
		}
		printf("请输入密码: ");
		scanf("%s", player.password);
		fwrite(&player, sizeof(PLAYER), 1, fp);
		fclose(fp);
		return Ok;
	} else {
		printf("用户名已注册请重试!");
		return Error;
	}
}


