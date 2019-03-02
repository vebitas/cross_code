#include "stdafx.h"
#include "button.h"


button::button()
{
}


button::~button()
{
}

HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnCollisionPoint, function<void(void)> cbFunction)
{
	_callbackFunction = cbFunction;

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;
	_btnCollisionPoint = btnCollisionPoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(_imageName);

	_rc = { (LONG)(2 * CAMERA->getCameraX()) + x - _image->GetFrameWidth() / 2 , (LONG)(2 * CAMERA->getCameraY()) + y - _image->GetFrameHeight() / 2
		,(LONG)(2 * CAMERA->getCameraX()) + x + _image->GetFrameWidth() / 2 , (LONG)(2 * CAMERA->getCameraX()) + y + _image->GetFrameHeight() / 2 };

	return S_OK;
}


void button::release()
{
}

void button::update(float x, float y)
{
	POINT p;
	p.x = _ptMouse.x;
	p.y = _ptMouse.y;
	if (PtInRect(&_rc, p))
	{
		_direction = BUTTONDIRECTION_COLLISION;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION_NULL;

	_rc = { (LONG)(CAMERA->getCameraX() + x - _image->GetFrameWidth() / 2) , (LONG)(CAMERA->getCameraY() + y - _image->GetFrameHeight() / 2)
	 , (LONG)(CAMERA->CAMERA->getCameraX() + x + _image->GetFrameWidth() / 2), (LONG)(CAMERA->getCameraY() + y + _image->GetFrameHeight() / 2) };

}

void button::render()
{
	switch (_direction)
	{
	case BUTTONDIRECTION_NULL:	case BUTTONDIRECTION_UP:
		_image->frameRender(_rc.left, _rc.top,
			_btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
	case BUTTONDIRECTION_DOWN:
		_image->frameRender(_rc.left, _rc.top,
			_btnDownFramePoint.x, _btnDownFramePoint.y);
		break;
	case BUTTONDIRECTION_COLLISION:
		_image->frameRender(_rc.left, _rc.top,
			_btnDownFramePoint.x, _btnDownFramePoint.y);
		break;
	}
}
