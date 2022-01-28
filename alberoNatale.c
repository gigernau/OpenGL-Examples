	#include <GL/glut.h>
	#include <math.h>
	#include<time.h>
	#include <stdio.h>
	#include <stdlib.h> 
	#include <string.h>
    #include <GL/glext.h>


	#define MAX_CPTS 12

	static int width = 500, height = 500;
	int flag1=1;
	int flag2 = 0;
	
	GLUnurbsObj *theNurb;
	GLUquadricObj *qobj;
	
	float anglexz=0.0;
	float angley=0.0;
    float asseZ = 2.5;
    float asseXY = 2.5;
    GLfloat twoPi = 2.0f * M_PI;


	static GLuint texnames[3];
unsigned * read_texture(char *name, int *width, int *height, int *components);

void
bwtorgba(unsigned char *b,unsigned char *l,int n) {
    while(n--) {
        l[0] = *b;
        l[1] = *b;
        l[2] = *b;
        l[3] = 0xff;
        l += 4; b++;
    }
}

void
rgbtorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *l,int n) {
    while(n--) {
        l[0] = r[0];
        l[1] = g[0];
        l[2] = b[0];
        l[3] = 0xff;
        l += 4; r++; g++; b++;
    }
}

void
rgbatorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *a,unsigned char *l,int n) {
    while(n--) {
        l[0] = r[0];
        l[1] = g[0];
        l[2] = b[0];
        l[3] = a[0];
        l += 4; r++; g++; b++; a++;
    }
}

typedef struct _ImageRec {
    unsigned short imagic;
    unsigned short type;
    unsigned short dim;
    unsigned short xsize, ysize, zsize;
    unsigned int min, max;
    unsigned int wasteBytes;
    char name[80];
    unsigned long colorMap;
    FILE *file;
    unsigned char *tmp, *tmpR, *tmpG, *tmpB;
    unsigned long rleEnd;
    unsigned int *rowStart;
    int *rowSize;
} ImageRec;

static void
ConvertShort(unsigned short *array, unsigned int length) {
    unsigned short b1, b2;
    unsigned char *ptr;

    ptr = (unsigned char *)array;
    while (length--) {
        b1 = *ptr++;
        b2 = *ptr++;
        *array++ = (b1 << 8) | (b2);
    }
}

static void
ConvertUint(unsigned *array, unsigned int length) {
    unsigned int b1, b2, b3, b4;
    unsigned char *ptr;

    ptr = (unsigned char *)array;
    while (length--) {
        b1 = *ptr++;
        b2 = *ptr++;
        b3 = *ptr++;
        b4 = *ptr++;
        *array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
    }
}

