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
		SetCursor(_cursor2);

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !(_isAttack) && !(_isSkill) && !(_isCharge))
		{
			if (GetTickCount() - _attackTimeKeyUp >= 250)
			{
				EFFECTMANAGER->play("circle", _player.x + 30, _player.y + 30);
				_effectPlay = true;
				_attackComboTime = GetTickCount();
				if (_attackComboCount == 0)
				{
					SOUNDMANAGER->play("sweep1", 1);
					_player.state = PLAYERSTATE::PLAYER_ATTACK_COMBO_1;
				}
				else if (_attackComboCount == 1)
				{
					SOUNDMANAGER->play("sweep2", 1);
					_player.state = PLAYERSTATE::PLAYER_ATTACK_COMBO_2;
				}
				else if (_attackComboCount == 2)
				{
					SOUNDMANAGER->play("sweep3", 1);
					_player.state = PLAYERSTATE::PLAYER_ATTACK_COMBO_1;
				}
				else if (_attackComboCount == 3)
				{
					SOUNDMANAGER->play("sweep4", 1);
					_player.state = PLAYERSTATE::PLAYER_ATTACK_COMBO_FINISH;
				}

				_attackComboCount++;
				_attackTimeKeyUp = GetTickCount();
			}
		}
	}
	else 
	{
		SetCursor(_cursor);
		if (!(_isSkill) && !(_isCharge))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !(_isThrowAttack))
			{
				if (GetTickCount() - _attackTimeKeyUp >= 200)
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
					_player.angle = getAngle2(_player.x + 30, _player.y + 15, _ptMouse.x, _ptMouse.y);

					if ((PI / 180) * 22.6f <= _player.angle &&_player.angle <= (PI / 180) * 67.5f)
					{
						_player.direction = PLAYERDIRECTION::DOWN_RIGHT;
						_player.angle = 315;
					}
					else if ((PI / 180) * 67.6f <= _player.angle && _player.angle <= (PI / 180) * 112.5f)
					{
						_player.direction = PLAYERDIRECTION::DOWN;
						_player.angle = 180;
					}
					else if ((PI / 180) * 112.6f <= _player.angle && _player.angle <= (PI / 180) * 157.5f)
					{
						_player.direction = PLAYERDIRECTION::DOWN_LEFT;
						_player.angle = 225;
					}
					else if ((PI / 180) * 157.6f <= _player.angle && _player.angle <= (PI / 180) * 202.5f)
					{
						_player.direction = PLAYERDIRECTION::LEFT;
						_player.angle = 90;
					}
					else if ((PI / 180) * 202.6f <= _player.angle && _player.angle <= (PI / 180) * 247.5f)
					{
						_player.direction = PLAYERDIRECTION::UP_LEFT;
						_player.angle = 135;
					}
					else if ((PI / 180) * 247.6f <= _player.angle && _player.angle <= (PI / 180) * 292.5f)
					{
						_player.direction = PLAYERDIRECTION::UP;
						_player.angle = 180;
					}
					else if ((PI / 180) * 292.6f <= _player.angle && _player.angle <= (PI / 180) * 337.5f)
					{
						_player.direction = PLAYERDIRECTION::UP_RIGHT;
						_player.angle = 45;
					}
					else
					{
						_player.direction = PLAYERDIRECTION::RIGHT;
						_player.angle = 90;
					}

					if (!(_player.state == PLAYERSTATE::PLAYER_THROW_HOLD || _player.state == PLAYERSTATE::PLAYER_THROW_HOLD_MOVE))
						_player.bullet->bulletFire(_player.x + 15, _player.y + 20, getAngle(_player.x + 30, _player.y + 30, _ptMouse.x + 10, _ptMouse.y + 5), _player.angle, 10, false);
					else
						_player.bullet->bulletFire(_player.x + 15, _player.y + 20, getAngle(_player.x + 30, _player.y + 30, _ptMouse.x + 10, _ptMouse.y + 5), _player.angle, 10, true);

					if (_throwCount == 0)
					{
						_player.state = PLAYERSTATE::PLAYER_THROW_1;
						_throwCount++;
						SOUNDMANAGER->play("throw1", 1);
					}
					else
					{
						_player.state = PLAYERSTATE::PLAYER_THROW_2;
						_throwCount--;
						SOUNDMANAGER->play("throw2", 1);
					}
					_attackTimeKeyUp = GetTickCount();
				}
				if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD_MOVE)
				{
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD_MOVE;
				}
				else if (_player.state == PLAYERSTATE::PLAYER_THROW_HOLD)
				{
					_player.state = PLAYERSTATE::PLAYER_THROW_HOLD;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//누를때마다 회피 속도 줄여주고 FPS는 증가 하지만 제대로 작동하지않음 ㅠㅠ
		if (GetTickCount() - _avoidTime >= 500)
		{
			_avoidTime = GetTickCount();
			_avoidFPS = 0;
			_player.avoidPower = 10;
		}
		else if (GetTickCount() - _avoidTime >= 400)
		{
			_avoidTime = GetTickCount();
			_avoidFPS = 2;
			_player.avoidPower = 8;
		}
		else if (GetTickCount() - _avoidTime >= 300)
		{
			_avoidTime = GetTickCount();
			_avoidFPS = 4;
			_player.avoidPower = 6;
		}
		else if (GetTickCount() - _avoidTime >= 250)
		{
			_avoidTime = GetTickCount();
			_avoidFPS = 6;
			_player.avoidPower = 4;
		}
		else
		{
			_avoidFPS = 8;
			_player.avoidPower = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		if(!(_player.state == PLAYERSTATE::PLAYER_AVOID))
		_player.state = PLAYERSTATE::PLAYER_DEFENSE;

		if (_player.state == PLAYERSTATE::PLAYER_DEFENSE)
		{
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
		}
	}

		if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			_player.direction = PLAYERDIRECTION::UP;
			_player.state = PLAYERSTATE::PLAYER_AVOID;
		}
		if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			_player.direction = PLAYERDIRECTION::DOWN;
			_player.state = PLAYERSTATE::PLAYER_AVOID;
		}
		if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			_player.direction = PLAYERDIRECTION::LEFT;
			_player.state = PLAYERSTATE::PLAYER_AVOID;
		}
		if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			_player.direction = PLAYERDIRECTION::RIGHT;
			_player.state = PLAYERSTATE::PLAYER_AVOID;
		}
		if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			_player.direction = PLAYERDIRECTION::UP_RIGHT;
			_player.state = PLAYERSTATE::PLAYER_AVOID;
		}
		if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			_player.direction = PLAYERDIRECTION::DOWN_RIGHT;
			_player.state = PLAYERSTATE::PLAYER_AVOID;
		}
		if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			_player.direction = PLAYERDIRECTION::UP_LEFT;
			_player.state = PLAYERSTATE::PLAYER_AVOID;
		}
		if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			_player.direction = PLAYERDIRECTION::DOWN_LEFT;
			_player.state = PLAYERSTATE::PLAYER_AVOID;
		}

	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON) && _player.state == PLAYERSTATE::PLAYER_DEFENSE)
	{
		_player.state = PLAYERSTATE::PLAYER_IDLE;
	}

	if (!_isSkill)
	{
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			_player.state = PLAYERSTATE::PLAYER_CHARGE;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
		{
			_player.state = PLAYERSTATE::PLAYER_IDLE;
			_isCharge = false;
			_effectPlay = true;
			_player.state = PLAYERSTATE::PLAYER_SKILL_FIRE;
		}
	}
}