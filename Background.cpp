#include "Background.h"

void CBackground::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteIdBackground)->Draw(x, y);
	// Draw only 1 object
	if (this->length == 1) return;

	// Draw LEFT TO RIGHT
	if (this->drawDirection == 1) {

		int xx = x + this->cell;

		for (int i = 1; i < this->length; i++)
		{
			s->Get(this->spriteIdBackground)->Draw(xx, y);
			xx += this->cell;
		}
	} // DRAW TOP TO BOTTOM
	else {
		int yy = y + this->cell;
		for (int i = 1; i < this->length; i++)
		{
			s->Get(this->spriteIdBackground)->Draw(x, yy);
			yy += this->cell;
		}
	}
}



void CBackground::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = right = x;
	top = bottom = y;
}