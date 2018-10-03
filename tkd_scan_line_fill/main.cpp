#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

struct point {
    public:
    double x, y;
    point(double x, double y) :x(x), y(y) {}

    bool operator<(point p) {
        pair<double, double> own(x, y), others(p.x, p.y);
        return own<others;
    }
};

struct edge {
    public:
    point start, finish;

    edge(point start, point finish) :start(start), finish(finish) {}

    bool is_y_inside(double y) {
        double ymin = min(start.y, finish.y);
        double ymax = max(start.y, finish.y);

        return (y>=ymin && y<=ymax);
    }

    double find_x(double y) {
        return start.x + (double) (finish.x - start.x)/(finish.y - start.y) * (y - start.y);
    }
};

/* Program entry point */
int N;
vector< point > points;
vector<edge> edges;
double ymin = INT_MAX, ymax = INT_MIN;

void generateEdges(vector<point> points) {
    for(int i=0; i<points.size(); i++) {
        point start = points[i];
        point finish = points[(i+1)%points.size()];
        point nextpoint = points[(i+2)%points.size()];

        if(start.y==finish.y) continue;

        edge e(start, finish);

        if(start.y<finish.y && finish.y < nextpoint.y) {
            double newfinish_y = finish.y-1;
            point newfinish = point(e.find_x(newfinish_y), newfinish_y);
            e = edge(start, newfinish);
        }
        else if(start.y>finish.y && finish.y>nextpoint.y) {
            double newfinish_y = finish.y+1;
            point newfinish = point(e.find_x(newfinish_y), newfinish_y);
            e = edge(start, newfinish);
        }
        edges.push_back(e);
    }
}

void scanLine(void)
{
    /* Clears buffers to preset values */
    glClear(GL_COLOR_BUFFER_BIT);

    //plot circumference
    glBegin(GL_LINE_LOOP);
    for(auto p: points) {
        glVertex2f(p.x, p.y);
    }
    glEnd();



    for(int y = ceil(ymin); y<=floor(ymax); y++) {
//        cout << y << endl;
        vector<point> intersections;

        for(edge e: edges) {
            if(e.is_y_inside(y)) {
                double x = e.find_x(y);
                intersections.push_back({x, y});
            }
        }

        sort(intersections.begin(), intersections.end());

        cout << y << " --> intersections: " << intersections.size() << endl;
        for(int i=0; i<intersections.size(); i+=2) {
            point start = intersections[i], finish = intersections[i+1];
            cout << start.x << "," << start.y << " --- " << finish.x << ","<<finish.y<< endl;
            glBegin(GL_LINES);
            glVertex2f(round(start.x), round(start.y));
            glVertex2f(round(finish.x), round(finish.y));
            glEnd();
            glFlush();
        }
    }




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
    gluOrtho2D(-150.0 , 150.0 , -150.0 , 150.0);
}

int main(int argc, char **argv)
{
    printf("Enter the number of vertexes in the polygon:\n");
    cin >> N;

    for(int i=0; i<N; i++) {
        printf("Enter the position of vertex %d: ", i);
        double x, y;
        cin >> x >> y;
        points.push_back({x, y});
        ymin = min(ymin, y);
        ymax = max(ymax, y);
    }

    //region fill
    generateEdges(points);

    cout << "non horizontal edges: " << edges.size() << endl;

    /* Initialise GLUT library */
    glutInit(&argc,argv);
    /* Set the initial display mode */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /* Set the initial window position and size */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(300,300);
    /* Create the window with title "DDA_Line" */
    glutCreateWindow("Scan Line Algorithm for region filling");
    /* Initialize drawing colors */
    Init();
    /* Call the displaying function */
    glutDisplayFunc(scanLine);

    /* Keep displaying untill the program is closed */
    glutMainLoop();

    return 0;
}
