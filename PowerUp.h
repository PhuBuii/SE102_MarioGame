#pragma once
#include "GameObject.h"
#include "PlayScene.h"


#define MUSHROOM_GRAVITY 0.002f
#define POWER_UP_DIRECTION 1

#define LEAF_GRAVITY	0.00015f
#define LEAF_SPEED_UP	0.07f

#define LEAF_FLOAT_SPEED	0.04f

#define ID_ANI_POWERUP_MUSHROOM 14000
#define ID_ANI_MUSHROOM_1UP 14001
#define ID_ANI_SUPER_LEAF 14002
#define ID_ANI_LEAF_FLY_LEFT 14002
#define ID_ANI_LEAF_FLY_RIGHT 14003


#define MUSHROOM_WALKING_STATE	1
#define POWER_UP_HIDDEN_STATE 2
#define MUSHROOM_UP_STATE_LEFT 3
#define MUSHROOM_UP_STATE_RIGHT 4
#define MUSHROOM_1UP_STATE 5
#define MUSHROOM_WAIT_STATE 6
#define LEAF_UP_STATE	7
#define LEAF_STATE	8

#define MUSHROOM_WALKING_SPEED	0.05f
#define MUSHROOM_UP_SPEED 0.025f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 12
#define LEAF_BBOX_HEIGHT 13

#define MUSHROOM_SUPER			1
#define MUSHROOM_1UP			2
#define SUPER_LEAF				3

#define LEAF_DIVERT_TIME		300
class CPowerUp : public CGameObject
{
protected:
	float y_target;
	float ax;
	float ay;
	float x_target;
	float x_init;
	int type;
	ULONGLONG start;
	int power_up_direction = 1;
	float m_x, m_y, u_x, u_y;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	virtual int IsCollidable() { return state != POWER_UP_HIDDEN_STATE && state != MUSHROOM_UP_STATE_LEFT && state != MUSHROOM_UP_STATE_RIGHT && state != LEAF_STATE; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	void SetType(int typeblock) { this->type = typeblock; }
	CPowerUp(float x, float y,int type);
	void DirectionOfPowerUp();
	virtual void SetState(int state);
};