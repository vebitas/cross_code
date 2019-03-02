#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
	:TILEX(0), TILEY(0)
{
	_vvTile.clear();
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	//setWindowsSize(0, 0, 1800, 800);
	
	IMAGEMANAGER->addFrameImage("stage1_1", L"image/tileNode/stage1_1.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addImage("mapToolBackground", L"image/tileNode/mapToolBackground.png", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("build_LR", L"image/tileNode/build_LR.png", 64, 800);
	IMAGEMANAGER->addImage("build_UD", L"image/tileNode/build_UD.png", 700, 64);
	IMAGEMANAGER->addFrameImage("button", L"image/tileNode/button.png", 100, 133, 3, 4);
	setTile();

	_increaseXMap = std::move(bind(&mapTool::increaseX, this));

	_increaseXButton = new button;
	_increaseXButton->init("button", WINSIZEX / 2 + 200, 600, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), _increaseXMap);

	_ptIdX = 0;
	_ptIdY = 0;

	CAMERA->init(800, 600, 3300, 3300);

	return S_OK;

}

void mapTool::release()
{
}

void mapTool::update()
{
	setMap();
	pickSampleTile();
	_increaseXButton->update(WINSIZEX / 2 + 200, 600);
	

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (CAMERA->getCameraY() > 0)
		{
			CAMERA->setCameraY(CAMERA->getCameraY() - 10);
		}
		else CAMERA->setCameraY(0);

	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERA->setCameraY(CAMERA->getCameraY() + 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (CAMERA->getCameraX() > 0)
		{
			CAMERA->setCameraX(CAMERA->getCameraX() - 10);
		}
		else CAMERA->setCameraX(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERA->setCameraX(CAMERA->getCameraX() + 10);
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (TILEX > 2)
		{
			for (int i = 0; i < TILEY; i++)
			{
				tagTile* delTile = _vvTile[i].back();
				_vvTile[i].pop_back();


				SAFE_DELETE(delTile);
			}
			TILEX--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (TILEY > 2)
		{
			for (int i = TILEX - 1; i >= 0; i--)
			{
				delete _vvTile.back()[i];			//데이터를 메모리에서 삭제함
				_vvTile.back()[i] = nullptr;		//포인터의 주소를 없앰
			}
			_vvTile.pop_back();
			TILEY--;
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown('A'))
	{

		for (int i = 0; i < TILEY; i++)
		{
			tagTile* tempTile = new tagTile;
		
			tempTile->terrainFrameX = 31;
			tempTile->terrainFrameY = 18;
		
			tempTile->objFrameX = 31;
			tempTile->objFrameY = 18;
		
			tempTile->terrain = TERRAIN::TR_FLOOR;
			tempTile->obj = OBJECT::OBJ_NONE;
		
			_vvTile[i].push_back(tempTile);
		}
		TILEX++;

		
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		vector<tagTile*> vTile;
		for (int i = 0; i < TILEX; ++i)
		{
			tagTile* tempTile = new tagTile;

			tempTile->terrainFrameX = 31;
			tempTile->terrainFrameY = 18;

			tempTile->objFrameX = 31;
			tempTile->objFrameY = 18;


			vTile.push_back(tempTile);
		}
		_vvTile.push_back(vTile);
		TILEY++;
	}

	//_ptViewMouse.x = _ptMouse.x - CAMERA->getCameraX();
	//_ptViewMouse.y = _ptMouse.y - CAMERA->getCameraY();

	_ptIdX = (_ptMouse.x ) / 32;
	_ptIdY = (_ptMouse.y ) / 32; 
		
	_ptSPidX = ((_ptMouse.x - CAMERA->getCameraX()) - 776) / 32;
	_ptSPidY =( _ptMouse.y - CAMERA->getCameraY()) / 32;

}
void mapTool::render()
{
	WCHAR str[128];
	IMAGEMANAGER->findImage("mapToolBackground")->render(0 + CAMERA->getCameraX() , 0 + CAMERA->getCameraY(), 0.5);

	for (int i = 0; i < TILEY; i++)			//타일맵 
	{
		for (int j = 0; j < TILEX; j++)
		{
			
			if ((j * TILESIZE) - CAMERA->getCameraX() < 0)
				continue;
			if (((j + 1) * TILESIZE) - CAMERA->getCameraX() > OUTPUTSIZEX)
				continue;
			if ((i * TILESIZE) - CAMERA->getCameraY() < 0)
				continue;
			if (((i + 1) * TILESIZE) - CAMERA->getCameraY() > OUTPUTSIZEY)
				continue;

			D2DMANAGER->drawRectangle(RGB(0, 0, 0), j * TILESIZE, i * TILESIZE  ,(j + 1) * TILESIZE, (i + 1) * TILESIZE);
			IMAGEMANAGER->frameRender("stage1_1", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->terrainFrameX, _vvTile[i][j]->terrainFrameY, 1);
			//swprintf_s(str, L"%d,%d", i, j);
			//D2DMANAGER->drawText(str,  (i * TILESIZE) - CAMERA->getCameraX(), (5 + j * TILESIZE) - CAMERA->getCameraY(), 10, RGB(0, 0, 0));
			
		}
	}

	IMAGEMANAGER->findImage("stage1_1")->frameRender(_ptMouse.x + 10, _ptMouse.y + 10, _tempTile.frameX, _tempTile.frameY);
	IMAGEMANAGER->findImage("stage1_1")->render(SAMPLE_TILE_STARTX + CAMERA->getCameraX(), 0 + CAMERA->getCameraY());
	for (int i = 0; i < SAMPLETILEY; i++)	//샘플맵
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			D2DMANAGER->drawRectangle(RGB(0, 0, 0), _sampleTile[i][j].tileRc.left + CAMERA->getCameraX(),
				_sampleTile[i][j].tileRc.top + CAMERA->getCameraY(),
				_sampleTile[i][j].tileRc.right + TILESIZE + CAMERA->getCameraX(),
				_sampleTile[i][j].tileRc.bottom + TILESIZE + CAMERA->getCameraY());
		}
	}
	
	
	IMAGEMANAGER->findImage("build_LR")->render(670 + CAMERA->getCameraX(), 0 + CAMERA->getCameraY(), 1);
	IMAGEMANAGER->findImage("build_UD")->render(0 + CAMERA->getCameraX(), 750 + CAMERA->getCameraY(), 1);
	
	_increaseXButton->render();
	
	swprintf_s(str, L"cameraX : %f", CAMERA->getCameraX());
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 20, 20, RGB(0, 0, 0));
	swprintf_s(str, L"cameraY : %f", CAMERA->getCameraY());
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 40, 20, RGB(0, 0, 0));
	swprintf_s(str, L"tileX : %d", TILEX);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 60, 20, RGB(0, 0, 0));
	swprintf_s(str, L"tileY : %d", TILEY);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 80, 20, RGB(0, 0, 0));
	swprintf_s(str, L"tempX : %d", _tempTile.frameX);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 100, 20, RGB(0, 0, 0));
	swprintf_s(str, L"tempY : %d", _tempTile.frameY);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 120, 20, RGB(0, 0, 0));
	swprintf_s(str, L"_ptSPidY : %d", _vvTile.size());
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 180, 20, RGB(0, 0, 0));
	swprintf_s(str, L"_ptSPidX : %d", _vvTile[0].size());
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 200, 20, RGB(0, 0, 0));
	swprintf_s(str, L"mouseY : %d", _tempTile.frameX);							
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 220, 20, RGB(0, 0, 0));
	swprintf_s(str, L"mouseY : %d", _tempTile.frameY);							
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 240, 20, RGB(0, 0, 0));
}

