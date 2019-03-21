#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(string enemyName, const char* imageName, float x, float y, int idX, int idY)
{
	_enemy.name = enemyName;
	_enemy.x = x;
	_enemy.y = y;
	_enemy.idX = idX;
	_enemy.idY = idY;
	_enemy.image = IMAGEMANAGER->findImage(imageName);
	_enemy.death = false;
	_enemy.rc = { (float)x, (float)y, (float)x + _enemy.image->GetFrameWidth() / 2, (float)y + _enemy.image->GetFrameHeight() / 2 };

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	if (_enemy.HP <= 0)
	{
		_enemy.death = true;
	}
	_enemy.rc = { (float)_enemy.x, (float)_enemy.y, (float)_enemy.x + _enemy.image->GetFrameWidth(), (float)_enemy.y + _enemy.image->GetFrameHeight()};
}

void enemy::render()
{
}
