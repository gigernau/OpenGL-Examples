#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define MAX_CPTS  12  

GLfloat cpts[MAX_CPTS][3];
int ncpts = 0;
static int width = 500, height = 500;
int flag=1;

GLvoid nurbsError(GLenum errorCode) 
{
	const GLubyte *estring;
	estring = gluErrorString(errorCode);
	fprintf (stderr, "Errore NURBS: %s\n", estring);
	exit (0);
}

void supNurbs(){

 GLUquadricObj *qobj;
 qobj = gluNewQuadric(); //Creazione
 gluQuadricCallback(qobj, GLU_ERROR, (GLvoid (*))nurbsError); //Gestione errori
 gluQuadricDrawStyle(qobj, GLU_FILL);
 gluQuadricOrientation(qobj, GLU_OUTSIDE);
 gluQuadricNormals(qobj, GLU_SMOOTH);
 //gluSphere(qobj, 0.75, 15, 10); //sfera
     //(GLUquadricObj *qobj,GLdouble radius,GLint slices, GLint stacks);
 //gluCylinder(qobj, 0.75,0.35,0.70,15,10); //cilindro
     //(GLUquadricObj *qobj,GLdouble baseRadius,GLdouble topRadius,GLdouble height,GLint slices, GLint stacks);
 //gluDisk (qobj,0.75,0.90,15,10);//disco
     //(GLUquadricObj *qobj, GLdouble innerRadius,GLdouble outerRadius, GLint slices, GLint rings);
    //gluPartialDisk (qobj,0.75,0.90,15,10,20,190);//parte disco
        //(GLUquadricObj *qobj, GLdouble innerRadius,GLdouble outerRadius, GLint slices, GLint rings,GLdouble startAngle, GLdouble sweepAngle);
    //glutWireSphere(0.75,15, 10);//palla vuoto
        //(GLdouble radius,GLint slices, GLint stacks);
 //glutSolidSphere(0.75,15, 10);//palla piena
     //(GLdouble radius,GLint slices, GLint stacks);
 //glutWireCube(0.75);//cubo vuoto
    //(GLdouble size);
 //glutSolidCube(0.45);//cubo pieno
       //(GLdouble size);
 //glutWireTorus(0.75, 0.90,10,15); //toro vuoto
    //(GLdouble innerRadius, GLdouble outerRadius,GLint nsides, GLint rings);
 glutSolidTorus(0.30, 0.60,10,15);// toro pieno
    //(GLdouble innerRadius, GLdouble outerRadius,GLint nsides, GLint rings);
 //glutWireCone(0.75, 1.0,15,10);//cono vuoto
    //(GLdouble radius, GLdouble height,GLint slices,GLint stacks);
 //glutSolidCone(0.65, 0.9,15,10);//cono pieno
   //(GLdouble radius, GLdouble height,GLint slices,GLint stacks);
}







float anglexz = 0.0;
float angley  = 0.0;

void mySpecialInput(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_RIGHT:
        anglexz += .1;
        if (anglexz > 360) anglexz = 0.0;
        break;
    case GLUT_KEY_LEFT:
        anglexz -= .1;
        if (anglexz > 360) anglexz = 0.0;
        break;

    case GLUT_KEY_DOWN:
        angley += .1;
        if (angley > 360){
        	angley = 0.0;
        	anglexz = 0.0;
        } 

        break;
    case GLUT_KEY_UP:
        angley -= .1;
        if (angley > 1) angley = 0.0;
        break;
    }

    glutPostRedisplay();
}

void drawScene( void )
{	
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	

	//Luce attivata
	glEnable(GL_LIGHTING);
	// luce default luce all'infinito (raggi paralleli) e NO COLOR
	glEnable(GL_LIGHT0);

	//Shade flat --> colore uniforme ogni faccia
	//glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-1,1,-1,1,1,5);
	//glFrustum(-1,1,-1,1,1,5);
	gluPerspective(90,1,1,22);


	//Attivazione stak matrici modellazione
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	float xRef,yRef,zRef;
	xRef=0.0;
	yRef=0.0;
	zRef=0.0;
	
	//gluLookAt(0.0, 6.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt( sin(anglexz)*3, sin(angley)*3, cos(anglexz)*3, xRef, yRef, zRef,.0, 1.0, .0 );

	glPushMatrix();
		
		glPushMatrix();	
				
					supNurbs();
				
				glutSwapBuffers();
		glPopMatrix();	
	
	glPopMatrix();

	glFlush();
	glDisable(GL_DEPTH_TEST);
	glFinish(); 

}


int main( int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowPosition( 300, 100 );
	glutInitWindowSize( 500, 500);
	glutInitWindowSize(width, height);
	glutCreateWindow( "Superfici BSpline e Nurbs" );
	glutDisplayFunc(drawScene);
	glutSpecialFunc(mySpecialInput); 
	glutMainLoop();
	return 0;
}