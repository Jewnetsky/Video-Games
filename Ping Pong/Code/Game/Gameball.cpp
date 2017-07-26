#include "stdafx.h"
#include "Gameball.h"
#include "Game.h"
#include "GameMath.h"
#include "Collision.h"
#include "GameObjectManager.h"
#include "Gamestates.h"


CGameball::CGameball() : 
	m_goal(0.0f, 0.0f),
	m_velocity(0.0f, 0.0f),
	m_degrees(0),
	m_radians(0.0f),
	m_elapsedTimeSinceStart(0.0f),
	m_magnitude(500.0f),
	m_pObjectManager(nullptr)
{
	LoadImageFile("Content/Screens/Gameball.png");
	assert(DidImageLoad());
	GetSprite().setOrigin(15, 15);
	CalculateRandomAngle();
	m_goal = InitializeVelocity();
	m_pObjectManager = &CGameObjectManager::GetGameObjectManager();
}

CGameball::~CGameball()
{
}

void CGameball::Update(float deltaTime) // Elapsed time between last frame
{
	if (roundState == RoundState::Starting) 
		ResetRound();
	
	m_elapsedTimeSinceStart += deltaTime;

	if (m_elapsedTimeSinceStart <= 1.4f)
		return;
	
	// Reset collision flag
	m_isCollisionOccurring = false;

	// Class objects and Vectors
	CGameMath gameMath;
	CCollision collision;
	
	// Get players from entity list
	std::shared_ptr<IEntity> player1 = m_pObjectManager->Get("Paddle1");
	std::shared_ptr<IEntity> player2 = m_pObjectManager->Get("Paddle2");

	// Add deltaTime from previous frame to the time the game started
	m_elapsedTimeSinceStart += deltaTime;

	// Calculate velocity 
	m_velocity = m_goal * deltaTime;
	
	// Broad phase
	collision.m_broadPhaseBox = collision.CalculateBroadPhaseBox(GetBoundingBox(), m_goal);
	if (m_goal.y > 0.0f)
	{
		if (collision.IfCollided(collision.m_broadPhaseBox, player1->GetBoundingBox()))
		{
			if (collision.IfCollided(GetBoundingBox(), player1->GetBoundingBox()))
			{
				if ((GetBoundingBox().left < player1->GetBoundingBox().left ||
					GetBoundingBox().left + GetBoundingBox().width > player1->GetBoundingBox().left + player1->GetBoundingBox().width) && 
					(GetBoundingBox().top + GetBoundingBox().height > player1->GetBoundingBox().top + 5.0f))
				{
					if (GetBoundingBox().left < player1->GetBoundingBox().left)
						GetSprite().setPosition(GetBoundingBox().left - 3, GetPosition().y);
					else if (GetBoundingBox().left + GetBoundingBox().width > player1->GetBoundingBox().left + player1->GetBoundingBox().width)
						GetSprite().setPosition(GetBoundingBox().left + GetBoundingBox().width + 3, GetPosition().y); 
				
					m_goal.x = 0.0f;
					m_velocity.x = 0.0f;

					m_goal.y *= 1.15f;
					m_velocity.y *= 1.15f;
				}
				else
				{
					// If ball is moving right
					if (m_goal.x > 0.0f)
					{
						if (player1->GetVelocity().x > player1->GetMagnitude() / 3.0f)
						{
							gameMath.ScaleVelocity(m_goal, m_velocity, 5.0f, m_magnitude, deltaTime, 0);

							// Check which direction paddle is heading during collision to decide which way the ball reflects
							if (player1->GetVelocity().x >= 0.0f)
							{
								m_goal.y = -m_goal.y;
								m_velocity.y = -m_velocity.y;
							}
							else if (player1->GetVelocity().x < 0.0f)
							{
								m_goal.x = -m_goal.x;
								m_velocity.x = -m_velocity.x;
								m_goal.y = -m_goal.y;
								m_velocity.y = -m_velocity.y;
							}
						}
						else
						{
							if (player1->GetVelocity().x >= 0.0f)
							{
								m_goal.y = -m_goal.y;
								m_velocity.y = -m_velocity.y;
							}
							else if (player1->GetVelocity().x < 0.0f)
							{
								m_goal.x = -m_goal.x;
								m_velocity.x = -m_velocity.x;
								m_goal.y = -m_goal.y;
								m_velocity.y = -m_velocity.y;
							}
						}
					}
					// If ball is moving left
					else if (m_goal.x < 0.0f)
					{
						if (player1->GetVelocity().x < -player1->GetMagnitude() / 3.0f)
						{
							gameMath.ScaleVelocity(m_goal, m_velocity, 5.0f, m_magnitude, deltaTime, 0);
							if (player1->GetVelocity().x >= 0.0f)
							{
								m_goal.x = -m_goal.x;
								m_velocity.x = -m_velocity.x;
								m_goal.y = -m_goal.y;
								m_velocity.y = -m_velocity.y;
							}
							else if (player1->GetVelocity().x < 0.0f)
							{
								m_goal.y = -m_goal.y;
								m_velocity.y = -m_velocity.y;
							}
						}
						else
						{
							if (player1->GetVelocity().x > 0.0f)
							{
								m_goal.x = -m_goal.x;
								m_velocity.x = -m_velocity.x;
								m_goal.y = -m_goal.y;
								m_velocity.y = -m_velocity.y;
							}
							else if (player1->GetVelocity().x <= 0)
							{
								m_goal.y = -m_goal.y;
								m_velocity.y = -m_velocity.y;
							}
						}
					}
				}
				m_isCollisionOccurring = true;
			}
		}
	}
	else if (m_goal.y < 0.0f)
	{
		if (collision.IfCollided(collision.m_broadPhaseBox, player2->GetBoundingBox()))
		{
			if (collision.IfCollided(GetBoundingBox(), player2->GetBoundingBox()))
			{
				if ((GetBoundingBox().left < player2->GetBoundingBox().left ||
					GetBoundingBox().left + GetBoundingBox().width > player2->GetBoundingBox().left + player2->GetBoundingBox().width) &&
					(GetBoundingBox().top < player2->GetBoundingBox().top + player2->GetBoundingBox().height - 5.0f))
				{
					if (GetBoundingBox().left < player1->GetBoundingBox().left)
						GetSprite().setPosition(GetBoundingBox().left - 3, GetPosition().y);
					else if (GetBoundingBox().left + GetBoundingBox().width > player1->GetBoundingBox().left + player1->GetBoundingBox().width)
						GetSprite().setPosition(GetBoundingBox().left + GetBoundingBox().width + 3, GetPosition().y);

					m_goal.x = 0.0f;
					m_velocity.x = 0.0f;

					m_goal.y *= 1.15f;
					m_velocity.y *= 1.15f;
				}
				else
				{
					m_velocity.y = -m_velocity.y;
					m_goal.y = -m_goal.y;
				}

				m_isCollisionOccurring = true;
			}
		}
	}
	
	// Collision detection against y axis
	if ((GetBoundingBox().left + m_velocity.x <= 0.0f) || 
		(GetBoundingBox().left + GetBoundingBox().width + m_velocity.x >= CGame::SCREEN_WIDTH) ||
		(GetBoundingBox().left == 0.0f) || (GetBoundingBox().left + GetBoundingBox().width == CGame::SCREEN_WIDTH))
	{
		if (((m_goal.y >= 0) && (m_goal.y <= 115)) ||
			((m_goal.y <= 0) && (m_goal.y >= -115)))// 0 - 140 140 - 190
		{
			// To avoid multiplying by 0
			if ((m_goal.y >= 0.0f) && (m_goal.y <= 1.5f))
				m_goal.y = 15.0f;
			else if ((m_goal.y < 0.0f) && (m_goal.y >= -1.0f))
				m_goal.y = -15.0f;

			// Apply y scalar
			gameMath.ScaleVelocity(m_goal, m_velocity, 3.0f, m_magnitude, deltaTime, 1);
		
			// Reflect ball
			m_goal.x = -m_goal.x;
			m_velocity.x = -m_velocity.x; // Use inverse sin and cosine to check if these angles are equivelant
	
		}
		else if (((m_goal.y > 115) && (m_goal.y <= 190)) ||
			((m_goal.y < -115) && (m_goal.y >= 190)))
		{
			// Apply y scalar
			gameMath.ScaleVelocity(m_goal, m_velocity, 1.75f, m_magnitude, deltaTime, 1);

			// Reflect ball
			m_goal.x = -m_goal.x;
			m_velocity.x = -m_velocity.x;
		}
		else
		{
			m_goal.x = -m_goal.x;
			m_velocity.x = -m_velocity.x;
		}

		m_isCollisionOccurring = true;
	}

	// Collision detection against the x axis
	if (GetPosition().y + m_velocity.y <= 0.0f + GetBoundingBox().height / 2 ||
		GetPosition().y + GetBoundingBox().height / 2 + m_velocity.y >= CGame::SCREEN_HEIGHT)
	{
		// Add point to appropriate player
		if (GetPosition().y + m_velocity.y <= GetBoundingBox().height / 2)
			m_pAddP1Point = true;
	
		else if (GetPosition().y + GetBoundingBox().height / 2 + m_velocity.y >= CGame::SCREEN_HEIGHT)
			m_pAddP2Point = true;
		
		roundState = RoundState::Ending;
		SetPosition(CGame::SCREEN_WIDTH / 2, CGame::SCREEN_HEIGHT / 2);
	}

	// Move character
	GetSprite().move(m_velocity);
}

