#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	
	_hogDirctionPatten = _hogStatePatten = _hogOldTime = _randNum = 0;
	_hogAttack = false;
	setHedgehog();
	return S_OK;
}

void enemyManager::release()
{
	for (_viShredder = _vShredder.begin(); _viShredder != _vShredder.end(); _viShredder++)
	{
		SAFE_DELETE((*_viShredder));
	}
	for (_viHedgehog = _vHedgehog.begin(); _viHedgehog != _vHedgehog.end(); _viHedgehog++)
	{
		SAFE_DELETE((*_viHedgehog));
	}
}

void enemyManager::update()
{
	for (_viShredder = _vShredder.begin(); _viShredder != _vShredder.end(); _viShredder++)
	{
		(*_viShredder)->update();
	}
	for (_viHedgehog = _vHedgehog.begin(); _viHedgehog != _vHedgehog.end(); _viHedgehog++)
	{
		(*_viHedgehog)->update();

	}
	enemyDeath();
}

void enemyManager::render(float alpha)
{
	for (_viShredder = _vShredder.begin(); _viShredder != _vShredder.end(); _viShredder++)
	{
		(*_viShredder)->render();
	}
	for (_viHedgehog = _vHedgehog.begin(); _viHedgehog != _vHedgehog.end(); _viHedgehog++)
	{
		(*_viHedgehog)->render(alpha);
		WCHAR str[128];
		swprintf_s(str, L"죽음상태 : %d", (*_viHedgehog)->getEnemyDeath());
		D2DMANAGER->drawText(str, CAMERA->getCameraX() + 100, CAMERA->getCameraY() + 200, 20, RGB(0, 0, 0));
	
	}
}

void enemyManager::setHedgehog()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			hedgehog* hog;
			hog = new hedgehog;

			hog->init("hog", "hog", 475 + (j * 400), 250 + (i * 100), 0, 0);
			_vHedgehog.push_back(hog);
		}
	}
}

void enemyManager::hogAI(float playerX, float playerY)
{
	if (GetTickCount() - _hogOldTime >= 1 * 500)
	{
		for (int i = 0; i < _vHedgehog.size(); i++)
		{
			if (_vHedgehog[i]->getEnemyIsAttack() == false)								//공격상태가 아닐때 AI
			{
				if (!(_vHedgehog[i]->getEnemyState() == ENEMYSTATE::HOG_ATTACKED))		//맞고있는중이 아닐때만 실행 
				{
					_hogStatePatten = RND->getFromIntTo(0, 3);
					_hogDirctionPatten = RND->getFromIntTo(0, 6);
					_randNum = RND->getFromIntTo(0, 2);
					_hogOldTime = GetTickCount();

					if (_randNum && _vHedgehog[i]->getEnemyIsAttack() == false)
					{
						switch (_hogStatePatten)
						{
						case 0:
							_vHedgehog[i]->setEnemyState(ENEMYSTATE::HOG_IDLE);
							switch (_hogDirctionPatten)
							{
							case 0:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_UP_RIGHT);
								break;
							case 1:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_RIGHT);
								break;
							case 2:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_DOWN_RIGHT);
								break;
							case 3:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_UP_LEFT);
								break;
							case 4:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_LEFT);
								break;
							case 5:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_DOWN_LEFT);
								break;
							}
							break;
						case 1:
							_vHedgehog[i]->setEnemyState(ENEMYSTATE::HOG_IDLE);
							break;
						case 2:
							_vHedgehog[i]->setEnemyState(ENEMYSTATE::HOG_MOVE);
							switch (_hogDirctionPatten)
							{
							case 0:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_UP_RIGHT);
								break;
							case 1:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_RIGHT);
								break;
							case 2:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_DOWN_RIGHT);
								break;
							case 3:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_UP_LEFT);
								break;
							case 4:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_LEFT);
								break;
							case 5:
								_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_DOWN_LEFT);
								break;
							}
							break;
						}
					}
				}
				else
				{
					if (GetTickCount() - _hogAttatedTime >= 1 * 500)
					{
						_vHedgehog[i]->setEnemyState(ENEMYSTATE::HOG_IDLE);
						_hogAttatedTime = GetTickCount();
						_vHedgehog[i]->setEnemyIsAttack(true);
						_hogAttackTime = GetTickCount();
					}
				}
			}
			else
			{
				if (!(_vHedgehog[i]->getEnemyState() == ENEMYSTATE::HOG_ATTACK) && !(_vHedgehog[i]->getEnemyState() == ENEMYSTATE::HOG_ATTACKED))
				{
					_vHedgehog[i]->setEnemyAngle((getAngle2(playerX, playerY, _vHedgehog[i]->getEnemyPosX(), _vHedgehog[i]->getEnemyPosY())));

					if ((int)_vHedgehog[i]->getEnemyAngle() % 60 == 0)
					{
						_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_LEFT);
					}
					else if ((int)_vHedgehog[i]->getEnemyAngle() % 60 == 1)
					{
						_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_UP_LEFT);
					}
					else if ((int)_vHedgehog[i]->getEnemyAngle() % 60 == 2)
					{
						_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_UP_RIGHT);
					}
					else if ((int)_vHedgehog[i]->getEnemyAngle() % 60 == 3)
					{
						_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_RIGHT);
					}
					else if ((int)_vHedgehog[i]->getEnemyAngle() % 60 == 4)
					{
						_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_DOWN_RIGHT);
					}
					else if ((int)_vHedgehog[i]->getEnemyAngle() % 60 == 5)
					{
						_vHedgehog[i]->setEnemyDirection(ENEMYDIRECTION::HOG_DOWN_LEFT);
					}

					_vHedgehog[i]->setEnemyState(ENEMYSTATE::HOG_IDLE);
					if (GetTickCount() - _hogAttackTime >= 1 * 500)
					{
						_vHedgehog[i]->setEnemyState(ENEMYSTATE::HOG_ATTACK);
						_hogAttackTime = GetTickCount();
					}
				}
				else
				{

					if (GetTickCount() - _hogAttatedTime >= 1 * 300 && !(_vHedgehog[i]->getEnemyState() == ENEMYSTATE::HOG_ATTACK))
					{
						_vHedgehog[i]->setEnemyState(ENEMYSTATE::HOG_IDLE);
						_hogAttatedTime = GetTickCount();
						_vHedgehog[i]->setEnemyIsAttack(true);
						_hogAttackTime = GetTickCount();
					}

					if (!_hogAttack)
					{
						if (GetTickCount() - _hogAttackTime >= 1 * 1500 && _vHedgehog[i]->getEnemySpeed() == 0)
						{
							_vHedgehog[i]->setEnemyAngle((getAngle2(playerX, playerY, _vHedgehog[i]->getEnemyPosX(), _vHedgehog[i]->getEnemyPosY())));
							_hogAttack = true;
							_hogAttackTime = GetTickCount();
							_vHedgehog[i]->setEnemySpeed(0);
						}
					}
					else
					{
						_vHedgehog[i]->setEnemySpeed(10);
					}
				}
			}
		}
	}
}

void enemyManager::enemyDeath()
{
	for (int i = 0; i < _vHedgehog.size();)
	{
		if (_vHedgehog[i]->getEnemyHP() <= 0)
		{
			EFFECTMANAGER->play("deadEff", _vHedgehog[i]->getEnemyPosX() + 30, _vHedgehog[i]->getEnemyPosY() + 10);
			_vHedgehog.erase(_vHedgehog.begin() + i);
		}
		else
		{
			i++;
		}
	}
}
