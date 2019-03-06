#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	_loadingScene = new loadingScene;
	_menuScene = new menuScene;
	_mapTool = new mapTool;
	_stage_1 = new stage_1;

	SCENEMANAGER->addScene("loadingScene", _loadingScene);
	SCENEMANAGER->addScene("menuScene", _menuScene);
	SCENEMANAGER->addScene("uiScene", _uiScene);
	SCENEMANAGER->addScene("mapTool", _mapTool);
	SCENEMANAGER->addScene("stage1", _stage_1);

	SCENEMANAGER->changeScene("stage1");
	
	return S_OK;
}

void playGround::release()
{
	gameNode::release();
	
}

void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("mapTool");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("stage1");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("menuScene");
	}
	KEYANIMANAGER->update();
}
void playGround::render()
{
	// Draw ���� - �� �ڵ尡 ������ D2D ��� X
	D2DMANAGER->beginDraw();
	//===========================================================================
	//				##		���⿡ �ڵ� �ۼ�(Start)			##


	SCENEMANAGER->render();




	//				##			���⿡ �ڵ� �ۼ�(End)			##
	//===========================================================================
	//				##ī�޶� ���� ���콺 ���� �ð����� ���	##===================
	WCHAR str[128];
	swprintf_s(str, L"cameraX : %d", CAMERA->getCameraX());
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 80, 20, RGB(0, 0, 0));
	swprintf_s(str, L"cameraY : %d", CAMERA->getCameraY());
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 100,20, RGB(0, 0, 0));
	swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 140, 20, RGB(0, 0, 0));
	swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);								
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 160, 20, RGB(0, 0, 0));
	//TIMEMANAGER->render();
	// Draw �� - �� �ڵ尡 ������ D2D ��� X
	D2DMANAGER->endDraw();
}



