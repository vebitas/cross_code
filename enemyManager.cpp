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
	_turretBullet = new turretBullet;
	_turretBullet->init("turretBullet", 600, 200);
	_hogDirctionPatten = _hogStatePatten = _hogOldTime = _randNum = 0;
	
	_botOldTime[0] = _botDirctionPatten = _botStatePatten = 0;
	_botOldTime[1] = _botOldTime[2] = 0;
	_hogAttack = false;

	_tretRandNum = 0;

	return S_OK;
}

void enemyManager::release()
{
	for (_viTurret = _vTurret.begin(); _viTurret != _vTurret.end(); _viTurret++)
	{
		SAFE_DELETE((*_viTurret));
	}
	for (_viHedgehog = _vHedgehog.begin(); _viHedgehog != _vHedgehog.end(); _viHedgehog++)
	{
		SAFE_DELETE((*_viHedgehog));
	}
	for (_viEasyBot = _vEasyBot.begin(); _viEasyBot != _vEasyBot.end(); _viEasyBot++)
	{
		SAFE_DELETE((*_viEasyBot));
	}
	SAFE_DELETE(_turretBullet);
}

void enemyManager::update(float playerX, float playerY)
{
	for (_viTurret = _vTurret.begin(); _viTurret != _vTurret.end(); _viTurret++)
	{
		(*_viTurret)->update(playerX, playerY);
	}
	for (_viHedgehog = _vHedgehog.begin(); _viHedgehog != _vHedgehog.end(); _viHedgehog++)
	{
		(*_viHedgehog)->update();
	}
	for (_viEasyBot = _vEasyBot.begin(); _viEasyBot != _vEasyBot.end(); _viEasyBot++)
	{
		(*_viEasyBot)->update();
	}
	enemyDeath();
	_turretBullet->update();
}

void enemyManager::render(float alpha)
{
	for (_viTurret = _vTurret.begin(); _viTurret != _vTurret.end(); _viTurret++)
	{
		(*_viTurret)->render(alpha);
	}
	for (_viHedgehog = _vHedgehog.begin(); _viHedgehog != _vHedgehog.end(); _viHedgehog++)
	{
		(*_viHedgehog)->render(alpha);
	}
	for (_viEasyBot = _vEasyBot.begin(); _viEasyBot != _vEasyBot.end(); _viEasyBot++)
	{
		(*_viEasyBot)->render(alpha);
	}
	_turretBullet->render();
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

void enemyManager::setEasyBot()
{
	easyBot* bot;
	bot = new easyBot;

	bot->init("easyBot", "easyBot", 200 , 200, 0, 0);
	_vEasyBot.push_back(bot);
	
	easyBot* bot2;
	bot2 = new easyBot;

	bot2->init("easyBot", "easyBot", 350, 800, 0, 0);
	_vEasyBot.push_back(bot2);

	easyBot* bot3;
	bot3 = new easyBot;

	bot3->init("easyBot", "easyBot", 600, 500, 0, 0);
	_vEasyBot.push_back(bot3);

}

void enemyManager::setTurret()
{
	for (int i = 0; i < 3; i++)
	{
		turret* tret;
		tret = new turret;
		tret->init("turret", "turret", 860 + (i * 150), 250, 0, 0);
		_vTurret.push_back(tret);
	}
	
	for (int i = 0; i < 2; i++)
	{
		turret* tret;
		tret = new turret;
		tret->init("turret", "turret", 1200 + (i * 150), 650, 0, 0);
		_vTurret.push_back(tret);
	}
	for (int i = 0; i < 2; i++)
	{
		turret* tret;
		tret = new turret;
		tret->init("turret", "turret", 850 + (i * 150), 850, 0, 0);
		_vTurret.push_back(tret);
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

void enemyManager::esayBotAI(float playerX, float playerY, D2D1_RECT_F playerRc)
{
	
	for (int i = 0; i < _vEasyBot.size(); i++)
	{
		RECT rc;
		if(IntersectRect(&rc, &makeRECT(_vEasyBot[i]->getEnemyRangeRc()), &makeRECT(playerRc)))
		{
			if (!(_vEasyBot[i]->getEnemyState() == ENEMYSTATE::BOT_ATTACKED))
			{
				_vEasyBot[i]->setEnemyState(ENEMYSTATE::BOT_RED_MODE);
				if (GetTickCount() - _botAttackTime[i] >= 1 * 300)
				{
					_vEasyBot[i]->setEnemyState(ENEMYSTATE::BOT_ATTACK);
					_vEasyBot[i]->setEnemyAngle(getAngle2(_vEasyBot[i]->getEnemyPosX(), _vEasyBot[i]->getEnemyPosY(), playerX, playerY));
				}
			}
		}
		else 
		{
			if (GetTickCount() - _botOldTime[i] >= 1 * 500)
			{
				if (!(_vEasyBot[i]->getEnemyState() == ENEMYSTATE::BOT_ATTACKED))
				{
					_botStatePatten = RND->getFromIntTo(0, 3);
					_botDirctionPatten = RND->getFromIntTo(0, 6);
					_botOldTime[i] = GetTickCount();

					if (_vEasyBot[i]->getEnemyIsAttack() == false)
					{
						switch (_botStatePatten)
						{
						case 0:
							_vEasyBot[i]->setEnemyState(ENEMYSTATE::BOT_IDLE);
							switch (_botDirctionPatten)
							{
							case 0:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_UP_RIGHT);
								break;
							case 1:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_RIGHT);
								break;
							case 2:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_DOWN_RIGHT);
								break;
							case 3:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_UP_LEFT);
								break;
							case 4:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_LEFT);
								break;
							case 5:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_DOWN_LEFT);
								break;
							}
							break;
						case 1:
							_vEasyBot[i]->setEnemyState(ENEMYSTATE::BOT_MOVE);
							switch (_botDirctionPatten)
							{
							case 0:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_UP_RIGHT);
								break;
							case 1:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_RIGHT);
								break;
							case 2:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_DOWN_RIGHT);
								break;
							case 3:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_UP_LEFT);
								break;
							case 4:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_LEFT);
								break;
							case 5:
								_vEasyBot[i]->setEnemyDirection(ENEMYDIRECTION::BOT_DOWN_LEFT);
								break;
							}
							break;
						}
					}
					
				}
			}
			_botAttackTime[i] = GetTickCount();
		}
		if (GetTickCount() - _botAttatedTime >= 300)
		{
			if (_vEasyBot[i]->getEnemyState() == ENEMYSTATE::BOT_ATTACKED)
			{
				_vEasyBot[i]->setEnemyState(ENEMYSTATE::BOT_IDLE);
				_botAttatedTime = GetTickCount();
				_botAttackTime[i] = GetTickCount();
			}
		}
	}
	
}

