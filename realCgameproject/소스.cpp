#pragma once
#pragma comment(lib,"C:\\Program Files (x86)\\FMOD SoundSystem\\FMOD Studio API Windows\\api\\lowlevel\\lib\\fmod_vc.lib")

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <stddef.h>
#include <locale.h>
#include <iostream>
#include <fmod.hpp>
#include <fmod.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>

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

#define WIDTH 20 //가로크기(조절가능)
#define HEIGHT 10//높이(조절가능)

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

ifstream in[6];	//파일 출력

int chepter = 0;

// 전역 변수로 선언
FMOD::System *g_System;
FMOD::Sound *g_Sound[5];	//0 메인브금 1 키사운드 2 따라하기게임 3 소코반 4 피하기게임
FMOD::Channel *g_Channel;
FMOD::Channel *embi_Channel;

bool IsPlaying_Key = false;
bool IsPlaying_Main = false;
bool IsPlaying = false;

//함수명 Gotoxy
//인자값인 x,y 에 대입하면 그 대입 한 곳으로 커서가 움직임
void Gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void FMod_Init()
{
	// 배경음, 효과음 초기화
	FMOD::System_Create(&g_System);
	g_System->init(32, FMOD_INIT_NORMAL, nullptr);
	g_System->createSound("main.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[0]);  //FMOD_LOOP_NORMAL은 노래를 반복적으로 재생
	g_System->createSound("keysound.mp3", FMOD_LOOP_NORMAL , nullptr, &g_Sound[1]); //FMOD_DEFAULT은 노래를 한번만 재생
	g_System->createSound("FollowUP.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[2]);
	g_System->createSound("sokoban.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[3]);
	g_System->createSound("Tree.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[4]);

	// 배경음 출력
	g_System->playSound(g_Sound[0], nullptr, false, &g_Channel);
}

void FMod_Release()
{
	for (int i = 0; i < 2; i++) g_Sound[i]->release();
	g_System->close();
	g_System->release();
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
		gotoxy(20, 20);
		printf("정답입니다!!!!!!!!!!!!!!");
		Sleep(1);
		_getch();
		return true;
	}
		
	else {
		gotoxy(20, 20);
		printf("틀렸습니다!!!!!!!!!!!!!!");
		Sleep(1);
		_getch();
		return false;
	}
}

/*r이나 R을 누르면 재시작할 수 있는 함수*/
void Restart() {
	RestartValue = 1; //RestartValue가 1이면 재시작 
}

/* 플레이어의 키를 받는 함수 WASD로 조작 */
void Tree_PlayerControl() {
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
	printf("Tree_Player : ★");
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
			Tree_PlayerControl(); //플레이어, 바위의 움직임 구현
			if (RestartValue == 1) {
				RestartValue = 0;
				break;
			}

			if (StageClear() == 1) { //스테이지를 깬다면 프로그램 종료
				system("cls");
				DrawStage();
				printInfo();
				Sleep(10);
				_getch();
				system("cls");
				return true;
			}
		}
	}
}

#define LEFT 2
#define RIGHT 3


typedef struct  // 함수포인터 별칭을 정의하고 구조체로 묶음
{
	int x;
	int y;

	int act;
}Tree;

typedef struct
{
	int x;
}Tree_Player;

Tree tree[WIDTH]; //가로크기 내에서 나무떨어져야됨

Tree_Player Player; // 플레이어의 위치를 나타냄

int isKeyDown(int key) //키 입력 여부확인
{
	return ((GetAsyncKeyState(key) & 0x8000) != 0); // 이것도 비트연산자 값이라는데 잘 모르겠음
}

void Tree_init()
{
	int i;

	for (i = 0; i < WIDTH; i++)
		tree[i].act = FALSE;

	Player.x = WIDTH / 2;
}

void CreateTree()//나무를 생성하는 것
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (!tree[i].act)
		{
			tree[i].x = rand() % WIDTH;
			tree[i].y = HEIGHT - 1;

			tree[i].act = TRUE;

			return;
		}
	}
}

void MoveTree()//나무를 움직이는 것
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (tree[i].act)
		{
			tree[i].y--;
		}
	}
}

