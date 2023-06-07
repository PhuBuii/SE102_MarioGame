#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


class CBackground : public CGameObject {
private:
	int cellWidth, length, spriteIdBackground;
public:
	CBackground(float x, float y, int cellWidth, int length, int spriteIdBackground) : CGameObject(x, y) {
		this->cellWidth = cellWidth;
		this->length = length;
		this->spriteIdBackground = spriteIdBackground;
	}
	void Render();
	void Update(DWORD dt) {}
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};