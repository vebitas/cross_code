#include "stdafx.h"
#include "boss.h"


boss::boss()
{
}


boss::~boss()
{
}

HRESULT boss::init()
{
	_bossBullet = new bossBullet;
	_bossBullet->init("bossBullet", 500, 1000);
	
	
	int diving[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("boss", "diving", "boss_diving2", diving, 10, 8, false, cbDiving, this);

	_boss.divingImg = IMAGEMANAGER->findImage("boss_diving2");
	_boss.ani = KEYANIMANAGER->findAnimation("boss", "diving");
	_effectTime = 300;
	_boss.x = WINSIZEX / 2;
	_boss.y = WINSIZEY / 2;
	_boss.headImg = IMAGEMANAGER->findImage("boss_head");
	_boss.bodyImg = IMAGEMANAGER->findImage("boss_body1");
	_boss.body2Img = IMAGEMANAGER->findImage("boss_body2");
	_boss.body3Img = IMAGEMANAGER->findImage("boss_body3");
	_boss.body4Img = IMAGEMANAGER->findImage("boss_body4");
	_boss.body5Img = IMAGEMANAGER->findImage("boss_body5");
	_boss.tailImg = IMAGEMANAGER->findImage("boss_tail");
	//_boss.divingImg = IMAGEMANAGER->findImage("boss_diving");
	_boss.angle = 0;
	_boss.direction = BOSSDIRECTION::BOSS_LEFT;
	_boss.state = BOSSSTATE::BOSS_MOVE;
	_boss.speed = 5;
	_boss.jumpPower = 5;
	_boss.alpha = 1;
	_boss.maxHP = 500;
	_boss.HP = 500;
	_curFrameX = 0;
	_count = 0;
	_bodyCount = 0;
	_frameCount = 0;
	_eyeFrame = 0;
	_tailFrameX = 0;
	_tailCount = 0;
	_angleSpeed = 0;
	_oldTime = GetTickCount();
	
	_groggyPos = false;
	_turn = false;

	_isLeft = true;
	for (int i = 0; i < 6; i++)
	{
		_bodyMoveCount[i] = 0;

	}

	for (int i = 0; i < 4; i++)
	{
		_keyOnceDown[i] = false;
		_keyUp[i] = false;
	}

	_rushOn = false;

	return S_OK;
}

void boss::release()
{

}

void boss::update()
{

	_count++;
	if (_count % 6 == 0)
	{
		if (_curFrameX <= 2)
			_curFrameX++;
		else
			_curFrameX = 0;
		_count = 0;
		
	}
	if (_boss.state == BOSSSTATE::BOSS_RUSH)
	{
		_tailCount++;
		if (_tailCount % 3 == 0)
		{
			if (_tailFrameX <= 2)
				_tailFrameX++;
			else
				_tailFrameX = 0;
			_tailCount = 0;
		}
	}
	else
	{
		_tailFrameX = 2;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_boss.direction = BOSS_UP;
		_boss.state = BOSS_MOVE;
		_boss.y -= 3.0f;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_boss.direction = BOSS_UP;
		_boss.state = BOSS_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_boss.direction = BOSS_DOWN;
		_boss.state = BOSS_MOVE;
		_boss.y += 3.0f;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_boss.direction = BOSS_DOWN;
		_boss.state = BOSS_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_boss.direction = BOSS_LEFT;
		_boss.state = BOSS_MOVE;
		_boss.x -= 3.0f;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_boss.direction = BOSS_LEFT;
		_boss.state = BOSS_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_boss.direction = BOSS_RIGHT;
		_boss.state = BOSS_MOVE;
		_boss.x += 3.0f;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_boss.direction = BOSS_RIGHT;
		_boss.state = BOSS_IDLE;
	}


	if (KEYMANAGER->isOnceKeyDown('1'))
	{
	
	}
	if (KEYMANAGER->isStayKeyDown('1'))
	{
		_rushOn = true;
		_boss.state = BOSSSTATE::BOSS_RUSH;
	}
	if (KEYMANAGER->isOnceKeyUp('1'))
	{
		_rushOn = false;
		_eyeFrame = 0;
		_body.headY = 0;
		_body.angle = 0;
		_body.body1_y = 0;
		_body.angle1 = 0;
		_body.angle2 = 0;
		_body.body2_y = 0;
		_body.body3_y = 0;
		_body.body4_y = 0;
		_body.body5_y = 0;
		_body.tailY = 0;
		_boss.state = BOSSSTATE::BOSS_IDLE;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SOUNDMANAGER->play("whale_1", 1);
	}
	if (KEYMANAGER->isStayKeyDown('2'))
	{
		_boss.state = BOSSSTATE::BOSS_GROGGY;
	}
	if (KEYMANAGER->isOnceKeyUp('2'))
	{
		_boss.state = BOSSSTATE::BOSS_IDLE;
		_eyeFrame = 0;
		_body.headX = 0;
		_body.headY = 0;
		_body.angle = 0;
		_body.angle1 = 0;
		_body.body1_y = 0;
		_body.body3_x = 0;
		_body.angle3 = 0;
		_body.angle4 = 0;
		_body.body4_x = 0;
		_body.body4_y = 0;
		_body.angle5 = 0;
		_body.body5_x = 0;
		_body.body5_y = 0;
		_body.tailAngle = 0;
		_body.tailX = 0;
		_body.tailY = 0;
	}
	
	
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SOUNDMANAGER->play("whale_2", 1);
		_boss.jumpPower = 13;
		_angleSpeed = 0;
		_boss.jumpStartX = _boss.x;
		_boss.jumpStartY = _boss.y;
		_boss.state = BOSS_DIVING;
	
	}
	
	
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		EFFECTMANAGER->play("effect4", _boss.x, _boss.y);
	}

	rush();
	idle();
	bossState();
	_bossBullet->update();

	_boss.rc = { (float)_boss.x, (float)_boss.y , (float)_boss.x + 700, (float)_boss.y + 300 };
}

