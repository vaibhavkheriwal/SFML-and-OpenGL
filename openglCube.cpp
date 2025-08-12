#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
    // create window
    sf::Window window(sf::VideoMode(800, 600), "3D Cube");
    window.setFramerateLimit(60);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = 800.f / 600.f;
    glFrustum(-aspect, aspect, -1.0, 1.0, 1.0, 100.0);

    bool running = true;
    sf::Event event;
    float angle = 0.f; // rotation angle

    while (running)
    {
        // handle events
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) running = false;
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) running = false;
        }

        // clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // reset modelview
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // move back so cube is visible
        glTranslatef(0.f, 0.f, -5.f);

        // rotate cube around y-axis at its origin
        glRotatef(angle, 0.f, 1.f, 0.f);

        // draw cube as white wireframe
        glColor3f(1.f, 1.f, 1.f);
        glBegin(GL_LINE_LOOP); // front face
        glVertex3f(-1.f, -1.f, 1.f);
        glVertex3f(1.f, -1.f, 1.f);
        glVertex3f(1.f, 1.f, 1.f);
        glVertex3f(-1.f, 1.f, 1.f);
        glEnd();

        glBegin(GL_LINE_LOOP); // back face
        glVertex3f(-1.f, -1.f, -1.f);
        glVertex3f(1.f, -1.f, -1.f);
        glVertex3f(1.f, 1.f, -1.f);
        glVertex3f(-1.f, 1.f, -1.f);
        glEnd();

        glBegin(GL_LINES); // connect edges
        glVertex3f(-1.f, -1.f, 1.f); glVertex3f(-1.f, -1.f, -1.f);
        glVertex3f(1.f, -1.f, 1.f); glVertex3f(1.f, -1.f, -1.f);
        glVertex3f(1.f, 1.f, 1.f); glVertex3f(1.f, 1.f, -1.f);
        glVertex3f(-1.f, 1.f, 1.f); glVertex3f(-1.f, 1.f, -1.f);
        glEnd();

        // update angle for continuous rotation
        angle += 1.f;
        if (angle > 360.f) angle = 0.f;

        // display frame
        window.display();
    }

    window.close();
    return 0;
}
