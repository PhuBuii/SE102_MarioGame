#include "TigerBrick.h"

void CTigerBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TIGER_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CTigerBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TIGER_BRICK_BBOX_WIDTH / 2;
	t = y - TIGER_BRICK_BBOX_HEIGHT / 2;
	r = l + TIGER_BRICK_BBOX_WIDTH;
	b = t + TIGER_BRICK_BBOX_HEIGHT;
}