void mapTool::setTile()
{
	TILEX = 20;
	TILEY = 20;

	for (int i = 0; i < TILEY; i++)							//맵 타일 렉트 세팅
	{
		vector<tagTile*> vTile;
		vector<D2D1_RECT_F> vRect;
		for (int j = 0; j < TILEX; j++)
		{
			tagTile* _tile = new tagTile;
			_tile->selectTile = 0;
			_tile->terrainFrameX = 30;
			_tile->terrainFrameY = 19;
			_tile->objFrameX = 0;
			_tile->objFrameY = 0;
			_tile->terrain = terraniSelect(_tile->terrainFrameX, _tile->terrainFrameY);
			_tile->obj = OBJECT::OBJ_NONE;
			vTile.push_back(_tile);
		}
		_vvTile.push_back(vTile);
	}

	for (int i = 0; i < SAMPLETILEY; i++)					//샘플(선택할 타일) 렉트 세팅
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTile[i][j].tileRc = { (float)(SAMPLE_TILE_STARTX + (j * TILESIZE)),
										(float)(i * TILESIZE),
										(float)(SAMPLE_TILE_STARTX + (j + 1) * TILESIZE),
										(float)(i * TILESIZE + TILESIZE) };
	
			_sampleTile[i][j].frameX = j;
			_sampleTile[i][j].frameY = i;
		}
	}
}
//마우스 클릭으로 그 해당 인덱스의 타일이미지프레임값을 tempTile에 저장
void mapTool::pickSampleTile()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_ptSPidX >= 0 && _ptSPidX <= 31 && _ptSPidY >= 0 && _ptSPidY <= 19)
		{
			_tempTile.frameX = _sampleTile[_ptSPidY][_ptSPidX].frameX;
			_tempTile.frameY = _sampleTile[_ptSPidY][_ptSPidX].frameY;
		}
	}
}
 //tempTile안에 있는 프레임값을 마우스좌표가 가르키고있는 해당 타일에 프레임값에 넣어줌
void mapTool::setMap()
{
	if ((TILEX > _ptIdX && 0 <= _ptIdX) && (TILEY > _ptIdY && 0 <= _ptIdY))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (TILEY > _ptIdX)
			{
				_vvTile[_ptIdY][_ptIdX]->terrainFrameX = _tempTile.frameX;
			}
			if (TILEX > _ptIdY)
			{
				_vvTile[_ptIdY][_ptIdX]->terrainFrameY = _tempTile.frameY;
			}
		}
	}
}

void mapTool::increaseX()
{

}

void mapTool::increaseY()
{
}

void mapTool::decreaseX()
{
	
}

void mapTool::decreaseY()
{
}

TERRAIN mapTool::terraniSelect(int frameX, int frameY)
{

	return TERRAIN::TR_FLOOR;
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{
	return OBJECT::OBJ_NONE;
}

DWORD mapTool::setAttribute(string imgName, UINT frameX, UINT frameY)
{
	return 0;
}

void mapTool::increaseMap()
{
}

void mapTool::decreaseMap()
{
}

void mapTool::setWindowsSize(int x, int y, int width, int height)
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


























