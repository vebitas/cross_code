#pragma once
#include "gameNode.h"
#include "mapTool.h"

class stageTwoMap : public gameNode
{
private:
	UINT TILEX;
	UINT TILEY;
	vector<vector<tagTile*>> _vvMap;

	D2D1_RECT_F _rc[34][46];

public:
	stageTwoMap();
	~stageTwoMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();
	void zOrder();

	UINT getTileX() { return TILEX; }
	UINT getTileY() { return TILEY; }

	D2D1_RECT_F getTileRc(int x, int y) { return _rc[y][x]; }

	tagTile* getTile(int x, int y) { return _vvMap[y][x]; }

};

