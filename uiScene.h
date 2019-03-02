#pragma once
#include "gameNode.h"

class uiScene : public gameNode
{
public:
	uiScene();
	~uiScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

