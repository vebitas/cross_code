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
	//setWindowsSize(0, 0, GAMESIZEX, GAMESIZEY);
	IMAGEMANAGER->addImage("testMap", L"image/map/testMap.png", GAMESIZEX, GAMESIZEY);
	IMAGEMANAGER->addFrameImage("barricade", L"image/object/barricade.png", 180, 113, 9, 1);
	CAMERA->init(WINSIZEX, WINSIZEY, 47 * TILESIZE, 45 * TILESIZE);
	_oneMap = new stageOneMap;
	_player = new player;
	_enemyManager = new enemyManager;
	_oneMap->init();
	_player->init();
	_player->setPlayerPosX(WINSIZEX / 2 + 160);
	_player->setPlayerPosY(WINSIZEY + 500);
	_enemyManager->init();

	_briFrameX = _briFrameY = _count = 0;
	_briAlpha = 0;

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
		_enemyManager->update();
	}
	enemyCollision();

	_count++;
	if (_enemyManager->getVHog().empty() == false)
	{
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
				}
			}
			else
			{
				_briAlpha = 1;
				CAMERA->linearKeepMove(_player->getPlayerPosX(), _player->getPlayerPosY(), 0.5, 0);
			}
		}
	}
	else
	{
		if (_briAlpha > 0)
			_briAlpha -= 0.02f;
		else
			_briAlpha = 0;
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

	enemyTileCheck();
	tileCheck();
	_briRc = { (float)360, (float)243, (float)1050, (float)730 };
	
	CAMERA->update(_player->getPlayerPosX(), _player->getPlayerPosY());
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
	EFFECTMANAGER->render(0);
	_player->render();
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

	D2DMANAGER->drawRectangle(RGB(255,0,255),rc[0]);

	WCHAR str[128];
	swprintf_s(str, L"%d, %d", _tileIndex[0].x, _tileIndex[0].y);
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 100, CAMERA->getCameraY() + 20, 20, RGB(0, 0, 0));
	swprintf_s(str, L"플레이어 : %f, %f", _player->getPlayerPosX(), _player->getPlayerPosY());
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 100, CAMERA->getCameraY() + 40, 20, RGB(0, 0, 0));
	swprintf_s(str, L"플레이어 : %d, %d", _player->getPlayerIdX(), _player->getPlayerIdY());
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 100, CAMERA->getCameraY() + 60, 20, RGB(0, 0, 0));
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
	RECT rc;
	for (int i = 0; i < _enemyManager->getVHog().size();)
	{
		if ((*_enemyManager->setVHog())[i]->getEnemyState() == ENEMYSTATE::HOG_ATTACK)
		{

		}
	}
}

void stage_1::enemyCollision()
{
	RECT rc;
	for (int i = 0; i < _enemyManager->getVHog().size();)
	{
		if (IntersectRect(&rc, &makeRECT(_enemyManager->getVHog()[i]->getEnemyRc()), &makeRECT(_player->getPlayerAttackRc()))
			&& !((*_enemyManager->setVHog())[i]->getEnemyState() == ENEMYSTATE::HOG_ATTACKED) && _player->getIsAttack() == true)
		{
			(*_enemyManager->setVHog())[i]->setEnemyHP((*_enemyManager->setVHog())[i]->getEnemyHP() - 10);
			(*_enemyManager->setVHog())[i]->setEnemyState(ENEMYSTATE::HOG_ATTACKED);
			EFFECTMANAGER->play("hit", (*_enemyManager->setVHog())[i]->getEnemyPosX() + 35, (*_enemyManager->setVHog())[i]->getEnemyPosY() + 23);
		}
		else i++;
	}
	RECT rc2;
	for (int i = 0; i < _enemyManager->getVHog().size();)
	{
		for(int j = 0; j < _player->getPlayerBullet()->getVPlayerBullet().size();)
		{ 
			if (IntersectRect(&rc2, &makeRECT(_enemyManager->getVHog()[i]->getEnemyRc()), &makeRECT(_player->getPlayerBullet()->getVPlayerBullet()[j].rc)))
			{
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


void stage_1::setWindowsSize(int x, int y, int width, int height)
{
	SAFE_RELEASE2(D2DMANAGER->_renderTarget);

	//---------------------------------------------------------------------------
	//   Hwnd Render Target 생성
	//---------------------------------------------------------------------------
	D2DMANAGER->_d2dFactory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(_hWnd, SizeU(width, height)),
		&D2DMANAGER->_renderTarget);

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

