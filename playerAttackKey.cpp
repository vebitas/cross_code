#include "stdafx.h"
#include "player.h"

void player::aimKeyInput()
{
	if (GetTickCount() - _attackComboTime >= 500 || _attackComboCount >= 4)
	{
		_attackComboCount = 0;
	}

	if(PtInEllipse(_cursorChangeEll, _ptMouse.x, _ptMouse.y) 
		&& !(_player.state == PLAYERSTATE::PLAYER_THROW_HOLD) && !(_player.state == PLAYERSTATE::PLAYER_THROW_HOLD_MOVE))
	{
		_cursor = LoadCursorFromFile("image/cursor/attackCursor.cur");
		SetCursor(_cursor);

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !(_isAttack))
		{
			EFFECTMANAGER->play("circle", _player.x + 30, _player.y+ 30);
			_effectPlay = true;
			_attackComboTime = GetTickCount();
			if(_attackComboCount == 0)
				_player.state = PLAYERSTATE::PLAYER_ATTACK_COMBO_1;
			else if(_attackComboCount == 1)
				_player.state = PLAYERSTATE::PLAYER_ATTACK_COMBO_2;
			else if (_attackComboCount == 2)
				_player.state = PLAYERSTATE::PLAYER_ATTACK_COMBO_1;
			else if (_attackComboCount == 3)
				_player.state = PLAYERSTATE::PLAYER_ATTACK_COMBO_FINISH;

			_attackComboCount++;
		}
	}
	else 
	{
		_cursor = LoadCursorFromFile("image/cursor/throwAttack.cur");
		SetCursor(_cursor);

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !(_isThrowAttack))
		{
			if (GetTickCount() - _attackTimeKeyUp >= 300)
			{
				attackAngle(false);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !(_player.state == PLAYERSTATE::PLAYER_THROW_AIM))
		{
			if (_player.state == PLAYER_THROW_HOLD_MOVE)
			{
				_player.state == PLAYER_THROW_HOLD_MOVE;
			}
			else if (_player.state == PLAYER_THROW_HOLD)
			{
				_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
			}
				attackAngle(true);

			if (!(_isThrowAttack))
			{
				if (KEYMANAGER->isStayKeyDown('W'))
				{
					_player.angle = (PI / 180) * 90;
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
				}
				if (KEYMANAGER->isStayKeyDown('S'))
				{
					_player.angle = (PI / 180) * 270;
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
				}
				if (KEYMANAGER->isStayKeyDown('A'))
				{
					_player.angle = (PI / 180) * 180;
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
				}
				if (KEYMANAGER->isStayKeyDown('D'))
				{
					_player.angle = 0;
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
				}
				if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('D'))
				{
					_player.angle = (PI / 180) * 45;
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
				}
				if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('A'))
				{
					_player.angle = (PI / 180) * 135;
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
				}
				if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A'))
				{
					_player.angle = (PI / 180) * 225;
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
				}
				if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('D'))
				{
					_player.angle = (PI / 180) * 315;
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
				}
				if (KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
				{
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (GetTickCount() - _attackTimeKeyUp >= 300)
			{

				_player.bullet->bulletFire(_player.x + 20, _player.y + 20, getAngle(_player.x, _player.y, _ptMouse.x, _ptMouse.y), 13);
				_player.angle = getAngle2(_player.x + 30, _player.y + 15, _ptMouse.x, _ptMouse.y);
				
				if ((PI / 180) * 22.6f <= _player.angle &&_player.angle <= (PI / 180) * 67.5f)
					_player.direction = PLAYERDIRECTION::DOWN_RIGHT;
				else if ((PI / 180) * 67.6f <= _player.angle && _player.angle <= (PI / 180) * 112.5f)
					_player.direction = PLAYERDIRECTION::DOWN;
				else if ((PI / 180) * 112.6f <= _player.angle && _player.angle <= (PI / 180) * 157.5f)
					_player.direction = PLAYERDIRECTION::DOWN_LEFT;
				else if ((PI / 180) * 157.6f <= _player.angle && _player.angle <= (PI / 180) * 202.5f)
					_player.direction = PLAYERDIRECTION::LEFT;
				else if ((PI / 180) * 202.6f <= _player.angle && _player.angle <= (PI / 180) * 247.5f)
					_player.direction = PLAYERDIRECTION::UP_LEFT;
				else if ((PI / 180) * 247.6f <= _player.angle && _player.angle <= (PI / 180) * 292.5f)
					_player.direction = PLAYERDIRECTION::UP;
				else if ((PI / 180) * 292.6f <= _player.angle && _player.angle <= (PI / 180) * 337.5f)
					_player.direction = PLAYERDIRECTION::UP_RIGHT;
				else
					_player.direction = PLAYERDIRECTION::RIGHT;

				if (_throwCount == 0)
				{
					_player.state = PLAYERSTATE::PLAYER_THROW_1;
					_throwCount++;
				}
				else
				{
					_player.state = PLAYERSTATE::PLAYER_THROW_2;
					_throwCount--;
				}
				_attackTimeKeyUp = GetTickCount();
			}
			if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD_MOVE)
			{
				_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
			}
			else if(_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
			{
				_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
			}
		}

	}
	
}