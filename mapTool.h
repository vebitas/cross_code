#pragma once
#include "gameNode.h"
#include "MapNode.h"
#include "button.h"
#include <vector>
#include <functional>

#define SAMPLE_TOTAL_SIZEX	SAMPLETILEX * TILESIZE

#define SAMPLE_TILE_STARTX	WINSIZEX - SAMPLE_TOTAL_SIZEX

#define OUTPUTSIZEX 700
#define OUTPUTSIZEY 800

static button*	_increaseXButton;
static button*  _increaseYButton;
static button*	_decreaseXButton;
static button*	_decreaseYButton;


class mapTool : public gameNode
{
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

	DWORD setAttribute(string imgName, UINT frameX, UINT frameY);

private:
	vector<vector<tagTile*>> _vvTile;

	tagTempTile _tempTile;

	button* _saveButton;

	UINT		TILEX;					
	UINT		TILEY;

	POINT _ptViewMouse;

	tagSampleTile _sampleTile[SAMPLETILEY][SAMPLETILEX];

	int _ptIdX;
	int _ptIdY;

	int _ptSPidX;
	int _ptSPidY;

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void setTile();												//Ÿ�� �ʱⰪ
	void pickSampleTile();										//Ŭ���� ����Ÿ�� ������ ��ȣ ����
	void setMap();												//Ŭ���� �ʿ��� ������ ������ ��ȣ�� ��Ÿ�� �����ӿ� �־���

	void increaseX();											//�ݹ��Լ� �� x,y�� ����
	void increaseY();
	void decreaseX();											//�ݹ��Լ� �� x,y�� ����
	void decreaseY();

	function<void(void)> _increaseXMap;
	function<void(void)> _increaseYMap;
	function<void(void)> _decreaseXMap;
	function<void(void)> _decreaseYMap;

	void increaseMap();
	void decreaseMap();

	void setWindowsSize(int x, int y, int width, int height);	//������ âũ�� ����

	TERRAIN terraniSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
};
