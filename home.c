#include <stdlib.h>
#include <GL/glut.h>


float _angle = 0.0;
GLuint _textureBrick, _textureDoor, _textureGrass, _textureRoof, _textureWindow, _textureSky;

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void renderScene(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // Front side
    glPushMatrix();
    
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-2,0,1);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(2,0,1);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(2,-1.5,1);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,1);
        glEnd();

        glBegin(GL_QUADS);  // Roof
            glTexCoord3f(0.0,2.0,0); glVertex3f(-2.2,0.5,0);
            glTexCoord3f(4.0,2.0,0);glVertex3f(2.2,0.5,0);
            glTexCoord3f(4.0,0.0,1.25); glVertex3f(2.2,-0.1,1.25);
            glTexCoord3f(0.0,0.0,1.25); glVertex3f(-2.2,-0.1,1.25);
        glEnd();

    glPopMatrix();

    // Back side
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,-1);  glVertex3f(-2,0,-1);
            glTexCoord3f(4.0,2.0,-1);  glVertex3f(2,0,-1);
            glTexCoord3f(4.0,0.0,-1);  glVertex3f(2,-1.5,-1);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-2,-1.5,-1);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureRoof);
       
        glBegin(GL_QUADS);  // Roof
            glTexCoord3f(0.0,2.0,0); glVertex3f(-2.2,0.5,0);
            glTexCoord3f(4.0,2.0,0);glVertex3f(2.2,0.5,0);
            glTexCoord3f(4.0,0.0,-1.25); glVertex3f(2.2,-0.1,-1.25);
            glTexCoord3f(0.0,0.0,-1.25); glVertex3f(-2.2,-0.1,-1.25);
        glEnd();

    glPopMatrix();

    // Right side
    glPushMatrix();
        
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,1); glVertex3f(2,0,1);
            glTexCoord3f(2.0,2.0,-1); glVertex3f(2,0,-1);
            glTexCoord3f(2.0,0.0,-1); glVertex3f(2,-1.5,-1);
            glTexCoord3f(0.0,0.0,1); glVertex3f(2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  // Wall Upper
            glTexCoord3f(0.0,1.0,0); glVertex3f(2,0.5,0);
            glTexCoord3f(1.0,0.0,1); glVertex3f(2,0,1);
            glTexCoord3f(-1.0,0.0,-1); glVertex3f(2,0,-1);
        glEnd();
    glPopMatrix();

    // Left side
    glPushMatrix();
       
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,1);    glVertex3f(-2,0,1);
            glTexCoord3f(2.0,2.0,-1);    glVertex3f(-2,0,-1);
            glTexCoord3f(2.0,0.0,-1);    glVertex3f(-2,-1.5,-1);
            glTexCoord3f(0.0,0.0,1);    glVertex3f(-2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  // Wall Upper
            glTexCoord3f(0.0,1.0,0);    glVertex3f(-2,0.5,0);
            glTexCoord3f(1.0,0.0,1);    glVertex3f(-2,0,1);
            glTexCoord3f(-1.0,0.0,-1);    glVertex3f(-2,0,-1);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void mySpecialFunc(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_RIGHT:
        _angle += 1;
        if (_angle > 360) _angle = 0.0;
        break;
    case GLUT_KEY_LEFT:
        _angle -= 1;
        if (_angle > 360) _angle = 0.0;
        break;
    }
    glutPostRedisplay();
}



void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(600,600);
    glutCreateWindow("Textured House by Rakib");
    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(resize);
    glutSpecialFunc(mySpecialFunc);
    glutDisplayFunc(renderScene);
    Initialize();

    glutMainLoop();

    return 0;
}
