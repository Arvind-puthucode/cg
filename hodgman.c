
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

int n=0,poly[20][2];
int xmin,xmax,ymin,ymax;
void init(){
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

static void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFlush();
}

int x_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4){
	float num = (x1*y2 - y1*x2) * (x3-x4) -
			(x1-x2) * (x3*y4 - y3*x4);
	float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
	return num*1.0/den;
}

int y_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4){
	int num = (x1*y2 - y1*x2) * (y3-y4) -
			(y1-y2) * (x3*y4 - y3*x4);
	int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
	return num/den;
}

void windowDraw(){
    glColor3d(0,1,1);

    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);

    glEnd();

    glFlush();
}
void polygonDraw(int c,int poly[20][2],int l){
    glClear(GL_COLOR_BUFFER_BIT);
    windowDraw();
    if(c==0){
        glColor3d(1,0,0);
    }
    else if(c==1){
        glColor3d(0,1,0);
    }
    cout<<"polygon draw:";
    glBegin(GL_POLYGON);
        for(int i=0;i<l;i++){
            glVertex2f(poly[i][0],poly[i][1]);
            cout<<poly[i][0]<<","<<poly[i][1]<<endl;
        }
    glEnd();

    glFlush();
}

int checkp(int p1[2],int p2[2],int boundary)
{   //left
 //   cout<<"p1"<<p1[0]<<" "<<p1[1]<<endl;

  //  cout<<"p2"<<p2[0]<<" "<<p2[1]<<endl;

  //  cout<<"xmin"<<xmin<<" "<<ymin<<endl;
    if(boundary==0)
    {   //out-in
        if(p1[0]<xmin && p2[0]>=xmin)
            return 0;
        //in-in
        else if(p1[0]>=xmin &&p2[0]>=xmin)
            return 1;
        // in-out
        else if(p1[0]>=xmin &&p2[0]<xmin)
            return 2;
        //out-out
        else
            return 3;
    }
//right
    else if(boundary==1)
    {   //out-in
        if(p1[0]>xmax && p2[0]<=xmax)
            return 0;
        //in-in
        else if(p1[0]<=xmax &&p2[0]<=xmax)
            return 1;
        // in-out
        else if(p1[0]<=xmax &&p2[0]>xmin)
            return 2;
        //out-out
        else
            return 3;
    }
//bottom
    else if(boundary==2)
    {   //out-in
        if(p1[1]<ymin && p2[1]>=ymin)
            return 0;
        //in-in
        else if(p1[1]>=ymin &&p2[1]>=ymin)
            return 1;
        // in-out
        else if(p1[1]>=ymin &&p2[1]<ymin)
            return 2;
        //out-out
        else
            return 3;
    }
//up

    else if(boundary==3)
    {   //out-in
        if(p1[1]>ymax && p2[1]<=ymax)
            return 0;
        //in-in
        else if(p1[1]<=ymax &&p2[1]<=ymax)
            return 1;
        // in-out
        else if(p1[1]<=ymax &&p2[1]>ymax)
            return 2;
        //out-out
        else
            return 3;
    }

}

