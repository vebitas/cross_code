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
	setWindowsSize(0, 0, 1800, 800);
	
	_player = new player;
	_player->init();

	IMAGEMANAGER->addFrameImage("stage1_1", L"image/tileNode/stage1_1.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_2", L"image/tileNode/stage1_2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_3", L"image/tileNode/stage1_3.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage2", L"image/tileNode/stage2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);	
	IMAGEMANAGER->addFrameImage("bossStage", L"image/tileNode/bossStage.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_1(mini)", L"image/tileNode/stage1_1(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_2(mini)", L"image/tileNode/stage1_2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_3(mini)", L"image/tileNode/stage1_3(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage2(mini)", L"image/tileNode/stage2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("bossStage(mini)", L"image/tileNode/bossStage(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addImage("mapToolBackground", L"image/tileNode/mapToolBackground.png", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("build_LR", L"image/tileNode/build_LR.png", 64, 830);
	IMAGEMANAGER->addImage("build_UD", L"image/tileNode/build_UD.png", 750, 64);
	IMAGEMANAGER->addFrameImage("button", L"image/tileNode/button.png", 150, 200, 3, 4);
	IMAGEMANAGER->addFrameImage("button2", L"image/tileNode/button_2.png", 375, 250, 3, 5);
	IMAGEMANAGER->addFrameImage("textXY", L"image/tileNode/textXY.png", 96, 48, 2, 1);
	IMAGEMANAGER->addImage("textMap", L"image/tileNode/textMap.png", 96, 48);
	IMAGEMANAGER->addImage("window", L"image/tileNode/window.png", 300, 300);
	IMAGEMANAGER->addFrameImage("okButton", L"image/tileNode/okButton.png", 144, 48, 3, 1);
	IMAGEMANAGER->addFrameImage("number", L"image/tileNode/number.png", 144, 48, 3, 1);
	buttonInit();
	setTile();
	
	_ptIdX = 0;
	_ptIdY = 0;
	_ptSPidX = 0;
	_ptSPidY = 0;
	_mapClippingPos.x = 0;
	_mapClippingPos.y = 0;
	_window.x = SAMPLE_TILE_STARTX;
	_window.y = 0;
	_pageSL = 0;

	_buttonSelect = 0;

	_dragMod = false;
	_mapDragMod = false;
	_dragFrameSave = false;
	_saveOn = false;
	_loadOn = false;
	_save = _load = false;

	_mapSelect = MAPNUMBER::STAGE1_1;

	_selectTileRc = { (float)_ptIdX * TILESIZE, (float)_ptIdY * TILESIZE, (float)_ptIdX * TILESIZE + TILESIZE, (float)_ptIdY * TILESIZE + TILESIZE };
	_selectSampleTileRc = { (float)_ptSPidX * TILESIZE, (float)_ptSPidY * TILESIZE, (float)_ptSPidX * TILESIZE + TILESIZE, (float)_ptSPidY * TILESIZE + TILESIZE };
	CAMERA->init(200, 200, 3300, 3300);

	_mouseCameraMoveRc[0] = { (float)0,(float)0, (float)730, (float)60 };
	_mouseCameraMoveRc[1] = { (float)670,(float)0, (float)730, (float)800};
	_mouseCameraMoveRc[2] = { (float)0,(float)750, (float)730, (float)800};
	_mouseCameraMoveRc[3] = { (float)0,(float)0, (float)60, (float)800};

	return S_OK;

}

void mapTool::release()
{
}

void mapTool::update()
{
	_player->update();
	setMap();
	pickSampleTile();

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (CAMERA->getCameraY() > 0)
		{
			CAMERA->setCameraY(CAMERA->getCameraY() - 10);
		}
		else CAMERA->setCameraY(0);

	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) )
	{
		CAMERA->setCameraY(CAMERA->getCameraY() + 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) )
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

	spDragMod();
	buttonUpdate();
	
	if (_dragFrameSave  && (_ptSPidX <= SAMPLETILEX && _ptSPidY <= SAMPLETILEY && _ptSPidX >= 0 && _ptSPidY >= 0))
	{
		_selectSampleTileRc = { (float)(SAMPLE_TILE_STARTX + (_dragStartIdX * TILESIZE)) + CAMERA->getCameraX(),
							(float)(_dragStartIdY * TILESIZE) + CAMERA->getCameraY(),
							(float)(SAMPLE_TILE_STARTX + (_ptSPidX * TILESIZE) + TILESIZE) + CAMERA->getCameraX(),
							(float)(_ptSPidY * TILESIZE + TILESIZE) + CAMERA->getCameraY() };
	}

	_ptIdX = (_ptMouse.x ) / 32;
	_ptIdY = (_ptMouse.y ) / 32; 
		
	_ptSPidX = ((_ptMouse.x - CAMERA->getCameraX()) - 776) / 32;
	_ptSPidY =( _ptMouse.y - CAMERA->getCameraY()) / 32;

	_mouseCameraMoveRc[0] = { (float)0 + CAMERA->getCameraX() ,(float)0 + CAMERA->getCameraY(), (float)730 + CAMERA->getCameraX(), (float)60 + CAMERA->getCameraY() };
	_mouseCameraMoveRc[1] = { (float)670 + CAMERA->getCameraX(),(float)0 + CAMERA->getCameraY(), (float)730 + CAMERA->getCameraX(), (float)800 + CAMERA->getCameraY() };
	_mouseCameraMoveRc[2] = { (float)0+ CAMERA->getCameraX(),(float)750 + CAMERA->getCameraY(), (float)730 + CAMERA->getCameraX(), (float)800 + CAMERA->getCameraY() };
	_mouseCameraMoveRc[3] = { (float)0+ CAMERA->getCameraX(),(float)0 + CAMERA->getCameraY(), (float)60 + CAMERA->getCameraX(), (float)800 + CAMERA->getCameraY() };

	if (!_mapDragMod)
	{
		_selectTileRc = { (float)_ptIdX * TILESIZE, (float)_ptIdY * TILESIZE, (float)_ptIdX * TILESIZE + TILESIZE, (float)_ptIdY * TILESIZE + TILESIZE };
	}
	else
	{
		_selectTileRc = { (float)_mapDragStartX * TILESIZE, (float)_mapDragStartY * TILESIZE, (float)_ptIdX * TILESIZE + TILESIZE, (float)_ptIdY * TILESIZE + TILESIZE };
	}

	_mapClippingPos.x = (CAMERA->getCameraX() + (OUTPUTSIZEX / 2)) / 32;
	_mapClippingPos.y = (CAMERA->getCameraY() + (OUTPUTSIZEY / 2)) / 32;

	mapSave();
	mapLoad();
}
void mapTool::render()
{
	WCHAR str[128];
	IMAGEMANAGER->findImage("mapToolBackground")->render(0 + CAMERA->getCameraX() , 0 + CAMERA->getCameraY(), 0.3);

	for (int i = _mapClippingPos.y - 12; i < _mapClippingPos.y + 11; i++)			//타일맵 
	{
		for (int j = _mapClippingPos.x - 11; j < _mapClippingPos.x + 11; j++)
		{
			if (j >= TILEX) continue;
			if (i >= TILEY) continue;
			if (j < 0) continue;
			if (i < 0) continue;
	
			D2DMANAGER->drawRectangle(RGB(0, 0, 0), j * TILESIZE, i * TILESIZE  ,(j + 1) * TILESIZE, (i + 1) * TILESIZE);

		
			switch (_vvTile[i][j]->selectTile)
			{
			case STAGE1_1:
				IMAGEMANAGER->frameRender("stage1_1", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->terrainFrameX, _vvTile[i][j]->terrainFrameY, 1);
				break;
			case STAGE1_2:
				IMAGEMANAGER->frameRender("stage1_2", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->terrainFrameX, _vvTile[i][j]->terrainFrameY, 1);
				break;
			case STAGE1_3:
				IMAGEMANAGER->frameRender("stage1_3", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->terrainFrameX, _vvTile[i][j]->terrainFrameY, 1);
				break;
			case STAGE2:
				IMAGEMANAGER->frameRender("stage2", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->terrainFrameX, _vvTile[i][j]->terrainFrameY, 1);
				break;
			case BOSS_STAGE:
				IMAGEMANAGER->frameRender("bossStage", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->terrainFrameX, _vvTile[i][j]->terrainFrameY, 1);
				break;
			}
			
			switch (_vvTile[i][j]->selectTile)
			{
			case STAGE1_1:
				IMAGEMANAGER->frameRender("stage1_1", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->objFrameX, _vvTile[i][j]->objFrameY, 1);
				break;
			case STAGE1_2:
				IMAGEMANAGER->frameRender("stage1_2", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->objFrameX, _vvTile[i][j]->objFrameY, 1);
				break;
			case STAGE1_3:
				IMAGEMANAGER->frameRender("stage1_3", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->objFrameX, _vvTile[i][j]->objFrameY, 1);
				break;
			case STAGE2:
				IMAGEMANAGER->frameRender("stage2", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->objFrameX, _vvTile[i][j]->objFrameY, 1);
				break;
			case BOSS_STAGE:
				IMAGEMANAGER->frameRender("bossStage", j * TILESIZE, i * TILESIZE, _vvTile[i][j]->objFrameX, _vvTile[i][j]->objFrameY, 1);
				break;
			}
			
		}
	}
	tilePreview();
	switch (_mapSelect)
	{
	case STAGE1_1:
		IMAGEMANAGER->findImage("stage1_1")->render(SAMPLE_TILE_STARTX + CAMERA->getCameraX(), 0 + CAMERA->getCameraY());
		break;
	case STAGE1_2:
		IMAGEMANAGER->findImage("stage1_2")->render(SAMPLE_TILE_STARTX + CAMERA->getCameraX(), 0 + CAMERA->getCameraY());
		break;
	case STAGE1_3:
		IMAGEMANAGER->findImage("stage1_3")->render(SAMPLE_TILE_STARTX + CAMERA->getCameraX(), 0 + CAMERA->getCameraY());
		break;
	case STAGE2:
		IMAGEMANAGER->findImage("stage2")->render(SAMPLE_TILE_STARTX + CAMERA->getCameraX(), 0 + CAMERA->getCameraY());
		break;
	case BOSS_STAGE:
		IMAGEMANAGER->findImage("bossStage")->render(SAMPLE_TILE_STARTX + CAMERA->getCameraX(), 0 + CAMERA->getCameraY());
		break;
	}
	
	

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
	
	

	IMAGEMANAGER->findImage("build_UD")->render(0 + CAMERA->getCameraX(), 740 + CAMERA->getCameraY(), 1);
	IMAGEMANAGER->findImage("build_LR")->render(700 + CAMERA->getCameraX(), 0 + CAMERA->getCameraY(), 1);

	buttonRender();

	if (_ptIdX < TILEX && _ptIdY < TILEY && _mapClippingPos.x + 11 > _ptIdX && _mapClippingPos.y + 11 > _ptIdY)
	{
		D2DMANAGER->fillRectangle(RGB(255, 0 ,255), _selectTileRc);
	}
	if ((_ptSPidX < SAMPLETILEX && _ptSPidY < SAMPLETILEY 
		&& _ptSPidX >= 0 && _ptSPidY >= 0) && _dragFrameSave)
	{
		D2DMANAGER->fillRectangle(RGB(255, 0, 255), _selectSampleTileRc);
	}


	IMAGEMANAGER->findImage("textXY")->frameRender(WINSIZEX / 2 - 70 + CAMERA->getCameraX(), 690 + CAMERA->getCameraY(), 0, 0);
	IMAGEMANAGER->findImage("textXY")->frameRender(WINSIZEX / 2 + 80 + CAMERA->getCameraX(), 690 + CAMERA->getCameraY(), 1, 0);
	IMAGEMANAGER->findImage("textMap")->render(WINSIZEX - 172 + CAMERA->getCameraX(), 695 + CAMERA->getCameraY());
	
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
	swprintf_s(str, L"_ptIdX : %d", _ptIdX);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 180, 20, RGB(0, 0, 0));
	swprintf_s(str, L"_ptIdY : %d", _ptIdY);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 200, 20, RGB(0, 0, 0));
	swprintf_s(str, L"시작x : %d", _saveOn);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 220, 20, RGB(0, 0, 0));
	swprintf_s(str, L"시작y : %d", _loadOn);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 240, 20, RGB(0, 0, 0));
	swprintf_s(str, L"차이x : %d", _save);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 260, 20, RGB(0, 0, 0));
	swprintf_s(str, L"차이y : %d", _load);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 280, 20, RGB(0, 0, 0));
	swprintf_s(str, L"드래그 모드 : %d", _dragFrameSave);
	D2DMANAGER->drawText(str, CAMERA->getCameraX(), CAMERA->getCameraY() + 300, 20, RGB(0, 0, 0));
	_player->render();
}

