#pragma once
#include "gameNode.h"
#include "button.h"

static button* _newGameButton;
static button* _optionButton;
static button* _exidButton;

class menuScene : public gameNode
{
private:
	//인트로 로고이미지
	image* _fish;
	//인트로 로고(글씨)
	image* _fishText;
	//로고 y축
	float _rfgFishY;
	//로고 알파값
	float _rfgAlpha;
	float _rfgTextAlpha;
	float _blackgroundAlpha;
	//타이틀로고 y축 알파값, 인트로필요한 y축 및 알파값들
	float _titleLogoPosY , _titleLogoAlpha;
	float _cloudPosY, _cloudAlpha;
	float _groundPosY, _groundAlpha;
	float _skyPosY, _skyAlpha;
	float _planetPosY, _planetAlpha;
	float _railingsPosY, _railingsAlpha;
	float _leaPosY, _leaAlpha;
	float _keyboardAlpha;
	int _leaFrameX, _count;
	//순서
	int _next;
	//글씨 깜빡이게 체크해주는 불변수 
	bool _fade;
	//버튼 x축
	float _newGameBPosX;
	float _optionBPosX;
	float _exidBPosX;
	float _buttonCount;

public:
	menuScene();
	~menuScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void introRender();
	void introUpdate();

	static void newGameB();
	static void optionB();
	static void exidB();

	void setWindowsSize(int x, int y, int width, int height);
};

