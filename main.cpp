#include<stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
float tx=50.0,ty=100;
float bx=50.0,by=0;
float rectWidth=5.0;
float botbeam=0;
float topbeam=0;
float vspeed=0.3;
float MoveY=0.0;//Arrow moving dy value
float vartopG;
float varbotG;

int limit=0,sci=1;float scf=-1; // for increment score score_int score_flag

char scs[20];
int status=1;
bool upKeyPressed;
bool mButtonPressed = false;
float mouseX, mouseY;

int logWidth = 100, logHeight = 100;
int phyWidth= 700;
int phyHeight= 700;
int centerX=logWidth/2;
int centerY=logHeight/2;

void printSome(char *str,int x,int y) {
glRasterPos2d(x,y);
for (int i=0;i<strlen(str);i++)
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
glFlush();
}

void SpecialKey(int key, int x, int y)
{
    if(key==GLUT_KEY_F1)
        {status=1; scf =-1;limit=0; sci=1; tx=50.0,ty=100;bx=50.0,by=0;rectWidth=5.0;botbeam=0;topbeam=0; MoveY=0.0;}
    glutPostRedisplay();
}
void mainMenu()
{
    glColor3f(0 , 0, 0);
    printSome("Flappy Arrow",43,95);
    glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
		glVertex2f(40 ,80);
		glVertex2f(40,70);
		glVertex2f(65 ,70);
		glVertex2f(65,80);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2f(40, 60);
		glVertex2f(40 ,50);
		glVertex2f(65 ,50);
		glVertex2f(65 ,60);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2f(40,40);
		glVertex2f(40 ,30);
		glVertex2f(65, 30);
		glVertex2f(65,40);
    glEnd();
        if(mouseX>=40 && mouseX<=60 && mouseY>=70&& mouseY<=80){  // start game
		glColor3f(0 ,0 ,1) ;
		if(mButtonPressed)
        {
            status=2;
            printf("Start clicked");
			mButtonPressed = false;
		}
	} else
		glColor3f(0 , 0, 0);
        printSome("Start",45,75);

	if(mouseX>=40 && mouseX<=60 && mouseY>=50 && mouseY<=60) {
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){
            printf("high Score pressed\n");
			mButtonPressed = false;
		}
	} else
		glColor3f(0 , 0, 0);
        printSome("High Score",45,55);

	if(mouseX>=40 && mouseX<=60 && mouseY>=30 && mouseY<=40){
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){
			mButtonPressed = false;
			exit(0);
		}
	}
	else
		glColor3f(0 , 0, 0);
        printSome("Exit",45,35);
	glutPostRedisplay();
}
void init()
{

	glClearColor(0.49,0.73,0.91,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0,logWidth,0,logHeight);
	glMatrixMode(GL_MODELVIEW);
}
void passiveMouse(int x,int y){
mouseX = x;
mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
mouseY = phyHeight - y;
mouseY=0.5+1.0*mouseY*logHeight/phyHeight;
glutPostRedisplay();

}
void mouseClick(int btn, int state, int x, int y)
{
if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
mouseX = x; mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
mouseY = phyHeight - y;mouseY=0.5+1.0*mouseY*logHeight/phyHeight;
mButtonPressed = true;

}
else {
    mButtonPressed = false;
	glutPostRedisplay();
}
}

void up(void)
{
if( status == 2)
{
MoveY+=0.9;
limit++;
glutPostRedisplay();

}

}

void down(void)
{
if(status==2)
{
MoveY-=0.9;
limit--;

glutPostRedisplay();
}

}
void KeyboardUp( unsigned char key,int x,int y)
{
switch( key ) {
case ' ':
glutIdleFunc(down);
upKeyPressed = false;
}
}
void keys(unsigned char key,int x,int y)
{
switch (key)
{

case ' ':
glutIdleFunc(up);
upKeyPressed = true;
break;

}
}


int drawBarrier(){

if(bx<-rectWidth && tx<-rectWidth)
{
    scf+=1;
tx=50;
bx=50;

botbeam=((rand()%50)+25);
topbeam=(ty-botbeam-25) ;
}
else
tx-=vspeed;
bx-=vspeed;
glPushMatrix();
glTranslatef(bx,-MoveY,0.0);

glColor3f(1.0,0.0,0.0);
int vartop=ty-topbeam;////////////////////////////////////////
vartopG = vartop;
int varbot=by+botbeam; /////////////////////////////////////
varbotG = varbot;
glRectf(bx,by,bx+rectWidth,varbot);//bottom
glColor3f(0.0,1.0,0.0);
glRectf(tx,ty,tx+rectWidth,vartop);//top
glPopMatrix();
}
void drawArrow()
{

glTranslatef(0.0,MoveY,0.0);
glColor3f(1.0,0.5,0.55);
glRectf(0,45,10,55);
glBegin(GL_TRIANGLES);
glVertex2f(10,55);
glVertex2f(15,50);
glVertex2f(10,45);
glEnd();

}

int gameOver(){

glColor3f(0.0,0.0,1.0);
glRectf(0.0,0.0,100.0,100.0);
printSome("Game over",40,70);
glColor3f(1.0,1.0,1.0);
printSome("YOU",25,58);
printSome("scored",45,58);
printSome(scs,70,58);
glFlush();
glColor3f(1.0,0.0,0.0);
printSome("Score:",1,95);
printSome(scs,10,95);


}
void Collision(void)
{
    if(limit==50|| limit==-50)
{
    status=3;
}
    if(bx<7 && bx+rectWidth>7 && 50+MoveY <100 && 50+MoveY > vartopG)
    {
        status=3;
    }
    if(bx<7 && bx+rectWidth>7 && 50+MoveY >0 && 50+MoveY < varbotG)
    {
        status=3;
    }

    if(bx<2 && bx+rectWidth>2 && 55+MoveY <100 && 55+MoveY > vartopG)
    {
        status=3;
    }

    if(bx<2 && bx+rectWidth>2 && 45+MoveY >0 && 45+MoveY < varbotG)
    {
        status=3;
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,logWidth,0,logHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
if(status==1)
mainMenu();

if(status==2)
{
    sci=(int)scf;
    sprintf(scs,"%d",sci);
    glColor3f(1.0,0.0,0.0);
    if(scf>=0)
    {
    printSome(scs,10,95);
    }
Collision();
drawArrow();
drawBarrier();
}

if(status ==3)
{
    gameOver();
}
	glFlush();
	glutSwapBuffers();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(phyWidth,phyHeight);
    glutCreateWindow("Arrow");
    init();
    glutKeyboardFunc(keys);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(SpecialKey);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(passiveMouse);
    glutDisplayFunc(display);
    glutMainLoop();
}
