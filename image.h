#pragma once
#include "animation.h"

class image
{
public:

	typedef struct tagImageInfo
	{
		DWORD					resID;
		IWICImagingFactory*		WICImagingFactory;		//Windows Imaging Component�� ���� Factory �������̽�
		IWICFormatConverter*	WICFormatConverter;		//Format Converter
		IWICBitmapDecoder*		WICDecoder;				//Bitmap Decoder
		IWICBitmapFrameDecode*	WICFrameDecoder;		//������ ������ ���ڵ��� Decoder �������̽�
		ID2D1Bitmap*			bitmap;					//D2D�� ��Ʈ��
		int						width;					//���� �̹��� ��
		int						height;					//���� �̹��� ����
		int						currentFrameX;			//���� ������X(��°)
		int						currentFrameY;			//���� ������Y(��°)
		int						maxFrameX;				//�ִ������� 
		int						maxFrameY;
		int						frameWidth;				//������ ���� ũ��
		int						frameHeight;			//������ ���� ũ��
		tagImageInfo()
		{
			resID				= 0;
			WICImagingFactory	= nullptr;
			WICFormatConverter	= nullptr;
			WICDecoder			= nullptr;
			WICFrameDecoder		= nullptr;
			bitmap				= nullptr;
			width				= 0;
			height				= 0;
			currentFrameX		= 0;
			currentFrameY		= 0;
			maxFrameX			= 0;
			maxFrameY			= 0;
			frameWidth			= 0;
			frameHeight			= 0;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO		_imageInfo;		//�̹��� ������ ���� ����ü
	LPWSTR				_fileName;		//�����̸��� ����� ĳ����������


public:
	image();
	~image();

	
	//===================================================================
	//							�̹��� �ʱ�ȭ
	//===================================================================
	
	// �Ϲ� �̹����� ���Ͽ��� ������ ��, ���ϸ�, ���� �ʺ�, ���� ����
	HRESULT init(LPCWSTR fileName, int width, int height);

	// ������ �̹����� ���Ͽ��� ������ ��, ���ϸ�, ���� �ʺ�, ���� ����, ���� ������ ��, ���� ������ ��
	HRESULT init(LPCWSTR fileName, int width, int height, int frameNumX, int frameNumY);

	// �̹��� ������
	void release(void);


	
	//===================================================================
	//						D2D ��� ���� �Լ�
	//- ī�޶� �̵� ���� & ������ ���� ���븸 ����
	//- Left Top ����
	//===================================================================
	

	//�⺻ ���
	void render(float alpha);

	//���� ũ�� ��� - �׷��� x��ǥ, y��ǥ, ����
	void render(float destX, float destY, float alpha = 1.0f);

	//���� ũ�� ��� - �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ����, ����
	void render(float destX, float destY, int showWidth, int showHeight, float alpha = 1.0f);

	//���� ũ��� �߶� �������� - �׷��� x��ǥ, y��ǥ -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void render(float destX, float destY, float sourX, float sourY,
		int sourWidth, int sourHeight, float alpha = 1.0f);

	//���� ũ��� �߶� �������� - �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���� -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void render(float destX, float destY, int showWidth, int showHeight, float sourX, float sourY,
		int sourWidth, int sourHeight, float alpha = 1.0f);


	//���� ũ�� �����ӷ��� - �׷��� x, y ��ǥ, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void frameRender(float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0f);


	void frameRenderAngle(float destX, float destY, int currentFrameX, int currentFrameY, float angle, float alpha = 1.0f);

	//���� ũ�� �����ӷ��� - �׷��� x, y ��ǥ, ����� �ʺ�, ����� ����, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void frameRender(float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float alpha = 1.0f);

	//���� ũ��� �߶� �������� �����ӷ��� - �׷��� x, y ��ǥ, ����� �ʺ�, ����� ����, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void frameRender(float destX, float destY, int sourX, int sourY, int sourWidth, int sourHeight, int currentFrameX, int currentFrameY, float alpha = 1.0f);


	//�¿����
	void frameRenderReverseX(float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0f);
	void frameRenderReverseX(float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float alpha = 1.0f);

	//���� ���� - ���� �ʿ�
	void loopRender(D2D1_RECT_F drawArea, int offSetX = 0, int offSetY = 0, float opacity = 1.0f);

	void aniRender(int destX, int destY, animation* ani);
	void aniRenderReverseX(int destX, int destY, animation* ani);

	
	//===================================================================
	//						�̹��� ���� Get, Set
	//===================================================================
	

	//���� ����~
	inline int GetWidth(void) { return _imageInfo->width; }

	//���� ����~
	inline int GetHeight(void) { return _imageInfo->height; }

	//������ �̹��� ����
	inline void SetFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void SetFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int GetMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int GetMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int GetFrameX(void) { return _imageInfo->currentFrameX; }
	inline int GetFrameY(void) { return _imageInfo->currentFrameY; }

	inline int GetFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int GetFrameHeight(void) { return _imageInfo->frameHeight; }




	//===================================================================
	//						���� �Լ�
	//===================================================================
private:
	POINTFLOAT GetRenderPosition(float destX, float destY);
	bool IsRnderPositionInWindow(POINTFLOAT pf, float width, float height);
};

