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
	_player.image = IMAGEMANAGER->findImage("leaMove");
	_player.x = GAMESIZEX / 2;
	_player.y = GAMESIZEY / 2;
	_player.speed = PLAYERSPEED;
	_player.alphaValue = 1;
	_player.direction = PLAYERDIRECTION::DOWN;
	_player.state = PLAYERSTATE::PLAYER_IDLE;

	_isLea = true;
	_isRight = false;

	keyAniInit();


	return S_OK;
}

void player::release()
{
}

void player::update()
{
	setType();
	playerKeyInput();
	playerState();
}

void player::render()
{
	if (_isRight)
	{
		_player.image->aniRender(_player.x, _player.y, _player.motion);
	}
	else
	{
		_player.image->aniRenderReverseX(_player.x, _player.y, _player.motion);
	}

	WCHAR str[128]; 
	swprintf_s(str, L"플레이어 상태 : %d", _player.state);
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 20, 20, RGB(0, 0, 0));
	swprintf_s(str, L"플레이어  : %d", _player.direction);
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 40, 20, RGB(0, 0, 0));
	swprintf_s(str, L"playerX : %f", _player.x);
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 60, 20, RGB(0, 0, 0));
	swprintf_s(str, L"playerY : %f", _player.y);
	D2DMANAGER->drawText(str, CAMERA->getCameraX() + 200, CAMERA->getCameraY() + 70, 20, RGB(0, 0, 0));
}

