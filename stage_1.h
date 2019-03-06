#pragma once
#include "gameNode.h"
#include "player.h"

class stage_1 : public gameNode
{
private:
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

