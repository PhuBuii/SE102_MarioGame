#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_ROTATE_SPEED 0.15f


#define KOOPAS_BBOX_WIDTH 20
#define KOOPAS_BBOX_HEIGHT 22
#define KOOPAS_BBOX_HEIGHT_DIE 9
#define KOOPAS_BBOX_HEIGHT_SHELL 14

#define KOOPAS_DIE_TIMEOUT 500

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_SHELL_IDLE	300
#define KOOPAS_STATE_SHELL_ROTATE	400

#define ID_ANI_KOOPAS_WALKING_LEFT 10000
#define ID_ANI_KOOPAS_WALKING_RIGHT 10010
#define ID_ANI_KOOPAS_SHELL_REFORM 10003

#define ID_ANI_KOOPAS_SHELL_IDLE 10001
#define ID_ANI_KOOPAS_SHELL_ROTATE 10002
class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
};