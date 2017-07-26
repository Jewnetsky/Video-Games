#include "stdafx.h"
#include "Renderer.h"
#include "Game.h"


CRenderer::CRenderer() :
	m_isLoaded(false)
{
}

CRenderer::~CRenderer()
{
}

void CRenderer::LoadTexture(const std::string filename, sf::Sprite& sprite, sf::Texture& image)
{
	if (image.loadFromFile(filename) == false)
	{
		m_filename = "";
		m_isLoaded = false;
	}
	else
	{
		m_filename = filename;
		sprite.setTexture(image);
		m_isLoaded = true;
	}
}

void CRenderer::LoadFont(std::string filename)
{
	assert(m_font.loadFromFile(filename));
}

void CRenderer::Draw(sf::RenderWindow& window, sf::Sprite& sprite)
{
	if (m_isLoaded)
	{
		window.draw(sprite); 
	}
}

void CRenderer::DrawScore(sf::RenderWindow& window, const unsigned int player1Score, const unsigned int player2Score, const bool resetText)
{
	// Get player scores in string
	std::ostringstream output;
	output << player2Score << "\n" << "------" << "\n" << player1Score;

	// Set text
	if (resetText)
		SetText(m_score, m_font, sf::Text::Bold, sf::Color::Cyan, output.str(), 50, CGame::SCREEN_HEIGHT / 3, 30);

	// Draw text
	DrawText(window, m_score);
}

void CRenderer::DrawText(sf::RenderWindow& window, const sf::Text& text)
{
	// Draw text
	window.draw(text);
}

void CRenderer::DrawWinner(sf::RenderWindow& window, const int whoWon)
{
	if (whoWon == 0)
	{
		SetText(m_winner, m_font, sf::Text::Bold, sf::Color::Green, "You Won!", CGame::SCREEN_WIDTH / 3, CGame::SCREEN_HEIGHT / 3, 100);
	}
	else if (whoWon == 1)
	{
		SetText(m_winner, m_font, sf::Text::Bold, sf::Color::Green, "You Lost!", CGame::SCREEN_WIDTH / 3, CGame::SCREEN_HEIGHT / 3, 100);
	}

	DrawText(window, m_winner);
}

void CRenderer::DrawCountdown(sf::RenderWindow& window)
{
	// Set text
	SetText(m_countdown, m_font, sf::Text::Bold, sf::Color::Red, "Start!", CGame::SCREEN_WIDTH / 3, CGame::SCREEN_HEIGHT / 3, 90);

	// Draw text
	DrawText(window, m_countdown);
}

void CRenderer::DrawFPS(sf::RenderWindow& window, const float fps)
{
	// Turn fps into string format
	std::ostringstream output;
	output << fps;

	// Set text <-- does calling this function create program overhead?..
	SetText(m_fps, m_font, sf::Text::Bold, sf::Color::White, output.str(), CGame::SCREEN_WIDTH / 8, CGame::SCREEN_HEIGHT / 8, 30);

	// Draw text
	DrawText(window, m_fps);
}

void CRenderer::SetText(sf::Text& text, const sf::Font& font, const sf::Uint32& style, const sf::Color& color, const std::string line, const float Xpos, const float Ypos, const unsigned int size) const
{
	text.setFont(font);
	text.setString(line);
	text.setCharacterSize(size);
	text.setStyle(style);
	text.setColor(color);
	text.setPosition(Xpos, Ypos);
}

CRenderer& CRenderer::GetRenderer()
{
	static CRenderer renderer;
	return renderer;
}









