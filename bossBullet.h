#pragma once
#include "gameNode.h"

struct tagBossBullet
{
	image* image;
	D2D1_RECT_F rc;
	float x, y;
	float fireX, fireY;
	animation* ani;
	float angle;
	float radius;
	float speed;
	bool isCollision;
};

class bossBullet : public gameNode
{
private:
	vector<tagBossBullet> _vBossBullet;
	vector<tagBossBullet>::iterator _viBossBullet;

	const char* _imageName;
	float _range;
	int _bossBulletMax;

public:
	bossBullet();
	~bossBullet();

	HRESULT init(const char* imageName, float range, int bulletMax);
	void release();
	void update();
	void render();

	void move();
	void bulletFire(float x, float y, float angle, float speed);
};

