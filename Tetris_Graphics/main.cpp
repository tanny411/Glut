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

/**
Tetris Shapes (values in matrix)
0--empty
1--T
2--L
3--Z
4--I
5--O
*/
int shapes[6][3][3]={
    {
        0,0,0,0,0,0,0,0,0
    },
    {
        1,0,0,1,1,0,1,0,0
    },
    {
        1,0,0,1,0,0,1,1,0
    },
    {
        1,0,0,1,1,0,0,1,0
    },
    {
        1,0,0,1,0,0,1,0,0
    },
    {
        1,1,0,1,1,0,0,0,0
    }
};
void drawShape(int indx,int x,int y){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(shapes[indx][i][j]){
                glBegin(GL_LINE_LOOP);
                    glVertex2d(x+j*10,y+i*10);
                    glVertex2d(x+(j+1)*10,y+i*10);
                    glVertex2d(x+(j+1)*10,y+(i+1)*10);
                    glVertex2d(x+j*10,y+(i+1)*10);
                glEnd();
            }
        }
    }
}
static void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);

    drawShape(5,0,0);

    glutSwapBuffers();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(400,600);
    glutInitWindowPosition(10,10);

    glutCreateWindow("TETRIS");
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    gluOrtho2D(0,100,0,150);

    glutDisplayFunc(draw);
    glutMainLoop();

    return EXIT_SUCCESS;
}
