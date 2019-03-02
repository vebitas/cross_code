#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "menuScene.h"
#include "uiScene.h"
#include "mapTool.h"


class playGround : public gameNode
{
private:
	loadingScene* _loadingScene;
	menuScene* _menuScene;
	uiScene* _uiScene;
	mapTool*  _mapTool;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};