void DeleteTree()
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (tree[i].act && tree[i].y < 0)
		{
			tree[i].act = FALSE;
		}
	}
}

int Tree_PlayerContainsTree()//플레이어랑 나무랑만났을때
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if ((tree[i].act) && (tree[i].y == 0) && (tree[i].x == Player.x))//플레어가 움직인 것과 나무가 만났을 때
		{
			system("cls");
			Sleep(1000);
			printf("죽었습니다ㅜㅜㅜ 다시하세요\n");
			return TRUE;
		}
	}

	return FALSE;
}

void MoveTree_Player() //플레이어의 움직이는 것
{
	if (isKeyDown(0x41)) //왼쪽을 나타내는 아스키코드값
		Player.x -= 1; //왼쪽일 경우 x좌표-1
	if (isKeyDown(0x44))// 오른쪽을 나타내는 아스키 코드값 대체
		Player.x += 1; // 오른쪽일 경우 x좌표 +1

	if (Player.x < 0)
		Player.x = 0;
	if (Player.x > WIDTH - 1)
		Player.x = WIDTH - 1;
}

void Tree_PrintMap() // 맵을 출력함
{
	system("cls"); //처음에 초기화 시켜주는 것

	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (tree[i].act)
		{
			Gotoxy(tree[i].x, HEIGHT - tree[i].y);//goto함수 x,y좌표값으로 생각하면 편함
			printf("♠");
		}
	}

	Gotoxy(Player.x, HEIGHT);
	printf("√");

	Gotoxy(0, HEIGHT + 1);
	for (i = 0; i < WIDTH; i++)
		printf("▤");
}

bool TreeAvoid_Game()
{
	long res;
	char key;
	time_t start, end;
	double pst;
	start = time(NULL);
	Tree_init();
	do
	{
		srand((int)malloc(NULL)); //중복없는 난수 생성, malloc함수는동적메모리할당(동적메모리를 잘 모르겠다;)

		CreateTree();
		MoveTree();
		DeleteTree();//위의 함수들을 불러옴

		MoveTree_Player();

		Tree_PrintMap();

		Sleep(100);// sleep함수로 지정된 시간이 경과되거나 시그널을 수신하면 대기에서 풀림
		end = time(NULL);
		pst = difftime(end, start);
		if (pst > 10)
		{
			system("cls");
			Sleep(1000);
			printf("클리어!");
			return true;
		}
	} while (!(Tree_PlayerContainsTree()));//플레이어가 나무랑 안부딪히는 동안 작동해야하므로
	return false;
}

