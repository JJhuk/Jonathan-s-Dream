#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 //선택 엔터
#define Menu_X 40
#define Menu_Y 24

int select_opt;	//귀찮아서 그냥 전역번수임.

//함수명 gotoxy
//인자값인 x,y 에 대입하면 그 대입 한 곳으로 커서가 움직임
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


//커서 지워주는 함수
//CONSOLE_CURSOR_INFO 콘솔의 커서 정보를 얻기 위한 구조체
//GetConsoleCursorInfo 콘솔 출력창 정보 반환
void RemoveCursor(void) {
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0; //bVisible 멤버 변경
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);	//변경값 적용
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
	printf("========================================================================================================================\n");
}

void DrawMain() {
	printf("=======================================================================================================================\n");
	printf("|     ∴                                            ∴                                                          ∴    |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                             ∴                                      |\n");
	printf("|                 ∴                                                                                                  |\n");
	printf("|                                                                                                ∴                   |\n");
	printf("|                                                 ∴                                                                  |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                                                                     |\n");
	printf("|     ∴                                                                                                              |\n");
	printf("|                                                                                                                     |\n");
	printf("|                             ∴                                              Dreams of Jonathan                      |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                    ∴                                                               |\n");
	printf("|                                                                                                                     |\n");
	printf("|                        ∴                                                       ∴                                  |\n");
	printf("|                                                                                                      ∴             |\n");
	printf("|       ／￣￣ ↘             ／￣￣ ↘           ／￣￣ ↘           ／￣￣ ↘          ／￣￣ ↘                    |\n");
	printf("|     ／     ^     ↘       ／      ^   ↘       ／      ^  ↘     ／     ^    ↘       ／     ^   ↘                 |\n");
	printf("|   ／      |  √_ ／  ／          |  √_／   ／      | √_ ／      ／     |  √_ ／   ／    |  √_ ／                |\n");
	printf("| ／          ↘ ___／          ↘ ____／          ↘ ___／         ↘ ____／       ↘ _________  |                   |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                                                                     |\n");
	printf("=======================================================================================================================\n");
}

