#include "stdafx.h"
#include "stage_1.h"


stage_1::stage_1()
{
}


stage_1::~stage_1()
{
}

HRESULT stage_1::init()
{
	setWindowsSize(0, 0, GAMESIZEX, GAMESIZEY);
	IMAGEMANAGER->addImage("testMap", L"image/map/testMap.png", GAMESIZEX, GAMESIZEY);
	_player = new player;
	_player->init();
	return S_OK;
}

void stage_1::release()
{
}

void stage_1::update()
{
	_player->update();
}

void stage_1::render()
{
	//IMAGEMANAGER->findImage("testMap")->render(1);
	_player->render();
}

void stage_1::setWindowsSize(int x, int y, int width, int height)
{
	SAFE_RELEASE2(D2DMANAGER->_renderTarget);

	//---------------------------------------------------------------------------
	//   Hwnd Render Target 생성
	//---------------------------------------------------------------------------
	D2DMANAGER->_d2dFactory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(_hWnd, SizeU(width, height)),
		&D2DMANAGER->_renderTarget);

	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실질적으로 클라이언트 영역 크기 셋팅을 한다
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);
}

