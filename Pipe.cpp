#include "Pipe.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"
CPipe::CPipe(float x, float y,
	float cell_width, float cell_height, int length,
	int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int drawDirection = 1) :CGameObject(x, y)
{
	this->length = length;
	this->cellWidth = cell_width;
	this->cellHeight = cell_height;
	this->spriteIdBegin = sprite_id_begin;
	this->spriteIdMiddle = sprite_id_middle;
	this->spriteIdEnd = sprite_id_end;
	this->drawDirection = drawDirection;
}
void CPipe::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	switch (this->drawDirection) {
	case LEFT_TO_RIGHT: {
		float xx = x - this->cellWidth / 2 + rect.right / 2;

		CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
		break;
	}
	case TOP_TO_BOTTOM: {
		float yy = y - this->cellHeight / 2 + rect.bottom / 2;

		CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
		break;
	}

	}
}



void CPipe::Render()
{
	if (this->length <= 0) return;
	CSprites* s = CSprites::GetInstance();
	switch (this->drawDirection) {
	case LEFT_TO_RIGHT: {
		float xx = x;
		s->Get(this->spriteIdBegin)->Draw(xx, y);
		xx += this->cellWidth;
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdMiddle)->Draw(xx, y);
			xx += this->cellWidth;
		}
		if (length > 1)
			s->Get(this->spriteIdEnd)->Draw(xx, y);
		break;
	}
	case TOP_TO_BOTTOM: {
		float yy = y;
		s->Get(this->spriteIdBegin)->Draw(x, yy);
		yy += this->cellHeight;
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdMiddle)->Draw(x, yy);
			yy += this->cellHeight;
		}
		if (length > 1)
			s->Get(this->spriteIdEnd)->Draw(x, yy);
		break;
	}
	}
	RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	switch (this->drawDirection) {
	case LEFT_TO_RIGHT: {
		float cellWidth_div_2 = this->cellWidth / 2;
		l = x - cellWidth_div_2;
		t = y - float(this->cellHeight / 2) - 1;
		r = l + this->cellWidth * this->length;
		b = t + this->cellHeight;
		break;
	}
	case TOP_TO_BOTTOM: {
		l = x + 1 - this->cellWidth * 2;
		t = y - this->cellHeight / 2 - 1;
		r = x + this->cellWidth * 2;
		b = t + this->cellHeight * this->length;
		break;
	}
	}
}
