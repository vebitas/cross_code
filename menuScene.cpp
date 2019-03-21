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
	IMAGEMANAGER->addImage("blackground2", L"image/intro/lodingBackground2.png", 1024, 768);
	IMAGEMANAGER->addImage("titleLogo", L"image/intro/title_logo.png", 325, 111);
	IMAGEMANAGER->addImage("clouds", L"image/intro/clouds.png", 1024, 499);
	IMAGEMANAGER->addImage("sky", L"image/intro/sky.png", 1024, 712);
	IMAGEMANAGER->addImage("ground", L"image/intro/ground.png", 1024, 292);
	IMAGEMANAGER->addImage("railings", L"image/intro/railings.png", 1024, 114);
	IMAGEMANAGER->addImage("planet", L"image/intro/planet.png", 300, 525);
	IMAGEMANAGER->addImage("keyboard", L"image/intro/keyboard.png", 102, 50);
	IMAGEMANAGER->addFrameImage("lea", L"image/intro/lea.png", 1800, 399, 6, 1);
	IMAGEMANAGER->addFrameImage("newGameB", L"image/intro/newGameButton.png", 288, 144 , 1, 3);
	IMAGEMANAGER->addFrameImage("optionB", L"image/intro/optionButton.png", 288, 144, 1, 3);
	IMAGEMANAGER->addFrameImage("exidB", L"image/intro/exidButton.png", 288, 144, 1, 3);

	_fish = IMAGEMANAGER->findImage("rfgFish");
	_fishText = IMAGEMANAGER->findImage("rfgText");

	_rfgFishY = WINSIZEY / 2 - 200;
	_rfgAlpha = 0;
	_rfgTextAlpha = 0;
	_blackgroundAlpha = 0;
	_next = 0;
	_titleLogoAlpha = 0;
	_titleLogoPosY = 0;
	_titleLogoAlpha = 0;
	_cloudPosY = WINSIZEY / 2 - 200;
	_cloudAlpha = 0;
	_groundPosY = WINSIZEY / 2 + 100;
	_groundAlpha = 0;
	_skyPosY = WINSIZEY / 2;
	_skyAlpha = 0;
	_planetPosY = 0;
	_planetAlpha = 0;
	_railingsPosY = WINSIZEY / 2 + 535;
	_railingsAlpha = 0;
	_leaPosY = WINSIZEY / 2 + 250;
	_leaAlpha = 0;
	_keyboardAlpha = 0;
	_leaFrameX = 0;
	_count = 0;
	_fade = false;

	_buttonCount = 0;
	_newGameBPosX = -150;
	_newGameButton = new button;
	_newGameButton->init("newGameB", _newGameBPosX, WINSIZEY / 2, PointMake(0, 2), PointMake(0, 0), PointMake(0, 1), newGameB);
	_optionBPosX = -150;
	_optionButton = new button;
	_optionButton->init("optionB", _optionBPosX, WINSIZEY / 2 + 100, PointMake(0, 2), PointMake(0, 0), PointMake(0, 1), optionB);
	_exidBPosX = -150;
	_exidButton = new button;
	_exidButton->init("exidB", _exidBPosX, WINSIZEY / 2 + 200, PointMake(0, 2), PointMake(0, 0), PointMake(0, 1), exidB);


	return S_OK;
}

void menuScene::release()
{
}

void menuScene::update()
{
	introUpdate();

	_count++;
	if (_count % 5 == 0)
	{
		if (_leaFrameX < 5)
			_leaFrameX++;
		else
			_leaFrameX = 0;
	}
}

void menuScene::render()
{
	//버튼 업데이트 
	_newGameButton->update(_newGameBPosX, WINSIZEY / 2 + 50);
	_optionButton->update(_optionBPosX, WINSIZEY / 2 + 150);
	_exidButton->update(_exidBPosX, WINSIZEY / 2 + 250);
	introRender();
	WCHAR str[128];
	swprintf_s(str, L"길이 : %d", _next);
	D2DMANAGER->drawText(str, 100, 100);
}

