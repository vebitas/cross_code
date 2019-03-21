#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "player.h"

class stageOneMap : public gameNode
{
private:
	UINT TILEX;
	UINT TILEY;

	player* _player;

	vector<vector<tagTile*>> _vvMap;


public:
	stageOneMap();
	~stageOneMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();
	void zOrder();

	UINT getTileX() { return TILEX; }
	UINT getTileY() { return TILEY; }

	tagTile* getTile(int x, int y) { return _vvMap[y][x]; }

};

