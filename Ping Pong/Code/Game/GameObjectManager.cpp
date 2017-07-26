
#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "IEntity.h"


CGameObjectManager::CGameObjectManager() 
{
}

CGameObjectManager::~CGameObjectManager()
{
}

void CGameObjectManager::Add(const std::string name, const std::shared_ptr<IEntity> gameObject)
{
	_gameObjects.insert(std::pair<std::string, std::shared_ptr<IEntity>>(name, gameObject));
}

void CGameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, std::shared_ptr<IEntity>>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->RenderSprite(renderWindow);
		itr++;
	}
}

void CGameObjectManager::UpdateAll(float dt)
{
	std::map<std::string, std::shared_ptr<IEntity>>::const_iterator itr = _gameObjects.begin();

	while (itr != _gameObjects.end())
	{
		itr->second->Update(dt);
		itr++;
	}
}

void CGameObjectManager::ResetAllToInitial()
{
	std::map<std::string, std::shared_ptr<IEntity>>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->ResetObjects();
		itr++;
	}
}

std::shared_ptr<IEntity> CGameObjectManager::Get(const std::string name) const
{
	std::map<std::string, std::shared_ptr<IEntity>>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return nullptr;
	return results->second;
}

CGameObjectManager& CGameObjectManager::GetGameObjectManager()
{
	static CGameObjectManager objectManager;
	return objectManager;
}