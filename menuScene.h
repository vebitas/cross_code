#pragma once
#include "gameNode.h"

class menuScene : public gameNode
{
private:
	image* _fish;
	image* _fishText;

	float _rfgFishY;

	float _rfgAlpha;
	float _rfgTextAlpha;
	float _blackgroundAlpha;
	float _glowAlpha_1;
	float _glowAlpha_2;
	float _glowAlpha_3;

	int _next;

public:
	menuScene();
	~menuScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void introRender();
	void introUpdate();

};

