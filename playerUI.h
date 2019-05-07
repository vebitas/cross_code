#pragma once
#include "gameNode.h"

class playerUI : public gameNode
{
private:
	D2D1_RECT_F _rc[4];
	int _attributeFrameX;
	bool _isUI;
public:
	playerUI();
	~playerUI();

	HRESULT init();
	void release();
	void update();
	void render(int HP, int MAXHP, int LV);

	int getPlayerAttribute() { return _attributeFrameX; }
	int getPlayerUIMode() { return _isUI; }

private:
	//내부함수

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}
};

