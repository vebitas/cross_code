#include "stdafx.h"
#include "image.h"

//�����Ϸ� ���ñ� (�� ���̺귯�� ������ msImg32 ���̺귯��)
#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL), _fileName(NULL)
{
}


image::~image()
{
}

HRESULT image::init(LPCWSTR fileName, int width, int height)
{
	return init(fileName, width, height, 1, 1);		//������ �̴����� 1 x 1 ��������ϸ� �������� ��©���� �� 1���� ������ ����
}

HRESULT image::init(LPCWSTR fileName, int width, int height, int frameNumX, int frameNumY)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	// �̹��� ���� ����
	HRESULT hr = E_FAIL;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameNumX - 1;
	_imageInfo->maxFrameY = frameNumY - 1;
	_imageInfo->frameWidth = width / frameNumX;
	_imageInfo->frameHeight = height / frameNumY;

	// ���� ��� ����
	int len;
	len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);

	
	//CLSCTX_LOCAL_SERVER
	// WIC�� ����ϱ� ���� Factory ��ü ����
	// CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
	//	IID_PPV_ARGS(&_imageInfo->WICImagingFactory));
	//if (_imageInfo->WICImagingFactory == nullptr)
	//{
	//	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_HANDLER,
	//	IID_PPV_ARGS(&_imageInfo->WICImagingFactory));
	//}
	//
	// ���ڴ� ����
	hr = D2DMANAGER->WICImagingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->WICDecoder));
	assert(hr == S_OK);

	// ù ��° �������� ����� �� �ִ� ��ü ����
	hr = _imageInfo->WICDecoder->GetFrame(0, &_imageInfo->WICFrameDecoder);
	assert(hr == S_OK);

	// ���� ������ ����
	hr = D2DMANAGER->WICImagingFactory->CreateFormatConverter(&_imageInfo->WICFormatConverter);
	assert(hr == S_OK);

	// ��Ʈ������ ��ȯ
	hr = _imageInfo->WICFormatConverter->Initialize(_imageInfo->WICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	// ��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	hr = D2DMANAGER->_renderTarget->CreateBitmapFromWicBitmap(_imageInfo->WICFormatConverter, NULL, &_imageInfo->bitmap);

	// �̹����� �������� �ʾ��� ���
	if (_imageInfo->bitmap == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

void image::release(void)
{
	if (_imageInfo)
	{
		SAFE_DELETE(_imageInfo);
	}
}



//===================================================================
//						D2D ��� ���� �Լ�
//- ī�޶� �̵� ���� & ������ ���� ���븸 ����
//- Left Top ����
//===================================================================

void image::render(float alpha)
{
	render(0, 0, _imageInfo->width, _imageInfo->height, 0.f, 0.f, _imageInfo->width, _imageInfo->height, alpha);
}

void image::render(float destX, float destY, float alpha)
{
	render(destX, destY, _imageInfo->width, _imageInfo->height, 0.f, 0.f, _imageInfo->width, _imageInfo->height, alpha);
}



void image::render(float destX, float destY, int showWidth, int showHeight, float alpha)
{
	render(destX, destY, showWidth, showHeight, 0.f, 0.f, _imageInfo->width, _imageInfo->height, alpha);
}

void image::render(float destX, float destY, float sourX, float sourY, int sourWidth, int sourHeight, float alpha)
{
	render(destX, destY, sourWidth, sourHeight, sourX, sourY, sourWidth, sourHeight, alpha);
}

void image::render(float destX, float destY, int showWidth, int showHeight, float sourX, float sourY, int sourWidth, int sourHeight, float alpha)
{
	POINTFLOAT pf = GetRenderPosition(destX, destY);

	if ( _imageInfo->bitmap != NULL )
	{
		if ( !IsRnderPositionInWindow(pf, showWidth, showHeight) )
			return;

		D2D1_RECT_F dxArea	= RectF(pf.x, pf.y, pf.x + showWidth, pf.y + showHeight);
		D2D1_RECT_F dxArea2 = RectF(  sourX
									, sourY
									, sourX + sourWidth
									, sourY + sourHeight);
		D2DMANAGER->_renderTarget->DrawBitmap(_imageInfo->bitmap
													, dxArea
													, alpha
													, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
													, dxArea2);
	}
}


//===================================================================
//						������ �̹��� ���� �Լ�
//- ī�޶� �̵� ���� & ������ ���� ���븸 ����
//- Left Top ����
//===================================================================

void image::frameRender(float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	frameRender(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, currentFrameX, currentFrameY, alpha);
}

void image::frameRenderAngle(float destX, float destY, int currentFrameX, int currentFrameY, float angle, float alpha)
{
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, Point2F(destX - CAMERA->getCameraX() + _imageInfo->frameWidth / 2, destY - CAMERA->getCameraY() + _imageInfo->frameHeight / 2)));
	frameRender(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, currentFrameX, currentFrameY, alpha);
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void image::frameRenderAngle(float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float angle, float alpha)
{
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, Point2F(destX - CAMERA->getCameraX() + _imageInfo->frameWidth / 2, destY - CAMERA->getCameraY() + _imageInfo->frameHeight / 2)));
	frameRender(destX, destY, showWidth, showHeight, currentFrameX, currentFrameY, alpha);
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void image::frameRender(float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float alpha)
{
	POINTFLOAT pf = GetRenderPosition(destX, destY);

	if (_imageInfo->bitmap != NULL)
	{
		if( !IsRnderPositionInWindow(pf, showWidth, showHeight) )
			return;

		D2D1_RECT_F dxArea = RectF(pf.x, pf.y, pf.x + showWidth, pf.y + showHeight);
		D2D1_RECT_F dxArea2 = RectF(  currentFrameX * _imageInfo->frameWidth
									, currentFrameY * _imageInfo->frameHeight
									, (currentFrameX + 1) * _imageInfo->frameWidth
									, (currentFrameY + 1) * _imageInfo->frameHeight);
		D2DMANAGER->_renderTarget->DrawBitmap(_imageInfo->bitmap
													, dxArea
													, alpha
													, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
													, dxArea2);
	}
}