void mapTool::setTile()
{
	TILEX = 20;
	TILEY = 20;

	for (int i = 0; i < TILEY; i++)							//맵 타일 렉트 세팅
	{
		vector<tagTile*> vTile;
		for (int j = 0; j < TILEX; j++)
		{
			tagTile* _tile = new tagTile;
			_tile->selectTile = 0;
			_tile->terrainFrameX = 30;
			_tile->terrainFrameY = 19;
			_tile->objFrameX = 30;
			_tile->objFrameY = 19;
			_tile->terrain = terraniSelect(_tile->terrainFrameX, _tile->terrainFrameY);
			_tile->obj = OBJECT::OBJ_NONE;
			_tile->heightTile = 0;
			vTile.push_back(_tile);
		}
		_vvTile.push_back(vTile);
	}

	for (int i = 0; i < 35; i++)
	{
		vector<tagTile*> vTile;
		for (int j = 0; j < 60; j++)
		{
			tagTile* _tile = new tagTile;
			_tile->selectTile = 0;
			_tile->terrainFrameX = 30;
			_tile->terrainFrameY = 19;
			_tile->objFrameX = 30;
			_tile->objFrameY = 19;
			_tile->terrain = terraniSelect(_tile->terrainFrameX, _tile->terrainFrameY);
			_tile->obj = OBJECT::OBJ_NONE;
			_tile->heightTile = 0;
			vTile.push_back(_tile);
		}
		_vvMiniMap.push_back(vTile);
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
	if (_mapClippingPos.x + 11 > _ptIdX && _mapClippingPos.x - 11 <= _ptIdX && _mapClippingPos.y + 11 > _ptIdY && _mapClippingPos.y - 12 <= _ptIdY)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_mapDragMod = true;
			_mapDragStartX = _ptIdX;
			_mapDragStartY = _ptIdY;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{

			if (_buttonSelect == 0)
			{
				//드래그모드가 아닐때는 클릭한 한개의 샘플좌표를 맵에 있는 해당 프레임에 대입시킨다.
				if (!_dragMod && _ptIdX < TILEX && _ptIdY < TILEY)
				{
					if (TILEX > _ptIdX)
					{
						_vvTile[_ptIdY][_ptIdX]->terrainFrameX = _tempTile.frameX;
					}
					if (TILEY > _ptIdY)
					{
						_vvTile[_ptIdY][_ptIdX]->terrainFrameY = _tempTile.frameY;
					}
					_vvTile[_ptIdY][_ptIdX]->selectTile = _mapSelect;
				}
				//드래그 모드일때
				else
				{
					for (int i = 0; i < abs(_dragchaiY) + 1; i++)
					{
						for (int j = 0; j < abs(_dragchaiX) + 1; j++)
						{
							if (_ptIdX + j >= TILEX) continue;
							if (_ptIdY + i >= TILEY) continue;

							POINT dragPoint;
							dragPoint.x = _dragStartIdX;
							dragPoint.y = _dragStartIdY;

							if (_dragchaiX < 0)
							{
								dragPoint.x += _dragchaiX;
							}
							if (_dragchaiY < 0)
							{
								dragPoint.y += _dragchaiY;
							}

							_vvTile[_ptIdY + i][_ptIdX + j]->terrainFrameX = dragPoint.x + j;
							_vvTile[_ptIdY + i][_ptIdX + j]->terrainFrameY = dragPoint.y + i;
							_vvTile[_ptIdY + i][_ptIdX + j]->selectTile = _mapSelect;
						}
					}
				}
			}
			else if (_buttonSelect == 1)
			{
				//드래그모드가 아닐때는 클릭한 한개의 샘플좌표를 맵에 있는 해당 프레임에 대입시킨다.
				if (!_dragMod && _ptIdX < TILEX && _ptIdY < TILEY)
				{
					if (TILEY > _ptIdX)
					{
						_vvTile[_ptIdY][_ptIdX]->objFrameX = _tempTile.frameX;
					}
					if (TILEX > _ptIdY)
					{
						_vvTile[_ptIdY][_ptIdX]->objFrameY = _tempTile.frameY;
					}
					_vvTile[_ptIdY][_ptIdX]->selectTile = _mapSelect;
				}
				//드래그 모드일때
				else
				{
					for (int i = 0; i < abs(_dragchaiY) + 1; i++)
					{
						for (int j = 0; j < abs(_dragchaiX) + 1; j++)
						{
							if (abs(_dragchaiX) + _ptIdX >= TILEX) continue;
							if (abs(_dragchaiY) + _ptIdY >= TILEY) continue;

							POINT dragPoint;
							dragPoint.x = _dragStartIdX;
							dragPoint.y = _dragStartIdY;

							if (_dragchaiX < 0)
							{
								dragPoint.x += _dragchaiX;
							}
							if (_dragchaiY < 0)
							{
								dragPoint.y += _dragchaiY;
							}

							_vvTile[_ptIdY + i][_ptIdX + j]->objFrameX = dragPoint.x + j;
							_vvTile[_ptIdY + i][_ptIdX + j]->objFrameY = dragPoint.y + i;
							_vvTile[_ptIdY + i][_ptIdX + j]->selectTile = _mapSelect;
						}
					}
				}
			}
			else
			{
				if (!_dragMod && _ptIdX < TILEX && _ptIdY < TILEY)
				{
					if (TILEY > _ptIdX)
					{
						_vvTile[_ptIdY][_ptIdX]->objFrameX = 30;
					}
					if (TILEX > _ptIdY)
					{
						_vvTile[_ptIdY][_ptIdX]->objFrameY = 19;
					}
				}
				//드래그 모드일때
				else
				{
					for (int i = 0; i < abs(_dragchaiY) + 1; i++)
					{
						for (int j = 0; j < abs(_dragchaiX) + 1; j++)
						{
							if (abs(_dragchaiX) + _ptIdX >= TILEX) continue;
							if (abs(_dragchaiY) + _ptIdY >= TILEY) continue;

							_dragTerm.x = 1;
							_dragTerm.y = 1;
							_vvTile[_ptIdY + i][_ptIdX + j]->objFrameX = 30;
							_vvTile[_ptIdY + i][_ptIdX + j]->objFrameY = 19;
							_vvTile[_ptIdY + i][_ptIdX + j]->selectTile = _mapSelect;
						}
					}
				}
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (!_dragMod)
			{
				POINT chai;

				_mapDragEndX = _ptIdX;
				_mapDragEndY = _ptIdY;
				
				_mapDragchaiX = (_mapDragEndX - _mapDragStartX);
				_mapDragchaiY = (_mapDragEndY - _mapDragStartY);
			
			
			
				for (int i = 0; i < _mapDragchaiY + 1; i++)
				{
					for (int j = 0; j < _mapDragchaiX + 1; j++)
					{
						if (_mapDragEndX >= TILEX) continue;
						if (_mapDragEndY >= TILEY) continue;
						if (_mapDragchaiX <= 0 || _mapDragchaiY <= 0) continue;

						_vvTile[_mapDragStartY + i][_mapDragStartX + j]->terrainFrameX = _tempTile.frameX;
						_vvTile[_mapDragStartY + i][_mapDragStartX + j]->terrainFrameY = _tempTile.frameY;
						_vvTile[_mapDragStartY + i][_mapDragStartX + j]->selectTile = _mapSelect;
					}
				}
			}
			_mapDragMod = false;
		}
	}
}

void mapTool::spDragMod()
{
	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _ptSPidX <= SAMPLETILEX && _ptSPidY <= SAMPLETILEY
											&& _ptSPidX >= 0 && _ptSPidY >= 0)
	{
		//마우스를 눌렀을때의 샘플좌표를 시작인덱스변수들에게 넣어준다.
		_dragFrameSave = true;
		_dragStartIdX = _ptSPidX;
		_dragStartIdY = _ptSPidY;
	}

	if(KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _ptSPidX <= SAMPLETILEX && _ptSPidY <= SAMPLETILEY
											&& _ptSPidX >= 0 && _ptSPidY >= 0)
	{
		//마우스를 뗐을때의 좌표를 앤드인덱스변수들에게 넣어준다.
		_dragFrameSave = false;
		_dragEndidX = _ptSPidX;
		_dragEndidY = _ptSPidY;
		_dragchaiX = _dragEndidX - _dragStartIdX;
		_dragchaiY = _dragEndidY - _dragStartIdY;
		//스타트 인덱스와 앤드 인덱스의 차이가 1이상일 경우 드래그모드를 활성화시킨다.
		if (_dragchaiX > 0 || _dragchaiY > 0 || _dragchaiX < 0 || _dragchaiY)
		{
			_dragMod = true;
		}
		else
		{
			_dragMod = false;
		}
	}
}


