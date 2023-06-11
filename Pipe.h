#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CPipe : public CGameObject {
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdEnd;
public:
	CPipe(float x, float y, float cell_width, float cell_height, int length, int sprite_id_begin, int sprite_id_end);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};