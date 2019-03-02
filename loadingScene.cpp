#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
	:_currentCount(0)
{
}


loadingScene::~loadingScene()

{
}

HRESULT loadingScene::init()
{
	
	IMAGEMANAGER->addImage("backBar", L"image/intro/backBar.png", 200, 7);
	IMAGEMANAGER->addImage("frontBar", L"image/intro/frontBar.png", 3, 3);
	IMAGEMANAGER->addImage("loadingBackground", L"image/intro/lodingBackground.png", WINSIZEX, WINSIZEY);

	CreateThread
	(
		NULL,			//스레드의 보안속성(자식윈도우가 있을때) 핸들로 자식인지 부모인지 여부파악
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드와 스택크기는 동일)
		ThreadFunction,	//스레드 함수 명
		this,			//스레드의 매개변수 (this로 하면 본 클래스)
		NULL,			//스레드의 특성(NULL로 두면 바로 실행함)
		0				//스레드의 생성 후 스레드의 ID를 넘겨준다 보통은 NULL로 둠.
	);



	return S_OK;
}

void loadingScene::release()
{
}

void loadingScene::update()
{
	_width = (float)_currentCount / (float)LOADINGMAX;
	
	if (_currentCount == LOADINGMAX)
	{
		
	}
}

void loadingScene::render()
{
	IMAGEMANAGER->findImage("loadingBackground")->render(0, 0, 255);
	IMAGEMANAGER->findImage("backBar")->render(100, 100, 255);
	IMAGEMANAGER->findImage("frontBar")->render(100, 100, 960 * _width, 3);

	D2DMANAGER->createBrush(RGB(255, 0, 255), 1);
	WCHAR str[128];
	swprintf_s(str, L"길이 : %d", _currentCount);
	D2DMANAGER->drawText(str, 100, 100);

}

DWORD CALLBACK ThreadFunction(LPVOID lpParameter)
{
	loadingScene* loadHelper = (loadingScene*)lpParameter;

	loadHelper->_currentCount++;

	return 0;
}
