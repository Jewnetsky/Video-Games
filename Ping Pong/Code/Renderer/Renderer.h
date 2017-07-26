
#ifndef RENDERER_H
#define RENDERER_H

#include "stdafx.h"


class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void LoadTexture(const std::string filename, sf::Sprite& sprite, sf::Texture& image); // Load filename
	void LoadFont(std::string filename);

	void Draw(sf::RenderWindow& window, sf::Sprite& sprite); // Make a render window
	void DrawScore(sf::RenderWindow& window, const unsigned int player1Score, const unsigned int playerSscore, const bool resetText);
	void DrawText(sf::RenderWindow& window, const sf::Text& text);
	void DrawWinner(sf::RenderWindow& window, const int whoWon); // Prints who won onto screen ------ 0 means player1 won, 1 means player2 won
	void DrawCountdown(sf::RenderWindow& window);
	void DrawFPS(sf::RenderWindow& window, const float fps);

	void SetText(sf::Text& text, const sf::Font& font, const sf::Uint32& style, const sf::Color& color, const std::string line, const float Xpos, const float Ypos, const unsigned int size) const;

	static CRenderer& GetRenderer();

	bool IsLoaded() const { return m_isLoaded; }
	
private:
	std::string m_filename;
	sf::Font m_font;
	bool m_isLoaded; // Checks if filename was loaded or not

private:
	sf::Text m_countdown;
	sf::Text m_winner;
	sf::Text m_score;
	sf::Text m_fps;
};
#endif




