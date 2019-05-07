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
	
	_effPos.x = 0;
	_effPos.y = 0;
	_explosion = false;

	EFFECTMANAGER->addEffect("ballN_E", "image/effect/ball_N_E.png", 160, 32, 32, 32, 5, 0.05, 20);
	IMAGEMANAGER->addFrameImage("ballN_E", L"image/effect/ball_N_E.png", 160, 16, 10, 1);
	int bulletN[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("playerBullet", "bulletN", _imageName, bulletN, 1, 5, true);
	int bullet[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("playerBullet", "bullet", _imageName, bullet, 4, 5, true);

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
		//D2DMANAGER->fillRectangle(RGB(255, 0, 255), _viPlayerBullet->rc);
		_viPlayerBullet->image->aniRenderAngle(_viPlayerBullet->x, _viPlayerBullet->y, _viPlayerBullet->ani, -(_viPlayerBullet->angle * (180/ PI)) + 90);
	}
	
}

void playerBullet::move()
{
	for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end(); )
	{
		_viPlayerBullet->x += cosf(_viPlayerBullet->angle) * _viPlayerBullet->speed;
		_viPlayerBullet->y += -sinf(_viPlayerBullet->angle) * _viPlayerBullet->speed;

		_viPlayerBullet->ani->start(false);

		_viPlayerBullet->rc = { (float)_viPlayerBullet->x + 10 , (float)_viPlayerBullet->y + 10 ,
			(float)_viPlayerBullet->x + 10 + _viPlayerBullet->image->GetFrameWidth() / 2 ,
			(float)_viPlayerBullet->y + 10 + _viPlayerBullet->image->GetFrameHeight() / 2};


		if (_range < getDistance(_viPlayerBullet->x, _viPlayerBullet->y, _viPlayerBullet->fireX, _viPlayerBullet->fireY))
		{
			_effPos.x = _viPlayerBullet->x + 15;
			_effPos.y = _viPlayerBullet->y + 15;
			_explosion = true;
			_viPlayerBullet = _vPlayerBullet.erase(_viPlayerBullet); 

		}
		else if (_viPlayerBullet->isPowerBullet == true && _viPlayerBullet->ballCount >= 3)
		{
			_effPos.x = _viPlayerBullet->x + 15;
			_effPos.y = _viPlayerBullet->y + 15;
			SOUNDMANAGER->play("throwE_1", 1);
			EFFECTMANAGER->play("ballN_E", _effPos.x, _effPos.y);
			_viPlayerBullet = _vPlayerBullet.erase(_viPlayerBullet);
		}
		else
		{
			_viPlayerBullet++;
		}	
	}
	if (_explosion)
	{
		SOUNDMANAGER->play("throwE_1", 1);
		EFFECTMANAGER->play( "ballN_E", _effPos.x, _effPos.y);
		_explosion = false;
	}
}

void playerBullet::bulletFire(float x, float y, float angle, float imgAngle,float speed, bool holdShot)
{
	if (_playerBulletMax < _vPlayerBullet.size()) return;

	tagPlayerBullet bullet;
	bullet.image = IMAGEMANAGER->findImage(_imageName);
	if (holdShot)
	{
		bullet.isPowerBullet = true;
		bullet.ani = KEYANIMANAGER->findAnimation("playerBullet", "bullet");
	}
	else
	{
		bullet.isPowerBullet = false;
		bullet.ani = KEYANIMANAGER->findAnimation("playerBullet", "bulletN");
	}
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.imgAngle = imgAngle;
	bullet.speed = speed;
	bullet.ballCount = 0;
	
	bullet.radius = bullet.image->GetFrameWidth() / 2;
	bullet.rc = { (float)x, (float)y, (float)x + bullet.image->GetFrameWidth() / 2, (float)y + bullet.image->GetFrameHeight() / 2 };
	bullet.isCollision = false;

	_vPlayerBullet.push_back(bullet);
}
