#include "stdafx.h"
#include "playerBullet.h"


playerBullet::playerBullet()
{
}


playerBullet::~playerBullet()
{
}

HRESULT playerBullet::init(const char* imageName, float range, int bulletMax)
{
	_imageName = imageName;
	_range = range;
	_playerBulletMax = bulletMax;
	int bulletN[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("playerBullet", "bulletN", _imageName, bulletN, 1, 5, true);

	return S_OK;
}

void playerBullet::release()
{
}

void playerBullet::update()
{
	move();
}

void playerBullet::render()
{
	for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end(); _viPlayerBullet++)
	{
		D2DMANAGER->fillRectangle(RGB(255, 0, 255), _viPlayerBullet->rc);
		//_viPlayerBullet->image->aniRender(_viPlayerBullet->x, _viPlayerBullet->y, _viPlayerBullet->ani);
	}
}

void playerBullet::move()
{
	for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end(); )
	{
		_viPlayerBullet->x += cosf(_viPlayerBullet->angle) * _viPlayerBullet->speed;
		_viPlayerBullet->y += -sinf(_viPlayerBullet->angle) * _viPlayerBullet->speed;

		//_viPlayerBullet->ani->start(false);

		_viPlayerBullet->rc = { (float)_viPlayerBullet->x, (float)_viPlayerBullet->y,
			(float)_viPlayerBullet->x + _viPlayerBullet->image->GetFrameWidth() / 2,
			(float)_viPlayerBullet->y + _viPlayerBullet->image->GetFrameHeight() / 2 };


		if (_range < getDistance(_viPlayerBullet->x, _viPlayerBullet->y, _viPlayerBullet->fireX, _viPlayerBullet->fireY))
		{
			_viPlayerBullet = _vPlayerBullet.erase(_viPlayerBullet);
		}
		else _viPlayerBullet++;
	}
}

void playerBullet::bulletFire(float x, float y, float angle, float speed)
{
	if (_playerBulletMax < _vPlayerBullet.size()) return;

	tagPlayerBullet bullet;
	bullet.image = IMAGEMANAGER->findImage(_imageName);
	bullet.ani = KEYANIMANAGER->findAnimation("playerBullet", "bulletN");
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.speed = speed;
	bullet.radius = bullet.image->GetFrameWidth() / 2;
	bullet.rc = { (float)bullet.x, (float)bullet.y, (float)bullet.x + bullet.image->GetFrameWidth(), (float)bullet.y + bullet.image->GetFrameHeight() };
	bullet.isCollision = false;
	
	_vPlayerBullet.push_back(bullet);
}
