#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "menuScene.h"
#include "uiScene.h"
#include "mapTool.h"
#include "stage_1.h"


class playGround : public gameNode
{
private:
	loadingScene* _loadingScene;
	menuScene* _menuScene;
	uiScene* _uiScene;
	mapTool*  _mapTool;
	stage_1* _stage_1;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};