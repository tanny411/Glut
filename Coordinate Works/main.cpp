#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#define PI acos(-1)
#define pii pair<int,int>
#define fs first
#define sc second
using namespace std;

///Aisha Khatun
///2015331042

int n,x,y;
double th;
vector<pii>pt;

static void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINE_LOOP);
            for(int i=0;i<n;i++){
                glVertex2f(pt[i].fs,pt[i].sc);
            }
        glEnd();
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(0.0,0.0,1.0);
}
static void translation(void){
    draw();
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f(pt[i].fs+x,pt[i].sc+y);
        }
    glEnd();
    glutSwapBuffers();
}
static void rotation(void){
    draw();
    th=th*PI/180.0;
    double X,Y;
    for(int i=0;i<n;i++){
        pt[i].fs-=x;
        pt[i].sc-=y;
    }
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            X=pt[i].fs*cos(th)+pt[i].sc*sin(th);
            Y=-pt[i].fs*sin(th)+pt[i].sc*cos(th);
            glVertex2f(X+x,Y+y);
        }
    glEnd();
    glutSwapBuffers();
}
static void scaling(void){
    draw();
    for(int i=0;i<n;i++){
        pt[i].fs-=x;
        pt[i].sc-=y;
    }
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f(pt[i].fs*th+x,pt[i].sc*th+y);
        }
    glEnd();
    glutSwapBuffers();
}
static void mirroring(void){
    draw();
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<n;i++){
            glVertex2f(x*pt[i].fs,y*pt[i].sc);
        }
    glEnd();
    glutSwapBuffers();
}
int main(int argc, char *argv[])
{
    cout<<"How Many Points?\n";
    cin>>n;
    pt=vector<pii>(n);
    for(int i=0;i<n;i++)
    {
        cin>>pt[i].fs>>pt[i].sc;
    }
    cout<<"Which operation?\n1.Translation\n2.Rotation\n3.Scaling\n4.Mirroring\n";
    cin>>x;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(10,10);

    glutCreateWindow("Coordinate Transformation");

    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    gluOrtho2D(-100.0,100.0,-100.0,100.0);

    if(x==1){
        cout<<"Provide the translation Vector\n";
        cin>>x>>y;
        glutDisplayFunc(translation);
    }
    else if(x==2)
    {
        cout<<"Rotate by how many degrees?\n";
        cin>>th;
        cout<<"WRT which point?\n";
        cin>>x>>y;
        glutDisplayFunc(rotation);
    }
    else if(x==3)
    {
        cout<<"WRT which point?\n";
        cin>>x>>y;
        cout<<"Scaling factor?\n";
        cin>>th;
        glutDisplayFunc(scaling);
    }
    else{
        cout<<"WRT which axis?x/y:\n";
        char p;
        while(cin>>p)
        {
            if(tolower(p)=='x'){
                x=1;y=-1;
                glutDisplayFunc(mirroring);
            }
            else if(tolower(p)=='y'){
                x=-1;y=1;
                glutDisplayFunc(mirroring);
            }
            else {
                cout<<"Invalid character! Try again:\n";
                continue;
            }
            break;
        }
    }

    glutMainLoop();

    return EXIT_SUCCESS;
}
/**
3
1 1 10 20 30 4
*/
