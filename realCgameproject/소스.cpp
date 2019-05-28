#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <stddef.h>
#include <locale.h>

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

wchar_t info[6] = { L"★●◎■○" };

char stage[14][60] = { '\0', };
const char StageData[14][60] =
{
	{"                                                           "},
	{"                                                           "},
	{"                               [][][][][][][]              "},
	{"                               []  x       []              "},
	{"           [][][][][]          []  [][]    [][][][][][]    "},
	{"           []    @+[][][][][]  []          x     x   []    "},
	{"   [][][][][]  []  [][]    []  []          []  []    []    "},
	{"   []  0O      0O      0O  []  []      [][][]  0O    []    "},
	{"   []  []  [][]x     x []x [][][][]0O  []    0O    [][][][]"},
	{"   []            [][]  x   []          []  0O            []"},
	{"   [][][][][][][][][][]        0O  [][][]          x     []"},
	{"                     []  0O    []  []  [][][][][][][][][][]"},
	{"                     []x [][]      []                      "},
	{"                     [][][][][][][][]                      "}
};
int currentX = 0, currentY = 0;
int RestartValue;

int select_opt;	//귀찮아서 그냥 전역번수임.

ifstream in;	//파일 출력

//함수명 Gotoxy
//인자값인 x,y 에 대입하면 그 대입 한 곳으로 커서가 움직임
void Gotoxy(int x, int y) {
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
	Gotoxy(0, 0); //첫 |부분 6,3
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
	Gotoxy(x, y);
	for (int i = 0; i < IMGSIZE_H; i++) {
		for (int j = 0; j < IMGSIZE_W; j++) {
			printf("%c", strkey[answer][i][j]);
		}
		Gotoxy(x, ++y);
	}
}

bool FollowUP_Game() {
	DrawFollowUPTemplate();
	srand(time(NULL));
	int answer[4];
	char inPut[4];
	bool IsCorrectAnswer = false;
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
		IsCorrectAnswer = true;
	else
		IsCorrectAnswer = false;
	system("cls");
	Gotoxy(0, 0);
	if (IsCorrectAnswer) {
		printf("정답입니다!!!!!!!!!!!!!!");
		_getch();
		return true;
	}
		
	else {
		printf("틀렸습니다!!!!!!!!!!!!!!");
		_getch();
		return false;
	}
}

/*r이나 R을 누르면 재시작할 수 있는 함수*/
void Restart() {
	RestartValue = 1; //RestartValue가 1이면 재시작 
}


/* 플레이어의 키를 받는 함수 WASD로 조작 */
void PlayerControl() {
	int dx = 0, dy = 0; // 플레이어가 움직이면 변하는 좌표의 변화값
	char temp = _getch(); //  _getch()함수는 문자 하나 입력을 대기
	if (temp == 'w' || temp == 'W') {
		dx = 0, dy = -1;
		//return UP;
	}
	else if (temp == 's' || temp == 'S') {
		dx = 0, dy = 1;
		//return DOWN;
	}
	else if (temp == 'a' || temp == 'A') {
		dx = -2, dy = 0;
		//return LEFT;
	}
	else if (temp == 'd' || temp == 'D') {
		dx = 2, dy = 0;
		//return RIGHT;
	}
	else if (temp == 'r' || temp == 'R') { //재시도
		Restart();
	}

	if (stage[currentY + dy][currentX + dx] == '[') { //벽을 만나면 아무것도 안함
		return;
	}
	if (stage[currentY + dy][currentX + dx] == '0') { //바위를 만나면 앞에는 숫자0 뒤에는 대문자 O
		if (stage[currentY + dy * 2][currentX + dx * 2] == ' ') { // 바위를 민다  ok
			stage[currentY + dy][currentX + dx] = ' ';
			stage[currentY + dy][currentX + dx + 1] = ' ';
			stage[currentY + dy * 2][currentX + dx * 2] = '0';
			stage[currentY + dy * 2][currentX + dx * 2 + 1] = 'O';
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == '0') { //바위가 두개 있으면 밀리지 않음 ok
			return;
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == 'x') { //목적지에 도달하면 X을 로 바꿈
			stage[currentY + dy][currentX + dx] = ' ';
			stage[currentY + dy][currentX + dx + 1] = ' ';
			stage[currentY + dy * 2][currentX + dx * 2] = '<';
			stage[currentY + dy * 2][currentX + dx * 2 + 1] = '>';
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == '<') {
			stage[currentY + dy][currentX + dx] = ' ';
			stage[currentY + dy][currentX + dx + 1] = ' ';
			stage[currentY + dy * 2][currentX + dx * 2] = '0';
			stage[currentY + dy * 2][currentX + dx * 2 + 1] = 'O';
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == '[') { //벽이면 아무것도 안함 ok
			return;
		}
	}


	currentX += dx;
	currentY += dy;
}

/*스테이지를 그리고, 플레이어 출력*/
void DrawStage() {
	//wchar_t info[6] = { L"★●◎■○" };
	setlocale(LC_ALL, "");
	for (int stageY = 0; stageY < 14; stageY++) {
		for (int stageX = 0; stageX < 60; stageX++) {

			Gotoxy(stageX, stageY);
			_putch(stage[stageY][stageX]);

		}
	}
	Gotoxy(currentX, currentY); //플레이어의 현재 좌표에 가서 플레이어를 나타냄
	putwchar(info[0]);
}


