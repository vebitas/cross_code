#pragma once
#include "gameNode.h"
#include "stageTwoMap.h"
#include "player.h"
#include "enemyManager.h"

class stage_2 : public gameNode 
{
private:
	stageTwoMap* _stage2;
	player* _player;
	enemyManager* _enemyManager;
	//타일체크
	POINT _tileIndex[3];
	//타일체크 RC들
	D2D1_RECT_F _tileCheckRc;
	D2D1_RECT_F _brricadeRc[2];
	D2D1_RECT_F _switchRc;
	D2D1_RECT_F _teleportRc;
	float _brricadeAlpha;
	//몇번 튕기는지
	int _ballCount;
	//오브젝트  프레임 번호
	int _teleportFrameX;
	int _switchFrameX;
	int _switchTime;
	//봇AI에 필요한 변수
	int _botAttackTime;
	bool _botAtttack;
	bool _switchOn;

	int _count;
	int _briFrameX;
	float _sceneChangeAlpha;
	int _turretAttackTime;
	bool _turretAttack;
public:
	stage_2();
	~stage_2();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileCheck();
	void easyBotTileCheck();
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

