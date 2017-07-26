
#ifndef PLAYERPADDLE_H
#define PLAYERPADDLE_H

#include "IEntity.h"


class CPlayerPaddle : public IEntity
{
public:
	CPlayerPaddle();
	~CPlayerPaddle();

	// Overriding functions
	void Update(float deltaTime);
	sf::Vector2f& GetVelocity() { return m_velocity; }
	float GetMagnitude() const { return m_magnitude; }
	void ResetObjects();

private:
	sf::Vector2f m_velocity;
	
	float m_magnitude;	
	float m_playerDelayTime; // Time variable that holds the time a player cannot make an action
	float m_elapsedTimeSinceCollision;
};
#endif