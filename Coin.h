#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000
#define ID_ANI_NOACTION	11001

#define ID_ANI_COIN_DISAPPEAR 11100

#define COIN_NORMAL_STATE 1
#define COIN_HIDDEN_STATE 2
#define COIN_UP_STATE 3
#define COIN_DISAPPEAR 4
#define COIN_TRANSFORM_STATE 5

#define COIN_UP_DISTANCE 35
#define COIN_SPEED_MOVE 0.25f

#define COIN_DISAPPEAR_TIME_ANIMATION 50

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_BY_NONE					0
#define COIN_TRANSFORMED_FROM_BRICK		1

#define COIN_TIMEOUT					10000

class CCoin : public CGameObject {
private:
	ULONGLONG disappear_time;
	float y_start_up;
	int type;

	ULONGLONG remain_start;

	void CoinTransformBrick();
public:
	CCoin(float x, float y, int type = 0) : CGameObject(x, y) {
		remain_start = 0;
		this->type = type;
		if (type == COIN_TRANSFORMED_FROM_BRICK) remain_start = GetTickCount64();
		y_start_up = -1;
		disappear_time = -1;
		CGameObject::SetState(COIN_NORMAL_STATE);

	}
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};