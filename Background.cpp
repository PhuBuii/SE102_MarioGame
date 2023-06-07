#include "Background.h"

void CBackground::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteIdBackground)->Draw(x, y);
	// Draw only 1 object
	if (this->length == 1) return;

	int xx = x + this->cellWidth;

	for (int i = 1; i < this->length; i++)
	{
		s->Get(this->spriteIdBackground)->Draw(xx, y);
		xx += this->cellWidth;
	}
}



void CBackground::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = right = x;
	top = bottom = y;
}