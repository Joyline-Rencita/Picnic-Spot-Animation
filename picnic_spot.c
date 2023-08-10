#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define SPEED 30.0

float radius=0;
static int submenu;
static int mainmenu;
static int value = -1;
static int day = 1, night = 0;
float cloudX = 0.0;
float boat1x;
float boat2x;// Boat's x-coordinate
float sunX = 0;
float sunY = 0;
int sunStatus =  0;
int boatStatus2 = 0;
int boatStatus1 = 0;
int carStatus = 0;
float carX=0.0;

void init ()
{
     // glClearColor(1,1,1,1);
        gluOrtho2D(0.0,500.0,0.0,500.0);
        glClearColor(1.0,1.0,1.0,1.0);
        glColor3f(0.0,0.0,1.0);
        glPointSize(2.0);
        glMatrixMode(GL_PROJECTION);
//	gluOrtho2D(-1000, 1000, -1000, 1000);
        glLoadIdentity();
}

void draw_pixel(GLfloat xc, GLfloat yc)
{
         glPointSize(5.0);
         glBegin(GL_POINTS);
         glVertex2f(xc,yc);
         glEnd();
}

void plotpixels(GLfloat Xplot ,GLfloat Yplot, GLfloat x,GLfloat y)
{
         draw_pixel(x+Xplot,y+Yplot); // Q1
         draw_pixel(-x+Xplot,y+Yplot); // Q2
         draw_pixel(x+Xplot,-y+Yplot); // Q4
         draw_pixel(-x+Xplot,-y+Yplot); // Q3
         draw_pixel(y+Xplot,x+Yplot); // Q1
         draw_pixel(-y+Xplot,x+Yplot); // Q2
         draw_pixel(y+Xplot,-x+Yplot); // Q4
         draw_pixel(-y+Xplot,-x+Yplot); // Q3
}
void draw_circle(GLfloat Xplot, GLfloat Yplot, GLfloat r)
{
         GLfloat Pk=1-r, x=0, y=r;
        while(y>x)
         {
                 plotpixels(Xplot,Yplot,x,y);
                 if(Pk < 0)
                         Pk += 2*x+3;
                 else
                 {
                         Pk += 2*(x-y)+5;
                         --y;
                }
                 ++x;
        }
        plotpixels(Xplot,Yplot,x,y);
}

void drawCloud(float x1, float x2, float x3, float y)
{
        float radius;
        for(radius=0;radius<=14;radius++)
        {
                draw_circle(x1+cloudX ,y,radius);
        }
        for(radius=0;radius<=23;radius++)
        {
                draw_circle(x2+cloudX,y,radius);
        }
        for(radius=0;radius<=13;radius++)
        {
                 draw_circle(x3+cloudX ,y,radius);
        }
    /*    for(radius=0;radius<=13;radius++)
        {
                draw_circle(x4,y,radius);
        } */

}

