#include "stdafx.h"
#include "player.h"

void player::playerState()
{
	switch (_player.state)
	{
	case PLAYERSTATE::PLAYER_IDLE:
		_isAttack = false;
		_isThrowAttack = false;
		_player.image = IMAGEMANAGER->findImage("leaMove");
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
		_isAttack = false;
		_isThrowAttack = false;
		_player.image = IMAGEMANAGER->findImage("leaMove");
		if (GetTickCount() - _moveEffTime >= 150)
		{
			_moveEffTime = GetTickCount();
			EFFECTMANAGER->play("moveEff", _player.x + 30, _player.y + 35);
		}
		_isMove = true;
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			_player.speed = PLAYERSPEED;
			_player.angle = (PI / 180 * 270);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			_player.speed = PLAYERSPEED;
			_player.angle = (PI / 180 * 225);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			_player.speed = PLAYERSPEED;
			_player.angle = (PI / 180 * 315);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			_player.speed = PLAYERSPEED;
			_player.angle = (PI / 180 * 180);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			_player.speed = PLAYERSPEED;
			_player.angle = (PI / 180 * 0);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			_player.speed = PLAYERSPEED;
			_player.angle = (PI / 180 * 90);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			_player.speed = PLAYERSPEED;
			_player.angle = (PI / 180 * 135);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			_player.speed = PLAYERSPEED;
			_player.angle = (PI / 180 * 45);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_MOVE_BREAK:
		_isAttack = false;
		_isThrowAttack = false;
		_player.image = IMAGEMANAGER->findImage("leaMove");
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			if (_player.speed >= 0)
				_player.speed -= 0.3;
			else
				_player.speed = 0;
			_player.angle = (PI / 180 * 270);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveBreakDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			if (_player.speed >= 0)
				_player.speed -= 0.3;
			else
				_player.speed = 0;
			_player.angle = (PI / 180 * 225);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveBreakDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			if (_player.speed >= 0)
				_player.speed -= 0.3;
			else
				_player.speed = 0;
			_player.angle = (PI / 180 * 315);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveBreakDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			if (_player.speed >= 0)
				_player.speed -= 0.3;
			else
				_player.speed = 0;
			_player.angle = (PI / 180 * 180);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveBreakRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			if (_player.speed >= 0)
				_player.speed -= 0.3;
			else
				_player.speed = 0;
			_player.angle = (PI / 180 * 0);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveBreakRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			if (_player.speed >= 0)
				_player.speed -= 0.3;
			else
				_player.speed = 0;
			_player.angle = (PI / 180 * 90);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveBreakUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			if (_player.speed >= 0)
				_player.speed -= 0.3;
			else
				_player.speed = 0;
			_player.angle = (PI / 180 * 135);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveBreakUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			if (_player.speed >= 0)
				_player.speed -= 0.3;
			else
				_player.speed = 0;
			_player.angle = (PI / 180 * 45);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "moveBreakUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_THROW_AIM:
		_isAttack = false;
		_isThrowAttack = false;
		_player.image = IMAGEMANAGER->findImage("leaMove");
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			playerAniName("lea", "throwAimDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			playerAniName("lea", "throwAimDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			playerAniName("lea", "throwAimDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			playerAniName("lea", "throwAimRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			playerAniName("lea", "throwAimRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			playerAniName("lea", "throwAimUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			playerAniName("lea", "throwAimUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			playerAniName("lea", "throwAimUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_THROW_HOLD:
		_isAttack = false;
		_isThrowAttack = false;
		_player.image = IMAGEMANAGER->findImage("leaMove");
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			playerAniName("lea", "throwHoldDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			playerAniName("lea", "throwHoldDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			playerAniName("lea", "throwHoldDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			playerAniName("lea", "throwHoldRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			playerAniName("lea", "throwHoldRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			playerAniName("lea", "throwHoldUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			playerAniName("lea", "throwHoldUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			playerAniName("lea", "throwHoldUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_THROW_HOLD_MOVE:
		_isAttack = false;
		_isThrowAttack = false;
		_player.image = IMAGEMANAGER->findImage("leaMove");
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			_player.speed = PLAYERSPEED / 2;
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "throwHoldMoveDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			_player.speed = PLAYERSPEED / 2;
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "throwHoldMoveDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			_player.speed = PLAYERSPEED / 2;
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "throwHoldMoveDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			_player.speed = PLAYERSPEED / 2;
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "throwHoldMoveRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			_player.speed = PLAYERSPEED / 2;
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "throwHoldMoveRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			_player.speed = PLAYERSPEED / 2;
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "throwHoldMoveUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			_player.speed = PLAYERSPEED / 2;
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "throwHoldMoveUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			_player.speed = PLAYERSPEED / 2;
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			playerAniName("lea", "throwHoldMoveUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_THROW_1:
		_isAttack = false;
		_isThrowAttack = true;
		_player.image = IMAGEMANAGER->findImage("leaThrow");
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			playerAniName("lea", "throwDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = true;
			playerAniName("lea", "throwDownLeft");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			playerAniName("lea", "throwDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = true;
			playerAniName("lea", "throwLeft");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			playerAniName("lea", "throwRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			playerAniName("lea", "throwUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = true;
			playerAniName("lea", "throwUpLeft");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			playerAniName("lea", "throwUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_THROW_2:
		_player.image = IMAGEMANAGER->findImage("leaThrow");
		_isAttack = false;
		_isThrowAttack = true;
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = false;
			playerAniName("lea", "throwDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			playerAniName("lea", "throwDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = false;
			playerAniName("lea", "throwDownLeft");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			playerAniName("lea", "throwRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = false;
			playerAniName("lea", "throwLeft");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = false;
			playerAniName("lea", "throwUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			playerAniName("lea", "throwUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = false;
			playerAniName("lea", "throwUpLeft");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_ATTACK_COMBO_1:
		_isAttack = true;
		_isThrowAttack = false;
		_effCopy = false;
		_player.image = IMAGEMANAGER->findImage("leaThrow");
		if(_effSelect == 0)
			_effect = IMAGEMANAGER->findImage("attackNormalR");
		else if (_effSelect == 1)
			_effect = IMAGEMANAGER->findImage("attackFireR");
		else if (_effSelect == 2)
			_effect = IMAGEMANAGER->findImage("attackIceR");
		else if (_effSelect == 3)
			_effect = IMAGEMANAGER->findImage("attackSpakeR");
		else if (_effSelect == 4)
			_effect = IMAGEMANAGER->findImage("attackWaveR");
		effectUpdate(4, 2 , 2);
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = false;
			_effPos.x = -20;
			_effPos.y = 0;
			_effectAngle = 180;
			_player.attackRc = { (float)_player.x , (float)_player.y + 40, (float)_player.x + 65, (float)_player.y + 75 };
			playerAniName("lea", "attackDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			_effPos.x = -35;
			_effPos.y = 0;
			_effectAngle = 225;
			_player.attackRc = { (float)_player.x - 20, (float)_player.y, (float)_player.x + 40, (float)_player.y + 75 };
			playerAniName("lea", "attackDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = false;
			_effPos.x = -5;
			_effPos.y = 0;
			_effectAngle = 135;
			_player.attackRc = { (float)_player.x + 20, (float)_player.y, (float)_player.x + 85, (float)_player.y + 75 };
			playerAniName("lea", "attackDownLeft");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			_effPos.x = -40;
			_effPos.y = 0;
			_effectAngle = 270;
			_player.attackRc = { (float)_player.x - 20, (float)_player.y, (float)_player.x + 40, (float)_player.y + 75 };
			playerAniName("lea", "attackRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = false;
			_effPos.x = 0;
			_effPos.y = 0;
			_effectAngle = 90;
			_player.attackRc = { (float)_player.x + 20, (float)_player.y, (float)_player.x + 85, (float)_player.y + 75 };
			playerAniName("lea", "attackLeft");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = false;
			_effPos.x = -20;
			_effPos.y = -20;
			_effectAngle = 0;
			_player.attackRc = { (float)_player.x , (float)_player.y - 20, (float)_player.x + 65, (float)_player.y + 15 };
			playerAniName("lea", "attackUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			_effPos.x = -30;
			_effPos.y = -20;
			_effectAngle = 315;
			_player.attackRc = { (float)_player.x - 20, (float)_player.y - 20, (float)_player.x + 40, (float)_player.y + 55 };
			playerAniName("lea", "attackUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = false;
			_effPos.x = -5;
			_effPos.y = -15;
			_effectAngle = 45;
			_player.attackRc = { (float)_player.x + 20, (float)_player.y - 20, (float)_player.x + 85, (float)_player.y + 55 };
			playerAniName("lea", "attackUpLeft");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_ATTACK_COMBO_2:
		_isAttack = true;
		_isThrowAttack = false;
		_effCopy = false;
		_player.image = IMAGEMANAGER->findImage("leaThrow");
		if (_effSelect == 0)
			_effect = IMAGEMANAGER->findImage("attackNormal");
		else if (_effSelect == 1)
			_effect = IMAGEMANAGER->findImage("attackFire");
		else if (_effSelect == 2)
			_effect = IMAGEMANAGER->findImage("attackIce");
		else if (_effSelect == 3)
			_effect = IMAGEMANAGER->findImage("attackSpake");
		else if (_effSelect == 4)
			_effect = IMAGEMANAGER->findImage("attackWave");
		effectUpdate(4, 2, 2);
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			_effPos.x = -20;
			_effPos.y = 0;
			_effectAngle = 180;
			_player.attackRc = { (float)_player.x , (float)_player.y + 40, (float)_player.x + 65, (float)_player.y + 75 };
			playerAniName("lea", "attackDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = true;
			_effPos.x = -35;
			_effPos.y = 0;
			_effectAngle = 225;
			_player.attackRc = { (float)_player.x - 20, (float)_player.y, (float)_player.x + 40, (float)_player.y + 75 };
			playerAniName("lea", "attackDownLeft");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			_effectAngle = 135;
			_effPos.x = -5;
			_effPos.y = 0;
			_player.attackRc = { (float)_player.x + 20, (float)_player.y, (float)_player.x + 85, (float)_player.y + 75 };
			playerAniName("lea", "attackDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = true;
			_effPos.x = -40;
			_effPos.y = 0;
			_effectAngle = 270;
			_player.attackRc = { (float)_player.x - 20, (float)_player.y, (float)_player.x + 40, (float)_player.y + 75 };
			playerAniName("lea", "attackLeft");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			_effPos.x = 0;
			_effPos.y = 0;
			_effectAngle = 90;
			_player.attackRc = { (float)_player.x + 20, (float)_player.y, (float)_player.x + 85, (float)_player.y + 75 };
			playerAniName("lea", "attackRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			_effPos.x = -20;
			_effPos.y = -20;
			_effectAngle = 0;
			_player.attackRc = { (float)_player.x , (float)_player.y - 20, (float)_player.x + 65, (float)_player.y + 15 };
			playerAniName("lea", "attackUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = true;
			_effPos.x = -30;
			_effPos.y = -20;
			_effectAngle = 315;
			_player.attackRc = { (float)_player.x - 20, (float)_player.y - 20, (float)_player.x + 40, (float)_player.y + 55 };
			playerAniName("lea", "attackUpLeft");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			_effPos.x = -5;
			_effPos.y = -15;
			_effectAngle = 45;
			_player.attackRc = { (float)_player.x + 20, (float)_player.y - 20, (float)_player.x + 85, (float)_player.y + 55 };
			playerAniName("lea", "attackUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_ATTACK_COMBO_FINISH:
		_isAttack = true;
		_isThrowAttack = false;
		_effCopy = true;
		_player.image = IMAGEMANAGER->findImage("leaThrow");
		if (_effSelect == 0)
			_effect = IMAGEMANAGER->findImage("attackNormal");
		else if (_effSelect == 1)
			_effect = IMAGEMANAGER->findImage("attackFire");
		else if (_effSelect == 2)
			_effect = IMAGEMANAGER->findImage("attackIce");
		else if (_effSelect == 3)
			_effect = IMAGEMANAGER->findImage("attackSpake");
		else if (_effSelect == 4)
			_effect = IMAGEMANAGER->findImage("attackWave");
		effectUpdate(4, 2, 4);
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			_effPos.x = -20;
			_effPos.y = 0;
			_effectAngle = 180;
			_player.speed = PLAYERSPEED / 3;
			_player.angle = (PI / 180 * 270);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			_player.attackRc = { (float)_player.x , (float)_player.y + 40, (float)_player.x + 65, (float)_player.y + 75 };
			playerAniName("lea", "attackDownLast");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = true;
			_effPos.x = -35;
			_effPos.y = 0;
			_effectAngle = 225;
			_player.speed = PLAYERSPEED / 3;
			_player.angle = (PI / 180 * 225);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			_player.attackRc = { (float)_player.x - 20, (float)_player.y, (float)_player.x + 40, (float)_player.y + 75 };
			playerAniName("lea", "attackDownLeftLast");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			_effectAngle = 135;
			_effPos.x = -5;
			_effPos.y = 0;
			_player.speed = PLAYERSPEED / 3;
			_player.angle = (PI / 180 * 315);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			_player.attackRc = { (float)_player.x + 20, (float)_player.y, (float)_player.x + 85, (float)_player.y + 75 };
			playerAniName("lea", "attackDownRightLast");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = true;
			_effPos.x = -40;
			_effPos.y = 0;
			_effectAngle = 270;
			_player.speed = PLAYERSPEED / 3;
			_player.angle = (PI / 180 * 180);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			_player.attackRc = { (float)_player.x - 20, (float)_player.y, (float)_player.x + 40, (float)_player.y + 75 };
			playerAniName("lea", "attackLeftLast");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			_effPos.x = 0;
			_effPos.y = 0;
			_effectAngle = 90;
			_player.speed = PLAYERSPEED / 3;
			_player.angle = (PI / 180 * 0);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			_player.attackRc = { (float)_player.x + 20, (float)_player.y, (float)_player.x + 85, (float)_player.y + 75 };
			playerAniName("lea", "attackRightLast");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			_effPos.x = -20;
			_effPos.y = -20;
			_effectAngle = 0;
			_player.speed = PLAYERSPEED / 3;
			_player.angle = (PI / 180 * 90);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			_player.attackRc = { (float)_player.x , (float)_player.y - 20, (float)_player.x + 65, (float)_player.y + 15 };
			playerAniName("lea", "attackUpLast");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = true;
			_effPos.x = -30;
			_effPos.y = -20;
			_effectAngle = 315;
			_player.speed = PLAYERSPEED / 3;
			_player.angle = (PI / 180 * 135);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			_player.attackRc = { (float)_player.x - 20, (float)_player.y - 20, (float)_player.x + 40, (float)_player.y + 55 };
			playerAniName("lea", "attackUpLeftLast");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			_effPos.x = -5;
			_effPos.y = -15;
			_effectAngle = 45;
			_player.speed = PLAYERSPEED / 3;
			_player.angle = (PI / 180 * 45);
			_player.x += cosf(_player.angle) * _player.speed;
			_player.y += -sinf(_player.angle) * _player.speed;
			_player.attackRc = { (float)_player.x + 20, (float)_player.y - 20, (float)_player.x + 85, (float)_player.y + 55 };
			playerAniName("lea", "attackUpRightLast");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_DEFENSE:
		_player.effImage = IMAGEMANAGER->findImage("guard");
		_player.image = IMAGEMANAGER->findImage("leaMove");
		_effPos.x = 0;
		_effPos.y = 0;
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			playerAniName("lea", "guardDown");
			_player.effAni = KEYANIMANAGER->findAnimation("eff", "guardEffDown");
			_player.effAni->start(false);
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			playerAniName("lea", "guardDownRight");
			_player.effAni = KEYANIMANAGER->findAnimation("eff", "guardEffDownRight");
			_player.effAni->start(false);
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			playerAniName("lea", "guardDownRight");
			_player.effAni = KEYANIMANAGER->findAnimation("eff", "guardEffDownRight");
			_player.effAni->start(false);
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			playerAniName("lea", "guardRight");
			_player.effAni = KEYANIMANAGER->findAnimation("eff", "guardEffRight");
			_player.effAni->start(false);
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			playerAniName("lea", "guardRight");
			_player.effAni = KEYANIMANAGER->findAnimation("eff", "guardEffRight");
			_player.effAni->start(false);
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			playerAniName("lea", "guardUp");
			_player.effAni = KEYANIMANAGER->findAnimation("eff", "guardEffUp");
			_player.effAni->start(false);
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			playerAniName("lea", "guardUpRight");
			_player.effAni = KEYANIMANAGER->findAnimation("eff", "guardEffUpRight");
			_player.effAni->start(false);
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			playerAniName("lea", "guardUpRight");
			_player.effAni = KEYANIMANAGER->findAnimation("eff", "guardEffUpRight");
			_player.effAni->start(false);
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_AVOID:
		_isAvoid = true;
		_player.alphaValue = 1;
		_player.image = IMAGEMANAGER->findImage("leaThrow");
		if (GetTickCount() - _avoidEffTime >= 70)
		{
			EFFECTMANAGER->play("avoidEff", _player.x + 30, _player.y + 30);
			_avoidEffTime = GetTickCount();
		}
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			if(_player.avoidPower >= 0)
			_player.avoidPower -= 0.25;
			else _player.avoidPower = 0;
			_player.angle = (PI / 180 * 270);
			_player.x += cosf(_player.angle) * _player.avoidPower;
			_player.y += -sinf(_player.angle) * _player.avoidPower;
			playerAniName("lea", "avoidDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = true;
			if (_player.avoidPower >= 0)
				_player.avoidPower -= 0.25;
			else _player.avoidPower = 0;
			_player.angle = (PI / 180 * 225);
			_player.x += cosf(_player.angle) * _player.avoidPower;
			_player.y += -sinf(_player.angle) * _player.avoidPower;
			playerAniName("lea", "avoidDownLeft");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			if (_player.avoidPower >= 0)
				_player.avoidPower -= 0.25;
			else _player.avoidPower = 0;
			_player.angle = (PI / 180 * 315);
			_player.x += cosf(_player.angle) * _player.avoidPower;
			_player.y += -sinf(_player.angle) * _player.avoidPower;
			playerAniName("lea", "avoidDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = true;
			if (_player.avoidPower >= 0)
				_player.avoidPower -= 0.25;
			else _player.avoidPower = 0;
			_player.angle = (PI / 180 * 180);
			_player.x += cosf(_player.angle) * _player.avoidPower;
			_player.y += -sinf(_player.angle) * _player.avoidPower;
			playerAniName("lea", "avoidLeft");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			if (_player.avoidPower >= 0)
				_player.avoidPower -= 0.25;
			else _player.avoidPower = 0;
			_player.angle = (PI / 180 * 0);
			_player.x += cosf(_player.angle) * _player.avoidPower;
			_player.y += -sinf(_player.angle) * _player.avoidPower;
			playerAniName("lea", "avoidRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			if (_player.avoidPower >= 0)
				_player.avoidPower -= 0.25;
			else _player.avoidPower = 0;
			_player.angle = (PI / 180 * 90);
			_player.x += cosf(_player.angle) * _player.avoidPower;
			_player.y += -sinf(_player.angle) * _player.avoidPower;
			playerAniName("lea", "avoidUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = true;
			if (_player.avoidPower >= 0)
				_player.avoidPower -= 0.25;
			else _player.avoidPower = 0;
			_player.angle = (PI / 180 * 135);
			_player.x += cosf(_player.angle) * _player.avoidPower;
			_player.y += -sinf(_player.angle) * _player.avoidPower;
			playerAniName("lea", "avoidUpLeft");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			if (_player.avoidPower >= 0)
				_player.avoidPower -= 0.25;
			else _player.avoidPower = 0;
			_player.angle = (PI / 180 * 45);
			_player.x += cosf(_player.angle) * _player.avoidPower;
			_player.y += -sinf(_player.angle) * _player.avoidPower;
			playerAniName("lea", "avoidUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_ATTACKED:
		_player.speed = 2.0f;
		_isAttacked = true;
		_player.image = IMAGEMANAGER->findImage("leaMove");
		if (_playerAlphaCount % 2 == 0)
		{
			_player.alphaValue = 0.8;
		}
		else if (_playerAlphaCount % 2 == 1)
		{
			_player.alphaValue = 0.5;
		}
		_playerAlphaCount++;
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			_player.angle = (PI / 180 * 90);
			playerAniName("lea", "attackedDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			_player.angle = (PI / 180 * 45);
			playerAniName("lea", "attackedDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			_player.angle = (PI / 180 * 135);
			playerAniName("lea", "attackedDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			_player.angle = (PI / 180 * 0);
			playerAniName("lea", "attackedRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			_player.angle = (PI / 180 * 180);
			playerAniName("lea", "attackedRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			_player.angle = (PI / 180 * 270);
			playerAniName("lea", "attackedUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			_player.angle = (PI / 180 * 315);
			playerAniName("lea", "attackedUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			_player.angle = (PI / 180 * 225);
			playerAniName("lea", "attackedUpRight");
			break;
		}
		_player.x += cosf(_player.angle) * _player.speed;
		_player.y += -sinf(_player.angle) * _player.speed;
		break;

	case PLAYERSTATE::PLAYER_TELEPORT:
		_isRight = true;
		_player.image = IMAGEMANAGER->findImage("leaMove");
		_player.effImage = IMAGEMANAGER->findImage("teleportEff");
		_player.effAni = KEYANIMANAGER->findAnimation("eff", "teleportEff");
		_player.effAni->start(false);
		_effPos.x = 0;
		_effPos.y = 0;
		playerAniName("lea", "teleportDown");
		break;
	case PLAYERSTATE::PLAYER_CHARGE:
		_isCharge = true;
		switch (_player.direction)
		{
		case PLAYERDIRECTION::DOWN:
			_isRight = true;
			_player.angle = (PI / 180 * 90);
			playerAniName("lea", "chargeDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			_player.angle = (PI / 180 * 45);
			playerAniName("lea", "chargeDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			_player.angle = (PI / 180 * 135);
			playerAniName("lea", "chargeDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			_player.angle = (PI / 180 * 0);
			playerAniName("lea", "chargeRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			_player.angle = (PI / 180 * 180);
			playerAniName("lea", "chargeRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			_player.angle = (PI / 180 * 270);
			playerAniName("lea", "chargeUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			_player.angle = (PI / 180 * 315);
			playerAniName("lea", "chargeUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			_player.angle = (PI / 180 * 225);
			playerAniName("lea", "chargeUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_SKILL_FIRE:
		_isSkill = true;
		_isAttack = true;
		_isThrowAttack = false;
		_effCopy = false;
		_player.attackRc = { (float)_player.x - 140, (float)_player.y - 130, (float)_player.x + 200 , (float)_player.y + 210 };
		_effectAngle = 180;
		_player.image = IMAGEMANAGER->findImage("leaThrow");
		playerAniName("lea", "skillMotion");
		_effect = IMAGEMANAGER->findImage("attackFireR");
		effectUpdate(4, 2, 2);
		
		if (_player.motion->getFramePosArrOnce() == 108)
		{
			_effSkillStart = true;
		}
		if (_effSkillStart)
		{
			POINTF effPos;
			float angle;
			angle = 0;
			effPos.x = effPos.y = 0;
			_effSpeed += 2;
			if (GetTickCount() - _effOldTime >= 100)
			{
				for (int i = 0; i < 10; i++)
				{
					angle = (PI / 180 * (i * 36));
					effPos.x = (cos(angle) * _effSpeed) + _player.x;
					effPos.y = (-sin(angle) * _effSpeed) + _player.y;
					EFFECTMANAGER->play("fire5", effPos.x + 30, effPos.y + 30);
				}
				_effOldTime = GetTickCount();
			}
		}
		else if(!(_effSpeed == 0))
		{
			POINTF effPos;
			float angle;
			angle = 0;
			effPos.x = effPos.y = 0;
			if(_effSpeed > 0)
			_effSpeed -= 2;
			else _effSpeed = 0;
			if (GetTickCount() - _effOldTime >= 100)
			{
				for (int i = 0; i < 10; i++)
				{
					angle = (PI / 180 * (i * 36));
					effPos.x = (cos(angle) * _effSpeed) + _player.x;
					effPos.y = (-sin(angle) * _effSpeed) + _player.y;
					EFFECTMANAGER->play("fire5", effPos.x + 30, effPos.y + 30);
				}
				_effOldTime = GetTickCount();
			}
		}
		if (_player.motion->getFramePosArrOnce() == 156)
		{
			_skillStartPos.x = _player.x;
			_skillStartPos.y = _player.y;
			_skillMove = true;
			_effSkillStart = false;
		}
		if (_skillMove)
		{
			if (_skillStartPos.y - _player.y <= 100)
			{
				EFFECTMANAGER->play("fire4", _player.x , _player.y - 20);
				EFFECTMANAGER->play("fire4", _player.x + 40, _player.y - 20);
				EFFECTMANAGER->play("fire4", _player.x + 70, _player.y - 20);
				_player.y -= 10.0f;
			}
			if (_player.motion->getFramePosArrOnce() == 123)
			{
				_skillMove = false;
			}
			if (_player.motion->getFramePosArrOnce() == 122)
			{
				EFFECTMANAGER->play("fire1", _player.x + 20, _player.y);
			}
			else if (_player.motion->getFramePosArrOnce() == 123)
			{
				_skillEff = true;
				_player.effImage = IMAGEMANAGER->findImage("fire2");
				_player.effAni = KEYANIMANAGER->findAnimation("eff", "fireEff");
				_player.effAni->start(false);
			}
		}
		else
		{
			if (_player.motion->getFramePosArrOnce() == 129)
			{
				_skillStartPos.y = _player.y;
			}
			if (_skillStartPos.y - _player.y > 0)
			{
				_player.y += 10.0f;
				EFFECTMANAGER->play("fire4", _player.x, _player.y - 20);
				EFFECTMANAGER->play("fire4", _player.x + 40, _player.y);
				EFFECTMANAGER->play("fire4", _player.x + 70, _player.y);
			}
			else if (_player.motion->getFramePosArrOnce() == 126)
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						EFFECTMANAGER->play("fire3", _player.x - 70 + (j * 55) , _player.y - 60 + (i * 55));
					}
				}
			}
		}
		if (!_skillEff)
		{
			_effPos.x = -20;
			_effPos.y = 0;
		}
		else
		{
			_effPos.x = 20;
			_effPos.y = -60;
		}
	
		break;
		
	}
}