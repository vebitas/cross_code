#pragma once
#include "gameNode.h"
#include "stageOneMap.h"
#include "player.h"
#include "enemyManager.h"

class stage_1 : public gameNode
{
private:
	stageOneMap* _oneMap;
	player* _player;
	enemyManager* _enemyManager;
	//Ÿ��üũ
	POINT _tileIndex[3];
	POINTF _playerSavePos;
	
	D2D1_RECT_F rc[2];
	D2D1_RECT_F _teleportRc;
	D2D1_RECT_F _briRc;
	//�ٸ�����Ʈ�� �ʿ��� ������
	int _briFrameX, _briFrameY;
	float _briAlpha;
	int _count;
	//�� ü���� �Ҷ� ȭ��Ʈ��� �� �ƿ�
	float _sceneChangeAlpha;

	int _hog;
	bool _hogAttack;

	int _teleportFrameX;

public:
	stage_1();
	~stage_1();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileCheck();
	void enemyTileCheck();
	void playerCollision();
	void enemyCollision();
	void teleportRcCollision();

	void setWindowsSize(int x, int y, int width, int height);

private:
	//�����Լ�

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}
};

