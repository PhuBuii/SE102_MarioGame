#pragma once
#include "GameObject.h"


#define MUSHROOM_GRAVITY 0.002f
#define POWER_UP_DIRECTION 1

#define ID_ANI_POWERUP_MUSHROOM 14000
#define ID_ANI_MUSHROOM_1UP 14001

#define MUSHROOM_WALKING_STATE	1
#define POWER_UP_HIDDEN_STATE 2
#define MUSHROOM_UP_STATE_LEFT 3
#define MUSHROOM_UP_STATE_RIGHT 4
#define MUSHROOM_1UP_STATE 5
#define MUSHROOM_WAIT_STATE 6

#define MUSHROOM_WALKING_SPEED	0.05f
#define MUSHROOM_UP_SPEED 0.025f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 12

#define MUSHROOM_SUPER			1
#define MUSHROOM_1UP			2
class CPowerUp : public CGameObject
{
protected:
	float y_target;
	float ax;
	float ay;
	int type;
	int power_up_direction = 1;
	float m_x, m_y, u_x, u_y;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != POWER_UP_HIDDEN_STATE) && (state != MUSHROOM_UP_STATE_LEFT || state != MUSHROOM_UP_STATE_RIGHT); };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPowerUp(float x, float y,int type);
	virtual void SetState(int state);
};