void DrawStartExemple() {	//이함수는 나중에 프로젝트 할때는 안쓸꺼임 그냥 프로토타입용
	system("cls");
		printf("=======================================================================================================================\n");
		printf("|                                                                                                              UI예시1|\n");
		printf("|   ☆                                  ☆                                                             ☆             |\n");
		printf("|              ★                                              ☆                        ★                           |\n");
		printf("|                        ☆                                                                                           |\n");
		printf("|                                                                                                           ★        |\n");
		printf("|      ★                                                  ★              ☆                                         |\n");
		printf("|                                        ☆                                                                           |\n");
		printf("|                                                                                                   ☆                |\n");
		printf("|                ☆                                                                                                   |\n");
		printf("|                                ★                     ☆                                                            |\n");
		printf("|                                                                                   ★                                |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|      ======== 조나단 ===================================================================================            |\n");
		printf("|      |                                                                                                 |            |\n");
		printf("|      |                                                                                                 |            |\n");
		printf("|      |     나는 내가 하늘에서 무엇을 할 수 있고 무엇을 할 수 없는지 알고 싶어요. 그 뿐이에요.          |            |\n");
		printf("|      |     다른 이들처럼 되는 것에 대해서는 생각하지 마세요.                                           |            |\n");
		printf("|      |     그보다 행복은 스스로의 한계를 탐구하는 데서 와요.                                           |            |\n");
		printf("|      |                                                                                                 |            |\n");
		printf("|      |                                                                                                 |            |\n");
		printf("|      ===================================================================================================            |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("=======================================================================================================================\n");
		gotoxy(0, 0);
		_getch();
		system("cls");
		printf("======================================================================================================================\n");
		printf("|                                                                                                              UI예시2|\n");
		printf("|                       ■■■■■■■■■■■■                                                                      |\n");
		printf("|                       ■■■■■■■■■■■■                                                                      |\n");
		printf("|                       ■■                ■■                                                                      |\n");
		printf("|                       ■■                ■■                                                                      |\n");
		printf("|             ■■■■■■■   ●           ■■■■■■■                                                            |\n");
		printf("|             ■■■■■■■            ●  ■■■■■■■                                                            |\n");
		printf("|             ■■                                  ■■■              ■■■■■■■■■■■■■■■■              |\n");
		printf("|       ■■■■■          ●          ●          ■■■              ■■■■■■■■■■■■■■■■              |\n");
		printf("|       ■■■■■                                  ■■■              ■■■                      ■■              |\n");
		printf("|       ■■■            ■■     ■■■■■       ■■■■■■■■■■■■■              ○  ○  ■■              |\n");
		printf("| ■■■■■■            ■■     ■■■■■       ■■■■■■■■■■■■■                      ■■              |\n");
		printf("| ■■■■■■            ■■     ■■■■■                                               ○  ○  ■■              |\n");
		printf("| ■■                                                                                              ■■              |\n");
		printf("| ■■  ●                 ●                           ■■＠■■■■■■■■              ○  ○  ■■              |\n");
		printf("| ■■                        ■■■■■■■■          ■■■■■■■■■■■                      ■■              |\n");
		printf("| ■■■■■■■■■■■■    ■■■■■■■■          ■■              ■■■■■■■■■■■■■■■              |\n");
		printf("| ■■■■■■■■■■■■                              ■■              ■■■■■■■■■■■■■■■              |\n");
		printf("|                     ■■                              ■■                                                          |\n");
		printf("|                     ■■■■■■■■■■■■■■■■■■■                                                          |\n");
		printf("|                     ■■■■■■■■■■■■■■■■■■■                            @ : 플레이어                  |\n");
		printf("|                                                                                      ■ : 벽                        |\n");
		printf("|                                                                                      ○ : 구멍                      |\n");
		printf("|                                                                                      ● : 밀어야할 돌               |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                      - R를 눌러 재시도 하기         |\n");
		printf("|                                                                                                                     |\n");
		printf("=======================================================================================================================\n");
		gotoxy(0, 0);
		_getch();
		system("cls");
		printf("=======================================================================================================================\n");
		printf("|피하자! 조나단!                                                                                               UI예시3|\n");
		printf("|                                                                                                                     |\n");
		printf("|          ^.^                                                                  ^,^                                   |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                 ^.^                                           ^.^                   |\n");
		printf("|                                                                                                                     |\n");
		printf("|                              ^.^                                                                                    |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|    ^.^                                                             ^.^                                              |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                        ^.^                                                                          |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                  ^.^                                |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|                       ↓                                                                                            |\n");
		printf("|                      ^.^                                                                                            |\n");
		printf("|                                                                    ↓                                               |\n");
		printf("|                                                                   ^.^                               ↓              |\n");
		printf("|                                                                                                    ^,^              |\n");
		printf("|              ↓                                                                                                     |\n");
		printf("|             ^.^                                                                                                     |\n");
		printf("|                           ※                                 ☜@☞                         ※                       |\n");
		printf("|     ================================================================================================================|\n");
		printf("|                                                                                                                     |\n");
		printf("=======================================================================================================================\n");
		gotoxy(0, 0);
}

void DrawCredit() {
	system("cls");
	printf("========================================================================================================================\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                              ■          ■      ■                     ■       ■      ■         ■■             |\n");
	printf("|         ■■■■■■■       ■      ■■■■■  ■           ■■■    ■      ■ ■  ■■      ■■■■■          |\n");
	printf("|                     ■       ■         ■■     ■          ■    ■   ■     ■   ■   ■        ■  ■            |\n");
	printf("|                    ■        ■        ■  ■    ■           ■■■    ■                           ■              |\n");
	printf("|                   ■         ■         ■■     ■                     ■        ■■■■           ■              |\n");
	printf("|                  ■          ■          ■      ■                                     ■       ■■■■■■        |\n");
	printf("|                 ■           ■        ■■■■  ■                                                                  |\n");
	printf("|                              ■                                                                                      |\n");
	printf("|                              ■          ■■■■■                          ■  ■  ■  ■                          |\n");
	printf("|                              ■                  ■                        ■  ■  ■  ■■                          |\n");
	printf("|                                                                          ■                ■■                      |\n");
	printf("|                                                                        ■   ◎     ★          ■■                  |\n");
	printf("|                                                                  ■■■■                      ■■■■              |\n");
	printf("|                                ■                                  ■■■  ■■■              ■■■                |\n");
	printf("|                        ■      ■■■■■■■■■■■                ■■    ■■               ■                    |\n");
	printf("|                        ■        ■■■■■ ■       ■■               ■                    ■                     |\n");
	printf("|                        ■■■■■■■■■■■       ■■■■               ■                ■                       |\n");
	printf("|                        ■        ■■■■■ ■       ■■                   ■■■■■■■■                         |\n");
	printf("|                        ■      ■■■■■■■■■■■                           ■       ■                          |\n");
	printf("|                                ■                                             ■ ■     ■ ■                        |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
	gotoxy(0, 0);
	_getch();
	system("cls");
	printf("========================================================================================================================\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                    ■            ■       ■        ■    ■     ■■       ■       |\n");
	printf("|            ■■■■■■■                          ■           ■ ■   ■■     ■■■■ ■    ■  ■  ■■■       |\n");
	printf("|              ■      ■               ■■■■■   ■          ■   ■    ■      ■  ■  ■    ■  ■      ■       |\n");
	printf("|              ■      ■               ■      ■   ■                 ■■         ■■   ■     ■■   ■■■       |\n");
	printf("|            ■■■■■■■             ■      ■   ■                ■   ■    ■■■■■■      ■        ■       |\n");
	printf("|                                       ■      ■   ■                 ■■                ■      ■■■■■■       |\n");
	printf("|         ■■■■■■■■■■■        ■■■■■   ■                                                                |\n");
	printf("|                                                    ■                               ■■■■                         |\n");
	printf("|            ■■■■■■■                   ■■■          ■■                  ○  ○     ■                      |\n");
	printf("|                        ■                  ■    ■         ■■           ■■■■■■      ■                      |\n");
	printf("|            ■■■■■■■                  ■    ■         ■■                  ■          ■                     |\n");
	printf("|            ■                               ■■■          ■■■■■■■■■  ■       ■■■■■■                |\n");
	printf("|            ■■■■■■■                                   ■■  ■          ■         ■         ■■■           |\n");
	printf("|                                                              ■     ■          ■       ■            ■            |\n");
	printf("|                                                                       ■        ■         ■■■■■■              |\n");
	printf("|                                                                         ■■■■■                   ■              |\n");
	printf("|                       ■               ■■                                     ■■                ■■■           |\n");
	printf("|                      ■ ■           ■                                       ■   ■■■■■■■■■   ■           |\n");
	printf("|                     ■■■           ■                                       ■■                    ■             |\n");
	printf("|                    ■     ■         ■                                         ■                   ■              |\n");
	printf("|                                        ■■                                   ■  ■■■■■■■■■■ ■            |\n");
	printf("|                                                                                   ■       ■         ■             |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
	gotoxy(0, 0);
	_getch();
	system("cls");
	printf("========================================================================================================================\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                    ■            ■      ■    ■■■■■        ■         ■       |\n");
	printf("|            ■■■■■■■                          ■          ■  ■    ■        ■         ■■■■■■■■       |\n");
	printf("|              ■      ■               ■■■■■   ■          ■  ■    ■       ■ ■         ■  ■      ■       |\n");
	printf("|              ■      ■               ■      ■   ■            ■      ■       ■  ■         ■■   ■■■       |\n");
	printf("|            ■■■■■■■             ■      ■   ■                    ■    ■■■■■■                 ■       |\n");
	printf("|                                       ■      ■   ■                    ■         ■              ■■■■■       |\n");
	printf("|         ■■■■■■■■■■■        ■■■■■   ■                               ■                      ■       |\n");
	printf("|                                                    ■                                                                |\n");
	printf("|            ■■■■■■■                   ■■■                              ■■■■■                           |\n");
	printf("|                        ■                  ■    ■                        ■■■■    ■■■■                      |\n");
	printf("|            ■■■■■■■                  ■    ■                          ■■■■■■■■                        |\n");
	printf("|            ■                               ■■■                 ■      ■  ■■    ■■  ■      ■              |\n");
	printf("|            ■■■■■■■                                          ■■  ■■                ■■  ■■              |\n");
	printf("|                                                                     ■■■■       ■■       ■■■■               |\n");
	printf("|                                                                       ■■■        ■        ■■■                 |\n");
	printf("|                                          ■                                ■                ■                      |\n");
	printf("|                           ■           ■  ■                                ■  ■■■■  ■                        |\n");
	printf("|                         ■  ■           ■                                    ■        ■                          |\n");
	printf("|                         ■  ■                                               ■■■■■■■■■                      |\n");
	printf("|                         ■  ■                                             ■                  ■                    |\n");
	printf("|                           ■                 ■                          ■                     ■                   |\n");
	printf("|                                            ■  ■                        ■■■■■■■■■■■■■                  |\n");
	printf("|                                              ■                          ■         ■■■       ■                  |\n");
	printf("|                                                                          ■       ■     ■      ■                  |\n");
	printf("|                                                                          ■       ■     ■      ■                  |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
	gotoxy(0, 0);
	_getch();
	system("cls");
	printf("========================================================================================================================\n");
	printf("|                                                                                                                      |\n");
	printf("|                      ■                ■                  ■    ■  ■  ■       ■■■■■        ■■■           |\n");
	printf("|         ■■■■■   ■  ■■■■■■  ■        ■■■    ■    ■■■  ■■         ■           ■    ■          |\n");
	printf("|         ■           ■      ■        ■      ■     ■   ■    ■  ■  ■          ■ ■          ■■■           |\n");
	printf("|         ■           ■     ■ ■      ■      ■     ■   ■    ■■■  ■         ■   ■      ■■■■■■        |\n");
	printf("|         ■           ■    ■   ■     ■■■  ■     ■   ■                                       ■  ■           |\n");
	printf("|         ■           ■   ■     ■    ■        ■■■    ■     ■■■■        ■■■■■       ■                |\n");
	printf("|         ■           ■                ■          ■      ■           ■            ■           ■■■■          |\n");
	printf("|         ■■■■■   ■                ■          ■                                                                |\n");
	printf("|                      ■                ■          ■■■■■                                                        |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                 ■■■■■                          ■■■■         |\n");
	printf("|                                   ■■■■■■■■■■        ■          ■■                    ■        ■       |\n");
	printf("|                                   ■     ■■       ■       ■ ■■■       ■                  ■   ＠      ■     |\n");
	printf("|                                   ■    ■■■      ■             ■        ■          ■■■■             ■     |\n");
	printf("|                                   ■   ■■■■     ■               ■      ■■          ■■■              ■    |\n");
	printf("|                                   ■     ■■       ■                 ■■■     ■              ■ ■ ■ ■        |\n");
	printf("|                                   ■                ■                    ■       ■         ■■                   |\n");
	printf("|                                   ■■■■■■■■■■                      ■      ■       ■                      |\n");
	printf("|                                            ■                                 ■    ■      ■                       |\n");
	printf("|                                            ■                                   ■■  ■    ■                       |\n");
	printf("|                                            ■                                       ■  ■ ■                        |\n");
	printf("|                                          ■  ■                                       ■  ■                         |\n");
	printf("|                                         ■     ■                                       ■ ■                        |\n");
	printf("|                                                                                           ■                         |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
	gotoxy(0, 0);
	_getch();
	system("cls");
}


int DrawMenu() {
	DrawMain();
	int x = Menu_X;
	int y = Menu_Y;
	gotoxy(x - 2, y);
	printf("▶  start ◀");
	gotoxy(x, y + 1);
	printf("  credit  ");
	gotoxy(x, y + 2);
	printf("  exit  ");
	while (1) {
		int n = KeyControl();
		switch (n) {
		case UP: {
			if (y > Menu_Y) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x + 8, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf("▶");
				gotoxy(x + 8, y);
				printf("◀");
			}
			break;
		}
		case DOWN: {
			if (y < Menu_Y + 2) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x + 8, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf("▶");
				gotoxy(x + 8, y);
				printf("◀");
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
	RemoveCursor();
	system("cls");
	select_opt = DrawMenu();		//1 게임시작 2 게임정보 3종료
}

int main()
{
	bool GameStart = true;

	while (GameStart) {
		gameInit();

		switch (select_opt) {
		case 1:
			DrawStartExemple();
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


