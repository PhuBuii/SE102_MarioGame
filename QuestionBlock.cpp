#include "QuestionBlock.h"
#include "Mario.h"

CQuestionBlock::CQuestionBlock(float x, float y, vector<LPGAMEOBJECT>& objects, int type_block) : CGameObject(x, y) {
	up_start = -1;
	this->type_block = type_block;
	this->ay = 0;
	y_init = y;
	POWERUP_STATE = MUSHROOM_UP_STATE_LEFT;
	CGameObject::SetState(QUESTION_BLOCK_STATE);
	coin = NULL;
	pu = NULL;
	switch (type_block) {
	case QBLOCK_TYPE_COIN:
		coin = new CCoin(x, y - 20);
		coin->SetState(COIN_HIDDEN_STATE);
		objects.push_back(coin);
		break;
	case QBLOCK_TYPE_POWERUP:
		pu = new CPowerUp(x, y - (QBLOCK_BBOX_HEIGHT - MUSHROOM_BBOX_HEIGHT) / 2, MUSHROOM_SUPER);
		pu->SetState(POWER_UP_HIDDEN_STATE);
		objects.push_back(pu);
		break;
	case QBLOCK_TYPE_1UP:
		pu = new CPowerUp(x, y- (QBLOCK_BBOX_HEIGHT - MUSHROOM_BBOX_HEIGHT) / 2, MUSHROOM_1UP);
		pu->SetState(POWER_UP_HIDDEN_STATE);
		objects.push_back(pu);
		break;
	}
}

void CQuestionBlock::OnNoCollision(DWORD dt) {
	y += vy * dt;
}

void CQuestionBlock::SetState(int state) {
	int old_state = this->state;
	CGameObject::SetState(state);

	if (old_state == QUESTION_BLOCK_STATE && state == EMPTY_BLOCK_STATE) {
		vy = -QUESTION_BLOCK_DEFLECT_SPEED;
		ay = QUESTION_BLOCK_GRAVITY;
		up_start = GetTickCount64();

	}

}

void CQuestionBlock::ActiveEvents() {
	switch (this->type_block) {
	case QBLOCK_TYPE_COIN:
		coin->SetState(COIN_UP_STATE);
		break;
	case QBLOCK_TYPE_POWERUP:
		pu->SetState(POWERUP_STATE);
		break;
	case QBLOCK_TYPE_1UP:
		pu->SetState(MUSHROOM_1UP_STATE);
		break;
	}

}

void CQuestionBlock::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMario*>(e->obj)) {
		float m_x, m_y;
		CMario* mario = dynamic_cast<CMario*>(e->obj);
		mario->GetPosition(m_x, m_y);
		if (m_x <= x)
			POWERUP_STATE = MUSHROOM_UP_STATE_LEFT;
		else
			POWERUP_STATE = MUSHROOM_UP_STATE_RIGHT;
	}
}
void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	vy += ay * dt;

	if (this->state == EMPTY_BLOCK_STATE) {
		if ((up_start != -1) && (GetTickCount64() - up_start > BLOCK_UP_TIME_OUT)) {
			vy = QUESTION_BLOCK_DEFLECT_SPEED;
			up_start = -1;
		}

		if (y > y_init && vy != 0) {
			vy = 0;
			ay = 0;
			y = y_init;
			ActiveEvents();
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBlock::Render()
{
	int id_ani = ID_ANI_QUESTION_BLOCK;
	if (state == EMPTY_BLOCK_STATE) {
		id_ani = ID_ANI_EMPTY_BLOCK;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(id_ani)->Render(x, y);
	RenderBoundingBox();
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QBLOCK_WIDTH / 2;
	t = y - QBLOCK_BBOX_HEIGHT / 2;
	r = l + QBLOCK_BBOX_WIDTH;
	b = t + QBLOCK_BBOX_HEIGHT;
}