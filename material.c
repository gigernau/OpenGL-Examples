	#include <GL/glut.h>
	#include <math.h>
	#include<time.h>
	#include <stdio.h>
	#define MAX_CPTS 12

	static int width = 500, height = 500;
	int flag=1;
	unsigned char pixel[4];
	int m = 30;
    int n = 30;
	int u1 = 0;
	int u2 = 1;
	int v1 = 0;
	int v2 = 1;
	int i1 = 0;
	int i2 = 30;
	int j12 = 0;
	int j22 = 30;
	GLUnurbsObj *theNurb;
	GLUquadricObj *qobj;

	typedef struct 
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
	}Point;

	float anglexz=0.0;
	float angley=0.0;
	
	float xass=0.0;
	float yass=0.0;

	GLvoid nurbsError(GLenum errorCode) 
	{
		const GLubyte *estring;
		estring = gluErrorString(errorCode);
		fprintf (stderr, "Errore NURBS: %s\n", estring);
		exit (0);
	}

	GLfloat light_B[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat diffuseRED[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat diffuseBLUE[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat diffuseYELL[] = { 1.0, 1.0, 0.0, 1.0 };
	
	GLfloat NOemm[] = { .0, .0, 0, 1.0 };
	GLfloat emm[] = { 0.8, 0.8, 0, 1.0 };
	float shine[] = {128.0f};
	float noShine[] = {0.0f};

void sfera(){
	

	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseRED);
	glMaterialfv(GL_FRONT,GL_SPECULAR,light_B);
	glMaterialfv(GL_FRONT,GL_SHININESS,shine);
	

	glutSolidSphere(0.75,150, 100);//palla piena
}


void cono(){

	
	glTranslatef(2.5,0,0);

	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseBLUE);
	glMaterialfv(GL_FRONT,GL_SPECULAR,diffuseBLUE);
	glMaterialfv(GL_FRONT,GL_SHININESS,noShine);
	glutSolidCone(0.65, 0.9, 150,100);//cono pieno
}

void toro(){

	

	glTranslatef(-2.5,0,0);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseYELL);
	glMaterialfv(GL_FRONT,GL_EMISSION,emm);
	glutSolidTorus(0.30, 0.60,100,150);// toro pieno
	glMaterialfv(GL_FRONT,GL_EMISSION,NOemm);
	
}




void drawScene( void )
	{
	GLfloat light_G[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat light_N[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_R[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_B[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_position1[] = { 2.0, 1.0, 1.0, 0.0 };
	GLfloat light_position2[] = { 1.0, 1.0, 1.0, 0.0 };

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	 //glOrtho(-1,1,-1,1,1,5);
	//glFrustum(-1,1,-1,1,1,5);
	gluPerspective(90,1,1,22);

	//Attivazione stak matrici modellazione
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	 //Sposto il sys di rifermento a -3 dall'osservatore
	glTranslatef(0.0,1.5,-4.0);
	glRotatef(-45,1,0,0);

	float xRef,yRef,zRef;
	xRef=0.0;
	yRef=0.0;
	zRef=0.0;

	

	gluLookAt(sin(anglexz)*3, sin(angley)*3, cos(anglexz)*3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_B);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_B);
	glPushMatrix();
		//glRotatef(angley*20, 0.0, 1.0, 0.0);
		//glLightfv(GL_LIGHT0, GL_POSITION, light_position );
		
		
		glPushMatrix();
			toro();
			
		glPopMatrix();

		glPushMatrix();
			glLightfv(GL_LIGHT1, GL_AMBIENT, light_G);
			glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
			cono();
			
		glPopMatrix();

		glPushMatrix();
			glLightfv(GL_LIGHT2, GL_AMBIENT, light_G);
			glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
			sfera();
			
		glPopMatrix();

		

	


		
	glPopMatrix();

	glFlush();

	glutSwapBuffers();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT0);
	glFinish();

}


void mySpecialInput(int key, int x, int y)
{
 switch(key)
        {
        case GLUT_KEY_UP:
            angley -= 0.1;
        break;
        case GLUT_KEY_DOWN:
         	angley += 0.1;
        break;
        case GLUT_KEY_LEFT:
            anglexz -= 0.1;
        break;
        case GLUT_KEY_RIGHT:
            anglexz += 0.1;
        break;
    }

    glutPostRedisplay();
}

	int main( int argc, char** argv){

	 glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowPosition( 100, 0 );
	glutInitWindowSize( 700, 650);
	//glutInitWindowSize(width, height);
	glutCreateWindow( "pavimento" );
	glutDisplayFunc(drawScene);
	glutSpecialFunc(mySpecialInput);
	//glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
	}