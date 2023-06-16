#include "Brick.h"

void CBrick::Render()
{
	int id_ani = ID_ANI_BRICK;
	if (state == ID_STATE_BREAK_BRICK) {
		id_ani = ID_ANI_BREAK_BRICK;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(id_ani)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::SetState(int state) {
	if (state == ID_STATE_BREAK_BRICK)
	{
		disappear_time = GetTickCount64();
	}
	CGameObject::SetState(state);

}
void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}