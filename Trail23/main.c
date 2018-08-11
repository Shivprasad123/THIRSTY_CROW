#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include <SOIL/SOIL.h>
#define FPS 10
float x1=120,x2=120,y1=100,y2=250,x3=170,y3=350;
float x4=170,y4=400,x5=250,y5=400,x6=250,y6=350;
float x7=300,y7=250;
float x8=300,y8=100;
double tx=800.0,ty=800.0;
float slope=0,b_line;
float up_x=500,up_y=20;
int lev=0;
int speed = 7000;
int st = 9;
int i;
int stx[9],sty[9];
int flag = 0;
int x=500,y=100;
int flag1=0,flag3=0,flag4=0,flag5=0,flag6=0,flag7=0,flag8=0,flag9=1,flag10=1,flag11=1;
int m1_x , m1_y;
void *font;
void *currentfont;
int fontType;
int in_about;
int enter;

int si,sj=0;
int GenRand(int lower , int upper , int count)
{
	int i;
	for (i = 0; i < count; i++) {
		int num = (rand() % (upper - lower + 1)) + lower;
		return num;
	}
}
void mouse(int button, int state, int x, int y)
{

}

void take(void){
    if(st>=0){
    flag7 =1;
    glPointSize(8.0);
     glBegin(GL_POINTS);
     glVertex2d(m1_x-8+tx,m1_y+7+ty);
     glEnd();
     }

}
float sx=150.0,sy=110.0;
void drop(void){
    flag1 = 1;
    flag7=0;
    flag8=1;
    sj++;
}
void myMenu(int id){
    switch(id){
        case 1:

            flag3=0;
            flag5=1;
            flag4=0;
        break;
        case 2:

            flag5=0;
            flag3=1;
        break;
    }
    glutPostRedisplay();
}

void dropSt(){
    if(flag8==1){
        float temp=sx;
        glPointSize(10.0);
        glBegin(GL_POINTS);
        for(si=0;si<sj;si++){
            glVertex2f(sx,sy);
            sx+= 15;
        }
        glPointSize(1.0);
        sx=temp;
        glEnd();
    }
}
void t_button(){
    flag1 = 0;
    st-=1;
    flag = 1;
    glutPostRedisplay();
}

