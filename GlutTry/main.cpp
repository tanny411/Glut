#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#define PI acos(-1)
using namespace std;
double inx,finx,iny,finy;
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
static void simpleLineAlgo(void){
    int ix=round(inx);
    int iy=round(iny);
    int fx=round(finx);
    int fy=round(finy);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(ix,iy);

    if(finy-iny==0){///x-axis parallel
        while(ix<=fx){
            ix++;
            glVertex2d(ix,iy);
        }
    }
    else if(finx-inx==0){///y-axis parallel
        while(iy<=fy){
            iy++;
            glVertex2d(ix,iy);
        }
    }
    else if(finx-inx==finy-iny){///m=1
        while(iy<=fy){
            iy++;
            ix++;
            glVertex2d(ix,iy);
        }
    }
    else{
        double m=(finy-iny)/(finx-inx);
        double b=iny-m*ix;
        if(m>1){
            while(ix<=fx)
            {
                ix++;
                iy=round(m*ix+b);
                glVertex2d(ix,iy);
            }
        }
        else{
            while(iy<=fy)
            {
                iy++;
                ix=round( (iy-b)/m );
                glVertex2d(ix,iy);
            }
        }
    }

    glEnd();
    glutSwapBuffers();
}
static void DDA(void)
{
    int ix=round(inx);
    int iy=round(iny);
    int fx=round(finx);
    int fy=round(finy);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(ix,iy);

    if(finy-iny==0){///x-axis parallel
        while(ix<=fx){
            ix++;
            glVertex2d(ix,iy);
        }
    }
    else if(finx-inx==0){///y-axis parallel
        while(iy<=fy){
            iy++;
            glVertex2d(ix,iy);
        }
    }
    else if(finx-inx==finy-iny){///m=1
        while(iy<=fy){
            iy++;
            ix++;
            glVertex2d(ix,iy);
        }
    }
    else{
        double m=(finy-iny)/(finx-inx);
        double b=iny-m*ix;
        if(m>1){
            while(ix<=fx)
            {
                ix++;
                iy=round(iy+m);
                glVertex2d(ix,iy);
            }
        }
        else{
            while(iy<=fy)
            {
                iy++;
                ix=round(ix+1/m);
                glVertex2d(ix,iy);
            }
        }
    }

    glEnd();
    glutSwapBuffers();
}
static void Bresenhams(void)
{
    int ix=round(inx);
    int iy=round(iny);
    int fx=round(finx);
    int fy=round(finy);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(ix,iy);

    if(finy-iny==0){///x-axis parallel
        while(ix<=fx){
            ix++;
            glVertex2d(ix,iy);
        }
    }
    else if(finx-inx==0){///y-axis parallel
        while(iy<=fy){
            iy++;
            glVertex2d(ix,iy);
        }
    }
    else if(finx-inx==finy-iny){///m=1
        while(iy<=fy){
            iy++;
            ix++;
            glVertex2d(ix,iy);
        }
    }
    else{
        double dx=finx-inx;
        double dy=finy-iny;
        double m=dy/dx;
        if(abs(m)>1){
            swap(ix,iy);
            swap(fx,fy);
            swap(dx,dy);
        }
        double d=dy+dy-dx;
        while(ix<=fx){
            ix++;
            if(d>=0){
                d+=dy+dy-dx-dx;
                if(m>0) iy++;
                else iy--;
            }
            else{
                d+=dy+dy;
            }
            if(abs(m)>1) glVertex2d(iy,ix);
            else glVertex2d(ix,iy);
        }
    }

    glEnd();
    glutSwapBuffers();
}
int main(int argc, char *argv[])
{
    cin>>inx>>iny>>finx>>finy;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(10,10);

    glutCreateWindow("Tanny");

    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    gluOrtho2D(-100.0,100.0,-100.0,100.0);

    glutDisplayFunc(Bresenhams);

    glutMainLoop();

    return EXIT_SUCCESS;
}

