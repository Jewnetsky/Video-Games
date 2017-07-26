
#include "stdafx.h"
#include "Collision.h"


CCollision::CCollision()
{
}

CCollision::~CCollision()
{
}

sf::Rect<float> CCollision::CalculateBroadPhaseBox(const sf::Rect<float>& box, const sf::Vector2f& velocity) const
{
	sf::Rect<float> broadPhaseBox;
	broadPhaseBox.left = velocity.x > 0 ? box.left : box.left + velocity.x; // Left means x coordinate of top left point
	broadPhaseBox.top = velocity.y > 0 ? box.top : box.top + velocity.y; // Top means y coordinate of top left point
	broadPhaseBox.width = velocity.x > 0 ? box.width + velocity.x : box.width - velocity.x;
	broadPhaseBox.height = velocity.y > 0 ? box.height + velocity.y : box.height - velocity.y; // Possible error: could be box.height - velocity.y)
	return broadPhaseBox;
}

bool CCollision::IfCollided(const sf::Rect<float>& box1, const sf::Rect<float>& box2) const
{
	return!(box1.left + box1.width < box2.left || box1.left > box2.left + box2.width ||
		box1.top + box1.height < box2.top || box1.top > box2.top + box2.height); // Changed    Box2.top was 6.0 in debug...
}


