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
 /*=============================전역 변수===========================================*/
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
/*================================== 함수 ===========================================*/

/*r이나 R을 누르면 재시작할 수 있는 함수*/
void Restart() {
	RestartValue = 1; //RestartValue가 1이면 재시작 
}

/*커서를 해당 좌표에 보냄*/
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
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

			gotoxy(stageX, stageY);
			_putch(stage[stageY][stageX]);

		}
	}
	gotoxy(currentX, currentY); //플레이어의 현재 좌표에 가서 플레이어를 나타냄
	putwchar(info[0]);
}

/*콘솔 창의 커서를 숨기는 함수*/
void Cursorhide(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
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
	gotoxy(68, 2);
	printf("PLAYER : ★");
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
	printf("- R을 눌러 다시 하기");
}

/*================================================================================*/

int main() {
	setlocale(LC_ALL, "");
	int x = 0, y = 0;

	Cursorhide(0);
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
				return 0;
			}
		}
	}
	_getch();

	system("pause");
	return 0;
}