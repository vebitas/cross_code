#pragma once
#include "gameNode.h"

class playerUI : public gameNode
{
private:

public:
	playerUI();
	~playerUI();

	HRESULT init();
	void release();
	void update();
	void render();
};

