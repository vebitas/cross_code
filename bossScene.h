#pragma once
#include "gameNode.h"
#include "bossStageMap.h"
#include "boss.h"
#include "player.h"

class bossScene : public gameNode
{
private:
	bossStageMap* _bossMap;
	boss* _boss;
	player* _player;

public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

