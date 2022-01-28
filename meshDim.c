#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>


// fare una strutta per veertive e una struttura per casetta che richiama struttura 
//con vertici per ogni facciata con array punti di tutta facciata
float anglexz = 0.0;
float angley  = 0.0;

float calcolay(float x,float z)
{
    float y;
    y=((2*sin(sqrt(x*x+z*z)))/sqrt(x*x+z*z));
    return y;
}

void drawQuad(float x,float z){

    glNormal3f(0,1,1);
    glBegin(GL_LINE_STRIP);
        glVertex3f(x-0.1,calcolay(x-0.10,z-0.10),z-0.1);
        glVertex3f(x-0.1,calcolay(x-0.10,z+0.10),z+0.10);
        glVertex3f(x+0.1,calcolay(x+0.10,z-0.10),z+0.10);
        glVertex3f(x+0.10,calcolay(x+0.10,z+0.10),z-0.10);
      
    glEnd();
}

void drawGrid()
{ 
    float x;

    float z ;
    for(x=-10.0; x<10.0 ; x+=0.1)
    {
        for (z = -10.0; z < 10.0; z+=0.1)
        {     
            drawQuad(x,z);
        }

    }

}




void drawSquare()
{


    float x=0,y=0,z=0;
    for(int j=0;j<10;j++)
    {

        x=0;
        for(int i=0;i<10;i++)
        {
             drawQuad(x,z);
         x+=0.1;
     }
     y+=0.1;
     }
     glFlush();
  }

//disegna cerchio x e y punti di origine
void drawPoligon(GLfloat x, GLfloat y,GLfloat z, GLfloat radius, int numVertex) {
	int i;
	GLfloat twoPi = 2.0f * M_PI;	

	glBegin (GL_TRIANGLE_FAN);
		glVertex2f (x, y); // centro

		for (i = 0 ; i <= numVertex; i ++) {
			glVertex3f (
		        x + (radius * cos(i * twoPi / numVertex)),
			    y + (radius * sin(i * twoPi / numVertex)),
			    z
		
			);
			
		}
	glEnd ();
}




void drawScene( void )
{	
	


	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//Luce attivata
	glEnable(GL_LIGHTING);
	// luce default luce all'infinito (raggi paralleli) e NO COLOR
	glEnable(GL_LIGHT0);

	//Shade flat --> colore uniforme ogni faccia
	glShadeModel(GL_FLAT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-1,1,-1,1,1,5);
	//glFrustum(-1,1,-1,1,1,5);
	gluPerspective(65,1,5,25);


	//Attivazione stak matrici modellazione
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

     	
	    glPushMatrix();

			gluLookAt( sin(anglexz)*3, sin(angley)*3, cos(anglexz)*25, 0.0, 0.0, 0.0,0.0, 1.0, 0.0 );


			glPushMatrix();

				//drawPoligon(-1,0,0,0.2,4);
                drawGrid();

                //drawQuad(0.0,0.0,-0.2);

			glPopMatrix();

		glPopMatrix();


		


	glFlush();
	glDisable(GL_DEPTH_TEST);


	glFinish(); 

}


void SpecialInput(int key, int x, int y)
{
 switch(key)
        {
        case GLUT_KEY_UP:
            angley -= 5;
        break;
        case GLUT_KEY_DOWN:
         	angley += 5;
        break;
        case GLUT_KEY_LEFT:
            anglexz -= 5;
        break;
        case GLUT_KEY_RIGHT:
            anglexz += 5;
        break;
    }

    glutPostRedisplay();
}

int main( int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition( 300, 100 );
	glutInitWindowSize( 500, 500);
	glutCreateWindow( "casetta" );
	glutDisplayFunc(drawScene);
	glutSpecialFunc(SpecialInput); 
	glutMainLoop();
	return 0;
}
