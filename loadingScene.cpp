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
		NULL,			//�������� ���ȼӼ�(�ڽ������찡 ������) �ڵ�� �ڽ����� �θ����� �����ľ�
		NULL,			//�������� ����ũ��(NULL�� �θ� ���ξ������ ����ũ��� ����)
		ThreadFunction,	//������ �Լ� ��
		this,			//�������� �Ű����� (this�� �ϸ� �� Ŭ����)
		NULL,			//�������� Ư��(NULL�� �θ� �ٷ� ������)
		0				//�������� ���� �� �������� ID�� �Ѱ��ش� ������ NULL�� ��.
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
	swprintf_s(str, L"���� : %d", _currentCount);
	D2DMANAGER->drawText(str, 100, 100);

}

DWORD CALLBACK ThreadFunction(LPVOID lpParameter)
{
	loadingScene* loadHelper = (loadingScene*)lpParameter;

	loadHelper->_currentCount++;

	return 0;
}
