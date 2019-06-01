#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <wchar.h>
#include <stddef.h>
#include <Windows.h>
#include <locale.h>

/*==================================================================================*/
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define RETRY 4
 /*=============================���� ����======================================4=====*/
wchar_t info[6] = { L"����" };


char stage[20][161] = { '\0', };
const char StageData[20][161] =
{
	{" [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" []                                                                                                                  []"},
	{" [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]"}
};
int Flypos1X[11] = { 60,62,64,66,68,70,68,66,64,62,60 }, Flypos1Y[11] = { 3,4,5,6,7,8,9,10,11,12,13 };
int JoPosX = 15, JoPosY = 4;
/*================================== �Լ� ===========================================*/

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
		dx = -2, dy = 0;
		//return LEFT;
	}
	else if (temp == 'd' || temp == 'D') {
		dx = 2, dy = 0;
		//return RIGHT;
	}

}

void DrawStage() {

	for (int stageY = 0; stageY < 20; stageY++) {
		for (int stageX = 0; stageX < 161; stageX++) {
			gotoxy(stageX, stageY);
			_putch(StageData[stageY][stageX]);
		}
	}
}

/*���������� �׸���, �÷��̾� ���*/
void DrawBird() {
	//wchar_t info[6] = { L"����" };
	//Flypos1X�� ��ǥ�� 2�� �þ�� �Ѵ�


	setlocale(LC_ALL, "");

	for (int i = 0; i < 11; i++) {
		for (int k = 0; k < 11; k++) {
			gotoxy(Flypos1X[k], Flypos1Y[k]);
			putwchar(info[1]);
		}
		for (int j = 0; j < 11; j++) {
			Flypos1X[j] += 2;
		}
		Sleep(1000);
		system("cls");
	}
}

void Jonadan() {
	gotoxy(JoPosX, JoPosY);
	putwchar(info[1]);
}

/*�ܼ� â�� Ŀ���� ����� �Լ�*/
void Cursorhide(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}


/*=============================================================================*/

int main() {
	setlocale(LC_ALL, "");
	int x = 0, y = 0;

	Cursorhide(0);
	while (1) {
		memcpy(stage, StageData, sizeof(stage));
		system("cls");
		while (1) {
			DrawStage();
		}
	}


	system("pause");
	return 0;
}