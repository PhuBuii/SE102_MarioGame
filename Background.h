#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


class CBackground : public CGameObject {
private:
	int spriteIdBackground;
public:
	CBackground(float x, float y, int spriteIdBackground) : CGameObject(x, y) {
		this->spriteIdBackground = spriteIdBackground;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};