#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Coin.h"
#include "Brick.h"

#define ID_ANI_PIRANHA 132011

#define PIRANHA_WIDTH 16
#define PIRANHA_BBOX_WIDTH 16
#define PIRANHA_BBOX_HEIGHT 22

#define PIRANHA_STATE_UP 100
#define PIRANHA_STATE_DOWN 101
#define PIRANHA_STATE_WAIT 102

#define PIRANHA_SPEED 0.025f

#define PIRANHA_TIMEOUT 1100
#define PIRANHA_WAIT_TIMEOUT 3000


#define ID_ANI_GREEN_VENUS_LOOK_DOWN_LEFT 133011
#define ID_ANI_GREEN_VENUS_LOOK_UP_LEFT 133012
#define ID_ANI_GREEN_VENUS_LOOK_DOWN_RIGHT 133013
#define ID_ANI_GREEN_VENUS_LOOK_UP_RIGHT 133014
#define ID_ANI_GREEN_VENUS_RISING 133015

#define ID_ANI_RED_VENUS_LOOK_DOWN_LEFT 131011
#define ID_ANI_RED_VENUS_LOOK_UP_LEFT 131012
#define ID_ANI_RED_VENUS_LOOK_DOWN_RIGHT 131013
#define ID_ANI_RED_VENUS_LOOK_UP_RIGHT 131014
#define ID_ANI_RED_VENUS_RISING 131015

#define VENUS_WIDTH 16
#define VENUS_BBOX_WIDTH 16
#define VENUS_BBOX_HEIGHT 32

#define VENUS_STATE_IDLE 103
#define VENUS_STATE_FIRE 104

#define VENUS_SPEED 0.03f

#define VENUS_IDLE_TIMEOUT 3000


class CPiranha : public CGameObject
{
protected:
	virtual void OnNoCollision(DWORD dt) { return; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) { return; };
	ULONGLONG up_start, wait_start;
	float speed;
public:
	CPiranha(float x, float y) : CGameObject(x, y) {
		up_start = -1;
		wait_start = -1;
		SetState(PIRANHA_STATE_WAIT);
		speed = PIRANHA_SPEED;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	int IsBlocking() { return 0; }
	int IsCollidable()
	{
		return (state != PIRANHA_STATE_WAIT);
	}
};

class CVenusFireTrap : public CPiranha {
protected:
	ULONGLONG idle_start;
public:
	CVenusFireTrap(float x, float y) : CPiranha(x, y) {
		idle_start = -1;
		speed = VENUS_SPEED;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
	virtual void SetState(int state);
	/*void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);*/
};