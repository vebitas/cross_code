#include "stdafx.h"
#include "stageOneMap.h"


stageOneMap::stageOneMap()
{
}


stageOneMap::~stageOneMap()
{
}

HRESULT stageOneMap::init()
{
	//IMAGEMANAGER->addFrameImage("stage1_1", L"image/tileNode/stage1_1.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addFrameImage("stage1_2", L"image/tileNode/stage1_2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addFrameImage("stage1_3", L"image/tileNode/stage1_3.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addFrameImage("stage2", L"image/tileNode/stage2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addFrameImage("bossStage", L"image/tileNode/bossStage.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addFrameImage("stage1_1(mini)", L"image/tileNode/stage1_1(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addFrameImage("stage1_2(mini)", L"image/tileNode/stage1_2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addFrameImage("stage1_3(mini)", L"image/tileNode/stage1_3(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addFrameImage("stage2(mini)", L"image/tileNode/stage2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addFrameImage("bossStage(mini)", L"image/tileNode/bossStage(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	//IMAGEMANAGER->addImage("mapToolBackground", L"image/tileNode/mapToolBackground.png", WINSIZEX, WINSIZEY);
	//IMAGEMANAGER->addImage("build_LR", L"image/tileNode/build_LR.png", 64, 830);
	//IMAGEMANAGER->addImage("build_UD", L"image/tileNode/build_UD.png", 750, 64);
	//IMAGEMANAGER->addFrameImage("button", L"image/tileNode/button.png", 150, 200, 3, 4);
	//IMAGEMANAGER->addFrameImage("button2", L"image/tileNode/button_2.png", 375, 250, 3, 5);
	//IMAGEMANAGER->addFrameImage("textXY", L"image/tileNode/textXY.png", 96, 48, 2, 1);
	//IMAGEMANAGER->addImage("textMap", L"image/tileNode/textMap.png", 96, 48);
	//IMAGEMANAGER->addImage("window", L"image/tileNode/window.png", 300, 300);
	//IMAGEMANAGER->addFrameImage("okButton", L"image/tileNode/okButton.png", 144, 48, 3, 1);
	//IMAGEMANAGER->addFrameImage("number", L"image/tileNode/number.png", 144, 48, 3, 1);

	load();
	return S_OK;
}

void stageOneMap::release()
{
}

void stageOneMap::update()
{
	
}

void stageOneMap::render()
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

		}
	}
}

void stageOneMap::load()
{
	
	
	HANDLE file = NULL;
	DWORD load;
	
	int _tileX;
	int _tileY;


	file = CreateFile("saveFile/¿˙¿Â_1.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
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
		}
	}
	CloseHandle(file);
}
