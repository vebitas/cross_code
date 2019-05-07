#pragma once
#include "gameNode.h"
#include "bossBullet.h"


enum BOSSDIRECTION
{
	//보스 방향
	BOSS_UP,
	BOSS_DOWN,
	BOSS_RIGHT,
	BOSS_LEFT,
};

enum BOSSSTATE
{
	//보스 상태
	BOSS_IDLE,
	BOSS_SHADOW,
	BOSS_MOVE,
	BOSS_RUSH,
	BOSS_DIVING,
	BOSS_UPRUSH,
	BOSS_GROGGY
};


struct tagBoss
{
	D2D1_RECT_F rc;
	D2D1_RECT_F attackRc; 
	image* headImg;
	image* bodyImg;
	image* body2Img;
	image* body3Img;
	image* body4Img;
	image* body5Img;
	image* tailImg;
	image* divingImg;
	animation* ani;
	BOSSDIRECTION direction;
	BOSSSTATE state;
	string name;
	float x, y;
	float speed;
	float moveAngle;
	float angle;
	float alpha;
	int HP;
	int maxHP;
	int damage;
	float jumpPower;
	float jumpStartX, jumpStartY;
};

struct tagBody
{
	float headX = 0, headY = 0;
	float body1_x = 0, body1_y = 0;
	float body2_x = 0, body2_y = 0;
	float body3_x = 0, body3_y = 0;
	float body4_x = 0, body4_y = 0;
	float body5_x = 0, body5_y = 0;
	float tailX = 0, tailY = 0;
	float angle = 0;
	float angle1 = 0;
	float angle2 = 0;
	float angle3 = 0;
	float angle4 = 0;
	float angle5 = 0;
	float tailAngle = 0;
	float headSize = 0;
	float bodySize_1 = 0;
	float bodySize_2 = 0;
	float bodySize_3 = 0;
	float bodySize_4 = 0;
	float bodySize_5 = 0;
	float tailSize = 0;

};

class boss : public gameNode
{
private:
	tagBoss _boss;
	tagBody _body;
	bossBullet* _bossBullet;

	int _curFrameX;
	int _tailFrameX;
	int _tailCount;
	int _count;

	int _frameCount;
	int _bodyCount;
	float _angleSpeed;

	bool _isLeft;

	int _bodyMoveCount[6];

	int _eyeFrame;

	int _randA, _randB;

	int _oldTime;

	int _effectTime;

	bool _keyOnceDown[4];
	bool _keyUp[4];

	bool _groggyPos;
	bool _rushOn;
	bool _once;
	bool _turn;

public:
	boss();
	~boss();

	HRESULT init();
	void release();
	void update();
	void render();

	void bossState();
	void rush();
	void idle();

	static void cbDiving(void* obj);

public:
	//접근 설정 모음
	float getBossPosX() { return _boss.x; }
	float getBossPosY() { return _boss.y; }
	float getMoveAngle() { return _boss.moveAngle; }
	float getBossSpeed() { return _boss.speed; }
	BOSSSTATE getBossState() { return _boss.state; }
	BOSSDIRECTION getBossDirection() { return _boss.direction; }
	int getBossHP() { return _boss.HP; }
	int getBossMaxHP() { return _boss.maxHP; }
	float getBossAlpha() { return _boss.alpha; }
	D2D1_RECT_F getBossAttackRc() { return _boss.attackRc; }
	D2D1_RECT_F getBossRc() { return _boss.rc; }

	void setBossPosX(float x) { _boss.x = x; }
	void setBossPosY(float y) { _boss.y = y; }
	void setBossSpeed(float speed) { _boss.speed = speed; }
	void setBossMoveAngle(float angle) { _boss.moveAngle = angle; }
	void setEffectTime(int time) { _effectTime = time; }
	void setBossState(BOSSSTATE state) { _boss.state = state; }
	void setBossDirection(BOSSDIRECTION direction) { _boss.direction = direction; }
	void setBossEyeFrame(int eyeFrameX) { _eyeFrame = eyeFrameX; }
	void setBossHP(int HP) { _boss.HP = HP; }
	void setBossAlpha(float alpha) { _boss.alpha = alpha; }

};