int lcp[20][2],rcp[20][2],bcp[20][2],tcp[20][2];
int l1=0;
void fn(int boundary,int a,int b,int c,int d)
{   l1=0;
   // cout<<"n is "<<n<<endl;
   // cout<<"xmin xmax ymin ymax"<<xmin<<" "<<xmax<<" "<<ymin<<" "<<ymax<<endl;
   // cout<<"boundary is"<<boundary<<endl<<endl;
    for(int i=0;i<n;i++)
    {   int ch=checkp(poly[i%n],poly[(i+1)%n],boundary);
        if(ch==0)
        { //  cout<<"out in"<<l1<<endl;
            if(boundary==0)
            { //  cout<<"boundary and lcp"<<boundary<<" "<<xmin<<endl;
                lcp[l1][0]=xmin;
                lcp[l1][1]=y_intersect(poly[i%n][0],poly[i%n][1],poly[(i+1)%n][0],poly[(i+1)%n][1],a,b,c,d);

            }
            else if(boundary==1)
            {lcp[l1][0]=xmax;
                // cout<<"boundary and lcp"<<boundary<<" "<<xmax<<endl;
                lcp[l1][1]=y_intersect(poly[i%n][0],poly[i%n][1],poly[(i+1)%n][0],poly[(i+1)%n][1],a,b,c,d);

            }
            else if(boundary==2)
            {
                lcp[l1][1]=ymin;
                lcp[l1][0]=x_intersect(poly[i%n][0],poly[i%n][1],poly[(i+1)%n][0],poly[(i+1)%n][1],a,b,c,d);
            }
            else
            {
                lcp[l1][1]=ymax;
                lcp[l1][0]=x_intersect(poly[i%n][0],poly[i%n][1],poly[(i+1)%n][0],poly[(i+1)%n][1],a,b,c,d);

            }

            //cout<<"intercept"<<lcp[l1][0]<<" ,"<<lcp[l1][1]<<endl;
            l1+=1;
            lcp[l1][0]=poly[(i+1)%n][0];
            lcp[l1][1]=poly[(i+1)%n][1];
            l1+=1;
        }
        else if(ch==1)
        {    cout<<"in in"<<l1<<endl;
            lcp[l1][0]=poly[(i+1)%n][0];
            lcp[l1][1]=poly[(i+1)%n][1];
            l1+=1;
        }
        else if(ch==2)
        {    cout<<"in out"<<l1<<endl;
            if(boundary==0)
            {   lcp[l1][0]=xmin;
                lcp[l1][1]=y_intersect(poly[i%n][0],poly[i%n][1],poly[(i+1)%n][0],poly[(i+1)%n][1],a,b,c,d);

            }
            else if(boundary==1)
            {   lcp[l1][0]=xmax;
                lcp[l1][1]=y_intersect(poly[i%n][0],poly[i%n][1],poly[(i+1)%n][0],poly[(i+1)%n][1],a,b,c,d);
            }
            else if(boundary==2)
            {
                lcp[l1][1]=ymin;
                lcp[l1][0]=x_intersect(poly[i%n][0],poly[i%n][1],poly[(i+1)%n][0],poly[(i+1)%n][1],a,b,c,d);
            }
            else
            {   lcp[l1][1]=ymax;
                lcp[l1][0]=x_intersect(poly[i%n][0],poly[i%n][1],poly[(i+1)%n][0],poly[(i+1)%n][1],a,b,c,d);


            }
            cout<<"intercept in out"<<lcp[l1][0]<<" ,"<<lcp[l1][1]<<endl;
            l1+=1;
        }
    }
    n=l1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<2;j++)
        {
            poly[i][j]=lcp[i][j];
        }
    }
    polygonDraw(1,poly,n);
   // Sleep(5);


}
void suthHodgClip(){
    //left boundary check
    fn(0,xmin,ymin,xmin,ymax);
    fn(1,xmax,ymin,xmax,ymax);
    fn(2,xmin,ymin,xmax,ymin);
    fn(3,xmax,ymin,xmax,ymax);
    polygonDraw(1,poly,n);

}

void mouseHandler(int button,int state,int x,int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(n==0)
        {   xmin=x;
            ymin=480-y;

        }
        else if(n==1)
        {
                xmax=x;
                ymax=480-y;
        }
        else{
            poly[n-2][0]=x;
            poly[n-2][1]=480-y;
        }
        n++;
    }
    if(n==2){
        cout<<"hi in n=2"<<endl<<endl;
        windowDraw();
    }
    if(n>2 && button == GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
        polygonDraw(0,poly,n-2);
        n=n-2;
        suthHodgClip();
       // n=2;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseHandler);
    glutMainLoop();

    return EXIT_SUCCESS;
}
