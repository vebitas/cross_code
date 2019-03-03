#pragma once

#define TILESIZE 32

#define TILECOUNTX 200
#define TILECOUNTY 200

#define SAMPLETILEX 32
#define SAMPLETILEY 19

enum class HEIGTH
{
	TILE_HEIGHT_ZERO,		//언무브
	TILE_HEIGTH_ONE,		//무브
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
	int tileNum;
	int heightTile;

	
};

typedef class tagSampleTile
{
public:
	D2D_RECT_F tileRc;
	int frameX;
	int frameY;
};

