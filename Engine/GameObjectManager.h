///-------------------------------------------------------------------------------------------------
// file: GameObjectManager.h 
//
// author: Jesse Berube
// documentation date: 11/30/2019
//
// summary:	The Game Object Manager
///-------------------------------------------------------------------------------------------------
#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_
#pragma once

#include "ISystem.h"

class GameObject;
class PrefabAsset;
class GameObjectManager final : public ISystem
{

private:
	std::map<STRCODE, GameObject*> gameObjects;
	std::list<GameObject*> gameObjectsToRemove;

protected:
	void initialize() override;
	void update(float deltaTime) override;

public:
	static GameObjectManager& instance()
	{
		static GameObjectManager _instance;
		return _instance;
	}
	void addGameObject(GameObject* gameObject);

	void removeGameObject(STRCODE gameObjectUID);
	void removeGameObject(GameObject* gameObject);
	GameObject* findGameObject(STRCODE gameObjectUID);
	GameObject* getGameObjectWithComponent(const std::string& compType);
	std::list<GameObject*> getGameObjectsWithComponent(std::string& compType);
	GameObject* createGameObject();
	GameObject* instantiatePrefab(PrefabAsset* prefab);
	GameObject* createGameObjectWithComponents(std::list<std::string>& comTypes);

private:
	GameObjectManager() = default;
	~GameObjectManager();
	GameObjectManager(const GameObjectManager& other) = default;
	GameObjectManager& operator= (const GameObjectManager& other) = default;


	void load(json::JSON& node, STRCODE levelID);
	void unload(STRCODE levelID);
	void deleteFromRemoveList();
	void initializeAllGameObjects();


	friend class GameEngine;
	friend class FileSystem;
};

#endif