
#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

class IEntity;

class CGameObjectManager
{
public:
	CGameObjectManager();
	~CGameObjectManager();

	void Add(const std::string name, const std::shared_ptr<IEntity> gameObject);
	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll(float dt);
	void ResetAllToInitial();

	std::shared_ptr<IEntity> Get(const std::string name) const;
	
	static CGameObjectManager& GetGameObjectManager();

private:
	std::map <std::string, std::shared_ptr<IEntity>> _gameObjects;
	sf::Clock clock;
};
#endif


