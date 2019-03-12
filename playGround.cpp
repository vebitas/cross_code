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


	IMAGEMANAGER->addFrameImage("stage1_1", L"image/tileNode/stage1_1.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_2", L"image/tileNode/stage1_2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_3", L"image/tileNode/stage1_3.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage2", L"image/tileNode/stage2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);	
	IMAGEMANAGER->addFrameImage("bossStage", L"image/tileNode/bossStage.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_1(mini)", L"image/tileNode/stage1_1(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_2(mini)", L"image/tileNode/stage1_2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_3(mini)", L"image/tileNode/stage1_3(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage2(mini)", L"image/tileNode/stage2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("bossStage(mini)", L"image/tileNode/bossStage(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addImage("mapToolBackground", L"image/tileNode/mapToolBackground.png", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("build_LR", L"image/tileNode/build_LR.png", 64, 830);
	IMAGEMANAGER->addImage("build_UD", L"image/tileNode/build_UD.png", 750, 64);
	IMAGEMANAGER->addFrameImage("button", L"image/tileNode/button.png", 150, 200, 3, 4);
	IMAGEMANAGER->addFrameImage("button2", L"image/tileNode/button_2.png", 375, 250, 3, 5);
	IMAGEMANAGER->addFrameImage("textXY", L"image/tileNode/textXY.png", 96, 48, 2, 1);
	IMAGEMANAGER->addImage("textMap", L"image/tileNode/textMap.png", 96, 48);
	IMAGEMANAGER->addImage("window", L"image/tileNode/window.png", 300, 300);
	IMAGEMANAGER->addFrameImage("okButton", L"image/tileNode/okButton.png", 144, 48, 3, 1);
	IMAGEMANAGER->addFrameImage("number", L"image/tileNode/number.png", 144, 48, 3, 1);

	_loadingScene = new loadingScene;
	_menuScene = new menuScene;
	_mapTool = new mapTool;
	_stage_1 = new stage_1;
	_cursor = LoadCursorFromFile("image/cursor/uiCursor.cur");
	SetCursor(_cursor);

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
	EFFECTMANAGER->update();
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
	//swprintf_s(str, L"cameraX : %d", CAMERA->getCameraX());
	//D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 80, 20, RGB(0, 0, 0));
	//swprintf_s(str, L"cameraY : %d", CAMERA->getCameraY());
	//D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 100,20, RGB(0, 0, 0));
	//swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 140, 20, RGB(0, 0, 0));
	//swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);								
	//D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 160, 20, RGB(0, 0, 0));
	//TIMEMANAGER->render();
	// Draw �� - �� �ڵ尡 ������ D2D ��� X
	D2DMANAGER->endDraw();
}



