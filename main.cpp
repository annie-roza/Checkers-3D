#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <gl/glut.h>
#include<MMSystem.h>
#define pi (2*acos(0.0))


bool b1=0,w1=0,b2=0,w2=0,k=0;
double cameraHeight;
double cameraAngle;
int bullet=0;
int drawgrid;
int drawaxes;
double angle;
double angle_c_z=0;
double angle_c_x=0, angle_t_x=0, angle_t_z=0,xr=0,yr=0,zr=0;
double limit=0.0,temp1=0,temp2=0,temp3=0;
struct point
{
	double x,y,z;
};

struct point pos,l,u,r;
double X=0,Z=0;
int Y=-1;
struct point arra[100];
void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
		    glColor3f(0.0f,1.0f,0.0f);
			glVertex3f( 1000,0,0);
			glVertex3f(-1000,0,0);

            glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(0,-1000,0);
			glVertex3f(0, 1000,0);

            glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0,0, 1000);
			glVertex3f(0,0,-1000);
		}glEnd();
	}
}

void drawCube(double a){
    glBegin(GL_QUADS);{


        //glColor3f(.3,.3,.7);
        glVertex3f( a,-a,a);    //Right side Plane
		glVertex3f( a,-a,-a);
		glVertex3f(-a,-a,-a);
		glVertex3f(-a,-a,a);

        //glColor3f(.7,.3,.7);   //Left side Plane
        glVertex3f( a, a,a);
		glVertex3f( -a,a,a);
		glVertex3f(-a,a,-a);
		glVertex3f(a,a,-a);

        //glColor3f(.3,.7,.3);
        glVertex3f( a, a, a);  //Bottom Square Plane
		glVertex3f( a,a,-a);
		glVertex3f(a,-a,-a);
		glVertex3f(a,-a,a);

        //glColor3f(0,.7,0);
        glVertex3f( -a, a,-a);  //Front Square Plane
		glVertex3f( a,a,-a);
		glVertex3f(a,-a,-a);
		glVertex3f(-a,-a,-a);

        //glColor3f(0,0,.7);
        glVertex3f( -a, a,-a);  //Top Square plane
		glVertex3f( -a,-a,-a);
		glVertex3f(-a,-a,a);
		glVertex3f(-a, a,a);

        //glColor3f(.7,0,0);
		glVertex3f( a, a,a);  //Back Square plane
		glVertex3f( a,-a,a);
		glVertex3f(-a,-a,a);
		glVertex3f(-a, a,a);
	}glEnd();


}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}

void draw_circle_line(double radius,int segments)
{
  int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    glBegin(GL_LINES);
    {
        for(i=0;i<segments;i++)
        {

            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);

        }
    }
        glEnd();
}
void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
//    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    glBegin(GL_POLYGON);
    {
        for(i=0;i<segments;i++)
        {

            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);

        }
    }
        glEnd();
}

