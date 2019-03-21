#pragma once
#include "gameNode.h"
#include "boss.h"
#include "shredder.h"
#include "hedgehog.h"

class enemyManager : public gameNode
{
private:
	//보스
	boss* _boss;
	//갑옷몬스터
	vector<shredder*> _vShredder;
	vector<shredder*>::iterator _viShredder;
	//고슴도치
	vector<hedgehog*> _vHedgehog;
	vector<hedgehog*>::iterator _viHedgehog;

	int _hogOldTime, _hogDirctionPatten, _hogStatePatten;
	int _randNum;
	int _hogAttackTime;
	int _hogAttatedTime;
	bool _hogAttack;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render(float alpha);

	void setHedgehog();
	void hogAI(float playerX, float playerY);
	void enemyDeath();

public:
	//접근 설정자
	vector<hedgehog*> getVHog() { return _vHedgehog; }
	vector<hedgehog*>* setVHog() { return &_vHedgehog; }

	void setHogAttack(bool attack) { _hogAttack = attack; }

private:
	//내부함수

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}
};