void image::frameRender(float destX, float destY, int sourX, int sourY, int sourWidth, int sourHeight, int currentFrameX, int currentFrameY, float alpha)
{
	POINTFLOAT pf = GetRenderPosition(destX, destY);

	if (_imageInfo->bitmap != NULL)
	{
		if (!IsRnderPositionInWindow(pf, sourWidth, sourHeight))
			return;

		D2D1_RECT_F dxArea =   RectF(pf.x, pf.y, pf.x + sourWidth, pf.y + sourHeight);
		D2D1_RECT_F dxArea2 =  RectF(currentFrameX * _imageInfo->frameWidth	+ sourX
								  ,  currentFrameY * _imageInfo->frameHeight	+ sourY
								  , (currentFrameX) * _imageInfo->frameWidth  + sourX + sourWidth
								  , (currentFrameY) * _imageInfo->frameHeight + sourY + sourHeight);
		D2DMANAGER->_renderTarget->DrawBitmap(_imageInfo->bitmap
			, dxArea
			, alpha
			, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
			, dxArea2);
	}
}

void image::frameRenderReverseX(float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	frameRenderReverseX(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, currentFrameX, currentFrameY, alpha);
}

void image::frameRenderReverseAngle(float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float angle, float alpha)
{
	
	frameRenderReverseX(destX, destY, showHeight, showHeight, currentFrameX, currentFrameY, angle, alpha);
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void image::frameRenderReverseX(float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float angle, float alpha)
{

	POINTFLOAT pf = GetRenderPosition(destX, destY);

	if (_imageInfo->bitmap != NULL)
	{
		if (!IsRnderPositionInWindow(pf, showWidth, showHeight))
			return;
		D2D1_SIZE_F size;
		size.width = -1;
		size.height = 1;
		Matrix3x2F scaleMat = D2D1::Matrix3x2F::Scale(size, Point2F(destX - CAMERA->getCameraX() + 60 + _imageInfo->frameWidth / 2, destY - CAMERA->getCameraY() + 60 + _imageInfo->frameHeight / 2));
		Matrix3x2F rotationMat = D2D1::Matrix3x2F::Rotation(angle, Point2F(destX - CAMERA->getCameraX() + 60 + _imageInfo->frameWidth / 2, destY - CAMERA->getCameraY() + 60 + _imageInfo->frameHeight / 2));
		
		D2DMANAGER->_renderTarget->SetTransform(scaleMat * rotationMat);
		
		D2D1_RECT_F dxArea = RectF(pf.x, pf.y, pf.x + showWidth, pf.y + showHeight);
		D2D1_RECT_F dxArea2 = RectF(currentFrameX * _imageInfo->frameWidth
			, currentFrameY * _imageInfo->frameHeight
			, (currentFrameX + 1) * _imageInfo->frameWidth
			, (currentFrameY + 1) * _imageInfo->frameHeight);
		D2DMANAGER->_renderTarget->DrawBitmap(_imageInfo->bitmap
			, dxArea
			, alpha
			, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
			, dxArea2);
		D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	}
}



void image::loopRender(D2D1_RECT_F drawArea, int offSetX, int offSetY, float opacity)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	//ȭ�鿡 �����̹��� �׷��� ������ �����غ���
	int drawAreaX = (&drawArea)->left;				//�׷��� ������ Left
	int drawAreaY = (&drawArea)->top;				//�׷��� ������ top
	int drawAreaW = (&drawArea)->right - drawAreaX; //�׷��� ������ ����ũ��
	int drawAreaH = (&drawArea)->bottom - drawAreaY;//�׷��� ������ ����ũ��

	//����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//������ ������ ���ؼ� ��Ȯ�� ��ġ�� �˾ƿ´�
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//�з��ö� ���� ���
		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ������� �̹����� �����ٸ�
		if (y + sourHeight > drawAreaH)
		{
			//�׸�ŭ ��������� - ���궧���� ������ -���� ���� �ƴ϶� �����ΰ���
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//ȭ������� ���������� �ٽ� �о�ø���(�ٽ� �׷��ش�)
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		// X��
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//������ ������ ���� ���� ����
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(rcDest.left, rcDest.top,
				   rcSour.left, rcSour.top,
				   rcSour.right - rcSour.left,
				   rcSour.bottom - rcSour.top);
		}
	}


}

