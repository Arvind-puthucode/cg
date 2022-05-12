
/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <iostream>
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

using namespace std;
/* GLUT callback Handlers */
void init()
{   glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);

}
int xmin,xmax,ymin,ymax;
int points[20][2],n=0;
void drawwindow()
{   glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,1);
    glColor3d(1,0,0);
    glBegin(GL_LINES);
        glVertex2f(0,ymax);
        glVertex2f(640,ymax);

        glVertex2f(0,ymin);
        glVertex2f(640,ymin);

        glVertex2f(xmin,0);
        glVertex2f(xmin,480);

        glVertex2f(xmax,0);
        glVertex2f(xmax,480);
    glEnd();
    glFlush();
    cout<<"window"<<xmin<<" "<<xmax<<" "<<ymin<<" "<<ymax<<endl;
}
int N=0;
void drawline(int x1,int y1,int x2,int y2)
{   glColor3d(1,0,0);
    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
    glFlush();


}
void cohen()
{
    drawwindow();
    N=n-2;
    int regioncode1[4]={0,0,0,0};
    int regioncode2[4]={0,0,0,0};
    if(points[0][1]>ymax)
        regioncode1[0]=1;
    if(points[0][1]<ymin)
        regioncode1[1]=1;
    if(points[0][0]>xmax)
        regioncode1[2]=1;
    if(points[0][0]< xmin)
        regioncode1[3]=1;


    if(points[1][1]>ymax)
        regioncode2[0]=1;
    if(points[1][1]<ymin)
        regioncode2[1]=1;
    if(points[1][0]>xmax)
        regioncode2[2]=1;
    if(points[1][0]< xmin)
        regioncode2[3]=1;
    int ta=1;
    int ans=0;
    for(int i=0;i<4;i++)
    {   if (!(regioncode1[i]==regioncode2[i] && regioncode1[i]==0))
            ta=0;
        ans=ans|(regioncode1[i]&regioncode2[i]);
    }
    if(ta==1)
    {   drawline(points[0][0],points[0][1],points[1][0],points[1][1]);
        cout<<"trivial inside"<<endl;
        return ;
    }
    if(ans!=0)
    {
        // completely out
        cout<<"trivial reject"<<endl;
        return;
    }
    // partially inside

    int x1=points[0][0],y1=points[0][1],x2=points[1][0],y2=points[1][1];
    float m=(y2-y1)*1.0/(x2-x1);
    int x=0,y=0;
    //left boundary check
    if(regioncode1[3]==1 || regioncode2[3]==1)
    {   cout<<"left check:"<<endl;
        cout<<"x1,y1,x2,y2"<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

        x=xmin;
        y=y1+(xmin-x1)*m;
        cout<<x<<" "<<y<<endl;
        if(regioncode1[3]==1)
        {
            //x1,y1 is the left point
            x1=x;
            y1=y;
        }
        else
        {
            x2=x;
            y2=y;
        }

    }
    //at right check
    if(regioncode1[2]==1 || regioncode2[2]==1)
    {   cout<<"right check:"<<endl;
         cout<<"x1,y1,x2,y2"<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

        x=xmax;
        y=y1+(xmax-x1)*m;
        cout<<x<<","<<y<<endl;
        if(regioncode1[2]==1)
        {
            //x1,y1 is the right point
            x1=x;
            y1=y;
        }
        else
        {
            x2=x;
            y2=y;
        }
    }
    // at bottom check
    if(regioncode1[1]==1 ||regioncode2[1]==1)
    {   cout<<"down check:"<<endl;
         cout<<"x1,y1,x2,y2"<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

        y=ymin;
        x=x1+(ymin-y1)*1.0/m;
        cout<<x<<","<<y;
        if(regioncode1[1]==1)
        {
            //x1,y1 is the right point
            x1=x;
            y1=y;
        }
        else
        {
            x2=x;
            y2=y;
        }

    }
    // at top check

    if(regioncode1[0]==1 ||regioncode2[0]==1)
    {   cout<<"top check:"<<endl;
         cout<<"x1,y1,x2,y2"<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

        y=ymax;
        x=x1+(ymax-y1)*1.0/m;
        cout<<x<<","<<y<<endl;
        if(regioncode1[0]==1)
        {
            //x1,y1 is the right point
            x1=x;
            y1=y;
        }
        else
        {
            x2=x;
            y2=y;
        }

    }
    cout<<"x1,y1,x2,y2"<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    drawline(x1,y1,x2,y2);

}
void mousehandler(int button, int status,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON &&status==GLUT_DOWN)
    {   if(n==0)
        {
            xmin=x;
            ymin=480-y;
            n+=1;
        }
        else if(n==1)
        {
            xmax=x;
            ymax=480-y;
            n+=1;
        }
        else
        {
            points[n-2][0]=x;
            points[n-2][1]=480-y;
            n+=1;
        }
        cout<<xmin<<","<<xmax<<","<<ymin<<","<<ymax<<endl;

        if(n==2)
        {
            drawwindow();
        }
    }
    else if(button==GLUT_RIGHT_BUTTON &&status==GLUT_DOWN && n>2)
    {   // cohen sutherland
        cout<<"hi:"<<endl;
        cohen();

    }
}
static void display(void)
{   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
}
/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mousehandler);

    glutMainLoop();

    return EXIT_SUCCESS;
}
