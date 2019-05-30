#include <iostream>
#include <fmod.hpp>
#include <conio.h> 
#include <ctime>


void Init();
void Update();
void Render();
void Release();

// ���� ������ ����
FMOD::System *g_System;
FMOD::Sound *g_Sound[2];
FMOD::Channel *g_Channel;
bool IsPlaying = false;

int main()
{
	int nKey;
	FMOD::Channel *embi_Channel;

	Init();

	while (1)
	{
		if (_kbhit())
		{
			nKey = _getch();

			// S Ű ������ ȿ���� ���
			if (nKey == 's')
			{
				if (!IsPlaying) // Ű�� ������ �� ��� ���� �ƴϾ��ٸ� ����Ѵ�.
				{
					IsPlaying = true;
					g_System->playSound(g_Sound[1], nullptr, false, &embi_Channel);
				}
				else // ��� ���̾��ٸ� �����Ѵ�.
				{
					IsPlaying = false;
					embi_Channel->stop();
				}
			}

		}

		Update();
		Render();
		g_System->update(); // ������Ʈ �Լ�
	}

	Release();


	return 0;
}

void Init()
{
	// �����, ȿ���� �ʱ�ȭ
	FMOD::System_Create(&g_System);
	g_System->init(32, FMOD_INIT_NORMAL, nullptr);
	g_System->createSound("Music/track1.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[0]);
	g_System->createSound("Music/keysound.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[1]);

	// ����� ���
	g_System->playSound(g_Sound[0], nullptr, false, &g_Channel);
	std::cout << "ȿ���� OFF" << std::endl;
}

void Update()
{

}

// ��ũ�� ���� �ʱ�ȭ -> ��� �ڵ� -> ��ũ�� ���� ��ü
void Render()
{

	// ȿ���� ���� ��� �κ�
	// �Է� ���� ������ �ܼ� â�� ����� �ؽ�Ʈ�� ����Ѵ�.

	if (IsPlaying && _kbhit())
	{
		system("cls");
		std::cout << "ȿ���� ON" << std::endl;
	}
	else if (!IsPlaying && _kbhit())
	{
		system("cls");
		std::cout << "ȿ���� OFF" << std::endl;
	}



}

void Release()
{
	for (int i = 0; i < 2; i++) g_Sound[i]->release();
	g_System->close();
	g_System->release();
}


