#include "TeleportGate.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"
#include "TeleportGate.h"

void CTeleportGate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
}

void CTeleportGate::OnCollisionWith(LPGAMEOBJECT obj) {
	
}

void CTeleportGate::TeleObject(LPGAMEOBJECT obj) {
	obj->SetPosition(des_x, des_y);
}

void CTeleportGate::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - TELEPORT_BBOX_WIDTH / 2;
	top = y - TELEPORT_BBOX_HEIGHT / 2;
	right = left + TELEPORT_BBOX_WIDTH;
	bottom = top + TELEPORT_BBOX_HEIGHT;
}

void CTeleportGate::Render() {
	RenderBoundingBox();
}