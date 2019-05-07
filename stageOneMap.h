#pragma once
#include "gameNode.h"
#include "mapTool.h"

class stageOneMap : public gameNode
{
private:
	UINT TILEX;
	UINT TILEY;

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

