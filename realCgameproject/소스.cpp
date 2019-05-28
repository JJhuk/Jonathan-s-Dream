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
#define SUBMIT 4 //���� ����
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

ifstream in;	//���� ���

//�Լ��� Gotoxy
//���ڰ��� x,y �� �����ϸ� �� ���� �� ������ Ŀ���� ������
void Gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
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
		printf("�����Դϴ�!!!!!!!!!!!!!!");
		_getch();
		return true;
	}
		
	else {
		printf("Ʋ�Ƚ��ϴ�!!!!!!!!!!!!!!");
		_getch();
		return false;
	}
}

/*r�̳� R�� ������ ������� �� �ִ� �Լ�*/
void Restart() {
	RestartValue = 1; //RestartValue�� 1�̸� ����� 
}


/* �÷��̾��� Ű�� �޴� �Լ� WASD�� ���� */
void PlayerControl() {
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
	printf("PLAYER : ��");
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
			PlayerControl(); //�÷��̾�, ������ ������ ����
			if (RestartValue == 1) {
				RestartValue = 0;
				break;
			}

			if (StageClear() == 1) { //���������� ���ٸ� ���α׷� ����
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
	printf("|      ======== �̸�   ===================================================================================            |\n");
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

void DrawStartExemple() {	//���Լ��� ���߿� ������Ʈ �Ҷ��� �Ⱦ����� �׳� ������Ÿ�Կ�
	system("cls");
		printf("=======================================================================================================================\n");
		printf("|                                                                                                              UI����1|\n");
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
		printf("|      ======== ������ ===================================================================================            |\n");
		printf("|      |                                                                                                 |            |\n");
		printf("|      |                                                                                                 |            |\n");
		printf("|      |     ���� ���� �ϴÿ��� ������ �� �� �ְ� ������ �� �� ������ �˰� �;��. �� ���̿���.          |            |\n");
		printf("|      |     �ٸ� �̵�ó�� �Ǵ� �Ϳ� ���ؼ��� �������� ������.                                           |            |\n");
		printf("|      |     �׺��� �ູ�� �������� �Ѱ踦 Ž���ϴ� ���� �Ϳ�.                                           |            |\n");
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
		printf("|                                                                                                              UI����2|\n");
		printf("|                       �������������                                                                      |\n");
		printf("|                       �������������                                                                      |\n");
		printf("|                       ���                ���                                                                      |\n");
		printf("|                       ���                ���                                                                      |\n");
		printf("|             ��������   ��           ��������                                                            |\n");
		printf("|             ��������            ��  ��������                                                            |\n");
		printf("|             ���                                  ����              �����������������              |\n");
		printf("|       ������          ��          ��          ����              �����������������              |\n");
		printf("|       ������                                  ����              ����                      ���              |\n");
		printf("|       ����            ���     ������       ��������������              ��  ��  ���              |\n");
		printf("| �������            ���     ������       ��������������                      ���              |\n");
		printf("| �������            ���     ������                                               ��  ��  ���              |\n");
		printf("| ���                                                                                              ���              |\n");
		printf("| ���  ��                 ��                           �������������              ��  ��  ���              |\n");
		printf("| ���                        ���������          ������������                      ���              |\n");
		printf("| �������������    ���������          ���              ����������������              |\n");
		printf("| �������������                              ���              ����������������              |\n");
		printf("|                     ���                              ���                                                          |\n");
		printf("|                     ��������������������                                                          |\n");
		printf("|                     ��������������������                            �� : �÷��̾�                  |\n");
		printf("|                                                                                      �� : ��                        |\n");
		printf("|                                                                                      �� : ����                      |\n");
		printf("|                                                                                      �� : �о���� ��               |\n");
		printf("|                                                                                                                     |\n");
		printf("|                                                                                      - R�� ���� ��õ� �ϱ�         |\n");
		printf("|                                                                                                                     |\n");
		printf("=======================================================================================================================\n");
		Gotoxy(0, 0);
		_getch();
		system("cls");
		printf("=======================================================================================================================\n");
		printf("|������! ������!                                                                                               UI����3|\n");
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
		printf("|                       ��                                                                                            |\n");
		printf("|                      ^.^                                                                                            |\n");
		printf("|                                                                    ��                                               |\n");
		printf("|                                                                   ^.^                               ��              |\n");
		printf("|                                                                                                    ^,^              |\n");
		printf("|              ��                                                                                                     |\n");
		printf("|             ^.^                                                                                                     |\n");
		printf("|                           ��                                 �С��                         ��                       |\n");
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

void GameInit() {
	RemoveCursor();
	system("cls");
	select_opt = DrawMenu();		//1 ���ӽ��� 2 �������� 3����
}

void TextManager() {
	string s;
	
	POINT p;
	in.open("C:\\Users\\LeeJuHyuk\\source\\repos\\SmugCgame\\realCgameproject\\text.txt");	//�� é�͸��� ������ �ٸ��� �Է��ؾ���.
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
					//���⿡ ���ǼҸ� �߰��ϸ� �ɵ�
					printf("%c", sub_s[i]);
					if (sub_s[i] == '.' && sub_s[i + 1] == '!') {	//�̶� 2��°�ٺ��� ��ĭ ���� �ؽ�Ʈ�� ��µǴ� ���װ� ����.
						p.y++;
						i++;
						Gotoxy(p.x, p.y);
					}
				}
			}
			if (!isName) {
				Gotoxy(100, 23);
				printf("��");
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
			TextManager();	//�ؽ�Ʈâ
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


