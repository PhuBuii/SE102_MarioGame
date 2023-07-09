#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "PSwitch.h"

#define ID_STATE_BRICK -1
#define ID_STATE_BREAK_BRICK -10

#define ID_ANI_BRICK 2003
#define	ID_ANI_BREAK_BRICK	2004
#define ID_ANI_GLASS_BRICK 2005
#define ID_ANI_GLASS_BRICK_KNOWN 2006

#define BRICK_WIDTH 17
#define BRICK_BBOX_WIDTH 15
#define BRICK_BBOX_HEIGHT 16

#define BRICK_DISAPPEAR_TIME_ANIMATION 300

#define GLASSBRICK_CONTAIN_COIN					0
#define GLASSBRICK_CONTAIN_PSWITCH				1

class CBrick : public CGameObject {
protected:
	ULONGLONG disappear_time;
public:
	CBrick(float x, float y) : CGameObject(x, y) {
		CGameObject::SetState(ID_STATE_BRICK);
		disappear_time = -1;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		if (state == ID_STATE_BREAK_BRICK && GetTickCount64() - disappear_time > BRICK_DISAPPEAR_TIME_ANIMATION) {
			isDeleted = true;
			return;
		}
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	virtual void SetState(int state);
	virtual int IsBlocking() {
		return state != ID_STATE_BREAK_BRICK;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
class CGlassBrick : public CBrick {
protected:
	int containObject;
	int idAni;
	bool broken;
	bool known;
public:
	CGlassBrick(float x, float y, int contain_object = 0) : CBrick(x, y) {
		this->containObject = contain_object;
		idAni = ID_ANI_GLASS_BRICK;
		broken = false;
		known = false;
	 disappear_time = -1; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		if (state == ID_STATE_BREAK_BRICK && GetTickCount64() - disappear_time > BRICK_DISAPPEAR_TIME_ANIMATION) {
			isDeleted = true;
			return;
		}
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	virtual int IsBlocking() {
		return state != ID_STATE_BREAK_BRICK;
	}
	void BrickTransformCoin();
	void BrickBreak();
	int getContainObject() {
		return containObject;
	}
	bool getBroken() {
		return broken;
	}
	void setKnown() {
		known = true;
	}
	bool getKnown() {
		return known;
	}
};	