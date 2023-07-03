#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Coin.h"
#include "PowerUp.h"

#include "Animations.h"

#define ID_ANI_QUESTION_BLOCK 12000
#define ID_ANI_EMPTY_BLOCK 13000

#define QUESTION_BLOCK_GRAVITY	0.0002f
#define QUESTION_BLOCK_DEFLECT_SPEED	0.2f

#define QUESTION_BLOCK_STATE 1
#define EMPTY_BLOCK_STATE 2

#define BLOCK_UP_TIME_OUT 80

#define BLOCK_UP_DISTANCE 10

#define QBLOCK_WIDTH 16
#define QBLOCK_BBOX_WIDTH 16
#define QBLOCK_BBOX_HEIGHT 17

#define QBLOCK_TYPE_COIN 1
#define QBLOCK_TYPE_POWERUP 2
#define QBLOCK_TYPE_1UP	3

class CQuestionBlock : public CGameObject {
private:

	float ay;

	float y_init;
	int POWERUP_STATE;

	CCoin* coin;
	CPowerUp* pu;
	ULONGLONG up_start;
	int type_block;
public:
	CQuestionBlock(float x, float y, vector<LPGAMEOBJECT>& objects, int type_block);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
	int GetTypeBlock() { return type_block; }
	void ActiveEvents();

};