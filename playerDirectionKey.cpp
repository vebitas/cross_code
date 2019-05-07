#include "stdafx.h"
#include "player.h"

void player::playerKeyInput()
{
	if (!(_isThrowAttack) && !(_isAttack) && !(_isSkill) && !(_isCharge)
		&& !(_player.state == PLAYERSTATE::PLAYER_THROW_AIM) && !(_player.state == PLAYERSTATE::PLAYER_THROW_HOLD_MOVE) && !(_isAvoid))
	{
		//(��������� �ݴ�������� ������ �������� ����ó��)
		if (KEYMANAGER->isStayKeyDown('W') && !(KEYMANAGER->isStayKeyDown('S')))
		{
			_player.direction = PLAYERDIRECTION::UP;
			_player.state = PLAYERSTATE::PLAYER_MOVE;
		}
		if (KEYMANAGER->isOnceKeyUp('W')
			&& !(KEYMANAGER->isStayKeyDown('S')))
		{
			_player.direction = PLAYERDIRECTION::UP;
			_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
			_breakCheck[0]++;
			_oldTime[0] = GetTickCount();
		}
		if (KEYMANAGER->isStayKeyDown('S') && !(KEYMANAGER->isStayKeyDown('W')))
		{
			_player.direction = PLAYERDIRECTION::DOWN;
			_player.state = PLAYERSTATE::PLAYER_MOVE;
		}
		if (KEYMANAGER->isOnceKeyUp('S')
			&& !(KEYMANAGER->isStayKeyDown('W')))
		{
			_player.direction = PLAYERDIRECTION::DOWN;
			_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
			_breakCheck[1]++;
			_oldTime[1] = GetTickCount();
		}
		if (KEYMANAGER->isStayKeyDown('A') && !(KEYMANAGER->isStayKeyDown('D')))
		{
			_player.direction = PLAYERDIRECTION::LEFT;
			_player.state = PLAYERSTATE::PLAYER_MOVE;
		}
		if (KEYMANAGER->isOnceKeyUp('A')
			&& !(KEYMANAGER->isStayKeyDown('D')))
		{
			_player.direction = PLAYERDIRECTION::LEFT;
			_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
			_breakCheck[2]++;
			_oldTime[2] = GetTickCount();
		}
		if (KEYMANAGER->isStayKeyDown('D') && !(KEYMANAGER->isStayKeyDown('A')))
		{
			_player.direction = PLAYERDIRECTION::RIGHT;
			_player.state = PLAYERSTATE::PLAYER_MOVE;
		}
		if (KEYMANAGER->isOnceKeyUp('D')
			&& !(KEYMANAGER->isStayKeyDown('A')))
		{
			_player.direction = PLAYERDIRECTION::RIGHT;
			_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
			_breakCheck[3]++;
			_oldTime[3] = GetTickCount();
		}
		//Ű 2���̻� ������ ��
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
		//�̵� ��ȯ�� �Ҷ� �극��ũ�� �Ȱɰ� �ϱ� ���� ����ó��
		if (KEYMANAGER->isOnceKeyUp('W') && (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D'))
			&& _player.state == PLAYERSTATE::PLAYER_THROW_HOLD_MOVE)
		{
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				_player.direction = PLAYERDIRECTION::LEFT;
				_player.state = PLAYERSTATE::PLAYER_MOVE;
			}
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				_player.direction = PLAYERDIRECTION::RIGHT;
				_player.state = PLAYERSTATE::PLAYER_MOVE;
			}
		}
		else if (KEYMANAGER->isOnceKeyUp('A') && (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S')))
		{
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				_player.direction = PLAYERDIRECTION::UP;
				_player.state = PLAYERSTATE::PLAYER_MOVE;
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				_player.direction = PLAYERDIRECTION::DOWN;
				_player.state = PLAYERSTATE::PLAYER_MOVE;
			}
		}
		else if (KEYMANAGER->isOnceKeyUp('S') && (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D')))
		{
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				_player.direction = PLAYERDIRECTION::LEFT;
				_player.state = PLAYERSTATE::PLAYER_MOVE;
			}
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				_player.direction = PLAYERDIRECTION::RIGHT;
				_player.state = PLAYERSTATE::PLAYER_MOVE;
			}
		}
		else if (KEYMANAGER->isOnceKeyUp('D') && (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S')))
		{
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				_player.direction = PLAYERDIRECTION::UP;
				_player.state = PLAYERSTATE::PLAYER_MOVE;
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				_player.direction = PLAYERDIRECTION::DOWN;
				_player.state = PLAYERSTATE::PLAYER_MOVE;
			}
		}
		//�̵� ��ȯ�� �Ҷ� �극��ũ�� �Ȱɰ� �ϱ� ���� ����ó�� (�������)

		
		if (_isAvoid)
		{
			_breakCheck[0] = 0;
			_breakCheck[1] = 0;
			_breakCheck[2] = 0;
			_breakCheck[3] = 0;
		}

		if (_breakCheck[0] == 1 && _breakCheck[3] == 1)
		{
			_player.direction = PLAYERDIRECTION::UP_RIGHT;
			_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
			_breakCheck[0] = 0;
			_breakCheck[3] = 0;
		}
		if (_breakCheck[1] == 1 && _breakCheck[3] == 1)
		{
			_player.direction = PLAYERDIRECTION::DOWN_RIGHT;
			_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
			_breakCheck[1] = 0;
			_breakCheck[3] = 0;
		}
		if (_breakCheck[1] == 1 && _breakCheck[2] == 1)
		{
			_player.direction = PLAYERDIRECTION::DOWN_LEFT;
			_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
			_breakCheck[1] = 0;
			_breakCheck[2] = 0;
		}
		if (_breakCheck[0] == 1 && _breakCheck[2] == 1)
		{
			_player.direction = PLAYERDIRECTION::UP_LEFT;
			_player.state = PLAYERSTATE::PLAYER_MOVE_BREAK;
			_breakCheck[0] = 0;
			_breakCheck[2] = 0;
		}



		if (GetTickCount() - _oldTime[0] >= 20)
		{
			if (_breakCheck[0] == 1)
				_breakCheck[0]--;
			_oldTime[0] = GetTickCount();
		}
		if (GetTickCount() - _oldTime[1] >= 20)
		{
			if (_breakCheck[1] == 1)
				_breakCheck[1]--;
			_oldTime[1] = GetTickCount();
		}
		if (GetTickCount() - _oldTime[2] >= 20)
		{
			if (_breakCheck[2] == 1)
				_breakCheck[2]--;
			_oldTime[2] = GetTickCount();
		}if (GetTickCount() - _oldTime[3] >= 20)
		{
			if (_breakCheck[3] == 1)
				_breakCheck[3]--;
			_oldTime[3] = GetTickCount();
		}
	}

}