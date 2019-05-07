#pragma once
#include "gameNode.h"
#define ENEMYFPS 10

enum ENEMYDIRECTION
{
	//쉐더 방향 
	SDER_UP_RIGHT,
	SDER_RIGHT,
	SDER_DOWN_RIGHT,
	SDER_UP_LEFT,
	SDER_LEFT,
	SDER_DOWN_LEFT,
	//고슴도치 방향
	HOG_UP_RIGHT,
	HOG_RIGHT,
	HOG_DOWN_RIGHT,
	HOG_UP_LEFT,
	HOG_LEFT,
	HOG_DOWN_LEFT,
	//이지봇	방향
	BOT_UP_RIGHT,
	BOT_RIGHT,
	BOT_DOWN_RIGHT,
	BOT_UP_LEFT,
	BOT_LEFT,
	BOT_DOWN_LEFT,
};

enum ENEMYSTATE
{
	//쉐더 상태
	SDER_IDLE,
	SDER_MOVE,
	SDER_ATTACK_HOLD,
	SDER_ATTACK,
	//고슴도치
	HOG_IDLE,
	HOG_MOVE,
	HOG_ATTACK,
	HOG_ATTACKED,
	//이지봇
	BOT_IDLE,
	BOT_MOVE,
	BOT_RED_MODE,
	BOT_ATTACK,
	BOT_ATTACKED,
	//터렛
	TURRET_IDLE,
	TURRET_ATTACK
};

struct tagEnemy
{
	image* image;
	D2D1_RECT_F rc;
	D2D1_RECT_F attackRc;
	D2D1_RECT_F rangeRc;
	string name;
	float x, y;
	int idX, idY;
	float speed;
	ENEMYDIRECTION direction;
	ENEMYSTATE state;
	animation* ani;
	int damaga;
	int HP;
	int maxHP;
	float angle;
	float alpha;
	bool isRight;
	bool isAttack;
	bool death;
};

class enemy : public gameNode
{
protected:
	tagEnemy _enemy;

public:
	enemy();
	~enemy();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY);
	virtual void release();
	virtual void update();
	virtual void render();
	

public:
	//설정, 접근자 모음
	D2D1_RECT_F getEnemyRc() { return _enemy.rc; }
	D2D1_RECT_F getEnemyAttackRc() { return _enemy.attackRc; }
	D2D1_RECT_F getEnemyRangeRc() { return _enemy.rangeRc; }
	string getEnemyName() { return _enemy.name; }
	float getEnemyPosX() { return _enemy.x; }
	float getEnemyPosY() { return _enemy.y; }
	int getEnemyIdX() { return _enemy.idX; }
	int getEnemyIdY() { return _enemy.idY; }
	float getEnemySpeed() { return _enemy.speed; }
	ENEMYDIRECTION getEnemyDirection() { return _enemy.direction; }
	ENEMYSTATE getEnemyState() { return _enemy.state; }
	animation* getEnemyAni() { return _enemy.ani; }
	float getEnemyAngle() { return _enemy.angle; }
	int getEnemyMaxHP() { return _enemy.maxHP; }
	int getEnemyHP() { return _enemy.HP; }
	bool getEnemyIsAttack() { return _enemy.isAttack; }
	bool getEnemyDeath() { return _enemy.death; }

	void setEnemyState(ENEMYSTATE state) { _enemy.state = state; }
	void setEnemyDirection(ENEMYDIRECTION direction) { _enemy.direction = direction; }
	void setEnemyPosX(float x) { _enemy.x = x; }
	void setEnemyPosY(float y) { _enemy.y = y; }
	void setEnemyIdX(int idX) { _enemy.idX = idX; }
	void setEnemyIdY(int idY) { _enemy.idY = idY; }
	void setEnemyMaxHP(int maxHP) { _enemy.maxHP = maxHP; }
	void setEnemyHP(int HP) { _enemy.HP = HP; }
	void setEnemySpeed(float speed) { _enemy.speed = speed; }
	void setEnemyAngle(float angle) { _enemy.angle = angle; }
	void setEnemyIsAttack(bool isAttack) { _enemy.isAttack = isAttack; }
};

