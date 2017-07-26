
#ifndef COLLISION_H
#define COLLISION_H

#include "stdafx.h"


class CCollision
{
public:
	CCollision();
	~CCollision();
	
	sf::Rect<float> CalculateBroadPhaseBox(const sf::Rect<float>& box, const sf::Vector2f& velocity) const;
	bool IfCollided(const sf::Rect<float>& box1, const sf::Rect<float>& box2) const;
	
public:
	sf::Rect<float> m_broadPhaseBox;
};
#endif
