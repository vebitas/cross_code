#include "stdafx.h"
#include "bossScene.h"


bossScene::bossScene()
{
}


bossScene::~bossScene()
{
}

HRESULT bossScene::init()
{
	_bossMap = new bossStageMap;
	_boss = new boss;
	_player = new player;

	KEYANIMANAGER->deleteAll();
	_boss->init();
	_bossMap->init();
	_player->init();
	_boss->setBossPosX(50 * TILESIZE / 2);
	_boss->setBossPosY(36 * TILESIZE / 2);
	CAMERA->init(WINSIZEX, WINSIZEY, 50 * TILESIZE, 36 * TILESIZE);
	return S_OK;
}

void bossScene::release()
{
	SAFE_DELETE(_bossMap);
	SAFE_DELETE(_boss);
	SAFE_DELETE(_player);
}

void bossScene::update()
{
	CAMERA->update(_player->getPlayerPosX(), _player->getPlayerPosY());
	_boss->update();
	_player->update();
	
}

void bossScene::render()
{
	_bossMap->render();
	EFFECTMANAGER->render(0);
	_boss->render();
	_player->render();
}
