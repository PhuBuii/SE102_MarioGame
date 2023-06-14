#include "Goomba.h"

CGoomba::CGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	bounce_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		if (state != GOOMBA_HIT_BY_KOOPA) {
			vy = 0;
		}

	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (state == GOOMBA_HIT_BY_KOOPA)
	{
		if (GetTickCount64() - bounce_start > GOOMBA_BOUNCE_TIMEOUT) {
			ay = GOOMBA_GRAVITY;
		}
		if (y > 500) {
			isDeleted = true;
			return;
		}
		else {
			y += vy * dt;
		}

	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBA_HIT_BY_KOOPA) {
		aniId = ID_ANI_HIT_BY_KOOPA;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_HIT_BY_KOOPA:
		vx = 0;
		ay = -GOOMBA_GRAVITY;
		bounce_start = GetTickCount64();
		break;
	}
}

void CParaGoomba::Render()
{
	int aniId = ID_ANI_PARAGOOMBA_WING_WALK;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARAGOOMBA_DIE;
	}
	else if (state == GOOMBA_HIT_BY_KOOPA) {
		aniId = ID_ANI_PARAGOOMBA_HIT_BY_KOOPA;
	}
	else if (state == GOOMBA_STATE_WALKING) {
		aniId = ID_ANI_PARAGOOMBA_WALKING;
	}
	else if (state == PARAGOOMBA_STATE_WING_FLYING) {
		aniId = ID_ANI_PARAGOOMBA_FLYING;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	CGoomba::GetBoundingBox(left, top, right, bottom);

	if (state == PARAGOOMBA_STATE_WING_WALKING)
	{
		left = x - PARAGOOMBA_WINGWALKING_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_WINGWALKING_BBOX_HEIGHT / 2;
		right = left + PARAGOOMBA_WINGWALKING_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_WINGWALKING_BBOX_HEIGHT;
	}
	else if (state == PARAGOOMBA_STATE_WING_FLYING) {
		left = x - PARAGOOMBA_FLYING_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_FLYING_BBOX_HEIGHT / 2;
		right = left + PARAGOOMBA_FLYING_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_FLYING_BBOX_HEIGHT;
	}

}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	if ((state == PARAGOOMBA_STATE_WING_FLYING) && (GetTickCount64() - fly_start > PARAGOOMBA_FLYING_TIMEOUT))
	{
		SetState(PARAGOOMBA_STATE_WING_WALKING);

	}
	if (on_platform) {

		if (state == PARAGOOMBA_STATE_WING_WALKING && wait_start == -1) {
			// START WAIT TIME			
			this->StartWaitTime();

		}
	}
	if ((state == PARAGOOMBA_STATE_WING_WALKING) && (GetTickCount64() - wait_start > PARAGOOMBA_WAIT_TIMEOUT) && on_platform) {

		SetState(PARAGOOMBA_STATE_WING_FLYING);
		on_platform = false;
	}


	CGoomba::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		if (state != GOOMBA_HIT_BY_KOOPA) {
			vy = 0;
			if (e->ny < 0) {
				on_platform = true;
			}

		}

	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}


CParaGoomba::CParaGoomba(float x, float y) :CGoomba(x, y)
{
	wait_start = -1;
	fly_start = -1;
	vx = -GOOMBA_WALKING_SPEED;
	ay = 0;
	vy = 0;
	on_platform = false;
	SetState(PARAGOOMBA_STATE_WING_WALKING);

}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARAGOOMBA_STATE_WING_FLYING:
		vy = -PARAGOOMBA_UP_SPEED;
		fly_start = GetTickCount64();
		wait_start = -1;
		ay = 0;
		break;
	case PARAGOOMBA_STATE_WING_WALKING:
		/*ay = GOOMBA_GRAVITY;
		vy = 0;*/
		/*break;*/
	case GOOMBA_STATE_WALKING:
		ay = GOOMBA_GRAVITY;
		vy = 0;
		/*fly_start = -1;
		wait_start = -1;*/
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_HIT_BY_KOOPA:
		vx = 0;
		vy = 0;
		ay = -GOOMBA_GRAVITY;
		bounce_start = GetTickCount64();
		break;
	}
}