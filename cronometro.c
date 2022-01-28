#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

int countSec= 0;
int countMin = 0;
int start = 0;

unsigned char pixel[4];


void drawPoint(){
	glColor3f( 1.0, 0.0, 0.0 );
	

	glRasterPos2f(0.2,0.35);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'5');

	glRasterPos2f(0.35,0.22);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'1');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'0');

	glRasterPos2f(0.35,-0.22);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'2');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'0');

	glRasterPos2f(0.2,-0.35);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'2');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'5');

	glRasterPos2f(-0.2,-0.35);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'3');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'5');

	glRasterPos2f(-0.35,-0.22);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'4');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'0');

	glRasterPos2f(-0.35,0.22);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'5');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'0');

	glRasterPos2f(-0.2,0.35);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'5');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'5');

	glRasterPos2f(-0.58,-0.9);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'S');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'t');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'a');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'r');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'t');

		glRasterPos2f(-0.06,-0.9);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'S');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'t');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'o');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'p');

		glRasterPos2f(0.43,-0.9);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'R');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'e');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'s');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'e');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'t');




	glPointSize(5);
	glBegin (GL_POINTS);
		glVertex3f(0.0,0.45,-0.1);
		glVertex3f(0.0,-0.45,-0.1);
		glVertex3f(0.45,0.0,-0.1);
		glVertex3f(-0.45,0.0,-0.1);
	glEnd ();

}


//disegna cerchio x e y punti di origine
void drawclock(GLfloat x, GLfloat y,GLfloat z, GLfloat radius, int numVertex) {
	int i;
	GLfloat twoPi = 2.0f * M_PI;
	drawPoint();
	
	glColor3f( 0.0, 0.0, 0.75 );
	glBegin (GL_TRIANGLE_FAN);
		glVertex3f (x, y, z); // centro

		for (i = 0 ; i <= numVertex; i ++) {
			glVertex3f (
		        x + (radius * cos(i * twoPi / numVertex)),
			    y + (radius * sin(i * twoPi / numVertex)),
				z
			);
			
		}
	glEnd ();
}

//disegna cerchio x e y punti di origine
void drawButton(GLfloat x, GLfloat y, GLfloat radius, int numVertex, float r, float g,float b) {
	int i;
	GLfloat twoPi = 2.0f * M_PI;
	drawPoint();
	


	glColor3f( r, g, b );
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
void drawSec(){
	int i;
	int count=0;
	
	glColor3f( 1.0, 0.0, 0.0 );
	glLineWidth(2);
	glBegin (GL_LINES);
		glVertex3f(0.0,0.0,-0.1);
		glVertex3f(0.0,0.4,-0.1);
	glEnd ();
}

//disegna lancette min
void drawMin(){
	int i;
	int count=0;
	
	
	glColor3f( 1.0, 0.0, 0.0 );
	glLineWidth(3.5);
	glBegin (GL_LINES);
		glVertex3f(0.0,0.0,-0.1);
		glVertex3f(0.0,0.40,-0.1);

	glEnd ();
}


void drawScene( void )
{	
	


	 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glEnable(GL_DEPTH_TEST);
	 

	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();

		  glOrtho(-1,1,-1,1,1,5);
		 //glFrustum(-1,1,-1,1,1,5);
		 //gluPerspective(45,1,1,5);
		 

     //glPopMatrix();

	//Attivazione stak matrici modellazione
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     //Sposto il sys di rifermento a -3 dall'osservatore
	glTranslatef(0.0,0.0,-3.0);



 	drawclock( 0.0,0.0,-0.2,0.5,360);
 	
 	//Pulsanti
 	drawButton(0.0,-0.7,0.1,360,1,0,0);
 	drawButton(0.5,-0.7,0.1,360,1,1,1);
 	drawButton(-0.5,-0.7,0.1,360,0,1,0);

 	glPushMatrix();
		 glRotatef(-(countSec*360/60),0.0,0.0,1.0);
	     drawSec();
	     countSec++;
    glPopMatrix();


     glPushMatrix();
		 glRotatef(-(countMin*360/60),0.0,0.0,1.0);
		 drawMin();
		 if(countSec== 60){
		 	countSec=0;
		 	countMin++;
		 }
		 
	 glPopMatrix();


	 glRotatef( -5.0, 0.0, 1.0, 1.0 );

	 glFlush();
	 glDisable(GL_DEPTH_TEST);


	glFinish(); 

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	unsigned char data[4];
	glReadPixels(500, 500,1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);
 	printf("%c",data[1]);
}


void timer(int extra)
{	
	if(start == 1){
		glutPostRedisplay();
    	glutTimerFunc(1000, timer, 0);
	}else {}

}


void motion(int x, int y)
{
	int i;
	y = glutGet( GLUT_WINDOW_HEIGHT ) - y;

	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
}

void mouse(int button,int state,int x,int y)
{
	int i;
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
		if(state==GLUT_DOWN)

			if(pixel[0]==0.0 && pixel[1]==255 && pixel[2]==0.0){
				//start
				start = 1;
				timer(1);
			}
			if(pixel[0]==255 && pixel[1]==0.0 && pixel[2]==0.0){
				//stop
				start = 0;
				timer(1);
			}
			if(pixel[0]==255 && pixel[1]==255 && pixel[2]==255){
				//reset
				countSec = 0;
				countMin = 0;
				start = 0;
				timer(1);
				glutPostRedisplay();
			}
			break;


			case GLUT_MIDDLE_BUTTON:
			if(state==GLUT_DOWN)
			{
				//glutIdleFunc(NULL);
			}
			break;
			case GLUT_RIGHT_BUTTON:
			if(state==GLUT_DOWN)
				//glutIdleFunc(spinDisplayReverse);
				break;
			default:
			break;
		}
	}

void SpecialInput(int key, int x, int y)
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
int main( int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition( 300, 100 );
	glutInitWindowSize( 500, 500);
	glutCreateWindow( "cronometro" );
	glutDisplayFunc(drawScene );
	glutSpecialFunc(SpecialInput); 
	//glutMouseFunc(mouse);
	// mouse event handlers
    glutPassiveMotionFunc(motion);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}
