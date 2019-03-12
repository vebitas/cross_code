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
};

