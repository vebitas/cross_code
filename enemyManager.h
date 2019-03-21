#pragma once
#include "gameNode.h"
#include "boss.h"
#include "shredder.h"
#include "hedgehog.h"

class enemyManager : public gameNode
{
private:
	//����
	boss* _boss;
	//���ʸ���
	vector<shredder*> _vShredder;
	vector<shredder*>::iterator _viShredder;
	//����ġ
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
	//���� ������
	vector<hedgehog*> getVHog() { return _vHedgehog; }
	vector<hedgehog*>* setVHog() { return &_vHedgehog; }

	void setHogAttack(bool attack) { _hogAttack = attack; }

private:
	//�����Լ�

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}
};

