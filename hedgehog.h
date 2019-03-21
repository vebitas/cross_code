#pragma once
#include "enemy.h"

class hedgehog : public enemy
{
private:
	float _alpha;
	int _count;
public:
	hedgehog();
	~hedgehog();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY);
	virtual void release();
	virtual void update();
	virtual void render(float alpha);

	void hogState();
};

