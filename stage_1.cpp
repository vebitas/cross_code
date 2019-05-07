#include "stdafx.h"
#include "stage_1.h"


stage_1::stage_1()
{
}


stage_1::~stage_1()
{
}

HRESULT stage_1::init()
{
	KEYANIMANAGER->deleteAll();
	setWindowsSize(0, 0, GAMESIZEX, GAMESIZEY);
	//IMAGEMANAGER->addImage("testMap", L"image/map/testMap.png", GAMESIZEX, GAMESIZEY);
	
;
	CAMERA->init(GAMESIZEX, GAMESIZEY, 47 * TILESIZE, 45 * TILESIZE);
	_oneMap = new stageOneMap;
	_player = new player;
	_enemyManager = new enemyManager;
	_oneMap->init();
	_player->init();
	_player->setPlayerPosX(GAMESIZEX / 2 + 160);
	_player->setPlayerPosY(GAMESIZEY + 500);
	_enemyManager->init();
	_enemyManager->setHedgehog();

	_teleportRc = { (float)1390, (float)490, (float)1400, (float)500 };

	_briFrameX = _briFrameY = _count = 0;
	_briAlpha = 0;
	_sceneChangeAlpha = 0;
	_teleportFrameX = 0;
	_hogAttack = false;

	SOUNDMANAGER->play("awakened", 0.8);
	return S_OK;
}

void stage_1::release()
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_oneMap);
	SAFE_DELETE(_enemyManager);
}

void stage_1::update()
{
	

	_oneMap->update();
	_player->update();
	if (_briAlpha == 1)
	{
		_enemyManager->hogAI(_player->getPlayerPosX(), _player->getPlayerPosY());
		_enemyManager->update(_player->getPlayerPosX(), _player->getPlayerPosY());
	}
	_count++;
	if (_enemyManager->getVHog().empty() == false)
	{
		enemyCollision();
		if (_count % 5 == 0)
		{
			if (_briFrameX < 8)
				_briFrameX++;
			else
				_briFrameX = 0;
		}
		if (_player->getPlayerPosY() <= 650)
		{
			if (_briAlpha < 1)
			{
				_briAlpha += 0.02f;
				if (_briAlpha <= 0.2f && _briAlpha <= 0.3f)
				{
					CAMERA->linearKeepMove(_player->getPlayerPosX(), _player->getPlayerPosY() - 300, 0.5, 10);
				}
				else if (_briAlpha <= 0.53f && _briAlpha < 0.31f)
				{
					EFFECTMANAGER->play("summon", 520, 480);
					EFFECTMANAGER->play("summon", 520, 380);
					EFFECTMANAGER->play("summon", 520, 280);
					EFFECTMANAGER->play("summon", 520, 180);
					EFFECTMANAGER->play("summon", 920, 480);
					EFFECTMANAGER->play("summon", 920, 380);
					EFFECTMANAGER->play("summon", 920, 280);
					EFFECTMANAGER->play("summon", 920, 180);
					SOUNDMANAGER->stop("awakened");
					SOUNDMANAGER->play("fierceBattle", 1);
				}
			}
			else
			{
				_briAlpha = 1;
				CAMERA->linearKeepMove(_player->getPlayerPosX(), _player->getPlayerPosY(), 0.2, 0.1);
			}
		}
	}
	else
	{
		if (_briAlpha > 0)
			_briAlpha -= 0.02f;
		else
		{
			_briAlpha = 0;
			_teleportFrameX = 1;
		}
	}


	if (_briAlpha > 0.01)
	{
		if (_player->getPlayerPosX() <= 360)
		{
			_player->setPlayerPosX(361);
		}
		else if (_player->getPlayerPosX() >= 1000)
		{
			_player->setPlayerPosX(999);
		}
		if (_player->getPlayerPosY() <= 200)
		{
			_player->setPlayerPosY(201);
		}
		else if (_player->getPlayerPosY() >= 660)
		{
			_player->setPlayerPosY(659);
		}
	}

	playerCollision();
	
	teleportRcCollision();
	enemyTileCheck();
	tileCheck();
	
	CAMERA->update(_player->getPlayerPosX(), _player->getPlayerPosY());
	_briRc = { (float)360, (float)243, (float)1050, (float)730 };

	if (_player->getPlayerState() == PLAYERSTATE::PLAYER_TELEPORT)
	{

		if (_sceneChangeAlpha < 1)
			_sceneChangeAlpha += 0.01;
		else
		{
			SCENEMANAGER->changeScene("stage2");
		}
	}
}

