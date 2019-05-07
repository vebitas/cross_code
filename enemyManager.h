#pragma once
#include "gameNode.h"
#include "boss.h"
#include "shredder.h"
#include "hedgehog.h"
#include "easyBot.h"
#include "turret.h"
#include "turretBullet.h"

class enemyManager : public gameNode
{
private:
	//보스
	boss* _boss;
	//갑옷몬스터
	vector<turret*> _vTurret;
	vector<turret*>::iterator _viTurret;
	//고슴도치
	vector<hedgehog*> _vHedgehog;
	vector<hedgehog*>::iterator _viHedgehog;
	//이지봇
	vector<easyBot*> _vEasyBot;
	vector<easyBot*>::iterator _viEasyBot;

	turretBullet* _turretBullet;
	//고슴도치 AI 변수
	int _hogOldTime, _hogDirctionPatten, _hogStatePatten;
	int _randNum;
	int _hogAttackTime;
	int _hogAttatedTime;
	//봇 AI 변수
	int _botOldTime[3], _botDirctionPatten, _botStatePatten;
	int _botAttackTime[3];
	int _botAttatedTime;
	//터렛 AI 변수
	int _tretRandNum;
	int _tretAttackTime[8];

	bool _hogAttack;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update(float playerX, float playerY);
	void render(float alpha);

	void setHedgehog();
	void setEasyBot();
	void setTurret();
	void hogAI(float playerX, float playerY);
	void esayBotAI(float playerX, float playerY, D2D1_RECT_F playerRc);
	void turretAI(float playerX, float playerY, D2D1_RECT_F playerRc);
	void enemyDeath();

public:
	//접근 설정자
	vector<hedgehog*> getVHog() { return _vHedgehog; }
	vector<hedgehog*>* setVHog() { return &_vHedgehog; }

	vector<easyBot*> getVBot() { return _vEasyBot; }
	vector<easyBot*>* setVBot() { return &_vEasyBot; }

	vector<turret*> getVTurret() { return _vTurret; }
	vector<turret*>* setVTurret() { return &_vTurret; }

	turretBullet* getTurretBullet() { return _turretBullet; }

	void setHogAttack(bool attack) { _hogAttack = attack; }



private:
	//내부함수

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}
};