void enemyManager::turretAI(float playerX, float playerY, D2D1_RECT_F playerRc)
{
	RECT rc;
	for (int i = 0; i < _vTurret.size(); i++)
	{
		if (IntersectRect(&rc, &makeRECT(_vTurret[i]->getEnemyRangeRc()), &makeRECT(playerRc)))
		{
			_tretRandNum = RND->getFromIntTo(0, 3);
			if (GetTickCount() - _tretAttackTime[i] >= 500)
			{
				_tretAttackTime[i] = GetTickCount();
				if (!(_tretRandNum == 0))
				{
					if (!(_vTurret[i]->getEnemyState() == ENEMYSTATE::TURRET_ATTACK))
					{
						_vTurret[i]->setEnemyState(ENEMYSTATE::TURRET_ATTACK);
						_turretBullet->bulletFire(_vTurret[i]->getEnemyRc().left + 2, _vTurret[i]->getEnemyRc().top + 2, getAngle2(playerX, playerY, _vTurret[i]->getEnemyPosX(), _vTurret[i]->getEnemyPosY()), 10.0f);
					}
					else
					{
						_vTurret[i]->setEnemyState(ENEMYSTATE::TURRET_IDLE);
					}
				}
			}
		}
		else
		{
			_vTurret[i]->setEnemyState(ENEMYSTATE::TURRET_IDLE);
		}
	}
	
}


void enemyManager::enemyDeath()
{
	for (int i = 0; i < _vTurret.size();)
	{
		if (_vTurret[i]->getEnemyHP() <= 0)
		{
			EFFECTMANAGER->play("deadEff", _vTurret[i]->getEnemyPosX() + 30, _vTurret[i]->getEnemyPosY() + 10);
			SOUNDMANAGER->play("enemyDeath", 1);
			_vTurret.erase(_vTurret.begin() + i);
		}
		else
		{
			i++;
		}
	}
	for (int i = 0; i < _vHedgehog.size();)
	{
		if (_vHedgehog[i]->getEnemyHP() <= 0)
		{
			EFFECTMANAGER->play("deadEff", _vHedgehog[i]->getEnemyPosX() + 30, _vHedgehog[i]->getEnemyPosY() + 10);
			SOUNDMANAGER->play("enemyDeath", 1);
			_vHedgehog.erase(_vHedgehog.begin() + i);
		}
		else
		{
			i++;
		}
	}

	for (int i = 0; i < _vEasyBot.size();)
	{
		if (_vEasyBot[i]->getEnemyHP() <= 0)
		{
			SOUNDMANAGER->play("enemyDeath", 1);
			EFFECTMANAGER->play("deadEff", _vEasyBot[i]->getEnemyPosX() + 30, _vEasyBot[i]->getEnemyPosY() + 10);
			_vEasyBot.erase(_vEasyBot.begin() + i);
		}
		else
		{
			i++;
		}
	}
}
