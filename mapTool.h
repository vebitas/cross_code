#pragma once
#include "gameNode.h"
#include "MapNode.h"
#include "button.h"
#include <vector>
#include <functional>

#define SAMPLE_TOTAL_SIZEX	SAMPLETILEX * TILESIZE

#define SAMPLE_TILE_STARTX	WINSIZEX - SAMPLE_TOTAL_SIZEX

#define CAMERASIZEX 
#define CAMERASIZEY

#define OUTPUTSIZEX 750
#define OUTPUTSIZEY 800

enum MAPNUMBER
{
	STAGE1_1 = 0,
	STAGE1_2,
	STAGE1_3,
	STAGE2,
	BOSS_STAGE
};

static button*	_increaseXButton;
static button*  _increaseYButton;
static button*	_decreaseXButton;
static button*	_decreaseYButton;
static button*	_mapPageAddButton;
static button*	_mapPageSubButton;

static button*	_saveButton;
static button*	_loadButton;
static button*	_terrainButton;
static button*	_objectButton;
static button*	_eraserButton;

static int _mapSelect;
static int  _buttonSelect;
static bool _save;
static bool _load;

class mapTool : public gameNode
{


private:
	vector<vector<tagTile*>> _vvTile;

	tagTempTile _tempTile;

	button* _saveButton;

	UINT		TILEX;					
	UINT		TILEY;

	POINT _dragTerm;

	tagSampleTile _sampleTile[SAMPLETILEY][SAMPLETILEX];
	
	D2D1_RECT_F _mouseCameraMoveRc[4];
	D2D1_RECT_F _selectTileRc;
	D2D1_RECT_F _selectSampleTileRc;

	int _ptIdX;
	int _ptIdY;

	int _ptSPidX;
	int _ptSPidY;

	int _dragStartIdX;
	int _dragStartIdY;
	int _dragEndidX;
	int _dragEndidY;
	int _dragchaiX;
	int _dragchaiY;

	POINT _mapClippingPos;
	
	bool _dragFrameSave;
	bool _dragMod;

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void setTile();													//타일 초기값
	void pickSampleTile();											//클릭한 샘플타일 프레임 번호 저장
	void setMap();													//클릭한 맵에다 저장한 프레임 번호를 맵타일 프레임에 넣어줌
	void dragMod();													//드래그 모드함수
	void tilePreview();												//선택된 타일 미리보기

	void buttonInit();
	void buttonUpdate();
	void buttonRender();

	void increaseX();												//콜백함수 맵 x,y축 증가
	void increaseY();
	void decreaseX();												//콜백함수 맵 x,y축 감소
	void decreaseY();


	function<void(void)> _increaseXMap;
	function<void(void)> _increaseYMap;
	function<void(void)> _decreaseXMap;
	function<void(void)> _decreaseYMap;

	static void cbMapPageAdd();
	static void cbMapPageSub();

	static void cbMapSave();
	static void cbMapLoad();
	void mapSave();
	void mapLoad();

	static void cbTerrainTile();
	static void cbObjectTile();
	static void cbEraser();

	void setWindowsSize(int x, int y, int width, int height);		//윈도우 창크기 설정

	TERRAIN terraniSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

public:
	
	UINT getTileX() { return TILEX; }
	UINT getTileY() { return TILEY; }

private:
	//내부함수

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}

	inline POINT makePOINT(POINTF pt)
	{
		return POINT{ (LONG)pt.x, (LONG)pt.y };
	}

	DWORD setAttribute(string imgName, UINT frameX, UINT frameY);
};

