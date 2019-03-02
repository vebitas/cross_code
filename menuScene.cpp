#include "stdafx.h"
#include "menuScene.h"


menuScene::menuScene()
{
}


menuScene::~menuScene()
{
}

HRESULT menuScene::init()
{
	IMAGEMANAGER->addImage("glow_1", L"image/intro/glow_1.png", WINSIZEX, 34);
	IMAGEMANAGER->addImage("glow_2", L"image/intro/glow_2.png", 128, 122);
	IMAGEMANAGER->addImage("glow_3", L"image/intro/glow_3.png", 128, 122);
	IMAGEMANAGER->addImage("rfgFish", L"image/intro/rfg-fish.png", 150, 150);
	IMAGEMANAGER->addImage("rfgText", L"image/intro/rfg-Text.png", 254, 46);
	IMAGEMANAGER->addImage("blackground", L"image/intro/lodingBackground.png", 1024, 768);

	_fish = IMAGEMANAGER->findImage("rfgFish");
	_fishText = IMAGEMANAGER->findImage("rfgText");

	_rfgFishY = WINSIZEY / 2 - 200;
	_rfgAlpha = 0;
	_rfgTextAlpha = 0;
	_blackgroundAlpha = 0;
	_next = 0;
	
	_glowAlpha_1 = 0;
	_glowAlpha_2 = 0;
	_glowAlpha_3 = 0;


	return S_OK;
}

void menuScene::release()
{
}

void menuScene::update()
{
	introUpdate();
}

void menuScene::render()
{
	
	introRender();
	WCHAR str[128];
	swprintf_s(str, L"±æÀÌ : %d", _glowAlpha_2);
	D2DMANAGER->drawText(str, 100, 100);
}

void menuScene::introRender()
{
	IMAGEMANAGER->findImage("blackground")->render(_blackgroundAlpha);
	IMAGEMANAGER->findImage("rfgFish")->render(WINSIZEX / 2 - 75, _rfgFishY, _rfgAlpha);
	IMAGEMANAGER->findImage("rfgText")->render(WINSIZEX / 2 - 130, WINSIZEY / 2 + 70, _rfgTextAlpha);
	IMAGEMANAGER->findImage("glow_2")->render(WINSIZEX / 2, WINSIZEY / 2 - 61, _glowAlpha_2);
	IMAGEMANAGER->findImage("glow_2")->render(WINSIZEX / 2, WINSIZEY / 2 - 61, _glowAlpha_2);
	IMAGEMANAGER->findImage("glow_1")->render(0, WINSIZEY / 2, _glowAlpha_1);
	IMAGEMANAGER->findImage("glow_3")->render(_glowAlpha_3);

}

void menuScene::introUpdate()
{
	switch (_next)
	{
	case 0:
		if (WINSIZEY / 2 - 80 > _rfgFishY)
		{
			_rfgFishY += 1;
		}
		else
		{
			_next++;
		}
		
		if (_rfgAlpha <= 1)
		{
			_rfgAlpha += 0.01;
			_rfgTextAlpha += 0.01;
		}
		
		break;
	case 1:
		if (_blackgroundAlpha <= 1)
		{
			_blackgroundAlpha += 0.01;
		}
		else
		{
			_next++;
		}

		if (_rfgAlpha >= 0)
		{
			_rfgAlpha -= 0.01;
			_rfgTextAlpha -= 0.01;
		}
		break;
	case 2:
		if (_glowAlpha_1 <= 1)
		{
			_glowAlpha_1 += 0.01;
		}
		else if(_glowAlpha_1 >= 1)
		{
			_glowAlpha_2 += 0.01;
		}
		else
		{

		}

		break;
	}
}