void stage_1::render()
{
	//맵 렌더 
	_oneMap->render();
	//바리게이트 랜더
	for (int i = 0; i < 36; i++)
	{
		IMAGEMANAGER->findImage("barricade")->frameRender(350 + (i * 20), 130 , _briFrameX, 0, _briAlpha);
	}
	_enemyManager->render(_briAlpha);
	IMAGEMANAGER->findImage("teleport")->frameRender(1360, 460, _teleportFrameX, 0);
	EFFECTMANAGER->render(0);
	_player->render(false);
	//바리게이트 랜더
	for (int i = 0; i < 36; i++)
	{
		IMAGEMANAGER->findImage("barricade")->frameRender(350 + (i * 20), 630, _briFrameX, 0, _briAlpha);
	}
	for (int i = 0; i < 25; i++)
	{
		IMAGEMANAGER->findImage("barricade")->frameRender(350, 130 + (i * 20), _briFrameX, 0, _briAlpha);
	}
	for (int i = 0; i < 25; i++)
	{
		IMAGEMANAGER->findImage("barricade")->frameRender(1050, 130 + (i * 20), _briFrameX, 0, _briAlpha);
	}

	//D2DMANAGER->fillRectangle(RGB(255, 0, 255), _briRc);
	_oneMap->zOrder();
	_player->render(true);
	//D2DMANAGER->drawRectangle(RGB(255,0,255), _teleportRc);

	IMAGEMANAGER->findImage("sceneChange")->render(0 + CAMERA->getCameraX() , 0 + CAMERA->getCameraY(), _sceneChangeAlpha);

	//WCHAR str[128];
	//swprintf_s(str, L"플레이어 상태 : %d", _player->getPlayerState());
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 20, 20, RGB(255, 255, 255));
	//swprintf_s(str, L"플레이어 : %f, %f", _player->getPlayerPosX(), _player->getPlayerPosY());
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 100, CAMERA->getCameraY() + 40, 20, RGB(0, 0, 0));
	//swprintf_s(str, L"플레이어 : %d, %d", _player->getPlayerIdX(), _player->getPlayerIdY());
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 100, CAMERA->getCameraY() + 60, 20, RGB(0, 0, 0));
	//swprintf_s(str, L"플레이어Y : %f", _player->getPlayerPosY());
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 100, CAMERA->getCameraY() + 80, 20, RGB(0, 0, 0));
}

void stage_1::tileCheck()
{
	_player->setPlayerIdX(_player->getPlayerPosX() / 32);
	_player->setPlayerIdY(_player->getPlayerPosY() / 32);
	
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_tileIndex[0].x = _player->getPlayerIdX();
		_tileIndex[0].y = _player->getPlayerIdY() + 1;
		if (_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() + _player->getPlayerSpeed());
		}		
	}
	if (_player->getPlayerDirection() == LEFT && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() + _player->getPlayerSpeed());
		}
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_tileIndex[0].x = _player->getPlayerIdX() + 1;
		_tileIndex[0].y = _player->getPlayerIdY() + 1;
		if (_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() - _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == RIGHT && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosX(_player->getPlayerPosX() - _player->getPlayerSpeed());
		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_tileIndex[0].x = _player->getPlayerIdX() + 1;
		_tileIndex[0].y = _player->getPlayerIdY() +1;
		if (_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() + _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == UP && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() + _player->getPlayerSpeed());
		}
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_tileIndex[0].x = _player->getPlayerIdX() + 1;
		_tileIndex[0].y = _player->getPlayerIdY() + 2;
		if (_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() - _player->getPlayerSpeed());
		}
	}
	if (_player->getPlayerDirection() == DOWN && _player->getPlayerState() == PLAYER_MOVE_BREAK)
	{
		if (_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LINE ||
			_oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getTerrain() == TERRAIN::TR_FOREST
			|| _oneMap->getTile(_tileIndex[0].x, _tileIndex[0].y)->getObject() == OBJECT::OBJ_LAMP)
		{
			_player->setPlayerPosY(_player->getPlayerPosY() - _player->getPlayerSpeed());
		}
	}

	rc[0] = { (float)_tileIndex[0].x * TILESIZE ,(float)_tileIndex[0].y * TILESIZE, (float)_tileIndex[0].x * TILESIZE + TILESIZE, (float)_tileIndex[0].y * TILESIZE + TILESIZE };
}

