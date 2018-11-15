#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

int n;
double xmin,xmax,ymin,ymax;

struct Line{
    double firstx,firsty;
    double secondx,secondy;

}lines[1000];

double dist(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int firstcode[1000],secondcode[1000];

void Init()
{
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1,1,1);
    gluOrtho2D(-300.0,300.0,-300.0,300.0);
}

int mask(double x,double y)
{
    int mask = 0;
    if(ymax<y) mask|=(1<<3);
    if(ymin>y) mask|=(1<<2);
    if(xmax<x) mask|=(1<<1);
    if(xmin>x) mask|=(1<<0);
    return mask;
}

double tolerance = 1e-5;
void midpoint(double x1,double y1,double x2,double y2)
{
    int mask1 = mask(x1,y1),mask2 = mask(x2,y2);
if(mask1==0 && mask2==0)
    {
        glClearColor(0.0,0.0,0.0,0);
        glColor3f(1,0,0);
        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glEnd();
        glFlush();
        return;
    }
    else if(mask1 & mask2) return;
    else if(dist(x1,y1,x2,y2)<=tolerance) return;

    double xmid = (x1+x2)/2.0,ymid = (y1+y2)/2.0;

    midpoint(x1,y1,xmid,ymid);
    midpoint(xmid,ymid,x2,y2);

    return;
}

void drawboard() {
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();
    glFlush();
}

void drawpolygon() {
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    for(int i=0; i<n; i++) {
        glVertex2f(lines[i].firstx , lines[i].firsty );
        glVertex2f(lines[i].secondx , lines[i].secondy);
    }
    glEnd();
    glFlush();
}

void midpoint()
{
    drawboard();
    drawpolygon();


    for(int i=0;i<n;i++)
    {
        midpoint(lines[i].firstx,lines[i].firsty,lines[i].secondx,lines[i].secondy);
    }
}

//30 70 70 30

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);

    cout << "Enter the coordinate of lower left corner of the viewport (x y) : ";
    cin >> xmin >> ymin;

    cout << "Enter the coordinate of upper right corner of the viewport (x y) : ";
    cin >> xmax >> ymax;

    cout << "Enter Number of lines in the polygon: ";
    cin >> n;

    for(int i=0;i<n;i++)
    {
        cout << "Enter the coordinates of endpoints of line " << i+1 << " (x1 y1 x2 y2): ";
        cin >> lines[i].firstx >> lines[i].firsty >> lines[i].secondx >> lines[i].secondy;
        firstcode[i] = mask(lines[i].firstx,lines[i].firsty);
        secondcode[i] = mask(lines[i].secondx,lines[i].secondy);
    }



    glutCreateWindow("Line Clipping - (Midpoint)");
    Init();
    glutDisplayFunc(midpoint);
    glutMainLoop();

    return 0;
}