void TextBox(int select) {
	switch (select) {
	case 0:
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
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 1:	//GUI1 부모님 대화
		system("cls");
		Gotoxy(0, 0);
		printf("=======================================================================================================================\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                     ___________                                                     |\n");
		printf("|                                                   /             \\                                                   |\n");
		printf("|                                                  |  __________   |      ;                                           |\n");
		printf("|                  ;         8  8  8  8  8          \/   `   /  \\ /                                                    |\n");
		printf("|                          (   ________   )    ;    /   0  v  0   \\   ;                                               |\n");
		printf("|              ;            ( /        \\)         /              \\                                                    |\n");
		printf("|                     ;      /  V  v  V \\       //       VVV      \\\\         ;                                        |\n");
		printf("|                           /  ;        ;\\    / /         V        \\  \\                                               |\n");
		printf("|                         //              \\\\/  /                    \\  \\                                              |\n");
		printf("|                       / /                \\ \\/                      \\  |   __________   ;                            |\n");
		printf("|                     /  /                  \\/                        \\ /  / 0        \\        ;                      |\n");
		printf("|                     \\ /                    \\                           </    ;       \\                              |\n");
		printf("|                                                                          /              \\      ;                    |\n");
		printf("|                                                                                                                     |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 2:	//GUI2 밤바다
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 //GUI1: 밤바다
		printf("=======================================================================================================================\n");
		printf("|            *                                                                                                        |\n");
		printf("|                                                                    +                                                |\n");
		printf("|                               +                *                              /------\\            *                 |\n");
		printf("|                                                                              (        )                             |\n");
		printf("|    +                                                                          \\______/                              |\n");
		printf("|                  *                                            *                                    *                |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                    *                                                      *                         |\n");
		printf("|            *                                            *                                                           |\n");
		printf("|                                                                                                      *              |\n");
		printf("|                                              ___--___                              *                                |\n");
		printf("|        ~~~~~~~~~~           ~~~~~~~~~       /        \\ __  ~~~                                 ~~~~~~               |\n");
		printf("|                 ~~~~~~~~~~                 /       0  \\ /               ~~~~~~~                                     |\n");
		printf("|                                           /       ;     \\    ~~                                                     |\n");
		printf("|                    ~~              __  __/__             \\ __        ~~              ~~~~~~                         |\n");
		printf("|                                      ------------------------              ~~                                       |\n");
		printf("|        ~~                            --    --    --   ---   --                                                      |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 3:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : 밤바다와 비행 GUI3
		printf("=======================================================================================================================\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                    /----------\\                     |\n");
		printf("|                                                                                  /              \\                   |\n");
		printf("|                                                                                 |             0 .|                  |\n");
		printf("|                        ------\\                                                  |            . o |                  |\n");
		printf("|                      /          \\                                                \\        .   ../                   |\n");
		printf("|                    /                ------                                        \\   . o  .. ./                    |\n");
		printf("|                     \\-------------/                                                 -----------                     |\n");
		printf("|                                                                                         /--------------             |\n");
		printf("|               -----------------------------------------------------             /--------                           |\n");
		printf("|     ---\\              ~~~                                 ~~~             //                                        |\n");
		printf("|           ----\\                  ---               ----                  |                                          |\n");
		printf("|                  ----\\        ~~~                                   /---                                            |\n");
		printf("|                        |                  ---            ~~          \\                                              |\n");
		printf("|                       /                 ________                       \\                                            |\n");
		printf("|                  ----/         -------                   -------          \\-------------------                      |\n");
		printf("|               /                                                                                                     |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 4:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : 밤바다와 비행 GUI3
		printf("=======================================================================================================================\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                    /----------\\                     |\n");
		printf("|                                                                                  /              \\                   |\n");
		printf("|                                                                                 |             0 .|                  |\n");
		printf("|                        ------\\                                                  |            . o |                  |\n");
		printf("|                      /          \\                                                \\        .   ../                   |\n");
		printf("|                    /                ------                                        \\   . o  .. ./                    |\n");
		printf("|                     \\-------------/                                                 -----------                     |\n");
		printf("|                                                                                         /--------------             |\n");
		printf("|               -----------------------------------------------------             /--------                           |\n");
		printf("|     ---\\              ~~~                                 ~~~             //                                        |\n");
		printf("|           ----\\                  ---               ----                  |                                          |\n");
		printf("|                  ----\\        ~~~                                   /---                                            |\n");
		printf("|                        |                  ---            ~~          \\                                              |\n");
		printf("|                       /                 ________                       \\                                            |\n");
		printf("|                  ----/         -------                   -------          \\-------------------                      |\n");
		printf("|               /                                                                                                     |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 5:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : 족장에게 혼나는 조나단
		printf("=======================================================================================================================\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                            /                 \\           \\                                          |\n");
		printf("|                       /                   /                   \\           \\                                         |\n");
		printf("|                      /              /    /                !    \\                                                    |\n");
		printf("|                                    /    /         _____         \\                                                   |\n");
		printf("|                              /    /    /        / -   - \\       \\                                                   |\n");
		printf("|                             /    /    /    !    | 0 o 0 |         \\    \\                                            |\n");
		printf("|                            /    /    /        /          \\        \\     \\      \\                                    |\n");
		printf("|                                /    /         \\         /    !     \\      \\     \\                                   |\n");
		printf("|                                    /            \\------/            \\       \\     \\                                 |\n");
		printf("|                                   /                |  |               \\                                             |\n");
		printf("|                  /               /                 m  m                \\               \\                            |\n");
		printf("|                 /               /                                       \\               \\                           |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                                                     |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 6:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 //화난 조나단
		printf("=======================================================================================================================\n");
		printf("|                                                                                                                     |\n");
		printf("|                                    /--\\    /--\\      /--\\     /--\\      /---\\                                       |\n");
		printf("|                                   /    \\ <|.    \\   |    |   |    |    /    .|>                                     |\n");
		printf("|                            /--\\   |    |   \\     \\ /      \\ /      \\  /     /  /--\\                                 |\n");
		printf("|                          /     \\ /      \\  /      /         \\       |       \\ /    \\                                |\n");
		printf("|                         |       |        |  >    |  >     <  |     /     <   |      |                               |\n");
		printf("|                          \\_____ \\_____    \\______ \\________ /_____/  _______/  ____/                                |\n");
		printf("|                            | |     | |      |  |      |  |   | |      | |      | |                                  |\n");
		printf("|                                                     __==__    +                                                     |\n");
		printf("|                                     +       \\    /     ``\\  \\      /                +                               |\n");
		printf("|                                          ---    / /      0   \\>    ---                                              |\n");
		printf("|                         #------------\\     /   / /           \\>    \\    /------------#                              |\n");
		printf("|              \\\\           #_          \\       / /             \\        /          _#        //                      |\n");
		printf("|                 \\\\          #_         \\     / /               \\      /         _#        //                        |\n");
		printf("|                               #_        \\   /                    \\   /       _#                                     |\n");
		printf("|                                  #_      \\_/                      \\_/      _#                                       |\n");
		printf("|                                                                                                                     |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 7:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : 밤바다와 비행 GUI3
		printf("=======================================================================================================================\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                    /----------\\                     |\n");
		printf("|                                                                                  /              \\                   |\n");
		printf("|                                                                                 |             0 .|                  |\n");
		printf("|                        ------\\                                                  |            . o |                  |\n");
		printf("|                      /          \\                                                \\        .   ../                   |\n");
		printf("|                    /                ------                                        \\   . o  .. ./                    |\n");
		printf("|                     \\-------------/                                                 -----------                     |\n");
		printf("|                                                                                         /--------------             |\n");
		printf("|               -----------------------------------------------------             /--------                           |\n");
		printf("|     ---\\              ~~~                                 ~~~             //                                        |\n");
		printf("|           ----\\                  ---               ----                  |                                          |\n");
		printf("|                  ----\\        ~~~                                   /---                                            |\n");
		printf("|                        |                  ---            ~~          \\                                              |\n");
		printf("|                       /                 ________                       \\                                            |\n");
		printf("|                  ----/         -------                   -------          \\-------------------                      |\n");
		printf("|               /                                                                                                     |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 8:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : GUI5: 혼자사는 조나단 누군가를 만나 각성
		printf("=======================================================================================================================\n");
		printf("|                                   ||                          ||                                                    |\n");
		printf("|                          \\       ||         /         \\      ||    /                                                |\n");
		printf("|                  +        \\      ||        /           \\     ||   /            +                                    |\n");
		printf("|                            \\              /             \\        /                                                  |\n");
		printf("|                    ----------               ------------            --------                       +                |\n");
		printf("|                              /           \\                        \\                                                 |\n");
		printf("|                             /     ||        \\    +      /     ||    \\                                               |\n");
		printf("|                +           /      ||         \\         /      ||     \\            +                                 |\n");
		printf("|                                   ||                  /       ||                                                    |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                               /-------\\                                                             |\n");
		printf("|           ---------------------------         |  .v.  |  -----------------------------------                        |\n");
		printf("|                                 ~~            \\      /       ~~                                                     |\n");
		printf("|                        ~~                    /        \\                    ~~                       ~~              |\n");
		printf("|                  ~~                          |          |                            ~~                             |\n");
		printf("|                              ~~              \\         /          ~~                                                |\n");
		printf("|                                              \\        /                                                             |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 9:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : GUI5: 혼자사는 조나단 누군가를 만나 각성
		printf("=======================================================================================================================\n");
		printf("|                                   ||                          ||                                                    |\n");
		printf("|                          \\       ||         /         \\      ||    /                                                |\n");
		printf("|                  +        \\      ||        /           \\     ||   /            +                                    |\n");
		printf("|                            \\              /             \\        /                                                  |\n");
		printf("|                    ----------               ------------            --------                       +                |\n");
		printf("|                              /           \\                        \\                                                 |\n");
		printf("|                             /     ||        \\    +      /     ||    \\                                               |\n");
		printf("|                +           /      ||         \\         /      ||     \\            +                                 |\n");
		printf("|                                   ||                  /       ||                                                    |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                               /-------\\                                                             |\n");
		printf("|           ---------------------------         |  .v.  |  -----------------------------------                        |\n");
		printf("|                                 ~~            \\      /       ~~                                                     |\n");
		printf("|                        ~~                    /        \\                    ~~                       ~~              |\n");
		printf("|                  ~~                          |          |                            ~~                             |\n");
		printf("|                              ~~              \\         /          ~~                                                |\n");
		printf("|                                              \\        /                                                             |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 10:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : 일반갈매기
		printf("=======================================================================================================================\n");
		printf("|                                               + . + . +                                                             |\n");
		printf("|                                                /-----\\                                                              |\n");
		printf("|                                               / 0 V 0 \\                                                             |\n");
		printf("|                              ----------\\     |       |     /----------                                              |\n");
		printf("|                                l             /         \\           /                                                |\n");
		printf("|                      *            l         |            |        /           *                                     |\n");
		printf("|                                       l    \\            /     /                                                     |\n");
		printf("|                                             \\          /                                                            |\n");
		printf("|                                               ----------                                                            |\n");
		printf("|                           ?                       m  m                                                              |\n");
		printf("|              _____                                                                      ?                           |\n");
		printf("|             /    .\>                                        ?                    _____                               |\n");
		printf("|          __|       |                      ?          _____                 ?   </.   \\                              |\n");
		printf("|           \\        _____     ?     _____          </ .   \\       _____         |      |                             |\n");
		printf("|             -----  /   . |>        /     \\   ?    |       |      /     \\       |      |                             |\n");
		printf("|                   /      |        |       |       |       |     |      |       |      |                             |\n");
		printf("|                  /        |      /         \\     /         \\   /        \\      /      |                             |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	case 11:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 //GUI9: 빛이 되어 떠나가는 조나단
		printf("=======================================================================================================================\n");
		printf("|                                        \\     .           .        /                                                 |\n");
		printf("|                             +           \\   /--------------\\   /                +                                   |\n");
		printf("|                                  .        /        .         \\      .                                               |\n");
		printf("|                +         -------------- /        .___.         \\  --------------           +                        |\n");
		printf("|                            .           |    ___ ( uVu ) ___     |         .                                         |\n");
		printf("|                                       |    /   \\(     )/   \\     |                                                  |\n");
		printf("|                ---------------        |  /   ^    | |    ^   \\     |     ---------------         +                  |\n");
		printf("|           +                           |           ^ ^            |                                                  |\n");
		printf("|                     .                  \\    .             .     /             .                                     |\n");
		printf("|                         ----------      \\                      /   ----------                                       |\n");
		printf("|             +                                 ---  ------                                     +                     |\n");
		printf("|                                  .         /    |    |    |   \\        .                                            |\n");
		printf("|                  +                        /     |    |    |    \\                  +     .                           |\n");
		printf("|                                          /      |    |    |     \\                                                   |\n");
		printf("|                           +        .    /       |         |      \\      +      .                                    |\n");
		printf("|                                        /        |    .    |       \\                                                 |\n");
		printf("|                                                                                                                     |\n");
		printf("|      ===================================================================================================            |\n");
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
		break;
	default:
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
		printf("|      ===================================================================================================            |\n");
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
		break;
	}
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

void Game_Init() {
	RemoveCursor();
	system("cls");
	select_opt = DrawMenu();		//1 게임시작 2 게임정보 3종료
}

void Game_Manager(int chepter) {
	switch (chepter) {
	case 2:
		g_Channel->setMode(FMOD_LOOP_OFF);
		g_Channel->stop();	//배경음악을 끄고,
		g_System->playSound(g_Sound[4], nullptr, false, &embi_Channel);	//피하기 브금을 켠다

		TreeAvoid_Game();

		embi_Channel->setMode(FMOD_LOOP_OFF);
		embi_Channel->stop();
		g_Channel->setMode(FMOD_LOOP_NORMAL);
		g_System->playSound(g_Sound[0], nullptr, false, &g_Channel);
		int c;
		while (c = getchar() != '\n' &&c != EOF);
		break;
	case 3:
		g_Channel->setMode(FMOD_LOOP_OFF);
		g_Channel->stop();	//배경음악을 끄고,
		g_System->playSound(g_Sound[3], nullptr, false, &embi_Channel);	//소코반 게임 브금을 켠다

		Sokoban_Game();

		embi_Channel->setMode(FMOD_LOOP_OFF);
		embi_Channel->stop();	
		g_Channel->setMode(FMOD_LOOP_NORMAL);
		g_System->playSound(g_Sound[0], nullptr, false, &g_Channel);
		break;
	case 4:
		g_Channel->setMode(FMOD_LOOP_OFF);
		g_Channel->stop();	//배경음악을 끄고,
		g_System->playSound(g_Sound[2], nullptr, false, &embi_Channel);	//따라하기 게임 브금을 켜고

		while (!FollowUP_Game());

		embi_Channel->setMode(FMOD_LOOP_OFF);
		embi_Channel->stop();	
		g_Channel->setMode(FMOD_LOOP_NORMAL);
		g_System->playSound(g_Sound[0], nullptr, false, &g_Channel);
		break;

	}
}

void TextManager() {
	string s;
	int UI_change = 0;	//UI변경해주는 친구

	POINT p;
	in[0].open("Intro.txt");	//각 챕터마다 파일을 다르게 입력해야함.
	in[1].open("1.txt");
	in[2].open("2.txt");
	in[3].open("3.txt");
	in[4].open("4.txt");
	in[5].open("5.txt");
	bool isName = TRUE;
	for (chepter = 0; chepter < 6; chepter++, UI_change++) {
		while (getline(in[chepter], s)) {
			istringstream ss(s);
			string sub_s;
			g_System->playSound(g_Sound[1], nullptr, false, &embi_Channel);
			embi_Channel->setMode(FMOD_LOOP_NORMAL);
			while (getline(ss, sub_s, '\t')) {
				p = { 11,20 };
				if (isName) {
					TextBox(UI_change);
					Gotoxy(16, 18);
					cout << sub_s;
					
				}
				else {
					Gotoxy(p.x, p.y);
					for (int i = 0; i < sub_s.length(); i++) {
						Sleep(1);
						//여기에 자판소리 추가하면 될듯
						if (sub_s[i] == '#') {	//이때 2번째줄부터 한칸 띄우고 텍스트가 출력되는 버그가 있음.
							p.y++;
							i++;
							Gotoxy(p.x, p.y);
						}
						if (sub_s[i] == '$') {
							i++;
							UI_change++;
						}
						printf("%c", sub_s[i]);
					}
				}
				if (!isName) {
					embi_Channel->setMode(FMOD_LOOP_OFF);
					Gotoxy(100, 23);
					printf("▼");
					Sleep(1);

					_getch();
				}
				isName = !isName;
				//g_System->update();
			}
			g_System->update();
		}
		Game_Manager(chepter);
	}
	
	embi_Channel->stop();
	for (int i = 0; i < 6; i++) {
		in[i].close();
	}
}

int main()
{
	bool GameStart = true;
	bool IsClearSokoban = false;
	bool IsClearFollowUp = false;

	int FMod_Key;
	FMOD::Channel *embi_Channel;
	FMod_Init();

	while (GameStart) {
		Game_Init();

		switch (select_opt) {

		case 1:	//start
			TextManager();	//텍스트창

			
			Sleep(1000);
			break;
		case 2:	//credit
			DrawCredit();
			break;

		case 3:	//exit
			GameStart = false;
		}
	}
	FMod_Release();
	return 0;
}