void player::keyAniInit()
{
	KEYANIMANAGER->deleteAll();
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
	int moveBreakUp[] = {9, 10, 11};
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakUp", "leaMove", moveBreakUp, 3, PLAYERFPS, false, cbMoveBreak, this);
	int moveBreakUpRight[] = { 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakUpRight", "leaMove", moveBreakUpRight, 3, PLAYERFPS, false, cbMoveBreak, this);
	int moveBreakRight[] = { 41, 42, 43 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakRight", "leaMove", moveBreakRight, 3, PLAYERFPS, false, cbMoveBreak, this);
	int moveBreakDownRight[] = { 57, 58, 59 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakDownRight", "leaMove", moveBreakDownRight, 3, PLAYERFPS, false, cbMoveBreak, this);
	int moveBreakDown[] = { 73, 74, 75 };
	KEYANIMANAGER->addArrayFrameAnimation("lea", "moveBreakDown", "leaMove", moveBreakDown, 3, PLAYERFPS, false, cbMoveBreak, this);

	_player.motion = KEYANIMANAGER->findAnimation("lea", "idleDown");

}

void player::playerKeyInput()
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_player.direction = PLAYERDIRECTION::UP;
		_player.state = PLAYERSTATE::PLAYER_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_player.direction = PLAYERDIRECTION::DOWN;
		_player.state = PLAYERSTATE::PLAYER_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_player.direction = PLAYERDIRECTION::LEFT;
		_player.state = PLAYERSTATE::PLAYER_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_player.direction = PLAYERDIRECTION::RIGHT;
		_player.state = PLAYERSTATE::PLAYER_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('D'))
	{
		_player.direction = PLAYERDIRECTION::UP_RIGHT;
		_player.state = PLAYERSTATE::PLAYER_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('A'))
	{
		_player.direction = PLAYERDIRECTION::UP_LEFT;
		_player.state = PLAYERSTATE::PLAYER_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S'))
	{
		_player.direction = PLAYERDIRECTION::DOWN_RIGHT;
		_player.state = PLAYERSTATE::PLAYER_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A'))
	{
		_player.direction = PLAYERDIRECTION::DOWN_LEFT;
		_player.state = PLAYERSTATE::PLAYER_MOVE;
	}
	//if (KEYMANAGER->isOnceKeyUp('W'))
	//{
	//		_player.direction = PLAYERDIRECTION::UP;
	//	_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
	//}
	//if (KEYMANAGER->isOnceKeyUp('S'))
	//{
	//		_player.direction = PLAYERDIRECTION::DOWN;
	//	_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
	//}
	//if (KEYMANAGER->isOnceKeyUp('A'))
	//{
	//	_player.direction = PLAYERDIRECTION::LEFT;
	//	_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
	//}
	//if (KEYMANAGER->isOnceKeyUp('D'))
	//{
	//	_player.direction = PLAYERDIRECTION::RIGHT;
	//	_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
	//}
}

void player::playerState()
{
	switch (_player.state)
	{
	case PLAYERSTATE::PLAYER_IDLE:
		switch (_player.direction)
		{
			case PLAYERDIRECTION::DOWN:
				_isRight = true;
				playerAniName("lea", "idleDown");
				break;
			case PLAYERDIRECTION::DOWN_LEFT:
				_isRight = false;
				playerAniName("lea", "idleDownRight");
				break;
			case PLAYERDIRECTION::DOWN_RIGHT:
				_isRight = true;
				playerAniName("lea", "idleDownRight");
				break;
			case PLAYERDIRECTION::LEFT:
				_isRight = false;
				playerAniName("lea", "idleRight");
				break;
			case PLAYERDIRECTION::RIGHT:
				_isRight = true;
				playerAniName("lea", "idleRight");
				break;
			case PLAYERDIRECTION::UP:
				_isRight = true;
				playerAniName("lea", "idleUp");
				break;
			case PLAYERDIRECTION::UP_LEFT:
				_isRight = false;
				playerAniName("lea", "idleUpRight");
				break;
			case PLAYERDIRECTION::UP_RIGHT:
				_isRight = true;
				playerAniName("lea", "idleUpRight");
				break;
		}
		break;
	case PLAYERSTATE::PLAYER_MOVE:
		switch (_player.direction)
		{
			case PLAYERDIRECTION::DOWN:
				_isRight = true;
				_player.speed = PLAYERSPEED;
				_player.y += _player.speed;
				playerAniName("lea", "moveDown");
				break;
			case PLAYERDIRECTION::DOWN_LEFT:
				_isRight = false;
				_player.speed = PLAYERSPEED;
				_player.x -= _player.speed;
				_player.y += _player.speed;
				playerAniName("lea", "moveDownRight");
				break;
			case PLAYERDIRECTION::DOWN_RIGHT:
				_isRight = true;
				_player.speed = PLAYERSPEED;
				_player.x += _player.speed;
				_player.y += _player.speed;
				playerAniName("lea", "moveDownRight");
				break;
			case PLAYERDIRECTION::LEFT:
				_isRight = false;
				_player.speed = PLAYERSPEED;
				_player.x -= _player.speed;
				playerAniName("lea", "moveRight");
				break;
			case PLAYERDIRECTION::RIGHT:
				_isRight = true;
				_player.speed = PLAYERSPEED;
				_player.x += _player.speed;
				playerAniName("lea", "moveRight");
				break;
			case PLAYERDIRECTION::UP:
				_isRight = true;
				_player.speed = PLAYERSPEED;
				_player.y -= _player.speed;
				playerAniName("lea", "moveUp");
				break;
			case PLAYERDIRECTION::UP_LEFT:
				_isRight = false;
				_player.speed = PLAYERSPEED;
				_player.x -= _player.speed;
				_player.y -= _player.speed;
				playerAniName("lea", "moveUpRight");
				break;
			case PLAYERDIRECTION::UP_RIGHT:
				_isRight = true;
				_player.speed = PLAYERSPEED;
				_player.x += _player.speed;
				_player.y -= _player.speed;
				playerAniName("lea", "moveUpRight");
				break;
		}
		break;
	case PLAYERSTATE::PLAYER_MOVE_BREAK:
		switch (_player.direction)
		{
			case PLAYERDIRECTION::DOWN:
				_isRight = true;
				if (_player.speed >= 0)
					_player.speed -= 0.3;
				else
					_player.speed = 0;
				_player.y += _player.speed;
				playerAniName("lea", "moveBreakDown");
				break;
			case PLAYERDIRECTION::DOWN_LEFT:
				_isRight = false;
				if (_player.speed >= 0)
					_player.speed -= 0.3;
				else
					_player.speed = 0;
				_player.x -= _player.speed;
				_player.y += _player.speed;
				playerAniName("lea", "moveBreakDownRight");
				break;
			case PLAYERDIRECTION::DOWN_RIGHT:
				_isRight = true;
				if (_player.speed >= 0)
					_player.speed -= 0.3;
				else
					_player.speed = 0;
				_player.x += _player.speed;
				_player.y += _player.speed;
				playerAniName("lea", "moveBreakDownRight");
				break;
			case PLAYERDIRECTION::LEFT:
				_isRight = false;
				if (_player.speed >= 0)
					_player.speed -= 0.3;
				else
					_player.speed = 0;
				_player.x -= _player.speed;
				playerAniName("lea", "moveBreakRight");
				break;
			case PLAYERDIRECTION::RIGHT:
				_isRight = true;
				if (_player.speed >= 0)
					_player.speed -= 0.3;
				else
					_player.speed = 0;
				_player.x += _player.speed;
				playerAniName("lea", "moveBreakRight");
				break;
			case PLAYERDIRECTION::UP:
				_isRight = true;
				if (_player.speed >= 0)
					_player.speed -= 0.3;
				else
					_player.speed = 0;
				_player.y -= _player.speed;
				playerAniName("lea", "moveBreakUp");
				break;
			case PLAYERDIRECTION::UP_LEFT:
				_isRight = false;
				if (_player.speed >= 0)
					_player.speed -= 0.3;
				else
					_player.speed = 0;
				_player.x -= _player.speed;
				_player.y -= _player.speed;
				playerAniName("lea", "moveBreakUpRight");
				break;
			case PLAYERDIRECTION::UP_RIGHT:
				_isRight = true;
				if (_player.speed >= 0)
					_player.speed -= 0.3;
				else
					_player.speed = 0;
				_player.x += _player.speed;
				_player.y -= _player.speed;
				playerAniName("lea", "moveBreakUpRight");
				break;
		}
		break;
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

void player::playerAniName(string playerName, string aniName)
{
	_player.motion = KEYANIMANAGER->findAnimation(playerName, aniName);
	_player.motion->start();
}

void player::cbMoveBreak(void * obj)
{
	player* playerBreak = (player*)obj;
	playerBreak->setPlayerState(PLAYERSTATE::PLAYER_IDLE);
}
