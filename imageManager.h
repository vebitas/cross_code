#pragma once

#include "singletonBase.h"
#include "image.h"
#include <map> //��� ���ص� �Ǵµ� �����غ� �� _��

class imageManager : public singletonBase<imageManager>
{
private:
	//map<string, image*> <-- �긦          mapImageList�� �θ��ڴ�.
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;


public:
	imageManager();
	~imageManager();


	HRESULT init(void);
	void release(void);


	
	//===================================================================
	//							�̹��� �߰�
	//===================================================================
	
	//�Ϲ� �̹��� �߰�
	image* addImage(string strKey, LPCWSTR fileName, int width, int height);

	//������ �̹��� �߰�
	image* addFrameImage(string strKey, LPCWSTR fileName, int width, int height, int frameNumX, int frameNumY);




	//�̹��� ã�� �Լ�
	image* findImage(string strKey);

	BOOL deleteImage(string strKey);

	BOOL deleteAll(void);

	//===================================================================
	//				���� �Լ� - Left Top �������� ����
	//===================================================================

	//�⺻ ���
	void render(string strKey, float alpha = 1.0f);

	//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����
	void render(string strKey, float destX, float destY, float alpha = 1.0f);

	//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���̤� ����
	void render(string strKey, float destX, float destY, int showWidth, int showHeight, float alpha = 1.0f);

	//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void render(string strKey, float destX, float destY, float sourX, float sourY,
		int sourWidth, int sourHeight, float alpha = 1.0f);

	//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���� -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void render(string strKey, float destX, float destY, int showWidth, int showHeight, float sourX, float sourY,
		int sourWidth, int sourHeight, float alpha = 1.0f);

	//��������
	void loopRender(string strKey, D2D1_RECT_F drawArea, int offSetX, int offSetY, float opacity = 1.0f);

	//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void frameRender(string strKey, float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0f);

	//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ����� �ʺ�, ����� ����, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void frameRender(string strKey, float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float alpha = 1.0f);

	//�¿����
	void frameRenderReverseX(string strKey, float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0f);
	void frameRenderReverseX(string strKey, float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float alpha = 1.0f);
};

