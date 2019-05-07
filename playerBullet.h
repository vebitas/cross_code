#pragma once
#include "gameNode.h"

struct tagPlayerBullet
{
	image* effImg;
	image* image;
	D2D1_RECT_F rc;
	float x, y;
	float fireX, fireY;
	animation* ani;
	animation* effAni;
	//int idX, idY;
	float angle;
	float imgAngle;
	float radius;
	float speed;
	int idX, idY;
	int ballCount;
	bool isCollision;
	bool isPowerBullet;
};

class playerBullet
{
private:

	vector<tagPlayerBullet> _vPlayerBullet;
	vector<tagPlayerBullet>::iterator _viPlayerBullet;

	const char* _imageName;
	float _range;
	int _playerBulletMax;
	POINTF _effPos;
	bool _explosion;
	

public:
	playerBullet();
	~playerBullet();

	HRESULT init(const char* imageName, float range, int bulletMax);
	void release();
	void update();
	void render();

	void move();
	void bulletFire(float x, float y, float angle, float imgAngle, float speed, bool holdShot);

public:
	//접근자 설정자
	vector<tagPlayerBullet> getVPlayerBullet() { return _vPlayerBullet; }
	vector<tagPlayerBullet>* setVPlayerBullet() { return &_vPlayerBullet; }

};

