#pragma once
#include "gameNode.h"

struct tagPlayerBullet
{
	image* image;
	D2D1_RECT_F rc;
	float x, y;
	float fireX, fireY;
	animation* ani;
	//int idX, idY;
	float angle;
	float radius;
	float speed;
	bool isCollision;
};

class playerBullet
{
private:
	vector<tagPlayerBullet> _vPlayerBullet;
	vector<tagPlayerBullet>::iterator _viPlayerBullet;

	const char* _imageName;
	float _range;
	int _playerBulletMax;
	

public:
	playerBullet();
	~playerBullet();

	HRESULT init(const char* imageName, float range, int bulletMax);
	void release();
	void update();
	void render();

	void move();
	void bulletFire(float x, float y, float angle, float speed);

public:
	//접근자 설정자
	vector<tagPlayerBullet> getVPlayerBullet() { return _vPlayerBullet; }
	vector<tagPlayerBullet>* setVPlayerBullet() { return &_vPlayerBullet; }
};