void Automate(){

    if(flag3==1){
        speed = 7000;
        if(flag4==0){
            slope = (ty-up_y)/(tx-up_x);
            b_line = up_y-slope*up_x;
            flag4=1;
        }
        if(tx>up_x){
            if(ty>up_y){
                ty=slope*tx + b_line;
        }
        else{
            ty=up_y;
        }
        tx -=10;
        }else{
            glColor3b(1.0,1.0,1.0);
            if(flag9==1){
                t_button();
                up_x=x4;
                up_y=y5;
                flag9=0;
            }
        }
    }
}
void addImage() {

	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	GLuint tex_2d1 = SOIL_load_OGL_texture
	(
		"crow2.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_COMPRESS_TO_DXT
	);

	glBindTexture(GL_TEXTURE_2D, tex_2d1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(0.0,0.0);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(1200, 0.0);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(1200.0, 1200.0);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(0.0, 1200.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void box(){

    glColor3f(0.4,0.7,0.9);
    glBegin(GL_POLYGON);
    glVertex2d(0,999);
    glVertex2d(1200,999);
    glVertex2d(1200,600);
    glVertex2d(0,600);
    glEnd();
}
void hill(){
    glColor3f(0.6,0.3,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2d(0,600);
    glVertex2d(150,850);
    glVertex2d(300,600);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2d(200,600);
    glVertex2d(350,850);
    glVertex2d(500,600);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2d(200,600);
    glVertex2d(380,840);
    glVertex2d(500,600);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2d(400,600);
    glVertex2d(590,830);
    glVertex2d(750,600);
    glEnd();
}

void plotpixels(GLint h,GLint k, GLint x,GLint y)
{
    glPointSize(2.0);
	draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);
	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);
	glPointSize(1.0);
}
void draw_circle(GLint h, GLint k, GLint r)
{
	GLint d=1-r, x=0, y=r;
	while(y>x)
	{
		plotpixels(h,k,x,y);
		if(d<0) d+=2*x+3;
		else
		{
			d+=2*(x-y)+5;
			--y;
		}
		++x;
	}
	plotpixels(h,k,x,y);
}

void sun(){
int l;
	for(l=0;l<=35;l++)
	{
		glColor3f(1.0,0.5,0.1);
		draw_circle(253,710,l);
	}
}
int cm=0;
void cloud(){
int l;
float cr=1.0,cg=1.0,cb=1.0;
    for(l=0;l<=20;l++)
	{
		glColor3f(cr,cg,cb);
		draw_circle(160+cm,850,l);

	}


	for(l=0;l<=35;l++)
	{
		glColor3f(cr,cg,cb);
		draw_circle(200+cm,850,l);
		draw_circle(225+cm,850,l);
	}
	//cloud2
		for(l=0;l<=20;l++)
	{
		glColor3f(cr,cg,cb);
		draw_circle(370+cm,800,l);
    }
    for(l=0;l<=35;l++)
	{

		glColor3f(cr,cg,cb);
		draw_circle(410+cm,800,l);
		draw_circle(435+cm,800,l);
		draw_circle(470+cm,800,l);
	}

    for(l=0;l<=20;l++)
	{
		glColor3f(cr,cg,cb);
		draw_circle(500+cm,800,l);
    }
    //cloud1
    int sp=-500;
    for(l=0;l<=20;l++)
	{
		glColor3f(cr,cg,cb);
		draw_circle(370+cm+sp,800,l);
    }
    for(l=0;l<=35;l++)
	{

		glColor3f(cr,cg,cb);
		draw_circle(410+cm+sp,800,l);
		draw_circle(435+cm+sp,800,l);
		draw_circle(470+cm+sp,800,l);
	}

    for(l=0;l<=20;l++)
	{
		glColor3f(cr,cg,cb);
		draw_circle(500+cm+sp,800,l);
    }
	cm+=20;
	if(cm>959){
        cm=0;
	}
}

void disp(void)
{
    flag6 = 1;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2,1.0,0.3,1.0);
    glMatrixMode(GL_MODELVIEW);
    box();
    sun();
    cloud();
    hill();
    tree();
    crow();
    dropSt();

    glPointSize(1.0);
    	if(flag1==0){
   		if(flag==1){
           		take();
   		 }
    	}
    stone();
    scanfill();
    Automate();
    glFlush();
}

void pot(void){

    glColor3f(0.5,0.1,0.0);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glVertex2f(x5,y5);
    glVertex2f(x6,y6);
    glVertex2f(x7,y7);
    glVertex2f(x8,y8);
    glEnd();
    glLineWidth(1.0);
    glColor3f(0.0,0.0,0.0);
}

void edgedetect(float x1,float y1,float x2,float y2,int *le,int *re){
    float mx , x ,temp;
    int i;
    if((y2-y1)<0){
        temp = y1 ;
        y1=y2;
        y2=temp;
        temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if((y2-y1)!=0)
        mx = (x2-x1)/(y2-y1);
    else
        mx = x2 -x1;
    x= x1;

    for(i=y1;i<=y2;i++){
        if(x<(float)le[i])
            le[i] = (int) x;
        if(x > (float)re[i])
            re[i] = (int)x;
            x+=mx;
    }
}

int flag2=0;
void draw_pixel(int x,int y){
  //  glColor3f(0.6,0.5,1.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    if(flag2==0){
        	glFlush();
        	flag2=1;
    }
}

void scanfill(){
    int le[500] , re[500];
    int i ,y;
    for(i=0;i<500;i++){
        le[i] = 500;
        re[i] = 0;
    }
    edgedetect(x1,y1,x2,y2,le,re);
    edgedetect(x2,y2,x3,y3,le,re);
    edgedetect(x3,y3,x4,y4,le,re);
    edgedetect(x4,y4,x5,y5,le,re);
    edgedetect(x5,y5,x6,y6,le,re);
    edgedetect(x6,y6,x7,y7,le,re);
    edgedetect(x7,y7,x8,y8,le,re);
    edgedetect(x8,y8,x1,y1,le,re);

    for(y=0;y<lev+150;y++){
        if(le[y]<=re[y])
            for(i=(int)le[y]+2;i<(int)re[y]-1;i++){
                glColor3f(0.6,0.5,1.0);
                glPointSize(1.2);
                draw_pixel(i,y);
                glPointSize(1.0);
            }
    }
}

void stone(void){
    glColor3f(0.0,0.0,0.0);
    if(flag10==1){
       for(i=0;i<st;i++){
        	sty[i] = GenRand(20,120,1);
        	stx[i]= GenRand(500,700,1);
        }
        flag10=0;
    }
    int i=0;
    int temp = x;
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for(i=0;i<st;i++){
        glVertex2d(stx[i],sty[i]);
    }
    x = temp;
    glEnd();
    glPointSize(1.0);
}

void crow(void){
    home();
      glColor3f(0.5,0.5,0.5);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(32.0+tx,77.0+ty);
    glEnd();

    m1_x = 22.5,m1_y=67.5;

    glLineWidth(2.0);
    glBegin(GL_POLYGON);
    glVertex2f(22.5+tx,70.0+ty);
    glVertex2f(22.5+tx,80.0+ty);

     glVertex2f(12.5+tx,75.0+ty);
    glVertex2f(22.5+tx,75.0+ty);
     glVertex2f(12.5+tx,67.5+ty);
    glEnd();

    //glColor3f(0.1,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(22.5+tx,70.0+ty);
    glVertex2f(22.5+tx,80.0+ty);
    glVertex2f(30.0+tx,87.5+ty);
    glVertex2f(37.5+tx,87.5+ty);
    glVertex2f(45.0+tx,85.0+ty);
    glVertex2f(45.0+tx,82.5+ty);
    glVertex2f(50.0+tx,62.5+ty);

    glVertex2f(75.0+tx,37.5+ty);
    glVertex2f(105.0+tx,45.0+ty);
    glVertex2f(87.5+tx,25.0+ty);
    glVertex2f(55.0+tx,25.0+ty);
    glVertex2f(45.0+tx,30.0+ty);
    glVertex2f(40.0+tx,37.5+ty);
    glVertex2f(32.5+tx,62.5+ty);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(77.5+tx,25.0+ty);
    glVertex2f(77.5+tx,11.5+ty);
    glVertex2f(77.5+tx,11.5+ty);
    glVertex2f(70.0+tx,5.0+ty);
    glVertex2f(77.5+tx,11.5+ty);
    glVertex2f(85.0+tx,5.0+ty);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(62.5+tx,25.0+ty);
    glVertex2f(62.5+tx,11.5+ty);
    glVertex2f(62.5+tx,11.5+ty);
    glVertex2f(55.0+tx,5.0+ty);
    glVertex2f(62.5+tx,11.5+ty);
    glVertex2f(70.0+tx,5.0+ty);
    glEnd();

    //glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(50.0+tx,62.5+ty);
    glVertex2f(75.0+tx,37.5+ty);
    glVertex2f(105.0+tx,45.0+ty);
    glVertex2f(87.5+tx,60.0+ty);
    glVertex2f(95.0+tx,55.0+ty);
    glVertex2f(92.5+tx,62.5+ty);
    glEnd();

    //glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(92.5+tx,62.5+ty);
    glVertex2f(125.0+tx,55.0+ty);
    glVertex2f(150.0+tx,62.5+ty);
    glVertex2f(145.0+tx,55.0+ty);
    glVertex2f(150.0+tx,47.5+ty);
    glVertex2f(145.0+tx,45.0+ty);
    glVertex2f(150.0+tx,35.0+ty);
    glVertex2f(105.0+tx,45.0+ty);
    glVertex2f(87.5+tx,60.0+ty);
    glVertex2f(95.0+tx,55.0+ty);
    glEnd();

   // glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(50.0+tx,62.5+ty);
    glVertex2f(92.5+tx,62.5+ty);
    glVertex2f(120.0+tx,77.5+ty);
    glVertex2f(115.0+tx,80.0+ty);
    glVertex2f(122.5+tx,85.0+ty);
    glVertex2f(117.5+tx,90.0+ty);
    glVertex2f(125.0+tx,92.5+ty);
    glVertex2f(122.5+tx,95.0+ty);
    glVertex2f(132.5+tx,100.0+ty);
    glVertex2f(100.0+tx,95.0+ty);
    glEnd();
    //-----------
    glColor3f(0.1,0.1,0.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(32.0+tx,77.0+ty);
    glEnd();

    m1_x = 22.5,m1_y=67.5;

    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(22.5+tx,70.0+ty);
    glVertex2f(22.5+tx,80.0+ty);

     glVertex2f(12.5+tx,75.0+ty);
    glVertex2f(22.5+tx,75.0+ty);
     glVertex2f(12.5+tx,67.5+ty);
    glEnd();

    glColor3f(0.1,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(22.5+tx,70.0+ty);
    glVertex2f(22.5+tx,80.0+ty);
    glVertex2f(30.0+tx,87.5+ty);
    glVertex2f(37.5+tx,87.5+ty);
    glVertex2f(45.0+tx,85.0+ty);
    glVertex2f(45.0+tx,82.5+ty);
    glVertex2f(50.0+tx,62.5+ty);

    glVertex2f(75.0+tx,37.5+ty);
    glVertex2f(105.0+tx,45.0+ty);
    glVertex2f(87.5+tx,25.0+ty);
    glVertex2f(55.0+tx,25.0+ty);
    glVertex2f(45.0+tx,30.0+ty);
    glVertex2f(40.0+tx,37.5+ty);
    glVertex2f(32.5+tx,62.5+ty);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(77.5+tx,25.0+ty);
    glVertex2f(77.5+tx,11.5+ty);
    glVertex2f(77.5+tx,11.5+ty);
    glVertex2f(70.0+tx,5.0+ty);
    glVertex2f(77.5+tx,11.5+ty);
    glVertex2f(85.0+tx,5.0+ty);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(62.5+tx,25.0+ty);
    glVertex2f(62.5+tx,11.5+ty);
    glVertex2f(62.5+tx,11.5+ty);
    glVertex2f(55.0+tx,5.0+ty);
    glVertex2f(62.5+tx,11.5+ty);
    glVertex2f(70.0+tx,5.0+ty);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(50.0+tx,62.5+ty);
    glVertex2f(75.0+tx,37.5+ty);
    glVertex2f(105.0+tx,45.0+ty);
    glVertex2f(87.5+tx,60.0+ty);
    glVertex2f(95.0+tx,55.0+ty);
    glVertex2f(92.5+tx,62.5+ty);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(92.5+tx,62.5+ty);
    glVertex2f(125.0+tx,55.0+ty);
    glVertex2f(150.0+tx,62.5+ty);
    glVertex2f(145.0+tx,55.0+ty);
    glVertex2f(150.0+tx,47.5+ty);
    glVertex2f(145.0+tx,45.0+ty);
    glVertex2f(150.0+tx,35.0+ty);
    glVertex2f(105.0+tx,45.0+ty);
    glVertex2f(87.5+tx,60.0+ty);
    glVertex2f(95.0+tx,55.0+ty);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(50.0+tx,62.5+ty);
    glVertex2f(92.5+tx,62.5+ty);
    glVertex2f(120.0+tx,77.5+ty);
    glVertex2f(115.0+tx,80.0+ty);
    glVertex2f(122.5+tx,85.0+ty);
    glVertex2f(117.5+tx,90.0+ty);
    glVertex2f(125.0+tx,92.5+ty);
    glVertex2f(122.5+tx,95.0+ty);
    glVertex2f(132.5+tx,100.0+ty);
    glVertex2f(100.0+tx,95.0+ty);
    glEnd();
    glPointSize(1.0);
    glLineWidth(1.0);
    pot();

}

void home()
{
    glColor3f(1.3, 0.5, 0.8);
   glBegin(GL_POLYGON);
    glVertex2f(480.0, 655.0);
    glVertex2f(580.0, 655.0);
    glVertex2f(605.0, 617.5);
    glVertex2f(505.0, 617.5);
    glEnd();

    glColor3f(0.1, 0.5, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(480.0, 655.0);
    glVertex2f(455.0, 617.5);
    glVertex2f(505.0, 617.5);
    glEnd();

    glColor3f(0.7, 0.2, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(455.0, 617.5);
    glVertex2f(505.0, 617.5);
    glVertex2f(505.0, 555.0);
    glVertex2f(455.0, 555.0);
    glEnd();

    glColor3f(0.7, 0.2, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(467.5, 592.5);
    glVertex2f(492.5, 592.5);
    glVertex2f(492.5, 555.0);
    glVertex2f(467.5, 555.0);
    glEnd();

    glColor3f(0.3, 0.7, 0.9);
    glPointSize(15.0);
    glBegin(GL_POINTS);
    glVertex2f(472.5, 572.5);
    glEnd();

    glColor3f(0.1, 0.2, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(505.0, 617.5);
    glVertex2f(605, 617.5);
    glVertex2f(605.0, 555.0);
    glVertex2f(505.0, 555.0);
    glEnd();

    glColor3f(0.2, 0.4, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(512.5, 610.0);
    glVertex2f(542.5, 610.0);
    glVertex2f(542.5, 587.5);
    glVertex2f(512.5, 587.5);
    glEnd();

    glColor3f(0.1, 0.7, 0.5);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(527.5, 610.0);
    glVertex2f(527.5, 587.5);
    glVertex2f(512.0,597.0);
    glVertex2f(542.5, 597.0);
    glEnd();

   glPointSize(1.0);
    glLineWidth(1.0);

}
void tree(){
int ttx=320,tty=150;
 glColor3f(0.9,0.2,0.0);
glBegin(GL_POLYGON);
glVertex2f(350+ttx,325+tty);
glVertex2f(350+ttx,395+tty);
glVertex2f(365+ttx,395+tty);
glVertex2f(365+ttx,325+tty);
glEnd();

int l;
	for(l=0;l<=30;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(340+ttx,400+tty,l);
		draw_circle(380+ttx,400+tty,l);
	}

	for(l=0;l<=25;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(350+ttx,440+tty,l);
		draw_circle(370+ttx,440+tty,l);
	}

	for(l=0;l<=20;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(360+ttx,465+tty,l);
	}

	//Main treee
	glColor3f(0.6,0.3,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(999,0);
	glVertex2f(910,0);
	glVertex2f(910,550);
	glVertex2f(999,550);
	glEnd();
	for(l=0;l<=100;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(910,550,l);
	}
	for(l=0;l<=100;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(990,570,l);
	}

	for(l=0;l<=150;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(870,730,l);
	}

	for(l=0;l<=200;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(900,930,l);
	}
	for(l=0;l<=100;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(940,680,l);
	}
}

void init(void)
{
    glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);

	gluOrtho2D(0.0,999.0,0.0,999.0);
}
void process_Normal_Keys(int key, int x, int y)
{
    int i=0;
    if(flag5==1){
     	switch (key)
    	{

       		case 27 : break;
     		case 100:
            		  tx-=10;
              		  break;
       		case 102: tx+=10;
            		  break;
       		case 101: ty+=10;
             		  break;
       		case 103: ty-=10;
            		  break;
    	}
    }
}

void timer_callback(){
	glutPostRedisplay();
	glutTimerFunc(speed/FPS,timer_callback,0);
}

void drawstring(float x,float y,float z,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);
	for(c=string;*c!='\0';c++)
	{	glColor3f(0.0,1.0,1.0);
		glutBitmapCharacter(currentfont,*c);
	}
}

void setFont(void *font)
{
	currentfont=font;
}

void display_about(void)
{
	glClearColor(0.8,1.2,0.2,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	addImage();
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.0,1.0,0.0);
	drawstring(150.0,875.0,0.0,"MINI PROJECT FOR COMPUTER GRAPHICS &  VISUALIZATION LABORATERY");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.0,1.0,0.1);
	drawstring(380,765,0.0,"THIRSTY CROW");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
        glColor3f(0.0,1.0,1.0);
        drawstring(40,630,0,"BY:");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
        glColor3f(0.0,1.0,1.0);
        drawstring(90,580,0,"S SHIVARAJ (1PE15CS131)");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
        glColor3f(0.0,1.0,1.0);
        drawstring(90,525,0,"SHIVAPRASAD N (1PE15CS151)");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.0,0.0,1.0);
	drawstring(750,75,0.0,"LEFT CLICK for Menu");
	glFlush();
}

void options(int id)
{
	switch(id)
	{
		case 1:
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

			disp();
			break;

		case 2:
		       	exit(1);
	}
}

void disp1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(flag6==0){
		display_about();
	} else{
        	disp();
	}
	glFlush();
}

void key_bd(unsigned char key,int x,int y){
    switch(key){
        case 't':
                flag1 = 0;
                st-=1;
                flag = 1;
                glutPostRedisplay();
                break;
        case 'd':
        if(flag7==1){
                if(tx<x4+20 && tx>x4-20){
                    drop();
                    lev+=30;
                }
                break;
        }
        case 's':
                speed -=500;
                timer_callback();
                break;
    }
}

int main(int argc,char **argv)
{
    	printf("Press 't' for take stone\n");
    	printf("Press 'd' for drop stone\n");
    	printf("Press 's' for speed up\n");
    	srand(time(0));

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1200,900);
	glutCreateWindow("Welcome");
	init();
	glutDisplayFunc(disp1);
	glutFullScreen();
	glutMouseFunc(mouse);
    glutSpecialFunc( process_Normal_Keys );
    glutKeyboardFunc(key_bd);
    glutTimerFunc(0,timer_callback,0);
    glutCreateMenu(options);
    glutAddMenuEntry("Working of thirsty crow",1);
    glutAddMenuEntry("Quit",2);
    glutAttachMenu(GLUT_LEFT_BUTTON);
    int submenu=glutCreateMenu(myMenu);
    glutAddMenuEntry("Keyboard",1);
    glutAddMenuEntry("Automate",2);
    glutCreateMenu(myMenu);
    glutAddSubMenu("Start",submenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
