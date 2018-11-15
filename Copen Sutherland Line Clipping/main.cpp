#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#define PI acos(-1)
#define fs first
#define sc second
#define pdd pair<double,double>
#define ppdd pair<pdd,pdd>
using namespace std;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
//Ractangle
int x_max,y_max,x_min,y_min;
//lines
vector<ppdd>v;
int n;

int koi(double x, double y)
{
    int ret=INSIDE;
    if(x<x_min) ret|=LEFT;
    else if(x>x_max)ret|=RIGHT;
    if(y<y_min)ret|=BOTTOM;
    else if(y>y_max)ret |= TOP;
    return ret;
}
ppdd sutherland(int i)
{
    double x1=v[i].fs.fs;
    double y1=v[i].fs.sc;
    double x2=v[i].sc.fs;
    double y2=v[i].sc.sc;

     // Compute region codes for P1, P2
    int code1 = koi(x1, y1);
    int code2 = koi(x2, y2);

    // Initialize line as outside the rectangular window
    bool accept = false;
    while (true)
    {
        if ((code1==0) && (code2==0))
        {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1&code2)
        {
            // If both endpoints are outside rectangle,in same region
            break;
        }
        else
        {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            double x, y;

            // At least one endpoint is outside the
            // rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP)
            {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                // point is below the rectangle
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = koi(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = koi(x2, y2);
            }
        }
    }
    if (accept) return ppdd({{x1,y1},{x2,y2}});
    else return ppdd({{1<<30,0},{0,0}});
}
static void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);
    //draw Rectangle
    glBegin(GL_LINE_LOOP);
        glVertex2d(x_min,y_min);
        glVertex2d(x_min,y_max);
        glVertex2d(x_max,y_max);
        glVertex2d(x_max,y_min);
    glEnd();

    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);

    for(int i=0;i<n;i++)
    {
        ppdd r=sutherland(i);
        if(r.fs.fs==1<<30) continue;
        glBegin(GL_LINE_LOOP);
            glVertex2d(r.fs.fs,r.fs.sc);
            glVertex2d(r.sc.fs,r.sc.sc);
        glEnd();
    }

    glutSwapBuffers();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(10,10);

    //Input
    cout<<"Input  Rectangle Coordinates\nLower Left:";
    cin>>x_min>>y_min;
    cout<<"Upper Right:";
    cin>>x_max>>y_max;
    cout<<"Give List of Line Segments:\n";
    cin>>n;
    v=vector<ppdd>(n);
    for(int i=0;i<n;i++) cin>>v[i].fs.fs>>v[i].fs.sc>>v[i].sc.fs>>v[i].sc.sc;

    //Call
    glutCreateWindow("Cohen Sutherland");
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    gluOrtho2D(-100.0,100.0,-100.0,100.0);
    glutDisplayFunc(draw);

    glutMainLoop();

    return EXIT_SUCCESS;
}
/*
4 4 10 8
3
5 5 7 7
7 9 11 4
1 5 4 1
*/
