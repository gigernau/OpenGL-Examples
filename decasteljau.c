#include <GL/glut.h>
#include <math.h>
#include<time.h>
#include <stdio.h>
#define MAX_CPTS  12  

GLfloat cpts[MAX_CPTS][3];
int ncpts = 0;
static int width = 500, height = 500;
int flag=1;
typedef struct {

	GLfloat x;
	GLfloat y;
	GLfloat z;

}Point;

struct timeb{
	time_t time;
    unsigned short millitm;
	short timezone;
    short dstflag;
 };
int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}

float binomial_coff(float n,float k)
{
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));
    return ans;
}

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

void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
      glVertex3f(p1.x, p1.y, p2.z);
      glVertex3f(p2.x, p2.y, p2.z);
    glEnd();
    glFlush();
}

Point drawBezier(Point* punti, int i, double t, int n) {
        Point P;
     	
     	
         P.x = (1-t)*punti[i].x + (t)*punti[i+1].x;
	     P.y = (1-t)*punti[i].y + (t)*punti[i+1].y;
	     P.z = (1-t)*punti[i].z + (t)*punti[i+1].z;
	    
        return P;
 }


Point drawBezierGeneralized(Point PT[], double t, int n) {
        Point P;
        P.x = 0; P.y = 0; P.z=0;  
        for (int i = 0; i<n; i++)
        {
            P.x = P.x + binomial_coff((float)(n - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (n - 1 - i)) * PT[i].x;
            P.y = P.y + binomial_coff((float)(n - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (n - 1 - i)) * PT[i].y;
            P.z = P.z + binomial_coff((float)(n - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (n - 1 - i)) * PT[i].z;
        }

        return P;
    }

Point decasteljau (int n, GLfloat p[][3], double t){
	int i;
	double r;
	
	Point punti[n];
	Point newPoint;

	for(i=0; i<n; i++){
		punti[i].x = p[i][0];
		punti[i].y = p[i][1];
		punti[i].z = p[i][2];
	}

	for(r=1; r<n; r++){
		for(i=0; i<n-r; i++){

			newPoint = drawBezierGeneralized(punti,t,n);
			
	}	}

	return newPoint;
}

void meshBezier(){

	
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, ncpts, &cpts[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	
	int m = 30;
	int u1 = 0;
	int u2 = 1;

	int i1 = 0;
	int i2 = 30;

	glMapGrid1f(m, u1, u2); /*inizializza i valori equispaziati*/
	glEvalMesh1(GL_LINE, i1, i2); /*disegna la curva*/
}


void randomPoint(int n){
		
		int exp1,exp2;


		for(int i=0;i<n;i++){
			srand(i); 
		   float x =  (float)rand()/(RAND_MAX*2.0-1.0);
		   float y =  (float)rand()/(RAND_MAX*2.0-1.0);
		   exp1=pow(-1.0,(rand()%10+1));
		   srand(time(NULL));
		   exp2=pow(-1.0,(rand()%10+1));
		   x=x*exp1;
		   y=y*exp2;



	       cpts[ncpts][0] = x;
	       cpts[ncpts][1] = y;
	       cpts[ncpts][2] = 0.0;

	       ncpts++;
		}
}

void drawScene( void )
{	
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	

	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1,1,-1,1,1,5);
	//glFrustum(-1,1,-1,1,1,5);
	//gluPerspective(90,1,1,22);


	//Attivazione stak matrici modellazione
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    //Sposto il sys di rifermento a -3 dall'osservatore
	//glTranslatef(0.0,-6.0,3.0);

	float xRef,yRef,zRef;
	xRef=0.0;
	yRef=0.0;
	zRef=0.0;

	
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	

	/*Point p1,p3,p2,p4;
	cpts[0][0] = -0.5;
	cpts[0][1] = -0.5;
	cpts[0][2] = 0.0;

	cpts[1][0] = -0.25;
	cpts[1][1] = 0.4;
	cpts[1][2] = 0.0;
	
	cpts[2][0] = 0.3;
	cpts[2][1] = 0.6;
	cpts[2][2] = 0.0;

	cpts[3][0] = 0.4;
	cpts[3][1] = -0.4;
	cpts[3][2] = 0.0;*/

	
	int n = 4;

	glPointSize(2);
			//drawDot(cpts[0][0],cpts[0][1],cpts[0][2]);
			//drawDot(cpts[1][0],cpts[1][1],cpts[1][2]);
			//drawDot(cpts[2][0],cpts[2][1],cpts[2][2]);
			//drawDot(cpts[3][0],cpts[3][1],cpts[3][2]);
	srand(time(NULL));    
	int num =4;
	if(flag){
		randomPoint(num);
		flag=0;
	}

	
	for(int i =0; i<ncpts; i++){
		drawDot(cpts[i][0],cpts[i][1],cpts[i][2]);
	}
	Point tempPoint;
	tempPoint.x = cpts[0][0];
	tempPoint.y = cpts[0][1];
	tempPoint.z = cpts[0][2];	

	glPushMatrix();
	
		glPushMatrix();	
				float c =0.0;
			    for(double w=0;w<1.0;w+=0.001){
			    	c = c + 0.3;
			    	glColor3f( c, 1.0, 0.0 );
			    	Point np=decasteljau(ncpts,cpts,w);
			    	drawLine(tempPoint,np);
			    	tempPoint = np;

			    }
			 
						
		
		
			glutSwapBuffers();
		glPopMatrix();	
	
	glPopMatrix();

	glFlush();
	glDisable(GL_DEPTH_TEST);
	glFinish(); 

}



void mouse(int button, int state, int x, int y)
{
    float wx, wy;
    //printf("%d\n",x );
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

       /* translate back to our coordinate system */
       wx = (2.0 * x) / (float)(width - 1) - 1.0;
       wy = (2.0 * (height - 1 - y)) / (float)(height - 1) - 1.0;

      /* see if we have room for any more control points */
       if (ncpts == MAX_CPTS) return;

       /* save the point */
       cpts[ncpts][0] = wx;
       cpts[ncpts][1] = wy;
       cpts[ncpts][2] = 0.0;
       ncpts++;

       /* draw the point */
      	
     	
    	glFlush();
		glutPostRedisplay();
    } 
    
}

int main( int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowPosition( 300, 100 );
	glutInitWindowSize( 500, 500);
	glutInitWindowSize(width, height);
	glutCreateWindow( "pavimento" );
	glutDisplayFunc(drawScene);
	//glutSpecialFunc(SpecialInput); 
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}