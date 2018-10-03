/**
Aisha Khatun
2015331042
**/


#include<bits/stdc++.h>
#define pii pair<int,int>
#define pdd pair<double,double>
#define pb push_back
#define fs first
#define sc second
#include <GL/glut.h>
using namespace std;
int nodeNo;
double ymin=1<<30,ymax=-1<<30;
struct edge{
    double x1,y1,x2,y2; ///1=min y (x,y);2=max y (x,y)
    double slopeInverse;
    edge(double a,double b,double c,double d,double e){
        slopeInverse=e;
        if(b>d){swap(b,d);swap(a,c);}
        x1=a;x2=c;y1=b;y2=d;
        ymin=min(ymin,y1);
        ymax=max(ymax,y2);
    }
    bool operator <(const edge &a) const{
        if(x1!=a.x1) return x1<a.x1;
        return x2<a.x2;
    }
};
vector<edge>v;
vector<pii>nodes;
void scanLine(void)
{
    for(int i=0;i<nodeNo;i++)
    {
        int j=(i+1)%nodeNo;
        int k=(j+1)%nodeNo;
        if(nodes[i].sc==nodes[j].sc) continue;
        double inv_m=(1.0*nodes[i].fs-nodes[j].fs)/(nodes[i].sc-nodes[j].sc);
        if(nodes[i].sc<nodes[j].sc && nodes[j].sc<nodes[k].sc) v.pb(edge(nodes[i].fs,nodes[i].sc,nodes[j].fs-inv_m,nodes[j].sc-1,inv_m));
        else if(nodes[i].sc>nodes[j].sc && nodes[j].sc>nodes[k].sc) v.pb(edge(nodes[i].fs,nodes[i].sc,nodes[j].fs+inv_m,nodes[j].sc+1,inv_m));
        else v.pb(edge(nodes[i].fs,nodes[i].sc,nodes[j].fs,nodes[j].sc,inv_m));
    }
    glClear(GL_COLOR_BUFFER_BIT);
    sort(v.begin(),v.end());
//    cout<<"edge list size "<<v.size()<<endl;
//    for(int i=0;i<v.size();i++)
//    {
//        cout<<v[i].x1<<" "<<v[i].y1<<"    "<<v[i].x2<<" "<<v[i].y2<<endl;
//    }
    for(int y=ceil(ymin);y<=floor(ymax);y++){
        double sx=-1<<30,ex=-1<<30; ///start and end x
        for(int i=0;i<v.size();i++)
        {
            if(v[i].y1<=y && y<=v[i].y2){
                if(sx==-1<<30){
                    sx=v[i].x1;
                }
                else {
                    ex=v[i].x1;
                    glBegin(GL_LINES);
                    glVertex2d(round(sx),y);
                    glVertex2d(round(ex),y);
                    glEnd();
                    sx=-1<<30;
                }
                v[i].x1+=v[i].slopeInverse;
            }
        }
    }
    glFlush();
}
void Init()
{
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,0.0,0.0);
    gluOrtho2D(-300.0 , 300.0 , -300.0 , 300.0);
}
int main(int argc, char **argv)
{
    ///Input must be in clockwise direction
    cout<<"Enter the Number of nodes followed by the list of nodes:\n";
    cin>>nodeNo;
    for(int i=0;i<nodeNo;i++)
    {
        double x,y;
        cin>>x>>y;
        nodes.pb(pdd(x,y));
    }

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutCreateWindow("Scan Line Region Filling");
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
