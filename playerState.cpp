#include "stdafx.h"
#include "player.h"

void player::playerState()
{
	switch (_player.state)
	{
	case PLAYERSTATE::PLAYER_IDLE:
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
		_player.image = IMAGEMANAGER->findImage("leaMove");
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
			playerAniName("lea", "attackDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = false;
			_effPos.x = -35;
			_effPos.y = 0;
			_effectAngle = 225;
			playerAniName("lea", "attackDownRight");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = false;
			_effPos.x = -5;
			_effPos.y = 0;
			_effectAngle = 135;
			playerAniName("lea", "attackDownLeft");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = false;
			_effPos.x = -40;
			_effPos.y = 0;
			_effectAngle = 270;
			playerAniName("lea", "attackRight");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = false;
			_effPos.x = 0;
			_effPos.y = 0;
			_effectAngle = 90;
			playerAniName("lea", "attackLeft");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = false;
			_effPos.x = -20;
			_effPos.y = -20;
			_effectAngle = 0;
			playerAniName("lea", "attackUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = false;
			_effPos.x = -30;
			_effPos.y = -20;
			_effectAngle = 315;
			playerAniName("lea", "attackUpRight");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = false;
			_effPos.x = -5;
			_effPos.y = -15;
			_effectAngle = 45;
			playerAniName("lea", "attackUpLeft");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_ATTACK_COMBO_2:
		_isAttack = true;
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
			playerAniName("lea", "attackDown");
			break;
		case PLAYERDIRECTION::DOWN_LEFT:
			_isRight = true;
			_effPos.x = -35;
			_effPos.y = 0;
			_effectAngle = 225;
			playerAniName("lea", "attackDownLeft");
			break;
		case PLAYERDIRECTION::DOWN_RIGHT:
			_isRight = true;
			_effectAngle = 135;
			_effPos.x = -5;
			_effPos.y = 0;
			playerAniName("lea", "attackDownRight");
			break;
		case PLAYERDIRECTION::LEFT:
			_isRight = true;
			_effPos.x = -40;
			_effPos.y = 0;
			_effectAngle = 270;
			playerAniName("lea", "attackLeft");
			break;
		case PLAYERDIRECTION::RIGHT:
			_isRight = true;
			_effPos.x = 0;
			_effPos.y = 0;
			_effectAngle = 90;
			playerAniName("lea", "attackRight");
			break;
		case PLAYERDIRECTION::UP:
			_isRight = true;
			_effPos.x = -20;
			_effPos.y = -20;
			_effectAngle = 0;
			playerAniName("lea", "attackUp");
			break;
		case PLAYERDIRECTION::UP_LEFT:
			_isRight = true;
			_effPos.x = -30;
			_effPos.y = -20;
			_effectAngle = 315;
			playerAniName("lea", "attackUpLeft");
			break;
		case PLAYERDIRECTION::UP_RIGHT:
			_isRight = true;
			_effPos.x = -5;
			_effPos.y = -15;
			_effectAngle = 45;
			playerAniName("lea", "attackUpRight");
			break;
		}
		break;
	case PLAYERSTATE::PLAYER_ATTACK_COMBO_FINISH:
		_isAttack = true;
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
			playerAniName("lea", "attackUpRightLast");
			break;
		}
		break;
	}
}