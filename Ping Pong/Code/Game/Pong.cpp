/*
Made by: Adam Janetsky
2d C++ Ping Pong Game using SFML
*/

/* 
HUNGARIAN NOTATION GUIDE:
Below are the meanings of the naming convention I used

I - Interface/Abstract class
C - Class
m_ - member of a class
p - pointer
*/

#include "stdafx.h"
#include "Game.h"
#include "SFMLMusicProvider.h"


int main(int argc, _TCHAR* argv[])
{
	CGame game;

	// Load
	game.Load();

	// Create audio thread
	CSFMLMusicProvider::MusicHandler mHandler; // Music handler
	std::thread audioThread(mHandler, &game.m_musicBuffer);

	// Game loop
	game.GameLoop();

	// Join thread
	if (audioThread.joinable())
		audioThread.join();

	// End game
	game.EndGame();
	return 0;
}
