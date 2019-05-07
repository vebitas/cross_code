#pragma once
#include "gameNode.h"
#include "button.h"

static button* _newGameButton;
static button* _optionButton;
static button* _exidButton;

class menuScene : public gameNode
{
private:
	//��Ʈ�� �ΰ��̹���
	image* _fish;
	//��Ʈ�� �ΰ�(�۾�)
	image* _fishText;
	//�ΰ� y��
	float _rfgFishY;
	//�ΰ� ���İ�
	float _rfgAlpha;
	float _rfgTextAlpha;
	float _blackgroundAlpha;
	//Ÿ��Ʋ�ΰ� y�� ���İ�, ��Ʈ���ʿ��� y�� �� ���İ���
	float _titleLogoPosY , _titleLogoAlpha;
	float _cloudPosY, _cloudAlpha;
	float _groundPosY, _groundAlpha;
	float _skyPosY, _skyAlpha;
	float _planetPosY, _planetAlpha;
	float _railingsPosY, _railingsAlpha;
	float _leaPosY, _leaAlpha;
	float _keyboardAlpha;
	int _leaFrameX, _count;
	//����
	int _next;
	//�۾� �����̰� üũ���ִ� �Һ��� 
	bool _fade;
	//��ư x��
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

