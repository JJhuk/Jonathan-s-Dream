#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 //선택 엔터
#define Menu_X 40
#define Menu_Y 24

#define IMGSIZE_W 7
#define IMGSIZE_H 4

#define FOLLOWUP_START_X 10
#define FOLLOWUP_START_Y 4

#define FOLLOWUP_START_INPUT_X 38
#define FOLLOWUP_START_INPUT_Y 21

char strkey[4][IMGSIZE_H][IMGSIZE_W] = {
	{
	"  @@  ",
	" @@@@ ",
	"@@@@@@",
	},
	{
	"@@@@@@",
	" @@@@ ",
	"  @@  "
	},
	{
	" @@@@",
	"@@@@@",
	" @@@@"
	},
	{
	"@@@@ ",
	"@@@@@",
	"@@@@ "
	}
};

int select_opt;	//귀찮아서 그냥 전역번수임.

ifstream in;

//함수명 gotoxy
//인자값인 x,y 에 대입하면 그 대입 한 곳으로 커서가 움직임
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}



// 입력 이벤트 출력
// 함수명 : DrawTemplate
// 기능 : 게임의 틀을 출력하는함수
void DrawFollowUPTemplate() {
	system("cls");
	gotoxy(0, 0); //첫 |부분 6,3
	printf("========================================================================================================================\n");
	printf("|                                                                                                                      |\n");
	printf("|     =============      =============      =============      =============                                           |\n");
	printf("|     |           |      |           |      |           |      |           |                                           |\n");
	printf("|     |           |      |           |      |           |      |           |                                           |\n");
	printf("|     |           |      |           |      |           |      |           |                                           |\n");
	printf("|     |           |      |           |      |           |      |           |                                           |\n");
	printf("|     |           |      |           |      |           |      |           |                                           |\n");
	printf("|     =============      =============      =============      =============                                           |\n");
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
	printf("|                                  =============      =============      =============      =============              |\n");
	printf("|                                  |           |      |           |      |           |      |           |              |\n");
	printf("|                                  |           |      |           |      |           |      |           |              |\n");
	printf("|                                  |           |      |           |      |           |      |           |              |\n");
	printf("|                                  |           |      |           |      |           |      |           |              |\n");
	printf("|                                  |           |      |           |      |           |      |           |              |\n");
	printf("|                                  =============      =============      =============      =============              |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
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
	char temp;

	while (true) {
		temp = _getch();
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

}

void Drawstrkey(int x, int y, int answer) {
	gotoxy(x, y);
	for (int i = 0; i < IMGSIZE_H; i++) {
		for (int j = 0; j < IMGSIZE_W; j++) {
			printf("%c", strkey[answer][i][j]);
		}
		gotoxy(x, ++y);
	}
}

bool FollowUP_game() {
	DrawFollowUPTemplate();
	srand(time(NULL));
	int answer[4];
	char inPut[4];
	for (int z = 0; z < 4; z++) {// 문제 생성
		answer[z] = rand() % 4; //0~3까지 난수생성 == up down left right

		if (answer[z] == UP) {
			Drawstrkey(FOLLOWUP_START_X+(z*19), FOLLOWUP_START_Y, UP);
			Sleep(250);
		}
		else if (answer[z] == DOWN) {
			Drawstrkey(FOLLOWUP_START_X+(z * 19), FOLLOWUP_START_Y, DOWN);
			Sleep(250);
		}
		else if (answer[z] == LEFT) {
			Drawstrkey(FOLLOWUP_START_X + (z * 19), FOLLOWUP_START_Y, LEFT);
			Sleep(250);
		}
		else if (answer[z] == RIGHT) {
			Drawstrkey(FOLLOWUP_START_X + (z * 19), FOLLOWUP_START_Y, RIGHT);
			Sleep(250);
		}
	}
	DrawFollowUPTemplate(); 
	for (int z1 = 0; z1 < 4; z1++) {	//정답 입력
		inPut[z1] = KeyControl();
		if (inPut[z1] == UP) {
			Drawstrkey(FOLLOWUP_START_INPUT_X + (z1 * 19), FOLLOWUP_START_INPUT_Y, UP);
			Sleep(250);
		}
		else if (inPut[z1] == DOWN) {
			Drawstrkey(FOLLOWUP_START_INPUT_X + (z1 * 19), FOLLOWUP_START_INPUT_Y, DOWN);
			Sleep(250);
		}
		else if (inPut[z1] == LEFT) {
			Drawstrkey(FOLLOWUP_START_INPUT_X + (z1 * 19), FOLLOWUP_START_INPUT_Y, LEFT);
			Sleep(250);
		}
		else if (inPut[z1] == RIGHT) {
			Drawstrkey(FOLLOWUP_START_INPUT_X + (z1 * 19), FOLLOWUP_START_INPUT_Y, RIGHT);
			Sleep(250);
		}
	}

	if (inPut[0] == answer[0] && inPut[1] == answer[1] && inPut[2] == answer[2] && inPut[3] == answer[3]) 
		return true;
	else
		return false;

}

void textBox() {
	system("cls");
	gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 
	printf("=======================================================================================================================\n");
	printf("|                                                                                                                     |\n");
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
	printf("|                                                                                                                     |\n");
	printf("|      ======== 이름   ===================================================================================            |\n");
	printf("|      |                                                                                                 |            |\n");
	printf("|      |                                                                                                 |            |\n");
	printf("|      |                                                                                                 |            |\n");
	printf("|      |                                                                                                 |            |\n");
	printf("|      |                                                                                                 |            |\n");
	printf("|      |                                                                                                 |            |\n");
	printf("|      |                                                                                                 |            |\n");
	printf("|      ===================================================================================================            |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                                                                     |\n");
	printf("=======================================================================================================================\n");
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
		printf("|                     ■■■■■■■■■■■■■■■■■■■                            ■ : 플레이어                  |\n");
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
		printf("|                           ※                                 ☜■☞                         ※                       |\n");
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


void textmanager() {
	string s;
	
	POINT p;
	in.open("C:\\Users\\LeeJuHyuk\\source\\repos\\SmugCgame\\realCgameproject\\text.txt");
	bool isName = TRUE;
	while (getline(in, s)) {
		istringstream ss(s);
		string sub_s;
		while (getline(ss, sub_s, '\t')) {
			p = { 11,20 };
			if (isName) {
				textBox();
				gotoxy(16, 18);
				cout << sub_s;
			}
			else {
				gotoxy(p.x, p.y);
				for (int i = 0; i < sub_s.length(); i++) {
					Sleep(50);
					cout << sub_s[i];
					if (sub_s[i] == '.' && sub_s[i + 1] == '!') {
						p.y++;
						i++;
						gotoxy(p.x, p.y);
					}

				}
			}
			if (!isName) {
				gotoxy(100, 24);
				printf("▼");
				_getch();
			}
			isName = !isName;
		}
	}
	in.close();
}


int main()
{
	bool GameStart = true;
	bool IsOKFollowUP_game = false;

	while (GameStart) {
		gameInit();

		switch (select_opt) {
		case 1:	//start
			//DrawStartExemple();
			textmanager();
			IsOKFollowUP_game = FollowUP_game();
			system("cls");
			gotoxy(0, 0);
			if (IsOKFollowUP_game)
				printf("정답입니다!!!!!!!!!!!!!!");
			else
				printf("틀렸습니다 ㅜㅜㅜㅜㅜㅜㅜㅜㅜ");
			_getch();
			
			break;
		case 2:	//credit
			DrawCredit();
			system("cls");
			break;
		case 3:	//exit
			GameStart = false;
		}
	}
	return 0;
}


