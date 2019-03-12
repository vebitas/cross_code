#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	
	IMAGEMANAGER->addFrameImage("leaMove", L"image/player/move.png", 1040, 1235, 16, 19);
	IMAGEMANAGER->addFrameImage("leaThrow", L"image/player/throw.png", 520, 1105, 8, 17);
	IMAGEMANAGER->addFrameImage("attackNormal", L"image/effect/sweep_normal.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackNormalR", L"image/effect/sweep_normal_R.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackNormalF", L"image/effect/sweep_normal_Last.png", 240, 42, 4, 1);
	IMAGEMANAGER->addFrameImage("attackFire", L"image/effect/sweep_fire.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackFireR", L"image/effect/sweep_fire_R.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackIce", L"image/effect/sweep_water.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackIceR", L"image/effect/sweep_water_R.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackSpake", L"image/effect/sweep_spake.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackSpakeR", L"image/effect/sweep_spake_R.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackWave", L"image/effect/sweep_wave.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackWaveR", L"image/effect/sweep_wave_R.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("bullet", L"image/effect/ball.png", 520, 320, 13, 8);
	IMAGEMANAGER->addFrameImage("bulletN", L"image/effect/ball_N_E.png", 160, 16, 10, 1);
	EFFECTMANAGER->addEffect("circle", "image/effect/circle.png", 900, 300, 300, 300, 7, 0.05, 20);
	
	_player.bullet = new playerBullet;
	_player.bullet->init("bullet", 1000, 500);


	_player.image = IMAGEMANAGER->findImage("leaMove");
	_player.x = GAMESIZEX / 2;
	_player.y = GAMESIZEY / 2;
	_player.speed = PLAYERSPEED;
	_player.angle = PI / 180;
	_player.alphaValue = 1;
	_player.direction = PLAYERDIRECTION::DOWN;
	_player.state = PLAYERSTATE::PLAYER_IDLE;

	
	_effectPlay = false;
	_isLea = true;
	_isRight = false;
	_isMove = false;
	_isThrowAttack = false;

	_effectCount = 0;
	_effectAngle = 0;
	_effPos.x = 0;
	_effPos.y = 0;
	_effSelect = 0;

	_player.rc = { (float)_player.x, (float)_player.y , (float)_player.x + 30, (float)_player.y + 30 };

	_attackRangeRc = { (float)_player.x, (float)_player.y, (float)150, (float)150 };
	_cursorChangeEll = EllipseMake(_player.x, _player.y, 130);
	_throwCount = 0;

	for (int i = 0; i < 4; i++)
	{
		_nobKey[i] = false;
		_breakCheck[i] = 0;
		_oldTime[i] = GetTickCount();
	}

	_attackTimeKeyDown = GetTickCount();
	_attackTimeKeyUp = GetTickCount();
	_attackComboTime = GetTickCount();

	_attackComboCount = 0;

	keyAniInit();
	effectInit();

	_cursor = LoadCursorFromFile("image/cursor/throwAttack.cur");
	SetCursor(_cursor);

	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_player.bullet);
}

void player::update()
{
	_player.bullet->update();
	setType();
	playerKeyInput();
	aimKeyInput();
	
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_effSelect = 0;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_effSelect = 1;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_effSelect = 2;
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_effSelect = 3;
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_effSelect = 4;
	}

	playerState();
	_cursorChangeEll = EllipseMake(_player.x + 30, _player.y + 30, 150);
	_attackRangeRc = { (float)_player.x + 30, (float) _player.y + 30, (float)150, (float)150 };
	_player.rc = { (float)_player.x + 15, (float)_player.y + 30 , (float)_player.x + 45, (float)_player.y + 60 };

}

