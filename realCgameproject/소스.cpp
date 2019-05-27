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

int select_opt;	//�����Ƽ� �׳� ����������.

ifstream in;

//�Լ��� gotoxy
//���ڰ��� x,y �� �����ϸ� �� ���� �� ������ Ŀ���� ������
void gotoxy(int x, int y) {
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
	gotoxy(0, 0); //ù |�κ� 6,3
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
		return true;
	else
		return false;

}

void textBox() {
	system("cls");
	gotoxy(0, 0);	//name : x 15 y 18, message x 11 y 20 
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
		gotoxy(0, 0);
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
		gotoxy(0, 0);
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
		gotoxy(0, 0);
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
	gotoxy(0, 0);
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
	gotoxy(0, 0);
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
	gotoxy(0, 0);
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
	gotoxy(0, 0);
	_getch();
	system("cls");
}

int DrawMenu() {
	DrawMain();
	int x = Menu_X;
	int y = Menu_Y;
	gotoxy(x - 2, y);
	printf("��  start ��");
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
				printf("��");
				gotoxy(x + 8, y);
				printf("��");
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
				printf("��");
				gotoxy(x + 8, y);
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

void gameInit() {
	RemoveCursor();
	system("cls");
	select_opt = DrawMenu();		//1 ���ӽ��� 2 �������� 3����
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
				printf("�����Դϴ�!!!!!!!!!!!!!!");
			else
				printf("Ʋ�Ƚ��ϴ� �̤̤̤̤̤̤̤̤�");
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


