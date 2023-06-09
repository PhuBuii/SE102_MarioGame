#include "PowerUp.h"

CPowerUp::CPowerUp(float x, float y) : CGameObject(x, y) {
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	y_target = -1;
	SetState(MUSHROOM_WALKING_STATE);
}

void CPowerUp::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CPowerUp::OnNoCollision(DWORD dt)
{
	if (state == MUSHROOM_WALKING_STATE) {
		x += vx * dt;
		y += vy * dt;
	}
	else if (state == MUSHROOM_UP_STATE) {
		y += vy * dt;
	}
};

void CPowerUp::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPowerUp*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CPowerUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state != POWER_UP_HIDDEN_STATE) {
		vy += ay * dt;
		vx += ax * dt;
	}

	if (y_target != -1 && state == MUSHROOM_UP_STATE && y <= y_target) {
		SetState(MUSHROOM_WALKING_STATE);
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPowerUp::Render()
{
	int aniId = ID_ANI_MUSHROOM;

	if (state != POWER_UP_HIDDEN_STATE) {
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	RenderBoundingBox();
}

void CPowerUp::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MUSHROOM_WALKING_STATE:
		vx = -MUSHROOM_WALKING_SPEED;
		ay = MUSHROOM_GRAVITY;
		break;
	case MUSHROOM_UP_STATE:
		ay = 0;
		vx = 0;
		vy = -MUSHROOM_UP_SPEED;
		y_target = y - 14;
		break;
	}
}