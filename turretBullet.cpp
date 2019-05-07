#include "stdafx.h"
#include "turretBullet.h"


turretBullet::turretBullet()
{
}


turretBullet::~turretBullet()
{
}

HRESULT turretBullet::init(const char * imageName, float range, int bulletMax)
{
	_imageName = imageName;
	_range = range;
	_turretBulletMax = bulletMax;

	_effPos.x = 0;
	_effPos.y = 0;
	_pang = false;

	EFFECTMANAGER->addEffect("turretBulletE", "image/enemy/turretBullet.png", 125, 25, 25, 25, 5, 0.05, 100);
	IMAGEMANAGER->addImage("turretBullet", L"image/enemy/turretBullet2.png", 15, 15);
	
	return S_OK;
}

void turretBullet::release()
{
}

void turretBullet::update()
{
	move();
}

void turretBullet::render()
{
	for (_viTurretBullet = _vTurretBullet.begin(); _viTurretBullet != _vTurretBullet.end(); _viTurretBullet++)
	{
		//D2DMANAGER->fillRectangle(RGB(255, 0, 255), _viTurretBullet->rc);
		_viTurretBullet->image->render(_viTurretBullet->x, _viTurretBullet->y);
	}
}

void turretBullet::move()
{
	for (_viTurretBullet = _vTurretBullet.begin(); _viTurretBullet != _vTurretBullet.end(); )
	{
		_viTurretBullet->x += -cosf(_viTurretBullet->angle) * _viTurretBullet->speed;
		_viTurretBullet->y += -sinf(_viTurretBullet->angle) * _viTurretBullet->speed;

		_viTurretBullet->rc = { (float)_viTurretBullet->x + 10 , (float)_viTurretBullet->y + 10 ,
			(float)_viTurretBullet->x + 10 + _viTurretBullet->image->GetFrameWidth() / 2 ,
			(float)_viTurretBullet->y + 10 + _viTurretBullet->image->GetFrameHeight() / 2 };


		if (_range < getDistance(_viTurretBullet->x, _viTurretBullet->y, _viTurretBullet->fireX, _viTurretBullet->fireY))
		{
			_effPos.x = _viTurretBullet->x + 15;
			_effPos.y = _viTurretBullet->y + 15;
			_pang = true;
			_viTurretBullet = _vTurretBullet.erase(_viTurretBullet);

		}
		else
		{
			_viTurretBullet++;
		}
	}

	if (_pang)
	{
		EFFECTMANAGER->play("turretBulletE", _effPos.x, _effPos.y);
		_pang = false;
	}
}

void turretBullet::bulletFire(float x, float y, float angle,  float speed)
{
	if (_turretBulletMax < _vTurretBullet.size()) return;

	tagTurretBullet bullet;
	bullet.image = IMAGEMANAGER->findImage(_imageName);

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.speed = speed;

	bullet.radius = bullet.image->GetFrameWidth() / 2;
	bullet.rc = { (float)x, (float)y, (float)x + bullet.image->GetFrameWidth() / 2, (float)y + bullet.image->GetFrameHeight() / 2 };
	bullet.isCollision = false;

	_vTurretBullet.push_back(bullet);
}
