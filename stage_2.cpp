#include "stdafx.h"
#include "stage_2.h"


stage_2::stage_2()
{
}


stage_2::~stage_2()
{
}

HRESULT stage_2::init()
{
	KEYANIMANAGER->deleteAll();
	setWindowsSize(0, 0, GAMESIZEX, GAMESIZEY);
	_stage2 = new stageTwoMap;
	_player = new player;
	_enemyManager = new enemyManager;

	_stage2->init();
	_player->init();
	_player->setPlayerPosX(80);
	_player->setPlayerPosY(845);

	_enemyManager->init();
	_enemyManager->setEasyBot();
	_enemyManager->setTurret();
	_teleportFrameX = 0;
	_switchFrameX = 0;
	_sceneChangeAlpha = 0;
	_botAtttack = false;
	_switchOn = false;
	_botAttackTime = GetTickCount();
	_brricadeAlpha = true;
	_turretAttack = false;
	SOUNDMANAGER->play("cargoHold", 0.8);
	CAMERA->init(GAMESIZEX, GAMESIZEY, TILESIZE * 46, TILESIZE * 34);
	return S_OK;
}

void stage_2::release()
{
	SAFE_DELETE(_stage2);
	SAFE_DELETE(_player);
	SAFE_DELETE(_enemyManager);
}

void stage_2::update()
{
	_stage2->update();
	_player->update();
	_enemyManager->esayBotAI(_player->getPlayerPosX(), _player->getPlayerPosY(), _player->getPlayerRc());
	_enemyManager->update(_player->getPlayerPosX(), _player->getPlayerPosY());
	_enemyManager->turretAI(_player->getPlayerPosX() + 15, _player->getPlayerPosY() + 20, _player->getPlayerRc());
	playerCollision();
	enemyCollision();
	tileCheck();
	easyBotTileCheck();
	_count++;
	if (_count % 8 == 0)
	{
		if (_briFrameX < 8)
			_briFrameX++;
		else
			_briFrameX = 0;

		if (_switchFrameX >= 5 && _brricadeAlpha >= 0 && !_switchOn)
		{
			if (_switchFrameX <= 12)
			{
				_switchFrameX++;
			}
			else
			{
				CAMERA->linearKeepMove(1500, 900, 1, 1);
				_switchOn = true;
			}
		}
	}
	if (_switchOn)
	{
		if (_brricadeAlpha >= 0)
			_brricadeAlpha -= 0.01;
		else
		{
			CAMERA->linearKeepMove(_player->getPlayerPosX(), _player->getPlayerPosY(), 0.5, 0.5);
		}
	}
	

	if (GetTickCount() - _switchTime >=1500)
	{
		if(_switchFrameX < 5 && _switchFrameX > 0)
		_switchFrameX--;
		_switchTime = GetTickCount();
	}

	//CAMERA->linearKeepMove(_player->getPlayerPosX(), _player->getPlayerPosY(), 0.2, 0);
	CAMERA->update(_player->getPlayerPosX(), _player->getPlayerPosY());

	_brricadeRc[0] = { (float)610, (float)150, (float)630, (float)250 };
	_brricadeRc[1] = { (float)1280, (float)800, (float)1410, (float)820 };
	_switchRc = { (float)700, 280, (float)730, (float)310 };
	_teleportRc = { (float)1325, (float)880, (float)1355, (float)910 };

	if (_player->getPlayerState() == PLAYERSTATE::PLAYER_TELEPORT)
	{

		if (_sceneChangeAlpha < 1)
			_sceneChangeAlpha += 0.01;
		else
		{
			SCENEMANAGER->changeScene("bossScene");
		}
	}
}

