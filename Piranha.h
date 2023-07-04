#pragma once
#include "GameObject.h"

#define ID_ANI_PIRANHA 132011

#define PIRANHA_WIDTH 16
#define PIRANHA_BBOX_WIDTH 16
#define PIRANHA_BBOX_HEIGHT 22

#define PIRANHA_STATE_UP 100
#define PIRANHA_STATE_DOWN 101
#define PIRANHA_STATE_WAIT 102

#define PIRANHA_SPEED 0.02f

#define PIRANHA_TIMEOUT 1500
#define PIRANHA_WAIT_TIMEOUT 3000


#define ID_ANI_GREEN_VENUS_LOOK_DOWN_LEFT 133011
#define ID_ANI_GREEN_VENUS_LOOK_UP_LEFT 133012
#define ID_ANI_GREEN_VENUS_LOOK_DOWN_RIGHT 133013
#define ID_ANI_GREEN_VENUS_LOOK_UP_RIGHT 133014
#define ID_ANI_GREEN_VENUS_RISING_LEFT 133012
#define ID_ANI_GREEN_VENUS_RISING_RIGHT 133014

#define ID_ANI_RED_VENUS_LOOK_DOWN_LEFT 131011
#define ID_ANI_RED_VENUS_LOOK_UP_LEFT 131017
#define ID_ANI_RED_VENUS_LOOK_DOWN_RIGHT 131014
#define ID_ANI_RED_VENUS_LOOK_UP_RIGHT 131012
#define ID_ANI_RED_VENUS_RISING_LEFT 131011
#define ID_ANI_RED_VENUS_RISING_RIGHT 131013

#define ID_ANI_RED_VENUS_MOVE_HEAD_TOP_LEFT	131015
#define ID_ANI_RED_VENUS_MOVE_HEAD_TOP_RIGHT	131016
#define ID_ANI_RED_VENUS_MOVE_HEAD_BOTTOM_LEFT	131017
#define ID_ANI_RED_VENUS_MOVE_HEAD_BOTTOM_RIGHT	131018

#define ID_ANI_VENUS_DIE_BY_ATTACK 133015

#define ID_ANI_FIREBALL_LEFT 134011
#define ID_ANI_FIREBALL_RIGHT 134012

#define FIREBALL_WIDTH 8
#define FIREBALL_BBOX_WIDTH 8
#define FIREBALL_BBOX_HEIGHT 8
#define FIREBALL_SPEED 0.03f

#define VENUS_WIDTH 16
#define VENUS_BBOX_WIDTH 15
#define VENUS_BBOX_HEIGHT 20

#define VENUS_STATE_IDLE 103
#define VENUS_STATE_FIRE 104
#define VENUS_STATE_UP 105
#define VENUS_STATE_DOWN 106
#define VENUS_STATE_WAIT 107
#define VENUS_STATE_DIE_BY_ATTACK 108

#define VENUS_SPEED 0.03f

#define VENUS_DIE_TIME_OUT 200
#define VENUS_IDLE_TIMEOUT 3000
#define VENUS_FIRE_TIMEOUT 2000
#define VENUS_TIMEOUT 1150
#define VENUS_WAIT_TIMEOUT 3000

class CPiranha : public CGameObject
{
protected:
	virtual void OnNoCollision(DWORD dt) { return; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) { return; };
	ULONGLONG up_start, wait_start;
	float speed;
	float maxY;
public:
	CPiranha(float x, float y) : CGameObject(x, y) {
		up_start = -1;
		wait_start = -1;
		maxY = y - PIRANHA_BBOX_HEIGHT;
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
	ULONGLONG idle_start, fire_start;
	float x_mario, y_mario;
	ULONGLONG die_start;
	int fire_ball_added;
	int color;
	float maxY;
public:
	CVenusFireTrap(float x, float y,int c) : CPiranha(x, y) {
		this->color = c;
		maxY = y - VENUS_BBOX_HEIGHT;
		idle_start = -1;
		speed = VENUS_SPEED;
		SetState(VENUS_STATE_WAIT);
		x_mario = 0;
		y_mario = 0;
		fire_ball_added = 0;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void GetMarioPosition(float x, float y);
	bool IsMarioOnLeft();
	bool IsMarioHigher();
	void IncreaseFireBall();
	int GetFireBall();
};


class CFireBall : public CVenusFireTrap {
protected:
	float cx, cy, cw, ch;
public:
	CFireBall(float x, float y, float x_mario, float y_mario, int c) : CVenusFireTrap(x, y, c)
	{
		// Rest of the constructor code
		if (x < x_mario) {
			vx = FIREBALL_SPEED;
		}
		else {
			vx = -FIREBALL_SPEED;
		}
		vy = (y_mario - y) / (x_mario - x) * vx;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
	bool IsMarioOnLeft();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
};