void boss::render()
{
	_bossBullet->render();
	//EFFECTMANAGER->render(0);
	if (!(_boss.state == BOSS_DIVING))
	{
		if (_isLeft)
		{
			_boss.tailImg->frameRenderAngle(_boss.x + 800 + _body.tailX, _boss.y + _body.tailY + 85, 170, 160, _tailFrameX, 0, _body.tailAngle, _boss.alpha);
			_boss.body5Img->frameRenderAngle(_boss.x + 685 + _body.body5_x, _boss.y + _body.body5_y + 70, 130 + _body.bodySize_5, 170 + _body.bodySize_5, 0, 0, _body.angle5, _boss.alpha);
			_boss.body4Img->frameRenderAngle(_boss.x + 560 + _body.body4_x, _boss.y + 35 + _body.body4_y, 180 + _body.bodySize_4, 230 + _body.bodySize_4, 0, 0, _body.angle4, _boss.alpha);
			_boss.body3Img->frameRenderAngle(_boss.x + 440 + _body.body3_x, _boss.y + _body.body3_y, 230 + _body.bodySize_3, 290 + _body.bodySize_3, _curFrameX, 0, _body.angle3, _boss.alpha);
			_boss.body2Img->frameRenderAngle(_boss.x + 300 + _body.body2_x, _boss.y - 30 + _body.body2_y, 310 + _body.bodySize_2, 370 + _body.bodySize_2, _curFrameX, 0, _body.angle2, _boss.alpha);
			_boss.bodyImg->frameRenderAngle(_boss.x + 150 + _body.body1_x, _boss.y - 50 + _body.body1_y, 350 + _body.bodySize_1, 430 + _body.bodySize_1, _curFrameX, 0, _body.angle1, _boss.alpha);
			_boss.headImg->frameRenderAngle(_boss.x - 35 + _body.headX, _boss.y - 10 + _body.headY, 350, 350, _eyeFrame, 0, _body.angle, _boss.alpha);
		}
		else
		{
			_boss.tailImg->frameRenderReverseAngle(_boss.x - 330 + _body.tailX, _boss.y + _body.tailY + 85, 170, 160, _tailFrameX, 0, _body.tailAngle, _boss.alpha);
			_boss.body5Img->frameRenderReverseAngle(_boss.x - 185 + _body.body5_x, _boss.y + 70 + _body.body5_y, 130 + _body.bodySize_5, 170 + _body.bodySize_5, 0, 0, _body.angle5, _boss.alpha);
			_boss.body4Img->frameRenderReverseAngle(_boss.x - 60 + _body.body4_x, _boss.y + 35 + _body.body4_y, 180 + _body.bodySize_4, 230 + _body.bodySize_4, 0, 0, _body.angle4, _boss.alpha);
			_boss.body3Img->frameRenderReverseAngle(_boss.x + 60 + _body.body3_x, _boss.y + _body.body3_y, 230 + _body.bodySize_3, 290 + _body.bodySize_3, _curFrameX, 0, _body.angle3, _boss.alpha);
			_boss.body2Img->frameRenderReverseAngle(_boss.x + 200 + _body.body2_x, _boss.y - 30 + _body.body2_y, 310 + _body.bodySize_2, 370 + _body.bodySize_2, _curFrameX, 0, _body.angle2, _boss.alpha);
			_boss.bodyImg->frameRenderReverseAngle(_boss.x + 350 + _body.body1_x, _boss.y - 50 + _body.body1_y, 350 + _body.bodySize_1, 430 + _body.bodySize_1, _curFrameX, 0, _body.angle1, _boss.alpha);
			_boss.headImg->frameRenderReverseAngle(_boss.x + 470 + _body.headX, _boss.y - 10 + _body.headY, 350, 350, _eyeFrame, 0, _body.angle, _boss.alpha);
		}
	}
	else
	{
		if (_isLeft)
		{
			_boss.divingImg->aniRender(_boss.x + 100, _boss.y - 300, _boss.ani, _boss.alpha);
		}
		else
		{
			_boss.divingImg->aniRenderReverseX(_boss.x - 100, _boss.y - 300, _boss.ani, _boss.alpha);
		}
	}

	//WCHAR str[128];
	//swprintf_s(str, L"%f", _boss.speed);
	//D2DMANAGER->drawText(str, CAMERA->getCameraX() + 400, CAMERA->getCameraY() + 20, 20, RGB(255, 255, 255));
	//D2DMANAGER->drawRectangle(_boss.rc);
}

