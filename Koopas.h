#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.03f
#define KOOPAS_ROTATE_SPEED 0.15f
#define KOOPAS_TRANSFORM_SPEED	0.1f


#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 25
#define KOOPAS_BBOX_HEIGHT_SHELL 13
#define KOOPAS_BBOX_HEIGHT_SHELL_TRANSFORM 12


#define KOOPAS_SHELL_WAIT_ROTATE_TIME_OUT 3000
#define KOOPAS_SHELL_TRANSFORM_WALKING_TIME_OUT	1000
#define KOOPAS_SHELL_TRANSFORM_ROTATE_TIME_OUT 200

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_SHELL_IDLE	200
#define KOOPAS_STATE_SHELL_ROTATE	300
#define KOOPAS_STATE_SHELL_TRANSFORM_WALKING	400
#define KOOPAS_STATE_DIE 500
#define KOOPAS_HIT_BY_KOOPAS 600

#define ID_ANI_KOOPAS_WALKING_LEFT 10000
#define ID_ANI_KOOPAS_WALKING_RIGHT 10010
#define ID_ANI_KOOPAS_SHELL_IDLE 10001
#define ID_ANI_KOOPAS_SHELL_ROTATE 10002
#define ID_ANI_KOOPAS_SHELL_TRANSFORM_WALKING 10003
#define ID_ANI_KOOPAS_HIT_BY_KOOPAS 10004


class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	bool isOnHand;
	float mario_x;
	float mario_y;
	ULONGLONG shell_wait_rotate_start;
	ULONGLONG shell_transform_start;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	int GetAni();

public:
	CKoopas(float x, float y);
	void SetOnHand(bool onHand) { this->isOnHand = onHand; }
	virtual void SetState(int state);
};