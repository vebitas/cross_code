#pragma once
#include "gameNode.h"
#include "bossStageMap.h"
#include "boss.h"
#include "bossBullet.h"
#include "player.h"

class bossScene : public gameNode
{
private:
	bossStageMap* _bossMap;
	boss* _boss;
	bossBullet* _bossBullet;
	player* _player;

	D2D1_RECT_F _tileCheckRc;
	POINT _tileIndex[3];

	int _cameraTime;
	int _bossPatten;
	int _bossAttackPatten;
	int _bossPattenTime;
	int _bossDashCount;
	int _bossBulletCount;
	POINT _bulletMarkPos[5];
	POINT _bulletPos[5];
	bool _markBoom[5];
	bool _turnWait[5];

	float _effTime; 
	int _bossAlpha;
	int _bossCollTime;
	int _bossAttackedTime;

	bool _bossDeath;
	bool _bossAttacked;
	bool _bulletMarkRender;
	bool _effZorder;
	bool _once;
	bool _pattenOnce;
public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileCheck();
	void bossCollision();
	void playerCollision();
	void BossAI(float playerX, float playerY, bool battleStart);

	void setWindowsSize(int x, int y, int width, int height);

private:
	//내부함수

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}
};