void image::aniRender(int destX, int destY, animation * ani)
{
	render(destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::aniRender(int destX, int destY, animation * ani, float alpha)
{
	render(destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}

void image::aniRenderAngle(int destX, int destY, animation * ani, float angle)
{
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, Point2F(destX - CAMERA->getCameraX() + _imageInfo->frameWidth / 2, destY - CAMERA->getCameraY() + _imageInfo->frameHeight / 2)));
	render(destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void image::aniRenderReverseX(int destX, int destY, animation * ani)
{
	D2D1_SIZE_F size;
	size.width = -1;
	size.height = 1;
	//D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Scale(size, Point2F(destX + _imageInfo->frameWidth / 2, destY + _imageInfo->frameHeight / 2)));
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Scale(size, Point2F(destX - CAMERA->getCameraX() + _imageInfo->frameWidth / 2, destY - CAMERA->getCameraY() + _imageInfo->frameHeight / 2)));
	render(destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void image::aniRenderReverseX(int destX, int destY, animation * ani, float alpha)
{
	D2D1_SIZE_F size;
	size.width = -1;
	size.height = 1;
	//D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Scale(size, Point2F(destX + _imageInfo->frameWidth / 2, destY + _imageInfo->frameHeight / 2)));
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Scale(size, Point2F(destX - CAMERA->getCameraX() + _imageInfo->frameWidth / 2, destY - CAMERA->getCameraY() + _imageInfo->frameHeight / 2)));
	render(destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
	D2DMANAGER->_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

POINTFLOAT image::GetRenderPosition(float destX, float destY)
{
	POINTFLOAT pf = { destX - (int)CAMERA->getCameraX() , destY - (int)CAMERA->getCameraY() };
	return pf;
}

bool image::IsRnderPositionInWindow(POINTFLOAT pf, float width, float height)
{
	if ( pf.x + width < 0  ) return false;
	if ( pf.y + height < 0 ) return false;
	if ( pf.x > WINSIZEX )	 return false;
	if ( pf.y > WINSIZEY )	 return false;

	return true;
}
