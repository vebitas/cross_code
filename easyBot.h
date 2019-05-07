#pragma once
#include "enemy.h"

#define EASYBOTFPS 8

class easyBot : public enemy
{
private:
	int _count;
	float _alpha;
public:
	easyBot();
	~easyBot();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY);
	virtual void release();
	virtual void update();
	virtual void render(float alpha);

	void easyBotStage();
};

