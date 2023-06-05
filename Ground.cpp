#include "Ground.h"

void CGround::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_GROUND)->Draw(x,y);
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GROUND_BBOX_WIDTH / 2;
	t = y - GROUND_BBOX_HEIGHT / 2;
	r = l + GROUND_BBOX_WIDTH;
	b = t + GROUND_BBOX_HEIGHT;
}