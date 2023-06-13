#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 12
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

// PARA-GOOMBA 


#define PARAGOOMBA_FLYING_BBOX_WIDTH 15
#define PARAGOOMBA_FLYING_BBOX_HEIGHT 15

#define PARAGOOMBA_WINGWALKING_BBOX_WIDTH 15
#define PARAGOOMBA_WINGWALKING_BBOX_HEIGHT 15

#define PARAGOOMBA_STATE_WING_FLYING 410
#define PARAGOOMBA_STATE_WING_WALKING 411
#define PARAGOOMBA_STATE_NO_WING_WALKING 420
#define PARAGOOMBA_STATE_DIE 430
#define PARAGOOMBA_STATE_HIT_BY_KOOPA 440

#define PARAGOOMBA_FLYING_TIMEOUT 1000

#define ID_ANI_PARAGOOMBA_WALKING 5100
#define ID_ANI_PARAGOOMBA_DIE 5101
#define ID_ANI_PARAGOOMBA_HIT_BY_KOOPA 5102
#define ID_ANI_PARAGOOMBA_FLYING 5103
#define ID_ANI_PARAGOOMBA_WING_WALK 5104
class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y);
	virtual void SetState(int state);
};
//Para-Goomba


class CParaGoomba : public CGoomba
{
protected:
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
public:
	CParaGoomba(float x, float y);
	virtual void SetState(int state);
};