#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#define PI acos(-1)
#define fs first
#define sc second
using namespace std;
double theta,S;
vector<pair<int,int>>v;
int n,x,y;

static void translation(void){

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f(v[i].fs,v[i].sc);
        }
    glEnd();
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f(v[i].fs+x,v[i].sc+y);
        }
    glEnd();
    glutSwapBuffers();
}
static void rotation(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f(v[i].fs,v[i].sc);
        }
    glEnd();
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);
    theta=(theta*PI)/180.0;
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f((v[i].fs-x)*cos(theta)+(v[i].sc-y)*sin(theta)+x,-(v[i].fs-x)*sin(theta)+(v[i].sc-y)*cos(theta)+y);
        }
    glEnd();
    glutSwapBuffers();
}
static void scaling(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f(v[i].fs,v[i].sc);
        }
    glEnd();
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f((v[i].fs-x)*S+x,(v[i].sc-y)*S+y);
        }
    glEnd();
    glutSwapBuffers();
}
static void mirroring(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f(v[i].fs,v[i].sc);
        }
    glEnd();
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f(x*v[i].fs,y*v[i].sc);
        }
    glEnd();
    glutSwapBuffers();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Coordinate Geometry");
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    gluOrtho2D(-100.0,100.0,-100.0,100.0);

    v.clear();
    cout<<"Number of points: ";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        v.push_back(pair<int,int>(a,b));
    }
    cout<<"Chose operation: \n1.Translation\n2.Rotation\n3.Scaling\n4.Mirroring\n";
    int op;
    cin>>op;
    if(op==1){
        cout<<"Vector: ";
        cin>>x>>y;
        glutDisplayFunc(translation);
    }
    else if(op==2)
    {
        cout<<"Degrees: ";
        cin>>theta;
        cout<<"Point: ";
        cin>>x>>y;
        glutDisplayFunc(rotation);
    }
    else if(op==3)
    {
        cout<<"Point: ";
        cin>>x>>y;
        cout<<"Scale: ";
        cin>>S;
        glutDisplayFunc(scaling);
    }
    else{
        cout<<"Axis:x=1/y=2: ";
        cin>>op;
        if(op==1){ x=1; y=-1; }
        else { x=-1; y=1; }
        glutDisplayFunc(mirroring);
    }
    glutMainLoop();
    return EXIT_SUCCESS;
}