void mapTool::tilePreview()
{
	if (!(_buttonSelect == 2))
	{
		switch (_mapSelect)
		{
		case STAGE1_1:
			if (!_dragMod)
			{
				IMAGEMANAGER->frameRender("stage1_1", _ptMouse.x - 20, _ptMouse.y - 20, _tempTile.frameX, _tempTile.frameY, 0.3);
			}
			else
			{
				for (int i = 0; i < _dragchaiY + 1; i++)
				{
					for (int j = 0; j < _dragchaiX + 1; j++)
					{
						IMAGEMANAGER->frameRender("stage1_1", _ptMouse.x - 20 + (TILESIZE * j), _ptMouse.y - 20 + (TILESIZE * i), _dragStartIdX + j, _dragStartIdY + i, 0.3);
					}
				}
			}
			break;
		case STAGE1_2:
			if (!_dragMod)
			{
				IMAGEMANAGER->frameRender("stage1_2", _ptMouse.x - 20, _ptMouse.y - 20, _tempTile.frameX, _tempTile.frameY, 0.3);
			}
			else
			{
				for (int i = 0; i < _dragchaiY + 1; i++)
				{
					for (int j = 0; j < _dragchaiX + 1; j++)
					{
						IMAGEMANAGER->frameRender("stage1_2", _ptMouse.x - 20 + (TILESIZE * j), _ptMouse.y - 20 + (TILESIZE * i), _dragStartIdX + j, _dragStartIdY + i, 0.3);
					}
				}
			}
			break;
		case STAGE1_3:
			if (!_dragMod)
			{
				IMAGEMANAGER->frameRender("stage1_3", _ptMouse.x - 20, _ptMouse.y - 20, _tempTile.frameX, _tempTile.frameY, 0.3);
			}
			else
			{
				for (int i = 0; i < _dragchaiY + 1; i++)
				{
					for (int j = 0; j < _dragchaiX + 1; j++)
					{
						IMAGEMANAGER->frameRender("stage1_3", _ptMouse.x - 20 + (TILESIZE * j), _ptMouse.y - 20 + (TILESIZE * i), _dragStartIdX + j, _dragStartIdY + i, 0.3);
					}
				}
			}
			break;
		case STAGE2:
			if (!_dragMod)
			{
				IMAGEMANAGER->frameRender("stage2", _ptMouse.x - 20, _ptMouse.y - 20, _tempTile.frameX, _tempTile.frameY, 0.3);
			}
			else
			{
				for (int i = 0; i < _dragchaiY + 1; i++)
				{
					for (int j = 0; j < _dragchaiX + 1; j++)
					{
						IMAGEMANAGER->frameRender("stage2", _ptMouse.x - 20 + (TILESIZE * j), _ptMouse.y - 20 + (TILESIZE * i), _dragStartIdX + j, _dragStartIdY + i, 0.3);
					}
				}
			}
			break;
		case BOSS_STAGE:
			if (!_dragMod)
			{
				IMAGEMANAGER->frameRender("bossStage", _ptMouse.x - 20, _ptMouse.y - 20, _tempTile.frameX, _tempTile.frameY, 0.3);
			}
			else
			{
				for (int i = 0; i < _dragchaiY + 1; i++)
				{
					for (int j = 0; j < _dragchaiX + 1; j++)
					{
						IMAGEMANAGER->frameRender("bossStage", _ptMouse.x - 20 + (TILESIZE * j), _ptMouse.y - 20 + (TILESIZE * i), _dragStartIdX + j, _dragStartIdY + i, 0.3);
					}
				}
			}
			break;
		}
	}
}

