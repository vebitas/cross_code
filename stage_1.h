#pragma once
#include "gameNode.h"
#include "stageOneMap.h"
#include "player.h"

class stage_1 : public gameNode
{
private:
	stageOneMap* _oneMap;
	player* _player;

public:
	stage_1();
	~stage_1();

	HRESULT init();
	void release();
	void update();
	void render();

	void setWindowsSize(int x, int y, int width, int height);
};

