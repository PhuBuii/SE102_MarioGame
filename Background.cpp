#include "Background.h"

void CBackground::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteIdBackground)->Draw(x, y);
}


void CBackground::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = right = x;
	top = bottom = y;
}