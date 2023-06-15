#include "Koopas.h"
#include "QuestionBlock.h"
#include "Mario.h"
#include "Goomba.h"

CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	isOnHand = false;
	shell_wait_rotate_start = -1;
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
	case KOOPAS_STATE_SHELL_TRANSFORM_WALKING:
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_SHELL_TRANSFORM / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_SHELL_TRANSFORM;
		break;
	case KOOPAS_STATE_DIE:
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_SHELL;
		break;

	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	if (!isOnHand) {
		x += vx * dt;
		y += vy * dt;
	}
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	float left, right, top, bottom;

	e->obj->GetBoundingBox(left, top, right, bottom);
	if (dynamic_cast<CKoopas*>(e->obj)) {
		CKoopas* kp = (CKoopas*)e->obj;
		if (state == KOOPAS_STATE_SHELL_ROTATE) {
			kp->SetState(KOOPAS_HIT_BY_KOOPAS);
		}
	}
	else if (dynamic_cast<CGoomba*>(e->obj)) {
		CGoomba* gb = (CGoomba*)(e->obj);
		if (state == KOOPAS_STATE_SHELL_ROTATE) {
			if (gb->GetState() != GOOMBA_STATE_DIE)
			{
				gb->SetState(GOOMBA_HIT_BY_KOOPA);
			}
		}
	}
	else if (dynamic_cast<CParaGoomba*>(e->obj)) {
		CParaGoomba* paragoomba = (CParaGoomba*)(e->obj);
		if (state == KOOPAS_STATE_SHELL_ROTATE) {
			if (paragoomba->GetState() == PARAGOOMBA_STATE_WING_FLYING || paragoomba->GetState() == PARAGOOMBA_STATE_WING_WALKING) {
				paragoomba->SetState(GOOMBA_STATE_WALKING);
			}
			else if (paragoomba->GetState() != GOOMBA_STATE_WALKING) {
				paragoomba->SetState(GOOMBA_HIT_BY_KOOPA);
			}
		}
	}
	else if (dynamic_cast<CQuestionBlock*>(e->obj)) {
		CQuestionBlock* qb = (CQuestionBlock*)e->obj;
		if (state == KOOPAS_STATE_SHELL_ROTATE) {
			qb->SetState(EMPTY_BLOCK_STATE);
		}
	}
	if (!e->obj->IsBlocking()) return;
	// If go end then reverse in walking state
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

	if (state == KOOPAS_STATE_SHELL_IDLE && shell_wait_rotate_start != -1 && GetTickCount64() - shell_wait_rotate_start > KOOPAS_SHELL_WAIT_ROTATE_TIME_OUT && !isOnHand) {
		SetState(KOOPAS_STATE_SHELL_TRANSFORM_WALKING);
	}
	else if (state == KOOPAS_STATE_SHELL_TRANSFORM_WALKING && shell_transform_start != -1 && GetTickCount64() - shell_transform_start > KOOPAS_SHELL_TRANSFORM_WALKING_TIME_OUT) {
		SetState(KOOPAS_STATE_WALKING);
		y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_SHELL_TRANSFORM) / 2;
	}
	else if (state == KOOPAS_STATE_SHELL_TRANSFORM_WALKING) {
		vx = 0;
		vy = 0;
	}
	else if ((state == KOOPAS_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (state == KOOPAS_HIT_BY_KOOPAS)
	{
		if (GetTickCount64() - die_start > GOOMBA_BOUNCE_TIMEOUT) {
			ay = KOOPAS_GRAVITY;
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

int CKoopas::GetAni() {
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
	case KOOPAS_STATE_SHELL_TRANSFORM_WALKING:
		aniId = ID_ANI_KOOPAS_SHELL_TRANSFORM_WALKING;
		break;
	case KOOPAS_STATE_DIE:
		aniId = ID_ANI_KOOPAS_SHELL_IDLE;
		break;
	case KOOPAS_HIT_BY_KOOPAS:
		aniId = ID_ANI_KOOPAS_HIT_BY_KOOPAS;
	}
	return aniId;
}

void CKoopas::Render()
{
	int aniId = GetAni();

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		shell_transform_start = -1;
		vx = -KOOPAS_WALKING_SPEED;
		vy = 0;
		break;
	case KOOPAS_STATE_SHELL_IDLE:
		if (this->state == KOOPAS_STATE_SHELL_ROTATE) {
			y -= 2;
		}
		vx = 0;
		shell_wait_rotate_start = GetTickCount64();
		break;
	case KOOPAS_STATE_SHELL_ROTATE:
		if (this->state == KOOPAS_STATE_SHELL_IDLE) {
			y -= 2;
		}
		shell_wait_rotate_start = -1;
		vx = -KOOPAS_ROTATE_SPEED;
		ay = KOOPAS_GRAVITY;
		break;
	case KOOPAS_STATE_SHELL_TRANSFORM_WALKING:
		shell_wait_rotate_start = -1;
		shell_transform_start = GetTickCount64();
		vx = -KOOPAS_TRANSFORM_SPEED;
		vy = 0;
		break;
	case KOOPAS_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0.06f;
		ay = 0;
		break;
	case KOOPAS_HIT_BY_KOOPAS:
		vx = 0;
		ay = -KOOPAS_GRAVITY;
		die_start = GetTickCount64();
		break;
	}
	CGameObject::SetState(state);
}