void stage_2::render()
{
	_stage2->render();
	IMAGEMANAGER->findImage("barricade")->frameRender(610, 150, _briFrameX, 0);
	IMAGEMANAGER->findImage("teleport")->frameRender(75, 850, 1, 0);
	IMAGEMANAGER->findImage("teleport")->frameRender(1305, 860, _teleportFrameX, 0);
	_enemyManager->render(1);
	EFFECTMANAGER->render(0);
	IMAGEMANAGER->findImage("switch")->frameRender(700, 250, _switchFrameX, 0);
	_player->render(false);
	for (int i = 0; i < 7; i++)
	{
		IMAGEMANAGER->findImage("barricade")->frameRender(1280 + (i *20), 700, _briFrameX, 0, _brricadeAlpha);
	}
	IMAGEMANAGER->findImage("sceneChange")->render(0 + CAMERA->getCameraX(), 0 + CAMERA->getCameraY(),  _sceneChangeAlpha);
	D2DMANAGER->drawRectangle(_teleportRc);
	_player->render(true);
	//D2DMANAGER->drawRectangle(_tileCheckRc);
	//D2DMANAGER->drawRectangle(_brricadeRc[0]);
	//D2DMANAGER->drawRectangle(_brricadeRc[1]);

	//for (int i = 0; i < _player->getPlayerBullet()->getVPlayerBullet().size(); i++)
	//{
	//	WCHAR str[128];
	//	swprintf_s(str, L"앵글값 : %f", _player->getPlayerBullet()->getVPlayerBullet()[i].angle);
	//	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 20, 20, RGB(255, 255, 255));
	//}
	
}

void stage_2::tileCheck()
{
	_player->setPlayerIdX(_player->getPlayerPosX() / 32);
	_player->setPlayerIdY(_player->getPlayerPosY() / 32);
	RECT temp;
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_tileIndex[0].x = _player->getPlayerIdX();
		_tileIndex[0].y = _player->getPlayerIdY() + 1;
		if (_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_CONTAINER)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() + _player->getPlayerSpeed());
		}		
	}
	if (_player->getPlayerDirection() == LEFT && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_CONTAINER)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() + _player->getPlayerSpeed());
		}
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_tileIndex[0].x = _player->getPlayerIdX() + 1;
		_tileIndex[0].y = _player->getPlayerIdY() + 1;
		if ((_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_CONTAINER)
			|| IntersectRect(&temp, &makeRECT(_player->getPlayerRc()), &makeRECT(_brricadeRc[0])))
		{
			_player->setPlayerPosX(_player->getPlayerPosX() - _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == RIGHT && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_CONTAINER)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() - _player->getPlayerSpeed());
		}
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_tileIndex[0].x = _player->getPlayerIdX() + 1;
		_tileIndex[0].y = _player->getPlayerIdY() + 1;
		if (_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_CONTAINER)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() + _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == UP && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_CONTAINER)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() + _player->getPlayerSpeed());
		}
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_tileIndex[0].x = _player->getPlayerIdX() + 1;
		_tileIndex[0].y = _player->getPlayerIdY() + 2;
		if ((_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_CONTAINER)
			|| (IntersectRect(&temp, &makeRECT(_player->getPlayerRc()), &makeRECT(_brricadeRc[1])) && _brricadeAlpha == 1))
		{
			_player->setPlayerPosY(_player->getPlayerPosY() - _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == DOWN && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP
			|| _stage2->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_CONTAINER)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() - _player->getPlayerSpeed());
		}
	}

	//_tileCheckRc = { (float)_tileIndex[0].x * TILESIZE ,(float)_tileIndex[0].y * TILESIZE, (float)_tileIndex[0].x * TILESIZE + TILESIZE, (float)_tileIndex[0].y * TILESIZE + TILESIZE };
}

