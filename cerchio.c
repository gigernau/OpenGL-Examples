#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>


void renderFunction()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}


void drawTriangle( float red, float green,float blue )
{
	glColor3f( red, green, blue );
	glPointSize( 3.0 );
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	//glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 1.0, 0.0, 1.0 );
	glBegin( GL_TRIANGLE_FAN );
	glVertex2f(0.0, 0.0); 
	glVertex2f(0.2, 0.2); 
	glVertex2f(1, 0.0);
	glVertex2f(0.0, 0.0); 
	glVertex2f(1, 0.0);
	glVertex2f(0.2, -0.2);
	glEnd();
}



//disegna cerchio x e y punti di origine
void drawcerchio (GLfloat x, GLfloat y, GLfloat radius, int numVertex) {
	int i;
	
	GLfloat twoPi = 2.0f * M_PI;
	
	glColor3f( 1.0, 0.0, 1.0 );
	glBegin (GL_TRIANGLE_FAN);
		glVertex2f (x, y); // centro del cerchio
		glColor3f( 0.0, 0.0, 1.0 );
		for (i = 0 ; i <= numVertex; i ++) {
			glVertex2f (
		        x + (radius * cos(i * twoPi / numVertex)),
			    y + (radius * sin(i * twoPi / numVertex))
			);
		}
	glEnd ();
}

//disegna cerchio x e y punti di origine
void drawcerchioCol(float red, float green,float blue, GLfloat radius, int numVertex) {
	int i;
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat twoPi = 2.0f * M_PI;
	
	glColor3f( red,green,blue);
	glBegin (GL_TRIANGLE_FAN);
		glVertex2f (x, y); // centro del cerchio
		for (i = 0 ; i <= numVertex; i ++) {
			glVertex2f (
		        x + (radius * cos(i * twoPi / numVertex)),
			    y + (radius * sin(i * twoPi / numVertex))
			);
		}
	glEnd ();
}

 
void createRing(double radius,double radius2, int numSegments, double x, double y)
{
	double mAngle = 0.0;
	double mAngle2 = 0.0;
	glBegin(GL_QUAD_STRIP);
	for(int i = 0; i < numSegments; i++)
	{
		mAngle = i * (2 * 3.14/numSegments);
		mAngle2 = i * (2 * 3.14/numSegments);
		glVertex2d(x + radius * cosf(mAngle), 
					y + radius * sinf(mAngle));
		glVertex2d(x + (radius + radius2 * cosf(mAngle2)) * cosf(mAngle2),
				   y + (radius + radius2 * sinf(mAngle2)) * sinf(mAngle2));
	}	
		
	glEnd();
}


void torus(int numc, int numt)
{
   int i, j, k;
   double s, t, x, y, twopi;

   twopi = 2 * M_PI;

   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      
      for (j = 0; j <= numt; j++) {
      	glColor3f( 0.0, 1.0, 0.0 );
         for (k = 1; k >= 0; k--) {
         	
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (0.5+.2*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (0.5+.2*cos(s*twopi/numc))*sin(t*twopi/numt);
            
            glVertex2f(x, y);
            glColor3f( 0.0, 0.0, 1.0 );
         }
      }
      glEnd();
   }
}


void SpecialInput(int key, int x, int y)
 {
    switch(key)
        {
        case GLUT_KEY_UP:
            glRotatef( 5.0, 0.0, 0.0, 1.0 );
        break;
        case GLUT_KEY_DOWN:
         
        break;
        case GLUT_KEY_LEFT:
            glScalef( 0.5, 0.5, 0.5 );
        break;
        case GLUT_KEY_RIGHT:
            glScalef( -0.5, -0.5, -0.5 );
        break;
    }

    glutPostRedisplay();
}

void drawSceneStella( void )
{
	//glScalef( 0.5, 0.5, 0.5 );
	 glClear( GL_COLOR_BUFFER_BIT );
	  drawTriangle( 1.0, 1.0, 1.0 );
	 glRotatef( 72.0, 0.0, 0.0, 1.0 );
	  drawTriangle( 1.0, 0.0, 1.0 );
	 glRotatef( 72.0, 0.0, 0.0, 1.0 );
	 drawTriangle( 1.0, 1.0, 1.0 );
	  glRotatef( 72.0, 0.0, 0.0, 1.0 );
	 drawTriangle( 1.0, 1.0, 1.0 );
	  glRotatef( 72.0, 0.0, 0.0, 1.0 );
	 drawTriangle( 1.0, 1.0, 1.0 );
	  glRotatef( 72.0, 0.0, 0.0, 1.0 );

	 glutSpecialFunc(SpecialInput);

	 glFlush();
 
}

 
void drawSceneCerchio( void )
{	
	//glScalef( 0.5, 0.5, 0.5 );
	 glClear( GL_COLOR_BUFFER_BIT );
	 //torus (360,360);
	 //createRing(0.5,0.8,360,0.0,0.0);
	 //glScalef( 0.5, 0.5, 0.5 );
	 drawcerchio( 0.0,0.0,0.5,360);
	 

	 glutSpecialFunc(SpecialInput);

	 glFlush();
 
}

 

int main( int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB);
	glutInitWindowPosition( 300, 100 );
	glutInitWindowSize( 300, 300);
	glutCreateWindow( "OpenGL - Demo" );
	glutDisplayFunc(drawSceneCerchio );
	glutMainLoop();
	return 0;
}