void draw_cylinder(double radius,double height,int segments)
{
    int i;
     struct point points[2][100];
     for(i=0;i<=segments;i++)
    {
        points[0][i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[0][i].y=radius*sin(((double)i/(double)segments)*2*pi);
        points[0][i].z=0;
        points[1][i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[1][i].y=radius*sin(((double)i/(double)segments)*2*pi);
        points[1][i].z=height;
    }

    for (i=0;i<segments;i++)
    {
        glBegin(GL_QUADS);{
			    //upper hemisphere
			    //glColor3f((i)%2,.5,(i)%2);
				glVertex3f(points[0][i].x,points[0][i].y,points[0][i].z);
				glVertex3f(points[0][i+1].x,points[0][i+1].y,points[0][i+1].z);
				glVertex3f(points[1][i+1].x,points[1][i+1].y,points[1][i+1].z);
				glVertex3f(points[1][i].x,points[1][i].y,points[1][i].z);

			}glEnd();


    }
}
void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<int(segments-limit);i++)
    {
        //create shading effect
//        if(i<segments/2)shade=2*(double)i/(double)segments;
//        else shade=2*(1.0-(double)i/(double)segments);
//        glColor3f(shade,0,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,1,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				}glEnd();
            glBegin(GL_QUADS);{
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}


void quad()
{
  // Draw A Quad
        glBegin(GL_QUADS);

            glColor3f(0.0f,1.0f,0.0f);
            glVertex3f(0.0f,0.0f,0.0f);					    // Top front Of The Quad (right)
            glVertex3f(10.0f,0.0f,0.0f);					// Top back Of The Quad (right)
            glVertex3f(10.0f,10.0f,0.0f);					// Bottom back Of The Quad (right)
            glVertex3f(0.0f,10.0f,0.0f);					// Bottom front Of The Quad (right)

            glColor3f(1.0f,1.0f,0.0f);
            glVertex3f(10.0f,10.0f,0.0f);					// Top front Of The Quad (left)
            glVertex3f(10.0f,0.0f,0.0f);					// Top back Of The Quad (left)
            glVertex3f(10.0f,0.0f,10.0f);					// Bottom back Of The Quad (left)
            glVertex3f(10.0f,10.0f,10.0f);					// Bottom front Of The Quad (left)


            glColor3f(1.0f,0.0f,1.0f);
            glVertex3f(10.0f,10.0f,10.0f);					    // Right front Of The Quad (top)
            glVertex3f(0.0f,10.0f,10.0f);					    // Right back Of The Quad (top)
            glVertex3f(0.0f,0.0f,10.0f);				    // Left back Of The Quad (top)
            glVertex3f(10.0f,0.0f,10.0f);				    // Left front Of The Quad (top)


            glColor3f(0.0f,1.0f,1.0f);
            glVertex3f(0.0f,10.0f,0.0f);					// Right front Of The Quad (bottom)
            glVertex3f(0.0f,0.0f,0.0f);					// Right back Of The Quad (bottom)
            glVertex3f(0.0f,0.0f,10.0f);				    // Left back Of The Quad (bottom)
            glVertex3f(0.0f,10.0f,10.0f);				    // Left front Of The Quad (bottom)

//

//
            glColor3f(1.0f,0.0f,0.0f);
           glVertex3f(0.0f,0.0f,0.0f);					    // Top Right Of The Quad (Front)
            glVertex3f(0.0f,0.0f,10.0f);					// Top Left Of The Quad (Front)
            glVertex3f(10.0f,0.0f,10.0f);					// Bottom Left Of The Quad (Front)
           glVertex3f(10.0f,0.0f,0.0f);			// Bottom Right Of The Quad (Front)



            glColor3f(1.0f,0.0f,0.0f);
            glVertex3f(0.0f,10.0f,0.0f);					    // Top Right Of The Quad (Front)
            glVertex3f(0.0f,10.0f,10.0f);					// Top Left Of The Quad (Front)
            glVertex3f(10.0f,10.0f,10.0f);					// Bottom Left Of The Quad (Front)
            glVertex3f(10.0f,10.0f,0.0f);

        glEnd();
}




void whiteMove(double temp1, double temp2){
    glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(temp1+xr,temp2+yr,1);
        drawCircle(1,30);
        draw_cylinder(1,.5,30);
    glPopMatrix();
}

void movement3D()
{
    draw_circle_line(110,40);
    glColor3f(1,0,0);
    drawSphere(20,30,30);

    glPushMatrix();
    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSphere(15,30,30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,0,1);
    glRotatef(angle,0,1,1);
    //draw_circle_line(110,40);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSphere(15,30,30);

    glPopMatrix();

}
void drawSS()
{
    draw_circle_line(110,40);
    glColor3f(1,0,0);
    drawSphere(20,30,30);

    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSphere(15,30,30);;

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSphere(10,30,30);;
    }
    glPopMatrix();
    glColor3f(1,1,1);

    /*glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);*/
}

void keyboardListener(unsigned char key, int xx,int yy){
    double x,y,z;
    double rate = 0.01;
	switch(key){

        case ' ':
            {
               temp1+=xr;
               temp2+=yr;
                glutPostRedisplay();
            }break;
        case 's':
            {


                glutPostRedisplay();
            }break;

		case '1':

			{
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(rate)+1*r.x*sin(rate);
			l.y = l.y*cos(rate)+r.y*sin(rate);
			l.z = l.z*cos(rate)+r.z*sin(rate);

			r.x = r.x*cos(rate)-x*sin(rate);
			r.y = r.y*cos(rate)-y*sin(rate);
			r.z = r.z*cos(rate)-z*sin(rate);}
			break;
        case '2':

			{
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(-rate)+r.x*sin(-rate);
			l.y = l.y*cos(-rate)+r.y*sin(-rate);
			l.z = l.z*cos(-rate)+r.z*sin(-rate);

			r.x = r.x*cos(-rate)-x*sin(-rate);
			r.y = r.y*cos(-rate)-y*sin(-rate);
			r.z = r.z*cos(-rate)-z*sin(-rate);
			}
			break;
        case '3':
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(rate)+u.x*sin(rate);
			l.y = l.y*cos(rate)+u.y*sin(rate);
			l.z = l.z*cos(rate)+u.z*sin(rate);

			u.x = u.x*cos(rate)-x*sin(rate);
			u.y = u.y*cos(rate)-y*sin(rate);
			u.z = u.z*cos(rate)-z*sin(rate);
			break;
        case '4':
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(-rate)+1*u.x*sin(-rate);
			l.y = l.y*cos(-rate)+u.y*sin(-rate);
			l.z = l.z*cos(-rate)+u.z*sin(-rate);

			u.x = u.x*cos(-rate)-x*sin(-rate);
			u.y = u.y*cos(-rate)-y*sin(-rate);
			u.z = u.z*cos(-rate)-z*sin(-rate);
			break;
        case '6':
            x=r.x;y=r.y;z=r.z;
			r.x = r.x*cos(rate)+u.x*sin(rate);
			r.y = r.y*cos(rate)+u.y*sin(rate);
			r.z = r.z*cos(rate)+u.z*sin(rate);

			u.x = u.x*cos(rate)-x*sin(rate);
			u.y = u.y*cos(rate)-y*sin(rate);
			u.z = u.z*cos(rate)-z*sin(rate);
			break;
        case '5':
            x=r.x;y=r.y;z=r.z;
			r.x = r.x*cos(-rate)+u.x*sin(-rate);
			r.y = r.y*cos(-rate)+u.y*sin(-rate);
			r.z = r.z*cos(-rate)+u.z*sin(-rate);

			u.x = u.x*cos(-rate)-x*sin(-rate);
			u.y = u.y*cos(-rate)-y*sin(-rate);
			u.z = u.z*cos(-rate)-z*sin(-rate);
			break;
        case 'q':
            if(angle_c_z<45){
                angle_c_z+=1.5;
            }
            break;
        case 'w':
            if(angle_c_z>-45){
                angle_c_z-=1.5;
            }
            break;
        case 'e':
            if(angle_c_x<45){
                angle_c_x+=1.5;
            }
            break;
        case 'r':
            if(angle_c_x>-45){
                angle_c_x-=1.5;
            }
            break;
        case 'a':
            if ( angle_t_x<45){
                    angle_t_x+=1.5;
            }
            break;

            break;
         case 'd':
            if ( angle_t_z<45){
                    angle_t_z+=1.5;
            }
            break;
        case 'f':
            if ( angle_t_z>-45){
                    angle_t_z-=1.5;
            }
            break;



		default:
			break;
	}

}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_UP:		//down arrow key
			//if( yr<=7.2)
            xr-=2;
            PlaySound(TEXT("genickbruch.wav"), NULL, SND_FILENAME | SND_ASYNC);
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:		// up arrow key
            xr+=2;
            PlaySound(TEXT("genickbruch.wav"), NULL, SND_FILENAME | SND_ASYNC);
			glutPostRedisplay();
			break;

		case GLUT_KEY_LEFT :
            yr-=2;
            PlaySound(TEXT("genickbruch.wav"), NULL, SND_FILENAME | SND_ASYNC);
			glutPostRedisplay();

			break;
		case GLUT_KEY_RIGHT :
			yr+=2;
			PlaySound(TEXT("genickbruch.wav"), NULL, SND_FILENAME | SND_ASYNC);
			glutPostRedisplay();
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x+=u.x;
			pos.y+=u.y;
			pos.z+=u.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos.x-=u.x;
			pos.y-=u.y;
			pos.z-=u.z;
			break;

		case GLUT_KEY_INSERT:
            {
                temp1 =temp1+ xr;
                temp2 =temp2+ yr;
                glutPostRedisplay();
            }break;

		case GLUT_KEY_HOME:
            {
                whiteMove(temp1,temp2);
                glutPostRedisplay();
            }break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				/*bullet =1;
				double length = 649;
				//double length = (649/cos(angle_c_x*pi/180))/cos(angle_t_x*pi/180);
                printf("---> %lf\n",length);
                //X = length* sin(angle_c_z*pi/180);
                X= length* tan(angle_c_z*pi/180);

                Z=-100*sin(angle_c_x*pi/180)-(649-100*cos(angle_c_x*pi/180))*tan((angle_t_x+angle_c_x)*pi/180);*/



			}
			break;


		case GLUT_RIGHT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
				//(600/cos(angle_c_x*pi/180))/cos(angle_t_x*pi/180);
			}
			break;
			//........

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

