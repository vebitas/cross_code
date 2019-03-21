#pragma once
#include "gameNode.h"
#include "MapNode.h"
#include "button.h"
#include "player.h"
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

//===============��ư����=============
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

static button* _windowSLAddButton;
static button* _windowSLSubButton;
static button* _windowOKButton;
//===================================

static int _mapSelect;
static int  _buttonSelect;
static bool _saveOn;
static bool _loadOn;

class mapTool : public gameNode
{


private:
	vector<vector<tagTile*>> _vvTile;
	vector<vector<tagTile*>> _vvMiniMap;

	tagTempTile _tempTile;

	button* _saveButton;

	UINT		TILEX;					
	UINT		TILEY;
	UINT		miniX, miniY;

	HCURSOR _cursor;

	POINT _dragTerm;

	tagSampleTile _sampleTile[SAMPLETILEY][SAMPLETILEX];
	
	D2D1_RECT_F _mouseCameraMoveRc[4];
	D2D1_RECT_F _selectTileRc;
	D2D1_RECT_F _selectSampleTileRc;

	int _ptIdX;
	int _ptIdY;

	int _ptSPidX;
	int _ptSPidY;
	//���� �巡�� ������ 
	int _dragStartIdX;
	int _dragStartIdY;
	int _dragEndidX;
	int _dragEndidY;
	int _dragchaiX;
	int _dragchaiY;
	//�� �巡�� ������
	int _mapDragStartX;
	int _mapDragStartY;
	int _mapDragEndX;
	int _mapDragEndY;
	int _mapDragchaiX;
	int _mapDragchaiY;

	int _pageSL;

	POINT _window;
	POINT _mapClippingPos;
	
	bool _dragFrameSave;
	bool _dragMod;
	bool _mapDragMod;
	bool _save, _load;

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void setTile();													//Ÿ�� �ʱⰪ
	void pickSampleTile();											//Ŭ���� ����Ÿ�� ������ ��ȣ ����
	void setMap();													//Ŭ���� �ʿ��� ������ ������ ��ȣ�� ��Ÿ�� �����ӿ� �־���
	void spDragMod();												//�巡�� ����Լ�
	void tilePreview();												//���õ� Ÿ�� �̸�����

	void buttonInit();
	void buttonUpdate();
	void buttonRender();

	//�ݹ��Լ� �� x,y�� ����
	void increaseX();											
	void increaseY();
	//�ݹ��Լ� �� x,y�� ����
	void decreaseX();												
	void decreaseY();

	void mapSaveLoad();
	void windowPageAdd();
	void windowPageSub();

	void imageSelect(int idX, int idY, int mapSelect, bool isTR);


	function<void(void)> _increaseXMap;
	function<void(void)> _increaseYMap;
	function<void(void)> _decreaseXMap;
	function<void(void)> _decreaseYMap;

	static void cbMapPageAdd();
	static void cbMapPageSub();

	static void cbMapSaveButton();
	static void cbMapLoadButton();

	void mapSave();
	void mapLoad();

	static void cbTerrainTile();
	static void cbObjectTile();
	static void cbEraser();

	void setWindowsSize(int x, int y, int width, int height);		//������ âũ�� ����

	TERRAIN terraniSelect(int selectTile, int frameX, int frameY);
	OBJECT objSelect(int selectOBJ, int frameX, int frameY);

public:

	UINT getTileX() { return TILEX; }
	UINT getTileY() { return TILEY; }

	void setTileX(UINT _tileX) { TILEX = _tileX; }
	void setTileY(UINT _tileY) { TILEY = _tileY; }



private:
	//�����Լ�

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}

	inline POINT makePOINT(POINTF pt)
	{
		return POINT{ (LONG)pt.x, (LONG)pt.y };
	}

	ATTRIBUTE setAttribute(tagTile selectNum, UINT frameX, UINT frameY);
};

