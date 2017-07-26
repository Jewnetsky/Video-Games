#include "stdafx.h"
#include "MainMenu.h"
#include "Game.h"


CMainMenu::MenuResult CMainMenu::Show(sf::RenderWindow& window)
{
	// Load menu image from file
	sf::Texture image;
	image.loadFromFile("Content/Screens/Mainmenu.png");
	sf::Sprite sprite(image);

	/* Setup clickable regions */
	
	// Play menu coordinates
	MenuItem playButton;
	playButton.rect.left = 0;
	playButton.rect.top = 145; // Before 0, 383, 1023, 560
	playButton.rect.width = CGame::SCREEN_HEIGHT / 2;
	playButton.rect.height = CGame::SCREEN_WIDTH;
	playButton.action = Play;

	// Exit menu coordinates
	MenuItem exitButton; 
	exitButton.rect.left = 0;
	exitButton.rect.top = CGame::SCREEN_HEIGHT / 2;
	exitButton.rect.width = CGame::SCREEN_WIDTH / 2;
	exitButton.rect.height = CGame::SCREEN_WIDTH;
	exitButton.action = Exit;

	_menuItems.push_back(playButton); // std::list
	_menuItems.push_back(exitButton); // push_back puts the data at the end of the list

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

CMainMenu::MenuResult CMainMenu::HandleClick(const int x, const int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++) // .end() refers to the last spot in the container AFTER the last item
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.width > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.height > x)
		{
			return (*it).action;
		}
	}

	return Nothing;
}

CMainMenu::MenuResult CMainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed) // If the event that occurred by user was a mouse button press
				return (HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y));
			if ((menuEvent.type == sf::Event::Closed) ||
				(menuEvent.key.code == sf::Keyboard::Escape))
				return Exit;
		}
	}
}



