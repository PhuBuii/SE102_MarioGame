#pragma once
#include "GameObject.h"


#define MUSHROOM_GRAVITY 0.002f
#define POWER_UP_DIRECTION 1

#define ID_ANI_MUSHROOM 14000

#define MUSHROOM_WALKING_STATE	1
#define POWER_UP_HIDDEN_STATE 2
#define MUSHROOM_UP_STATE 3

#define MUSHROOM_WALKING_SPEED	0.05f
#define MUSHROOM_UP_SPEED 0.02f

#define MUSHROOM_BBOX_WIDTH 14
#define MUSHROOM_BBOX_HEIGHT 11

class CPowerUp : public CGameObject
{
protected:
	float y_target;
	float ax;
	float ay;
	int power_up_direction = 1;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPowerUp(float x, float y);
	virtual void SetState(int state);
};