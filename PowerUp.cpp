#include "PowerUp.h"
#include "Mario.h"

CPowerUp::CPowerUp(float x, float y,int type) : CGameObject(x, y) {
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	this->type = type;
	y_target = -1;
	if (type == SUPER_LEAF) {
		ax = MUSHROOM_WALKING_SPEED / 1000;
		ay = MUSHROOM_GRAVITY ;
		vx = MUSHROOM_WALKING_SPEED / 3;

		start = GetTickCount64();
	}
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
	else if (state == MUSHROOM_UP_STATE_LEFT || state == MUSHROOM_UP_STATE_RIGHT || state == MUSHROOM_1UP_STATE|| state == LEAF_UP_STATE) {
		y += vy * dt;
	}
};

void CPowerUp::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPowerUp*>(e->obj)) return;

	if (state == MUSHROOM_UP_STATE_LEFT || state == MUSHROOM_UP_STATE_RIGHT) return;

	else if (e->ny != 0)
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

	if (y_target != -1 && (state == MUSHROOM_UP_STATE_LEFT || state == MUSHROOM_UP_STATE_RIGHT) && y <= y_target) {
		SetState(MUSHROOM_WALKING_STATE);
	}
	if (y_target != -1 && state == MUSHROOM_1UP_STATE && y <= y_target) {
		SetState(MUSHROOM_WAIT_STATE);
	}
	if (y_target != -1 && state == LEAF_UP_STATE && y <= y_target) {
		OnNoCollision(dt);
		IsDiversion();
		vy = ay * dt;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPowerUp::Render()
{
	int aniId = ID_ANI_SUPER_LEAF;
	if (type == MUSHROOM_SUPER)
		aniId = ID_ANI_POWERUP_MUSHROOM;
	else if (type == MUSHROOM_1UP)
		aniId = ID_ANI_MUSHROOM_1UP;
	if (state != POWER_UP_HIDDEN_STATE) {
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	RenderBoundingBox();
}
void CPowerUp::IsDiversion()
{
	if (GetTickCount64() - start >= LEAF_DIVERT_TIME) {
		vx = -vx;
		start = GetTickCount64();
	}
}
void CPowerUp::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MUSHROOM_WALKING_STATE:
		vx = MUSHROOM_WALKING_SPEED * power_up_direction;
		ay = MUSHROOM_GRAVITY;
		break;
	case MUSHROOM_UP_STATE_LEFT:
		ay = 0;
		vx = 0;
		vy = -MUSHROOM_UP_SPEED;
		y_target = y - MUSHROOM_BBOX_HEIGHT;
		power_up_direction = -1;
		break;
	case MUSHROOM_UP_STATE_RIGHT:
		ay = 0;
		vx = 0;
		vy = -MUSHROOM_UP_SPEED;
		y_target = y - MUSHROOM_BBOX_HEIGHT;
		power_up_direction = 1;
		break;
	case MUSHROOM_1UP_STATE:
		vx = 0;
		ay = 0;
		vy = -MUSHROOM_UP_SPEED;
		y_target = y - MUSHROOM_BBOX_HEIGHT;
		break;
	case MUSHROOM_WAIT_STATE:
		ay = 0;
		vy = 0;
		break;
	case LEAF_UP_STATE:
		vx = 0;
		ay = 0;
		vy = -MUSHROOM_UP_SPEED;
		y_target = y-MUSHROOM_BBOX_HEIGHT-10;
		break;
	}
}