#include "Pipe.h"
CPipe::CPipe(float x, float y,
	float cell_width, float cell_height, int length,
	int sprite_id_begin, int sprite_id_end) : CGameObject(x, y)
{
	this->length = length;
	this->cellWidth = cell_width;
	this->cellHeight = cell_height;
	this->spriteIdBegin = sprite_id_begin;
	this->spriteIdEnd = sprite_id_end;
}
void CPipe::Render()
{
	if (this->length <= 0) return;
	CAnimations* s = CAnimations::GetInstance();

		float yy = y;
		s->Get(this->spriteIdBegin)->Render(x, yy);
		yy += this->cellHeight;
		for (int i = 1; i < this->length; i++)
		{
			s->Get(this->spriteIdEnd)->Render(x, yy);
			yy += this->cellHeight;
		}
	//RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->cellWidth / 2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth;
	b = t + this->cellHeight*this->length;
}