void stage_2::easyBotTileCheck()
{
	for (int i = 0; i < _enemyManager->getVBot().size(); i++)
	{
		(*_enemyManager->setVBot())[i]->setEnemyIdX(_enemyManager->getVBot()[i]->getEnemyPosX() / 32);
		(*_enemyManager->setVBot())[i]->setEnemyIdY(_enemyManager->getVBot()[i]->getEnemyPosY() / 32);

		if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_UP_LEFT)
		{
			_tileIndex[1].x = _enemyManager->getVBot()[i]->getEnemyIdX();
			_tileIndex[1].y = _enemyManager->getVBot()[i]->getEnemyIdY() + 1;
		}
		else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_LEFT)
		{
			_tileIndex[1].x = _enemyManager->getVBot()[i]->getEnemyIdX();
			_tileIndex[1].y = _enemyManager->getVBot()[i]->getEnemyIdY() + 1;
		}
		else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_DOWN_LEFT)
		{
			_tileIndex[1].x = _enemyManager->getVBot()[i]->getEnemyIdX();
			_tileIndex[1].y = _enemyManager->getVBot()[i]->getEnemyIdY() + 1;
		}
		else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_UP_RIGHT)
		{
			_tileIndex[1].x = _enemyManager->getVBot()[i]->getEnemyIdX() + 1;
			_tileIndex[1].y = _enemyManager->getVBot()[i]->getEnemyIdY() + 1;
		}
		else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_RIGHT)
		{
			_tileIndex[1].x = _enemyManager->getVBot()[i]->getEnemyIdX() + 1;
			_tileIndex[1].y = _enemyManager->getVBot()[i]->getEnemyIdY() + 1;
		}
		else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_DOWN_LEFT)
		{
			_tileIndex[1].x = _enemyManager->getVBot()[i]->getEnemyIdX() + 1;
			_tileIndex[1].y = _enemyManager->getVBot()[i]->getEnemyIdY() + 1;
		}

		if (_stage2->getTile(_tileIndex[1].x, _tileIndex[1].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[1].x, _tileIndex[1].y)->getObject() == OBJECT::OBJ_CONTAINER)
		{
			if (_enemyManager->getVBot()[i]->getEnemyState() == ENEMYSTATE::BOT_MOVE)
			{
				if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_UP_LEFT)
				{
					(*_enemyManager->setVBot())[i]->setEnemyAngle(PI / 180 * 315);
				}
				else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_LEFT)
				{
					(*_enemyManager->setVBot())[i]->setEnemyAngle(PI / 180 * 0);
				}
				else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_DOWN_LEFT)
				{
					(*_enemyManager->setVBot())[i]->setEnemyAngle(PI / 180 * 45);
				}
				else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_UP_RIGHT)
				{
					(*_enemyManager->setVBot())[i]->setEnemyAngle(PI / 180 * 225);
				}
				else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_RIGHT)
				{
					(*_enemyManager->setVBot())[i]->setEnemyAngle(PI / 180 * 180);
				}
				else if (_enemyManager->getVBot()[i]->getEnemyDirection() == ENEMYDIRECTION::BOT_DOWN_RIGHT)
				{
					(*_enemyManager->setVBot())[i]->setEnemyAngle(PI / 180 * 135);
				}
				(*_enemyManager->setVBot())[i]->setEnemyPosX(_enemyManager->getVBot()[i]->getEnemyPosX()
					+ (cos(_enemyManager->getVBot()[i]->getEnemyAngle()) * _enemyManager->getVBot()[i]->getEnemySpeed()));
				(*_enemyManager->setVBot())[i]->setEnemyPosY(_enemyManager->getVBot()[i]->getEnemyPosY()
					+ (-sin(_enemyManager->getVBot()[i]->getEnemyAngle()) * _enemyManager->getVBot()[i]->getEnemySpeed()));
			}
			else
			{
				_tileIndex[1].x = _enemyManager->getVBot()[i]->getEnemyIdX() + 1;
				_tileIndex[1].y = _enemyManager->getVBot()[i]->getEnemyIdY() + 1;

				if (_stage2->getTile(_tileIndex[1].x, _tileIndex[1].y)->getObject() == OBJECT::OBJ_LINE ||
					_stage2->getTile(_tileIndex[1].x, _tileIndex[1].y)->getObject() == OBJECT::OBJ_CONTAINER)
				{
					(*_enemyManager->setVBot())[i]->setEnemyAngle(-(getAngle2(_player->getPlayerPosX(), _player->getPlayerPosY(),
						_enemyManager->getVBot()[i]->getEnemyPosX(), _enemyManager->getVBot()[i]->getEnemyPosY())));
					(*_enemyManager->setVBot())[i]->setEnemyPosX(_enemyManager->getVBot()[i]->getEnemyPosX()
						+ (cos(_enemyManager->getVBot()[i]->getEnemyAngle()) * _enemyManager->getVBot()[i]->getEnemySpeed()));
					(*_enemyManager->setVBot())[i]->setEnemyPosY(_enemyManager->getVBot()[i]->getEnemyPosY()
						+ (-sin(_enemyManager->getVBot()[i]->getEnemyAngle()) * _enemyManager->getVBot()[i]->getEnemySpeed()));
				}
			}
		}

	}
	_tileCheckRc = { (float)_tileIndex[1].x * TILESIZE ,(float)_tileIndex[1].y * TILESIZE, (float)_tileIndex[1].x * TILESIZE + TILESIZE, (float)_tileIndex[1].y * TILESIZE + TILESIZE };
}

