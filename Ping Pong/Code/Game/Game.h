
#ifndef GAME_H
#define GAME_H

// Forward declarations
class CGameObjectManager;
class CRenderer;

// Dependencies
#include "stdafx.h"
#include "SFMLMusicProvider.h"
#include "SFMLSoundProvider.h"


class CGame
{
public:
	CGame();
	~CGame();

public:
	void Load();
	void Update(float dt);
	void Draw();
	void GameLoop();
	void EndGame();

	bool IsExiting();
	bool DidPlayersScore(); // 0 means player 1 scored, 1 means player 2 scored
	bool DidBallCollideWithPaddle(); // True if collided; false otherwise

private:
	void ShowSplashScreen();
	void ShowMenu();
	
public:
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

	CSFMLMusicProvider m_musicBuffer;
	CSFMLSoundProvider m_soundBuffer;

	static sf::Event m_event;

private:
	sf::Music m_music;
	sf::RenderWindow m_mainWindow;
	Timer m_countDownTimer;
	Timer m_deltaTimer;

private:
	unsigned int m_player1Score; // Send these to private section along with a previous score and use the getters of each to compare whether any player scored (in the getobjectmanager class in the draw function) so you can re update the scoreboard appropriately
	unsigned int m_player2Score;

	int m_scoringPlayer; // 0 is the default value, 1 means player 1 scored, and 2 means player 2 scored

	bool m_updateScore;
	bool m_maxScoreReached; // True if player or AI have reached max score

	float m_currentTime;

private:
	CGameObjectManager* m_pObjectManager;
	CRenderer* m_pRenderer;
};

#endif






