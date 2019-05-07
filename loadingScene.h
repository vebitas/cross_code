#pragma once
#include "gameNode.h"
#include "mapTool.h"

#define LOADINGMAX 3000

class loadingScene : public gameNode
{
private:
	RECT _progressRc;		//프로그래스바 렉트
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

	void imgAdd();
	void soundAdd();
	void setWindowsSize(int x, int y, int width, int height);

};

static DWORD CALLBACK ThreadFunction(LPVOID lpParameter);