static ImageRec *ImageOpen(char *fileName)
{
    union {
        int testWord;
        char testByte[4];
    } endianTest;
    ImageRec *image;
    int swapFlag;
    int x;

    endianTest.testWord = 1;
    if (endianTest.testByte[0] == 1) {
        swapFlag = 1;
    } else {
        swapFlag = 0;
    }

    image = (ImageRec *)malloc(sizeof(ImageRec));
    if (image == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    if ((image->file = fopen(fileName, "rb")) == NULL) {
        perror(fileName);
        exit(1);
    }

    fread(image, 1, 12, image->file);

    if (swapFlag) {
        ConvertShort(&image->imagic, 6);
    }

    image->tmp = (unsigned char *)malloc(image->xsize*256);
    image->tmpR = (unsigned char *)malloc(image->xsize*256);
    image->tmpG = (unsigned char *)malloc(image->xsize*256);
    image->tmpB = (unsigned char *)malloc(image->xsize*256);
    if (image->tmp == NULL || image->tmpR == NULL || image->tmpG == NULL ||
        image->tmpB == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }

    if ((image->type & 0xFF00) == 0x0100) {
        x = image->ysize * image->zsize * (int) sizeof(unsigned);
        image->rowStart = (unsigned *)malloc(x);
        image->rowSize = (int *)malloc(x);
        if (image->rowStart == NULL || image->rowSize == NULL) {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        image->rleEnd = 512 + (2 * x);
        fseek(image->file, 512, SEEK_SET);
        fread(image->rowStart, 1, x, image->file);
        fread(image->rowSize, 1, x, image->file);
        if (swapFlag) {
            ConvertUint(image->rowStart, x/(int) sizeof(unsigned));
            ConvertUint((unsigned *)image->rowSize, x/(int) sizeof(int));
        }
    }
    return image;
}

static void
ImageClose(ImageRec *image) {
    fclose(image->file);
    free(image->tmp);
    free(image->tmpR);
    free(image->tmpG);
    free(image->tmpB);
    free(image);
}

static void
ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z) {
    unsigned char *iPtr, *oPtr, pixel;
    int count;

    if ((image->type & 0xFF00) == 0x0100) {
        fseek(image->file, (long) image->rowStart[y+z*image->ysize], SEEK_SET);
        fread(image->tmp, 1, (unsigned int)image->rowSize[y+z*image->ysize],
              image->file);

        iPtr = image->tmp;
        oPtr = buf;
        for (;;) {
            pixel = *iPtr++;
            count = (int)(pixel & 0x7F);
            if (!count) {
                return;
            }
            if (pixel & 0x80) {
                while (count--) {
                    *oPtr++ = *iPtr++;
                }
            } else {
                pixel = *iPtr++;
                while (count--) {
                    *oPtr++ = pixel;
                }
            }
        }
    } else {
        fseek(image->file, 512+(y*image->xsize)+(z*image->xsize*image->ysize),
              SEEK_SET);
        fread(buf, 1, image->xsize, image->file);
    }
}

unsigned *
read_texture(char *name, int *width, int *height, int *components) {
    unsigned *base, *lptr;
    unsigned char *rbuf, *gbuf, *bbuf, *abuf;
    ImageRec *image;
    int y;

    image = ImageOpen(name);
    
    if(!image)
        return NULL;
    (*width)=image->xsize;
    (*height)=image->ysize;
    (*components)=image->zsize;
    base = (unsigned *)malloc(image->xsize*image->ysize*sizeof(unsigned));
    rbuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
    gbuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
    bbuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
    abuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
    if(!base || !rbuf || !gbuf || !bbuf)
      return NULL;
    lptr = base;
    for(y=0; y<image->ysize; y++) {
        if(image->zsize>=4) {
            ImageGetRow(image,rbuf,y,0);
            ImageGetRow(image,gbuf,y,1);
            ImageGetRow(image,bbuf,y,2);
            ImageGetRow(image,abuf,y,3);
            rgbatorgba(rbuf,gbuf,bbuf,abuf,(unsigned char *)lptr,image->xsize);
            lptr += image->xsize;
        } else if(image->zsize==3) {
            ImageGetRow(image,rbuf,y,0);
            ImageGetRow(image,gbuf,y,1);
            ImageGetRow(image,bbuf,y,2);
            rgbtorgba(rbuf,gbuf,bbuf,(unsigned char *)lptr,image->xsize);
            lptr += image->xsize;
        } else {
            ImageGetRow(image,rbuf,y,0);
            bwtorgba(rbuf,(unsigned char *)lptr,image->xsize);
            lptr += image->xsize;
        }
    }
    ImageClose(image);
    free(rbuf);
    free(gbuf);
    free(bbuf);
    free(abuf);

    return (unsigned *) base;
}








































GLfloat ambient[4] = { 0.8, 0.8, 0.8, 1 };

GLfloat pos[4] = { 0.0, 0.0, 2.0, 1 };
GLfloat colD[4] = { 0.8, 0.8, 0.8, 1 };
GLfloat colA[4] = { 0.3, 0.3, 0.3, 1 };
GLfloat colS[4] = { 0.0, 0.0, 0.0, 1 };
GLfloat spotDir[3] = { -0.8, 1, 15.0 };

GLfloat matDiffuse[4] = { 0.8, 0.8, 0.8, 1 };
GLfloat matAmbient[4] = { 0.2, 0.2, 0.2, 1 };
GLfloat matSpecular[4] = { 0.0, 0.0, 0.0, 1 };
GLfloat matEmission[4] = { 0.0, 0.0, 0.0, 1 };

static GLfloat sgenparams[] = { 1, 0, 0, 0 };
static GLfloat tgenparams[] = { 0, 1, 0, 0 };
static GLfloat zgenparams[] = { 0, 0, 1, 0 };

GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

GLvoid initgfx( void ){
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
}

GLvoid initTexture(  unsigned *image, unsigned *image1,unsigned *image2,unsigned *image3, GLsizei imageWidth, GLsizei imageHeight ){
	GLsizei sWidth=256, sHeight=256;
	unsigned *sImage;
    unsigned *sImage1;
	unsigned *sImage2;
	unsigned *sImage3;

	sImage = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );    
    sImage1 = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );	
	sImage2 = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );
	sImage3 = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );

	gluScaleImage( GL_RGBA, imageWidth, imageHeight,GL_UNSIGNED_BYTE, image,sWidth, sHeight, GL_UNSIGNED_BYTE, sImage );
	gluScaleImage( GL_RGBA, imageWidth, imageHeight,GL_UNSIGNED_BYTE, image1,sWidth, sHeight, GL_UNSIGNED_BYTE, sImage1 );
    gluScaleImage( GL_RGBA, imageWidth, imageHeight,GL_UNSIGNED_BYTE, image2,sWidth, sHeight, GL_UNSIGNED_BYTE, sImage2 );
	gluScaleImage( GL_RGBA, imageWidth, imageHeight,GL_UNSIGNED_BYTE, image3,sWidth, sHeight, GL_UNSIGNED_BYTE, sImage3 );

	glGenTextures(4, texnames);

	glBindTexture(GL_TEXTURE_2D, texnames[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, sImage);


	glBindTexture(GL_TEXTURE_2D, texnames[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, sImage2);

	glBindTexture(GL_TEXTURE_2D, texnames[2]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, sImage3);


    glBindTexture(GL_TEXTURE_2D, texnames[3]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, sImage1);

	
	
	glEnable( GL_TEXTURE_2D );
}

GLvoid nurbsError(GLenum errorCode) 
	{
		const GLubyte *estring;
		estring = gluErrorString(errorCode);
		fprintf (stderr, "Errore NURBS: %s\n", estring);
		exit (0);
	}


GLfloat light_B[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat diffuseRED[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat diffuseBLUE[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat diffuseYELL[] = { 1.0, 1.0, 0.0, 1.0 };

GLfloat diffuseARANC[] = { 0.8, 0.6, 0.0, 1.0 };
GLfloat diffuseCELESTE[]={0.3,.7,.8,1};
GLfloat diffuseVIOLA[] = { 1.0, 0.0, 1.0, 1.0 };
GLfloat NOemm[] = { .0, .0, 0, 1.0 };
GLfloat emm[] = { 0.8, 0.8, 0, 1.0 };
float shine[] = {128.0f};
float noShine[] = {0.0f};
int cluci = 0;

float calcolaz(float x,float z)
{
	float y;
	y=((2*sin(sqrt(x*x+z*z)))/sqrt(x*x+z*z));
	return y;
}







void chioma(){
	glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texnames[0]);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, tgenparams);
    double i = 0;
    int j =0;
    int flag=1;
    for (i=0.0;i<1.5;i+=0.3){
    	
    	glPushMatrix();
    			glTranslatef(0.0,0.0,0.8-i);
    			glutSolidCone(0.40+(i/2),0.6,15,10);//cono pieno
    	glPopMatrix();
       
    }
    
    glEnable(GL_LIGHTING);

}
void puntale(){
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseRED);
	glMaterialfv(GL_FRONT,GL_SPECULAR,light_B);
    glMaterialfv(GL_FRONT,GL_SHININESS,shine);
    glTranslatef(0.0,0.0,-0.1);
	glutSolidCone(0.035,0.35,15,10);//cono pieno
	glTranslatef(0.0,0.0,0.19);
	glutSolidSphere(0.07,80,60);
	glTranslatef(0.0,0.0,0.03);
	glutSolidCone(0.035,0.35,80,60);
	


	
}
void tronco(){
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, texnames[1]);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, tgenparams);
	glEnable(GL_TEXTURE_2D);
	glutSolidCone(0.20,1.5,15,10);//cono pieno
	glEnable(GL_LIGHTING);	
}