void boss::bossState()
{
	switch (_boss.state)
	{
	case BOSSSTATE::BOSS_IDLE:
		_groggyPos = false;
		if (_boss.alpha < 1)
			_boss.alpha += 0.04;
		switch (_boss.direction)
		{
		case BOSSDIRECTION::BOSS_LEFT:
			_isLeft = true;
			break;
		case BOSSDIRECTION::BOSS_RIGHT:
			_isLeft = false;
			break;
		}
		break;
	case BOSSSTATE::BOSS_SHADOW:
		_boss.alpha = 0;
		break;
	case BOSSSTATE::BOSS_MOVE:
		for (int i = 0; i < 4; i++)
		{
			_keyOnceDown[i] = true;
		}

		_groggyPos = false;
		_boss.alpha = 0;
		_boss.speed = 3.5f;
		if (GetTickCount() - _oldTime >= _effectTime)
		{
			EFFECTMANAGER->play("effect4", _boss.x + 300, _boss.y + 150);
			_oldTime = GetTickCount();
		}
		break;
	case BOSSSTATE::BOSS_RUSH:

		if (_keyOnceDown[0])
		{
			SOUNDMANAGER->play("whale_3", 1);
			_turn = false;
			_boss.speed = 0;
			_keyOnceDown[0] = false;
		}

		_groggyPos = false;
		if (_boss.alpha < 1)
			_boss.alpha += 0.04;
		switch (_boss.direction)
		{
		case BOSSDIRECTION::BOSS_LEFT:

			if (GetTickCount() - _oldTime >= 100)
			{
				EFFECTMANAGER->play("effect5", _boss.x + 60, _boss.y);
				EFFECTMANAGER->play("effect5", _boss.x + 30, _boss.y + 20);
				EFFECTMANAGER->play("effect5", _boss.x + 10, _boss.y + 40);
				EFFECTMANAGER->play("effect5", _boss.x, _boss.y + 60);
				EFFECTMANAGER->play("effect5", _boss.x - 10, _boss.y + 80);
				EFFECTMANAGER->play("effect5", _boss.x - 20, _boss.y + 100);
				EFFECTMANAGER->play("effect5", _boss.x - 30, _boss.y + 120);
				EFFECTMANAGER->play("effect5", _boss.x - 40, _boss.y + 140);
				EFFECTMANAGER->play("effect5", _boss.x - 40, _boss.y + 160);
				EFFECTMANAGER->play("effect5", _boss.x - 40, _boss.y + 180);
				EFFECTMANAGER->play("effect5", _boss.x - 30, _boss.y + 200);
				EFFECTMANAGER->play("effect5", _boss.x - 20, _boss.y + 220);
				EFFECTMANAGER->play("effect5", _boss.x - 10, _boss.y + 240);
				EFFECTMANAGER->play("effect5", _boss.x, _boss.y + 260);
				EFFECTMANAGER->play("effect5", _boss.x + 10, _boss.y + 280);
				EFFECTMANAGER->play("effect5", _boss.x + 20, _boss.y + 300);
				EFFECTMANAGER->play("effect5", _boss.x + 30, _boss.y + 320);
				_oldTime = GetTickCount();
			}
			_isLeft = true;
			_eyeFrame = 3;
			
			if (_boss.speed > -6 && !_turn)
			{
				_boss.speed -= 0.2f; 
				_boss.y -= 2;
			}
			else if (_boss.speed < 12)
			{
				_turn = true;
				_boss.speed += 0.4f;
			}
			_boss.x -= _boss.speed;
			break;
		case BOSSDIRECTION::BOSS_RIGHT:
			_isLeft = false;
			if (GetTickCount() - _oldTime >= 100)
			{
				EFFECTMANAGER->play("effect5", _boss.x + 700 - 60, _boss.y);
				EFFECTMANAGER->play("effect5", _boss.x + 700 - 30, _boss.y + 20);
				EFFECTMANAGER->play("effect5", _boss.x + 700 - 10, _boss.y + 40);
				EFFECTMANAGER->play("effect5", _boss.x + 700, _boss.y + 60);
				EFFECTMANAGER->play("effect5", _boss.x + 700 + 10, _boss.y + 80);
				EFFECTMANAGER->play("effect5", _boss.x + 700 + 20, _boss.y + 100);
				EFFECTMANAGER->play("effect5", _boss.x + 700 + 30, _boss.y + 120);
				EFFECTMANAGER->play("effect5", _boss.x + 700 + 40, _boss.y + 140);
				EFFECTMANAGER->play("effect5", _boss.x + 700 + 40, _boss.y + 160);
				EFFECTMANAGER->play("effect5", _boss.x + 700 + 40, _boss.y + 180);
				EFFECTMANAGER->play("effect5", _boss.x + 700 + 30, _boss.y + 200);
				EFFECTMANAGER->play("effect5", _boss.x + 700 + 20, _boss.y + 220);
				EFFECTMANAGER->play("effect5", _boss.x + 700 + 10, _boss.y + 240);
				EFFECTMANAGER->play("effect5", _boss.x + 700, _boss.y + 260);
				EFFECTMANAGER->play("effect5", _boss.x + 700 - 10, _boss.y + 280);
				EFFECTMANAGER->play("effect5", _boss.x + 700 - 20, _boss.y + 300);
				EFFECTMANAGER->play("effect5", _boss.x + 700 - 30, _boss.y + 320);
				_oldTime = GetTickCount();
			}
			_eyeFrame = 3;
			if (_boss.speed > -6 && !_turn)
			{
				_boss.speed -= 0.2f;
				_boss.y -= 2;
			}
			else if (_boss.speed < 12)
			{
				_turn = true;
				_boss.speed += 0.4f;
			}
			_boss.x += _boss.speed;
			break;
		}
		break;
	case BOSSSTATE::BOSS_GROGGY:
		_groggyPos = true;
		if (_boss.alpha < 1)
			_boss.alpha += 0.04;
		switch (_boss.direction)
		{
		case BOSSDIRECTION::BOSS_LEFT:
			_isLeft = true;
			break;
		case BOSSDIRECTION::BOSS_RIGHT:
			_isLeft = false;
			break;
		}
		break;
	case BOSSSTATE::BOSS_DIVING:
		_boss.divingImg = IMAGEMANAGER->findImage("boss_diving2");
		if (_boss.alpha < 1)
			_boss.alpha += 0.04;
		switch (_boss.direction)
		{
		case BOSSDIRECTION::BOSS_LEFT:

			if (_keyOnceDown[1])
			{
				SOUNDMANAGER->play("whale_2", 1);
				_boss.jumpPower = 10;
				_angleSpeed = 0;
				_boss.x -= 200;
				_boss.jumpStartX = _boss.x;
				_boss.jumpStartY = _boss.y;
				_keyOnceDown[1] = false;
			}

			_isLeft = true;
			_boss.ani = KEYANIMANAGER->findAnimation("boss", "diving");
			_boss.ani->start(false);
			if(_boss.jumpPower > 6)
			_boss.jumpPower -= 0.5f;
			else if (_boss.jumpPower > 5)
			{
				_boss.jumpPower -= 0.045f;
			}
			else
			{
				_boss.jumpPower -= 0.7f;
				_boss.x -= 2;
			}
			if (_boss.jumpStartY + 150 >= _boss.y)
			_boss.y -= _boss.jumpPower;
			_boss.x -= 2;
			break;
		case BOSSDIRECTION::BOSS_RIGHT:
			if (_keyOnceDown[1])
			{
				SOUNDMANAGER->play("whale_2", 1);
				_boss.jumpPower = 8;
				_angleSpeed = 0;
				_boss.jumpStartX = _boss.x;
				_boss.jumpStartY = _boss.y;
				_keyOnceDown[1] = false;
			}
			_isLeft = false;
			_boss.ani = KEYANIMANAGER->findAnimation("boss", "diving");
			_boss.ani->start(false);
			if (_boss.jumpPower > 6)
				_boss.jumpPower -= 0.5f;
			else if (_boss.jumpPower > 5)
			{
				_boss.jumpPower -= 0.045f;
			}
			else
			{
				_boss.jumpPower -= 0.7f;
				_boss.x += 2;
			}
			if(_boss.jumpStartY + 150 >= _boss.y)
			_boss.y -= _boss.jumpPower;
			_boss.x += 2;

			break;
		}
		break;
	}

	//¸ÂÀ»¶§ ÁÂÇ¥
	if (_groggyPos)
	{
		_frameCount = 0;
		if (_isLeft)
		{
			_eyeFrame = 1;
			_body.headX = 30;
			_body.headY = -130;
			_body.angle = 30;
			_body.angle1 = 20;
			_body.body1_y = -40;
			_body.body3_x = -20;
			_body.angle3 = -20;
			_body.angle4 = -35;
			_body.body4_x = -10;
			_body.body4_y = -50;
			_body.angle5 = -45;
			_body.body5_x = -20;
			_body.body5_y = -120;
			_body.tailAngle = -55;
			_body.tailX = -45;
			_body.tailY = -200;
		}
		else
		{
			_eyeFrame = 1;
			_body.headX = -30;
			_body.headY = -130;
			_body.angle = -30;
			_body.angle1 = -20;
			_body.body1_y = -40;
			_body.body3_x = 20;
			_body.angle3 = 20;
			_body.angle4 = 35;
			_body.body4_x = 10;
			_body.body4_y = -50;
			_body.angle5 = 45;
			_body.body5_x = 20;
			_body.body5_y = -120;
			_body.tailAngle = 55;
			_body.tailX = 25;
			_body.tailY = -250;
		}
		idle();
	}
}

