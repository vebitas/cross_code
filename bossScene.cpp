#include "stdafx.h"
#include "bossScene.h"


bossScene::bossScene()
{
}


bossScene::~bossScene()
{
}

HRESULT bossScene::init()
{
	KEYANIMANAGER->deleteAll();
	setWindowsSize(0, 0, GAMESIZEX, GAMESIZEY);
	_bossMap = new bossStageMap;
	_boss = new boss;
	_player = new player;
	_bossBullet = new bossBullet;
	SOUNDMANAGER->play("bossBattle", 0.5);
	_boss->init();
	_bossBullet->init("bossBullet", 800, 50);
	_bossMap->init();
	_player->init();
	_boss->setBossPosX(50 * TILESIZE / 2);
	_boss->setBossPosY(36 * TILESIZE / 2);
	CAMERA->init(GAMESIZEX, GAMESIZEY, 50 * TILESIZE, 36 * TILESIZE);
	_bossPatten = 0;
	_bossAttackPatten = 0;
	_pattenOnce = false;
	_effTime = 0;
	_bossDashCount = 0;
	_bossBulletCount = 0;
	_bossAlpha = 0;
	_bossPattenTime = GetTickCount();
	_effZorder = false;
	_bulletMarkRender = false;
	_bossAttacked = false;
	_bossDeath = false;
	_bossCollTime = GetTickCount();
	_bossAttackedTime = GetTickCount();

	for (int i = 0; i < 5; i++)
	{
		_bulletMarkPos[i].x = 0;
		_bulletMarkPos[i].y = 0;
		_bulletPos[i].x = 0;
		_bulletPos[i].y = 0;
		_markBoom[i] = false;
		_turnWait[i] = false;
	}

	return S_OK;
}

void bossScene::release()
{
	SAFE_DELETE(_bossMap);
	SAFE_DELETE(_boss);
	SAFE_DELETE(_player);
}

void bossScene::update()
{
	_boss->update();
	_bossBullet->update();
	BossAI(_player->getPlayerPosX(), _player->getPlayerPosY(), true);
	_player->update();
	tileCheck();
	playerCollision();
	bossCollision();

	if (_boss->getBossHP() <= 0 && !_bossDeath)
	{
		_boss->setBossState(BOSSSTATE::BOSS_GROGGY);
		_bossDeath = true;
		SOUNDMANAGER->play("whale_2", 1);
	}

	CAMERA->update(_player->getPlayerPosX(), _player->getPlayerPosY());
	if (_boss->getBossState() == BOSSSTATE::BOSS_DIVING)
	{
		if (_once)
		{
			if(BOSSDIRECTION::BOSS_LEFT)
				CAMERA->linearKeepMove(_boss->getBossPosX() + 100, _boss->getBossPosY() - 200, 0.5f, 1);
			else
				CAMERA->linearKeepMove(_boss->getBossPosX() + 400, _boss->getBossPosY() - 200, 0.5f, 1);

			_cameraTime = GetTickCount();
			_once = false;
		}
		else if (GetTickCount() - _cameraTime >= 1000)
		{
			CAMERA->linearKeepMove(_player->getPlayerPosX(), _player->getPlayerPosY(), 0.5f, 0.6f);
			_cameraTime = GetTickCount();
		}
	}
	else
	{
		if (GetTickCount() - _cameraTime >= 600)
		{
			CAMERA->linearKeepMove(_player->getPlayerPosX(), _player->getPlayerPosY(), 0.5f, 1);
			_once = true;
		}
	}
}

void bossScene::render()
{
	_bossMap->render();
	EFFECTMANAGER->render(0);
	_boss->render();
	_player->render(false);
	if(_boss->getBossState() == BOSSSTATE::BOSS_DIVING)
		_boss->render();
	_bossBullet->render();
	if (_bulletMarkRender)
	{
		for (int i = 0; i < 5; i++)
		{
			IMAGEMANAGER->findImage("X")->render(_bulletMarkPos[i].x, _bulletMarkPos[i].y, 1);
		}
	}
	if(_effZorder || _player->getPlayerState() == PLAYERSTATE::PLAYER_SKILL_FIRE || _boss->getBossState() == BOSSSTATE::BOSS_GROGGY)
		EFFECTMANAGER->render(0);
	
	_player->render(true);
	_bossMap->zOrder();
	IMAGEMANAGER->findImage("bossHPOutLine")->render(0 + CAMERA->getCameraX(), GAMESIZEY - 35 + CAMERA->getCameraY(), GAMESIZEX, 35, 1);
	IMAGEMANAGER->findImage("bossHPBar")->render(100 + CAMERA->getCameraX(), GAMESIZEY - 30 + CAMERA->getCameraY(), (float)(_boss->getBossHP() * 860 / _boss->getBossMaxHP()), 24, 0, 0, 860, 24, 1);

	//WCHAR str[128]; 
	//for (int i = 0; i < 5; i++)
	//{
	//	swprintf_s(str, L"%d", _turnWait[i]);dw
	//	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 400, CAMERA->getCameraY() + 100 + (i * 50), 20, RGB(255, 255, 255));
	//}

}

