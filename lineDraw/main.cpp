#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


/* Program entry point */

double X1, Y1, X2, Y2;

float round_value(float v)
{
    return floor(v + 0.5);
}

void SimpleLine(void)
{
    double dx=(X2-X1);
    double dy=(Y2-Y1);
    double tangent , b;
    float x=X1,y=Y1;

    /* Clears buffers to preset values */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Plot the points */
    glBegin(GL_POINTS);
    /* Plot the first point */
    glVertex2d(round_value(x), round_value(y));
    int k;

    if(dx == 0)
    {
        while(y<=Y2)
        {
            y += 1.0;
            glVertex2d(round_value(x), round_value(y));
        }
    }
    else if(dy == 0)
    {
        while(x<=X2)
        {
            x += 1.0;
            glVertex2d(round_value(x),round_value(y));
        }
    }
    else
    {
        tangent = dy/dx ;
        b = y - tangent * x;

        if(tangent >= 1)
        {
            while(x<=X2)
            {
                y+=1.0;
                x = (y - b)/tangent;

                glVertex2d(round_value(x),round_value(y));
            }
        }
        else
        {
            while(y<=Y2)
            {
                x+=1.0;
                y = tangent*x + b;

                glVertex2d(round_value(x),round_value(y));

            }
        }
    }

    glEnd();

    glFlush();
}

void Init()
{
    /* Set clear color to white */
    glClearColor(0.0,0.0,0.0,0);
    /* Set fill color to black */
    glColor3f(1.0,0.0,0.0);
    /* glViewport(0 , 0 , 640 , 480); */
    /* glMatrixMode(GL_PROJECTION); */
    /* glLoadIdentity(); */
    gluOrtho2D(-100.0 , 100.0 , -100.0 , 100.0);
}
int main(int argc, char **argv)
{
    printf("Enter two end points of the line to be drawn:\n");
    printf("\n************************************");
    printf("\nEnter Point1( X1 , Y1):\n");
    scanf("%lf%lf",&X1,&Y1);
    printf("\n************************************");
    printf("\nEnter Point1( X2 , Y2):\n");
    scanf("%lf%lf",&X2,&Y2);

    /* Initialise GLUT library */
    glutInit(&argc,argv);
    /* Set the initial display mode */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /* Set the initial window position and size */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(300,300);
    /* Create the window with title "DDA_Line" */
    glutCreateWindow("Simple Line Drawing Algorithm");
    /* Initialize drawing colors */
    Init();
    /* Call the displaying function */
    glutDisplayFunc(SimpleLine);
    /* Keep displaying untill the program is closed */
    glutMainLoop();

    return 0;
}
