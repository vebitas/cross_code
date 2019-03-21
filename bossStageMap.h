#pragma once
#include "gameNode.h"
#include "mapTool.h"

class bossStageMap : public gameNode 
{
private:
	UINT TILEX;
	UINT TILEY;

	vector<vector<tagTile*>> _vvMap;


public:
	bossStageMap();
	~bossStageMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();

	UINT getTileX() { return TILEX; }
	UINT getTileY() { return TILEY; }

	tagTile* getTile(int x, int y) { return _vvMap[y][x]; }
};