void menuScene::introRender()
{
	IMAGEMANAGER->findImage("blackground")->render(_blackgroundAlpha);

	IMAGEMANAGER->findImage("rfgFish")->render(WINSIZEX / 2 - 75, _rfgFishY, _rfgAlpha);
	IMAGEMANAGER->findImage("rfgText")->render(WINSIZEX / 2 - 130, WINSIZEY / 2 + 70, _rfgTextAlpha);
	
	
	IMAGEMANAGER->findImage("sky")->render(0, _skyPosY - 300, _skyAlpha);
	IMAGEMANAGER->findImage("planet")->render(0, _planetPosY, _planetAlpha);
	IMAGEMANAGER->findImage("clouds")->render(0, _cloudPosY, _cloudAlpha);
	IMAGEMANAGER->findImage("ground")->render(0, _groundPosY, _groundAlpha);
	IMAGEMANAGER->findImage("railings")->render(0, _railingsPosY, _railingsAlpha);
	IMAGEMANAGER->findImage("titleLogo")->render(WINSIZEX / 2 - 300, WINSIZEY / 2 - 100 + _titleLogoPosY, 600, 200, _titleLogoAlpha);
	IMAGEMANAGER->findImage("lea")->frameRender(WINSIZEX / 2 + 150, _leaPosY , _leaFrameX, 0, _leaAlpha);
	IMAGEMANAGER->findImage("keyboard")->render(WINSIZEX / 2 - 100, WINSIZEY / 2 - 80, 200, 98, _keyboardAlpha);
	if (_buttonCount > 0)
	{
		_newGameButton->render();
		_optionButton->render();
		_exidButton->render();
	}
	IMAGEMANAGER->findImage("blackground2")->render(1);
	
	
}

void menuScene::introUpdate()
{
	

	//인트로 순서업데이트
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
		if (_titleLogoAlpha <= 1)
		{
			_titleLogoAlpha += 0.01;
		}
		else
		{
			if(_titleLogoPosY > -180)
			_titleLogoPosY -= 2;
			else if (_leaAlpha < 1)
			{
				_cloudAlpha += 0.01;
				_groundAlpha += 0.01;
				_skyAlpha += 0.01;
				_planetAlpha += 0.01;
				_railingsAlpha += 0.01;
				_leaAlpha += 0.01;

				if (_cloudPosY > 100)
				{
					_cloudPosY -= 2;
					_planetPosY -= 2;
				}
				if (_groundPosY > 440)
					_groundPosY -= 1;
				if (_leaPosY > 280)
				{
					_leaPosY -= 5;
					_railingsPosY -= 5;
				}


				if (_blackgroundAlpha >= 0)
					_blackgroundAlpha -= 0.01;
			}
			else
			{
				if (_keyboardAlpha == 0)
					_keyboardAlpha = 1;
				else
				{
					if (_fade)
					{
						if (_keyboardAlpha < 1)
						{
							_keyboardAlpha += 0.01;
						}
						else
						{
							_fade = false;
						}
					}
					else
					{
						if (_keyboardAlpha > 0.2f)
						{
							_keyboardAlpha -= 0.01;
						}
						else
						{
							_fade = true;
						}
					}	
				}
				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					_next++;
					_fade = false;
					_keyboardAlpha = 0;
				}
			}
		}
		break;
	case 3:
		_buttonCount++;
		if(_newGameBPosX < 150 && _buttonCount > 0)
		_newGameBPosX += 10;
		if (_optionBPosX < 150 && _buttonCount > 10)
			_optionBPosX += 10;
		if (_exidBPosX < 150 && _buttonCount > 20)
			_exidBPosX += 10;

		break;
	}
}

void menuScene::newGameB()
{
	SCENEMANAGER->changeScene("stage1");
}

void menuScene::optionB()
{
	SCENEMANAGER->changeScene("uiScene");
}

void menuScene::exidB()
{
	PostQuitMessage(0);
}


