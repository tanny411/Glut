#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#define PI acos(-1)
using namespace std;

static void circle(void){
    glClear(GL_COLOR_BUFFER_BIT);
    GLint circle_points=1000;
        glBegin(GL_LINE_LOOP);
            for(int i=0;i<circle_points;i++){
                double angle=2*PI*i/circle_points;
                glVertex2f(0.5*cos(angle), 0.5*sin(angle));
            }
        glEnd();
    glutSwapBuffers();
}
static void lineAlgo(double inx,double iny,double finx,double finy){
    int ix=round(inx);
    int iy=round(iny);
    int fx=round(finx);
    int fy=round(finy);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(ix,iy);

    if(finy-iny==0){///x-axis parallel

    }
    else if(finx-inx==0){///y-axis parallel

    }
    else if(finx-inx==finy-iny){///m=1

    }
    else{
        double m=(finy-iny)/(finx-inx);
//        glVertex2d();
    }

    glEnd();
    glutSwapBuffers();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glClearColor(0.0,0.0,0.0,1.0);
    glColor3f(1.0,0.0,0.0);
    gluOrtho2D(-100.0,100.0,-100.0,100.0);

    glutCreateWindow("Tanny Osthir");

    glutDisplayFunc(circle);

    glutMainLoop();

    return EXIT_SUCCESS;
}

