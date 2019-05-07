#pragma once
#include "gameNode.h"

struct tagTurretBullet
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
	float radius;
	float speed;
	int idX, idY;
	bool isCollision;
};

class turretBullet : public gameNode
{
private:

	vector<tagTurretBullet> _vTurretBullet;
	vector<tagTurretBullet>::iterator _viTurretBullet;

	const char* _imageName;
	float _range;
	int _turretBulletMax;
	POINTF _effPos;
	bool _pang;


public:
	turretBullet();
	~turretBullet();

	HRESULT init(const char* imageName, float range, int bulletMax);
	void release();
	void update();
	void render();

	void move();
	void bulletFire(float x, float y, float angle, float speed);

	

public:
	//접근자 설정자
	vector<tagTurretBullet> getVTurretBullet() { return _vTurretBullet; }
	vector<tagTurretBullet>* setVTurretBullet() { return &_vTurretBullet; }

};

