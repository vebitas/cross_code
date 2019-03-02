#pragma once
#include "singletonBase.h"
#include "fontLoader.h"

class camera;
class d2dManager : public singletonBase<d2dManager>
{
public:
	ID2D1Factory*				_d2dFactory;
	ID2D1HwndRenderTarget*		_renderTarget;
	IDWriteFactory*				_writeFactory;
	IDWriteTextFormat*			_defaultTextFormat;		//�⺻ �ؽ�Ʈ ����
	IDWriteTextFormat*			_customTextFormat;		//Ŀ���� �ؽ�Ʈ ����
	ID2D1SolidColorBrush*		_defaultBrush;			//�⺻ ������ �귯��

	IDWriteFontCollection*		_collection;			//��Ʈ���� ���ִ°�~ Ŀ������Ʈ ���� ����
	
	IWICImagingFactory*		WICImagingFactory;

public:
	d2dManager();
	~d2dManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void beginDraw();
	void endDraw();
	ID2D1SolidColorBrush* createBrush(COLORREF rgb, float opacity = 1.0f);


	HRESULT createCollection(wstring path);


	
	//===================================================================
	//			Draw, Fill Method (Line, Rectangle, Ellipse)
	//- ī�޶� �̵� ���� & ������ ���� ���븸 ����
	//===================================================================
	

	void drawLine(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	//������
	void drawLine(float startX, float startY, float endX, float endY);
	//����
	void drawLine(COLORREF rgb, float startX, float startY, float endX, float endY);


	void drawRectangle(COLORREF rgb, float left, float top, float right, float bottom);
	void drawRectangle(float left, float top, float right, float bottom);

	void drawRectangle(D2D_RECT_F rc);
	void drawRectangle(COLORREF rgb, D2D_RECT_F rc);

	void drawEllipse(COLORREF rgb, float left, float top, float right, float bottom);
	void drawEllipse(float left, float top, float right, float bottom);

	void drawEllipse(D2D1_ELLIPSE e);
	void drawEllipse(COLORREF rgb, D2D1_ELLIPSE e);




	void fillRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY);
	void fillRectangle(COLORREF rgb, D2D_RECT_F rc);
	void fillEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY);
	void fillEllipse(COLORREF rgb, D2D1_ELLIPSE e);

	
	void drawText(LPCWSTR string, float x, float y);
	void drawText(LPCWSTR string, float x, float y, int fontSize);
	void drawText(LPCWSTR string, float x, float y, int fontSize, COLORREF rgb);
	//����� ���ڿ�, ���ڿ��� �׸� Rect�� Left, Top, Right, Bottom, �׸� �귯��
	void drawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR string, float startX, float startY, float endX, float endY);

	//����� ���ڿ�, ���ڿ��� �׸� Rect�� Left, Top, Right, Bottom, �׸� �귯��, ��Ʈ��, ��Ʈ ũ��
	void drawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);



	//===================================================================
	//			���� �Լ�
	//===================================================================

private:
	D2D1_RECT_F getDrawRectfArea( float startX, float startY, float endX, float endY);
	bool		isRectFInRangeWindow(const D2D1_RECT_F& rcf );
};

