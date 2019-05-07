#include "stdafx.h"
#include "stageTwoMap.h"


stageTwoMap::stageTwoMap()
{
}


stageTwoMap::~stageTwoMap()
{
}

HRESULT stageTwoMap::init()
{
	load();
	return S_OK;
}

void stageTwoMap::release()
{
}

void stageTwoMap::update()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_rc[i][j] = { (float)0 + (j * TILESIZE), (float)0 + (i * TILESIZE), (float)32 * (j * TILESIZE + TILESIZE), (float)32 * (i * TILESIZE + TILESIZE) };
		}
	}
}

void stageTwoMap::render()
{
	for (int i = 0; i < TILEY; i++)			//≈∏¿œ∏  
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (j >= TILEX) continue;
			if (i >= TILEY) continue;
			if (j < 0) continue;
			if (i < 0) continue;


			switch (_vvMap[i][j]->selectTile)
			{
			case STAGE1_1:
				_vvMap[i][j]->trImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->terrainFrameX, _vvMap[i][j]->terrainFrameY);
				break;
			case STAGE1_2:
				_vvMap[i][j]->trImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->terrainFrameX, _vvMap[i][j]->terrainFrameY);
				break;
			case STAGE1_3:
				_vvMap[i][j]->trImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->terrainFrameX, _vvMap[i][j]->terrainFrameY);
				break;
			case STAGE2:
				_vvMap[i][j]->trImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->terrainFrameX, _vvMap[i][j]->terrainFrameY);
				break;
			case BOSS_STAGE:
				_vvMap[i][j]->trImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->terrainFrameX, _vvMap[i][j]->terrainFrameY);
				break;
			}


			switch (_vvMap[i][j]->selectOBJ)
			{
			case STAGE1_1:
				_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
				break;
			case STAGE1_2:
				_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
				break;
			case STAGE1_3:
				_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
				break;
			case STAGE2:
				_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
				break;
			case BOSS_STAGE:
				_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
				break;
			}

			//D2DMANAGER->drawRectangle(RGB(255, 0, 255), _rc[i][j]);
		}
	}
}

