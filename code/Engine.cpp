#include "Engine.h"

// Constants
const float DEFAULT_BASE_WIDTH = 4.0;
const float DEFAULT_BASE_HEIGHT = 4.0;

const Color DEFAULT_TEXT_COLOR = Color::White;
const string DEFAULT_FONT_FILE = "KOMIKAP_.ttf";
const int DEFAULT_CHARACTER_SIZE = 16;
const string DEFAULT_PRESENTATION_NAME = "Particles\n";
const string DEFAULT_WINDOW_NAME = "Particle Program";





// private:
	// A regular RenderWindow
	// RenderWindow m_Window;

	// vector for Particles
	// vector<Particle> m_particles;

	// Private functions for internal use only
	void Engine::input()
    {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Right) {
                        cout << "Right mouse button clicked\n";
                    }
                    if (event.mouseButton.button == Mouse::Left) {
                        cout << "Left mouse button clicked\n";
                    }
                    break;
                default:
                    break;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Num1)){cout << "Num line 1 pressed\n";}
        if (Keyboard::isKeyPressed(Keyboard::Num2)){cout << "Num line 2 pressed\n";}

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
}
    

	void Engine::update(float dtAsSeconds)
    {

    }
	
    void Engine::draw()
    {

    }

// public:
	// The Engine constructor
	Engine::Engine()
    {
        RenderWindow window(VideoMode::getDesktopMode(), DEFAULT_WINDOW_NAME, Style::Fullscreen);

        Font font;
        if (!font.loadFromFile(DEFAULT_FONT_FILE)) {
            cerr << "Error loading font" << endl;
            return;
        }
        Text text("", font, DEFAULT_CHARACTER_SIZE);
        text.setFillColor(DEFAULT_TEXT_COLOR);
    }

	// Run will call all the private functions
	void Engine::run()
    {
        Clock clock;
        clock.restart();

        cout<< "Starting Particle unit tests..." << endl;
        Particle p(window, 4, { (int)window.getSize().x/2, (int)window.getSize().y/2});
        p.unitTests();
        cout << "Unit tests complete. Starting engine..." << endl;

        while (window.isOpen()) 
        {
            float elapsed = (clock.getElapsedTime()).asSeconds(); // consider changing to micro or milli
            clock.restart();

            this->input();
            this->update(elapsed);
            this->draw();
        }

    }
