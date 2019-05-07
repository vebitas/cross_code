#include "stdafx.h"
#include "turret.h"


turret::turret()
{
}


turret::~turret()
{
}

HRESULT turret::init(string enemyName, const char * imageName, float x, float y, int idX, int idY)
{
	enemy::init(enemyName, imageName, x, y, idX, idY);

	_enemy.name = enemyName;
	_enemy.state = ENEMYSTATE::TURRET_IDLE;
	_enemy.alpha = 1;
	_enemy.speed = 0;
	_enemy.isAttack = false;
	_enemy.HP = 50;
	_enemy.rangeRc = { (float)_enemy.x, (float)_enemy.y, (float)_enemy.x + 100, (float)_enemy.y + 100 };

	int idleUp[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleUp", imageName, idleUp, 1, TURRETFPS, true);
	int idleUpRight1[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleUpRight1", imageName, idleUpRight1, 1, TURRETFPS, true);
	int idleUpRight2[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleUpRight2", imageName, idleUpRight2, 1, TURRETFPS, true);
	int idleUpRight3[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleUpRight3", imageName, idleUpRight3, 1, TURRETFPS, true);
	int idleRight[] = { 39 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleRight", imageName, idleRight, 1, TURRETFPS, true);
	int idleDownRight1[] = { 48 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleDownRight1", imageName, idleDownRight1, 1, TURRETFPS, true);
	int idleDownRight2[] = { 57 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleDownRight2", imageName, idleDownRight2, 1, TURRETFPS, true);
	int idleDownRight3[] = { 66 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleDownRight3", imageName, idleDownRight3, 1, TURRETFPS, true);
	int idleDown[] = { 75 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleDown", imageName, idleDown, 1, TURRETFPS, true);
	int attackUp[] = { 4, 5, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackUp", imageName, attackUp, 2, TURRETFPS, false);
	int attackUpRight1[] = { 13, 14, 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackUpRight1", imageName, attackUpRight1, 2, TURRETFPS, false);
	int attackUpRight2[] = { 22 , 23, 21 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackUpRight2", imageName, attackUpRight2, 2, TURRETFPS, false);
	int attackUpRight3[] = { 31, 32, 30 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackUpRight3", imageName, attackUpRight3, 2, TURRETFPS, false);
	int attackRight[] = { 40, 41, 39 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackRight", imageName, attackRight, 2 , TURRETFPS, false);
	int attackDownRight1[] = { 49, 50, 48 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackDownRight1", imageName, attackDownRight1, 2, TURRETFPS, false);
	int attackDownRight2[] = { 58, 59, 57 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackDownRight2", imageName, attackDownRight2, 2, TURRETFPS, false);
	int attackDownRight3[] = { 67, 68, 66 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackDownRight3", imageName, attackDownRight3, 2, TURRETFPS, false);
	int attackDown[] = { 76, 77, 75 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackDown", imageName, attackDown, 2, TURRETFPS, false);


	_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDown");

	return S_OK;
}

void turret::release()
{
}

void turret::update(float playerX, float playerY)
{
	enemy::update();

	turretState((int)(getAngle2(playerX, playerY, _enemy.x, _enemy.y) * (180 / PI)));
	_enemy.angle = getAngle2(playerX, playerY, _enemy.x, _enemy.y) * (180 / PI);
	_enemy.rc = { (float)_enemy.x + 15, (float)_enemy.y + 10, (float)_enemy.x + _enemy.image->GetFrameWidth() - 15, (float)_enemy.y + _enemy.image->GetFrameHeight() - 10 };
	_enemy.rangeRc = { (float)_enemy.x - 230, (float)_enemy.y - 230, (float)_enemy.x + 250, (float)_enemy.y + 250 };
}

void turret::render(float alpha)
{
	if (_enemy.isRight)
	{
		_enemy.image->aniRender(_enemy.x, _enemy.y, _enemy.ani, alpha);
	}
	else
	{
		_enemy.image->aniRenderReverseX(_enemy.x, _enemy.y, _enemy.ani, alpha);
	}

	//D2DMANAGER->drawRectangle(_enemy.rangeRc);
	//WCHAR str[128];
	//swprintf_s(str, L"%f", _enemy.angle);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 600, CAMERA->getCameraY() + 120, 20, RGB(255, 255, 255));
}

void turret::turretState(float angle)
{
	switch (_enemy.state)
	{
	case ENEMYSTATE::TURRET_IDLE:
		if ((int)(angle / 22.5f) == 0)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleRight");
		}
		else if ((int)(angle / 22.5f) == 1)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight3");
		}
		else if ((int)(angle / 22.5f) == 2)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight2");
		}
		else if ((int)(angle / 22.5f) == 3)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight1");
		}
		else if ((int)(angle / 22.5f) == 4)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUp");
		}
		else if ((int)(angle / 22.5f) == 5)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight1");
		}
		else if ((int)(angle / 22.5f) == 6)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight2");
		}
		else if ((int)(angle / 22.5f) == 7)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight3");
		}
		else if ((int)(angle / 22.5f) == 8)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleRight");
		}
		else if ((int)(angle / 22.5f) == 9)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight1");
		}
		else if ((int)(angle / 22.5f) == 10)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight2");
		}
		else if ((int)(angle / 22.5f) == 11)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight3");
		}
		else if ((int)(angle / 22.5f) == 12)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDown");
		}
		else if ((int)(angle / 22.5f) == 13)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight3");
		}
		else if ((int)(angle / 22.5f) == 14)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight2");
		}		
		else if ((int)(angle / 22.5f) == 15)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight1");
		}
		_enemy.ani->start(false);
		break;
	case ENEMYSTATE::TURRET_ATTACK:
		if ((int)(angle / 22.5f) == 0)
		{
		_enemy.isRight = false;
		_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackRight");
		}
		else if ((int)(angle / 22.5f) == 1)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUpRight3");
		}
		else if ((int)(angle / 22.5f) == 2)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUpRight2");
		}
		else if ((int)(angle / 22.5f) == 3)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUpRight1");
		}
		else if ((int)(angle / 22.5f) == 4)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUp");
		}
		else if ((int)(angle / 22.5f) == 5)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUpRight1");
		}
		else if ((int)(angle / 22.5f) == 6)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUpRight2");
		}
		else if ((int)(angle / 22.5f) == 7)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUpRight3");
		}
		else if ((int)(angle / 22.5f) == 8)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackRight");
		}
		else if ((int)(angle / 22.5f) == 9)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackDownRight1");
		}
		else if ((int)(angle / 22.5f) == 10)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackDownRight2");
		}
		else if ((int)(angle / 22.5f) == 11)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackDownRight3");
		}
		else if ((int)(angle / 22.5f) == 12)
		{
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackDown");
		}
		else if ((int)(angle / 22.5f) == 13)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackDownRight3");
		}
		else if ((int)(angle / 22.5f) == 14)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackDownRight2");
		}
		else if ((int)(angle / 22.5f) == 15)
		{
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackDownRight1");
		}
		_enemy.ani->start(true);
		break;
	}
}
