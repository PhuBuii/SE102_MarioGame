#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Coin.h"
#include "Brick.h"

#define ID_ANI_PIRANHA 132011

#define PIRANHA_WIDTH 16
#define PIRANHA_BBOX_WIDTH 16
#define PIRANHA_BBOX_HEIGHT 24

#define PIRANHA_STATE_UP 100
#define PIRANHA_STATE_DOWN 101

#define PIRANHA_SPEED 0.025f

#define PIRANHA_UP_TIMEOUT 1000



class CPiranha : public CGameObject
{
protected:
	virtual void OnNoCollision(DWORD dt) { return; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) { return; };
	ULONGLONG up_start;
public:
	CPiranha(float x, float y) : CGameObject(x, y) {
		up_start = -1;
		SetState(PIRANHA_STATE_UP);

	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
};