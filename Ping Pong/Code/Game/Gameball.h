
#ifndef GAMEBALL_H
#define GAMEBALL_H

class CGameObjectManager;

#include "IEntity.h"


class CGameball : public IEntity
{
public:
	CGameball();
	~CGameball();

	// Overriding functions
	void Update(float deltaTime);
	sf::Vector2f InitializeVelocity();
	float GetMagnitude() const { return m_magnitude; }
	void ResetObjects();
	
	void ResetRound();
	void CalculateRandomAngle();
	sf::Vector2f& GetVelocity() { return m_goal; }

	
private:
	sf::Vector2f m_goal;
	sf::Vector2f m_velocity;
	
	int m_degrees;

	float m_radians; // Angle of gameball's path from initializing the velocity
	float m_elapsedTimeSinceStart;
	float m_magnitude; // Magnitude of velocity vector
	

	CGameObjectManager* m_pObjectManager;
};
#endif