void quadratino(float x, float z){
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, texnames[2]);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, tgenparams);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glVertex3f(x-0.50,z-0.50,calcolaz(x-0.50,z-0.50)/6);
	glVertex3f(x-0.50,z+0.50,calcolaz(x-0.50,z+0.50)/6);
	glVertex3f(x+0.50,z+0.50,calcolaz(x+0.50,z+0.50)/6);
	glVertex3f(x+0.50,z-0.50,calcolaz(x+0.50,z-0.50)/6);
	glEnd();
	glEnable(GL_LIGHTING);
	
}


void neveterra(){
	float i,j;
	for(i=-4.0; i<4.0 ; i=i+0.50)
		for (j = -4.0; j < 4.0; j=j+0.50) 
			quadratino(i,j);


}

void pezzocielo(float x, float z){
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, texnames[3]);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, tgenparams);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glVertex3f(x-0.50,z-0.50,calcolaz(x-0.50,z-0.50)*3);
	glVertex3f(x-0.50,z+0.50,calcolaz(x-0.50,z+0.50)*3);
	glVertex3f(x+0.50,z+0.50,calcolaz(x+0.50,z+0.50)*3);
	glVertex3f(x+0.50,z-0.50,calcolaz(x+0.50,z-0.50)*3);
	glEnd();
	glEnable(GL_LIGHTING);
	
}

