#pragma once

#define TILESIZE 32

#define TILECOUNTX 200
#define TILECOUNTY 200

#define SAMPLETILEX 32
#define SAMPLETILEY 19

enum class HEIGTH
{
	TILE_HEIGHT_ZERO,		//�𹫺�
	TILE_HEIGTH_ONE,		//����
	TILE_HEIGHT_TWO,
	TILE_HEIGHT_THREE
};

enum class TERRAIN
{
	TR_FLOOR, TR_WATER, TR_FALL
};

enum class OBJECT
{
	OBJ_WALL,
	OBJ_GRASS,
	OBJ_SWITCH,
	OBJ_BOX,
	OBJ_PIPE,
	OBJ_NONE
};

enum class CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_END
};

struct tagTempTile
{
	int frameX;
	int frameY;
};

typedef class tagTile 
{
public:
	tagTile() : terrainFrameX(NULL),
		terrainFrameY(NULL),
		terrain(TERRAIN::TR_FLOOR),
		obj(OBJECT::OBJ_NONE),
		objFrameX(NULL),
		objFrameY(NULL),
		selectTile(NULL),
		heightTile(NULL)
	{};
	~tagTile() {};
	int terrainFrameX;
	int terrainFrameY;
	TERRAIN terrain;
	OBJECT obj;
	int objFrameX;
	int objFrameY;
	int selectTile;
	int heightTile;

public:
	//======================== ������  ���� =============================
	int getTerrainFrameX() { return terrainFrameX; }
	int getTerrainFrameY() { return terrainFrameY; }
	TERRAIN getTerrain() { return terrain; }
	OBJECT getObject() { return obj; }
	int getOBJFrameX() { return objFrameX; }
	int getOBJFrameY() { return objFrameY; }
	int getSelectTile() { return selectTile; }
	int getHeightTile() { return heightTile; }

	// ======================= ������  ���� =============================
	void setTerrainFrameX(int trFrameX) { terrainFrameX = trFrameX; }
	void setTerrainFrameY(int trFrameY) { terrainFrameY = trFrameY; }
	void setTerrain(TERRAIN tr) { terrain = tr; }
	void setObject(OBJECT object) { obj = object; }
	void setOBJFrameX(int objX) { objFrameX = objX; }
	void setOBJFrameY(int objY) { objFrameY = objY; }
	void setSelectTile(int selTile) { selectTile = selTile; }
	void setheightTile(int height) { heightTile = height; }
};

typedef class tagSampleTile
{
public:
	D2D_RECT_F tileRc;
	int frameX;
	int frameY;
};

