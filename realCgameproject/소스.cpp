#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include<time.h>
#include<conio.h>
#define LEFT 2
#define RIGHT 3
#define WIDTH 20 //����ũ��(��������)
#define HEIGHT 10//����(��������)

typedef struct  // �Լ������� ��Ī�� �����ϰ� ����ü�� ����
{
	int x;
	int y;

	int act;
}Tree;

typedef struct
{
	int x;
}Player;

Tree tree[WIDTH]; //����ũ�� ������ �����������ߵ�
Player player; // �÷��̾��� ��ġ�� ��Ÿ��

void gotoxy(int x, int y) // x,y�� ��ǥ�� �������ִ� �� �̰� ������� �׳� �ܿ��� �Ǿ�����
{
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int isKeyDown(int key) //Ű �Է� ����Ȯ��
{
	return ((GetAsyncKeyState(key) & 0x8000) != 0); // �̰͵� ��Ʈ������ ���̶�µ� �� �𸣰���
}

void init()
{
	int i;

	for (i = 0; i < WIDTH; i++)
		tree[i].act = FALSE;

	player.x = WIDTH / 2;
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

int PlayerContainsTree()//�÷��̾�� ��������������
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if ((tree[i].act) && (tree[i].y == 0) && (tree[i].x == player.x))//�÷�� ������ �Ͱ� ������ ������ ��
		{
			return TRUE;
		}
	}

	return FALSE;
}

void MovePlayer() //�÷��̾��� �����̴� ��
{
	if (isKeyDown(0x41)) //������ ��Ÿ���� �ƽ�Ű�ڵ尪
		player.x -= 1; //������ ��� x��ǥ-1
	if (isKeyDown(0x44))// �������� ��Ÿ���� �ƽ�Ű �ڵ尪 ��ü
		player.x += 1; // �������� ��� x��ǥ +1

	if (player.x < 0)
		player.x = 0;
	if (player.x > WIDTH - 1)
		player.x = WIDTH - 1;
}

void PrintMap() // ���� �����
{
	system("cls"); //ó���� �ʱ�ȭ �����ִ� ��

	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (tree[i].act)
		{
			gotoxy(tree[i].x, HEIGHT - tree[i].y);//goto�Լ� x,y��ǥ������ �����ϸ� ����
			printf("��");
		}
	}

	gotoxy(player.x, HEIGHT);
	printf("��");

	gotoxy(0, HEIGHT + 1);
	for (i = 0; i < WIDTH; i++)
		printf("��");
}

int main()
{
	long res;
	char key;
	time_t start, end;
	double pst;
	start = time(NULL);
	init();
	do
	{
		srand((int)malloc(NULL)); //�ߺ����� ���� ����, malloc�Լ��µ����޸��Ҵ�(�����޸𸮸� �� �𸣰ڴ�;)

		CreateTree();
		MoveTree();
		DeleteTree();//���� �Լ����� �ҷ���

		MovePlayer();

		PrintMap();

		Sleep(100);// sleep�Լ��� ������ �ð��� ����ǰų� �ñ׳��� �����ϸ� ��⿡�� Ǯ��
		end = time(NULL);
		pst = difftime(end, start);
		if (pst > 10)
		{
			system("cls");
			printf("Ŭ����!");
			_getch();
			return 0;
		}
	} while (!(PlayerContainsTree()));//�÷��̾ ������ �Ⱥε����� ���� �۵��ؾ��ϹǷ�
	return 0;
}