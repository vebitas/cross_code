#pragma once
#include "enemy.h"
#define TURRETFPS 10

class turret : public enemy
{
private:
	float _alpha;
	int _count;
public:
	turret();
	~turret();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY);
	virtual void release();
	virtual void update(float playerX, float playerY);
	virtual void render(float alpha);

	void turretState(float angle);
};

