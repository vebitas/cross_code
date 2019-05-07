#include "stdafx.h"
#include "hedgehog.h"


hedgehog::hedgehog()
{
}


hedgehog::~hedgehog()
{
}

HRESULT hedgehog::init(string enemyName, const char * imageName, float x, float y, int idX, int idY)
{
	enemy::init(enemyName, imageName, x, y, idX, idY);

	_enemy.name = enemyName;
	_enemy.state = ENEMYSTATE::HOG_IDLE;
	_enemy.direction = ENEMYDIRECTION::HOG_DOWN_RIGHT;
	_enemy.alpha = 1;
	_enemy.speed = 1.0f;
	_enemy.isAttack = false;
	_enemy.HP = 200;
	_alpha = 0;
	_count = 0;

	int idleUpRight[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleUpRight", imageName, idleUpRight, 4, ENEMYFPS, true);
	int idleRight[] = { 10, 11, 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleRight", imageName, idleRight, 4, ENEMYFPS, true);
	int idleDownRight[] = { 20, 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleDownRight", imageName, idleDownRight, 4, ENEMYFPS, true);
	int moveUpRight[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "moveUpRight", imageName, moveUpRight, 4, ENEMYFPS, true);
	int moveRight[] = { 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "moveRight", imageName, moveRight, 4, ENEMYFPS, true);
	int moveDownRight[] = { 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "moveDownRight", imageName, moveDownRight, 4, ENEMYFPS, true);
	int attackUD[] = { 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackUD", imageName, attackUD, 2, ENEMYFPS + 5, true);
	int attackRL[] = { 32, 33 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackRL", imageName, attackRL, 2, ENEMYFPS + 5, true);
	int attackedUpRight[] = { 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackedUpRight", imageName, attackedUpRight, 2, ENEMYFPS, true);
	int attackedRight[] = { 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackedRight", imageName, attackedRight, 2, ENEMYFPS, true);
	int attackedDownRight[] = { 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackedDownRight", imageName, attackedDownRight, 2, ENEMYFPS, true);

	_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight");

	return S_OK;
}

void hedgehog::release()
{
}

void hedgehog::update()
{
	enemy::update();

	if (_enemy.HP <= 199)
	{
		_enemy.isAttack = true;
	}
	hogState();
	_enemy.rc = { (float)_enemy.x + 15, (float)_enemy.y + 10, (float)_enemy.x + _enemy.image->GetFrameWidth() - 15, (float)_enemy.y + _enemy.image->GetFrameHeight() - 10 };
}

void hedgehog::render(float alpha)
{
	if (_enemy.isRight)
	{
		_enemy.image->aniRender(_enemy.x, _enemy.y, _enemy.ani, alpha + _alpha);
	}
	else
	{
		_enemy.image->aniRenderReverseX(_enemy.x, _enemy.y, _enemy.ani, alpha + _alpha);
	}



	//D2DMANAGER->drawRectangle(_enemy.rc);
	//WCHAR str[128];
	//swprintf_s(str, L"에너미 체력 : %d", _enemy.HP);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 300, CAMERA->getCameraY() + 20, 20, RGB(255, 255, 255));
}

void hedgehog::hogState()
{
	switch (_enemy.state)
	{
	case ENEMYSTATE::HOG_IDLE:
		_alpha = 0;
		_enemy.speed = 0;
		switch (_enemy.direction)
		{
		case ENEMYDIRECTION::HOG_UP_RIGHT:
			_enemy.isRight = true;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight");
			break;
		case ENEMYDIRECTION::HOG_RIGHT:
			_enemy.isRight = true;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleRight");
			break;
		case ENEMYDIRECTION::HOG_DOWN_RIGHT:
			_enemy.isRight = true;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight");
			break;
		case ENEMYDIRECTION::HOG_UP_LEFT:
			_enemy.isRight = false;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight");
			break;
		case ENEMYDIRECTION::HOG_LEFT:
			_enemy.isRight = false;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleRight");
			break;
		case ENEMYDIRECTION::HOG_DOWN_LEFT:
			_enemy.isRight = false;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight");
			break;
		}
		_enemy.ani->start(false);
		break;
	case ENEMYSTATE::HOG_MOVE:
		_alpha = 0;
		_enemy.speed = 1.0f;
		switch (_enemy.direction)
		{
		case ENEMYDIRECTION::HOG_UP_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 45);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveUpRight");
			break;
		case ENEMYDIRECTION::HOG_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 0);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveRight");
			break;
		case ENEMYDIRECTION::HOG_DOWN_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 315);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveDownRight");
			break;
		case ENEMYDIRECTION::HOG_UP_LEFT:
			_enemy.isRight = false;
			_enemy.angle = (PI / 180 * 135);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveUpRight");
			break;
		case ENEMYDIRECTION::HOG_LEFT:
			_enemy.isRight = false;
			_enemy.angle = (PI / 180 * 180);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveRight");
			break;
		case ENEMYDIRECTION::HOG_DOWN_LEFT:
			_enemy.isRight = false;
			_enemy.angle = (PI / 180 * 225);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveDownRight");
			break;
		}
		_enemy.x += cos(_enemy.angle) * _enemy.speed;
		_enemy.y += -sin(_enemy.angle) * _enemy.speed;
		_enemy.ani->start(false);
		break;
	case ENEMYSTATE::HOG_ATTACK:
		_alpha = 0;
		switch (_enemy.direction)
		{
		case ENEMYDIRECTION::HOG_UP_RIGHT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUD");
			break;
		case ENEMYDIRECTION::HOG_RIGHT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackRL");
			break;
		case ENEMYDIRECTION::HOG_DOWN_RIGHT:
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUD");
			break;
		case ENEMYDIRECTION::HOG_UP_LEFT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUD");
			break;
		case ENEMYDIRECTION::HOG_LEFT:
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackRL");
			break;
		case ENEMYDIRECTION::HOG_DOWN_LEFT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUD");
			break;
		}
		_enemy.x += -cos(_enemy.angle) * _enemy.speed;
		_enemy.y += -sin(_enemy.angle) * _enemy.speed;
		_enemy.ani->start(false);
		break;
	case ENEMYSTATE::HOG_ATTACKED:
		_enemy.speed = 1.0f;
		if (_count % 2 == 0)
		{
			_alpha = -0.2;
		}
		else if(_count % 2 == 1)
		{
			_alpha = -0.5;
		}
		_count++;

		switch (_enemy.direction)
		{
		case ENEMYDIRECTION::HOG_UP_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 225);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedUpRight");
			break;
		case ENEMYDIRECTION::HOG_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 180);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedRight");
			break;
		case ENEMYDIRECTION::HOG_DOWN_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 135);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedDownRight");
			break;
		case ENEMYDIRECTION::HOG_UP_LEFT:
			_enemy.isRight = false;
			_enemy.angle = (PI / 180 * 315);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedUpRight");
			break;
		case ENEMYDIRECTION::HOG_LEFT:
			_enemy.angle = (PI / 180 * 0);
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedRight");
			break;
		case ENEMYDIRECTION::HOG_DOWN_LEFT:
			_enemy.angle = (PI / 180 * 45);
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedDownRight");
			break;
		}
		_enemy.x += cos(_enemy.angle) * (_enemy.speed - 0.5f);
		_enemy.y += -sin(_enemy.angle) * (_enemy.speed - 0.5f);
		_enemy.ani->start(false);
		break;
	}
}