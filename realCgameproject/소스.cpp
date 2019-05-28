#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include<time.h>
#include<conio.h>
#define LEFT 2
#define RIGHT 3
#define WIDTH 20 //가로크기(조절가능)
#define HEIGHT 10//높이(조절가능)

typedef struct  // 함수포인터 별칭을 정의하고 구조체로 묶음
{
	int x;
	int y;

	int act;
}Tree;

typedef struct
{
	int x;
}Player;

Tree tree[WIDTH]; //가로크기 내에서 나무떨어져야됨
Player player; // 플레이어의 위치를 나타냄

void gotoxy(int x, int y) // x,y를 좌표상에 구현해주는 것 이건 설명없이 그냥 외우라고 되어있음
{
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int isKeyDown(int key) //키 입력 여부확인
{
	return ((GetAsyncKeyState(key) & 0x8000) != 0); // 이것도 비트연산자 값이라는데 잘 모르겠음
}

void init()
{
	int i;

	for (i = 0; i < WIDTH; i++)
		tree[i].act = FALSE;

	player.x = WIDTH / 2;
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

int PlayerContainsTree()//플레이어랑 나무랑만났을때
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if ((tree[i].act) && (tree[i].y == 0) && (tree[i].x == player.x))//플레어가 움직인 것과 나무가 만났을 때
		{
			return TRUE;
		}
	}

	return FALSE;
}

void MovePlayer() //플레이어의 움직이는 것
{
	if (isKeyDown(0x41)) //왼쪽을 나타내는 아스키코드값
		player.x -= 1; //왼쪽일 경우 x좌표-1
	if (isKeyDown(0x44))// 오른쪽을 나타내는 아스키 코드값 대체
		player.x += 1; // 오른쪽일 경우 x좌표 +1

	if (player.x < 0)
		player.x = 0;
	if (player.x > WIDTH - 1)
		player.x = WIDTH - 1;
}

void PrintMap() // 맵을 출력함
{
	system("cls"); //처음에 초기화 시켜주는 것

	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (tree[i].act)
		{
			gotoxy(tree[i].x, HEIGHT - tree[i].y);//goto함수 x,y좌표값으로 생각하면 편함
			printf("♠");
		}
	}

	gotoxy(player.x, HEIGHT);
	printf("√");

	gotoxy(0, HEIGHT + 1);
	for (i = 0; i < WIDTH; i++)
		printf("▤");
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
		srand((int)malloc(NULL)); //중복없는 난수 생성, malloc함수는동적메모리할당(동적메모리를 잘 모르겠다;)

		CreateTree();
		MoveTree();
		DeleteTree();//위의 함수들을 불러옴

		MovePlayer();

		PrintMap();

		Sleep(100);// sleep함수로 지정된 시간이 경과되거나 시그널을 수신하면 대기에서 풀림
		end = time(NULL);
		pst = difftime(end, start);
		if (pst > 10)
		{
			system("cls");
			printf("클리어!");
			_getch();
			return 0;
		}
	} while (!(PlayerContainsTree()));//플레이어가 나무랑 안부딪히는 동안 작동해야하므로
	return 0;
}