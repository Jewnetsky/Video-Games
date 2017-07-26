
#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class GameState 
{ 
	Uninitialized, 
	ShowingSplash, 
	Paused,
	ShowingMenu, 
	Playing, 
	Exiting 
};

enum class RoundState 
{ 
	Starting, 
	Playing, 
	Ending
};

extern GameState gameState;
extern RoundState roundState;
#endif