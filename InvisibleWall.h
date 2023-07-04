#include "Animation.h"
#include "Animations.h"
#include "GameObject.h"

#define COLLIABLE_STATE	1
#define	NO_COLLIABLE_STATE	2

class CInvisibleWall : public CGameObject {
protected:

	float ax, ay;
	int width, height;

	bool isOnPlatform;
public:
	CInvisibleWall(float x, float y, int width, int height) : CGameObject(x, y) {
		this->width = width;
		this->height = height;
		ax = 0;
		ay = 0.0002f;
		isOnPlatform = false;
		SetState(COLLIABLE_STATE);
	}
	void Render() { RenderBoundingBox(); }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return state != NO_COLLIABLE_STATE; }

	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetState(int state);

	bool SetOnPlatform(bool isOnPlatform) { this->isOnPlatform = isOnPlatform; }
	bool GetOnPlatform() { return isOnPlatform; }
};