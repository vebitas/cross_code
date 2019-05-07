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

	enemyImg();
	effImg();
	objImg();
	soundInit();

	_loadingScene = new loadingScene;
	_menuScene = new menuScene;
	_mapTool = new mapTool;
	_stage_1 = new stage_1;
	_stage_2 = new stage_2;
	_bossScene = new bossScene;
	_uiScene = new uiScene;
	_cursor = LoadCursorFromFile("image/cursor/uiCursor.cur");
	SetCursor(_cursor);

	SCENEMANAGER->addScene("loadingScene", _loadingScene);
	SCENEMANAGER->addScene("menuScene", _menuScene);
	SCENEMANAGER->addScene("uiScene", _uiScene);
	SCENEMANAGER->addScene("mapTool", _mapTool);
	SCENEMANAGER->addScene("stage1", _stage_1);
	SCENEMANAGER->addScene("stage2", _stage_2);
	SCENEMANAGER->addScene("bossScene", _bossScene);

	SCENEMANAGER->changeScene("loadingScene");
	
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
		SCENEMANAGER->changeScene("loadingScene");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene("bossScene");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SCENEMANAGER->changeScene("stage2");
	}
	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
}
void playGround::render()
{
	// Draw 시작 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->beginDraw();
	//===========================================================================
	//				##		여기에 코드 작성(Start)			##

	SCENEMANAGER->render();


	//				##			여기에 코드 작성(End)			##
	//===========================================================================
	//				##카메라 정보 마우스 정보 시간정보 출력	##===================
	WCHAR str[128];
	//swprintf_s(str, L"cameraX : %d", CAMERA->getCameraX());
	//D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 80, 20, RGB(0, 0, 0));
	//swprintf_s(str, L"cameraY : %d", CAMERA->getCameraY());
	//D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 100,20, RGB(0, 0, 0));
	//swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 300, 20, RGB(0, 0, 0));
	//swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);								
	//D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() +400, 20, RGB(0, 0, 0));
	TIMEMANAGER->render();
	// Draw 끝 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->endDraw();
}

void playGround::enemyImg()
{
	
}

void playGround::effImg()
{
	
}

void playGround::objImg()
{
	
}

void playGround::soundInit()
{
	

}



