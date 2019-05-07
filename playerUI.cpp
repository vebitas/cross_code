#include "stdafx.h"
#include "playerUI.h"


playerUI::playerUI()
{
}


playerUI::~playerUI()
{
}

HRESULT playerUI::init()
{
	_attributeFrameX = 0;

	_rc[0] = { (float)25, (float)25, (float)50, (float)50 };	
	_rc[1] = { (float)25, (float)25, (float)50, (float)50 };
	_rc[2] = { (float)25, (float)25, (float)50, (float)50 };
	_rc[3] = { (float)25, (float)25, (float)50, (float)50 };

	_isUI = false;
	return S_OK;
}

void playerUI::release()
{
}

void playerUI::update()
{
	POINT ptMouse;
	ptMouse.x = _ptMouse.x;
	ptMouse.y = _ptMouse.y;

	_isUI = false;
	if (PtInRect(&makeRECT(_rc[0]), ptMouse))		//플레이어 UI 렉트와 충돌 했을 때 공격이펙트 전환
	{
		_isUI = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_attributeFrameX == 1)
				_attributeFrameX = 0;
			else
				_attributeFrameX = 1;
		}
	}
	else if(PtInRect(&makeRECT(_rc[1]), ptMouse))
	{
		_isUI = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_attributeFrameX == 4)
				_attributeFrameX = 0;
			else
				_attributeFrameX = 4;
		}
	
	}
	else if (PtInRect(&makeRECT(_rc[2]), ptMouse))
	{
		_isUI = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_attributeFrameX == 2)
				_attributeFrameX = 0;
			else
				_attributeFrameX = 2;
		}
	}
	else if (PtInRect(&makeRECT(_rc[3]), ptMouse))
	{
		_isUI = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_attributeFrameX == 3)
				_attributeFrameX = 0;
			else
				_attributeFrameX = 3;
		}
	}

	
	_rc[0] = { (float)85 + CAMERA->getCameraX(), (float)35 + CAMERA->getCameraY(), (float)125 + CAMERA->getCameraX(), (float)75 + CAMERA->getCameraY() };
	_rc[1] = { (float)35 + CAMERA->getCameraX(), (float)85 + CAMERA->getCameraY(), (float)75 + CAMERA->getCameraX(), (float)125 + CAMERA->getCameraY() };
	_rc[2] = { (float)135 + CAMERA->getCameraX(), (float)85 + CAMERA->getCameraY(), (float)175 + CAMERA->getCameraX(), (float)125 + CAMERA->getCameraY() };
	_rc[3] = { (float)85 + CAMERA->getCameraX(), (float)135 + CAMERA->getCameraY(), (float)125 + CAMERA->getCameraX(), (float)175 + CAMERA->getCameraY() };
}

void playerUI::render(int HP, int MAXHP, int LV)
{

	IMAGEMANAGER->findImage("playerAttribute")->frameRender(25 + CAMERA->getCameraX(), 25 + CAMERA->getCameraY(), _attributeFrameX, 0, 1);
	IMAGEMANAGER->findImage("playerUI")->render(125 + CAMERA->getCameraX(), 25 + + CAMERA->getCameraY(), 1);
	IMAGEMANAGER->findImage("playerHPBar")->render(200 + CAMERA->getCameraX(), 90 + CAMERA->getCameraY(),(float)((HP * 103 / MAXHP)), 7, 0 , 0, 103, 7, 1);
	IMAGEMANAGER->findImage("number")->frameRender(220 + CAMERA->getCameraX(), 32 + CAMERA->getCameraY(), LV, 0, 1);
	//IMAGEMANAGER->findImage("number")->frameRender(220 + CAMERA->getCameraX(), 70 + CAMERA->getCameraY(), (HP / 1000) % 10, 0, 1); //천의 자리
	if(!((int)(HP / 100) % 10 == 0))
	IMAGEMANAGER->findImage("number")->frameRender(240 + CAMERA->getCameraX(), 70 + CAMERA->getCameraY(), 15, 20, (int)(HP / 100) % 10, 0, 1); //백의 자리
	if (!((int)(HP / 10) % 10 == 0) || !((int)(HP / 100) % 10 == 0))
	IMAGEMANAGER->findImage("number")->frameRender(255 + CAMERA->getCameraX(), 70 + CAMERA->getCameraY(), 15, 20, (int)(HP / 10) % 10, 0, 1); //십의 자리
	IMAGEMANAGER->findImage("number")->frameRender(270 + CAMERA->getCameraX(), 70 + CAMERA->getCameraY(), 15, 20, HP % 10, 0, 1); //일의 자리
	//for (int i = 0; i < 4; i++)
	//{
	//	D2DMANAGER->drawRectangle(RGB(255, 0, 255), _rc[i]);
	//}
	//WCHAR str[128];
	//swprintf_s(str, L"최대체력 : %d", MAXHP);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 400, CAMERA->getCameraY() + 70, 20, RGB(255, 255, 255));
}
