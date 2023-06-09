#pragma once

#include "GameObject.h"


#define ID_ANI_PSWITCH						8810 
#define ID_ANI_PSWITCH_ACTIVED				8811 // after collide with Mario

#define PSWITCH_STATE_STATIC	710
#define PSWITCH_STATE_RISING	711

#define PSWITCH_BBOX_WIDTH					15
#define PSWITCH_BBOX_HEIGHT					15

#define PSWITCH_ACTIVED_BBOX_WIDTH			0
#define PSWITCH_ACTIVED_BBOX_HEIGHT			0

#define PSWITCH_RISING_SPEED 0.01f

#define BRICK_BBOX_WIDTH 15
#define BRICK_BBOX_HEIGHT 16

class CPSwitch : public CGameObject
{
protected:
	bool isActived;
	float y_rise;

public:
	CPSwitch(float x, float y) : CGameObject(x, y) {
		isActived = false;
		this->y_rise = y - BRICK_BBOX_HEIGHT;
		SetState(PSWITCH_STATE_RISING);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
	void IsActived();
	virtual void SetState(int state);
};