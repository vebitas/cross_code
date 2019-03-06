#pragma once
#include "gameNode.h"

#define PLAYERFPS 10

enum PLAYERSTATE
{
	PLAYER_IDLE = 0,
	PLAYER_MOVE,
	PLAYER_MOVEBREAK,
	PLAYER_THROW_HOLD,
	PLAYER_THROW,
	PLAYER_ATTACK,
	PLAYER_ATTACK_COMBO2,
	PLAYER_ATTACK_COMBO3,
	PLAYER_JUMP,
	PLAYER_LEVELUP,
	PLAYER_DEATH,
	PLAYER_SKILL_1,
	PLAYER_SKILL_2,
	PLAYER_SKILL_3
};

enum PLAYERDIRECTION
{
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT,
};

struct tagPlayer
{
	D2D1_RECT_F rc;
	D2D1_RECT_F attackRc;
	image* image;
	animation* motion;
	PLAYERSTATE state;
	PLAYERDIRECTION direction;
	string name;
	float x, y;
	float speed;
	float jumpPower;
	float gravity;
	float angle;
	int idX, idY;
	int HP;
	int maxHP;
	int MP;
	int maxMP;
	int damage;
	int money;
	int alphaValue;
	int level;
	int exp;
	int maxExp;
};

class player : public gameNode
{
private:
	tagPlayer _player;

	bool _isLea;
	bool _isRight;

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyAniInit();
	void playerKeyInput();
	void playerState();
	void setType();

	void playerAniName(string playerName, string aniName);
};

