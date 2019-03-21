#include "stdafx.h"
#include "uiScene.h"


uiScene::uiScene()
{
}


uiScene::~uiScene()
{
}

HRESULT uiScene::init()
{
	IMAGEMANAGER->addImage("uiImage", L"image/intro/optionImage.png", 1024, 768);
	return S_OK;
}

void uiScene::release()
{
}

void uiScene::update()
{
}

void uiScene::render()
{
	IMAGEMANAGER->findImage("uiImage")->render(1);
}