void cielo(){

	float i,j;
	for(i=-4.0; i<4.0 ; i=i+0.50)
		for (j = -4.0; j < 4.0; j=j+0.50) 
			pezzocielo(i,j);

}



void luce(int att){
	if(att){
		glDisable(GL_TEXTURE_2D);
	    glMaterialfv(GL_FRONT,GL_DIFFUSE,light_B);
	    glMaterialfv(GL_FRONT,GL_SPECULAR,light_B);
	    glMaterialfv(GL_FRONT,GL_SHININESS,shine);
	    glMaterialfv(GL_FRONT,GL_EMISSION,emm);
	    glutSolidSphere(0.015,15, 10);
	    glMaterialfv(GL_FRONT,GL_EMISSION,NOemm);
	}
	else{

	    glutSolidSphere(0.015,15, 10);
	 
	}
	
}

int flag3=1;

void sfera(int col){

   
    glDisable(GL_TEXTURE_2D);
	
    if(flag3 == -1 && col == 1)
    	col = 4;

    if(flag3 == -1 && col == 2)
    	col = 5;

	if (col == 1 || col == 5 )
	    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseARANC);
	else if (col == 0 || col == 6 )
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseVIOLA);
    else if ( col == 9 || col == 4)
        glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseRED);
    else if ( col == 2 || col == 7 )
        glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseBLUE);
    else if (col == 3 || col == 8 )
        glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseYELL);
    else if(col = 10)
    	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseCELESTE);

    glMaterialfv(GL_FRONT,GL_SPECULAR,light_B);
    glMaterialfv(GL_FRONT,GL_SHININESS,shine);
    

    glutSolidSphere(0.05,15, 10);//palla piena


}

void posizionapalle(int numBall,float radius,int flag3){
	for(int y=0;y<numBall;y++){
                glTranslatef(
                    (radius * cos(y * twoPi /numBall)),
                    (radius * sin(y * twoPi / numBall)),
                    0);
                if (flag3)
                	sfera(y+1);
                else
                	sfera(y);
            }
}




void palline() {

    glTranslatef(-0.28,-0.9,-0.5);
    int numBall=10;
    float radius = 0.58;
    float altezza = 0.0;

    for(float i=0;i<1.2;i+=0.2){
    	
    	glPushMatrix();
           posizionapalle(numBall,radius,flag3);
        glPopMatrix();

        numBall-=1;
        flag3=-1*flag3;
        glTranslatef(0.022,0.14,0.28);
        radius-=0.05;
    }
    glTranslatef(0.15,0.058,0.1);
	puntale();
}


void posizionaluci(int numluci,float radius,int att){
	for(int y=0;y<numluci;y++){
                glTranslatef(
                    (radius * cos(y * twoPi /numluci)),
                    (radius * sin(y * twoPi / numluci)),
                    0);

                luce(att);
                
            }
}

void giocoluci(int att) {

    glTranslatef(-0.28,-0.9,-0.5);
    int numBall=10;
    float radius = 0.55;
    float altezza = 0.0;

    for(float i=0;i<1.2;i+=0.2){
        glPushMatrix();
           posizionaluci(numBall,radius,att);
        glPopMatrix();

        numBall-=1;
        glTranslatef(0.022,0.14,0.28);
        radius-=0.05;
    }

}

