#pragma once
#include "image.h"

class gameNode
{
private:

	//�Ŵ����� �̴��Ҳ��� ����
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	//���� ���� -> ����� ��忡�� �ʱ�ȭ�� �ߵǾ����� ������ ������ ���� ����
	//S_OK, E_FAIL, SUCCEDED ������ �˷���.
	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	

};

