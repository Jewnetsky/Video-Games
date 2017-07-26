
#ifndef AIPADDLE_H
#define AIPADDLE_H


class CGameObjectManager;

#include "stdafx.h"
#include "IEntity.h"


class CAIPaddle : public IEntity
{
public:
	CAIPaddle();
	~CAIPaddle();

	// Overriding functions
	void Update(float deltaTime);
	sf::Vector2f& GetVelocity() { return m_velocity; }
	float GetMagnitude() const { return m_magnitude; }
	void ResetObjects();

	
private:
	sf::Vector2f m_goal;
	sf::Vector2f m_velocity; 
	float m_magnitude;
	CGameObjectManager* m_objectManager;
	Timer m_speedTimer; // Timer that starts when round begins and keeps track of how long AI has increase speed
	bool m_isInvincible;
};
#endif 