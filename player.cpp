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
	_player.bullet = new playerBullet;
	_player.bullet->init("bullet", 1000, 500);
	_playerUI = new playerUI;
	_playerUI->init();

	_player.effImage = IMAGEMANAGER->findImage("guard");
	_player.image = IMAGEMANAGER->findImage("leaMove");
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_player.speed = PLAYERSPEED;
	_player.angle = PI / 180;
	_player.alphaValue = 1;
	_player.level = 1;
	_player.HP = 230;
	_player.maxHP = 230;
	_player.direction = PLAYERDIRECTION::DOWN;
	_player.state = PLAYERSTATE::PLAYER_IDLE;
	_player.avoidPower = 10;
	_avoidFPS = 0;
	_playerAlphaCount = 0;
	
	_effectPlay = false;
	_isLea = true;
	_isRight = false;
	_isMove = false;
	_isThrowAttack = false;
	_isAvoid = false;
	_isAttacked = false;
	_isCharge = false;
	_isSkill = false;
	_skillMove = false;
	_skillEff = false;
	_effSkillStart = false;

	_effectCount = 0;
	_effectAngle = 0;
	_effPos.x = 0;
	_effPos.y = 0;
	_effSelect = 0;
	_effCount = 0;
	_effSpeed = 10;
	_skillStartPos.x = _player.x;
	_skillStartPos.y = _player.y;
	_effOldTime = GetTickCount();

	_player.rc = { (float)_player.x, (float)_player.y , (float)_player.x + 30, (float)_player.y + 30 };
	_player.attackRc = { (float)_player.x, (float)_player.y, (float)_player.x + 30, (float)_player.y + 30 };
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
	_avoidTime = GetTickCount();
	_avoidEffTime = GetTickCount();
	_moveEffTime = GetTickCount();
	_attackedOldTime = GetTickCount();

	_attackComboCount = 0;

	keyAniInit();
	effectInit();

	_cursor = LoadCursorFromFile("image/cursor/throwAttack.cur");
	_cursor2 = LoadCursorFromFile("image/cursor/attackCursor.cur");
	SetCursor(_cursor);

	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_player.bullet);
}

void player::update()
{
	_playerUI->update();
	_player.bullet->update();	//플레이어 총알 업뎃
	setType();					//플레이어 이미지네임 타입

	if ((!(_player.state == PLAYERSTATE::PLAYER_ATTACKED) && !(_player.state == PLAYERSTATE::PLAYER_TELEPORT)) 
		|| _isAttacked == false)
	{
		if (_playerUI->getPlayerUIMode() == false)
		{
			playerKeyInput();		//방향키 입력
			aimKeyInput();			//공격키 입력
			_attackedOldTime = GetTickCount();
			_player.alphaValue = 1;
		}
	}
	else
	{
		if (GetTickCount() - _attackedOldTime >= 500)
		{
			if (!(_player.state == PLAYERSTATE::PLAYER_TELEPORT))
				_player.state = PLAYERSTATE::PLAYER_IDLE;
		}
		if (GetTickCount() - _attackedOldTime >= 300)
		{
			_isAttacked = false;
		}
	}

	switch (_playerUI->getPlayerAttribute())
	{
	case 0:
		_effSelect = 0;
		break;
	case 1:
		_effSelect = 1;
		break;
	case 2:
		_effSelect = 2;
		break;
	case 3:
		_effSelect = 3;
		break;
	case 4:
		_effSelect = 4;
		break;
	}

	_player.attackRc = { (float)_player.x + 20, (float)_player.y + 20, (float)_player.x + 40, (float)_player.y + 40 };
	playerState();
	_cursorChangeEll = EllipseMake(_player.x + 30, _player.y + 30, 150);
	_attackRangeRc = { (float)_player.x + 30, (float) _player.y + 30, (float)150, (float)150 };
	_player.rc = { (float)_player.x + 15, (float)_player.y + 30 , (float)_player.x + 45, (float)_player.y + 60 };
}

