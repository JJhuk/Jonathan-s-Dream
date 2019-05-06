#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 //���� ����
#define Menu_X 10
#define Menu_Y 20

int select_opt;	//�����Ƽ� �׳� ����������.

//�Լ��� gotoxy
//���ڰ��� x,y �� �����ϸ� �� ���� �� ������ Ŀ���� ������

void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

//�Լ��� KeyControl
//��� : Ű�� ���� ���� return ��

int KeyControl() {
	char temp = _getch();

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


// �Լ��� : DrawTemplate
// ��� : ������ Ʋ�� ����ϴ��Լ�
void DrawTemplate() {
	gotoxy(0, 0);
	printf("========================================================================================================================\n");
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
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("|                                                                                                                      |\n");
	printf("========================================================================================================================\n");
}

int DrawMenu() {
	DrawTemplate();
	int x = Menu_X;
	int y = Menu_Y;
	gotoxy(x - 2, y);
	printf("> ���� ���� ");
	gotoxy(x, y + 1);
	printf("�� �� �� ��");
	gotoxy(x, y + 2);
	printf("   �� ��   ");
	while (1) {
		int n = KeyControl();
		switch (n) {
		case UP: {
			if (y > Menu_Y) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < Menu_Y + 2) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
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
	select_opt = DrawMenu();		//1 ���ӽ��� 2 �������� 3����
}

void DrawCredit() {
	DrawTemplate();
	int x = Menu_X;
	int y = Menu_Y;
	gotoxy(x, y);
	printf("������ : XXX(��Ī)");
	gotoxy(x, y + 1);
	printf("�� ��");
	gotoxy(x, y + 2);
	printf("������");
	gotoxy(x, y + 3);
	printf("����");
	gotoxy(x, y + 4);
	printf("������");
	gotoxy(x, y + 5);
	printf("�̼�ȣ");
	_getch();
}


int main()
{
	bool GameStart = true;

	while (GameStart) {
		system("cls");
		gameInit();

		switch (select_opt) {
		case 1:
			DrawTemplate();
			_getch();
			system("cls");
			break;
		case 2:
			DrawCredit();
			system("cls");
			break;
		case 3:
			GameStart = false;
		}
	}
	return 0;
}


