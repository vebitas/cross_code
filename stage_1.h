#pragma once
#include "gameNode.h"
#include "stageOneMap.h"
#include "player.h"
#include "enemyManager.h"

class stage_1 : public gameNode
{
private:
	stageOneMap* _oneMap;
	player* _player;
	enemyManager* _enemyManager;
	//타일체크
	POINT _tileIndex[3];
	POINTF _playerSavePos;
	
	D2D1_RECT_F rc[2];

	D2D1_RECT_F _briRc;
	int _briFrameX, _briFrameY;
	float _briAlpha;
	int _count;

public:
	stage_1();
	~stage_1();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileCheck();
	void enemyTileCheck();
	void playerCollision();
	void enemyCollision();

	void setWindowsSize(int x, int y, int width, int height);

private:
	//내부함수

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}
};

