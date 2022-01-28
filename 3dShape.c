#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

void specialKeys(int key, int x, int y)
{
 int xRot=0,yRot=0;

 xRot = (key == GLUT_KEY_UP)? -1 : xRot;
 xRot = (key == GLUT_KEY_DOWN)? 1 : xRot;
 yRot = (key == GLUT_KEY_LEFT)? -1 : yRot;
 yRot = (key == GLUT_KEY_RIGHT)? 1 : yRot;

 glRotatef(xRot, 1.0f, 0.0f, 0.0f);
 glRotatef(yRot, 0.0f, 1.0f, 0.0f);

 glutPostRedisplay();
}


void drawPoligono(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int numVertex) {
   int i;
   
   GLfloat twoPi = 2.0f * M_PI;
   
      glColor3f( 0.0, 1.0, 0.0 );
      glBegin (GL_QUAD_STRIP);
      
      for (i = 0 ; i <= 8; i ++) {
         glVertex3f (
                 x + (radius * cos(i * twoPi / numVertex)),
                 y + (radius * sin(i * twoPi / numVertex)),
                 z+0.49
            );
         glVertex3f (
                 x + (radius * cos(i * twoPi / numVertex)),
                 y + (radius * sin(i * twoPi / numVertex)),
                 z-0.5
            );
      }

      glEnd();

         glColor3f( 1.0, 0.0, 0.0 );
      glBegin (GL_TRIANGLE_FAN);
         glVertex3f (x, y, z); // centro
         glColor3f( 1.0, 0.0, 0.0 );
         for (i = 0 ; i <= numVertex; i ++) {
            glVertex3f (
                 x + (radius * cos(i * twoPi / numVertex)),
                y + (radius * sin(i * twoPi / numVertex)),
                z
            );
         }
      glEnd ();

      glColor3f( 1.0, 2.0, 0.0 );
      glBegin (GL_TRIANGLE_FAN);
         //glVertex3f (x, y, z); // centro
         z -= 0.5;
         for (i = 0 ; i <= numVertex; i ++) {
            glVertex3f (
                 x + (radius * cos(i * twoPi / numVertex)),
                 y + (radius * sin(i * twoPi / numVertex)),
                 z
            );
         }
      glEnd ();



}

void drawCone(float x, float y, float z, float radius)
{
 glBegin(GL_TRIANGLE_FAN);
 
 glVertex3f(x, y, z);
 glColor3f( 1.0, 0.0, 0.0 );
 float angle;
 for(angle = 0.0f; angle < (2.0f*M_PI); angle += (M_PI/9.0f))
 {    
    
    x = radius*sin(angle);
    y = radius*cos(angle);
    glVertex2f(x, y);
    
 }
 glEnd();
}

void renderScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

    glColor3f( 0.0, 1.0, 0.0 );
   //drawCone(0,0,0.75,0.5);
   drawPoligono(0.0,0,0.5,0.5,8);

   glutSwapBuffers();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

 glutInitWindowPosition( 300, 100 );
 glutInitWindowSize( 500, 500);

 glutCreateWindow("Triangle Example");

 glutSpecialFunc(specialKeys);
 glutDisplayFunc(renderScene);

 glutMainLoop();
 return 0;
}