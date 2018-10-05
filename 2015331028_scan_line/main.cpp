#include<bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
/*
Anisur Rahman
2015331028
*/
int nodeNo;
double Ymin=INT_MAX,Ymax=INT_MIN;
struct edge{
    double xmin,ymin,xmax,ymax;
    double slopeInverse;
    edge(double a,double b,double c,double d,double e){
        slopeInverse=e;
        if(b>d){swap(b,d);swap(a,c);}
        xmin=a;xmax=c;ymin=b;ymax=d;
        Ymin=min(Ymin,ymin);
        Ymax=max(Ymax,ymax);
    }
    bool operator <(const edge &a) const{
        if(xmin!=a.xmin) return xmin<a.xmin;
        return xmax<a.xmax;
    }
};
vector<edge>v;
vector< pair<int,int> >nodes;
void scanLine(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<nodeNo;i++)
    {
        int j=(i+1)%nodeNo;
        int k=(j+1)%nodeNo;
        if(nodes[i].second==nodes[j].second) continue;

        double inv_m=(1.0*nodes[i].first-nodes[j].first)/(nodes[i].second-nodes[j].second);

        if(nodes[i].second<nodes[j].second && nodes[j].second<nodes[k].second){
            v.push_back(edge(nodes[i].first,nodes[i].second,nodes[j].first-inv_m,nodes[j].second-1,inv_m));
        }
        else if(nodes[i].second>nodes[j].second && nodes[j].second>nodes[k].second){
            v.push_back(edge(nodes[i].first,nodes[i].second,nodes[j].first+inv_m,nodes[j].second+1,inv_m));
        }
        else{
            v.push_back(edge(nodes[i].first,nodes[i].second,nodes[j].first,nodes[j].second,inv_m));
        }
    }
    sort(v.begin(),v.end());
    for(int y=ceil(Ymin);y<=floor(Ymax);y++){
        double sx=INT_MIN,ex=INT_MIN;
        for(int i=0;i<v.size();i++)
        {
            if(v[i].ymin<=y && y<=v[i].ymax){
                if(sx==INT_MIN){
                    sx=v[i].xmin;
                }
                else {
                    ex=v[i].xmin;
                    glBegin(GL_LINES);
                    glVertex2d(round(sx),y);
                    glVertex2d(round(ex),y);
                    glEnd();
                    sx=INT_MIN;
                }
                v[i].xmin+=v[i].slopeInverse;
            }
        }
    }
    glFlush();
}
void Init()
{
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    gluOrtho2D(-300.0,300.0 , -300.0 , 300.0);
}
int main(int argc, char **argv)
{
    cout<<"Number of Node?\n";
    cin>>nodeNo;
    cout<<"List the nodes:\n";
    for(int i=0;i<nodeNo;i++)
    {
        double x,y;
        cin>>x>>y;
        nodes.push_back(pair<int,int>(x,y));
    }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutCreateWindow("scan Line");
    Init();
    glutDisplayFunc(scanLine);
    glutMainLoop();

    return 0;
}
/**
4
0 -30
-30 0
0 30
30 0

6
20 -10
-10 30
30 50
70 20
50 -20
40 10

10
-16.4 -52.5
31 -31.5
5 20
47 68
99 36.6
85.4 148
-4 106
-92 139
-93.5 -16.6
-54 45

4
-10 -10
10 -10
10 10
-10 10
*/
