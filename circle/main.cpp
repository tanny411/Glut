#include<bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
double X,Y,R;
void plot(double x,double y)
{
  x=round(x);
  y=round(y);
  glVertex2d(x+X,y+Y);
  glVertex2d(y+X,x+Y);
  glVertex2d(x+X,-y+Y);
  glVertex2d(y+X,-x+Y);
  glVertex2d(-x+X,-y+Y);
  glVertex2d(-y+X,-x+Y);
  glVertex2d(-y+X,x+Y);
  glVertex2d(-x+X,y+Y);
}
void SimpleCircle(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    double x=0;
    double y=R;
    while(x<=y){
      y=sqrt(R*R-x*x);
      plot(x,y);
      x=x+1.0;
    }
    glEnd();
    glFlush();
}

void trigonometric(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
     double theta=0,x,y;
     double en=(acos(0.0))/2;
     while(theta<=en){
        x=R*sin(theta);
        y=R*cos(theta);
        plot(x,y);
        theta=theta+0.05;
     }
     glEnd();
     glFlush();
}

void bresenhams(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    double x=0, y=R;
    plot(x,y);
    double d=3-2*R;
    while (x<=y)
    {
        x++;
        if(d>0)
        {
            y--;
            d+=4*(x-y)+10;
        }
        else d+=4*x+6;
        plot(x,y);
    }
    glEnd();
    glFlush();
}

void midpoint(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    double x=0, y=R;
    plot(x,y);
    double d=1-R;
    while (x<=y)
    {
        x++;
        if(d<0){
            d+=2*x+1;
        }
        else {
          y--;
          d+=2*x-2*y+1;
        }
        plot(x,y);
    }
    glEnd();
    glFlush();
}

void Init()
{
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    gluOrtho2D(-100.0 , 100.0 , -100.0 , 100.0);
}
int main(int argc, char **argv)
{
    printf("Enter the center of the circle to be drawn and Radius:\n");
    cin>>X>>Y>>R;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Circle Drawing algorithms");
    Init();
    glutDisplayFunc(midpoint);
    glutMainLoop();

    return 0;
}