void bossScene::tileCheck()
{
	_player->setPlayerIdX(_player->getPlayerPosX() / 32);
	_player->setPlayerIdY(_player->getPlayerPosY() / 32);

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_tileIndex[0].x = _player->getPlayerIdX();
		_tileIndex[0].y = _player->getPlayerIdY() + 1;
		if (_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() + _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == LEFT && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() + _player->getPlayerSpeed());
		}
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_tileIndex[0].x = _player->getPlayerIdX() + 1;
		_tileIndex[0].y = _player->getPlayerIdY() + 1;
		if (_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() - _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == RIGHT && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() - _player->getPlayerSpeed());
		}
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_tileIndex[0].x = _player->getPlayerIdX() + 1;
		_tileIndex[0].y = _player->getPlayerIdY() + 1;
		if (_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() + _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == UP && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() + _player->getPlayerSpeed());
		}
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_tileIndex[0].x = _player->getPlayerIdX() + 1;
		_tileIndex[0].y = _player->getPlayerIdY() + 2;
		if (_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() - _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == DOWN && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _bossMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() - _player->getPlayerSpeed());
		}
	}

	_tileCheckRc = { (float)_tileIndex[0].x * TILESIZE ,(float)_tileIndex[0].y * TILESIZE, (float)_tileIndex[0].x * TILESIZE + TILESIZE, (float)_tileIndex[0].y * TILESIZE + TILESIZE };
}
//플레이어공격 vs 보스충돌
void bossScene::bossCollision()
{
	RECT rc;
	if (IntersectRect(&rc, &makeRECT(_boss->getBossRc()), &makeRECT(_player->getPlayerAttackRc()))
		&&  _player->getIsAttack() == true)
	{
		if (_boss->getBossState() == BOSSSTATE::BOSS_IDLE || _boss->getBossState() == BOSSSTATE::BOSS_RUSH && !(_boss->getBossAlpha() == 0))
		{
			if (GetTickCount() - _bossCollTime >= 500)
			{
				_boss->setBossHP(_boss->getBossHP() - 20);
				_bossCollTime = GetTickCount();
				_bossAttacked = true;
				_bossAttackedTime = GetTickCount();
			}
		}
	}
	RECT rc2;
	for (int i = 0; i < _player->getPlayerBullet()->getVPlayerBullet().size();)
	{
		if (IntersectRect(&rc2, &makeRECT(_boss->getBossRc()), &makeRECT(_player->getPlayerBullet()->getVPlayerBullet()[i].rc)) && (_boss->getBossState() == BOSSSTATE::BOSS_IDLE || _boss->getBossState() == BOSSSTATE::BOSS_RUSH))
		{
			SOUNDMANAGER->play("throwE_1", 1);
			_boss->setBossHP(_boss->getBossHP() - 20);
			EFFECTMANAGER->play("ballN_E", _player->getPlayerBullet()->getVPlayerBullet()[i].x + 10, _player->getPlayerBullet()->getVPlayerBullet()[i].y + 10);
			_player->getPlayerBullet()->setVPlayerBullet()->erase(_player->getPlayerBullet()->setVPlayerBullet()->begin() + i);
			_bossAttacked = true;
			_bossAttackedTime = GetTickCount();
		}
		else i++;
	}


	if (_bossAttacked)
	{
		if (_bossAlpha == 0)
		{
			_boss->setBossAlpha(0.5f);
			_bossAlpha = 1;
		}
		else
		{
			_boss->setBossAlpha(0.8f);
			_bossAlpha = 0;
		}
	
	}
	
	if (GetTickCount() - _bossAttackedTime >= 500)
	{
		_bossAttacked = false;
	}

}
void bossScene::playerCollision()
{
	for (int i = 0; i < _bossBullet->getVBossBullet().size();)
	{
		RECT rc;
		if (IntersectRect(&rc, &makeRECT(_bossBullet->getVBossBullet()[i].rc), &makeRECT(_player->getPlayerRc()))
			&& !(_player->getPlayerState() == PLAYERSTATE::PLAYER_ATTACKED) && !(_player->getPlayerState() == PLAYERSTATE::PLAYER_SKILL_FIRE))
		{
			SOUNDMANAGER->play("playerAttacked", 1);
			_player->setPlayerState(PLAYERSTATE::PLAYER_ATTACKED);
			_player->setPlayerHP(_player->getPlayerHP() - 10);
			EFFECTMANAGER->play("effect5", _bossBullet->getVBossBullet()[i].x + 50, _bossBullet->getVBossBullet()[i].y + 40);
			_bossBullet->setVBossBullet()->erase(_bossBullet->setVBossBullet()->begin() + i);
		}
		else
		{
			i++;
		}
	}

	if (_boss->getBossState() == BOSSSTATE::BOSS_RUSH)
	{
		RECT rc2;
		if (IntersectRect(&rc2, &makeRECT(_boss->getBossRc()), &makeRECT(_player->getPlayerRc()))
			&& !(_player->getPlayerState() == PLAYERSTATE::PLAYER_ATTACKED) && !(_player->getPlayerState() == PLAYERSTATE::PLAYER_SKILL_FIRE))
		{
			SOUNDMANAGER->play("playerAttacked", 1);
			_player->setPlayerState(PLAYERSTATE::PLAYER_ATTACKED);
			_player->setPlayerHP(_player->getPlayerHP() - 1);
		}
	}
}
//보스 공격패턴 모음
void bossScene::BossAI(float playerX, float playerY, bool battleStart)
{
	_effTime += TIMEMANAGER->getElapsedTime();
	if (battleStart && !_bossDeath)
	{
		switch (_bossAttackPatten)
		{
		case 0:
			switch (_bossPatten)
			{
			case 0:
				_effZorder = false;
				_boss->setBossState(BOSSSTATE::BOSS_MOVE);
				_boss->setBossMoveAngle(getAngle2(playerX - 270, playerY - 110, _boss->getBossPosX(), _boss->getBossPosY()));
				_boss->setBossPosX(_boss->getBossPosX() + (-cos(_boss->getMoveAngle()) * _boss->getBossSpeed()));
				_boss->setBossPosY(_boss->getBossPosY() + (-sin(_boss->getMoveAngle()) * _boss->getBossSpeed()));
				if (_boss->getBossPosX() < _player->getPlayerPosX() - 200)
				{
					_boss->setBossDirection(BOSSDIRECTION::BOSS_RIGHT);
				}
				else
					_boss->setBossDirection(BOSSDIRECTION::BOSS_LEFT);

				if (GetTickCount() - _bossPattenTime >= 6 * 1000)
				{
					_bossPattenTime = GetTickCount();
					_bossPatten++;
				}
				break;
			case 1:
				_pattenOnce = true;
				_boss->setBossState(BOSSSTATE::BOSS_SHADOW);
				POINT effPos;
				//effPos.x = RND->getFromIntTo(0, 300);
				//effPos.y = RND->getFromIntTo(0, 300);
				if (_effTime >= 0.08f)
				{
					_effTime = 0;
					for (int i = 0; i < 3; i++) {
						effPos.x = RND->getFromIntTo(0, 300);
						effPos.y = RND->getFromIntTo(0, 300);
						EFFECTMANAGER->play("effect5", _boss->getBossPosX() + 150 + effPos.x, _boss->getBossPosY() + effPos.y);
					}
					//EFFECTMANAGER->play("effect5", _boss->getBossPosX() + 150 + effPos.x, _boss->getBossPosY() + effPos.y);
				}
				if (GetTickCount() - _bossPattenTime >= 2 * 1000)
				{
					_bossPattenTime = GetTickCount();
					_bossPatten++;
				}

				break;
			case 2:
				if (_pattenOnce)
				{
					_boss->setBossPosY(_boss->getBossPosY() - 300);
					_pattenOnce = false;
				}
				if (_boss->getBossState() == BOSSSTATE::BOSS_IDLE)
				{
					_bossPatten = 0;
					_bossPatten = 3;
				}


				if (_bossPatten == 2)
				{
					_boss->setBossState(BOSSSTATE::BOSS_DIVING);
				}
				break;
			case 3:
				if (!(_boss->getBossState() == BOSSSTATE::BOSS_DIVING))
				{
					_boss->setBossState(BOSSSTATE::BOSS_MOVE);


					if (_boss->getBossDirection() == BOSSDIRECTION::BOSS_LEFT)
					{
						if (_boss->getBossPosX() > -300)
							_boss->setBossPosX(_boss->getBossPosX() - 3.0f);
						else
						{
							_bossPatten = 0;
							_bossAttackPatten = 1;
							_boss->setBossDirection(BOSSDIRECTION::BOSS_RIGHT);
						}
					}
					else
					{
						if (_boss->getBossPosX() < GAMESIZEX + 300)
							_boss->setBossPosX(_boss->getBossPosX() + 3.0f);
						else
						{
							_bossPatten = 0;
							_bossAttackPatten = 1;
							_boss->setBossDirection(BOSSDIRECTION::BOSS_LEFT);
						}
					}
				}
				else
				{
					if (_boss->getBossPosX() > GAMESIZEX / 2)
					{
						_boss->setBossDirection(BOSSDIRECTION::BOSS_LEFT);
					}
					else
					{
						_boss->setBossDirection(BOSSDIRECTION::BOSS_RIGHT);
					}
				}
				break;
			}
			break;
			
		case 1:
			switch (_bossPatten)
			{
			case 0:
				_boss->setBossMoveAngle(getAngle2(playerX - 270, playerY - 110, _boss->getBossPosX(), _boss->getBossPosY()));
				if(_boss->getBossPosY() < playerY - 150)
					_boss->setBossPosY(_boss->getBossPosY() + 1.0f);
				else 
					_boss->setBossPosY(_boss->getBossPosY() - 1.0f);
				_boss->setBossState(BOSSSTATE::BOSS_RUSH);

				if (_boss->getBossDirection() == BOSSDIRECTION::BOSS_LEFT)
				{
					if (_boss->getBossPosX() < - 800)
					{
						_bossPatten++;
						_boss->setBossState(BOSSSTATE::BOSS_IDLE);
					}
				}
				else
				{
					if (_boss->getBossPosX() > GAMESIZEX + 800)
					{
						_bossPatten++;
						_boss->setBossState(BOSSSTATE::BOSS_IDLE);
					}
				}

				break;
			case 1:
				_bossDashCount++;
				if (_boss->getBossDirection() == BOSSDIRECTION::BOSS_LEFT)
				{
					_bossPatten = 0;
					_boss->setBossDirection(BOSSDIRECTION::BOSS_RIGHT);
				}
				else
				{
					_bossPatten = 0;
					_boss->setBossDirection(BOSSDIRECTION::BOSS_LEFT);
				}

				if (_bossDashCount == 3)
				{
					_bossPatten = 0;
					_bossDashCount = 0;
					_bossAttackPatten = 2;
					_bossPattenTime = GetTickCount();
				}
				break;
			}
			break;
		case 2:
			switch (_bossPatten)
			{
			case 0:
				_boss->setBossState(BOSSSTATE::BOSS_SHADOW);
				_boss->setBossDirection(BOSSDIRECTION::BOSS_RIGHT);
				if (GetTickCount() - _bossPattenTime >= 2 * 1000)
				{
					_bossPattenTime = GetTickCount();
					_bossPatten++;
					CAMERA->linearKeepMove(_boss->getBossPosX(), _boss->getBossPosY() - 200, 1, 1);
				}
				break;
			case 1:
				POINT effPos;
				_boss->setBossPosX(GAMESIZEX / 2 - 100);
				_boss->setBossPosY(100);
				_boss->setBossEyeFrame(2);
				_effZorder = true;
				if (_effTime >= 0.05f)
				{
					_effTime = 0;
					for (int i = 0; i < 6; i++) {
						effPos.x = RND->getFromIntTo(0, 800);
						effPos.y = RND->getFromIntTo(0, 400);
						EFFECTMANAGER->play("effect5", _boss->getBossPosX() - 100 + effPos.x, _boss->getBossPosY() - 50 + effPos.y);
					}
					//EFFECTMANAGER->play("effect5", _boss->getBossPosX() + 150 + effPos.x, _boss->getBossPosY() + effPos.y);
				}
				if (GetTickCount() - _bossPattenTime >= 3 * 1000)
				{
					_bossPatten++;
					_bossPattenTime = GetTickCount();
					SOUNDMANAGER->play("whale_2", 1);
				}

				break; 
			case 2:
				_boss->setBossState(BOSSSTATE::BOSS_IDLE);
				if (GetTickCount() - _bossPattenTime >= 1 * 500)
				{
					SOUNDMANAGER->play("throwE_2", 1);
					EFFECTMANAGER->play("effect8", _boss->getBossPosX() + 610, _boss->getBossPosY() - 30);
					_bossPattenTime = GetTickCount();
					_bossBulletCount++;
					//_bossBullet->bulletFire(_boss->getBossPosX(), _boss->getBossPosY(), 270, 1);
				}
				if (_bossBulletCount == 5)
				{
					_bossBulletCount = 0;
					_bossPatten++;
					_bossPattenTime = GetTickCount();
				}
				break;
			case 3:
				for (int i = 0; i < 5; i++)
				{
					_bulletMarkPos[i].x = RND->getFromIntTo(100, 1200);
					_bulletMarkPos[i].y = RND->getFromIntTo(400, 800);
					_bossPatten = 4;
					_bulletPos[i].x = GAMESIZEX / 2;
					_bulletPos[i].y = -100;
				}
				break;
			case 4:
				_bulletMarkRender = true;
				for (int i = 0; i < 5; i++)
				{
					float angle;
					angle = getAngle2(_bulletPos[i].x, _bulletPos[i].y, _bulletMarkPos[i].x, _bulletMarkPos[i].y);
					
					if (_bulletPos[i].y < _bulletMarkPos[i].y && !_markBoom[i])
					{
						_bulletPos[i].x += cos(angle) * 5.0f;
						_bulletPos[i].y += sin(angle) * 5.0f;
					}
					else
					{
						
						_markBoom[i] = true;
					}

					if (GetTickCount() - _bossPattenTime >= 100)
					{
						for (int j = 0; j < 5; j++)
						{
							EFFECTMANAGER->play("effect3", _bulletPos[j].x + 50, _bulletPos[j].y + 50);
						}
						_bossPattenTime = GetTickCount();
					}
				

					if (_markBoom[i] && !_turnWait[i])
					{
						for (int k = 0; k < 9; k++)
						{
							_bossBullet->bulletFire(_bulletMarkPos[i].x, _bulletMarkPos[i].y, 0 + (k * 40), 5.0f);
						}
						_turnWait[i] = true;
					}

					
					if (_turnWait[0] && _turnWait[1] && _turnWait[2] && _turnWait[3] && _turnWait[4])
					{
						_bossPatten = 5;
						_bossPattenTime = GetTickCount();
					}
					
				}
				break;
			case 5:
				_bulletMarkRender = false;
				for (int i = 0; i < 5; i++)
				{
					_turnWait[i] = false;
					_markBoom[i] = false;
				}

				if (_effTime >= 0.05f)
				{
					_effTime = 0;
					for (int i = 0; i < 6; i++) {
						effPos.x = RND->getFromIntTo(0, 800);
						effPos.y = RND->getFromIntTo(0, 400);
						EFFECTMANAGER->play("effect5", _boss->getBossPosX() - 100 + effPos.x, _boss->getBossPosY() - 50 + effPos.y);
					}
					//EFFECTMANAGER->play("effect5", _boss->getBossPosX() + 150 + effPos.x, _boss->getBossPosY() + effPos.y);
				}

				if (GetTickCount() - _bossPattenTime >= 3 * 1000)
				{
					_bossPatten = 0;
					_effZorder = false;
					_bossPattenTime = GetTickCount();
					_bossAttackPatten = 0;
				}
				break;
	
			}
			break;
		}
	}
	else
	{

	if (_effTime >= 0.05f)
	{
		POINT effPos;
		_effTime = 0;
		for (int i = 0; i < 6; i++) {
			effPos.x = RND->getFromIntTo(0, 800);
			effPos.y = RND->getFromIntTo(0, 400);
			EFFECTMANAGER->play("bossDeath", _boss->getBossPosX() - 100 + effPos.x, _boss->getBossPosY() - 50 + effPos.y);
			SOUNDMANAGER->play("enemyDeath", 1);
		}
		//EFFECTMANAGER->play("effect5", _boss->getBossPosX() + 150 + effPos.x, _boss->getBossPosY() + effPos.y);
	}
	}
}

void bossScene::setWindowsSize(int x, int y, int width, int height)
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
