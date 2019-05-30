#include <iostream>
#include <fmod.hpp>
#include <conio.h> 
#include <ctime>


void Init();
void Update();
void Render();
void Release();

// 전역 변수로 선언
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

			// S 키 누르면 효과음 출력
			if (nKey == 's')
			{
				if (!IsPlaying) // 키를 눌렀을 때 재생 중이 아니었다면 재생한다.
				{
					IsPlaying = true;
					g_System->playSound(g_Sound[1], nullptr, false, &embi_Channel);
				}
				else // 재생 중이었다면 정지한다.
				{
					IsPlaying = false;
					embi_Channel->stop();
				}
			}

		}

		Update();
		Render();
		g_System->update(); // 업데이트 함수
	}

	Release();


	return 0;
}

void Init()
{
	// 배경음, 효과음 초기화
	FMOD::System_Create(&g_System);
	g_System->init(32, FMOD_INIT_NORMAL, nullptr);
	g_System->createSound("Music/track1.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[0]);
	g_System->createSound("Music/keysound.mp3", FMOD_LOOP_NORMAL, nullptr, &g_Sound[1]);

	// 배경음 출력
	g_System->playSound(g_Sound[0], nullptr, false, &g_Channel);
	std::cout << "효과음 OFF" << std::endl;
}

void Update()
{

}

// 스크린 버퍼 초기화 -> 출력 코드 -> 스크린 버퍼 교체
void Render()
{

	// 효과음 유무 출력 부분
	// 입력 받을 때마다 콘솔 창을 지우고 텍스트를 출력한다.

	if (IsPlaying && _kbhit())
	{
		system("cls");
		std::cout << "효과음 ON" << std::endl;
	}
	else if (!IsPlaying && _kbhit())
	{
		system("cls");
		std::cout << "효과음 OFF" << std::endl;
	}



}

void Release()
{
	for (int i = 0; i < 2; i++) g_Sound[i]->release();
	g_System->close();
	g_System->release();
}


