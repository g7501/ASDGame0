#include "Editor.h"


void Editor::RunEditor(int type)
{
	if (type==2)
	{
		ParticleEditor();
	}
}

void Editor::ParticleEditor()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "Particle Editor");

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type= sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    Running = !Running;
                }
                if (event.key.code == sf::Keyboard::N)
                {
                    delete CurrentFX;
                    CurrentFX = new ParticleFX();
                }
            }
        }
        window->clear();
        if (CurrentFX && Running)
        {
            CurrentFX->Render(window, sf::Vector2f(0, 0), FrameTime);
            if (CurrentFX->PendingDelete)
            {
                delete CurrentFX;
                CurrentFX = nullptr;
            }
        }
        

        


        window->display();


    }
}



