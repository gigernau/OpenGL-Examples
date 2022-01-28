#include <GL/glut.h>
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

void calcolapunti(float mat[][3], float x, float z){
	float matt[4][3]={
		{x-0.50,calcolay(x-0.50,z-0.50),z-0.50},
		{x-0.50,calcolay(x-0.50,z+0.50),z+0.50},
		{x+0.50,calcolay(x+0.50,z+0.50),z+0.50},
		{x+0.50,calcolay(x+0.50,z-0.50),z-0.50}
	};
	mat=matt;
}

void newell(float mat[][3],int n){
	float mx,my,mz;
	mx=0.0;
	my=0.0;
	mz=0.0;
	for(int i=0;i<n;i++){
		mx=mx+((((mat[i][1])-mat[((i+1)%n)][1]))*((mat[i][2]+mat[(i+1)%n][2])));
		my=my+((mat[i][2]-mat[(i+1)%n][2])*(mat[i][0]+mat[(i+1)%n][0]));
		mz=mz+((mat[i][0]-mat[(i+1)%n][0])*(mat[i][1]+mat[(i+1)%n][1]));
	}
	glNormal3f(mx,my,mz);
}


void quadratino(float x, float z){
	float punti[4][3];
	calcolapunti(punti,x,z);
	
	glBegin(GL_LINE_LOOP);newell(punti,4);
	glVertex3f(x-0.50,calcolay(x-0.50,z-0.50),z-0.50);
	glVertex3f(x-0.50,calcolay(x-0.50,z+0.50),z+0.50);
	glVertex3f(x+0.50,calcolay(x+0.50,z-0.50),z+0.50);
	glVertex3f(x+0.50,calcolay(x+0.50,z+0.50),z-0.50);
	glEnd();
}
void pavimento()
{

	float i,j;
	for(i=-10.0; i<10.0 ; i=i+0.50)
	{
		for (j = -10.0; j < 10.0; j=j+0.50)
		{	 
			quadratino(i,j);
			
		}
	
	}
}

void drawScene( void )
{	
	


	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	//Luce attivata
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
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
	//glTranslatef(0.0,0.0,-3.0);

	float xRef,yRef,zRef;
	xRef=0.0;
	yRef=0.0;
	zRef=0.0;


	glPushMatrix();
		gluLookAt( sin(anglexz)*1, sin(angley)*6, cos(anglexz)*20, 0.0, 0.0, 0.0,0.0, 1.0, 0.0 );
		glPushMatrix();
			pavimento();
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
	glutCreateWindow( "pavimento" );
	glutDisplayFunc(drawScene);
	glutSpecialFunc(SpecialInput); 
	glutMainLoop();
	return 0;
}