void stageTwoMap::load()
{


	HANDLE file = NULL;
	DWORD load;

	int _tileX;
	int _tileY;


	file = CreateFile("saveFile/¿˙¿Â_2.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &_tileX, sizeof(int), &load, NULL);
	ReadFile(file, &_tileY, sizeof(int), &load, NULL);

	TILEX = _tileX;
	TILEY = _tileY;

	for (int j = 0; j < TILEY; ++j)
	{
		vector<tagTile*> vTile;
		for (int i = 0; i < TILEX; ++i)
		{
			tagTile* tempTile = new tagTile;
			ZeroMemory(tempTile, sizeof(tagTile));
			vTile.push_back(tempTile);
		}
		_vvMap.push_back(vTile);
	}


	
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//int height;
			OBJECT obj;
			int objFrameX;
			int objFrameY;
			int selectTile;
			TERRAIN terrain;
			int trFrameX;
			int trFrameY;
			int selectOBJ;

			//ReadFile(file, &height, sizeof(int), &load, NULL);
			ReadFile(file, &obj, sizeof(OBJECT), &load, NULL);
			ReadFile(file, &objFrameX, sizeof(int), &load, NULL);
			ReadFile(file, &objFrameY, sizeof(int), &load, NULL);
			ReadFile(file, &selectTile, sizeof(int), &load, NULL);
			ReadFile(file, &terrain, sizeof(TERRAIN), &load, NULL);
			ReadFile(file, &trFrameX, sizeof(int), &load, NULL);
			ReadFile(file, &trFrameY, sizeof(int), &load, NULL);
			ReadFile(file, &selectOBJ, sizeof(int), &load, NULL);

			//_vvTile[i][j]->setheightTile(height);
			_vvMap[i][j]->setObject(obj);
			_vvMap[i][j]->setOBJFrameX(objFrameX);
			_vvMap[i][j]->setOBJFrameY(objFrameY);
			_vvMap[i][j]->setSelectTile(selectTile);
			_vvMap[i][j]->setTerrain(terrain);
			_vvMap[i][j]->setTerrainFrameX(trFrameX);
			_vvMap[i][j]->setTerrainFrameY(trFrameY);
			_vvMap[i][j]->setSelectOBJ(selectOBJ);


			if (selectTile == 0)
			{
				_vvMap[i][j]->trImg = IMAGEMANAGER->findImage("stage1_1");
			}
			else if (selectTile == 1)
			{
				_vvMap[i][j]->trImg = IMAGEMANAGER->findImage("stage1_2");
			}
			else if (selectTile == 2)
			{
				_vvMap[i][j]->trImg = IMAGEMANAGER->findImage("stage1_3");
			}
			else if (selectTile == 3)
			{
				_vvMap[i][j]->trImg = IMAGEMANAGER->findImage("stage2");
			}
			else if (selectTile == 4)
			{
				_vvMap[i][j]->trImg = IMAGEMANAGER->findImage("bossStage");
			}

			if (selectOBJ == 0)
			{
				_vvMap[i][j]->objImg = IMAGEMANAGER->findImage("stage1_1");
			}
			else if (selectOBJ == 1)
			{
				_vvMap[i][j]->objImg = IMAGEMANAGER->findImage("stage1_2");
			}
			else if (selectOBJ == 2)
			{
				_vvMap[i][j]->objImg = IMAGEMANAGER->findImage("stage1_3");
			}
			else if (selectOBJ == 3)
			{
				_vvMap[i][j]->objImg = IMAGEMANAGER->findImage("stage2");
			}
			else if (selectOBJ == 4)
			{
				_vvMap[i][j]->objImg = IMAGEMANAGER->findImage("bossStage");
			}

			_vvMap[i][j]->setTerrain(TERRAIN::TR_FLOOR);

			if (_vvMap[i][j]->selectOBJ == 0 && ((_vvMap[i][j]->objFrameX == 6 && _vvMap[i][j]->objFrameY == 4) || (_vvMap[i][j]->objFrameX == 7 && _vvMap[i][j]->objFrameY == 4) || (_vvMap[i][j]->objFrameX == 8 && _vvMap[i][j]->objFrameY == 4)
				|| (_vvMap[i][j]->objFrameX == 6 && _vvMap[i][j]->objFrameY == 5) || (_vvMap[i][j]->objFrameX == 8 && _vvMap[i][j]->objFrameY == 5)
				|| (_vvMap[i][j]->objFrameX == 6 && _vvMap[i][j]->objFrameY == 6) || (_vvMap[i][j]->objFrameX == 7 && _vvMap[i][j]->objFrameY == 6) || (_vvMap[i][j]->objFrameX == 8 && _vvMap[i][j]->objFrameY == 6)
				|| (_vvMap[i][j]->objFrameX == 6 && _vvMap[i][j]->objFrameY == 7) || (_vvMap[i][j]->objFrameX == 7 && _vvMap[i][j]->objFrameY == 7) || (_vvMap[i][j]->objFrameX == 8 && _vvMap[i][j]->objFrameY == 7) || (_vvMap[i][j]->objFrameX == 9 && _vvMap[i][j]->objFrameY == 7)
				|| (_vvMap[i][j]->objFrameX == 6 && _vvMap[i][j]->objFrameY == 8) || (_vvMap[i][j]->objFrameX == 7 && _vvMap[i][j]->objFrameY == 8) || (_vvMap[i][j]->objFrameX == 8 && _vvMap[i][j]->objFrameY == 8) || (_vvMap[i][j]->objFrameX == 9 && _vvMap[i][j]->objFrameY == 8)))
			{
				_vvMap[i][j]->setObject(OBJECT::OBJ_LINE);
			}
			else if (_vvMap[i][j]->selectOBJ == 3 && ((_vvMap[i][j]->objFrameX == 0 && _vvMap[i][j]->objFrameY == 8) || (_vvMap[i][j]->objFrameX == 1 && _vvMap[i][j]->objFrameY == 8) || (_vvMap[i][j]->objFrameX == 0 && _vvMap[i][j]->objFrameY == 9)
				|| (_vvMap[i][j]->objFrameX == 1 && _vvMap[i][j]->objFrameY == 9) || (_vvMap[i][j]->objFrameX == 0 && _vvMap[i][j]->objFrameY == 10)
				|| (_vvMap[i][j]->objFrameX == 1 && _vvMap[i][j]->objFrameY == 10) || (_vvMap[i][j]->objFrameX == 0 && _vvMap[i][j]->objFrameY == 11) || (_vvMap[i][j]->objFrameX == 1 && _vvMap[i][j]->objFrameY == 11)
				|| (_vvMap[i][j]->objFrameX == 0 && _vvMap[i][j]->objFrameY == 12) || (_vvMap[i][j]->objFrameX == 1 && _vvMap[i][j]->objFrameY == 12) || (_vvMap[i][j]->objFrameX == 0 && _vvMap[i][j]->objFrameY == 13) || (_vvMap[i][j]->objFrameX == 1 && _vvMap[i][j]->objFrameY == 13)
				|| (_vvMap[i][j]->objFrameX == 2 && _vvMap[i][j]->objFrameY == 11) || (_vvMap[i][j]->objFrameX == 3 && _vvMap[i][j]->objFrameY == 11) || (_vvMap[i][j]->objFrameX == 4 && _vvMap[i][j]->objFrameY == 11) || (_vvMap[i][j]->objFrameX == 5 && _vvMap[i][j]->objFrameY == 11)
				|| (_vvMap[i][j]->objFrameX == 6 && _vvMap[i][j]->objFrameY == 11) || (_vvMap[i][j]->objFrameX == 7 && _vvMap[i][j]->objFrameY == 11)))
			{
				_vvMap[i][j]->setObject(OBJECT::OBJ_CONTAINER);
			}
			else
			{
				_vvMap[i][j]->setObject(OBJECT::OBJ_NONE);
			}

			_rc[i][j] = { (float)0 + (j * TILESIZE), (float)0 + (i * TILESIZE), (float)32 * (j * TILESIZE + TILESIZE), (float)32 * (i * TILESIZE + TILESIZE) };
		}
	}
	CloseHandle(file);
}

void stageTwoMap::zOrder()
{
	for (int i = 0; i < TILEY; i++)			//≈∏¿œ∏  
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (j >= TILEX) continue;
			if (i >= TILEY) continue;
			if (j < 0) continue;
			if (i < 0) continue;
			if (_vvMap[i][j]->obj == OBJECT::OBJ_GATE)
			{
				switch (_vvMap[i][j]->selectOBJ)
				{
				case STAGE1_1:
					_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
					break;
				case STAGE1_2:
					_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
					break;
				case STAGE1_3:
					_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
					break;
				case STAGE2:
					_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
					break;
				case BOSS_STAGE:
					_vvMap[i][j]->objImg->frameRender(j * TILESIZE, i * TILESIZE, _vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
					break;
				}
			}
		}
	}
}
