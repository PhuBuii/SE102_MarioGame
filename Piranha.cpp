#include "Piranha.h"
#include "Game.h"

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
	int aniID = ID_ANI_RED_VENUS_RISING_LEFT;
	if (IsMarioOnLeft())
	aniID = ID_ANI_RED_VENUS_RISING_LEFT;
	else
	aniID = ID_ANI_RED_VENUS_RISING_RIGHT;
	if (state == VENUS_STATE_IDLE) {
		if (IsMarioHigher()) {
			if (IsMarioOnLeft()) {
				aniID = ID_ANI_RED_VENUS_LOOK_UP_LEFT;
			}
			else {
				aniID = ID_ANI_RED_VENUS_LOOK_UP_RIGHT;
			}
		}
		else {
			if (IsMarioOnLeft()) {
				aniID = ID_ANI_RED_VENUS_LOOK_DOWN_LEFT;
			}
			else {
				aniID = ID_ANI_RED_VENUS_LOOK_DOWN_RIGHT;
			}
		}

	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
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
	case VENUS_STATE_FIRE:
		fire_start = GetTickCount64();
		fire_ball_added = true;
		break;
	}
}
void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if ((state == VENUS_STATE_IDLE) && (GetTickCount64() - idle_start > VENUS_IDLE_TIMEOUT))
	{
		SetState(VENUS_STATE_FIRE);
		fire_ball_added = true;
	}
	else if ((state == VENUS_STATE_FIRE) && (GetTickCount64() - fire_start > VENUS_FIRE_TIMEOUT))
	{
		SetState(PIRANHA_STATE_DOWN);
		fire_ball_added = false;
	}
	else if ((state == PIRANHA_STATE_UP) && (GetTickCount64() - up_start > PIRANHA_TIMEOUT))
	{
		SetState(VENUS_STATE_IDLE);
	}
	CPiranha::Update(dt, coObjects);
}
void CVenusFireTrap::GetMarioPosition(float x, float y)
{
	x_mario = x;
	y_mario = y;
}

bool CVenusFireTrap::IsMarioOnLeft()
{
	if (x > x_mario) {
		return true;
	}
	else
		return false;
}
bool CVenusFireTrap::IsMarioHigher()
{
	if (y > y_mario)
		return false;
	else
		return true;
}

void CVenusFireTrap::SetFireBallAdded()
{
	fire_ball_added = true;
}

bool CVenusFireTrap::IsFireBallAdded()
{
	return fire_ball_added;
}

CFireBall::CFireBall(float x, float y, float x_mario, float y_mario) : CGameObject(x, y)
{
	vx = (y_mario - y) / (x_mario - x);
	vy = y - vx * x;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	x += vx * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_BBOX_WIDTH / 2;
	t = y - FIREBALL_BBOX_HEIGHT / 2;
	r = l + FIREBALL_BBOX_WIDTH;
	b = t + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::Render()
{
	int aniId = ID_ANI_FIREBALL;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}