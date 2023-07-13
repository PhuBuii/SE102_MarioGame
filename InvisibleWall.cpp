#pragma once

#include "InvisibleWall.h"
#include "Platform.h"

void CInvisibleWall::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - width / 2;
	t = y - height / 2;
	r = l + width;
	b = t + height;
}

void CInvisibleWall::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0;
	}
}

void CInvisibleWall::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CInvisibleWall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	vx += ax * dt;
	vy += ay * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CInvisibleWall::SetState(int state) {
	CGameObject::SetState(state);
}