void mapTool::buttonInit()
{
	_increaseXMap = std::move(bind(&mapTool::increaseX, this));
	_decreaseXMap = std::move(bind(&mapTool::decreaseX, this));
	_increaseYMap = std::move(bind(&mapTool::increaseY, this));
	_decreaseYMap = std::move(bind(&mapTool::decreaseY, this));

	_increaseXButton = new button;
	_increaseXButton->init("button", WINSIZEX / 2, 700, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), _increaseXMap);
	_decreaseXButton = new button;
	_decreaseXButton->init("button", WINSIZEX / 2, 800, PointMake(2, 1), PointMake(0, 1), PointMake(1, 1), _decreaseXMap);
	_increaseYButton = new button;
	_increaseYButton->init("button", WINSIZEX / 2 + 150, 700, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), _increaseYMap);
	_decreaseYButton = new button;
	_decreaseYButton->init("button", WINSIZEX / 2 + 150, 800, PointMake(2, 1), PointMake(0, 1), PointMake(1, 1), _decreaseYMap);
	_mapPageAddButton = new button;
	_mapPageAddButton->init("button", WINSIZEX - 200, 750, PointMake(2, 2), PointMake(0, 2), PointMake(1, 2), cbMapPageAdd);
	_mapPageSubButton = new button;
	_mapPageSubButton->init("button", WINSIZEX - 250, 750, PointMake(2, 3), PointMake(0, 3), PointMake(1, 3), cbMapPageSub);
	_saveButton = new button;
	_saveButton->init("button2", WINSIZEX - 650, 680, PointMake(2, 2), PointMake(0, 2), PointMake(1, 2), cbMapSaveButton);
	_loadButton = new button;
	_loadButton->init("button2", WINSIZEX - 650, 750, PointMake(2, 3), PointMake(0, 3), PointMake(1, 3), cbMapLoadButton);
	_terrainButton = new button;
	_terrainButton->init("button2", WINSIZEX - 200, 750, PointMake(2, 1), PointMake(0, 1), PointMake(1, 1), cbTerrainTile);
	_objectButton = new button;
	_objectButton->init("button2", WINSIZEX - 200, 750, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), cbObjectTile);
	_eraserButton = new button;
	_eraserButton->init("button2", WINSIZEX - 200, 750, PointMake(2, 4), PointMake(0, 4), PointMake(1, 4), cbEraser);
	_windowSLAddButton = new button;
	_windowSLAddButton->init("button", WINSIZEX - 200, 750, PointMake(2, 2), PointMake(0, 2), PointMake(1, 2), bind(&mapTool::windowPageAdd, this));
	_windowSLSubButton = new button;
	_windowSLSubButton->init("button", WINSIZEX - 200, 750, PointMake(2, 3), PointMake(0, 3), PointMake(1, 3), bind(&mapTool::windowPageSub, this));
	_windowOKButton = new button;
	_windowOKButton->init("okButton", WINSIZEX - 200, 750, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), bind(&mapTool::mapSaveLoad, this));
}

