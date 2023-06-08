#include "QuestionBlock.h"

CQuestionBlock::CQuestionBlock(float x, float y, vector<LPGAMEOBJECT>& objects, int type_block) : CGameObject(x, y) {
	up_start = -1;
	this->type_block = type_block;
	CGameObject::SetState(QUESTION_BLOCK_STATE);
	switch (type_block) {
	case QBLOCK_TYPE_COIN:
		coin = new CCoin(x, y - 20);
		coin->SetState(COIN_HIDDEN_STATE);
		objects.push_back(coin);
		break;
	case QBLOCK_TYPE_POWERUP:
		break;
	}
}

void CQuestionBlock::SetState(int state) {
	int old_state = this->state;
	CGameObject::SetState(state);

	if (old_state == QUESTION_BLOCK_STATE && state == EMPTY_BLOCK_STATE) {
		if (type_block == QBLOCK_TYPE_COIN) {
			coin->SetState(COIN_UP_STATE);
		}
		y -= BLOCK_UP_DISTANCE;
		up_start = GetTickCount64();
	}

}

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if ((this->state == EMPTY_BLOCK_STATE) && (up_start != -1) && (GetTickCount64() - up_start > BLOCK_UP_TIME_OUT)) {
		y += BLOCK_UP_DISTANCE;
		up_start = -1;
	}

	CGameObject::Update(dt, coObjects);
}

void CQuestionBlock::Render()
{
	int id_ani = ID_ANI_QUESTION_BLOCK;
	if (state == EMPTY_BLOCK_STATE) {
		id_ani = ID_ANI_EMPTY_BLOCK;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(id_ani)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QBLOCK_WIDTH / 2;
	t = y - QBLOCK_BBOX_HEIGHT / 2;
	r = l + QBLOCK_BBOX_WIDTH;
	b = t + QBLOCK_BBOX_HEIGHT;
}