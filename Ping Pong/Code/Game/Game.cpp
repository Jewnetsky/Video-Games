
// Dependencies
#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameObjectManager.h"
#include "IEntity.h"
#include "Gameball.h"
#include "PlayerPaddle.h"
#include "AIPaddle.h" 
#include "Gamestates.h"


CGame::CGame() :
	m_player1Score(0),
	m_player2Score(0),
	m_scoringPlayer(0),
	m_updateScore(true),
	m_maxScoreReached(false),
	m_pObjectManager(nullptr),
	m_pRenderer(nullptr)
{
	// Get game object manager
	m_pObjectManager = &CGameObjectManager::GetGameObjectManager();

	// Get Renderer
	m_pRenderer = &CRenderer::GetRenderer();
}

CGame::~CGame()
{
}

void CGame::Load()
{
	if (gameState != GameState::Uninitialized)
		return;

	// Create window
	m_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pong!");

	// Create and initialize entities 
	std::shared_ptr<IEntity> player1 = std::shared_ptr<IEntity>(new CPlayerPaddle());
	player1->SetPosition(SCREEN_WIDTH / 2, 700);

	std::shared_ptr<IEntity> player2 = std::shared_ptr<IEntity>(new CAIPaddle());
	player2->SetPosition(SCREEN_WIDTH / 2, 40);

	std::shared_ptr<IEntity> ball = std::shared_ptr<IEntity>(new CGameball());
	ball->SetPosition(CGame::SCREEN_WIDTH / 2, CGame::SCREEN_HEIGHT / 2);

	// ** Not the best algorithm for initializing entities **


	// Add game objects to object manager
	m_pObjectManager->Add("Ball", ball);
	m_pObjectManager->Add("Paddle1", player1);
	m_pObjectManager->Add("Paddle2", player2);

	// Update gamestate
	gameState = GameState::ShowingSplash;

	// Load font
	m_pRenderer->LoadFont("Content/Fonts/AGENCYB.ttf");

	// Load sounds into sound cache
	m_soundBuffer.InitSounds();
	
	// Load music into music cache
	m_musicBuffer.InitSounds();
}

void CGame::Update(float dt)
{
	m_pObjectManager->UpdateAll(dt);

	// Play sound if collision occurred
	if (DidBallCollideWithPaddle())
		m_soundBuffer.PlaySound("Content/Sounds/Bounce.m4a");

	// If any player scored, update m_updateScore to true
	if (DidPlayersScore())
	{
		if (m_scoringPlayer == 1)
			m_player1Score++;
		else if (m_scoringPlayer == 2)
			m_player2Score++;
		
		m_updateScore = true;
		roundState = RoundState::Ending;
		m_scoringPlayer = 0;

		// Play goal making sound
		m_soundBuffer.PlaySound("Content/Sounds/Goal.m4a");

		// Switch gameState
		if ((m_player1Score >= 5) ||
			(m_player2Score >= 5))
		{
			gameState = GameState::ShowingMenu;
			m_maxScoreReached = true;
		}
	}
}

void CGame::Draw()
{
	// Draw game objects
	m_pObjectManager->DrawAll(m_mainWindow);

	// Draw score
	m_pRenderer->DrawScore(m_mainWindow, m_player1Score, m_player2Score, m_updateScore);
	if (m_updateScore)
		m_updateScore = false;

	// Draw countdown until game starts if needed
	if (m_countDownTimer.GetTime() < 1.0l)
		m_pRenderer->DrawCountdown(m_mainWindow);

	// Display who won if game ends
	if (gameState == GameState::ShowingMenu)
	{
		// Figure out who won
		if (m_player1Score > m_player2Score)
		{
			m_pRenderer->DrawWinner(m_mainWindow, 0);
		}
		else if (m_player1Score < m_player2Score)
		{
			m_pRenderer->DrawWinner(m_mainWindow, 1);
		}
	}
}

void CGame::GameLoop()
{
	// Loop
	while (m_mainWindow.pollEvent(m_event) || (!IsExiting()))
	{

		// Game flow
		switch (gameState)
		{
		case GameState::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
		case GameState::ShowingMenu:
		{
			ShowMenu();
			if (gameState == GameState::Playing)
				roundState = RoundState::Starting;

			// Initialize currentTime
			m_currentTime = (float)clock();

			break;
		}
		case GameState::Playing:
		{
			// Update frame time variables
			float newTime = (float)clock();
			float dt = (newTime - m_currentTime) / CLOCKS_PER_SEC;
			m_currentTime = newTime;

			if (dt > .01)
				dt = .01f;

			// If round ended, start it
			if (roundState == RoundState::Ending)
				roundState = RoundState::Starting;

			// Start clock when round begins
			if (roundState == RoundState::Starting)
				m_countDownTimer.Reset();

			// Main phase
			m_mainWindow.clear(sf::Color(sf::Color(0, 0, 0))); // Clears window
			Update(dt);
			Draw();
			m_mainWindow.display(); // Renders window

			// If esc key was pressed
			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_event.key.code == sf::Keyboard::Escape)
				{
					gameState = GameState::ShowingMenu;
					roundState = RoundState::Ending;
				}
			}

			// If max score was reached
			if (m_maxScoreReached)
			{
				gameState = GameState::ShowingMenu;
				roundState = RoundState::Ending;
			}


			// Pause screen for two seconds if game ended
			if (gameState == GameState::ShowingMenu)
			{
				if (m_maxScoreReached)
				{
					Timer stallTimer; // Stalls game
					stallTimer.Reset();

					// Stall game for 2 seconds
					while (stallTimer.GetTime() < 2)
					{
					}
				}

				m_pObjectManager->ResetAllToInitial();
				m_player1Score = 0;
				m_player2Score = 0;
				m_updateScore = true;
				m_maxScoreReached = false;
			}
			break;
		}
		}
	}
}

void CGame::EndGame()
{
	m_mainWindow.close();
}

bool CGame::IsExiting()
{
	if (gameState == GameState::Exiting)
		return true;
	else
		return false;
}

bool CGame::DidPlayersScore()
{
	std::shared_ptr<IEntity> ball = m_pObjectManager->Get("Ball");
	if (ball->DidPlayer1Score())
	{
		m_scoringPlayer = 1;
		return true;
	}
	else if (ball->DidPlayer2Score())
	{
		m_scoringPlayer = 2;
		return true;
	}
	else
		return false;
}

bool CGame::DidBallCollideWithPaddle()
{
	std::shared_ptr<IEntity> ball = m_pObjectManager->Get("Ball");
	if (ball->IsColliding())
		return true;
	else
		return false;
}

void CGame::ShowSplashScreen()
{
	CSplashScreen splashScreen; 
	splashScreen.Show(m_mainWindow); 
	gameState = GameState::ShowingMenu;
}

void CGame::ShowMenu()
{
	CMainMenu mainMenu;
	CMainMenu::MenuResult result = mainMenu.Show(m_mainWindow); 

	// Menu flow
	switch (result)
	{
	case CMainMenu::Exit:
	{
		gameState = GameState::Exiting;
		break;
	}
	case CMainMenu::Play:
	{
		gameState = GameState::Playing;
		break;
	}
	}
}
sf::Event CGame::m_event;


	

	

