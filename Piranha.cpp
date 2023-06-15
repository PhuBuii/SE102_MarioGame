#include "Piranha.h"

void CPiranha::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIRANHA_BBOX_WIDTH / 2;
	t = y - PIRANHA_BBOX_HEIGHT / 2;
	r = l + PIRANHA_BBOX_WIDTH;
	b = t + PIRANHA_BBOX_HEIGHT;
}

void CPiranha::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_PIRANHA)->Render(x, y);

	RenderBoundingBox();
}

void CPiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;


	if ((state == PIRANHA_STATE_UP) && (GetTickCount64() - up_start > PIRANHA_TIMEOUT))
	{
		SetState(PIRANHA_STATE_DOWN);
	}
	else if ((state == PIRANHA_STATE_DOWN) && (GetTickCount64() - up_start > PIRANHA_TIMEOUT))
	{
		SetState(PIRANHA_STATE_WAIT);
	}
	else if ((state == PIRANHA_STATE_WAIT) && (GetTickCount64() - wait_start > PIRANHA_WAIT_TIMEOUT))
	{
		SetState(PIRANHA_STATE_UP);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranha::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case  PIRANHA_STATE_UP:
		vy = -speed;
		wait_start = -1;
		up_start = GetTickCount64();
		break;
	case  PIRANHA_STATE_DOWN:
		vy = speed;
		wait_start = -1;
		up_start = GetTickCount64();
		break;
	case  PIRANHA_STATE_WAIT:
		vy = 0;
		wait_start = GetTickCount64();
		up_start = -1;
		break;
	}
}


void CVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VENUS_BBOX_WIDTH / 2;
	t = y - VENUS_BBOX_HEIGHT / 2;
	r = l + VENUS_BBOX_WIDTH;
	b = t + VENUS_BBOX_HEIGHT;
}

void CVenusFireTrap::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_RED_VENUS_RISING)->Render(x, y);
}
void CVenusFireTrap::SetState(int state)
{
	CPiranha::SetState(state);
	switch (state)
	{
	case  VENUS_STATE_IDLE:
		vy = 0;
		idle_start = GetTickCount64();
		break;
	}
}
void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if ((state == VENUS_STATE_IDLE) && (GetTickCount64() - idle_start > VENUS_IDLE_TIMEOUT))
	{
		SetState(PIRANHA_STATE_DOWN);
	}
	else if ((state == PIRANHA_STATE_UP) && (GetTickCount64() - up_start > PIRANHA_TIMEOUT))
	{
		SetState(VENUS_STATE_IDLE);
	}

	CPiranha::Update(dt, coObjects);
}