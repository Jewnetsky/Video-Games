
#ifndef MAINMENU_H
#define MAINMENU_H

#include "stdafx.h"


class CMainMenu
{
public:
	enum MenuResult {Nothing, Exit, Play};

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		MenuResult action;
	};
	MenuResult Show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(const int x, const int y);
	std::list<MenuItem> _menuItems;
};
#endif