void player::render(bool uiRender)
{
	//D2DMANAGER->fillEllipse(RGB(255, 0, 255), _attackRangeRc);
	_playerUI->render(_player.HP, _player.maxHP, _player.level);
	if (!uiRender)
	{
		if (_player.state == PLAYERSTATE::PLAYER_DEFENSE && (_player.direction == UP || _player.direction == UP_RIGHT || _player.direction == UP_LEFT))
		{
			if (_isRight)
			{
				_player.effImage->aniRender(_player.x + _effPos.x, _player.y + _effPos.y, _player.effAni, 1);
			}
			else
			{
				_player.effImage->aniRenderReverseX(_player.x + _effPos.x, _player.y + _effPos.y, _player.effAni, 1);
			}

		}
		if (_isRight)
		{
			_player.image->aniRender(_player.x, _player.y, _player.motion, _player.alphaValue);
		}
		else
		{
			_player.image->aniRenderReverseX(_player.x, _player.y, _player.motion, _player.alphaValue);
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
		if (_player.state == PLAYERSTATE::PLAYER_DEFENSE && !(_player.direction == UP || _player.direction == UP_RIGHT || _player.direction == UP_LEFT))
		{
			if (_isRight)
			{
				_player.effImage->aniRender(_player.x + _effPos.x, _player.y + _effPos.y, _player.effAni, 1);
			}
			else
			{
				_player.effImage->aniRenderReverseX(_player.x + _effPos.x, _player.y + _effPos.y, _player.effAni, 1);
			}

		}
		//if (_player.state == PLAYERSTATE::PLAYER_TELEPORT)
		//{
		//	_player.effImage->aniRender(_player.x + _effPos.x, _player.y + _effPos.y, _player.effAni, 1);
		//}
		else if (_player.state == PLAYERSTATE::PLAYER_SKILL_FIRE && _skillEff)
		{
			_player.effImage->aniRender(_player.x + _effPos.x, _player.y + _effPos.y, _player.effAni, 1);
		}
	}
	//D2DMANAGER->fillRectangle(RGB(255, 255, 255), _player.attackRc);
	
	
	//WCHAR str[128]; 
	//swprintf_s(str, L"플레이어 상태 : %f", _effSpeed);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 400, CAMERA->getCameraY() + 20, 20, RGB(255, 255, 255));
	//swprintf_s(str, L"플레이어  : %d", _effectFrameY);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 40, 20, RGB(255, 255, 255));
	//swprintf_s(str, L"playerX : %f", _player.x);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 60, 20, RGB(255, 255, 255));
	//swprintf_s(str, L"playerY : %f", _player.y);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 70, 20, RGB(255, 255, 255));
	//for (int i = 0; i < 4; i++)
	//{
	//	swprintf_s(str, L"%d : %d", i , _breakCheck[i]);
	//	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 90 + (i * 20), 20, RGB(255, 255, 255));
	//}
	//D2DMANAGER->drawRectangle(RGB(255,0,255), _player.rc);
	//EFFECTMANAGER->render(0);
}

void player::keyAniInit()
{
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
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimUp", "leaMove", throwAimUp, 2, 6, false, cbThrowAim, this);
	int throwAimUpRight[] = { 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimUpRight", "leaMove", throwAimUpRight, 2, 6, false, cbThrowAim, this);
	int throwAimRight[] = { 44, 45 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimRight", "leaMove", throwAimRight, 2, 6, false, cbThrowAim, this);
	int throwAimDownRight[] = { 60, 61 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimDownRight", "leaMove", throwAimDownRight, 2, 6, false, cbThrowAim, this);
	int throwAimDown[] = { 76, 77 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "throwAimDown", "leaMove", throwAimDown, 2, 6, false, cbThrowAim, this);
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
	//가드
	int guardUp[] = { 89, 90, 91 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "guardUp", "leaMove", guardUp, 3, PLAYERFPS, true);
	int guardUpRight[] = { 105, 106, 107 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "guardUpRight", "leaMove", guardUpRight, 3, PLAYERFPS, true);
	int guardRight[] = { 121, 122, 123 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "guardRight", "leaMove", guardRight, 3, PLAYERFPS, true);
	int guardDownRight[] = { 137, 138, 139 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "guardDownRight", "leaMove", guardDownRight, 3, PLAYERFPS, true);
	int guardDown[] = { 153, 154, 155 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "guardDown", "leaMove", guardDown, 3, PLAYERFPS, true);
	//가드효과
	int guardEffUp[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("eff", "guardEffUp", "guard", guardEffUp, 3, PLAYERFPS, true);
	int guardEffUpRight[] = { 8, 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("eff", "guardEffUpRight", "guard", guardEffUpRight, 3, PLAYERFPS, true);
	int guardEffRight[] = { 16, 17, 18 };
	KEYANIMANAGER->addArrayFrameAnimation("eff", "guardEffRight", "guard", guardEffRight, 3, PLAYERFPS, true);
	int guardEffDownRight[] = { 32, 33, 34 };
	KEYANIMANAGER->addArrayFrameAnimation("eff", "guardEffDownRight", "guard", guardEffDownRight, 3, PLAYERFPS, true);
	int guardEffDown[] = { 40, 41, 42 };
	KEYANIMANAGER->addArrayFrameAnimation("eff", "guardEffDown", "guard", guardEffDown, 3, PLAYERFPS, true);
	//회피
	int avoidLeft[] = { 5, 4, 3, 2, 1, 0, 7, 141, 140};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "avoidLeft", "leaThrow", avoidLeft, 9, PLAYERFPS + 5 + _avoidFPS, false, cbAvoid, this);
	int avoidUpLeft[] = { 6, 5, 4, 3, 2, 0, 6, 137, 136};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "avoidUpLeft", "leaThrow", avoidUpLeft, 9, PLAYERFPS + 5 + _avoidFPS, false, cbAvoid, this);
	int avoidDownLeft[] = { 4, 3, 2, 1, 0, 6, 4, 145, 144} ;
	KEYANIMANAGER->addArrayFrameAnimation("lea", "avoidDownLeft", "leaThrow", avoidDownLeft, 9, PLAYERFPS + 5 + _avoidFPS, false, cbAvoid, this);
	int avoidUpRight[] = { 0, 7, 6, 5, 4, 2, 0, 134, 135};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "avoidUpRight", "leaThrow", avoidUpRight, 9, PLAYERFPS + 5 + _avoidFPS, false, cbAvoid, this);
	int avoidDownRight[] = {2, 1, 0, 7, 6, 4, 2, 142, 143};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "avoidDownRight", "leaThrow", avoidDownRight, 9, PLAYERFPS + 5 + _avoidFPS, false, cbAvoid, this);
	int avoidUp[] = { 7, 6, 5, 4, 2, 1, 7, 130, 131};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "avoidUp", "leaThrow", avoidUp, 9, PLAYERFPS + 5 + _avoidFPS, false, cbAvoid, this);
	int avoidRight[] = { 1, 0, 7, 6, 5, 3, 1, 138, 139};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "avoidRight", "leaThrow", avoidRight, 9, PLAYERFPS + 5 + _avoidFPS, false, cbAvoid, this);
	int avoidDown[] = { 3, 2, 1, 0, 6, 5, 3, 146, 147};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "avoidDown", "leaThrow", avoidDown, 9, PLAYERFPS + 5 + _avoidFPS, false, cbAvoid, this);
	//맞은 상태
	int attackedUp[] = { 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackedUp", "leaMove", attackedUp, 2, PLAYERFPS, true);
	int attackedUpRight[] = { 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackedUpRight", "leaMove", attackedUpRight, 2, PLAYERFPS, true);
	int attackedRight[] = { 46, 47 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackedRight", "leaMove", attackedRight, 2, PLAYERFPS, true);
	int attackedDownRight[] = { 62, 63 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackedDownRight", "leaMove", attackedDownRight, 2, PLAYERFPS, true);
	int attackedDown[] = { 78, 79 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "attackedDown", "leaMove", attackedDown, 2, PLAYERFPS, true);
	//텔레포트 상태
	int teleportDown[] = { 206, 207, 220, 221 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "teleportDown", "leaMove", teleportDown, 4, PLAYERFPS, true);
	//텔포 효과
	int teleportEff[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("eff", "teleportEff", "teleportEff", teleportEff, 11, PLAYERFPS, true);
	//차지
	int chargeUp[] = { 162, 163, 164, 165};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "chargeUp", "leaMove", chargeUp, 4, PLAYERFPS, true);
	int chargeUpRight[] = { 178, 179, 180, 181 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "chargeUpRight", "leaMove", chargeUpRight, 4, PLAYERFPS, true);
	int chargeRight[] = { 194, 195, 196, 197 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "chargeRight", "leaMove", chargeRight, 4, PLAYERFPS, true);
	int chargeDownRight[] = { 210, 211, 212, 213};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "chargeDownRight", "leaMove", chargeDownRight, 4, PLAYERFPS, true);
	int chargeDown[] = { 226, 227, 228, 229 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "chargeDown", "leaMove", chargeDown, 4, PLAYERFPS, true);
	//스킬모션
	int skillMotion[] = { 104, 105, 106, 107, 108, 150, 151, 152, 153, 154, 123, 109, 110, 111, 111, 111,
						112, 113, 114, 104, 105, 106, 107, 108, 151, 155, 152, 153, 156, 152, 153, 154, 157,
						150, 151, 154, 157, 150, 115, 116, 119, 119, 120, 121, 122, 122, 122, 122,
						122, 122, 122, 122, 122, 122, 122, 123, 124, 125, 126, 127, 128, 129, 129, 129, 129, 129, 129 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "skillMotion", "leaThrow", skillMotion, 67, PLAYERFPS, false, cbSkillFire, this);
	//파이어스킬효과
	int fireEff[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("eff", "fireEff", "fire2", fireEff, 8, PLAYERFPS + 5, true);

	_player.effAni = KEYANIMANAGER->findAnimation("eff", "guardEffUp");
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

void player::cbAvoid(void * obj)
{
	player* playerEvasion = (player*)obj;
	playerEvasion->setPlayerState(PLAYERSTATE::PLAYER_IDLE);

	playerEvasion->setIsAvoid(false);
}

void player::cbSkillFire(void * obj)
{
	player* playerSkillFire = (player*)obj;
	playerSkillFire->setPlayerState(PLAYERSTATE::PLAYER_IDLE);
	playerSkillFire->setIsSkill(false);
	playerSkillFire->setIsSkillMove(false);
	playerSkillFire->setSkillEff(false);
	playerSkillFire->setEffSpeed(0);
}
