#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_STATE_BRICK -1
#define ID_STATE_BREAK_BRICK -10

#define ID_ANI_BRICK 2003
#define	ID_ANI_BREAK_BRICK	2004

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 19

#define BRICK_DISAPPEAR_TIME_ANIMATION 300

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