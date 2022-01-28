#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

typedef struct {

	GLfloat x;
	GLfloat y;
	GLfloat z;

}vertice;

vertice vert1[8];
vertice vert2[8];


//disegna cerchio x e y punti di origine
void drawcerchio1(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int numVertex) {
	int i;
	
	GLfloat twoPi = 2.0f * M_PI;
	
	glColor3f( 1.0, 0.0, 1.0 );
	glBegin (GL_TRIANGLE_FAN);
		glVertex3f (x, y, z); // centro
		glColor3f( 0.0, 0.0, 1.0 );
		for (i = 0 ; i <= numVertex; i ++) {
			glVertex3f (
		        x + (radius * cos(i * twoPi / numVertex)),
			    y + (radius * sin(i * twoPi / numVertex)),
			    z
			);

			vert1[i].x = x;
			vert1[i].y = y;
			vert1[i].z = z;

		}
	glEnd ();
}

void drawcerchio2(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int numVertex) {
	int i;
	
	GLfloat twoPi = 2.0f * M_PI;
	
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

			vert2[i].x = x;
			vert2[i].y = y;
			vert2[i].z = z;
		}
	glEnd ();
}

void SpecialInput(int key, int x, int y)
 {
    switch(key)
        {
        case GLUT_KEY_UP:
        	glRotatef( -5.0, 0.0, 1, 0 );

 
        break;
        case GLUT_KEY_DOWN:
        	glScalef( 0.5, 0.5, 0.5 );
         	
        break;
        case GLUT_KEY_LEFT:
            //glRotatef( 5.0, 0.0, 0.0, 1.0 );
         	glTranslatef(0.0,0.0,-0.3);
	 
        break;
        case GLUT_KEY_RIGHT:
            glRotatef( -5.0, 0.0, 0.0, 1.0 );

        break;
    }

    glutPostRedisplay();
}

void poli(){

	int i;
	glColor3f( 0.0, 1.0, 0.0 );
	glBegin (GL_QUAD_STRIP);
		
		glColor3f( 0.0, 1.0, 0.0 );
		for (i = 0 ; i <= 8; i ++) {
			glVertex3f(vert1[i].x, vert1[i].y, vert1[i].z);
			glVertex3f(vert2[i].x, vert2[i].y, vert2[i].z); // centro
		}

	glEnd();

}

 
void drawScene( void )
{	
	

     
	 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glEnable(GL_DEPTH_TEST);
	 glRotatef(45.0,0.0,1.0,1.0);

	 glOrtho(-1,1,-1,1,1,5);
	 //glFrustum(-1,1,-1,1,1,5);
	 //gluPerspective(45,1,1,5);


	 //Sposto il sys di rifermento a -3 dall'osservatore
	 glTranslatef(0.0,0.0,-3.0);
	 
	 drawcerchio1( 0.2,0.2,-0.5,0.5,8);
	 //drawcerchio2( 0.2,0.2,-2.5,0.5,8);
	 poli();
	 glRotatef(45.0,0.0,0.0,1.0);
	 

	 //far plane (depth buffer max)
	 //per ogni px -calcolo dist tra osservatore e punto
	 //			   -confronto distanza con depth buffer
	 //			   - if dis < val -----> obj piu vicino e aggiorno i valore
	 //				 else scarto valori perche obj oscurato

	 glutSpecialFunc(SpecialInput); 
	 glFlush();
	 glDisable(GL_DEPTH_TEST);
 
}

 

int main( int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition( 300, 100 );
	glutInitWindowSize( 500, 500);
	glutCreateWindow( "Prisma 8gonale" );
	glutDisplayFunc(drawScene );
	glutMainLoop();
	return 0;
}
