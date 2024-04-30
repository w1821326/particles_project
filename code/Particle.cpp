#include "Particle.h"


//Public Functions
Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition)
{
    cerr << "Made it into Particle()\n";
    std::random_device rd;
    std::mt19937 gen(rd());

    m_numPoints = numPoints;
    
    srand(time(0));
    m_radiansPerSec = MY_PI * (float)rand() / (2); // consider changing the constant to change max rotation speed
    
        m_cartesianPlane.setCenter(0,0);
    m_cartesianPlane.setSize(target.getSize().x, (-1.0)*target.getSize().y);

    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition);
    m_ttl = TTL; // consider making random;

    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

    
    m_vx = (rand() % (500 - 500 + 1)) + (-500);
    m_vy = (rand() % (200 + 1));

    m_color1 = Color(255,255,255,255);
    int red;
    int green;
    int blue;
    do
    {
        red = rand() % (255+1);
        green = rand() % (255+1);
        blue = rand() % (255+1);
    
    } while ((red + green + blue) <= 200);
    m_color2 = Color(red, green, blue, 255);
 
    

    m_A = Matrix(2, m_numPoints);

    

    std::uniform_real_distribution<float> distribution(0.0f, MY_PI/2);

    // Generate random floats
    float theta = distribution(gen);
    float dTheta = 2 * MY_PI / (numPoints-1);

    for (int j = 0; j < numPoints; j++)
    {
        float r, dx, dy;
        
        std::uniform_real_distribution<float> r_dist(20.0f, 80.0f);
        r = r_dist(gen);
        dx = r * cos(theta);
        dy = r * sin(theta);

        m_A(0, j) = m_centerCoordinate.x + dx;
        m_A(1, j) = m_centerCoordinate.y + dy;

        theta += dTheta;
    }


}

void Particle::draw(RenderTarget& target, RenderStates states) const
{
    VertexArray lines(PrimitiveType::TriangleFan, m_numPoints+1);

    Vector2i center = target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane);
    
    lines[0].position = static_cast<sf::Vector2f>(center);
    lines[0].color = m_color1;

    for (int j = 1; j < m_numPoints+1; j++)
    {
        Vector2f next_point_f(m_A(0, j-1), m_A(1, j-1));


        Vector2i next_point_i = target.mapCoordsToPixel(next_point_f, m_cartesianPlane);

        lines[j].position = static_cast<sf::Vector2f>(next_point_i);
        lines[j].color = m_color2;
    }

    target.draw(lines);
}



void Particle::update(float dt)
{
    m_ttl -= dt;

    this->rotate(dt*m_radiansPerSec);
    this->scale(dt);

    float dx = dt * m_vx;
    
    m_vy -= (G*dt);
    float dy = (m_vy*dt);

    this->translate(dx, dy); 

}

// Private Functions
    ///rotate Particle by theta radians counter-clockwise
    ///construct a RotationMatrix R, left mulitply it to m_A
    void Particle::rotate(double theta)
    {
        Vector2f temp = m_centerCoordinate;
        this->translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
        
        RotationMatrix r = RotationMatrix(theta);

        m_A = r * m_A; 

        this->translate(temp.x, temp.y);
    }

    ///Scale the size of the Particle by factor c
    ///construct a ScalingMatrix S, left multiply it to m_A
    void Particle::scale(double c)
    {
        Vector2f temp = m_centerCoordinate;
        this->translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
        
        ScalingMatrix s = ScalingMatrix(c);
        m_A = s * m_A;

        this->translate(temp.x, temp.y);
    }

    ///shift the Particle by (xShift, yShift) coordinates
    ///construct a TranslationMatrix T, add it to m_A
    void Particle::translate(double xShift, double yShift)
    {
        TranslationMatrix t = TranslationMatrix(xShift, yShift, m_numPoints);
        m_A = t + m_A;

        m_centerCoordinate.x += xShift;
        m_centerCoordinate.y += yShift;
    }

//////////////////////////
// Unit Testing functions

bool Particle::almostEqual(double a, double b, double eps)
{
	return fabs(a - b) < eps;
}

void Particle::unitTests()
{
    int score = 0;

    cout << "Testing RotationMatrix constructor...";
    double theta = MY_PI / 4.0;
    RotationMatrix r(MY_PI / 4);
    if (r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0, 0), cos(theta))
        && almostEqual(r(0, 1), -sin(theta))
        && almostEqual(r(1, 0), sin(theta))
        && almostEqual(r(1, 1), cos(theta)))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if (s.getRows() == 2 && s.getCols() == 2
        && almostEqual(s(0, 0), 1.5)
        && almostEqual(s(0, 1), 0)
        && almostEqual(s(1, 0), 0)
        && almostEqual(s(1, 1), 1.5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if (t.getRows() == 2 && t.getCols() == 3
        && almostEqual(t(0, 0), 5)
        && almostEqual(t(1, 0), -5)
        && almostEqual(t(0, 1), 5)
        && almostEqual(t(1, 1), -5)
        && almostEqual(t(0, 2), 5)
        && almostEqual(t(1, 2), -5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    
    cout << "Testing Particles..." << endl;
    cout << "Testing Particle mapping to Cartesian origin..." << endl;
    if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
    {
        cout << "Failed.  Expected (0,0).  Received: (" << m_centerCoordinate.x << "," << m_centerCoordinate.y << ")" << endl;
    }
    else
    {
        cout << "Passed.  +1" << endl;
        score++;
    }

    cout << "Applying one rotation of 90 degrees about the origin..." << endl;
    Matrix initialCoords = m_A;
    rotate(MY_PI / 2.0);
    bool rotationPassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1, j), initialCoords(0, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            rotationPassed = false;
        }
    }
    if (rotationPassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a scale of 0.5..." << endl;
    initialCoords = m_A;
    scale(0.5);
    bool scalePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0,j)) || !almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            scalePassed = false;
        }
    }
    if (scalePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a translation of (10, 5)..." << endl;
    initialCoords = m_A;
    translate(10, 5);
    bool translatePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            translatePassed = false;
        }
    }
    if (translatePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Score: " << score << " / 7" << endl;
}