void player::render()
{
	//D2DMANAGER->fillEllipse(RGB(255, 0, 255), _attackRangeRc);
	if (_isRight)
	{
		_player.image->aniRender(_player.x, _player.y, _player.motion);
	}
	else
	{
		_player.image->aniRenderReverseX(_player.x, _player.y, _player.motion);
	}
	if (_effectPlay)
	{
		if (!_effCopy)
		{
			_effect->frameRenderAngle(_player.x + _effPos.x, _player.y + _effPos.y, _effectFrameX, _effectFrameY, _effectAngle);
		}
		else
		{
			_effect->frameRenderAngle(_player.x + _effPos.x, _player.y + _effPos.y, _effectFrameX, _effectFrameY, _effectAngle);
		}
	}
	for (int i = 0; i < _player.bullet->getVPlayerBullet().size(); i++)
	{
		_player.bullet->render();
	}
	
	WCHAR str[128]; 
	swprintf_s(str, L"플레이어 상태 : %d", _effectAngle);
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 20, 20, RGB(255, 255, 255));
	swprintf_s(str, L"플레이어  : %d", _effectFrameY);
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 40, 20, RGB(255, 255, 255));
	swprintf_s(str, L"playerX : %f", _player.x);
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 60, 20, RGB(255, 255, 255));
	swprintf_s(str, L"playerY : %f", _player.y);
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 70, 20, RGB(255, 255, 255));
	for (int i = 0; i < 4; i++)
	{
		swprintf_s(str, L"%d : %d", i , _breakCheck[i]);
		D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 90 + (i * 20), 20, RGB(255, 255, 255));
	}
	D2DMANAGER->drawRectangle(_player.rc);
	EFFECTMANAGER->render(0);
}

