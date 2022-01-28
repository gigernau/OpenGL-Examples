#include <GL/glut.h>
#include <math.h>

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




void trimmingNurbs(){


	GLfloat cp[4][4][3] = {
								{{-3, -3, -3}, {-3, -1, -3},{-3, 1, -3}, {-3, 3, -3}},
								{{-1, -3, -3}, {-1, -1, 3}, {-1, 1, 3}, {-1, 3, -3}},
								{{1, -3, -3}, {1, -1, 3}, {1, 1, 3}, {1, 3, -3}},
								{{3, -3, -3}, {3, -1, -3}, {3, 1, -3}, {3, 3, -3}}
						  };
	

	GLUnurbsObj *theNurb;
	GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
	GLfloat w[4][4]={ {1, .5, .5, 1},{1, .5, .5, 1},{1, .5, .5, 1},{1, .5, .5, 1}};
	GLfloat cpw[4][4][4];


	//calcolo omogeneo
		for (int i=0; i<4; i++){
			for (int j=0; j<4; j++){
				for (int k=0; k<3; k++){
					cpw[i][j][k] = (cp[i][j][k])*(w[i][j]);
				}

				cpw[i][j][3] = w[i][j];
			}
			
		} 

	GLfloat E[5][2]={{0,0},{1,0},{1,1},{0,1},{0,0}};
	GLfloat P[5][2]={{0.3,0.3},{0.3,0.7},{0.7,0.7},{0.7,0.3},{0.3,0.3}};


	glEnable(GL_AUTO_NORMAL);
	theNurb=gluNewNurbsRenderer(); /*puntatore all’oggetto NURBS */

	gluBeginSurface(theNurb);
		//property
		gluNurbsProperty(theNurb, GLU_U_STEP, 30);
		gluNurbsProperty(theNurb, GLU_V_STEP, 30);
		gluNurbsProperty(theNurb, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
		gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);

		//gluNurbsSurface(theNurb,10, knots, 4, knots,2 * 3, 3, &cp [0][0][0],3, 2, GL_MAP2_VERTEX_3);
		gluNurbsSurface(theNurb,8, knots, 8, knots,4 * 4, 4, &cpw[0][0][0],4, 4, GL_MAP2_VERTEX_4);

		gluBeginTrim(theNurb); //confine esterno
			gluPwlCurve(theNurb,5,&E[0][0],2,GLU_MAP1_TRIM_2);
		gluEndTrim(theNurb);
		
		//confine interno 
		gluBeginTrim(theNurb); 
			gluPwlCurve(theNurb,5,&P[0][0],2,GLU_MAP1_TRIM_2);
		gluEndTrim(theNurb);
	gluEndSurface(theNurb);

	


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
        if (anglexz > 360) angley = 0.0;
        break;
    case GLUT_KEY_UP:
        angley -= .1;
        if (angley > 360) angley = 0.0;
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
	gluLookAt( sin(anglexz)*3, sin(angley)*3, cos(anglexz)*3, xRef, yRef, zRef,0.0, 1.0, 0.0 );

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