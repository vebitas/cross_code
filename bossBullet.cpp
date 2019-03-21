#include "stdafx.h"
#include "bossBullet.h"


bossBullet::bossBullet()
{
}


bossBullet::~bossBullet()
{
}

HRESULT bossBullet::init(const char* imageName, float range, int bulletMax)
{
	_imageName = imageName;
	_range = range;
	_bossBulletMax = bulletMax;
	int bulletN[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	KEYANIMANAGER->addArrayFrameAnimation("bossBulletN", "bulletN", _imageName, bulletN, 13, 10, true);
	return S_OK;
}

void bossBullet::release()
{
}

void bossBullet::update()
{
}

void bossBullet::render()
{
	for (_viBossBullet = _vBossBullet.begin(); _viBossBullet != _vBossBullet.end(); _viBossBullet++)
	{
		_viBossBullet->image->aniRender(_viBossBullet->x, _viBossBullet->y, _viBossBullet->ani, 1);
	}
}

void bossBullet::move()
{
	for (_viBossBullet = _vBossBullet.begin(); _viBossBullet != _vBossBullet.end(); _viBossBullet++)
	{
		_viBossBullet->x += cosf(_viBossBullet->angle) * _viBossBullet->speed;
		_viBossBullet->y += -sinf(_viBossBullet->angle) * _viBossBullet->speed;

		_viBossBullet->rc = { (float)_viBossBullet->x, (float)_viBossBullet->y,
		(float)_viBossBullet->x + _viBossBullet->image->GetFrameWidth() / 2,
		(float)_viBossBullet->x + _viBossBullet->image->GetFrameHeight() / 2 };

		if (_range < getDistance(_viBossBullet->x, _viBossBullet->y, _viBossBullet->fireX, _viBossBullet->fireY))
		{
			_viBossBullet = _vBossBullet.erase(_viBossBullet);
		}
		else _viBossBullet++;
	}
}

void bossBullet::bulletFire(float x, float y, float angle, float speed)
{
	if (_bossBulletMax < _vBossBullet.size()) return;

	tagBossBullet bullet;
	bullet.image = IMAGEMANAGER->findImage(_imageName);
	bullet.ani = KEYANIMANAGER->findAnimation("bossBulletN", "bulletN");
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.speed = speed;
	bullet.radius = bullet.image->GetFrameWidth() / 2;
	bullet.rc = { (float)bullet.x, (float)bullet.y, (float)bullet.x + bullet.image->GetFrameWidth() / 2, (float)bullet.y + bullet.image->GetFrameHeight() / 2 };

	_vBossBullet.push_back(bullet);
	
}


