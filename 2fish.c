#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include<time.h>
static GLuint texnames[2];

GLvoid initgfx( void ){
    glClearColor( 0.0, 0.0, 1.0, 1.0 );
}

GLvoid initTexture( unsigned *image,unsigned *image2, GLsizei imageWidth, GLsizei imageHeight ){
    GLsizei sWidth=256, sHeight=256;
    unsigned *sImage;
    unsigned *sImage2;
    sImage = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) ); 
    sImage2 = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );
    gluScaleImage( GL_RGBA, imageWidth, imageHeight,GL_UNSIGNED_BYTE, image,sWidth, sHeight, GL_UNSIGNED_BYTE, sImage );
    gluScaleImage( GL_RGBA, imageWidth, imageHeight,GL_UNSIGNED_BYTE, image2,sWidth, sHeight, GL_UNSIGNED_BYTE, sImage2 );
    glGenTextures(2, texnames);
    glBindTexture(GL_TEXTURE_2D, texnames[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexImage2D(GL_TEXTURE_2D, 0, 4, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, sImage);
    glBindTexture(GL_TEXTURE_2D, texnames[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, sImage2);
    //glTexImage2D(GL_TEXTURE_2D, 0, 4, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
    //glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    
    
    glEnable( GL_TEXTURE_2D );
}

GLvoid drawScene(void){
    float v0[3] = { -1.5, -1.0, 0.0 };
    float v1[3] = { 1.5, -1.0, 0.0 };
    float v2[3] = { 1.5, 1.0, 0.0 };
    float v3[3] = { -1.5, 1.0, 0.0 };
    float v4[3] = { 1.5, -1.0, 0.0};
    float v5[3] = { 4.5, -1.0, 0.0 };
    float v6[3] = { 4.5, 1.0, 0.0  };
    float v7[3] = { 1.5, 1.0, 0.0 };
    float t0[2] = { 0.0, 0.0 };
    float t1[2] = { 1.0, 0.0 };
    float t2[2] = { 1.0, 1.0 };
    float t3[2] = { 0.0, 1.0 };
    float t01[2] = { 0.5, 0.5 };
    float t11[2] = { 1.5, 0.5 };
    float t21[2] = { 1.5, 1.5 };
    float t31[2] = { 0.5, 1.5 };
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3f( 1.0, 1.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, texnames[0]);
    glColor3f(0,0,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    glBegin( GL_QUADS );
    glTexCoord2fv( t0 ); glVertex3fv( v0 );
    glTexCoord2fv( t1 ); glVertex3fv( v1 );
    glTexCoord2fv( t2 ); glVertex3fv( v2 );
    glTexCoord2fv( t3 ); glVertex3fv( v3 );
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texnames[1]); 
    glBegin( GL_QUADS );
    glTexCoord2fv( t0 ); glVertex3fv( v4 );
    glTexCoord2fv( t1 ); glVertex3fv( v5 );
    glTexCoord2fv( t2 ); glVertex3fv( v6 );
    glTexCoord2fv( t3 ); glVertex3fv( v7 );
    glEnd();
    glColor3f(0,0,0);
    glutSolidSphere(0.75,150, 100);
    glutSwapBuffers();
}


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


int county =0;
int countx = 0;
int countz = 0;

char *imageFileName = "fish.rgba";


void animate() {
    if(county<1000){
        glTranslatef(0,-0.001,-0.003);
        glRotatef(-0.035,0,1,0);
    }
    else if (county<2000){
        glTranslatef(0,0.001,0.003);
        glRotatef(0.035,0,1,0);
    }
    else if (county == 2000)
        county = 0;

    
    if(countx<8000){
        glTranslatef(0.001,0,0);
    }
    else if(countx<16000){
        glTranslatef(-0.001,0,0);
    }
    else if (countx == 16000){
        countx = 0;
        
    }
    
    county++;
    countx++;
  

    glutPostRedisplay();
  
}


int main( int argc, char *argv[] )
{
    char *imageFileName1 = "fish.rgba";
    char *imageFileName2 = "tronco.rgba";

    char *img1, *img2;

    img1 = imageFileName;
    img2 = imageFileName2;

    unsigned *image, *image2;
    GLsizei width=640, height=480;
    GLsizei imageWidth, imageHeight, components;
    GLdouble aspect;
    glutInit( &argc, argv );
    image = read_texture(img1, &imageWidth, &imageHeight, &components);
    image2 = read_texture(img2, &imageWidth, &imageHeight, &components);
    glutInitWindowSize( width, height );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutCreateWindow( argv[0] );
    initTexture( image,image2, imageWidth, imageHeight );
    initgfx();
    aspect = (GLdouble) width / (GLdouble) height;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, aspect, 1.0, 50.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( -2.5, 0.0, -12.0 );
    glutDisplayFunc( drawScene );
    glutIdleFunc(animate);
    glutMainLoop();
}


