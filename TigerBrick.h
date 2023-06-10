#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_TIGER_BRICK 12001
#define TIGER_BRICK_WIDTH 16
#define TIGER_BRICK_BBOX_WIDTH 16
#define TIGER_BRICK_BBOX_HEIGHT 18

class CTigerBrick : public CGameObject {
public:
	CTigerBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};