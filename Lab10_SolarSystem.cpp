#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <string>

// Global Variables
float year = 0.0f;
float day = 0.0f;
float moonOrbit = 0.0f;
float storyProgress = 0.0f;

// Window dimensions
int windowWidth = 800;
int windowHeight = 600;

void drawText(const std::string& text, float x, float y) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawTextOverlay() {
    glDisable(GL_LIGHTING); // Disable lighting for text
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f); // White text

    std::string message;
    if (storyProgress < 40.0f) {
        message = "66M BCE: Late Cretaceous. Dinosaurs thrive globally.";
    } else if (storyProgress >= 40.0f && storyProgress < 50.0f) {
        message = "IMPACT: A 10km asteroid strikes the Yucatan Peninsula!";
        glColor3f(1.0f, 0.2f, 0.2f); // Red text for impact
    } else if (storyProgress >= 50.0f && storyProgress < 80.0f) {
        message = "AFTERMATH: Ash blocks the sun. 75% of life goes extinct.";
        glColor3f(0.7f, 0.7f, 0.7f); // Gray text for aftermath
    } else if (storyProgress >= 80.0f && storyProgress < 120.0f) {
        message = "2.5M BCE: The Ice Age. Glaciers cover the Earth and Megafauna roam.";
        glColor3f(0.6f, 0.8f, 1.0f); // Light blue
    } else if (storyProgress >= 120.0f && storyProgress < 150.0f) {
        message = "10k BCE: Rapid climate warming & human hunting cause Megafauna extinction.";
        glColor3f(1.0f, 0.8f, 0.4f); // Yellowish
    } else if (storyProgress >= 150.0f && storyProgress < 170.0f) {
        message = "2500 BCE: Ancient Egypt. The Great Pyramids are built.";
        glColor3f(0.8f, 1.0f, 0.8f); // Light green
    } else if (storyProgress >= 170.0f && storyProgress < 190.0f) {
        message = "1 CE: Birth of Christ and the peak of the Roman Empire.";
        glColor3f(1.0f, 0.8f, 0.0f); // Gold
    } else if (storyProgress >= 190.0f && storyProgress < 210.0f) {
        message = "1347 CE: The Black Death sweeps across Eurasia, killing millions.";
        glColor3f(0.5f, 0.8f, 0.2f); // Sickly green
    } else if (storyProgress >= 210.0f && storyProgress < 230.0f) {
        message = "18th Century: The Industrial Revolution begins. Smog fills the air.";
        glColor3f(0.6f, 0.6f, 0.6f); // Grey
    } else {
        message = "Present Day: The Information Age & Space Exploration.";
        glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    }

    drawText(message, 20.0f, 20.0f);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW); // Ensure we are back in modelview
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Space background
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Light configuration
    GLfloat light_ambient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 5.0, 15.0,  // Eye
              0.0, 0.0, 0.0,   // Center
              0.0, 1.0, 0.0);  // Up

    // Light position (at Sun's center)
    GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // 1. The Sun
    glPushMatrix();
        GLfloat emissionOn[] = { 1.0f, 0.8f, 0.0f, 1.0f };
        GLfloat emissionOff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionOn);
        glColor3f(1.0f, 0.8f, 0.0f); // Yellow
        glutSolidSphere(1.5, 40, 40);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionOff); // Turn off for other objects
    glPopMatrix();

    // Earth's orbit configuration
    float earthOrbitRadius = 6.0f;

    // 2. The Earth
    glPushMatrix();
        glRotatef(year, 0.0f, 1.0f, 0.0f); // Orbit around Sun
        glTranslatef(earthOrbitRadius, 0.0f, 0.0f);

        glPushMatrix(); // Save Earth's center for drawing Earth itself
            glRotatef(day, 0.0f, 1.0f, 0.0f); // Earth's axial spin
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Align poles

            if (storyProgress >= 230.0f) {
                glColor3f(0.1f, 0.4f, 0.8f); // Modern Earth (ocean blue)
            } else if (storyProgress >= 210.0f) {
                glColor3f(0.4f, 0.4f, 0.4f); // Industrial smog (grey/brown)
            } else if (storyProgress >= 190.0f) {
                glColor3f(0.4f, 0.5f, 0.3f); // Black Death (sickly dark green)
            } else if (storyProgress >= 120.0f) {
                glColor3f(0.2f, 0.6f, 0.3f); // Early Humans (green/lush)
            } else if (storyProgress >= 80.0f) {
                glColor3f(0.8f, 0.9f, 1.0f); // Ice Age Earth (white/icy)
            } else if (storyProgress >= 50.0f) {
                glColor3f(0.3f, 0.25f, 0.2f); // Dark ash/brown
            } else {
                glColor3f(0.1f, 0.4f, 0.8f); // Ocean blue
            }
            glutSolidSphere(0.6, 30, 30);
        glPopMatrix();

        // 3. The Moon
        glPushMatrix();
            glRotatef(moonOrbit, 0.0f, 1.0f, 0.0f);
            glTranslatef(1.2f, 0.0f, 0.0f);
            glColor3f(0.6f, 0.6f, 0.6f); // Gray moon
            glutSolidSphere(0.2, 20, 20);
        glPopMatrix();

        // 4. The Asteroid / Impact Effect (Local to Earth)
        if (storyProgress < 50.0f) {
            // Asteroid approaching
            glPushMatrix();
                // Interpolate from a distant point down to (0,0,0) relative to Earth
                float t = storyProgress / 50.0f; // 0.0 to 1.0
                float startX = 5.0f, startY = 8.0f, startZ = -5.0f;
                float currentX = startX * (1.0f - t);
                float currentY = startY * (1.0f - t);
                float currentZ = startZ * (1.0f - t);

                glTranslatef(currentX, currentY, currentZ);
                glColor3f(0.3f, 0.3f, 0.3f); // Dark gray
                glutSolidSphere(0.15, 15, 15);
            glPopMatrix();
        } else if (storyProgress >= 50.0f && storyProgress < 80.0f) {
            // Impact Effect: Expanding Torus
            glPushMatrix();
                glDisable(GL_LIGHTING);
                float expansion = (storyProgress - 50.0f) * 0.1f; // grows as progress increases
                glColor3f(1.0f, 0.5f, 0.0f); // Bright orange
                
                // Align torus to Earth surface/equator
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                glutWireTorus(0.05 + expansion * 0.2, 0.6 + expansion, 15, 30);
                glEnable(GL_LIGHTING);
            glPopMatrix();
        }

        // 5. Historic Eras Effects
        if (storyProgress >= 150.0f && storyProgress < 170.0f) {
            // Pyramids (Tetrahedron)
            glPushMatrix();
                glColor3f(0.9f, 0.8f, 0.2f); // Sand color
                glTranslatef(0.0f, 0.6f, 0.0f); // On top of Earth
                glScalef(0.1f, 0.1f, 0.1f);
                glRotatef(25.0f, 1.0f, 0.0f, 0.0f); // Rotate to stand upright
                glutSolidTetrahedron();
            glPopMatrix();
        } else if (storyProgress >= 170.0f && storyProgress < 190.0f) {
            // Birth of Christ (Cross)
            glPushMatrix();
                glColor3f(1.0f, 0.8f, 0.0f); // Gold
                glTranslatef(0.0f, 0.7f, 0.0f); // Hovering slightly above Earth
                
                // Vertical bar
                glPushMatrix();
                    glScalef(0.05f, 0.3f, 0.05f);
                    glutSolidCube(1.0);
                glPopMatrix();
                
                // Horizontal bar
                glPushMatrix();
                    glTranslatef(0.0f, 0.05f, 0.0f); // Move up the vertical bar slightly
                    glScalef(0.2f, 0.05f, 0.05f);
                    glutSolidCube(1.0);
                glPopMatrix();
            glPopMatrix();
        } else if (storyProgress >= 210.0f && storyProgress < 230.0f) {
            // Industrial Revolution (Smog clouds)
            glPushMatrix();
                glColor3f(0.3f, 0.3f, 0.3f); // Dark grey
                for (int i = 0; i < 5; i++) {
                    glPushMatrix();
                        glRotatef(i * 72.0f, 0.0f, 1.0f, 0.0f);
                        glTranslatef(0.65f, 0.2f * (i % 2), 0.0f);
                        glutSolidSphere(0.1, 10, 10);
                    glPopMatrix();
                }
            glPopMatrix();
        } else if (storyProgress >= 230.0f) {
            // Modern Satellites
            glPushMatrix();
                glColor3f(0.8f, 0.8f, 0.8f); // Metallic
                glRotatef(year * 5.0f, 0.0f, 1.0f, 0.0f); // Fast orbit around Earth
                glRotatef(45.0f, 1.0f, 0.0f, 0.0f); // Tilted orbit
                glutWireTorus(0.02, 0.9, 10, 30); // Satellite network
            glPopMatrix();
        }

    glPopMatrix(); // End Earth system

    drawTextOverlay();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') { // Spacebar
        storyProgress += 1.0f;
        year += 5.0f;
        day += 20.0f;
        moonOrbit += 10.0f;
        
        if (storyProgress > 250.0f) {
            storyProgress = 250.0f;
        }
        
        glutPostRedisplay();
    } else if (key == 27) { // ESC
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("K-Pg Asteroid Impact Simulation");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}