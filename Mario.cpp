#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Koopas.h"
#include "Coin.h"
#include "Portal.h"
#include "Platform.h"
#include "QuestionBlock.h"
#include "PowerUp.h"
#include "Piranha.h"
#include "PSwitch.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x<=10)	x = 10;
	if (x>=3000) x=3000;
	if (y >= 195) SetState(MARIO_STATE_DIE);
	if (isHolding) {
		if (enemies && dynamic_cast<CKoopas*>(enemies)) {
			if (enemies->GetState() != KOOPAS_STATE_WALKING && enemies->GetState() != KOOPAS_HIT_BY_KOOPAS)
				MarioHolding();
			else {
				dynamic_cast<CKoopas*>(enemies)->SetOnHand(false);
				isHolding = false;
				if (enemies ->GetState() != KOOPAS_HIT_BY_KOOPAS)	MarioIsAttacked();
				enemies = NULL;
			}
		}
		else {
			enemies = NULL;
		}
	}
	else {
		if (enemies && dynamic_cast<CKoopas*>(enemies)) {
			dynamic_cast<CKoopas*>(enemies)->SetOnHand(false);
			
			kick_start = GetTickCount64();
			SetState(MARIO_STATE_KICK);
			enemies->SetState(KOOPAS_STATE_SHELL_ROTATE);
			float koopa_vx, koopa_vy;
			enemies->GetSpeed(koopa_vx, koopa_vy);
			if (nx > 0 && koopa_vx < 0) {
				enemies->SetSpeed(-koopa_vx, koopa_vy);
			}
			enemies = NULL;
		}
	}
	vy += ay * dt;
	vx += ax * dt;
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (state == MARIO_STATE_WAIT_DIE && GetTickCount64() - start_die > MARIO_WAIT_DIE_TIME_OUT) {
		start_die = -1;
		SetState(MARIO_STATE_DIE);
	}

	if (isTransform) {

		if (transformType == MARIO_STATE_TRANSFORM) {
			if (GetTickCount64() - transform_start > MARIO_TRANSFORM_TIME_OUT) {
				isTransform = false;
				transform_start = -1;
				if (level == MARIO_LEVEL_SMALL) {
					level = MARIO_LEVEL_BIG;
				}
				else if (level == MARIO_LEVEL_BIG) {
					level = MARIO_LEVEL_SMALL;
				}
			}
			else this->SetState(MARIO_STATE_TRANSFORM);
		}
		else if (transformType == MARIO_STATE_RACOON_TRANSFORM) {
			if (GetTickCount64() - transform_start > MARIO_RACOON_TRANSFORM_TIME_OUT) {
				isTransform = false;
				transform_start = -1;
				if (level == MARIO_LEVEL_RACOON) {
					level = MARIO_LEVEL_BIG;
				}
				else if (level == MARIO_LEVEL_BIG) {
					level = MARIO_LEVEL_RACOON;
				}
			}
			else this->SetState(MARIO_STATE_RACOON_TRANSFORM);
		}
	}
	if (kick_start != -1 && GetTickCount64() - kick_start > MARIO_KICK_TIME_OUT)
	{
		kick_start = -1;
	}
	else if (kick_start != -1) {
		this->SetState(MARIO_STATE_KICK);
	}
	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;

		if (enemies) {
			if (dynamic_cast<CKoopas*>(enemies)) {
				enemies->SetSpeed(vx, vy);
			}
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CParaGoomba*>(e->obj))
		OnCollisionWithParaGoomba(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if(dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CPowerUp*>(e->obj)) 
		OnCollisionWithPowerUp(e);
	else if (dynamic_cast<CPiranha*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CPSwitch*>(e->obj))
		OnCollisionWithPSwitch(e);
}
void CMario::OnCollisionWithPSwitch(LPCOLLISIONEVENT e)
{
	CPSwitch* pswitch = dynamic_cast<CPSwitch*>(e->obj);
	pswitch->IsActived();
}
void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		MarioIsAttacked();
	}
}
void CMario::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	CPiranha* piranha = dynamic_cast<CPiranha*>(e->obj);


	if (untouchable == 0)
	{
		MarioIsAttacked();
	}

}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			MarioIsAttacked();
		}
	}
}