void mapTool::buttonUpdate()
{
	_increaseXButton->update(WINSIZEX / 2 - 100, 680);
	_decreaseXButton->update(WINSIZEX / 2 - 100, 750);
	_increaseYButton->update(WINSIZEX / 2 + 50, 680);
	_decreaseYButton->update(WINSIZEX / 2 + 50, 750);
	_mapPageAddButton->update(WINSIZEX - 50, 720);
	_mapPageSubButton->update(WINSIZEX - 200, 720);
	_saveButton->update(WINSIZEX - 650, 680);
	_loadButton->update(WINSIZEX - 650, 750);
	_terrainButton->update(WINSIZEX - 500, 680);
	_objectButton->update(WINSIZEX - 500, 750);
	_eraserButton->update(WINSIZEX - 350, 680);
	_windowSLAddButton->update(_window.x + 440, _window.y + 570);
	_windowSLSubButton->update(_window.x + 300, _window.y + 570);
	_windowOKButton->update(_window.x + 370, _window.y + 570);
	
}

void mapTool::buttonRender()
{
	_increaseXButton->render();
	_decreaseXButton->render();
	_increaseYButton->render();
	_decreaseYButton->render();
	_mapPageAddButton->render();
	_mapPageSubButton->render();
	_saveButton->render();
	_loadButton->render();
	_eraserButton->render();
	_objectButton->render();
	_terrainButton->render();
	if (_saveOn || _loadOn)
	{
		IMAGEMANAGER->findImage("window")->render(_window.x + 220 + CAMERA->getCameraX(), _window.y + 330 + CAMERA->getCameraY());
		if (_saveOn)
		{
			IMAGEMANAGER->findImage("button2")->frameRender(_window.x + 270 + CAMERA->getCameraX(), _window.y + 345 + CAMERA->getCameraY(), 0, 2);
		}
		if (_loadOn)
		{
			for (int i = 0; i < 35; i++)
			{
				_vvMiniMap[i].clear();
			}
			_vvMiniMap.clear();
			
			HANDLE file = NULL;
			DWORD load;
			if (_pageSL == 0)
			{
				file = CreateFile("saveFile/저장_1.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			}
			if (_pageSL == 1)
			{
				file = CreateFile("saveFile/저장_2.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			}
			if (_pageSL == 2)
			{
				file = CreateFile("saveFile/저장_3.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			}
			IMAGEMANAGER->findImage("button2")->frameRender(_window.x + 270 + CAMERA->getCameraX(), _window.y + 345 + CAMERA->getCameraY(), 0, 3);
			
			int _tileX;
			int _tileY;
			ReadFile(file, &_tileX, sizeof(int), &load, NULL);
			ReadFile(file, &_tileY, sizeof(int), &load, NULL);
			
			for (int j = 0; j < 35; ++j)
			{
				vector<tagTile*> vTile;
				for (int i = 0; i < 60; ++i)
				{
					tagTile* tempTile = new tagTile;
					ZeroMemory(tempTile, sizeof(tagTile));
					vTile.push_back(tempTile);
				}
				_vvMiniMap.push_back(vTile);
			}
			
			for (int i = 0; i < _tileY; i++)
			{
				for (int j = 0; j < _tileX; j++)
				{
					if (i > 35) continue;
					if (j > 60) continue;

					int height;
					OBJECT obj;
					int objFrameX;
					int objFrameY;
					int selectTile;
					TERRAIN terrain;
					int trFrameX;
					int trFrameY;
			
					ReadFile(file, &height, sizeof(int), &load, NULL);
					ReadFile(file, &obj, sizeof(OBJECT), &load, NULL);
					ReadFile(file, &objFrameX, sizeof(int), &load, NULL);
					ReadFile(file, &objFrameY, sizeof(int), &load, NULL);
					ReadFile(file, &selectTile, sizeof(int), &load, NULL);
					ReadFile(file, &terrain, sizeof(TERRAIN), &load, NULL);
					ReadFile(file, &trFrameX, sizeof(int), &load, NULL);
					ReadFile(file, &trFrameY, sizeof(int), &load, NULL);
			
					_vvMiniMap[i][j]->setheightTile(height);
					_vvMiniMap[i][j]->setObject(obj);
					_vvMiniMap[i][j]->setOBJFrameX(objFrameX);
					_vvMiniMap[i][j]->setOBJFrameY(objFrameY);
					_vvMiniMap[i][j]->setSelectTile(selectTile);
					_vvMiniMap[i][j]->setTerrain(terrain);
					_vvMiniMap[i][j]->setTerrainFrameX(trFrameX);
					_vvMiniMap[i][j]->setTerrainFrameY(trFrameY);
			
					IMAGEMANAGER->frameRender("stage1_1(mini)", (_window.x + 250 + (j * 4)) + CAMERA->getCameraX(), (_window.y + 400 + (i * 4)) + CAMERA->getCameraY(), _vvMiniMap[i][j]->terrainFrameX, _vvMiniMap[i][j]->terrainFrameY);
					IMAGEMANAGER->frameRender("stage1_1(mini)", (_window.x + 250 + (j * 4)) + CAMERA->getCameraX(), (_window.y + 400 + (i * 4)) + CAMERA->getCameraY(), _vvMiniMap[i][j]->objFrameX, _vvMiniMap[i][j]->objFrameY);
				
				}
			}
			CloseHandle(file);
		}
		IMAGEMANAGER->findImage("number")->frameRender(_window.x + 420 + CAMERA->getCameraX(), _window.y + 345 + CAMERA->getCameraY(), _pageSL, 0);

		_windowSLAddButton->render();
		_windowSLSubButton->render();
		_windowOKButton->render();
	}

	switch (_buttonSelect)
	{
	case 0:
		IMAGEMANAGER->findImage("button2")->frameRender((WINSIZEX - 500 - IMAGEMANAGER->findImage("button2")->GetFrameWidth() / 2) + CAMERA->getCameraX(),
															(680 - IMAGEMANAGER->findImage("button2")->GetFrameHeight() / 2) + CAMERA->getCameraY(), 2, 1);
		break;
	case 1:
		IMAGEMANAGER->findImage("button2")->frameRender((WINSIZEX - 500 - IMAGEMANAGER->findImage("button2")->GetFrameWidth() / 2) + CAMERA->getCameraX(),
															(750 - IMAGEMANAGER->findImage("button2")->GetFrameHeight() / 2) + CAMERA->getCameraY(), 2, 0);
		break;
	case 2:
		IMAGEMANAGER->findImage("button2")->frameRender((WINSIZEX - 350 - IMAGEMANAGER->findImage("button2")->GetFrameWidth() / 2) + CAMERA->getCameraX(),
															(680 - IMAGEMANAGER->findImage("button2")->GetFrameHeight() / 2) + CAMERA->getCameraY(), 2, 4);
		break;
	}
}

void mapTool::increaseX()
{
	for (int i = 0; i < TILEY; i++)
	{
		tagTile* tempTile = new tagTile;

		tempTile->terrainFrameX = 31;
		tempTile->terrainFrameY = 18;
		tempTile->heightTile = 0;
		tempTile->objFrameX = 31;
		tempTile->objFrameY = 18;

		tempTile->terrain = TERRAIN::TR_FLOOR;
		tempTile->obj = OBJECT::OBJ_NONE;

		_vvTile[i].push_back(tempTile);
	}
	TILEX++;
}

void mapTool::increaseY()
{
	vector<tagTile*> vTile;
	for (int i = 0; i < TILEX; ++i)
	{
		tagTile* tempTile = new tagTile;

		tempTile->terrainFrameX = 31;
		tempTile->terrainFrameY = 18;
		tempTile->heightTile = 0;
		tempTile->objFrameX = 31;
		tempTile->objFrameY = 18;


		vTile.push_back(tempTile);
	}
	_vvTile.push_back(vTile);
	TILEY++;
}

void mapTool::decreaseX()
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

void mapTool::decreaseY()
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

void mapTool::mapSaveLoad()
{
	if (_saveOn)
	{
		_save = true;
	}
	else if (_loadOn)
	{
		_load = true;
	}
}

void mapTool::windowPageAdd()
{
	if (_pageSL < 2)
	{
		_pageSL++;
	}
}

void mapTool::windowPageSub()
{
	if (_pageSL > 0)
	{
		_pageSL--;
	}
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

void mapTool::cbMapPageAdd()
{
	if (_mapSelect < 4)
	{
		_mapSelect++;
	}
}

void mapTool::cbMapPageSub()
{
	if (_mapSelect > 0)
	{
		_mapSelect--;
	}
}

void mapTool::cbMapSaveButton()
{
	if (_loadOn)
		_loadOn = false;
	if(!_saveOn)
		_saveOn = true;
	else _saveOn = false;
}

void mapTool::cbMapLoadButton()
{
	if (_saveOn)
		_saveOn = false;
	if(!_loadOn)
		_loadOn = true;
	else _loadOn = false;
}

void mapTool::mapSave()
{
	if (_save)
	{
		HANDLE file = NULL;
		DWORD save;

		int _tileX = TILEX;
		int _tileY = TILEY;
		if (_pageSL == 0)
		{
			file = CreateFile("saveFile/저장_1.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		if (_pageSL == 1)
		{
			file = CreateFile("saveFile/저장_2.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		if (_pageSL == 2)
		{
			file = CreateFile("saveFile/저장_3.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		
		WriteFile(file, &_tileX, sizeof(int), &save, NULL);
		WriteFile(file, &_tileY, sizeof(int), &save, NULL);

		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
		
				int height;
				OBJECT obj;
				int objFrameX;
				int objFrameY;
				int selectTile;
				TERRAIN terrain;
				int trFrameX;
				int trFrameY;

		
				//height = _vvTile[j][i]->getHeightTile();
				obj = _vvTile[i][j]->getObject();
				objFrameX = _vvTile[i][j]->getOBJFrameX();
				objFrameY = _vvTile[i][j]->getOBJFrameY();
				selectTile = _vvTile[i][j]->getSelectTile();
				terrain = _vvTile[i][j]->getTerrain();
				trFrameX = _vvTile[i][j]->getTerrainFrameX();
				trFrameY = _vvTile[i][j]->getTerrainFrameY();
		
				WriteFile(file, &height, sizeof(int), &save, NULL);
				WriteFile(file, &obj, sizeof(OBJECT), &save, NULL);
				WriteFile(file, &objFrameX, sizeof(int), &save, NULL);
				WriteFile(file, &objFrameY, sizeof(int), &save, NULL);
				WriteFile(file, &selectTile, sizeof(int), &save, NULL);
				WriteFile(file, &terrain, sizeof(TERRAIN), &save, NULL);
				WriteFile(file, &trFrameX, sizeof(int), &save, NULL);
				WriteFile(file, &trFrameY, sizeof(int), &save, NULL);
			}
		}
		CloseHandle(file);
		_save = false;
	}
}

void mapTool::mapLoad()
{
	if (_load)
	{
		for (int i = 0; i < TILEY; i++)
		{
			_vvTile[i].clear();
		}
		_vvTile.clear();

		HANDLE file = NULL;
		DWORD load;

		int _tileX;
		int _tileY;

		if (_pageSL == 0)
		{
			file = CreateFile("saveFile/저장_1.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		if (_pageSL == 1)
		{
			file = CreateFile("saveFile/저장_2.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		if (_pageSL == 2)
		{
			file = CreateFile("saveFile/저장_3.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		}

		ReadFile(file, &_tileX, sizeof(int), &load, NULL);
		ReadFile(file, &_tileY, sizeof(int), &load, NULL);

		setTileX(_tileX);
		setTileY(_tileY);

		
		for (int j = 0; j < TILEY; ++j)
		{
			vector<tagTile*> vTile;
			for (int i = 0; i < TILEX; ++i)
			{
				tagTile* tempTile = new tagTile;
				ZeroMemory(tempTile, sizeof(tagTile));
				vTile.push_back(tempTile);
			}
			_vvTile.push_back(vTile);
		}

		

		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				int height;
				OBJECT obj;
				int objFrameX;
				int objFrameY;
				int selectTile;
				TERRAIN terrain;
				int trFrameX;
				int trFrameY;
		
		
				ReadFile(file, &height, sizeof(int), &load, NULL);
				ReadFile(file, &obj, sizeof(OBJECT), &load, NULL);
				ReadFile(file, &objFrameX, sizeof(int), &load, NULL);
				ReadFile(file, &objFrameY, sizeof(int), &load, NULL);
				ReadFile(file, &selectTile, sizeof(int), &load, NULL);
				ReadFile(file, &terrain, sizeof(TERRAIN), &load, NULL);
				ReadFile(file, &trFrameX, sizeof(int), &load, NULL);
				ReadFile(file, &trFrameY, sizeof(int), &load, NULL);
		
				_vvTile[i][j]->setheightTile(height);
				_vvTile[i][j]->setObject(obj);
				_vvTile[i][j]->setOBJFrameX(objFrameX);
				_vvTile[i][j]->setOBJFrameY(objFrameY);
				_vvTile[i][j]->setSelectTile(selectTile);
				_vvTile[i][j]->setTerrain(terrain);
				_vvTile[i][j]->setTerrainFrameX(trFrameX);
				_vvTile[i][j]->setTerrainFrameY(trFrameY);
			}
		}
		CloseHandle(file);
		_load = false;
	}
}

void mapTool::cbTerrainTile()
{
	_buttonSelect = 0;
}

void mapTool::cbObjectTile()
{
	_buttonSelect = 1;
}

void mapTool::cbEraser()
{
	_buttonSelect = 2;
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


























