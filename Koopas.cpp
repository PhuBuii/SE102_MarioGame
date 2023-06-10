#include "Koopas.h"

CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
		break;
	case KOOPAS_STATE_SHELL_IDLE:
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_SHELL;
		break;
	case KOOPAS_STATE_SHELL_ROTATE:
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_SHELL;
		break;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;

	float left, right, top, bottom;

	e->obj->GetBoundingBox(left, top, right, bottom);

	// If go end then reverse
	if (state == KOOPAS_STATE_WALKING) {
		if ((x < left && vx < 0) || (x > right && vx > 0)) {
			vx = -vx;
		}
	}
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int aniId = -1;
	switch (state) {
	case KOOPAS_STATE_WALKING:
		if (vx < 0)
			aniId = ID_ANI_KOOPAS_WALKING_LEFT;
		else
			aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
		break;
	case KOOPAS_STATE_SHELL_IDLE:
		aniId = ID_ANI_KOOPAS_SHELL_IDLE;
		break;
	case KOOPAS_STATE_SHELL_ROTATE:
		aniId = ID_ANI_KOOPAS_SHELL_ROTATE;
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_SHELL_IDLE:
		vx = 0;
		break;
	case KOOPAS_STATE_SHELL_ROTATE:
		vx = -KOOPAS_ROTATE_SPEED;
		break;
	}
}