#include "Engine.h"

// Constants
const float DEFAULT_BASE_WIDTH = 4.0;
const float DEFAULT_BASE_HEIGHT = 4.0;

const Color DEFAULT_TEXT_COLOR = Color::White;
const string DEFAULT_FONT_FILE = "KOMIKAP_.ttf";
const int DEFAULT_CHARACTER_SIZE = 26;
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
                    }
                    if (event.mouseButton.button == Mouse::Left) {
                        for (int i = 0; i < 5; i++)
                        {
                            std::random_device rd;
                            std::mt19937 gen(rd());
                            std::uniform_int_distribution<int> points(20, 30);

                            Particle p(window, points(gen), sf::Mouse::getPosition(window));
                            m_particles.push_back(p);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Num1)){}
        if (Keyboard::isKeyPressed(Keyboard::Num2)){}

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
}
    

	void Engine::update(float dtAsSeconds)
    {
        if (m_particles.empty() == false)
        {
        for (auto it = m_particles.begin(); it != m_particles.end();) 
        {
        if ((*it).getTTL() <= 0) { 
            it = m_particles.erase(it); // Remove the current element and get the iterator to the next one
        } else {
            (*it).update(dtAsSeconds); // could add multithreading here maybe
            ++it; // Move to the next element
            //cout << "updating particle" << endl;
        }
        }
    }

    }
	
void Engine::draw()
{
    window.clear();

    for (const Particle& p : m_particles)
    {
        window.draw(p, RenderStates::Default);
    }

    window.draw(text);

    window.display(); 
}


// public:
	// The Engine constructor
	Engine::Engine()
    {
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        window.create(desktopMode, "", sf::Style::Fullscreen | sf::Style::None);
        //window.create(desktopMode, "", sf::Style::Default);

        
        if (!font.loadFromFile(DEFAULT_FONT_FILE)) {
            cerr << "Error loading font" << endl;
            return;
        } else {
            cerr << "Font loaded successfully\n";
        }
        text = Text("Left Click to spawn particles!\n", font, DEFAULT_CHARACTER_SIZE);
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
            //float elapsed = (clock.getElapsedTime()).asSeconds(); // consider changing to micro or milli
            //clock.restart();
            float elapsed = (clock.restart()).asSeconds();

            this->input();
            this->update(elapsed);
            this->draw();
        }

    }
