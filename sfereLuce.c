#include <GL/glut.h>
	#include <math.h>
	#include<time.h>
	#include <stdio.h>
	#define MAX_CPTS 12

	static int width = 500, height = 500;
	int flag=1;
	GLfloat angle=0.0;
	GLfloat cp[4][4][3] = {
			{{-3.0, -3.0, -3.0}, {-3.0, -1.0, -3.0},{-3.0, 1.0, -3.0}, {-3.0, 3.0, -3.0}},
			{{-1.0, -3.0, -3.0}, {-1.0, -1.0, 3.0}, {-1.0, 1.0, 3.0}, {-1, 3.0, -3.0}},
			{{1.0, -3.0, -3.0}, {1.0, -1.0, 3.0}, {1.0, 1.0, 3.0}, {1.0, 3.0, -3.0}},
			{{3.0, -3.0, -3.0}, {3.0, -1.0, -3.0}, {3.0, 1.0, -3.0}, {3.0, 3.0, -3.0}}};
	GLfloat knots[8]={0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0};
	GLfloat w[4][4]={{1, 0.5, 0.5, 1},{1, 0.5, 0.5, 1},
					 {1, 0.5, 0.5, 1},{1, 0.5, 0.5, 1}};
	GLfloat cpw[4][4][4];
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

	float anglex=0.0;
	float angley=0.0;
	float anglez=0.0;
	float xass=0.0;
	float yass=0.0;

	GLvoid nurbsError(GLenum errorCode) 
	{
		const GLubyte *estring;
		estring = gluErrorString(errorCode);
		fprintf (stderr, "Errore NURBS: %s\n", estring);
		exit (0);
	}
void SpecialInput(int key, int x, int y)
	{
	switch(key)
		{
		case GLUT_KEY_UP:
			yass=yass+10.0;
		break;
		case GLUT_KEY_DOWN:	
			yass=yass-10.0;
		break;
		case GLUT_KEY_LEFT:
			xass=xass-10.0;
		break;
		case GLUT_KEY_RIGHT:
			xass=xass+10.0;
		break;
	}
	glutPostRedisplay();
} 

void mySpecialInput(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_RIGHT:
        anglex += .1;
        if (anglex > 360) anglex = 0.0;
        anglez=anglex;
        break;
    case GLUT_KEY_LEFT:
        anglex -= .1;
        if (anglex > 360) anglex = 0.0;
        anglez=anglex;
        break;
    case GLUT_KEY_DOWN:
        angley += .1;
        if (angley > 360) angley = 0.0;
        anglez=angley;
        break;
    case GLUT_KEY_UP:
        angley -= .1;
        if (angley > 360) angley = 0.0;
        anglez=angley;
        break;
    }

    glutPostRedisplay();
}


void supNURBS(){	
 	theNurb=gluNewNurbsRenderer();
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb,8, knots, 8, knots, 4 * 3, 3, &cp[0][0][0],4, 4, GL_MAP2_VERTEX_3);
    gluNurbsProperty(theNurb, GLU_U_STEP, 30);
	gluNurbsProperty(theNurb, GLU_V_STEP, 30);
	gluNurbsProperty(theNurb, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
    gluEndSurface(theNurb);
    glEnable(GL_AUTO_NORMAL);			
}
void supNURBS2()
{
		for (int i=0; i<4; i++){
			for (int j=0; j<4; j++){
				for(int k=0;k<3;k++){
				cpw[i][j][k] = (cp[i][j][k])*w[i][j];
				}
				cpw[i][j][3] = w[i][j];
			}
			
		}
	theNurb=gluNewNurbsRenderer();
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb,8, knots, 8, knots, 4 * 4, 4, &cpw[0][0][0],4, 4, GL_MAP2_VERTEX_4);
     gluNurbsProperty(theNurb, GLU_U_STEP,30);
	gluNurbsProperty(theNurb, GLU_V_STEP, 30);
	gluNurbsProperty(theNurb, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
    gluEndSurface(theNurb);
    
    //glEnable(GL_MAP2_VERTEX_4);
    glEnable(GL_AUTO_NORMAL);		
    //glMapGrid2f(n, u1, u2,m,v1,v2); /inizializza i valori equispaziati/
	//glEvalMesh2(GL_FILL, i1, i2,j1,j2); /disegna la curva/
}

