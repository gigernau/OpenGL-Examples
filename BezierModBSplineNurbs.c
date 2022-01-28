#include <GL/glut.h>
#include <math.h>
#include<time.h>
#include <stdio.h>
#define MAX_CPTS  12  

GLfloat cpts[MAX_CPTS][3];
int ncpts = 0;
static int width = 500, height = 500;
int flag=1;

//disegna cerchio x e y punti di origine
void drawPunto(GLfloat x, GLfloat y,GLfloat z, GLfloat radius, int numVertex) {
	int i;
	GLfloat twoPi = 2.0f * M_PI;
	
	
	glColor3f( 1.0, 0.0, 0.0 );
	glBegin (GL_TRIANGLE_FAN);
		glVertex3f (x, y,z); // centro

		for (i = 0 ; i <= numVertex; i ++) {
			glVertex3f (
		        x + (radius * cos(i * twoPi / numVertex)),
			    y + (radius * sin(i * twoPi / numVertex)),
			    z
		
			);
			
		}
	glEnd ();
}
void drawDot(GLfloat x, GLfloat y, GLfloat z) {
    drawPunto(x,y,z,0.025,360);
    
}

GLvoid nurbsError(GLenum errorCode) 
{
	const GLubyte *estring;
	estring = gluErrorString(errorCode);
	fprintf (stderr, "Errore NURBS: %s\n", estring);
	exit (0);
}


void BSpline(){
	GLfloat cp[4][3] = { { -4.0, -4.0, 0.0}, 
						 { -2.0, 4.0, 0.0},
						 { 2.0, -4.0, 0.0}, 
						 { 4.0, 4.0, 0.0}
						};

	GLUnurbsObj *theNurb;
	GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};

	theNurb=gluNewNurbsRenderer();
	
	gluBeginCurve(theNurb); 
		gluNurbsCurve(theNurb, 8, knots, 3, &cp[0][0], 4, GL_MAP1_VERTEX_3);
	gluEndCurve(theNurb);
}

void Nurbs(){

		GLfloat cp[4][3] = { { -4.0, -4.0, 0.0}, 
						 { -2.0, 4.0, 0.0},
						 { 2.0, -4.0, 0.0}, 
						 { 4.0, 4.0, 0.0}
						};

		GLUnurbsObj *theNurb;
		GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
		GLfloat w[4] ={ 1.0, 5.0, 1.0, 1.0};
		GLfloat cpw[4][4];


			glPointSize(2);

		 for(int i =0; i<4; i++){
		 	drawDot(cp[i][0],cp[i][1],cp[i][2]);
		}


		//calcolo omogeneo
		for (int i=0; i<4; i++){
			for (int j=0; j<3; j++){
				cpw[i][j] = (cp[i][j])*w[i];
			}
			cpw[i][3] = w[i];
		}

		theNurb=gluNewNurbsRenderer(); /*puntatore a NURBS */
		gluNurbsCallback(theNurb, GLU_ERROR, (GLvoid (*))nurbsError);
		gluBeginCurve(theNurb); 
			gluNurbsCurve(theNurb, 8, knots, 4, &cpw[0][0], 4, GL_MAP1_VERTEX_4);
		gluEndCurve(theNurb); 
}




void drawScene( void )
{	
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	

	

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
	
	gluLookAt(0.0, 6.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
		
		glPushMatrix();	
				
					//BSpline();
					Nurbs();
				
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
	glutCreateWindow( "pavimento" );
	glutDisplayFunc(drawScene);
	glutMainLoop();
	return 0;
}