void stage_1::enemyTileCheck()
{
	//바리게이트안에서만 체크
	for (int i = 0; i < _enemyManager->getVHog().size(); i++)
	{
		if((*_enemyManager->setVHog())[i]->getEnemyPosX() <= 360)
		{
			(*_enemyManager->setVHog())[i]->setEnemyPosX(361);
			_enemyManager->setHogAttack(false);
			(*_enemyManager->setVHog())[i]->setEnemyState(ENEMYSTATE::HOG_IDLE);
		}
		else if ((*_enemyManager->setVHog())[i]->getEnemyPosX() >= 1000)
		{
			(*_enemyManager->setVHog())[i]->setEnemyPosX(999);
			_enemyManager->setHogAttack(false);
			(*_enemyManager->setVHog())[i]->setEnemyState(ENEMYSTATE::HOG_IDLE);
		}
		if ((*_enemyManager->setVHog())[i]->getEnemyPosY() <= 200)
		{
			(*_enemyManager->setVHog())[i]->setEnemyPosY(201);
			_enemyManager->setHogAttack(false);
			(*_enemyManager->setVHog())[i]->setEnemyState(ENEMYSTATE::HOG_IDLE);
		}
		else if ((*_enemyManager->setVHog())[i]->getEnemyPosY() >= 660)
		{
			(*_enemyManager->setVHog())[i]->setEnemyPosY(659);
			_enemyManager->setHogAttack(false);
			(*_enemyManager->setVHog())[i]->setEnemyState(ENEMYSTATE::HOG_IDLE);
		}
	}
}

void stage_1::playerCollision()
{
	RECT rc3;
	//몬스터 공격 vs 플레이어 충돌

	//if()

	for (int k = 0; k < _enemyManager->getVHog().size();)
	{
		if (((*_enemyManager->setVHog())[k]->getEnemyState() == ENEMYSTATE::HOG_ATTACK &&
			IntersectRect(&rc3, &makeRECT(_enemyManager->getVHog()[k]->getEnemyRc()), &makeRECT(_player->getPlayerRc())))
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
		}
		else k++;
	}
}

void stage_1::enemyCollision()
{
	RECT rc;
	//몬스터 vs 플레이어 근접 공격 충돌
	for (int i = 0; i < _enemyManager->getVHog().size();)
	{
		if (IntersectRect(&rc, &makeRECT(_enemyManager->getVHog()[i]->getEnemyRc()), &makeRECT(_player->getPlayerAttackRc()))
			&& !((*_enemyManager->setVHog())[i]->getEnemyState() == ENEMYSTATE::HOG_ATTACKED) && _player->getIsAttack() == true)
		{
			(*_enemyManager->setVHog())[i]->setEnemyHP((*_enemyManager->setVHog())[i]->getEnemyHP() - 20);
			(*_enemyManager->setVHog())[i]->setEnemyState(ENEMYSTATE::HOG_ATTACKED);
			EFFECTMANAGER->play("hit", (*_enemyManager->setVHog())[i]->getEnemyPosX() + 35, (*_enemyManager->setVHog())[i]->getEnemyPosY() + 23);
		}
		else i++;
	}
	RECT rc2;
	//몬스터 vs 플레이어 총알 충돌
	for (int i = 0; i < _enemyManager->getVHog().size();)	
	{
		for(int j = 0; j < _player->getPlayerBullet()->getVPlayerBullet().size();)
		{ 
			if (IntersectRect(&rc2, &makeRECT(_enemyManager->getVHog()[i]->getEnemyRc()), &makeRECT(_player->getPlayerBullet()->getVPlayerBullet()[j].rc)))
			{
				SOUNDMANAGER->play("throwE_1", 1);
				(*_enemyManager->setVHog())[i]->setEnemyHP((*_enemyManager->setVHog())[i]->getEnemyHP() - 10);
				(*_enemyManager->setVHog())[i]->setEnemyState(ENEMYSTATE::HOG_ATTACKED);
				_player->getPlayerBullet()->setVPlayerBullet()->erase(_player->getPlayerBullet()->setVPlayerBullet()->begin() + j);
				EFFECTMANAGER->play("hit", (*_enemyManager->setVHog())[i]->getEnemyPosX() + 35, (*_enemyManager->setVHog())[i]->getEnemyPosY() + 23);
			}
			else j++;
		}
		i++;
	}
}

void stage_1::teleportRcCollision()
{
	RECT rc;
	if (IntersectRect(&rc, &makeRECT(_teleportRc), &makeRECT(_player->getPlayerRc())) && !(_player->getPlayerState() == PLAYERSTATE::PLAYER_TELEPORT))
	{
		_player->setPlayerState(PLAYERSTATE::PLAYER_TELEPORT);
	
	}
}

void stage_1::setWindowsSize(int x, int y, int width, int height)
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