void supNURBSes5(){

	GLfloat E[5][2]={{0,0},{1,0},{1,1},{0,1},{0,0}};
	GLfloat P[7][2]={{0.3,0.5},{0.3,0.8},
					{0.6,0.8},{0.6,0.5},{0.6, 0.2},
					{0.3, 0.2},{0.3, 0.5}};


		for (int i=0; i<4; i++){
			for (int j=0; j<4; j++){
				for(int k=0;k<3;k++){
				cpw[i][j][k] = (cp[i][j][k])*w[i][j];
				}
				cpw[i][j][3] = w[i][j];
			}
			
		}
	theNurb=gluNewNurbsRenderer();
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb,8, knots, 8, knots, 4 * 4, 4, &cpw[0][0][0],4, 4, GL_MAP2_VERTEX_4);
    gluBeginTrim(theNurb);
    gluPwlCurve(theNurb,5,&E[0][0],2,GLU_MAP1_TRIM_2);
    gluEndTrim(theNurb);
    gluBeginTrim(theNurb); //confine interno
	gluPwlCurve(theNurb,5,&P[0][0],2,GLU_MAP1_TRIM_2);
	gluEndTrim(theNurb);
    gluNurbsProperty(theNurb, GLU_U_STEP,30);
	gluNurbsProperty(theNurb, GLU_V_STEP, 30);
	gluNurbsProperty(theNurb, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
    gluEndSurface(theNurb);
    
    glEnable(GL_AUTO_NORMAL);		

}
void supNURBSes6(){

	
	qobj = gluNewQuadric(); //Creazione
	gluQuadricCallback(qobj, GLU_ERROR, (GLvoid (*))nurbsError); //Gestione errori
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluSphere(qobj, 0.75, 100, 100); //sfera
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
	//glutSolidTorus(0.30, 0.60,10,15);// toro pieno
			 //(GLdouble innerRadius, GLdouble outerRadius,GLint nsides, GLint rings);
	//glutWireCone(0.75, 1.0,15,10);//cono vuoto
			 //(GLdouble radius, GLdouble height,GLint slices,GLint stacks);
	//glutSolidCone(0.65, 0.9,15,10);//cono pieno
			//(GLdouble radius, GLdouble height,GLint slices,GLint stacks);
}




	void drawScene( void )
	{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

	glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	 //glOrtho(-1,1,-1,1,1,5);
	//glFrustum(-1,1,-1,1,1,5);
	gluPerspective(90,1,1,22);

	//Attivazione stak matrici modellazione
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	 //Sposto il sys di rifermento a -3 dall'osservatore
	//glTranslatef(0.0,-6.0,3.0);

	 float xRef,yRef,zRef;
	xRef=0.0;
	yRef=0.0;
	zRef=0.0;

	gluLookAt(sin(anglex)*3, sin(angley)*3, cos(anglez)*3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
		glPushMatrix();
			
			glTranslatef(0.5,0.0,0.0);
			supNURBSes6();
			glutSwapBuffers();

		glPopMatrix();
		glPushMatrix();
			
			glTranslatef(-0.5,0.0,0.0);
			supNURBSes6();
			glutSwapBuffers();

		glPopMatrix();
	glPopMatrix();

	glFlush();
	glDisable(GL_DEPTH_TEST);
	glFinish();

	}

	void mouse(int button, int state, int x, int y)
	{
		  
			if (button == GLUT_LEFT_BUTTON )
			{

				angle=angle+10.0;
				glutPostRedisplay();
			}
			if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
			{
				angle=angle-10.0;
				glutPostRedisplay();

			}
			glutPostRedisplay();
	}
	int main( int argc, char** argv){

	 glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowPosition( 300, 100 );
	glutInitWindowSize( 500, 500);
	glutInitWindowSize(width, height);
	glutCreateWindow( "pavimento" );
	glutDisplayFunc(drawScene);
	glutSpecialFunc(mySpecialInput);
	//glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
	}