void CMario::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* paragoomba = dynamic_cast<CParaGoomba*>(e->obj);
	float x_goomba, y_goomba;
	paragoomba->GetPosition(x_goomba, y_goomba);
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (paragoomba->GetState() != GOOMBA_STATE_DIE)
		{
			if (paragoomba->GetState() == PARAGOOMBA_STATE_WING_FLYING ||
				paragoomba->GetState() == PARAGOOMBA_STATE_WING_WALKING) {
				paragoomba->SetState(GOOMBA_STATE_WALKING);
				y_goomba -= (e->t * e->dy + e->ny);
				paragoomba->SetPosition(x_goomba, y_goomba);

			}
			else {
				paragoomba->SetState(GOOMBA_STATE_DIE);
			}


			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (paragoomba->GetState() != GOOMBA_STATE_DIE)
			{
				MarioIsAttacked();
			}
		}
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e) {
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	if (koopas->GetState() == KOOPAS_HIT_BY_KOOPAS) return;
	// jump on top >> koopa transform to shell and deflect a bit 
	if (e->ny < 0)
	{
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		if (koopas->GetState() != KOOPAS_STATE_SHELL_ROTATE) {
			if (koopas->GetState() != KOOPAS_STATE_SHELL_IDLE)
			{
				koopas->SetState(KOOPAS_STATE_SHELL_IDLE);
			}
			else if (koopas->GetState() == KOOPAS_STATE_SHELL_IDLE) {
				kick_start = GetTickCount64();
				SetState(MARIO_STATE_KICK);
				koopas->SetState(KOOPAS_STATE_SHELL_ROTATE);
			}
		}
		else {
			koopas->SetState(KOOPAS_STATE_SHELL_IDLE);
		}
	} // Kick shell
	else if (e->nx != 0 && koopas->GetState() == KOOPAS_STATE_SHELL_IDLE) {
		if (handingMode == false) {
			koopas->SetOnHand(false);
			float vx, vy;
			kick_start = GetTickCount64();
			SetState(MARIO_STATE_KICK);
			koopas->SetState(KOOPAS_STATE_SHELL_ROTATE);
			koopas->GetSpeed(vx, vy);
			if (e->nx < 0) {
				if (vx < 0) koopas->SetSpeed(-vx, vy);
			}
			else if (e->nx > 0) {
				if (vx > 0) koopas->SetSpeed(-vx, vy);
			}
		}
		else {
			enemies = koopas;
			isHolding = true;
			MarioHolding();
		}
	}
	else  // hit by koopas
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() != KOOPAS_STATE_SHELL_IDLE && koopas->GetState() != KOOPAS_STATE_SHELL_TRANSFORM_WALKING) {
				MarioIsAttacked();
			}
		}
	}

}
void CMario::MarioIsAttacked() {
	if (level > MARIO_LEVEL_SMALL)
	{
		StartUntouchable();
		isTransform = true;
		transform_start = GetTickCount64();
		if (level == MARIO_LEVEL_BIG) {
			transformType = MARIO_STATE_TRANSFORM;
			this->SetState(MARIO_STATE_TRANSFORM);
		}
		else {
			transformType = MARIO_STATE_RACOON_TRANSFORM;
			this->SetState(MARIO_STATE_RACOON_TRANSFORM);
		}
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_WAIT_DIE);
	}
}
void CMario::MarioHolding() {
	int direction = (vx >= 0) ? 1 : -1;
	if (vx == 0) direction = (nx >= 0) ? 1 : -1;
	dynamic_cast<CKoopas*>(enemies)->SetOnHand(true);
	enemies->SetSpeed(vx, vy);
	switch (level) {
	case MARIO_LEVEL_SMALL:
		if (direction == 1) {
			if (vx == 0)
				enemies->SetPosition(x + direction * (MARIO_SMALL_BBOX_WIDTH + KOOPAS_BBOX_WIDTH + 2) / 2, y);
			else
				enemies->SetPosition(x + direction * (MARIO_SMALL_BBOX_WIDTH + KOOPAS_BBOX_WIDTH + 8) / 2, y);
		}
		else {
			if (vx == 0)
				enemies->SetPosition(x + direction * (MARIO_SMALL_BBOX_WIDTH + KOOPAS_BBOX_WIDTH - 2) / 2, y);
			else
				enemies->SetPosition(x + direction * (MARIO_SMALL_BBOX_WIDTH + KOOPAS_BBOX_WIDTH + 6) / 2, y);
		}
		break;
	case MARIO_LEVEL_BIG:
		if (direction == 1) {
			if (vx == 0)
				enemies->SetPosition(x + direction * (MARIO_BIG_BBOX_WIDTH + KOOPAS_BBOX_WIDTH - 3) / 2, y - 1);
			else
				enemies->SetPosition(x + direction * (MARIO_BIG_BBOX_WIDTH + KOOPAS_BBOX_WIDTH + 5) / 2, y - 1);
		}
		else {
			if (vx == 0)
				enemies->SetPosition(x + direction * (MARIO_BIG_BBOX_WIDTH + KOOPAS_BBOX_WIDTH - 6) / 2, y - 2);
			else
				enemies->SetPosition(x + direction * (MARIO_BIG_BBOX_WIDTH + KOOPAS_BBOX_WIDTH + 3) / 2, y - 2);
		}
		break;
	case MARIO_LEVEL_RACOON:
		if (direction == 1) {
			if (vx == 0)
				enemies->SetPosition(x + direction * (MARIO_RACOON_BBOX_WIDTH + KOOPAS_BBOX_WIDTH - 3) / 2, y - 1);
			else
				enemies->SetPosition(x + direction * (MARIO_RACOON_BBOX_WIDTH + KOOPAS_BBOX_WIDTH + 5) / 2, y - 1);
		}
		else {
			if (vx == 0)
				enemies->SetPosition(x + direction * (MARIO_RACOON_BBOX_WIDTH + KOOPAS_BBOX_WIDTH - 6) / 2, y - 2);
			else
				enemies->SetPosition(x + direction * (MARIO_RACOON_BBOX_WIDTH + KOOPAS_BBOX_WIDTH + 3) / 2, y - 2);
		}
		break;
	}
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	int coin_state = e->obj->GetState();
	if (coin_state == COIN_NORMAL_STATE || coin_state ==COIN_TRANSFORM_STATE) {
		e->obj->Delete();
		coin++;
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e) {
	CQuestionBlock* qb = (CQuestionBlock*)e->obj;
	if (qb->GetTypeBlock() == QBLOCK_TYPE_POWERUP && level == MARIO_LEVEL_BIG)
		qb->SetTypeBlock(QBLOCK_TYPE_LEAF);
	if (e->ny > 0) {
		qb->SetState(EMPTY_BLOCK_STATE);
		if(qb->GetTypeBlock() == QBLOCK_TYPE_COIN)coin++;
	}
}

void CMario::OnCollisionWithPowerUp(LPCOLLISIONEVENT e) {
	CPowerUp* pu = (CPowerUp*)e->obj;
	if (pu->GetState() != POWER_UP_HIDDEN_STATE && pu->GetState() != MUSHROOM_UP_STATE_LEFT && pu->GetState() != MUSHROOM_UP_STATE_RIGHT && pu->GetState() != MUSHROOM_WAIT_STATE) {
		if (level == MARIO_LEVEL_SMALL) {
			isTransform = true;
			transform_start = GetTickCount64();
			transformType = MARIO_STATE_TRANSFORM;
			this->SetState(MARIO_STATE_TRANSFORM);
			SetLevel(MARIO_LEVEL_BIG);
		}
		else if (level == MARIO_LEVEL_BIG) {
			isTransform = true;
			transform_start = GetTickCount64();
			transformType = MARIO_STATE_RACOON_TRANSFORM;
			this->SetState(MARIO_STATE_RACOON_TRANSFORM);
			SetLevel(MARIO_LEVEL_RACOON);
		}
		pu->Delete();
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (this->state == MARIO_STATE_TRANSFORM) {
		if (nx > 0)
			aniId = ID_ANI_MARIO_SMALL_TRANSFORM_TO_BIG_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_TRANSFORM_TO_BIG_LEFT;
	}
	else if (this->state == MARIO_STATE_KICK) {
		if (nx > 0)
			aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
	}
	else if (isHolding) {
		if (vx == 0) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_HOLDING_RIGHT_IDLE;
			else
				aniId = ID_ANI_MARIO_SMALL_HOLDING_LEFT_IDLE;
		}
		else if (vx > 0)
		{
			if (ax < 0)
				aniId = ID_ANI_MARIO_SMALL_HOLDING_RIGHT_IDLE;
			else if (ax == MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_SMALL_HOLDING_RIGHT_RUN;
			else if (ax == MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_SMALL_HOLDING_RIGHT_WALK;
		}
		else // vx < 0
		{
			if (ax > 0)
				aniId = ID_ANI_MARIO_SMALL_HOLDING_LEFT_IDLE;
			else if (ax == -MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_SMALL_HOLDING_LEFT_RUN;
			else if (ax == -MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_SMALL_HOLDING_LEFT_WALK;
		}
	}
	else if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else {
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else {
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (this->state == MARIO_STATE_TRANSFORM) {
		if (nx > 0)
			aniId = ID_ANI_MARIO_BIG_TRANSFORM_TO_SMALL_RIGHT;
		else
			aniId = ID_ANI_MARIO_BIG_TRANSFORM_TO_SMALL_LEFT;
	}
	else if (state == MARIO_STATE_RACOON_TRANSFORM) {
		aniId = ID_ANI_MARIO_RACOON_TRANSFORM_TO_BIG;
	}
	else if (this->state == MARIO_STATE_KICK) {
		if (nx > 0)
			aniId = ID_ANI_MARIO_BIG_KICK_RIGHT;
		else
			aniId = ID_ANI_MARIO_BIG_KICK_LEFT;
	}
	else if (isHolding) {
		if (vx == 0) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_BIG_HOLDING_RIGHT_IDLE;
			else
				aniId = ID_ANI_MARIO_BIG_HOLDING_LEFT_IDLE;
		}
		else if (vx > 0)
		{
			if (ax < 0)
				aniId = ID_ANI_MARIO_BIG_HOLDING_RIGHT_IDLE;
			else if (ax == MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_BIG_HOLDING_RIGHT_RUN;
			else if (ax == MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_BIG_HOLDING_RIGHT_WALK;
		}
		else // vx < 0
		{
			if (ax > 0)
				aniId = ID_ANI_MARIO_BIG_HOLDING_LEFT_IDLE;
			else if (ax == -MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_BIG_HOLDING_LEFT_RUN;
			else if (ax == -MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_BIG_HOLDING_LEFT_WALK;
		}
	}
	else if (!isOnPlatform)
	{
		if (ax == 0) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
int CMario::GetAniIdRacoon() {
	int aniId = -1;
	if (this->state == MARIO_STATE_RACOON_TRANSFORM) {
		aniId = ID_ANI_MARIO_RACOON_TRANSFORM_TO_BIG;
	}
	else if (this->state == MARIO_STATE_KICK) {
		if (nx > 0)
			aniId = ID_ANI_MARIO_RACOON_KICK_RIGHT;
		else
			aniId = ID_ANI_MARIO_RACOON_KICK_LEFT;
	}
	else if (isHolding) {
		if (vx == 0) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACOON_HOLDING_RIGHT_IDLE;
			else
				aniId = ID_ANI_MARIO_RACOON_HOLDING_LEFT_IDLE;
		}
		else if (vx > 0)
		{
			if (ax < 0)
				aniId = ID_ANI_MARIO_RACOON_HOLDING_RIGHT_IDLE;
			else if (ax == MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_RACOON_HOLDING_RIGHT_RUN;
			else if (ax == MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_RACOON_HOLDING_RIGHT_WALK;
		}
		else // vx < 0
		{
			if (ax > 0)
				aniId = ID_ANI_MARIO_RACOON_HOLDING_LEFT_IDLE;
			else if (ax == -MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_RACOON_HOLDING_LEFT_RUN;
			else if (ax == -MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_RACOON_HOLDING_LEFT_WALK;
		}
	}
	else if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0) {
				if (vy < 0) aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_UP_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_DOWN_RIGHT;
			}
			else {
				if (vy < 0) aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_UP_LEFT;
				else aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_DOWN_LEFT;
			}
		}
		else
		{
			if (nx >= 0) {
				if (vy < 0) aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_UP_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_DOWN_RIGHT;
			}
			else {
				{
					if (vy < 0) aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_UP_LEFT;
					else aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_DOWN_LEFT;
				}
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE || state == MARIO_STATE_WAIT_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();
	
	if (untouchable && GetTickCount64() % 2 == 0)
		animations->Get(aniId)->Render(x, y);
	else if (!untouchable)
		animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;
	if (this->state == MARIO_STATE_WAIT_DIE) {
		if (GetTickCount64() - start_die > MARIO_WAIT_DIE_TIME_OUT) {
			vy = -MARIO_DIE_DEFLECT_SPEED;
			ay = MARIO_GRAVITY;
			vx = 0;
			ax = 0;
			CGameObject::SetState(MARIO_STATE_DIE);
		}
		return;
	}
	CGameObject::SetState(state);


	switch (this->state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_KICK:
		vx = 0.0f;
		break;

	case MARIO_STATE_HOLDING:
		isHolding = true;
		break;

	case MARIO_STATE_HOLDING_RELEASE:
		isHolding = false;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_WAIT_DIE:
		vy = 0;
		vx = 0;
		ax = 0;
		ay = 0;
		start_die = GetTickCount64();
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		ay = MARIO_GRAVITY;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_TRANSFORM:
		vy = 0;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_RACOON_TRANSFORM:
		vy = 0;
		vx = 0;
		ax = 0;
		break;
	}


}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG )
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACOON) {
		if (isSitting)
		{
			left = x - MARIO_RACOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjus1t position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL && isTransform == false)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	else if (this->level == MARIO_LEVEL_SMALL && isTransform == true) {
		y -= MARIO_SMALL_BBOX_HEIGHT / 2;
	}
	if (!isTransform) {
		level = l;
	}
}