/*스테이지를 클리어 했는지 확인하는 함수*/
int StageClear() {
	int cx = 0, cy = 0;
	int count = 0;
	for (cy = 0; cy < 12; cy++) {
		for (cx = 0; cx < 57; cx++) {
			if (stage[cy][cx] == 'x' || stage[cy][cx] == '0') //.이 있거나 o이 있으면 count++
				count++;
		}
	}
	if (count == 0) {
		return 1;
	}
	else if (count != 0) {
		return 2;
	}
}//난 클리어했다!!!!!!!!!!!!!!!

void printInfo() {
	Gotoxy(68, 2);
	printf("PLAYER : ★");
	Gotoxy(68, 3);
	printf("  ROCK : 0O");
	Gotoxy(68, 4);
	printf("  HOLE : x ");
	Gotoxy(68, 5);
	printf(" CLEAR : <>");
	Gotoxy(73, 7);
	printf("U P");
	Gotoxy(74, 8);
	printf("W");
	Gotoxy(66, 9);
	printf("LEFT A     D RIGHT");
	Gotoxy(74, 10);
	printf("S");
	Gotoxy(73, 11);
	printf("DOWN");
	Gotoxy(67, 13);
	printf("- R을 눌러 다시 하기");
}

bool Sokoban_Game() {
	setlocale(LC_ALL, "");
	int x = 0, y = 0;
	while (1) {
		memcpy(stage, StageData, sizeof(stage)); //memcpy는 메모리를 복사
		for (y = 0; y < 14; y++) { //플레이어를 찾아서 좌표를 입력받고, 원래 있던 자리는 공백으로
			for (x = 0; x < 60; x++) {
				if (stage[y][x] == '@' && stage[y][x + 1] == '+') {
					currentX = x; //플레이어 현재 좌표 저장
					currentY = y;
					stage[y][x] = ' ';
					stage[y][x + 1] = ' ';//이동했으므로 원래 있던 자리는 공백으로
				}
			}
		}
		system("cls");
		while (1) {
			DrawStage(); // 스테이지와 플레이어 출력
			printInfo();
			PlayerControl(); //플레이어, 바위의 움직임 구현
			if (RestartValue == 1) {
				RestartValue = 0;
				break;
			}

			if (StageClear() == 1) { //스테이지를 깬다면 프로그램 종료
				system("cls");
				DrawStage();
				printInfo();
				_getch();
				Sleep(10);
				system("cls");
				return true;
			}
		}
	}
}

void TextBox() {
	system("cls");
	Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 
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
		Gotoxy(0, 0);
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
		Gotoxy(0, 0);
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
		Gotoxy(0, 0);
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
	Gotoxy(0, 0);
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
	Gotoxy(0, 0);
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
	Gotoxy(0, 0);
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
	Gotoxy(0, 0);
	_getch();
	system("cls");
}

int DrawMenu() {
	DrawMain();
	int x = Menu_X;
	int y = Menu_Y;
	Gotoxy(x - 2, y);
	printf("▶  start ◀");
	Gotoxy(x, y + 1);
	printf("  credit  ");
	Gotoxy(x, y + 2);
	printf("  exit  ");
	while (1) {
		int n = KeyControl();
		switch (n) {
		case UP: {
			if (y > Menu_Y) {
				Gotoxy(x - 2, y);
				printf(" ");
				Gotoxy(x + 8, y);
				printf(" ");
				Gotoxy(x - 2, --y);
				printf("▶");
				Gotoxy(x + 8, y);
				printf("◀");
			}
			break;
		}
		case DOWN: {
			if (y < Menu_Y + 2) {
				Gotoxy(x - 2, y);
				printf(" ");
				Gotoxy(x + 8, y);
				printf(" ");
				Gotoxy(x - 2, ++y);
				printf("▶");
				Gotoxy(x + 8, y);
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

void GameInit() {
	RemoveCursor();
	system("cls");
	select_opt = DrawMenu();		//1 게임시작 2 게임정보 3종료
}

void TextManager() {
	string s;
	
	POINT p;
	in.open("C:\\Users\\LeeJuHyuk\\source\\repos\\SmugCgame\\realCgameproject\\text.txt");	//각 챕터마다 파일을 다르게 입력해야함.
	bool isName = TRUE;
	while (getline(in, s)) {
		istringstream ss(s);
		string sub_s;
		while (getline(ss, sub_s, '\t')) {
			p = { 11,20 };
			if (isName) {
				TextBox();
				Gotoxy(16, 18);
				cout << sub_s;
			}
			else {
				Gotoxy(p.x, p.y);
				for (int i = 0; i < sub_s.length(); i++) {
					Sleep(50);
					//여기에 자판소리 추가하면 될듯
					printf("%c", sub_s[i]);
					if (sub_s[i] == '.' && sub_s[i + 1] == '!') {	//이때 2번째줄부터 한칸 띄우고 텍스트가 출력되는 버그가 있음.
						p.y++;
						i++;
						Gotoxy(p.x, p.y);
					}
				}
			}
			if (!isName) {
				Gotoxy(100, 23);
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
	bool IsClearSokoban = false;
	bool IsClearFollowUp = false;
	

	while (GameStart) {
		GameInit();

		switch (select_opt) {

		case 1:	//start
			TextManager();	//텍스트창
			while (FollowUP_Game())
				if (Sokoban_Game())
					break;
			break;
		case 2:	//credit
			DrawCredit();
			break;

		case 3:	//exit
			GameStart = false;
		}
	}
	return 0;
}


