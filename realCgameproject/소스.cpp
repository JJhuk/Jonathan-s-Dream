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

int select_opt;	//귀찮아서 그냥 전역번수임.

//함수명 gotoxy
//인자값인 x,y 에 대입하면 그 대입 한 곳으로 커서가 움직임

void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

//함수명 KeyControl
//기능 : 키를 받은 것을 return 함

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
	else if (temp == 13)	//13은 엔터의 아스키코드
		return SUBMIT;
}


// 함수명 : DrawTemplate
// 기능 : 게임의 틀을 출력하는함수
void DrawTemplate() {
	gotoxy(0, 0);
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
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
}

int DrawMenu() {
	DrawTemplate();
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
			if (y >= Menu_Y) {
				return y - Menu_Y + 1;	//1 2 3 순으로 리턴을 함
			}
		}
		}
	}
}
void gameInit() {
	select_opt = DrawMenu();		//1 게임시작 2 게임정보 3종료
}

void DrawCredit() {
	DrawTemplate();
	int x = Menu_X;
	int y = Menu_Y;
	gotoxy(x, y);
	printf("팀원명 : XXX(가칭)");
	gotoxy(x, y + 1);
	printf("조 원");
	gotoxy(x, y + 2);
	printf("이주혁");
	gotoxy(x, y + 3);
	printf("성희연");
	gotoxy(x, y + 4);
	printf("박주윤");
	gotoxy(x, y + 5);
	printf("이석호");
	_getch();
}


int main()
{
	bool GameStart = true;

	while (GameStart) {
		system("cls");
		gameInit();

		switch (select_opt) {
		case 1:
			DrawTemplate();
			_getch();
			system("cls");
			break;
		case 2:
			DrawCredit();
			system("cls");
			break;
		case 3:
			GameStart = false;
		}
	}
	return 0;
}


