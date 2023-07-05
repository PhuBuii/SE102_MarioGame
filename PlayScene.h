#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;
	float x_mario, y_mario;
	bool isEnableRenderBoundingBox;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _IsInCamera(LPGAMEOBJECT obj);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	void AddObject(CGameObject* obj);
	void Clear();
	void PurgeDeletedObjects();
	void SetIsEnableRenderBoundingBox(bool enableRender) { this->isEnableRenderBoundingBox = enableRender; }
	int GetIsEnableRenderBoundingBox() { return isEnableRenderBoundingBox; }
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	vector<LPGAMEOBJECT>& GetObjects() { return objects; }
};

typedef CPlayScene* LPPLAYSCENE;

