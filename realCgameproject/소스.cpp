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
#define SUBMIT 4 //���� ����
#define Menu_X 40
#define Menu_Y 24

#define IMGSIZE_W 7
#define IMGSIZE_H 4

#define WIDTH 20 //����ũ��(��������)
#define HEIGHT 10//����(��������)

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

wchar_t info[6] = { L"�ڡܡݡ��" };

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

int select_opt;	//�����Ƽ� �׳� ����������.

ifstream in[6];	//���� ���

int chepter = 0;

// ���� ������ ����
FMOD::System *g_System;
FMOD::Sound *g_Sound[5];	//0 ���κ�� 1 Ű���� 2 �����ϱ���� 3 ���ڹ� 4 ���ϱ����
FMOD::Channel *g_Channel;
FMOD::Channel *embi_Channel;

bool IsPlaying_Key = false;
bool IsPlaying_Main = false;
bool IsPlaying = false;

//�Լ��� Gotoxy
//���ڰ��� x,y �� �����ϸ� �� ���� �� ������ Ŀ���� ������
void Gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void FMod_Init()
{
	// �����, ȿ���� �ʱ�ȭ
	FMOD::System_Create(&g_System);
	g_System->init(32, FMOD_INIT_NORMAL, nullptr);
	g_System->createSound("main.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[0]);  //FMOD_LOOP_NORMAL�� �뷡�� �ݺ������� ���
	g_System->createSound("keysound.mp3", FMOD_LOOP_NORMAL , nullptr, &g_Sound[1]); //FMOD_DEFAULT�� �뷡�� �ѹ��� ���
	g_System->createSound("FollowUP.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[2]);
	g_System->createSound("sokoban.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[3]);
	g_System->createSound("Tree.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[4]);

	// ����� ���
	g_System->playSound(g_Sound[0], nullptr, false, &g_Channel);
}

void FMod_Release()
{
	for (int i = 0; i < 2; i++) g_Sound[i]->release();
	g_System->close();
	g_System->release();
}

// �Է� �̺�Ʈ ���
// �Լ��� : DrawTemplate
// ��� : ������ Ʋ�� ����ϴ��Լ�
void DrawFollowUPTemplate() {
	system("cls");
	Gotoxy(0, 0); //ù |�κ� 6,3
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

//Ŀ�� �����ִ� �Լ�
//CONSOLE_CURSOR_INFO �ܼ��� Ŀ�� ������ ��� ���� ����ü
//GetConsoleCursorInfo �ܼ� ���â ���� ��ȯ
void RemoveCursor(void) {
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0; //bVisible ��� ����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);	//���氪 ����
}

//�Լ��� KeyControl
//��� : Ű�� ���� ���� return ��
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
		else if (temp == 13)	//13�� ������ �ƽ�Ű�ڵ�
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
	for (int z = 0; z < 4; z++) {// ���� ����
		answer[z] = rand() % 4; //0~3���� �������� == up down left right

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
	for (int z1 = 0; z1 < 4; z1++) {	//���� �Է�
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
		printf("�����Դϴ�!!!!!!!!!!!!!!");
		Sleep(1);
		_getch();
		return true;
	}
		
	else {
		gotoxy(20, 20);
		printf("Ʋ�Ƚ��ϴ�!!!!!!!!!!!!!!");
		Sleep(1);
		_getch();
		return false;
	}
}

/*r�̳� R�� ������ ������� �� �ִ� �Լ�*/
void Restart() {
	RestartValue = 1; //RestartValue�� 1�̸� ����� 
}

/* �÷��̾��� Ű�� �޴� �Լ� WASD�� ���� */
void Tree_PlayerControl() {
	int dx = 0, dy = 0; // �÷��̾ �����̸� ���ϴ� ��ǥ�� ��ȭ��
	char temp = _getch(); //  _getch()�Լ��� ���� �ϳ� �Է��� ���
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
	else if (temp == 'r' || temp == 'R') { //��õ�
		Restart();
	}

	if (stage[currentY + dy][currentX + dx] == '[') { //���� ������ �ƹ��͵� ����
		return;
	}
	if (stage[currentY + dy][currentX + dx] == '0') { //������ ������ �տ��� ����0 �ڿ��� �빮�� O
		if (stage[currentY + dy * 2][currentX + dx * 2] == ' ') { // ������ �δ�  ok
			stage[currentY + dy][currentX + dx] = ' ';
			stage[currentY + dy][currentX + dx + 1] = ' ';
			stage[currentY + dy * 2][currentX + dx * 2] = '0';
			stage[currentY + dy * 2][currentX + dx * 2 + 1] = 'O';
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == '0') { //������ �ΰ� ������ �и��� ���� ok
			return;
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == 'x') { //�������� �����ϸ� X�� �� �ٲ�
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
		else if (stage[currentY + dy * 2][currentX + dx * 2] == '[') { //���̸� �ƹ��͵� ���� ok
			return;
		}
	}


	currentX += dx;
	currentY += dy;
}

/*���������� �׸���, �÷��̾� ���*/
void DrawStage() {
	//wchar_t info[6] = { L"�ڡܡݡ��" };
	setlocale(LC_ALL, "");
	for (int stageY = 0; stageY < 14; stageY++) {
		for (int stageX = 0; stageX < 60; stageX++) {

			Gotoxy(stageX, stageY);
			_putch(stage[stageY][stageX]);

		}
	}
	Gotoxy(currentX, currentY); //�÷��̾��� ���� ��ǥ�� ���� �÷��̾ ��Ÿ��
	putwchar(info[0]);
}

/*���������� Ŭ���� �ߴ��� Ȯ���ϴ� �Լ�*/
int StageClear() {
	int cx = 0, cy = 0;
	int count = 0;
	for (cy = 0; cy < 12; cy++) {
		for (cx = 0; cx < 57; cx++) {
			if (stage[cy][cx] == 'x' || stage[cy][cx] == '0') //.�� �ְų� o�� ������ count++
				count++;
		}
	}
	if (count == 0) {
		return 1;
	}
	else if (count != 0) {
		return 2;
	}
}//�� Ŭ�����ߴ�!!!!!!!!!!!!!!!

void printInfo() {
	Gotoxy(68, 2);
	printf("Tree_Player : ��");
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
	printf("- R�� ���� �ٽ� �ϱ�");
}

bool Sokoban_Game() {
	setlocale(LC_ALL, "");
	int x = 0, y = 0;
	while (1) {
		memcpy(stage, StageData, sizeof(stage)); //memcpy�� �޸𸮸� ����
		for (y = 0; y < 14; y++) { //�÷��̾ ã�Ƽ� ��ǥ�� �Է¹ް�, ���� �ִ� �ڸ��� ��������
			for (x = 0; x < 60; x++) {
				if (stage[y][x] == '@' && stage[y][x + 1] == '+') {
					currentX = x; //�÷��̾� ���� ��ǥ ����
					currentY = y;
					stage[y][x] = ' ';
					stage[y][x + 1] = ' ';//�̵������Ƿ� ���� �ִ� �ڸ��� ��������
				}
			}
		}
		system("cls");
		while (1) {
			DrawStage(); // ���������� �÷��̾� ���
			printInfo();
			Tree_PlayerControl(); //�÷��̾�, ������ ������ ����
			if (RestartValue == 1) {
				RestartValue = 0;
				break;
			}

			if (StageClear() == 1) { //���������� ���ٸ� ���α׷� ����
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


typedef struct  // �Լ������� ��Ī�� �����ϰ� ����ü�� ����
{
	int x;
	int y;

	int act;
}Tree;

typedef struct
{
	int x;
}Tree_Player;

Tree tree[WIDTH]; //����ũ�� ������ �����������ߵ�

Tree_Player Player; // �÷��̾��� ��ġ�� ��Ÿ��

int isKeyDown(int key) //Ű �Է� ����Ȯ��
{
	return ((GetAsyncKeyState(key) & 0x8000) != 0); // �̰͵� ��Ʈ������ ���̶�µ� �� �𸣰���
}

void Tree_init()
{
	int i;

	for (i = 0; i < WIDTH; i++)
		tree[i].act = FALSE;

	Player.x = WIDTH / 2;
}

void CreateTree()//������ �����ϴ� ��
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

void MoveTree()//������ �����̴� ��
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

int Tree_PlayerContainsTree()//�÷��̾�� ��������������
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if ((tree[i].act) && (tree[i].y == 0) && (tree[i].x == Player.x))//�÷�� ������ �Ͱ� ������ ������ ��
		{
			system("cls");
			Sleep(1000);
			printf("�׾����ϴ٤̤̤� �ٽ��ϼ���\n");
			return TRUE;
		}
	}

	return FALSE;
}

void MoveTree_Player() //�÷��̾��� �����̴� ��
{
	if (isKeyDown(0x41)) //������ ��Ÿ���� �ƽ�Ű�ڵ尪
		Player.x -= 1; //������ ��� x��ǥ-1
	if (isKeyDown(0x44))// �������� ��Ÿ���� �ƽ�Ű �ڵ尪 ��ü
		Player.x += 1; // �������� ��� x��ǥ +1

	if (Player.x < 0)
		Player.x = 0;
	if (Player.x > WIDTH - 1)
		Player.x = WIDTH - 1;
}

void Tree_PrintMap() // ���� �����
{
	system("cls"); //ó���� �ʱ�ȭ �����ִ� ��

	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (tree[i].act)
		{
			Gotoxy(tree[i].x, HEIGHT - tree[i].y);//goto�Լ� x,y��ǥ������ �����ϸ� ����
			printf("��");
		}
	}

	Gotoxy(Player.x, HEIGHT);
	printf("��");

	Gotoxy(0, HEIGHT + 1);
	for (i = 0; i < WIDTH; i++)
		printf("��");
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
		srand((int)malloc(NULL)); //�ߺ����� ���� ����, malloc�Լ��µ����޸��Ҵ�(�����޸𸮸� �� �𸣰ڴ�;)

		CreateTree();
		MoveTree();
		DeleteTree();//���� �Լ����� �ҷ���

		MoveTree_Player();

		Tree_PrintMap();

		Sleep(100);// sleep�Լ��� ������ �ð��� ����ǰų� �ñ׳��� �����ϸ� ��⿡�� Ǯ��
		end = time(NULL);
		pst = difftime(end, start);
		if (pst > 10)
		{
			system("cls");
			Sleep(1000);
			printf("Ŭ����!");
			return true;
		}
	} while (!(Tree_PlayerContainsTree()));//�÷��̾ ������ �Ⱥε����� ���� �۵��ؾ��ϹǷ�
	return false;
}

void TextBox(int select) {
	switch (select) {
	case 0:
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 
		printf("=======================================================================================================================\n");
		printf("|                                                                                                                     |\n");
		printf("|   ��                                  ��                                                             ��             |\n");
		printf("|              ��                                              ��                        ��                           |\n");
		printf("|                        ��                                                                                           |\n");
		printf("|                                                                                                           ��        |\n");
		printf("|      ��                                                  ��              ��                                         |\n");
		printf("|                                        ��                                                                           |\n");
		printf("|                                                                                                   ��                |\n");
		printf("|                ��                                                                                                   |\n");
		printf("|                                ��                     ��                                                            |\n");
		printf("|                                                                                   ��                                |\n");
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
	case 1:	//GUI1 �θ�� ��ȭ
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
	case 2:	//GUI2 ��ٴ�
		system("cls");
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 //GUI1: ��ٴ�
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
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : ��ٴٿ� ���� GUI3
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
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : ��ٴٿ� ���� GUI3
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
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : ���忡�� ȥ���� ������
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
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 //ȭ�� ������
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
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : ��ٴٿ� ���� GUI3
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
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : GUI5: ȥ�ڻ�� ������ �������� ���� ����
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
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : GUI5: ȥ�ڻ�� ������ �������� ���� ����
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
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 : �Ϲݰ��ű�
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
		Gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 //GUI9: ���� �Ǿ� �������� ������
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
		printf("|   ��                                  ��                                                             ��             |\n");
		printf("|              ��                                              ��                        ��                           |\n");
		printf("|                        ��                                                                                           |\n");
		printf("|                                                                                                           ��        |\n");
		printf("|      ��                                                  ��              ��                                         |\n");
		printf("|                                        ��                                                                           |\n");
		printf("|                                                                                                   ��                |\n");
		printf("|                ��                                                                                                   |\n");
		printf("|                                ��                     ��                                                            |\n");
		printf("|                                                                                   ��                                |\n");
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
	printf("|     ��                                            ��                                                          ��    |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                             ��                                      |\n");
	printf("|                 ��                                                                                                  |\n");
	printf("|                                                                                                ��                   |\n");
	printf("|                                                 ��                                                                  |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                                                                                     |\n");
	printf("|     ��                                                                                                              |\n");
	printf("|                                                                                                                     |\n");
	printf("|                             ��                                              Dreams of Jonathan                      |\n");
	printf("|                                                                                                                     |\n");
	printf("|                                                    ��                                                               |\n");
	printf("|                                                                                                                     |\n");
	printf("|                        ��                                                       ��                                  |\n");
	printf("|                                                                                                      ��             |\n");
	printf("|       ������ ��             ������ ��           ������ ��           ������ ��          ������ ��                    |\n");
	printf("|     ��     ^     ��       ��      ^   ��       ��      ^  ��     ��     ^    ��       ��     ^   ��                 |\n");
	printf("|   ��      |  ��_ ��  ��          |  ��_��   ��      | ��_ ��      ��     |  ��_ ��   ��    |  ��_ ��                |\n");
	printf("| ��          �� ___��          �� ____��          �� ___��         �� ____��       �� _________  |                   |\n");
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
	printf("|                              ��          ��      ��                     ��       ��      ��         ���             |\n");
	printf("|         ��������       ��      ������  ��           ����    ��      �� ��  ���      ������          |\n");
	printf("|                     ��       ��         ���     ��          ��    ��   ��     ��   ��   ��        ��  ��            |\n");
	printf("|                    ��        ��        ��  ��    ��           ����    ��                           ��              |\n");
	printf("|                   ��         ��         ���     ��                     ��        �����           ��              |\n");
	printf("|                  ��          ��          ��      ��                                     ��       �������        |\n");
	printf("|                 ��           ��        �����  ��                                                                  |\n");
	printf("|                              ��                                                                                      |\n");
	printf("|                              ��          ������                          ��  ��  ��  ��                          |\n");
	printf("|                              ��                  ��                        ��  ��  ��  ���                          |\n");
	printf("|                                                                          ��                ���                      |\n");
	printf("|                                                                        ��   ��     ��          ���                  |\n");
	printf("|                                                                  �����                      �����              |\n");
	printf("|                                ��                                  ����  ����              ����                |\n");
	printf("|                        ��      ������������                ���    ���               ��                    |\n");
	printf("|                        ��        ������ ��       ���               ��                    ��                     |\n");
	printf("|                        ������������       �����               ��                ��                       |\n");
	printf("|                        ��        ������ ��       ���                   ���������                         |\n");
	printf("|                        ��      ������������                           ��       ��                          |\n");
	printf("|                                ��                                             �� ��     �� ��                        |\n");
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
	printf("|                                                    ��            ��       ��        ��    ��     ���       ��       |\n");
	printf("|            ��������                          ��           �� ��   ���     ����� ��    ��  ��  ����       |\n");
	printf("|              ��      ��               ������   ��          ��   ��    ��      ��  ��  ��    ��  ��      ��       |\n");
	printf("|              ��      ��               ��      ��   ��                 ���         ���   ��     ���   ����       |\n");
	printf("|            ��������             ��      ��   ��                ��   ��    �������      ��        ��       |\n");
	printf("|                                       ��      ��   ��                 ���                ��      �������       |\n");
	printf("|         ������������        ������   ��                                                                |\n");
	printf("|                                                    ��                               �����                         |\n");
	printf("|            ��������                   ����          ���                  ��  ��     ��                      |\n");
	printf("|                        ��                  ��    ��         ���           �������      ��                      |\n");
	printf("|            ��������                  ��    ��         ���                  ��          ��                     |\n");
	printf("|            ��                               ����          ����������  ��       �������                |\n");
	printf("|            ��������                                   ���  ��          ��         ��         ����           |\n");
	printf("|                                                              ��     ��          ��       ��            ��            |\n");
	printf("|                                                                       ��        ��         �������              |\n");
	printf("|                                                                         ������                   ��              |\n");
	printf("|                       ��               ���                                     ���                ����           |\n");
	printf("|                      �� ��           ��                                       ��   ����������   ��           |\n");
	printf("|                     ����           ��                                       ���                    ��             |\n");
	printf("|                    ��     ��         ��                                         ��                   ��              |\n");
	printf("|                                        ���                                   ��  ����������� ��            |\n");
	printf("|                                                                                   ��       ��         ��             |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
	Gotoxy(0, 0);
	_getch();
	system("cls");
	printf("========================================================================================================================\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                    ��            ��      ��    ������        ��         ��       |\n");
	printf("|            ��������                          ��          ��  ��    ��        ��         ���������       |\n");
	printf("|              ��      ��               ������   ��          ��  ��    ��       �� ��         ��  ��      ��       |\n");
	printf("|              ��      ��               ��      ��   ��            ��      ��       ��  ��         ���   ����       |\n");
	printf("|            ��������             ��      ��   ��                    ��    �������                 ��       |\n");
	printf("|                                       ��      ��   ��                    ��         ��              ������       |\n");
	printf("|         ������������        ������   ��                               ��                      ��       |\n");
	printf("|                                                    ��                                                                |\n");
	printf("|            ��������                   ����                              ������                           |\n");
	printf("|                        ��                  ��    ��                        �����    �����                      |\n");
	printf("|            ��������                  ��    ��                          ���������                        |\n");
	printf("|            ��                               ����                 ��      ��  ���    ���  ��      ��              |\n");
	printf("|            ��������                                          ���  ���                ���  ���              |\n");
	printf("|                                                                     �����       ���       �����               |\n");
	printf("|                                                                       ����        ��        ����                 |\n");
	printf("|                                          ��                                ��                ��                      |\n");
	printf("|                           ��           ��  ��                                ��  �����  ��                        |\n");
	printf("|                         ��  ��           ��                                    ��        ��                          |\n");
	printf("|                         ��  ��                                               ����������                      |\n");
	printf("|                         ��  ��                                             ��                  ��                    |\n");
	printf("|                           ��                 ��                          ��                     ��                   |\n");
	printf("|                                            ��  ��                        ��������������                  |\n");
	printf("|                                              ��                          ��         ����       ��                  |\n");
	printf("|                                                                          ��       ��     ��      ��                  |\n");
	printf("|                                                                          ��       ��     ��      ��                  |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
	Gotoxy(0, 0);
	_getch();
	system("cls");
	printf("========================================================================================================================\n");
	printf("|                                                                                                                      |\n");
	printf("|                      ��                ��                  ��    ��  ��  ��       ������        ����           |\n");
	printf("|         ������   ��  �������  ��        ����    ��    ����  ���         ��           ��    ��          |\n");
	printf("|         ��           ��      ��        ��      ��     ��   ��    ��  ��  ��          �� ��          ����           |\n");
	printf("|         ��           ��     �� ��      ��      ��     ��   ��    ����  ��         ��   ��      �������        |\n");
	printf("|         ��           ��    ��   ��     ����  ��     ��   ��                                       ��  ��           |\n");
	printf("|         ��           ��   ��     ��    ��        ����    ��     �����        ������       ��                |\n");
	printf("|         ��           ��                ��          ��      ��           ��            ��           �����          |\n");
	printf("|         ������   ��                ��          ��                                                                |\n");
	printf("|                      ��                ��          ������                                                        |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                 ������                          �����         |\n");
	printf("|                                   �����������        ��          ���                    ��        ��       |\n");
	printf("|                                   ��     ���       ��       �� ����       ��                  ��   ��      ��     |\n");
	printf("|                                   ��    ����      ��             ��        ��          �����             ��     |\n");
	printf("|                                   ��   �����     ��               ��      ���          ����              ��    |\n");
	printf("|                                   ��     ���       ��                 ����     ��              �� �� �� ��        |\n");
	printf("|                                   ��                ��                    ��       ��         ���                   |\n");
	printf("|                                   �����������                      ��      ��       ��                      |\n");
	printf("|                                            ��                                 ��    ��      ��                       |\n");
	printf("|                                            ��                                   ���  ��    ��                       |\n");
	printf("|                                            ��                                       ��  �� ��                        |\n");
	printf("|                                          ��  ��                                       ��  ��                         |\n");
	printf("|                                         ��     ��                                       �� ��                        |\n");
	printf("|                                                                                           ��                         |\n");
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
	printf("��  start ��");
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
				printf("��");
				Gotoxy(x + 8, y);
				printf("��");
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
				printf("��");
				Gotoxy(x + 8, y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y >= Menu_Y) {
				return y - Menu_Y + 1;	//1 2 3 ������ ������ ��
			}
		}
		}
	}
}

void Game_Init() {
	RemoveCursor();
	system("cls");
	select_opt = DrawMenu();		//1 ���ӽ��� 2 �������� 3����
}

void Game_Manager(int chepter) {
	switch (chepter) {
	case 2:
		g_Channel->setMode(FMOD_LOOP_OFF);
		g_Channel->stop();	//��������� ����,
		g_System->playSound(g_Sound[4], nullptr, false, &embi_Channel);	//���ϱ� ����� �Ҵ�

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
		g_Channel->stop();	//��������� ����,
		g_System->playSound(g_Sound[3], nullptr, false, &embi_Channel);	//���ڹ� ���� ����� �Ҵ�

		Sokoban_Game();

		embi_Channel->setMode(FMOD_LOOP_OFF);
		embi_Channel->stop();	
		g_Channel->setMode(FMOD_LOOP_NORMAL);
		g_System->playSound(g_Sound[0], nullptr, false, &g_Channel);
		break;
	case 4:
		g_Channel->setMode(FMOD_LOOP_OFF);
		g_Channel->stop();	//��������� ����,
		g_System->playSound(g_Sound[2], nullptr, false, &embi_Channel);	//�����ϱ� ���� ����� �Ѱ�

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
	int UI_change = 0;	//UI�������ִ� ģ��

	POINT p;
	in[0].open("Intro.txt");	//�� é�͸��� ������ �ٸ��� �Է��ؾ���.
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
						//���⿡ ���ǼҸ� �߰��ϸ� �ɵ�
						if (sub_s[i] == '#') {	//�̶� 2��°�ٺ��� ��ĭ ���� �ؽ�Ʈ�� ��µǴ� ���װ� ����.
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
					printf("��");
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
			TextManager();	//�ؽ�Ʈâ

			
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


