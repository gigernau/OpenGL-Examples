#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

int countOre = 0;
int countMin = 0;

void SpecialInput(int key, int x, int y)
 {
    switch(key)
        {
        case GLUT_KEY_UP:
        	//glRotatef( -5.0, 0.0, 1, 0 );

 
        break;
        case GLUT_KEY_DOWN:
        	//glScalef( 0.5, 0.5, 0.5 );
         	
        break;
        case GLUT_KEY_LEFT:
            //glRotatef( 5.0, 0.0, 0.0, 1.0 );
         	
        break;
        case GLUT_KEY_RIGHT:
            //glRotatef( -5.0, 0.0, 0.0, 1.0 );

        break;
    }

    glutPostRedisplay();
}

void drawPoint(){
	glColor3f( 1.0, 0.0, 0.0 );
	
	glRasterPos2f(0.2,0.35);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'1');
	glRasterPos2f(0.35,0.22);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'2');
	glRasterPos2f(0.35,-0.22);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'4');
	glRasterPos2f(0.2,-0.35);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'5');
	glRasterPos2f(-0.2,-0.35);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'7');
	glRasterPos2f(-0.35,-0.22);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'8');
	glRasterPos2f(-0.35,0.22);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'1');
	glRasterPos2f(-0.32,0.22);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'0');
	glRasterPos2f(-0.2,0.35);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'1');
	glRasterPos2f(-0.17,0.35);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'1');


	glPointSize(5);
	glBegin (GL_POINTS);
		glVertex3f(0.0,0.45,-0.3);
		glVertex3f(0.0,-0.45,-0.3);
		glVertex3f(0.45,0.0,-0.3);
		glVertex3f(-0.45,0.0,-0.3);
	glEnd ();

}


//disegna cerchio x e y punti di origine
void drawclock(GLfloat x, GLfloat y, GLfloat radius, int numVertex) {
	int i;
	GLfloat twoPi = 2.0f * M_PI;
	
	
	glColor3f( 1.0, 1.0, 0.0 );
	glBegin (GL_TRIANGLE_FAN);
		glVertex2f (x, y); // centro

		for (i = 0 ; i <= numVertex; i ++) {
			glVertex2f (
		        x + (radius * cos(i * twoPi / numVertex)),
			    y + (radius * sin(i * twoPi / numVertex))
		
			);
			
		}
	glEnd ();
}




//disegna lancette ora
void drawOra(){
	int i;
	int count=0;
	
	glColor3f( 0.0, 0.0, 0.0 );
	glLineWidth(5);
	glBegin (GL_LINES);
		glVertex3f(0.0,0.0,-0.3);
		glVertex3f(0.0,0.30,-0.3);
	glEnd ();
}

//disegna lancette min
void drawMin(){
	int i;
	int count=0;
	
	
	glColor3f( 0.0, 0.0, 0.0 );
	glLineWidth(3.5);
	glBegin (GL_LINES);
		glVertex3f(0.0,0.0,-0.3);
		glVertex3f(0.0,0.40,-0.3);

	glEnd ();
}




 
void drawScene( void )
{	
	


	 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glEnable(GL_DEPTH_TEST);
	 


	//Attivazione stak matrici modellazione
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     drawPoint();
 	drawclock( 0.0,0.0,0.5,360);

 	glPushMatrix();
		 glRotatef(-(countMin*360/60),0.0,0.0,1.0);
	     drawMin();
	     countMin++;
    glPopMatrix();


     glPushMatrix();
		 glRotatef(-(countOre*360/12),0.0,0.0,1.0);
		 drawOra();
		 if(countMin== 60){
		 	countMin=0;
		 	countOre++;
		 }
		 
	 glPopMatrix();

	 glFlush();
	 glDisable(GL_DEPTH_TEST);
 
}

 

int main( int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition( 300, 100 );
	glutInitWindowSize( 500, 500);
	glutCreateWindow( "orologio" );
	glutDisplayFunc(drawScene );
	glutSpecialFunc(SpecialInput); 
	glutMainLoop();
	return 0;
}
