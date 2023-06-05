#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define ID_ANI_GROUND 1
#define GROUND_WIDTH 49
#define GROUND_BBOX_WIDTH 49
#define GROUND_BBOX_HEIGHT 15

class CGround : public CGameObject {
public:
	CGround(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};