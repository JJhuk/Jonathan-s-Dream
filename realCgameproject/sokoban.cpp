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
 /*=============================���� ����===========================================*/
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

			gotoxy(stageX, stageY);
			_putch(stage[stageY][stageX]);

		}
	}
	gotoxy(currentX, currentY); //�÷��̾��� ���� ��ǥ�� ���� �÷��̾ ��Ÿ��
	putwchar(info[0]);
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
	gotoxy(68, 2);
	printf("PLAYER : ��");
	gotoxy(68, 3);
	printf("  ROCK : 0O");
	gotoxy(68, 4);
	printf("  HOLE : x ");
	gotoxy(68, 5);
	printf(" CLEAR : <>");
	gotoxy(73, 7);
	printf("U P");
	gotoxy(74, 8);
	printf("W");
	gotoxy(66, 9);
	printf("LEFT A     D RIGHT");
	gotoxy(74, 10);
	printf("S");
	gotoxy(73, 11);
	printf("DOWN");
	gotoxy(67, 13);
	printf("- R�� ���� �ٽ� �ϱ�");
}

/*================================================================================*/

int main() {
	setlocale(LC_ALL, "");
	int x = 0, y = 0;

	Cursorhide(0);
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
				return 0;
			}
		}
	}
	_getch();

	system("pause");
	return 0;
}