void boss::rush()
{
	if (_rushOn)
	{
		if (_isLeft)
		{
			_eyeFrame = 3;
			_body.headY = 20;
			_body.angle = -10;
			_body.body1_y = -20;
			_body.angle1 = -10;
			_body.angle2 = -10;
			_body.body2_y = -50;
			_body.body3_y = -60;
			_body.body4_y = -50;
			_body.body5_y = -40;
			_body.tailY = -30;
		}
		else
		{
			_eyeFrame = 3;
			_body.headY = 20;
			_body.angle = 10;
			_body.body1_y = -20;
			_body.angle1 = 10;
			_body.angle2 = 10;
			_body.body2_y = -50;
			_body.body3_y = -60;
			_body.body4_y = -50;
			_body.body5_y = -40;
			_body.tailX = -20;
			_body.tailY = -30;
		}
		idle();
	}
}

void boss::idle()
{
	//¼û½¬´Â »óÅÂ
	_frameCount++;
	if (_frameCount % 6 == 0)
	{
		if (_frameCount > 0)
		{
			_bodyMoveCount[0]++;
			if (_bodyMoveCount[0] % 20 < 10)
			{
				_body.body1_y -= 0.7f;
				_body.headY -= 0.5f;
				_body.bodySize_1 += 0.5;
			}
			else
			{
				_body.body1_y += 0.7f;
				_body.headY += 0.5f;
				_body.bodySize_1 -= 0.5;
			}
		}
		if (_frameCount > 20)
		{
			_bodyMoveCount[1]++;
			if (_bodyMoveCount[1] % 20 < 10)
			{
				_body.body2_y -= 0.7f;
				_body.bodySize_2 += 0.5;
			}
			else
			{
				_body.body2_y += 0.7f;
				_body.bodySize_2 -= 0.5;
			}
		}

		if (_frameCount > 40)
		{
			_bodyMoveCount[2]++;
			if (_bodyMoveCount[2] % 20 < 10)
			{
				_body.body3_y -= 0.7f;
				_body.bodySize_3 += 0.5;
			}
			else
			{
				_body.body3_y += 0.7f;
				_body.bodySize_3 -= 0.5;
			}
		}

		if (_frameCount > 60)
		{
			_bodyMoveCount[4]++;
			if (_bodyMoveCount[4] % 20 < 10)
			{
				_body.body4_y -= 0.7f;
				_body.bodySize_4 += 0.5;
			}
			else
			{
				_body.body4_y += 0.7f;
				_body.bodySize_4 -= 0.5;
			}
		}

		if (_frameCount > 80)
		{
			_bodyMoveCount[5]++;
			if (_bodyMoveCount[5] % 20 < 10)
			{
				_body.body5_y -= 0.7f;
				_body.bodySize_5 += 0.5;
			}
			else
			{
				_body.body5_y += 0.7f;
				_body.bodySize_5 -= 0.5;
			}
		}

		if (_frameCount > 100)
		{
			_bodyMoveCount[1]++;
			if (_bodyMoveCount[1] % 20 < 10)
			{
				_body.tailY -= 0.7f;
				_body.tailAngle -= 1;
			}
			else
			{
				_body.tailY += 0.7f;
				_body.tailAngle += 1;
			}
		}
	}
}

void boss::cbDiving(void * obj)
{
	boss* diving = (boss*)obj;
	diving->setBossState(BOSSSTATE::BOSS_IDLE);

	if (diving->getBossDirection() == BOSS_LEFT)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				EFFECTMANAGER->play("effect5", diving->getBossPosX() + (j * 100), diving->getBossPosY() + (i * 40));
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				EFFECTMANAGER->play("effect5", diving->getBossPosX() - 100 + (j * 100), diving->getBossPosY() + (i * 40));
			}
		}
	}
	
}