void player::keyAniInit()
{
	KEYANIMANAGER->deleteAll();
	//아무것도 안할때
	int idleUp[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "idleUp", "leaMove", idleUp, 1, PLAYERFPS, true);
	int idleUpRight[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "idleUpRight", "leaMove", idleUpRight, 1, PLAYERFPS, true);
	int idleRight[] = { 33 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "idleRight", "leaMove", idleRight, 1, PLAYERFPS, true);
	int idleDownRight[] = { 49 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "idleDownRight", "leaMove", idleDownRight, 1, PLAYERFPS, true);
	int idleDown[] = { 65 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "idleDown", "leaMove", idleDown, 1, PLAYERFPS, true);
	//이동중
	int moveUp[] = { 3, 4, 5, 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveUp", "leaMove", moveUp, 6, PLAYERFPS, true);
	int moveUpRight[] = { 19, 20, 21, 22, 23, 24 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveUpRight", "leaMove", moveUpRight, 6, PLAYERFPS, true);
	int moveRight[] = { 35, 36, 37, 38, 39, 40 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveRight", "leaMove", moveRight, 6, PLAYERFPS, true);
	int moveDownRight[] = { 51, 52, 53, 54, 55, 56 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveDownRight", "leaMove", moveDownRight, 6, PLAYERFPS, true);
	int moveDown[] = {67, 68, 69, 70, 71, 72 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveDown", "leaMove", moveDown, 6, PLAYERFPS, true);
	//이동후 브레이크
	int moveBreakUp[] = {9, 10};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakUp", "leaMove", moveBreakUp, 2, PLAYERFPS, false, cbMoveBreak, this);
	int moveBreakUpRight[] = { 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakUpRight", "leaMove", moveBreakUpRight, 2, PLAYERFPS, false, cbMoveBreak, this);
	int moveBreakRight[] = { 41, 42 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakRight", "leaMove", moveBreakRight, 2, PLAYERFPS, false, cbMoveBreak, this);
	int moveBreakDownRight[] = { 57, 58 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakDownRight", "leaMove", moveBreakDownRight, 2, PLAYERFPS, false, cbMoveBreak, this);
	int moveBreakDown[] = { 73, 74 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakDown", "leaMove", moveBreakDown, 2, PLAYERFPS, false, cbMoveBreak, this);
	//원거리공격조준
	int throwAimUp[] = { 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimUp", "leaMove", throwAimUp, 2, 8, false, cbThrowAim, this);
	int throwAimUpRight[] = { 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimUpRight", "leaMove", throwAimUpRight, 2, 8, false, cbThrowAim, this);
	int throwAimRight[] = { 44, 45 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimRight", "leaMove", throwAimRight, 2, 8, false, cbThrowAim, this);
	int throwAimDownRight[] = { 60, 61 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimDownRight", "leaMove", throwAimDownRight, 2, 8, false, cbThrowAim, this);
	int throwAimDown[] = { 76, 77 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimDown", "leaMove", throwAimDown, 2, 8, false, cbThrowAim, this);
	//원거리공격차지
	int throwHoldUp[] = { 80, 81, 82, 83 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldUp", "leaMove", throwHoldUp, 4, 10, true);
	int throwHoldUpRight[] = { 96, 97, 98, 99 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldUpRight", "leaMove", throwHoldUpRight, 4, 10, true);
	int throwHoldRight[] = {112, 113, 114, 115 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldRight", "leaMove", throwHoldRight, 4, 10, true);
	int throwHoldDownRight[] = { 128, 129, 130, 131 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldDownRight", "leaMove", throwHoldDownRight, 4, 10, true);
	int throwHoldDown[] = { 144, 145, 146, 147 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldDown", "leaMove", throwHoldDown, 4, 10, true);
	//원거리공격차지중 이동
	int throwHoldMoveUp[] = { 84, 85 ,86 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldMoveUp", "leaMove", throwHoldMoveUp, 3, 10, true);
	int throwHoldMoveUpRight[] = { 100, 101, 102 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldMoveUpRight", "leaMove", throwHoldMoveUpRight, 3, 10, true);
	int throwHoldMoveRight[] = { 116, 117, 118 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldMoveRight", "leaMove", throwHoldMoveRight, 3, 10, true);
	int throwHoldMoveDownRight[] = { 132, 133, 134 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldMoveDownRight", "leaMove", throwHoldMoveDownRight, 3, 10, true);
	int throwHoldMoveDown[] = { 148, 149, 150 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwHoldMoveDown", "leaMove", throwHoldMoveDown, 3, 10, true);
	//원거리 공격
	int throwUp[] = { 3, 2 ,1 ,8, 16, 24 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwUp", "leaThrow", throwUp, 6, 22, false, cbAttack, this);
	int throwDown[] = { 7, 6, 5, 12, 20, 28};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwDown", "leaThrow", throwDown, 6, 22, false, cbAttack, this);
	int throwUpRight[] = { 4, 3, 2, 9, 17, 25 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwUpRight", "leaThrow", throwUpRight, 6, 22, false, cbAttack, this);
	int throwRight[] = { 6, 5, 4, 3, 10, 18, 26};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwRight", "leaThrow", throwRight, 7, 22, false, cbAttack, this);
	int throwLeft[] = { 2, 1, 0, 7, 14, 22, 30 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwLeft", "leaThrow", throwLeft, 7, 22, false, cbAttack, this);
	int throwUpLeft[] = { 2,1,0,15, 23, 31  };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwUpLeft", "leaThrow", throwUpLeft, 6, 22, false, cbAttack, this);
	int throwDownLeft[] = { 0, 7, 6, 13, 21, 29};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwDownLeft", "leaThrow", throwDownLeft, 6, 22, false, cbAttack, this);
	int throwDownRight[] = { 6, 5, 4, 11, 19, 27};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwDownRight", "leaThrow", throwDownRight, 6, 22, false, cbAttack, this);
	//근접공격
	int attackRight[] = { 5,  35, 43, 51, 59};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackRight", "leaThrow", attackRight, 5, 18, false, cbAttack, this);
	int attackRightLast[] = { 3, 2, 1, 7, 6, 5, 4, 34, 42, 50, 58};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackRightLast", "leaThrow", attackRightLast, 11, 18, false, cbAttack, this);
	int attackUp[] = { 2, 32, 40, 48, 56};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackUp", "leaThrow", attackUp, 5, 18, false, cbAttack, this);
	int attackUpLast[] = { 1, 0, 6, 5, 4, 2, 32, 40, 48, 56 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackUpLast", "leaThrow", attackUpLast, 10, 18, false, cbAttack, this);
	int attackUpRight[] = { 3, 33, 41, 49, 57 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackUpRight", "leaThrow", attackUpRight, 5, 18, false, cbAttack, this);
	int attackUpRightLast[] = { 2, 1, 7, 6, 5, 3, 17, 33, 41, 49, 57};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackUpRightLast", "leaThrow", attackUpRightLast, 11, 18, false, cbAttack, this);
	int attackUpLeft[] = { 1, 39, 47, 55, 63};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackUpLeft", "leaThrow", attackUpLeft, 5, 18, false, cbAttack, this);
	int attackUpLeftLast[] = { 1, 0, 6, 5, 3, 2, 1, 39, 47, 55, 63};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackUpLeftLast", "leaThrow", attackUpLeftLast, 11, 18, false, cbAttack, this);
	int attackLeft[] = { 0, 38, 46, 54, 62 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackLeft", "leaThrow", attackLeft, 5, 18, false, cbAttack, this);
	int attackLeftLast[] = { 0, 6, 5, 4, 2, 1, 0, 38, 46, 54, 62};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackLeftLast", "leaThrow", attackLeftLast, 11, 18, false, cbAttack, this);
	int attackDownLeft[] = { 7, 37, 45, 53, 61};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackDownLeft", "leaThrow", attackDownLeft, 5, 18, false, cbAttack, this);
	int attackDownLeftLast[] = { 7, 6, 4, 3, 2, 0, 7, 37, 45, 53, 61};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackDownLeftLast", "leaThrow", attackDownLeftLast, 11, 18, false, cbAttack, this);
	int attackDown[] = { 7, 6, 36, 44, 52, 60};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackDown", "leaThrow", attackDown, 6, 18, false, cbAttack, this);
	int attackDownLast[] = { 6, 5, 3, 2, 1, 0, 6, 36, 44, 52, 60};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackDownLast", "leaThrow", attackDownLast, 11, 18, false, cbAttack, this);
	int attackDownRight[] = { 5, 35, 43, 51, 59};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackDownRight", "leaThrow", attackDownRight, 5, 18, false, cbAttack, this);
	int attackDownRightLast[] = { 4, 3, 1, 0, 7, 5, 35, 43, 51, 59};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackDownRightLast", "leaThrow", attackDownRightLast, 10, 18, false, cbAttack, this);

	_player.motion = KEYANIMANAGER->findAnimation("lea", "idleDown");
}

void player::effectInit()
{
	_effectMaxFrameX = 4, _effectMaxFrameY = 2;
	_effectFrameX = _effectFrameY = 0;
	_effect = IMAGEMANAGER->findImage("attackNormal");
}

void player::effectUpdate(int maxFrameX, int maxFrameY, int fps)
{
	if (_effectPlay)
	{
		_effectCount++;
		if (_effectCount % fps == 0)
		{
			if (_effectFrameX < maxFrameX - 1)
			{
				_effectFrameX++;
			}
			else
			{
				if (_effectFrameY < maxFrameY - 1)
				{
					_effectFrameY++;
				}
				else
				{
					_effectFrameY = 0;
					_effectPlay = false;

				}
				_effectFrameX = 0;
			}
			_effectCount = 0;
		}
	}
	else
	{
		_effectFrameX = 0;
		_effectFrameY = 0;
		_effectPlay = false;
	}

	
}


void player::setType()
{
	if (_isLea)
	{
		_player.name = "leaMove";
	}
	else
	{
		_player.name = "leaThrow";
	}
}

void player::tileCheck()
{
	D2D1_RECT_F rcCollision;
	D2D1_RECT_F rc;

	//rcCollision
}

// 마우스 위치에 따른 방향전환
void player::attackAngle(bool stayOn)
{
	_player.angle = getAngle2(_player.x + 30, _player.y + 15, _ptMouse.x, _ptMouse.y);
	if ((PI / 180) * 22.6f <= _player.angle &&_player.angle <= (PI / 180) * 67.5f)
	{
		_player.direction = PLAYERDIRECTION::DOWN_RIGHT;
		
		if (!stayOn)
			_player.state = PLAYERSTATE::PLAYER_THROW_AIM;
		if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
			_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
	
	}
	else if ((PI / 180) * 67.6f <= _player.angle && _player.angle <= (PI / 180) * 112.5f)
	{
		_player.direction = PLAYERDIRECTION::DOWN;
	
		if (!stayOn)
			_player.state = PLAYERSTATE::PLAYER_THROW_AIM;
		if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
			_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
	
	}
	else if ((PI / 180) * 112.6f <= _player.angle && _player.angle <= (PI / 180) * 157.5f)
	{
		_player.direction = PLAYERDIRECTION::DOWN_LEFT;
	
		if (!stayOn)
			_player.state = PLAYERSTATE::PLAYER_THROW_AIM;
		if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
			_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
	
	}
	else if ((PI / 180) * 157.6f <= _player.angle && _player.angle <= (PI / 180) * 202.5f)
	{
		_player.direction = PLAYERDIRECTION::LEFT;
	
		if (!stayOn)
			_player.state = PLAYERSTATE::PLAYER_THROW_AIM;
		if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
			_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
		
	}
	else if ((PI / 180) * 202.6f <= _player.angle && _player.angle <= (PI / 180) * 247.5f)
	{
		_player.direction = PLAYERDIRECTION::UP_LEFT;
	
		if (!stayOn)
			_player.state = PLAYERSTATE::PLAYER_THROW_AIM;
		if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
			_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
		
	}
	else if ((PI / 180) * 247.6f <= _player.angle && _player.angle <= (PI / 180) * 292.5f)
	{
		_player.direction = PLAYERDIRECTION::UP;
		
		if (!stayOn)
			_player.state = PLAYERSTATE::PLAYER_THROW_AIM;
		if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
			_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
	
	}
	else if ((PI / 180) * 292.6f <= _player.angle && _player.angle <= (PI / 180) * 337.5f)
	{
		_player.direction = PLAYERDIRECTION::UP_RIGHT;
		
		if (!stayOn)
			_player.state = PLAYERSTATE::PLAYER_THROW_AIM;
		if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
			_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
	
	}
	else
	{
		_player.direction = PLAYERDIRECTION::RIGHT;
		
		if (!stayOn)
			_player.state = PLAYERSTATE::PLAYER_THROW_AIM;
		if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
			_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
		
	}
}

void player::playerAniName(string playerName, string aniName)
{
	_player.motion = KEYANIMANAGER->findAnimation(playerName, aniName);
	_player.motion->start(false);
}

void player::cbMoveBreak(void * obj)
{
	player* playerBreak = (player*)obj;
	playerBreak->setPlayerState(PLAYERSTATE::PLAYER_IDLE);
}

void player::cbThrowAim(void * obj)
{
	player* playerThrowAim = (player*)obj;
	if(!(playerThrowAim->getPlayerState() == PLAYERSTATE::PLAYER_THROW_1 || playerThrowAim->getPlayerState() == PLAYERSTATE::PLAYER_THROW_2))
	playerThrowAim->setPlayerState(PLAYERSTATE::PLAYER_THROW_HOLD);
}

void player::cbAttack(void * obj)
{
	player* playerAttack = (player*)obj;

	if (playerAttack->getIsThorowAttack() == true)
	{
		playerAttack->setIsThrowAttack(false);
	}
	else
	{
		playerAttack->setIsAttack(false);
	}

	playerAttack->setEffectPlay(false);
	playerAttack->setPlayerState(PLAYERSTATE::PLAYER_IDLE);
}
