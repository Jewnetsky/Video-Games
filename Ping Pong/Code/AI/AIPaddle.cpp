
#include "stdafx.h"
#include "AIPaddle.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "Gamestates.h"


CAIPaddle::CAIPaddle() :
	m_goal(0.0f, 0.0f),
	m_velocity(0.0f, 0.0f),
	m_magnitude(400.0f),
	m_objectManager(nullptr),
	m_isInvincible(false)
{
	LoadImageFile("Content/Screens/Paddle.png");
	assert(DidImageLoad());
	GetSprite().setOrigin(GetBoundingBox().width / 2, GetBoundingBox().height / 2);
	m_objectManager = &CGameObjectManager::GetGameObjectManager();
}

CAIPaddle::~CAIPaddle()
{
}

void CAIPaddle::Update(float deltaTime)
{
	std::shared_ptr<IEntity> ball = m_objectManager->Get("Ball");

	// If round ended and objects and flags need to be reset 
	if (roundState == RoundState::Starting)
	{
		m_speedTimer.Reset();
		roundState = RoundState::Playing;
		m_isInvincible = true;
	}

	// If the total time for the ball moving this round is less than 8 seconds
	if (m_isInvincible)
	{
		if (m_speedTimer.GetTime() < 8)
		{
			if (GetPosition().x > ball->GetPosition().x) // <- This keeps being entered
				m_goal.x = -m_magnitude - 225.0f;
			else if (GetPosition().x < ball->GetPosition().x)
				m_goal.x = m_magnitude + 225.0f;
		}
		else
		{
			m_speedTimer.Stop();
			m_isInvincible = false;
		}
	}
	else
	{
		if (GetPosition().x > ball->GetPosition().x)
			m_goal.x = -m_magnitude;
		else if (GetPosition().x < ball->GetPosition().x)
			m_goal.x = m_magnitude;
	}

	// Calculate velocity this frame
	m_velocity.x = m_goal.x * deltaTime;

	// Screen boundary checks
	if (GetBoundingBox().left + m_velocity.x <= 0.0f ||
		GetBoundingBox().left + GetBoundingBox().width + m_velocity.x >= CGame::SCREEN_WIDTH)
	{
		m_velocity.x = -m_velocity.x;
		m_goal.x = -m_goal.x;
	}

	GetSprite().move(m_velocity.x, 0.0f);
}

void CAIPaddle::ResetObjects()
{
	SetPosition(CGame::SCREEN_WIDTH / 2, 40);
	ZeroVelocity(m_goal);
	ZeroVelocity(m_velocity);
}





