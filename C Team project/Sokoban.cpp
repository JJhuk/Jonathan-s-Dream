#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <wchar.h>
#include <stddef.h>
#include <Windows.h>

/*==================================================================================*/
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define RETRY 4
 /*=============================���� ����===========================================*/
char stage[20][120] = { '\0', };
const char StageData[15][120] =
{
	{"###########################################################################"},
	{"###### @ ##                                                              ##"},
	{"#####   ##                                                               ##"},
	{"####   ####                                                              ##"},
	{"### o ###                                                                ##"},
	{"## . ###                                                                 ##"},
	{"##     #                                                                 ##"},
	{"##                                                                       ##"},
	{"##                                                                       ##"},
	{"##                                                                       ##"},
	{"##                                                                       ##"},
	{"##                                                                       ##"},
	{"##                                                                       ##"},
	{"##                                                                       ##"},
	{"###########################################################################"}
};
int currentX = 0, currentY = 0;
int RestartValue;
/*================================== �Լ� ===========================================*/

/*r�̳� R�� ������ ������� �� �ִ� �Լ�*/
void Restart() {
	RestartValue = 1; //RestartValue�� 1�̸� ����� 
}

/*Ŀ���� �ش� ��ǥ�� ����*/
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
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
		dx = -1, dy = 0;
		//return LEFT;
	}
	else if (temp == 'd' || temp == 'D') {
		dx = 1, dy = 0;
		//return RIGHT;
	}
	else if (temp == 'r' || temp == 'R') { //��õ�
		Restart();
	}
	
	if (stage[currentY+dy][currentX + dx] == '#') { //���� ������ �ƹ��͵� ����
		return;
	}
	if (stage[currentY + dy][currentX + dx] == 'o') { //������ ������
		if (stage[currentY + dy * 2][currentX + dx * 2] == ' ') { // ������ �δ�  /StageData�� stage��� �ٲ���
			stage[currentY + dy][currentX + dx] = ' ';
			stage[currentY + dy * 2][currentX + dx * 2] = 'o';
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == 'o') { //������ �ΰ� ������ �и��� ����
			return;
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == '.') { //�������� �����ϸ� .�� o�� �ٲ�
			stage[currentY + dy][currentX + dx] = ' ';
			stage[currentY + dy * 2][currentX + dx * 2] = '&';
		}
		else if (stage[currentY+dy*2][currentX+dx*2] == '#') { //���̸� �ƹ��͵� ����
			return;
		}
	}
	//&�� . o ��ȯ
	/*if (stage[currentY + dy][currentX + dy] == '&') { //���� �����̶��
		if (stage[currentY + dy * 2][currentX + dx * 2] == ' ') { // �� �κ��� ����
			stage[currentY + dy][currentX + dx] = '.';
			stage[currentY + dy * 2][currentY + dy * 2] = 'o';
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == '#') {
			return;
		}
		else if (stage[currentY + dy * 2][currentX + dx * 2] == 'o') {
			return;
		}
	}*/

	currentX += dx;
	currentY += dy;
}

/*���������� �׸���, �÷��̾� ���*/
void DrawStage() {
	for (int stageY = 0; stageY < 20; stageY++) {
		for (int stageX = 0; stageX < 120; stageX++) {
			gotoxy(stageX, stageY);
			_putch(stage[stageY][stageX]);
		}
	}
	gotoxy(currentX, currentY); //�÷��̾��� ���� ��ǥ�� ���� �÷��̾ ��Ÿ��
	_putch('@');
}

/*�ܼ� â�� Ŀ���� ����� �Լ�*/
void Cursorhide(char show) {
	HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

/*���������� Ŭ���� �ߴ��� Ȯ���ϴ� �Լ�*/
int StageClear() {
	int cx = 0, cy = 0;
	int count = 0;
	for (cy = 0; cy < 10; cy++) {
		for (cx = 0; cx < 21; cx++) {
			if (stage[cy][cx] == '.' || stage[cy][cx] == 'o') //.�� �ְų� o�� ������ count++
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

/*=============================================================================*/

int main() {
	int x = 0, y = 0;
	
	Cursorhide(0);
	while (1) {
		memcpy(stage, StageData, sizeof(stage)); //memcpy�� �޸𸮸� ����
		for (y = 0; y < 20; y++) { //�÷��̾ ã�Ƽ� ��ǥ�� �Է¹ް�, ���� �ִ� �ڸ��� ��������
			for (x = 0; x < 120; x++) {
				if (stage[y][x] == '@') {
					currentX = x; //�÷��̾� ���� ��ǥ ����
					currentY = y;
					stage[y][x] = ' '; //�̵������Ƿ� ���� �ִ� �ڸ��� ��������
				}
			}
		}
		system("cls");
		while (1) {
			DrawStage(); // ���������� �÷��̾� ���
			PlayerControl(); //�÷��̾�, ������ ������ ����
			if (RestartValue == 1) {
				RestartValue = 0;
				break;
			}

			if (StageClear() == 1) { //���������� ���ٸ� ���α׷� ����
				system("cls");
				DrawStage();

				_getch();
				Sleep(10);
				system("cls");
				return 0;
			}
		}
	}
	_getch();

	system("pause");
	return 0;
}