void drawTriangle(){

    if((xr<=14 && xr>=-1)&&(yr>=-1 && yr<=14)){
    glTranslatef(-7+xr,7-yr,0);
    drawCone(.25,1.2,3);
    }

}






void drawBoard(){

    glPushMatrix();
    glColor3f(0,.7,.7);
    drawTriangle();
    glPopMatrix();

    //Board brown square
    glPushMatrix();
    glColor3f(0.35,0.16, 0.14);
    glTranslatef(0,0,1.25);
    glPushMatrix();
        glPushMatrix();
        glTranslatef(7,-7,0);
        drawSquare(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(3,-7,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1,-7,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-5,-7,0);
        drawSquare(1);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
        glTranslatef(5,-5,0);
        drawSquare(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(1,-5,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-3,-5,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-7,-5,0);
        drawSquare(1);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
        glTranslatef(7,-3,0);
        drawSquare(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(3,-3,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1,-3,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-5,-3,0);
        drawSquare(1);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
        glTranslatef(5,-1,0);
        drawSquare(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(1,-1,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-3,-1,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-7,-1,0);
        drawSquare(1);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
        glTranslatef(7,1,0);
        drawSquare(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(3,1,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1,1,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-5,1,0);
        drawSquare(1);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
        glTranslatef(5,3,0);
        drawSquare(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(1,3,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-3,3,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-7,3,0);
        drawSquare(1);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();           //Second Column
        glPushMatrix();
        glTranslatef(7,5,0);
        drawSquare(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(3,5,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1,5,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-5,5,0);
        drawSquare(1);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();           //First Column
        glPushMatrix();
        glTranslatef(5,7,0);
        drawSquare(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(1,7,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-3,7,0);
        drawSquare(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-7,7,0);
        drawSquare(1);
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();




    //Board Cream Square
    glPushMatrix();       //Board Cover
    glColor3f(0.92,0.78, 0.62);
    glTranslatef(0,0,1.35);
    drawSquare(8);
    glPopMatrix();


    glPushMatrix();     //For black Square
    glTranslatef(0,0,1.45);
    glColor3f(0,0, 0);
    drawSquare(8.2);
    glPopMatrix();

    glPushMatrix();     //For Design Square
    glColor3f(0.92,0.78, 0.62);
    glTranslatef(0,0,1.55);
    drawSquare(9);
    glPopMatrix();

    glPushMatrix();       //Board base
    glColor3f(0.35,0.16, 0.14);
    glTranslatef(0,0,1.65);
    glScalef(1,1,.01);
    drawCube(10);
    glPopMatrix();

    glPushMatrix();       //Table Top
    glColor3f(0.52, 0.37,0.26);
    glTranslatef(0,0,3.5);
    glScalef(1,1,.10);
    drawCube(15);
    glPopMatrix();
}






void drawPoints(double x,double y,double z){
     x=-7;
     y=7;
     z=1.25;
    glPushMatrix();
    glColor3f(1,0,0);
    glBegin(GL_POINTS);{
//        glVertex3f(-7,7,1.5);
//        glVertex3f(-7,5,1.5);
    for(int i=0;i<=7;i++){
            for(int j=0;j<=7;j++){
            glVertex3f(x,y,z);
            x=x;
            y=y-2;
            z=z;
            }
            x=x+2;
            y=7;
            z=z;
        int j=0;
    }
    }glEnd();
    glPopMatrix();

}






void drawPieces(){
    double x=-7;
    double y=7;



    glPushMatrix();         //black
    for(int i=0;i<=1;i++){
        for(int j=0;j<=3;j++){
            b1=1;
            glPushMatrix();
            glColor3f(0,0,0);
            glTranslatef(-x,-y,1);
            drawCircle(1,30);
            draw_cylinder(1,.5,30);
            glPopMatrix();
            y=y-4;
        }
        x=-5;
        y=5;
    }
    glPopMatrix();

    glPushMatrix();         //white
    x=-7;
    y=7;
    for(int i=0;i<=1;i++){
        for(int j=0;j<=3;j++){
            w1=1;
            glPushMatrix();
            glColor3f(1,1,1);
            glTranslatef(x,y,1);
            drawCircle(1,30);
            draw_cylinder(1,.5,30);
            glPopMatrix();
            y=y-4;
        }
        x=-5;
        y=5;
    }
    glPopMatrix();
}

void drawCheckers3d(){
    drawPieces();
    drawPoints(1,1,1);
	drawBoard();
}
void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(pos.x,pos.y,pos.z,	pos.x+l.x,pos.y+l.y,pos.z+l.z,	u.x,u.y,u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawGrid();


    drawCheckers3d();
    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();
    //movement3D();
    //drawSphere(30,10,10);
    //drawScenario();
    //drawCastle();
    //quad();
    //drawCone(5,10,50);
    //draw_cylinder(10,10,30);

    //draw_cylinder(2,500,segment);
    //100*sin(angle_c_x)+(500-100*cos(angle_c_x))*sin(angle_t_x);


    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//display();
//	angle+=.1;
//	//codes for any changes in Models, Camera
//	limit+=0.01;
//	if(limit>=50.0)
//    {
//        limit=0;
//    }



                glPushMatrix();
                    glColor3f(1,1,1);
                    glTranslatef(temp1+xr,temp2+yr,1);
                    drawCircle(1,30);
                    draw_cylinder(1,.5,30);
                glPopMatrix();
                glutPostRedisplay();
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	//cameraHeight=150.0;
	//cameraAngle=1.0;
	//angle=0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	5000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
    pos.x=0;
    pos.y=0;
    pos.z=-20;
    l.x=0;u.x=-1;r.x=0;
    l.y=0;u.y=0;r.y=1;
    l.z=1;u.z=0;r.z=0;
	glutInit(&argc,argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Checkers 3D");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}





















/*
void drawSphere(double radius,int slices,int stacks,int up)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		if(up==3){
                r= 2*radius- radius*cos(((double)i/(double)stacks)*(pi/2));
		}else{
		     r=  radius*cos(((double)i/(double)stacks)*(pi/2));
		}
		for(j=0;j<=slices;j++)
		{
		    if(up!=3){
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		    }
		    else{
            points[i][j].x= r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=(r*sin(((double)j/(double)slices)*2*pi));
			points[i][j].z=h;

		    }
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);

		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
			    glColor3f(j%2,j%2,j%2);
			    if(up==1 or up==-1 or up==3)
                {
                    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                }
                //lower hemisphere
                if(up==0 or up==-1)
                {

                    glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
                }


			}glEnd();
		}
	}
}


void offline()
{

    glBegin(GL_QUADS);{
        //upper hemisphere
        glColor3f(.1,.1,.1);
        glVertex3f(200,-650,200);
        glVertex3f(200,-650,-200);
        glVertex3f(-200,-650,-200);
        glVertex3f(-200,-650,200);

    }glEnd();


    if(bullet==1 && abs(X)<200 && abs(Z)<200){
    Y++;
    arra[Y].x=X;
    arra[Y].z = Z;
    printf("%lf %lf %lf %lf\n",X,Z,angle_c_x,angle_c_z);

	bullet =0;

    }
    int j;
    for(j=0;j<=Y;j++){
        glColor3f(1.0,0.0,0.0);

            glBegin(GL_QUADS);{
            glVertex3f(arra[j].x+5 ,-649, arra[j].z+5);
            glVertex3f(arra[j].x+5,-649, arra[j].z-5);
            glVertex3f(arra[j].x-5,-649,arra[j].z-5 );
            glVertex3f(arra[j].x-5, -649, arra[j].z+5);
        }glEnd();
    }

    int segment =30;
    glRotatef(angle_c_z,0,0,1);
    glRotatef(angle_c_x,1,0,0);
    glRotatef(90,1,0,0);
    glTranslatef(0,0,20);
    drawSphere(20,segment,segment,0);
    draw_cylinder(20,100,segment);
    glTranslatef(0,0,100);
    drawSphere(20,segment,segment,1);
    double r,l;
    r=15;
    l=170;
    glTranslatef(0,0,20);

    glRotatef(angle_t_x,1,0,0);
    glRotatef(angle_t_z,0,0,1);

    glTranslatef(0,0,r);
    drawSphere(r,segment,segment,0);
    draw_cylinder(r,l,segment);
    glTranslatef(0,0,l);
    drawSphere(r,segment,segment,3);
}
*/