void illuminazione(){
     // varie circoferrenze luci
    for (int j=0;j<3; j++){
                
            glPushMatrix();
                glRotatef(10,0.0,0.0,1.0);
                giocoluci(flag1);
            glPopMatrix();
                glRotatef(20,0.0,0.0,1.0);
						
            glPushMatrix();
                    glRotatef(20,0.0,0.0,1.0);
                    giocoluci(flag2);
            glPopMatrix();
            glTranslatef(0.0,0.0,0.05);
    }

}


void alberello (){

		glPushMatrix();
			glTranslatef(0.0,0.0,-1.3);
			tronco();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0,0.0,-0.1);
			chioma();	
		glPopMatrix();

        glPushMatrix();
            palline();
        glPopMatrix();

        glPushMatrix();
            palline();
        glPopMatrix();

        glPushMatrix();

           illuminazione();
            
        glPopMatrix();

}

void drawScene( void ){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	

	glEnable( GL_TEXTURE_GEN_S );
	glEnable( GL_TEXTURE_GEN_T );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90,1,1,22);

	//Attivazione stak matrici modellazione
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	float xRef,yRef,zRef;
	xRef=0.0;
	yRef=0.0;
	zRef=0.0;


	gluLookAt(sin(anglexz)*asseXY, sin(angley)*asseXY, cos(anglexz)*asseZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 	glRotatef(-90,1.0,0.0,0.0);



	glPushMatrix();

		alberello();
	glPopMatrix();


    glPushMatrix();
  			glTranslatef(0.0,0.0,-1.6);
			neveterra();	
    glPopMatrix();

	glPushMatrix();
			glTranslatef(0.0,0.0,-1.0);
			cielo();	
	glPopMatrix();


	glutSwapBuffers();
	glFlush();
	glDisable(GL_DEPTH_TEST);
	glFinish();

}

int count= 0;

void animation() {
    if(count<11){
       flag1 = 0;
       flag2 = 1;
    }
    else if (count<22){
       flag1 = 1;
       flag2 = 0;
    }
    else if (count == 25)
        count = 0;
    
    count++;

    glutPostRedisplay();
  
}

void mySpecialInput(int key, int x, int y)
{
 switch(key)
        {
        case GLUT_KEY_UP:
            angley -= 0.1;
            asseXY = asseZ;
        break;
        case GLUT_KEY_DOWN:
            angley += 0.1;
            asseXY = asseZ;
        break;
        case GLUT_KEY_LEFT:
            anglexz -= 0.1;
            asseXY = asseZ;
        break;
        case GLUT_KEY_RIGHT:
            anglexz += 0.1;
            asseXY = asseZ;
        break;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
          
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        asseZ+=0.3;
 
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        asseZ-=0.3;

    glutPostRedisplay();
}

int main( int argc, char** argv){

    char *imageFileName0 = "albero2.rgba";
    char *imageFileName1 = "cielo.rgba";
	char *imageFileName2 = "tronco.rgba";
	char *imageFileName3 = "neve3.rgba";


	char *img0, *img1, *img2, *img3;

    img0 = imageFileName0;
	img1 = imageFileName1;
	img2 = imageFileName2;
	img3 = imageFileName3;


	unsigned *image0 ,*image1, *image2, *image3;
	GLsizei imageWidth, imageHeight, components;
	glutInit(&argc, argv);
    image0 = read_texture(img0, &imageWidth, &imageHeight, &components);
	image1 = read_texture(img1, &imageWidth, &imageHeight, &components);
	image2 = read_texture(img2, &imageWidth, &imageHeight, &components);
	image3 = read_texture(img3, &imageWidth, &imageHeight, &components);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowPosition( 300, 100 );
	glutInitWindowSize( 500, 500);
	glutInitWindowSize(width, height);
	glutCreateWindow( "albero" );
	initTexture( image0,image1,image2,image3, imageWidth, imageHeight );
	initgfx();
	glutDisplayFunc(drawScene);
	glutIdleFunc(animation);
	glutSpecialFunc(mySpecialInput);
    glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}