void drawhead(float x, float y, float z, char *string)
{
    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);

    for (char *c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void drawsubhead(float x, float y, float z, char *string)
{
    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);

    for (char *c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

void drawBoat1()
{
        //boat-1  on right side

        glColor3f(0.3486,0.1725,0.0157);
        glPointSize(3.0);
        glBegin(GL_POLYGON);
        glVertex2f(405,175);    //brown base
        glVertex2f(405,185);
        glVertex2f(345,185);
        glVertex2f(345,175);
        glEnd();

        glColor3f(0.3486,0.1725,0.0157);        //brown standard
        glPointSize(3.0);
        glBegin(GL_POLYGON);
        glVertex2f(374,185);
        glVertex2f(376,185);
        glVertex2f(376,245);
        glVertex2f(374,245);
        glEnd();

        glColor3f(0.9804,1.00,0.0);     //yellow color on right side
        glPointSize(3.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(376,185);
        glVertex2f(376,245);
        glVertex2f(400,200);
        glEnd();

        glColor3f(0.9804,1.00,0.0);     //yellow color on left side
        glPointSize(3.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(355,195);
        glVertex2f(374,195);
        glVertex2f(374,235);
        glEnd();

}

void drawBoat2()
{
        glColor3f(0.3486,0.1725,0.0157);
        glPointSize(3.0);
        glBegin(GL_POLYGON);
        glVertex2f(105,215);    //brown base
        glVertex2f(105,225);
        glVertex2f(45,225);
        glVertex2f(45,215);
        glEnd();

        glColor3f(0.3486,0.1725,0.0157);        //brown standard
        glPointSize(3.0);
        glBegin(GL_POLYGON);
        glVertex2f(74,225);
        glVertex2f(76,225);
        glVertex2f(76,285);
        glVertex2f(74,285);
        glEnd();

        glColor3f(0.9804,1.00,0.0);     //yellow color on right side
        glPointSize(3.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(76,225);
        glVertex2f(76,285);
        glVertex2f(100,240);
        glEnd();

        glColor3f(0.9804,1.00,0.0);     //yellow color on left side
        glPointSize(3.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(55,235);
        glVertex2f(74,235);
        glVertex2f(74,275);
        glEnd();
}

void drawSun()
{
        for(radius=0;radius<=20;radius++)
                {
                        glColor3f(1.0,0.66123,0.0);
                        draw_circle(235,400,radius);
                }

}

void drawMoon()
{
        for(radius=0;radius<=20;radius++)
        {
           glColor3f(1.0,1.0,1.0);
           draw_circle(305,395,radius);
        }
}

void drawCar()
{
        glColor3f(0,0.0,1.0);
        glPointSize(3.0);
        glBegin(GL_POLYGON);

        glVertex2f(60,80);   //base
        glVertex2f(60,110);
        glVertex2f(105,110);
        glVertex2f(100,140);  //top
        glVertex2f(135,140);
        glVertex2f(155,110);
        glVertex2f(185,110);
        glVertex2f(185,80);
        glEnd();

        for(radius=0;radius<=7;radius++)
        {
                glColor3f(0.0,0.0,0.0);
                draw_circle(80,73,radius);
        }

        //draw_circle(80,73,7);
        for(radius=0;radius<=7;radius++)
        {
                glColor3f(0.0,0.0,0.0);
                draw_circle(160,73,radius);
        }

        glEnd();
}

void drawObject()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(1.0);

	if(day == 1)
	{
		//sky

        	glColor3f(0.0,0.9854,0.912);
   		glPointSize(3.0);
        	glBegin(GL_POLYGON);
        	glVertex2f(0,330);
        	glVertex2f(0,850);
        	glVertex2f(1280,330);
                glVertex2f(1280,850);
                glEnd();

                //sun

                glPushMatrix();
                glTranslatef(sunX, sunY, 0.0);  //Translate boat along the x-axis which is at the right side of screen
                drawSun();
                glPopMatrix();

		//clouds

   		glColor3f(1.0,1.0,1.0);
        	glPointSize(3.0);
        	drawCloud(70,99,128,460);
        	drawCloud(320,345,372,460);

		/*
                     // **********************car ******************************** //
                glPushMatrix();
                        glTranslatef(carX,0.0,0.0);   //translate car along x axis
                        drawCar();
                glPopMatrix();
*/
	}

	if(night == 1 && day == 0)
	{
		//drawing night sky


		glColor3f(0.04f,0.07f,0.27f);
		glPointSize(3.0);
        	glBegin(GL_POLYGON);
        	glVertex2f(0,330);
     		glVertex2f(0,850);
        	glVertex2f(1280,330);
        	glVertex2f(1280,850);
	        glEnd();
	
		//moon

		glPushMatrix();
                       glTranslatef(sunX, sunY, 0.0);  // Translate boat along the x-axis  which is at the right side of screen
                       drawMoon();
                glPopMatrix();

	}

	//drawing Mountains

        glColor3f(0.0,0.55,0.0);
        glPointSize(3.0);
        glBegin(GL_LINES);
        glVertex2f(0,330);
        glVertex2f(1280,330);   //base line of the mountain
        glEnd();

        // first mountain
        glColor3f(0,0.55,0);
        glPointSize(3.0);
        glBegin(GL_POLYGON);

        glVertex2f(0,330);
        glVertex2f(56.0,395.0);   //tip
        glVertex2f(96.5,330);
        glEnd();
	
	//second mountain

        glColor3f(0,0.55,0);
        glPointSize(3.0);
        glBegin(GL_POLYGON);

        glVertex2f(96.5,330);
        glVertex2f(75.5,360.5);
        glVertex2f(150,450);
        glVertex2f(215,330);
        glEnd();

        //small third  mountain

        glColor3f(0,0.55,0);
        glPointSize(3.0);
        glBegin(GL_POLYGON);

        glVertex2f(160,330);
        glVertex2f(215,395);
        glVertex2f(250,330);
        glVertex2f(235,330);  //next mountain
        glVertex2f(278,400);
        glVertex2f(330,330);
        glEnd();


        //7th mountain

        glBegin(GL_TRIANGLES);
        glVertex2f(293,330);
        glVertex2f(375,430);
        glVertex2f(435,330);
        glEnd();

        //8th mountain
        glBegin(GL_POLYGON);
        glVertex2f(350,330);
        glVertex2f(470,445);
	glVertex2f(500,390);
        glVertex2f(500,330);

        glEnd();
	
	//grassland  below mouontains

        glColor3f(0.6,0.8,0.196078);
        glPointSize(3.0);
        glBegin(GL_POLYGON);
        glVertex2f(0,270);
        glVertex2f(0,330);
        glVertex2f(1280,330);
        glVertex2f(1280,270);
        glEnd();

        //river

        glColor3f(0.0,0.9545,0.874545);
        glPointSize(3.0);
        glBegin(GL_POLYGON);
        glVertex2f(0,270);
        glVertex2f(1280,270);
        glVertex2f(0,140);
        glVertex2f(1280,140);
        glEnd();

        //boats

        glPushMatrix();
            glTranslatef(boat2x, 0.0, 0.0);  // Translate boat along the x-axis  which is at the right side of screen
            drawBoat2();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(boat1x, 0.0, 0.0);  // Translate boat along the x-axis which is at the left side of screen
            drawBoat1();
        glPopMatrix();

        //************************ground*********************************\//

        glColor3f(0.0,0.9999,0.0);
        //glColor3f(0.25f,0.69f,0.37f);
        glPointSize(3.0);
        glBegin(GL_POLYGON);
        glVertex2f(0,140);
        glVertex2f(1280,140);
        glVertex2f(0,0);
        glVertex2f(1280,0);
        glEnd();

	// **********************car ******************************** //

                glPushMatrix();
                        glTranslatef(carX,0.0,0.0);   //translate car along x axis
                        drawCar();
                glPopMatrix();

        //******************* Drawing Trees*************************

        //tree on the way
	
	//tree trunk

        glColor3f(0.263,0.149,0.0863);
        glPointSize(3.0);
        glBegin(GL_POLYGON);
        glVertex2f(28,0);
        glVertex2f(28,80);
        glVertex2f(40,80);
        glVertex2f(40,0);
        glEnd();

        //tree leaves

        for(radius=0;radius<=12;radius++)    //bottom left
        {
               glColor3f(0.1,0.28,0.0);
               draw_circle(24,48,radius);
               glEnd();
        }
        for(radius=0;radius<=15;radius++)   //mid left
        {
               glColor3f(0.1,0.28,0.0);
               draw_circle(17,65,radius);
               glEnd();
        }

        for(radius=0;radius<=12;radius++)       //bottom right
        {
               glColor3f(0.1,0.28,0.0);
               draw_circle(41,48,radius);
               glEnd();
        }
        for(radius=0;radius<=15;radius++)       //mid right
        {
               glColor3f(0.1,0.28,0.0);
               draw_circle(47,65,radius);
               glEnd();
        }

        for(radius=0;radius<=18;radius++)       //top
        {
               glColor3f(0.1,0.28,0.0);
               draw_circle(33,83,radius);
               glEnd();
        }
	
	glFlush();
}

void display()
{
    glClearColor(0,0,0,1);

    if (value == -1)
    {
	char clgName[] = "ST JOSEPH ENGINEERING COLLEGE";
	  drawhead(175, 470, 0, clgName);

        char placeName[] = "VAMANJOOR, MANGALURU - 575028, KARNATAKA, INDIA";
	  drawsubhead(185, 455, 0, placeName);

        char deptName[] = "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING";
	drawhead(133, 415, 0, deptName);

        char project[] = "COMPUTER GRAPHICS MINI PROJECT";
	drawhead(173, 370, 0, project);

        char on[] = "ON";
	drawhead(245, 345, 0, on);

        char projectName[] = "PICNIC SPOT ANIMATION";
	drawhead(200, 310, 0, projectName);

        char proBy[] = "PROJECT BY: ";
	drawhead(230, 260, 0, proBy);

        char p1[] = "Joyline Rencita Dsouza";
	drawhead(100, 220, 0, p1);

        char p1Usn[] = "4SO20CS073";
	drawhead(350, 220, 0, p1Usn);

        char p2[] = "Melanie Crystal Miranda";
	drawhead(100, 190, 0, p2);

        char p2Usn[] = "4SO20CS085";
	drawhead(350, 190, 0, p2Usn);

        char gb[] = "Under the guidance of ";
	drawhead(220, 125, 0, gb);

        char guidedBy[] = "Mr. Anirudhan Adukkathayar C";
	drawhead(205, 80, 0, guidedBy);

        char d1[] = "ASSISTANT PROFESSOR, CSE DEPARTMENT";
	drawsubhead(215, 65, 0, d1);

	char in[] = "PRESS ENTER TO CONTINUE";
	drawsubhead(232, 30, 0, in);

        glutSwapBuffers();
        glutDetachMenu(GLUT_RIGHT_BUTTON);
    }

    if(value == 0)
    {
        char projectName[] = "PICNIC SPOT ANIMATION";
        drawhead(190, 470, 0, projectName);

        char border[] = "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~";
        drawhead(70, 450, 0, border);

        char day[] = "Press 'd' or 'D' to change the scene to day.";
        drawhead(165, 390, 0, day);

        char night[] = "Press 'n' or 'N' to change the scene to night";
        drawhead(165, 360, 0, night);

        char boat1[] = "Click '1' to move the boat 1.";
        drawhead(165, 330, 0, boat1);

        char boat2[] = " Click '3' to move the boat 2";
        drawhead(165,300, 0 ,boat2);

        char stop1[] = "Click '2' to stop boat 1.";
        drawhead(165, 270,0, stop1);

        char stop2[] = "Click '4' to stop the boat 2. ";
        drawhead(165, 240,0, stop2);

        char car[] = "Click '5' to move the car";
        drawhead(165, 210,0, car);

        char stop3[] = "Click '6' to stop the car. ";
        drawhead(165, 180,0, stop3);

        char quit[] = "Click LEFT MOUSE BUTTON to quit.";
        drawhead(165, 150, 0, quit);

        char in[] = "Press 's' or 'S' to Continue";
        drawhead(165, 120, 0, in);

        glutSwapBuffers();
        glutDetachMenu(GLUT_RIGHT_BUTTON);
    }

    if(value == 1)
    {
            drawObject();
    }
}
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
	    case 's' :
	    case 'S' : value = 1;
		       glClear(GL_COLOR_BUFFER_BIT);
		       glutPostRedisplay();
		       break;
	    case 'd' :
	    case 'D' : day = 1;
		       night = 0;
		       glClear(GL_COLOR_BUFFER_BIT);
		       glutPostRedisplay();
		       break;
	    case 'n' :
	    case 'N' : day = 0;
		       night = 1;
		       glClear(GL_COLOR_BUFFER_BIT);
   		       glutPostRedisplay();
		       break;
    }
    
    		if(key=='1')
                {                              //boat start
                        boatStatus1 = 1;
                }

                else if(key== '2')
                        //boat stop
                {
                        boatStatus1 = 0;
                }


                else if(key== '3')              //boat1 start
                 {       boatStatus2 = 1;

                }

                else if(key=='4')
                        //boat1 stop
                {
                        boatStatus2 = 0;
                }

                else if(key == '5')
                {
                        carStatus = 1;
                }

                else if(key == '6')
                {
                        carStatus = 0;
                }    


    if (key == 13)
    {
        value = 0;
        glClear(GL_COLOR_BUFFER_BIT);
        glutPostRedisplay();
    }

}	

void mouse(int btn,int state,int x,int y)
{
        if(btn == GLUT_LEFT_BUTTON && state==GLUT_UP)
		exit(0);
}

	//Animation
	
void idle()
{
//      glTranslatef(cloudX, 0.0, 0.0);
        if(day==1)
                cloudX += SPEED/600;

        if(cloudX > 500)
                cloudX = 0;
        if(boatStatus1 == 1)
        {

                boat1x -= 0.00025;  // Increment boat 1's x-coordinate for animation
        }
        if(boatStatus2 == 1)
        {
                boat2x += 0.00030;  // Decrement boat 2's x-coordinate for animation

        }

        if (boat1x >500)
                 boat1x = 0.0;  // Reset boat 1's x-coordinate if it goes off the screen

    if (boat2x >500)
                boat2x = 0.0;  // Reset boat 2's x-coordinate if it goes off the screen

    //for car
        if(carStatus == 1)
        {
                carX += 0.00025;  // Increment car's x-coordinate for animation
        }

        if (carX >500)
                carX = 10.0;

//************* sun & moon animation ************** //

        sunX += 0.00001;
        sunY += 0.00002;

    glutPostRedisplay();  // Trigger a redisplay to update the animation

}

//************Main Function **************

int main(int argc,char **argv)
{
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(1280,850);
//	glutInitWindowSize(1000,900);
        glutInitWindowPosition(400,0);
        glutCreateWindow("Picnic Spot Animation");
        init();
        glutDisplayFunc(display);
	glutIdleFunc(idle);
        glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
        glutMainLoop();
	return 0;
}