void stage_2::playerCollision()
{
	if (GetTickCount() - _botAttackTime >= 300)
	{
		_botAtttack = false;
	}

	RECT rc;
	//몬스터 공격 vs 플레이어 충돌
	for (int k = 0; k < _enemyManager->getVBot().size(); k++)
	{
		if (((*_enemyManager->setVBot())[k]->getEnemyState() == ENEMYSTATE::BOT_ATTACK &&
			IntersectRect(&rc, &makeRECT(_enemyManager->getVBot()[k]->getEnemyRc()), &makeRECT(_player->getPlayerRc())))
			&& !(_player->getPlayerState() == PLAYERSTATE::PLAYER_ATTACKED) && !(_player->getPlayerState() == PLAYERSTATE::PLAYER_SKILL_FIRE))
		{
			if (!_botAtttack)
			{
				if (_player->getPlayerState() == PLAYERSTATE::PLAYER_DEFENSE)
				{
					_player->setPlayerHP(_player->getPlayerHP() - 2);
				}
				else
				{
					SOUNDMANAGER->play("playerAttacked", 1);
					_player->setPlayerState(PLAYERSTATE::PLAYER_ATTACKED);
					_player->setPlayerHP(_player->getPlayerHP() - 10);
					_botAtttack = true;
					_botAttackTime = GetTickCount();
					SOUNDMANAGER->play("playerAttacked", 1);
				}
			}
		}
	}
	RECT rc2;
	//터렛 공격 vs 플레이어 충돌
	for (int k = 0; k < _enemyManager->getTurretBullet()->getVTurretBullet().size(); k++)
	{
		if (IntersectRect(&rc2, &makeRECT(_enemyManager->getTurretBullet()->getVTurretBullet()[k].rc), &makeRECT(_player->getPlayerRc()))
			&& !(_player->getPlayerState() == PLAYERSTATE::PLAYER_ATTACKED) && !(_player->getPlayerState() == PLAYERSTATE::PLAYER_SKILL_FIRE))
		{
			if (_player->getPlayerState() == PLAYERSTATE::PLAYER_DEFENSE)
			{
				_player->setPlayerHP(_player->getPlayerHP() - 2);
			

			}
			else
			{
				_player->setPlayerState(PLAYERSTATE::PLAYER_ATTACKED);
				_player->setPlayerHP(_player->getPlayerHP() - 10);
				SOUNDMANAGER->play("playerAttacked", 1);
			}
			_enemyManager->getTurretBullet()->setVTurretBullet()->erase(_enemyManager->getTurretBullet()->setVTurretBullet()->begin() + k);
			EFFECTMANAGER->play("turretBulletE", _player->getPlayerPosX() + 30, _player->getPlayerPosY() + 10);
		}
	}
	//플레이어 총알 vs 오브젝트
	for (int i = 0; i < _player->getPlayerBullet()->getVPlayerBullet().size(); i++)
	{
		(*_player->getPlayerBullet()->setVPlayerBullet())[i].idX = _player->getPlayerBullet()->getVPlayerBullet()[i].x / 32;
		(*_player->getPlayerBullet()->setVPlayerBullet())[i].idY = _player->getPlayerBullet()->getVPlayerBullet()[i].y / 32;

		if (_player->getPlayerBullet()->getVPlayerBullet()[i].angle >= (PI / 180 * 90) && _player->getPlayerBullet()->getVPlayerBullet()[i].angle <= (PI / 180 * 180))
		{
			_tileIndex[2].x = _player->getPlayerBullet()->getVPlayerBullet()[i].idX;
			_tileIndex[2].y = _player->getPlayerBullet()->getVPlayerBullet()[i].idY;
		}

		else
		{
			_tileIndex[2].x = _player->getPlayerBullet()->getVPlayerBullet()[i].idX + 1;
			_tileIndex[2].y = _player->getPlayerBullet()->getVPlayerBullet()[i].idY + 1;
		}

		if (_stage2->getTile(_tileIndex[2].x, _tileIndex[2].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[2].x, _tileIndex[2].y)->getObject() == OBJECT::OBJ_CONTAINER)
		{
			if (_player->getPlayerBullet()->getVPlayerBullet()[i].isPowerBullet == false)
			{
				SOUNDMANAGER->play("throwE_1", 1);
				EFFECTMANAGER->play("ballN_E", _player->getPlayerBullet()->getVPlayerBullet()[i].x + 10, _player->getPlayerBullet()->getVPlayerBullet()[i].y + 10);
				_player->getPlayerBullet()->setVPlayerBullet()->erase(_player->getPlayerBullet()->setVPlayerBullet()->begin() + i);
			}
			else
			{
				if(_player->getPlayerBullet()->getVPlayerBullet()[i].y <= 200 || _player->getPlayerBullet()->getVPlayerBullet()[i].y >= 950)
					(*_player->getPlayerBullet()->setVPlayerBullet())[i].angle = -(_player->getPlayerBullet()->getVPlayerBullet()[i].angle) - (2 * PI);
				else 
				(*_player->getPlayerBullet()->setVPlayerBullet())[i].angle = -(_player->getPlayerBullet()->getVPlayerBullet()[i].angle) - (PI);
				(*_player->getPlayerBullet()->setVPlayerBullet())[i].ballCount = _player->getPlayerBullet()->getVPlayerBullet()[i].ballCount + 1;
			}
		}
	}

	RECT rc4;
	//스위치랑 플레이어 총알 충돌
	for (int i = 0; i < _player->getPlayerBullet()->getVPlayerBullet().size();)
	{
		if (IntersectRect(&rc4, &makeRECT(_switchRc), &makeRECT(_player->getPlayerBullet()->getVPlayerBullet()[i].rc)))
		{
			_switchTime = GetTickCount();
			if (_switchFrameX <= 4)
				_switchFrameX += 1;
			EFFECTMANAGER->play("hit", _player->getPlayerBullet()->getVPlayerBullet()[i].x + 10, _player->getPlayerBullet()->getVPlayerBullet()[i].y + 10);
			_player->getPlayerBullet()->setVPlayerBullet()->erase(_player->getPlayerBullet()->setVPlayerBullet()->begin() + i);
		}
		else i++;
	}
	RECT rc5;
	if (IntersectRect(&rc5, &makeRECT(_teleportRc), &makeRECT(_player->getPlayerRc())) && !(_player->getPlayerState() == PLAYERSTATE::PLAYER_TELEPORT))
	{
		_player->setPlayerState(PLAYERSTATE::PLAYER_TELEPORT);
	}
}

