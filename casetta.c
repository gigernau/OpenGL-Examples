#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>


// fare una strutta per veertive e una struttura per casetta che richiama struttura 
//con vertici per ogni facciata con array punti di tutta facciata
float anglexz = 0.0;
float angley  = 0.0;


//Dichiarazione struttura Vertice
typedef struct {

	GLfloat x;
	GLfloat y;
	GLfloat z;

}vertice;

//Dichiarazione struttura facciata
typedef struct {

	vertice v1;
	vertice v2;
	vertice v3;
	vertice v4;
	vertice v5;
	
}facciata;

//Dichiarazione struttura casetta
typedef struct {

	vertice normali[7];
	vertice vertici[10];
	facciata facciate[7];

}casetta;



GLfloat normali[7][3] = 
{  
    {1.0, 0.0, 0.0},
    {-1.0, 0.0, 0.0},  
    {0.0, 0.0, 1.0}, 
    {0.0, 0.0, -1.0}, 
    {1.0, 1.0, 0.0}, 
    {-1.0, 1.0, 0.0}, 
    {0.0, -1.0, 0.0}, 

};

GLfloat vertici[10][3] = 
{
    {0.2, 0.1, 0.0},//0
    {0.9, 0.1, 0.0},//1
    {0.9, 0.575, 0.0},//2
    {0.2, 0.575, 0.0},//3
    {0.2, 0.1, 0.5},//4
    {0.9, 0.1, 0.5},//5
    {0.9, 0.575, 0.5},//6
    {0.2, 0.575, 0.5},//7
    {0.2, 0.8, 0.25},//8
    {0.9, 0.8, 0.25}//9
};

GLint facciate[7][5] =
{
    {0,1,2,3},
    {4,5,6,7},
    {4,0,3,8,7},
    {5,1,2,9,6},
    {3,2,9,8},
    {7,6,9,8},
    {4,0,5,1}
};
 

void drawCasetta()
{


    int i,j;
    for(i=0; i<7 ; i++)
    {
    	glBegin(GL_POLYGON);
    	glNormal3f(normali[i][0],normali[i][1],normali[i][2]);
    	//per ogni facciata
        for (int j = 0; j < 5; j++)
        {     
        
            glVertex3f(vertici[facciate[i][j]][0],vertici[facciate[i][j]][1],vertici[facciate[i][j]][2]);
            
        }
        glEnd();
    }
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

void drawCasetta1(){


	//vettore normale
	glNormal3f(1.0,0.0,0.0);

/* main rec */
    glClear (GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.1, 0.0);      //0
    glVertex3f (0.9, 0.1, 0.0);		 //1
    glVertex3f (0.9, 0.575, 0.0);    //2
    glVertex3f (0.2, 0.575, 0.0);    //3
    glEnd();



	//vettore normale
	glNormal3f(-1.0,0.0,0.0);

    /*back rec*/
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.1, 0.5);      //4
    glVertex3f (0.9, 0.1, 0.5);      //5   
    glVertex3f (0.9, 0.575, 0.5);    //6
    glVertex3f (0.2, 0.575, 0.5);    //8
    glEnd();



	//vettore normale
	glNormal3f(0.0,0.0,1.0);

    /* left rec */
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.1, 0.5);      //4
    glVertex3f (0.2, 0.1, 0.0);      //0
    glVertex3f (0.2, 0.575, 0.0);    //3
    glVertex3f (0.2, 0.8, 0.25);     //7
    glVertex3f (0.2, 0.575, 0.5);    //8
    glEnd();


	//vettore normale
	glNormal3f(0.0,0.0,-1.0);


    /* right rec */
    glBegin(GL_POLYGON);
    glVertex3f (0.9, 0.1, 0.5);      //5
    glVertex3f (0.9, 0.1, 0.0);      //1
    glVertex3f (0.9, 0.575, 0.0);    //2
    glVertex3f (0.9, 0.8, 0.25);     //9
    glVertex3f (0.9, 0.575, 0.5);    //6
    glEnd();

   


	//vettore normale
	glNormal3f(1.0,1.0,0.0);

    /* roof */
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.575, 0.0);    //3
    glVertex3f (0.9, 0.575, 0.0);    //2
    glVertex3f (0.9, 0.8, 0.25);     //9
    glVertex3f (0.2, 0.8, 0.25);     //7
    glEnd();

    //vettore normale
	glNormal3f(-1.0,1.0,0.0);
    /*back roof */
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.575, 0.5);    //8
    glVertex3f (0.9, 0.575, 0.5);    //6
    glVertex3f (0.9, 0.8, 0.25);     //9
    glVertex3f (0.2, 0.8, 0.25);     //7
    glEnd();




	

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
	gluPerspective(45,1,1.4,5);


	//Attivazione stak matrici modellazione
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Sposto il sys di rifermento a -3 dall'osservatore
	//glTranslatef(0.0,0.0,-3.0);

     	float xRef,yRef,zRef;
     	xRef=0.0;
     	yRef=0.0;
     	zRef=0.0;

     	
	    glPushMatrix();
	     
	     //Spostare il punto di vista
		 //rotoScope per x y e x , eye(pos osservatore),center e upVector
		
	    	
			/* Posiziona eye sull’asse z positivo,
			* guarda verso ( xRef, yRef, zRef ),
			* e definisce y positivo come `up'
			*/
		 	//tra +60 e -60
			gluLookAt( sin(anglexz)*3, sin(angley)*3, cos(anglexz)*3, xRef, yRef, zRef,0.0, 1.0, 0.0 );


			glPushMatrix();

				drawCasetta1();
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
