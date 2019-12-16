#include "Core.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "AssetManager.h"
#include "FileSystem.h"
#include "PrefabAsset.h"

GameObjectManager::~GameObjectManager()
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject.second != nullptr)
		{
			delete gameObject.second;
			gameObject.second = nullptr;
		}
	}
	gameObjects.clear();
	deleteFromRemoveList();
}


//Used to load a file, and cache the level id 
void GameObjectManager::load(json::JSON& node, STRCODE levelID)
{
	if (node.hasKey("GameObjects"))
	{

		json::JSON gameObjectsNode = node["GameObjects"];
		for (auto& gameObjectNode : gameObjectsNode.ArrayRange())
		{
			GameObject* newGameObject = new GameObject();
			
			newGameObject->levelID = levelID;
			
			newGameObject->load(gameObjectNode);
			addGameObject(newGameObject);
		}

		initializeAllGameObjects();
	}
}

//delete all game objects that match the levelid sent
void GameObjectManager::unload(STRCODE levelID)
{
	for (auto gameObject : gameObjects)
	{
		if (gameObject.second != nullptr && gameObject.second->levelID == levelID)
		{
			//If destoryOnUnload is true, destroy the gameobject
			if (gameObject.second->destroyOnUnload)
			{
				removeGameObject(gameObject.second);
			}
		}
	}

	//This will delete the gameobjects right away
	deleteFromRemoveList();
}

void GameObjectManager::deleteFromRemoveList()
{
	//Created this as a function since it would be written multiple times otherwise
	for (auto& gameObject : gameObjectsToRemove)
	{
		if (gameObject != nullptr)
		{
			gameObjects.erase(gameObject->id);
			
			delete gameObject;
			gameObject = nullptr;
		}
	}
	gameObjectsToRemove.clear();
}

//Initialize all gameobjects. Currently called in load()
void GameObjectManager::initializeAllGameObjects()
{
	for (auto gameObject : gameObjects)
	{
		if (gameObject.second != nullptr)
		{
			if (!gameObject.second->initialized)
			{
				gameObject.second->initialize();
			}
		}
	}
}

void GameObjectManager::initialize()
{
}

void GameObjectManager::update(float deltaTime)
{
	deleteFromRemoveList();

	for (auto& gameObject : gameObjects)
	{
		gameObject.second->update(deltaTime);
	}
}

void GameObjectManager::addGameObject(GameObject* gameObject)
{
	//need strcode in gameobject to add
	gameObject->levelID = FileSystem::instance().getCurrentLevel();
	gameObjects.emplace(gameObject->id, gameObject);

}

void GameObjectManager::removeGameObject(STRCODE gameObjectUID)
{
	//Need to check if it is actually in the gameobject list
	GameObject* toRemove = findGameObject(gameObjectUID);

	if (toRemove != nullptr)
	{
		gameObjectsToRemove.push_back(toRemove);
	}
}

void GameObjectManager::removeGameObject(GameObject* gameObject)
{
	//Need to check if it is actually in the gameobject list
	GameObject* toRemove = findGameObject(gameObject->id);

	if (toRemove != nullptr)
	{
		gameObjectsToRemove.push_back(toRemove);
	}
}

GameObject* GameObjectManager::findGameObject(STRCODE gameObjectUID)
{
	auto iter = gameObjects.find(gameObjectUID);
	
	if (iter != gameObjects.end())
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}

GameObject* GameObjectManager::getGameObjectWithComponent(const std::string& compType)
{
	for (auto gameObject : gameObjects)
	{
		if (gameObject.second != nullptr && gameObject.second->getComponent(compType) != nullptr)
		{
			return gameObject.second;
		}
	}
	return nullptr;
}


std::list<GameObject*> GameObjectManager::getGameObjectsWithComponent(std::string& compType)
{
	std::list<GameObject*> returnList;

	for (auto gameObject : gameObjects)
	{
		if (gameObject.second != nullptr && gameObject.second->getComponent(compType) != nullptr)
		{
			returnList.push_back(gameObject.second);
		}
	}
	return returnList;
}

GameObject* GameObjectManager::createGameObject()
{
	GameObject* newGameObject = new GameObject();

	newGameObject->initialize();
	addGameObject(newGameObject);

	return newGameObject;
}

GameObject* GameObjectManager::createGameObjectWithComponents(std::list<std::string>& comTypes)
{
	GameObject* newGameObject = new GameObject();

	newGameObject->createComponents(comTypes);
	newGameObject->initialize();
	addGameObject(newGameObject);
	return newGameObject;
}

GameObject* GameObjectManager::instantiatePrefab(PrefabAsset* prefab)
{
	if (prefab == nullptr)
	{
		return nullptr;
	}
	GameObject* newGameObject = new GameObject();
	newGameObject->load(prefab->getPrefab());
	newGameObject->initialize();
	addGameObject(newGameObject);
	return newGameObject;
}