sf::Vector2f CGameball::InitializeVelocity()
{
	// Get random angle to send the gameball
	sf::Vector2f newVelocity;

	// Set newVelocity's x and y components
	newVelocity.x = abs(std::cos(m_radians));
	newVelocity.y = abs(std::sin(m_radians));

	// Truncate to avoid e value
	if ((newVelocity.x < 0.009) && (newVelocity.x > -0.009))
		newVelocity.x = 0.0f;
	if ((newVelocity.y < 0.009) && (newVelocity.y > -0.009))
		newVelocity.y = 0.0f;

	// Make sure newVelocity's components are set to match with screen coordinates instead of cartesian
	if ((m_degrees >= 1.0f) && (m_degrees <= 90))
		newVelocity.y = -newVelocity.y;
	else if ((m_degrees >= 91.0f) && (m_degrees <= 180.0f))
	{
		newVelocity.x = -newVelocity.x;
		newVelocity.y = -newVelocity.y;
	}
	else if ((m_degrees >= 181.0f) && (m_degrees <= 270.0f))
		newVelocity.x = -newVelocity.x;

	return newVelocity * m_magnitude;
}

void CGameball::CalculateRandomAngle()
{
	CGameMath gameMath;

	// Get random angle
	std::mt19937::result_type seed = (unsigned int)(time(nullptr));
	auto randNumber = std::bind(std::uniform_int_distribution<int>(0, 360), std::mt19937(seed));
	
	// Get degrees and make sure it is not equal to projection perpendicular to the paddle
	do
	{
		m_degrees = randNumber();
	} while (((m_degrees >= 0) && (m_degrees <= 10)) ||
		((m_degrees >= 80) && (m_degrees <= 100)) ||
		((m_degrees >= 170) && (m_degrees <= 190)) ||
		((m_degrees >= 260) && (m_degrees <= 280)) ||
		((m_degrees >= 350) && (m_degrees <= 360)));

	// Turn deg to rad
	 m_radians = gameMath.DegreesToRadians(m_degrees);
}

void CGameball::ResetObjects()
{
	SetPosition(CGame::SCREEN_WIDTH / 2, CGame::SCREEN_HEIGHT / 2);
	CalculateRandomAngle();
	m_goal = InitializeVelocity();
	ZeroVelocity(m_velocity);
}

void CGameball::ResetRound()
{
	CalculateRandomAngle();
	m_goal = InitializeVelocity();
	m_pAddP1Point = false;
	m_pAddP2Point = false;
	m_elapsedTimeSinceStart = 0.0f;
}



