#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


class CBackground : public CGameObject {
private:
	int cell, length, spriteIdBackground, drawDirection;
public:
	CBackground(float x, float y, int cell, int length, int spriteIdBackground, int drawDirection = 1) : CGameObject(x, y) {
		this->cell = cell;
		this->length = length;
		this->spriteIdBackground = spriteIdBackground;
		this->drawDirection = drawDirection;
	}
	void Render();
	void Update(DWORD dt) {}
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};