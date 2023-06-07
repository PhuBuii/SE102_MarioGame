#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Coin.h"

#include "Animations.h"

#define ID_ANI_QUESTION_BLOCK 12000
#define ID_ANI_EMPTY_BLOCK 13000

#define QUESTION_BLOCK_STATE 1
#define EMPTY_BLOCK_STATE 2

#define BLOCK_UP_TIME_OUT 75

#define BLOCK_UP_DISTANCE 8

#define QBLOCK_WIDTH 16
#define QBLOCK_BBOX_WIDTH 16
#define QBLOCK_BBOX_HEIGHT 16

class CQuestionBlock : public CGameObject {
private:
	CCoin* coin;
	ULONGLONG up_start;
public:
	CQuestionBlock(float x, float y, vector<LPGAMEOBJECT>& objects);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};