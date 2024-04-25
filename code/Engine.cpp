#include "Engine.h"

// Constants
const float DEFAULT_BASE_WIDTH = 4.0;
const float DEFAULT_BASE_HEIGHT = 4.0;

const Color DEFAULT_TEXT_COLOR = Color::White;
const string DEFAULT_FONT_FILE = "KOMIKAP_.ttf";
const string DEFAULT_PRESENTATION_NAME = "Particles\n";
const string DEFAULT_WINDOW_NAME = "Particle Program";





// private:
	// A regular RenderWindow
	// RenderWindow m_Window;

	// vector for Particles
	// vector<Particle> m_particles;

	// Private functions for internal use only
	void Engine;input()
    {

    }

	void Engine:update(float dtAsSeconds)
    {

    }
	
    void Engine:draw()
    {

    }

// public:
	// The Engine constructor
	Engine:Engine()
    {
        RenderWindow window(VideoMode(m_pixelWidth, m_pixelHeight), DEFAULT_WINDOW_NAME);

        Font font;
        if (!font.loadFromFile(DEFAULT_FONT_FILE)) {
            cerr << "Error loading font" << endl;
            return;
        }

        Text text("", font, DEFAULT_CHARACTER_SIZE);
        text.setFillColor(DEFAULT_TEXT_COLOR);
    }

	// Run will call all the private functions
	void Engine:run()
    {

    }
