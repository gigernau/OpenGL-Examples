	#include <GL/glut.h>
	#include <math.h>
	#include<time.h>
	#include <stdio.h>
	#define MAX_CPTS 12

	static int width = 500, height = 500;
	int flag=1;

	int tasto1 = 0;
	int tasto2 = 0;
	int tasto3 = 0;

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


void bottone(int col){

	GLfloat light_N[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_R[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_W[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_G[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat light_B[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	switch(col){
		case 1:
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,light_R);
			break;
		case 2:
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,light_B);
			break;
		case 3:
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,light_G);
			break;

	}
	
	
	glutSolidCube(0.45);//cubo pieno
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,light_N);
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
	GLfloat light_N[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_R[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_B[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//glShadeModel(GL_FLAT);

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

	//posizione 

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_B);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position );
		
	//gluLookAt(sin(anglex)*3, sin(angley)*3, cos(anglez)*3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_R);
	
	glPushMatrix();
		glRotatef(anglex*20, 0.0, 1.0, 0.0);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position );
		
		
		glPushMatrix();
			glTranslatef(0.5,0.0,0.0);
			supNURBSes6();
			

		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.5,0.0,0.0);
			supNURBSes6();
			

		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
	glFlush();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT0);
	glFinish();

}
void drawScene2( void )
	{
	GLfloat light_G[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat light_R[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_B[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat light_W[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_position1[] = { 1.0, 1.4, 1.0, 0.0 };
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//glShadeModel(GL_FLAT);

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
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_W);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position );
		
	//gluLookAt(sin(anglex)*3, sin(angley)*3, cos(anglez)*3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPushMatrix();
		glTranslatef(0.0,1.0,0.0);
		bottone(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0,1.0,0.0);
		bottone(2);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.0,1.0,0.0);
		bottone(3);
	glPopMatrix();


	glPushMatrix();
		glTranslatef(0.0,-1.0,0.0);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,light_W);
		glRotatef(angley*20, 0.0, 1.0, 0.0);

		if(tasto1){
			glLightfv(GL_LIGHT1, GL_DIFFUSE, light_G);
		}
		else if(tasto2){
			glLightfv(GL_LIGHT1, GL_DIFFUSE, light_R);
		}
		else if(tasto3){
			glLightfv(GL_LIGHT1, GL_DIFFUSE, light_B);
		}
		
		
		glLightfv(GL_LIGHT1, GL_POSITION, light_position1 );
		    


		glPushMatrix();
			glTranslatef(0.5,0.0,0.0);
			supNURBSes6();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.5,0.0,0.0);
			supNURBSes6();
		glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
	glFlush();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT0);
	glFinish();

	}

void mouse(int button, int state, int x, int y)
{
    float wx, wy;
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

       /* translate back to our coordinate system */
       wx = (2.0 * x) / (float)(width - 1) - 1.0;
       wy = (2.0 * (height - 1 - y)) / (float)(height - 1) - 1.0;

       printf("%f-%f\n",wx,wy);

        //tasto verde
       if(wx>=-0.21 && wx<=0.006 ){
       		if(wy>=0.06 && wy<=0.26 ){
       			tasto1 = 1;
       			tasto2 = 0;
       			tasto3 = 0;
       			printf("%d\n",tasto1 );
       		}
       }

       //tasto rosso
       if(wx>=0.29 && wx<=0.51 ){
       		if(wy>=0.05 && wy<=0.25 ){
       			tasto2 = 2;
       			tasto1 = 0;
       			tasto3 = 0;

       			printf("%d\n",tasto2 );
       		}

       }

       //tasto blu
       if(wx>=0.80 && wx<=1.02 ){
       		if(wy>=0.05 && wy<=0.25 ){
       			tasto3 = 3;
       			tasto2 = 0;
       			tasto1 = 0;

       			printf("%d\n",tasto3 );
       		}
       }



       

      
     	
    	glFlush();
		glutPostRedisplay();
    } 
    
}

	int main( int argc, char** argv){

	 glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowPosition( 100, 0 );
	glutInitWindowSize( 700, 650);
	//glutInitWindowSize(width, height);
	glutCreateWindow( "sfere intersecate" );
	glutDisplayFunc(drawScene2);
	glutSpecialFunc(mySpecialInput);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
	}