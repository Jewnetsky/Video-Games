
#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"
#include "Renderer.h"


class IEntity
{
public:
	IEntity() : m_isCollisionOccurring(false),
		m_pAddP1Point(false),
		m_pAddP2Point(false) {}
		
	virtual ~IEntity() {}

	void LoadImageFile(const std::string filename) { CRenderer::GetRenderer().LoadTexture(filename, GetSprite(), m_image); };
	void RenderSprite(sf::RenderWindow& window) { CRenderer::GetRenderer().Draw(window, GetSprite()); }
	bool DidImageLoad() const { return CRenderer::GetRenderer().IsLoaded(); }

	// Pure virtuals
	virtual void Update(float) = 0;
	virtual sf::Vector2f& GetVelocity() = 0;
	virtual float GetMagnitude() const = 0;
	virtual void ResetObjects() = 0; // Restores entity objects to their initial state

	bool DidPlayer1Score() const { return m_pAddP1Point; }
	bool DidPlayer2Score() const { return m_pAddP2Point; }

    virtual bool IsColliding() const { return m_isCollisionOccurring; } // Check what this is

protected:
	sf::Sprite& GetSprite() { return m_sprite; };

	bool m_isCollisionOccurring;
	bool m_pAddP1Point;
	bool m_pAddP2Point;

private:
	sf::Sprite m_sprite;
	sf::Texture m_image;

public:
	virtual sf::Rect<float> GetBoundingBox() { return GetSprite().getGlobalBounds(); }

	inline void SetPosition(float x, float y)
	{
		if (CRenderer::GetRenderer().IsLoaded())
		{
			GetSprite().setPosition(x, y);
		}
	}

	inline sf::Vector2f GetPosition()
	{
		if (CRenderer::GetRenderer().IsLoaded())
		{
			return GetSprite().getPosition();
		}
		return sf::Vector2f();
	}
	
	inline void ZeroVelocity(sf::Vector2f& velocity) 
	{
		velocity.x = 0.0f;
		velocity.y = 0.0f;
	}
};
#endif

// NOTE: Child classes access different copies of their parent class when their parent class is an interface


