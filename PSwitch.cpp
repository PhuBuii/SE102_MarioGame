#include "Game.h"
#include "PSwitch.h"
#include "PlayScene.h"

void CPSwitch::Render() {
	int aniId = ID_ANI_PSWITCH;
	if (isActived) aniId = ID_ANI_PSWITCH_ACTIVED;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);

	/*RenderBoundingBox();*/
}

void CPSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (y <= y_rise) {
		/*y += vy * dt;*/
		SetState(PSWITCH_STATE_STATIC);
	}
	/*vy += ay * dt;*/
	y += vy * dt;
	/*x += vx * dt; */

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPSwitch::GetBoundingBox(float& l, float& t, float& r, float& b) {
	if (!isActived) {
		l = x - PSWITCH_BBOX_WIDTH / 2;
		t = y - PSWITCH_BBOX_HEIGHT / 2;
		r = l + PSWITCH_BBOX_WIDTH;
		b = t + PSWITCH_BBOX_HEIGHT;
	}
	else {
		l = x - PSWITCH_ACTIVED_BBOX_WIDTH / 2;
		t = y - PSWITCH_ACTIVED_BBOX_HEIGHT / 2;
		r = l + PSWITCH_ACTIVED_BBOX_WIDTH;
		b = t + PSWITCH_ACTIVED_BBOX_HEIGHT;
	}
}

void CPSwitch::IsActived() {
	if (isActived) return;

	isActived = true;

	if ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene()) {
		vector<LPGAMEOBJECT> objects = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetObjects();

		for (size_t i = 0; i < objects.size(); i++)
			if (dynamic_cast<CGlassBrick*>(objects[i]))
				dynamic_cast<CGlassBrick*>(objects[i])->BrickTransformCoin();
	}
}

void CPSwitch::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case  PSWITCH_STATE_RISING:
		vy = -PSWITCH_RISING_SPEED;
		break;
	case  PSWITCH_STATE_STATIC:
		vy = 0;
		break;
	}
}

