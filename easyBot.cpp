#include "stdafx.h"
#include "easyBot.h"


easyBot::easyBot()
{
}


easyBot::~easyBot()
{
}

HRESULT easyBot::init(string enemyName, const char * imageName, float x, float y, int idX, int idY)
{
	enemy::init(enemyName, imageName, x, y, idX, idY);

	_enemy.name = enemyName;
	_enemy.state = ENEMYSTATE::BOT_IDLE;
	_enemy.direction = ENEMYDIRECTION::BOT_DOWN_RIGHT;
	_enemy.alpha = 1;
	_enemy.speed = 1.0f;
	_enemy.isAttack = false;
	_enemy.HP = 50;
	_enemy.rangeRc = { (float)_enemy.x, (float)_enemy.y, (float)_enemy.x + 100, (float)_enemy.y + 100 };

	int idleUpRight[] = {0};
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleUpRight", imageName, idleUpRight, 1, EASYBOTFPS, true);
	int idleRight[] = {11};
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleRight", imageName, idleRight, 1, EASYBOTFPS, true);
	int idleDownRight[] = {22};
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleDownRight", imageName, idleDownRight, 1, EASYBOTFPS, true);
	int moveUpRight[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "moveUpRight", imageName, moveUpRight, 3, EASYBOTFPS, true);
	int moveRight[] = { 11, 12, 13};														  
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "moveRight", imageName, moveRight, 3, EASYBOTFPS, true);
	int moveDownRight[] = { 22, 23, 24};													  
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "moveDownRight", imageName, moveDownRight, 3, EASYBOTFPS, true);
	int redModeUpRight[] = { 3, 4, 5};
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "redModeUpRight", imageName, redModeUpRight, 3, EASYBOTFPS - 2, false);
	int redModeRight[] = { 14, 15, 16};
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "redModeRight", imageName, redModeRight, 3, EASYBOTFPS - 2, false);
	int redModeDownRight[] = {25, 26, 27};
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "redModeDownRight", imageName, redModeDownRight, 3, EASYBOTFPS - 2, false);
	int attackUpRight[] = { 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackUpRight", imageName, attackUpRight, 3, EASYBOTFPS + 8, true);
	int attackRight[] = { 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackRight", imageName, attackRight, 3, EASYBOTFPS + 8, true);
	int attackDownRight[] = { 28, 29, 30 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackDownRight", imageName, attackDownRight, 3, EASYBOTFPS + 8, true);
	int attackedUpRight[] = { 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackedUpRight", imageName, attackedUpRight, 2, EASYBOTFPS, true);
	int attackedRight[] = { 20, 21 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackedRight", imageName, attackedRight, 2, EASYBOTFPS, true);
	int attackedDownRight[] = { 31, 32 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "attackedDownRight", imageName, attackedDownRight, 2, EASYBOTFPS, true);

	_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight");

	return S_OK;
}

void easyBot::release()
{
}

void easyBot::update()
{
	enemy::update();

	easyBotStage();
	_enemy.rangeRc = { (float)_enemy.x - 100, (float)_enemy.y - 100, (float)_enemy.x + 160, (float)_enemy.y + 160 };
	_enemy.rc = { (float)_enemy.x + 15, (float)_enemy.y + 10, (float)_enemy.x + _enemy.image->GetFrameWidth() - 15, (float)_enemy.y + _enemy.image->GetFrameHeight() - 10 };
}

void easyBot::render(float alpha)
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
}

void easyBot::easyBotStage()
{
	switch (_enemy.state)
	{
	case ENEMYSTATE::BOT_IDLE:
		_enemy.speed = 0;
		switch (_enemy.direction)
		{
		case ENEMYDIRECTION::BOT_UP_RIGHT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight");
			break;
		case ENEMYDIRECTION::BOT_RIGHT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_RIGHT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight");
			break;
		case ENEMYDIRECTION::BOT_UP_LEFT:
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleUpRight");
			break;
		case ENEMYDIRECTION::BOT_LEFT:
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_LEFT:
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "idleDownRight");
			break;
		}
		_enemy.ani->start(false);
		break;
	case ENEMYSTATE::BOT_MOVE:
		_enemy.speed = 1.0f;
		switch (_enemy.direction)
		{
		case ENEMYDIRECTION::BOT_UP_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 45);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveUpRight");
			break;
		case ENEMYDIRECTION::BOT_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 0);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 315);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveDownRight");
			break;
		case ENEMYDIRECTION::BOT_UP_LEFT:
			_enemy.isRight = false;
			_enemy.angle = (PI / 180 * 135);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveUpRight");
			break;
		case ENEMYDIRECTION::BOT_LEFT:
			_enemy.isRight = false;
			_enemy.angle = (PI / 180 * 180);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_LEFT:
			_enemy.isRight = false;
			_enemy.angle = (PI / 180 * 225);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "moveDownRight");
			break;
		}
		_enemy.x += cos(_enemy.angle) * _enemy.speed;
		_enemy.y += -sin(_enemy.angle) * _enemy.speed;
		_enemy.ani->start(false);
		break;
	case ENEMYSTATE::BOT_RED_MODE:
		_enemy.speed = 0;
		switch (_enemy.direction)
		{
		case ENEMYDIRECTION::BOT_UP_RIGHT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "redModeUpRight");
			break;
		case ENEMYDIRECTION::BOT_RIGHT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "redModeRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_RIGHT:
			_enemy.isRight = true;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "redModeDownRight");
			break;
		case ENEMYDIRECTION::BOT_UP_LEFT:
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "redModeUpRight");
			break;
		case ENEMYDIRECTION::BOT_LEFT:
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "redModeRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_LEFT:
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "redModeDownRight");
			break;
		}
		_enemy.ani->start(false);
		break;
	case ENEMYSTATE::BOT_ATTACK:
		_enemy.speed = 2.0f;
		switch (_enemy.direction)
		{
		case ENEMYDIRECTION::BOT_UP_RIGHT:
			_enemy.isRight = true;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUpRight");
			break;
		case ENEMYDIRECTION::BOT_RIGHT:
			_enemy.isRight = true;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_RIGHT:
			_enemy.isRight = true;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackDownRight");
			break;
		case ENEMYDIRECTION::BOT_UP_LEFT:
			_enemy.isRight = false;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackUpRight");
			break;
		case ENEMYDIRECTION::BOT_LEFT:
			_enemy.isRight = false;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_LEFT:
			_enemy.isRight = false;

			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackDownRight");
			break;
		}
		_enemy.ani->start(false);
		_enemy.x += cos(_enemy.angle) * _enemy.speed;
		_enemy.y += sin(_enemy.angle) * _enemy.speed;
		break;
	case ENEMYSTATE::BOT_ATTACKED:
		_enemy.speed = 0.3f;
		if (_count % 2 == 0)
		{
			_alpha = -0.2;
		}
		else if (_count % 2 == 1)
		{
			_alpha = -0.5;
		}
		_count++;

		switch (_enemy.direction)
		{
		case ENEMYDIRECTION::BOT_UP_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 225);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedUpRight");
			break;
		case ENEMYDIRECTION::BOT_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 180);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_RIGHT:
			_enemy.isRight = true;
			_enemy.angle = (PI / 180 * 135);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedDownRight");
			break;
		case ENEMYDIRECTION::BOT_UP_LEFT:
			_enemy.isRight = false;
			_enemy.angle = (PI / 180 * 315);
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedUpRight");
			break;
		case ENEMYDIRECTION::BOT_LEFT:
			_enemy.angle = (PI / 180 * 0);
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedRight");
			break;
		case ENEMYDIRECTION::BOT_DOWN_LEFT:
			_enemy.angle = (PI / 180 * 45);
			_enemy.isRight = false;
			_enemy.ani = KEYANIMANAGER->findAnimation(_enemy.name, "attackedDownRight");
			break;
		}
		_enemy.x += cos(_enemy.angle) * _enemy.speed;
		_enemy.y += -sin(_enemy.angle) * _enemy.speed;
		_enemy.ani->start(false);
		break;
	}
}
