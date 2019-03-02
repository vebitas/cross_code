#pragma once
#include "gameNode.h"

#define LOADINGMAX 300

class loadingScene : public gameNode
{
private:
	RECT _progressRc;		//���α׷����� ��Ʈ
	float _x, _y;
	float _width;

	image* _progressBarTop;
	image* _progressBarBottom;


public:
	loadingScene();
	~loadingScene();

	int _currentCount;

	HRESULT init();
	void release();
	void update();
	void render();

};

static DWORD CALLBACK ThreadFunction(LPVOID lpParameter);