void stage_2::enemyCollision()
{
	if (GetTickCount() - _turretAttackTime >= 400)
	{
		_turretAttack = true;
	}
	RECT rc;
	//몬스터 vs 플레이어 근접 공격 충돌
	for (int i = 0; i < _enemyManager->getVBot().size();)
	{
		if (IntersectRect(&rc, &makeRECT(_enemyManager->getVBot()[i]->getEnemyRc()), &makeRECT(_player->getPlayerAttackRc()))
			&& !((*_enemyManager->setVBot())[i]->getEnemyState() == ENEMYSTATE::BOT_ATTACKED) && _player->getIsAttack() == true)
		{
			(*_enemyManager->setVBot())[i]->setEnemyHP((*_enemyManager->setVBot())[i]->getEnemyHP() - 20);
			(*_enemyManager->setVBot())[i]->setEnemyState(ENEMYSTATE::BOT_ATTACKED);
			EFFECTMANAGER->play("hit", (*_enemyManager->setVBot())[i]->getEnemyPosX() + 35, (*_enemyManager->setVBot())[i]->getEnemyPosY() + 23);
		}
		else i++;
	}

	RECT rc2;
	//몬스터 vs 플레이어 총알 충돌
	for (int i = 0; i < _enemyManager->getVBot().size();)
	{
		for (int j = 0; j < _player->getPlayerBullet()->getVPlayerBullet().size();)
		{
			if (IntersectRect(&rc2, &makeRECT(_enemyManager->getVBot()[i]->getEnemyRc()), &makeRECT(_player->getPlayerBullet()->getVPlayerBullet()[j].rc)))
			{
				SOUNDMANAGER->play("throwE_1", 1);
				(*_enemyManager->setVBot())[i]->setEnemyHP((*_enemyManager->setVBot())[i]->getEnemyHP() - 10);
				(*_enemyManager->setVBot())[i]->setEnemyState(ENEMYSTATE::BOT_ATTACKED);
				_player->getPlayerBullet()->setVPlayerBullet()->erase(_player->getPlayerBullet()->setVPlayerBullet()->begin() + j);
				EFFECTMANAGER->play("hit", (*_enemyManager->setVBot())[i]->getEnemyPosX() + 35, (*_enemyManager->setVBot())[i]->getEnemyPosY() + 23);
			}
			else j++;
		}
		i++;
	}

	RECT rc3;
	//몬스터(터렛) vs 플레이어 근접 공격 충돌
	for (int i = 0; i < _enemyManager->getVTurret().size();)
	{
		if (IntersectRect(&rc3, &makeRECT(_enemyManager->getVTurret()[i]->getEnemyRc()), &makeRECT(_player->getPlayerAttackRc()))
			&& _player->getIsAttack() == true && _turretAttack)
		{
			(*_enemyManager->setVTurret())[i]->setEnemyHP((*_enemyManager->setVTurret())[i]->getEnemyHP() - 20);
			(*_enemyManager->setVTurret())[i]->setEnemyState(ENEMYSTATE::TURRET_IDLE);
			EFFECTMANAGER->play("hit", (*_enemyManager->setVTurret())[i]->getEnemyPosX() + 35, (*_enemyManager->setVTurret())[i]->getEnemyPosY() + 23);
			_turretAttack = false;
			_turretAttackTime = GetTickCount();
		}
		else i++;
	}

	RECT rc4;
	//몬스터(터렛) vs 플레이어 총알 충돌
	for (int i = 0; i < _enemyManager->getVTurret().size();)
	{
		for (int j = 0; j < _player->getPlayerBullet()->getVPlayerBullet().size();)
		{
			if (IntersectRect(&rc4, &makeRECT(_enemyManager->getVTurret()[i]->getEnemyRc()), &makeRECT(_player->getPlayerBullet()->getVPlayerBullet()[j].rc)))
			{
				SOUNDMANAGER->play("throwE_1", 1);
				(*_enemyManager->setVTurret())[i]->setEnemyHP((*_enemyManager->setVTurret())[i]->getEnemyHP() - 10);
				(*_enemyManager->setVTurret())[i]->setEnemyState(ENEMYSTATE::TURRET_IDLE);
				_player->getPlayerBullet()->setVPlayerBullet()->erase(_player->getPlayerBullet()->setVPlayerBullet()->begin() + j);
				_turretAttack = false;
				_turretAttackTime = GetTickCount();
				EFFECTMANAGER->play("hit", (*_enemyManager->setVTurret())[i]->getEnemyPosX() + 35, (*_enemyManager->setVTurret())[i]->getEnemyPosY() + 23);
			}
			else j++;
		}
		i++;
	}
	//몬스터(터렛) vs 타일오브젝트 충돌
	for (int i = 0; i < _enemyManager->getTurretBullet()->getVTurretBullet().size(); i++)
	{
		(*_enemyManager->getTurretBullet()->setVTurretBullet())[i].idX = _enemyManager->getTurretBullet()->getVTurretBullet()[i].x / 32;
		(*_enemyManager->getTurretBullet()->setVTurretBullet())[i].idY = _enemyManager->getTurretBullet()->getVTurretBullet()[i].y / 32;

		_tileIndex[3].x = _enemyManager->getTurretBullet()->getVTurretBullet()[i].idX;
		_tileIndex[3].y = _enemyManager->getTurretBullet()->getVTurretBullet()[i].idY;

		if (_stage2->getTile(_tileIndex[3].x, _tileIndex[3].y)->getObject() == OBJECT::OBJ_LINE ||
			_stage2->getTile(_tileIndex[3].x, _tileIndex[3].y)->getObject() == OBJECT::OBJ_CONTAINER)
		{
			SOUNDMANAGER->play("throwE_1", 1);
			EFFECTMANAGER->play("turretBulletE", _enemyManager->getTurretBullet()->getVTurretBullet()[i].x + 25, _enemyManager->getTurretBullet()->getVTurretBullet()[i].y + 10);
			_enemyManager->getTurretBullet()->setVTurretBullet()->erase(_enemyManager->getTurretBullet()->setVTurretBullet()->begin() + i);
		}
	}
}

void stage_2::setWindowsSize(int x, int y, int width, int height)
{
	//SAFE_RELEASE2(D2DMANAGER->_renderTarget);
	D2DMANAGER->_renderTarget->Resize(SizeU(width, height));

	//---------------------------------------------------------------------------
	//   Hwnd Render Target 생성
	//---------------------------------------------------------------------------
	//D2DMANAGER->_d2dFactory->CreateHwndRenderTarget(RenderTargetProperties(),
	//	HwndRenderTargetProperties(_hWnd, SizeU(width, height)),
	//	&D2DMANAGER->_renderTarget);

	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실질적으로 클라이언트 영역 크기 셋팅을 한다
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);
}


