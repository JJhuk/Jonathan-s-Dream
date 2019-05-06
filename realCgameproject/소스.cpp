#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 //선택 엔터
#define Menu_X 10
#define Menu_Y 20

void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int KeyControl() {
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
		return UP;
	else if (temp == 'a' || temp == 'A')
		return LEFT;
	else if (temp == 's' || temp == 'S')
		return DOWN;
	else if (temp == 'd' || temp == 'D')
		return RIGHT;
	else if (temp == 13)
		return SUBMIT;
}

//hello world

int DrawMenu() {
	printf("========================================================================================================================\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
	int x = Menu_X;
	int y = Menu_Y;
	gotoxy(x - 2, y);
	printf("> 게임 시작 ");
	gotoxy(x, y + 1);
	printf("게 임 정 보");
	gotoxy(x, y + 2);
	printf("   종 료   ");
	while (1) {
		int n = KeyControl();
		switch (n) {
		case UP: {
			if (y > Menu_Y) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < Menu_Y + 2) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			if (y > Menu_Y) {
				return y - 12;
			}
		}
		}
	}
}
void gameInit() {
	int select_opt;
	select_opt = DrawMenu();
	printf("선택한 매뉴 : %d\n", select_opt);
}


int main()
{
	bool GameStart = true;

	gameInit();

	return 0;
}


