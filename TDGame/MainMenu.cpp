#include "MainMenu.h"

int MainMenu::MenuLoop()
{
	sf::Event event;


	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (StartButton->CallIfHovered())
				{
					window->close();
					return 0;
				}
				if (LoadButton->CallIfHovered())
				{
					window->close();
					return 1;
				}
				if (ExitButton->CallIfHovered())
				{
					window->close();
					return -1;
				}
			}
		}

		window->clear();
		StartButton->Render(window);
		LoadButton->Render(window);
		ExitButton->Render(window);

		


		window->display();
	}

	return 0;
}

MainMenu::MainMenu()
{
	config = getConfiguration();
	//MSWindow::ShellExecute(0, 0, L"http://www.google.com", 0, 0, SW_SHOW);

	window = new sf::RenderWindow(sf::VideoMode(config.ScreenX, config.ScreenY), "TD Game", sf::Style::Fullscreen);
	StartButton = new VButton(sf::Vector2i(config.ScreenX/2-250,300),sf::Vector2i(config.ScreenX/2+250,500),"MainMenu/Start.png");
	LoadButton = new VButton(sf::Vector2i(config.ScreenX / 2 - 250, 600), sf::Vector2i(config.ScreenX / 2 + 250, 800), "MainMenu/Load.png");
	ExitButton = new VButton(sf::Vector2i(config.ScreenX / 2 - 250, 900), sf::Vector2i(config.ScreenX / 2 + 250, 1000), "MainMenu/Exit.png");
}
