
#include "stdafx.h"
#include "SplashScreen.h"


void CSplashScreen::Show(sf::RenderWindow& window)
{
	sf::Texture image;
	if (!image.loadFromFile("Content/Screens/Splashscreen.png")) // Image too small. About 1/4th of normal size
		return;

	sf::Sprite sprite(image);

	window.draw(sprite); // Draws sprite on window 
	window.display(); // Displays what's on window

	sf::Event event;
	while (true)
	{
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::EventType::KeyPressed)
				|| (event.type == sf::Event::EventType::MouseButtonPressed)
				|| (event.type == sf::Event::EventType::Closed))
			{
				return; 
			}
		}
	}
}
