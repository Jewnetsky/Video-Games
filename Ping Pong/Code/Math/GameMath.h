
#ifndef GAMEMATH_H
#define GAMEMATH_H

#include <math.h>


/* Vector overloading functions */
inline sf::Vector2f operator*(const sf::Vector2f& left, const sf::Vector2f& right) 
{
	sf::Vector2f product;
	product.x = left.x * right.x;
	product.y = left.y * right.y;
	return product;
}

inline sf::Vector2f operator*(const int scalar, const sf::Vector2f vec) 
{
	sf::Vector2f scaledVector;
	scaledVector.x = vec.x * scalar;
	scaledVector.y = vec.y * scalar;
	return scaledVector;
}

inline sf::Rect<float> operator+(const sf::Rect<float> box1, const sf::Vector2f velocity)
{
	sf::Rect<float> rect;
	rect.left = box1.left + velocity.x;
	rect.top = box1.top + velocity.y;
	return rect;
}

inline sf::Vector2f operator+=(const sf::Vector2f left, const int right)
{
	sf::Vector2f newVec;
	newVec.x = left.x + right;
	newVec.y = left.y + right;
	return newVec;
}


// GameMath class
class CGameMath
{
public:
	inline float DegreesToRadians(int degrees)
	{
		// Get radians
		float _radians = (float)(degrees * 3.14) / 180.0f;

		// Truncate near-zero numbers so value doesn't turn into a value with e
		_radians = (_radians * 100.0f) / 100.0f;

		return _radians;
	}

	inline sf::Vector2f CreateNormalVector(const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Vector2f& v) const
	{
		sf::Vector2f normal;

		if (v.x < 0.0f)
		{
			normal.x = -(point2.y - point1.y);
			normal.y = point2.x - point1.x;
		}
		else if (v.x >= 0.0f)
		{
			normal.x = point2.y - point1.y;
			normal.y = -(point2.x - point1.x);
		}
	
		return normal;
	}

	inline void NormalizeVector(sf::Vector2f& v)
	{
		// Get magnitude
		float magnitude = CalculateMagnitude(v);

		// Divide dimensions of vector by the magnitude of the vector
		v.x = v.x / magnitude;
		v.y = v.y / magnitude;
	}
	
	inline float CalculateMagnitude(const sf::Vector2f& vec) const
	{
		float magnitude = sqrtf((vec.x * vec.x) + (vec.y * vec.y));
		return magnitude;
	}

	inline sf::Vector2f AdjustVelocity(sf::Vector2f& v, const float magnitude) //  Adjusts velocity to given magnitude
	{
		NormalizeVector(v);
		v *= magnitude;
		return v;
	}

	inline void ScaleVelocity(sf::Vector2f& v, sf::Vector2f& vThisFrame, const float scalar, const float magnitude, const float deltaTime, const int axis) // For axis 0 is scale x, 1 is scale y
	{
		if (axis == 0)
		{
			v.x *= scalar;
			AdjustVelocity(v, magnitude);
			vThisFrame = v * deltaTime;
		}
		else if (axis == 1)
		{
			v.y *= scalar;
			AdjustVelocity(v, magnitude);
			vThisFrame = v* deltaTime;
		}
	}
};
#endif

	




