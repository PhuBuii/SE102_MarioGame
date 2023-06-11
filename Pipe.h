#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PIPE 15000
#define PIPE_WIDTH 32
#define PIPE_BBOX_WIDTH 32
#define PIPE_BBOX_HEIGHT 48

#define LEFT_TO_RIGHT	1
#define TOP_TO_BOTTOM	2
class CPipe : public CGameObject {
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
	int drawDirection;
	bool canStanding;
public:
	CPipe(float x, float y, float cell_width, float cell_height, int length, int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int drawDirection);
	void Render();
	void Update(DWORD dt) {}
	void RenderBoundingBox();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};