
#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"


CPlayerPaddle::CPlayerPaddle() :
	m_velocity(0.0f, 0.0f),
	m_magnitude(700.0f),
	m_playerDelayTime(0.0f),
	m_elapsedTimeSinceCollision(0.0f)
{
	LoadImageFile("Content/Screens/Paddle.png");
	assert(DidImageLoad());
	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
}

CPlayerPaddle::~CPlayerPaddle()
{
}

void CPlayerPaddle::Update(float deltaTime)
{
	
	// Stall keyboard input when repeated y axis collision occurs
	if ((m_playerDelayTime > 0.0f) && (m_elapsedTimeSinceCollision <= m_playerDelayTime))
	{
		m_elapsedTimeSinceCollision += deltaTime;
	}
	// Get keyboard input and carry out desired action
	else
	{
		// Reset playerDelayTime to 0
		if ((m_playerDelayTime > 0.0f) && (m_elapsedTimeSinceCollision > 0.0f))
		{
			m_elapsedTimeSinceCollision = 0.0f;
			m_playerDelayTime = 0.0f;
		}

		// Keyboard logic
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //  Originally at 3.0f
		{
			m_velocity.x -= 3.0f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_velocity.x += 3.0f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_velocity.x = 0.0f;
		}
		else if (sf::Event::KeyReleased)
		{
			if ((CGame::m_event.key.code == sf::Keyboard::Left) ||
				(CGame::m_event.key.code == sf::Keyboard::Right))
				m_velocity.x = 0.0f;
		}

		// Make sure velocity doesn't go higher than max velocity/magnitude
		if (m_velocity.x > m_magnitude)
			m_velocity.x = m_magnitude;

		if (m_velocity.x < -m_magnitude)
			m_velocity.x = -m_magnitude;

		sf::Vector2f pos = this->GetPosition();

		if ((GetBoundingBox().left <= 0.0f) ||
			(GetBoundingBox().left + GetBoundingBox().width >= CGame::SCREEN_WIDTH))
		{
			m_playerDelayTime = 0.15f;
			m_velocity.x = -m_velocity.x;
		}
	}

	GetSprite().move(m_velocity.x * deltaTime, 0.0f);
}

void CPlayerPaddle::ResetObjects()
{
	SetPosition(CGame::SCREEN_WIDTH / 2, 700);
	ZeroVelocity(m_velocity);
}


