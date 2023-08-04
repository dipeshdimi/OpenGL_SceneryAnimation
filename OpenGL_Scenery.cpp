#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include<cstdlib>

float y_sun = -5;
float x_size = 0.6;
float y_size = 0.8;
float z_size = 0.6;
float r = 1.0;
float g = 0.325;
float b = 0.286;
int state = 1;
float tx=10;
double R=.02;
int cloudState=0;
int rainState=0;

void circle(GLdouble rad)
{
    GLint points = 50;
    GLdouble delTheta = (2.0 * 3.14159265) / (GLdouble)points;
    GLdouble theta = 0.0;

    glBegin(GL_POLYGON);
    {
        for(int i = 0; i <=50; i++, theta += delTheta )
        {
            glVertex2f(rad * cos(theta),rad * sin(theta));
        }
    }
    glEnd();
}

void cloud(double x, double y)
{
   
    
    glBegin(GL_TRIANGLE_FAN);
        for(int i=0;i<360;i++)
        {
            x=x+cos((i*3.14)/180)*R;
            y=y+sin((i*3.14)/180)*R;
 
            glVertex2d(x,y);       
        }   
    glEnd();   
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    

	glPushMatrix();
    glColor3f(r,g,b);
    glScalef(x_size,y_size,z_size);
    glTranslatef(4,y_sun,0);
    circle(2);
    glPopMatrix();
	glEnd();
    
    if(state == 0)
    {
    	glColor3f( 1.0, 1.0, 1.0 );
        glPointSize(1.0);
        glBegin( GL_POINTS );
        for( int i = 1; i < 100; i++ )
        {
            int x = (rand()%21) - 10;
            int y = (rand()%15) - 4;
            glVertex2i(x,y );
        }
        glEnd();
    }
    
    if(rainState == 1)
    {
    	cloudState=1;
    	glColor3f( .5647, .6, .6314 );
        glBegin(GL_LINES);
        for( int i = 1; i < 100; i++ )
        {
            int x = (rand()%21) - 10;
            int y = (rand()%15) - 4;
            
			glVertex2f(x, y);
			glVertex2f(x+0.6, y+0.6);
        }
        glEnd();
    }
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(0.5922, 0.4863, 0.3255);
    glVertex2f(-10.0,-4.0);
    glVertex2f(-7.0,5.0);
    glVertex2f(-4.0,-4.0);
    
    glVertex2f(-4.0,-4.0);
    glVertex2f(-1.0,5.0);
    glVertex2f(2.0,-4.0);
    
    glVertex2f(2.0,-4.0);
    glVertex2f(5.0,5.0);
    glVertex2f(8.0,-4.0);
    
    glVertex2f(8.0,-4.0);
    glVertex2f(11.0,5.0);
    glVertex2f(14.0,-4.0);
    
    glEnd();
    
    
    glBegin(GL_QUADS);
    
    glColor3f(0.231, 0.702, 0.816);
    glVertex2f(-10.0,-4.0);
    glVertex2f(-10.0,-7.5);
    glVertex2f(10.0,-7.5);
    glVertex2f(10.0,-4.0);
    
    
    glColor3f(0.4941, 0.9843, 0.3137);
    glVertex2f(-10.0,-7.5);
    glColor3f(0.4941, 0.7843, 0.3137);
    glVertex2f(-10.0,-10.0);
    glColor3f(0.4941, 0.8843, 0.3137);
    glVertex2f(10.0,-10.0);
    glColor3f(0.4941, 0.7343, 0.3137);
    glVertex2f(10.0,-7.5);
    
    glEnd();
    
    float brown = 9.5;
    float green = 10;
    while(brown > -10.0 && green >-10.0)
    {
		glColor3f(.1,0.2,0.1);
		glPushMatrix();
		glTranslatef(0, 0, 0);
		glBegin(GL_POLYGON);
		    glVertex2f(brown-0.5,-4.0);
		    glVertex2f(brown,-4.0);
		    glVertex2f(brown,-3.0);
		    glVertex2f(brown-0.5,-3.0);
		glEnd();
		brown -= 1.5;

		glColor3f(.1,0.5,0.1);
		glBegin(GL_TRIANGLES);
		    glVertex2f(green-0.75,-2);
		    glVertex2f(green,-3);
		    glVertex2f(green-1.5,-3);

		    glVertex2f(green-0.75,-1.5);
		    glVertex2f(green,-2.5);
		    glVertex2f(green-1.5,-2.5);


		    glVertex2f(green-0.75,-1);
		    glVertex2f(green,-2);
		    glVertex2f(green-1.5,-2);

		glEnd();
		
		green -= 1.5;
		glPopMatrix();
	}
	
	if(cloudState==1)
	{
		glPushMatrix();
		glColor3ub(220,220,220);
		if(rainState==1)
			glColor3ub(142, 146, 144);
		glTranslatef(tx,0,0);
		cloud(0,7.2); 
		cloud(1.5,7.1);
		cloud(1,7.0);
		cloud(-2,6.9);

		cloud(-8,7.3); 
		cloud(-9.5,7.2);
		cloud(-9.0,7.0);
		cloud(-9.0,7.1);
		cloud(-7.5,7.1);

		glPopMatrix();
		tx+=.1;
		if(tx>10)
		tx=-10;
	}
	    
    glutSwapBuffers();
    
    glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/20, timer, 0);
	
	switch(state)
	{
		case 1:
			if(y_sun < 10)
			{
				r = 1.0, g = 0.325, b = 0.286;
				y_sun += 0.15;
				if(x_size>0.3 && y_size>0.50 && z_size>0.30)
				{
					x_size -= 0.003214;
					y_size -= 0.003214;
					z_size -= 0.003214;
				}
				if(g < 0.992768)
					g += 0.007232;
				glClearColor(0.5294, 0.8078, 0.9216, 1.0);
			}
			else
				state = -1;
			break;
		case -1:
			if(y_sun > -8)
			{
				y_sun -= 0.15;
				if(x_size<0.6 && y_size<0.8 && z_size<0.6)
				{
					x_size += 0.003214;
					y_size += 0.003214;
					z_size += 0.003214;
				}
				if(g > 0.325)
					g -= 0.007232;
				glClearColor(0.5294, 0.8078, 0.9216, 1.0);
			}
			else
				state = 0;
			break;
		case 0:
			if(y_sun < 10)
			{
				y_sun += 0.15;
				x_size = 0.3;
				y_size = 0.5;
				z_size = 0.3;
	
				r = 1.0;
				g = 1.0;
				b = 1.0;
	
				glClearColor(0.0, 0.0, 0.0, 1.0);
			}
			else
				return;
		
			
	}
}

void MyKeyboardFunc(unsigned char Key, int x, int y)
{
	switch(Key)
	{
		case 'd': state=1; break;
		case 'D': state=1; break;
		case 'n': state=0; break;
		case 'N': state=0; break;
		case 'c': 
			if(cloudState==0)
			{
				cloudState=1;
				break;
			}
			if(cloudState==1)
			{
				cloudState=0;
				break;
			}
		case 'C':
			if(cloudState==0)
			{
				cloudState=1;
				break;
			}
			if(cloudState==1)
			{
				cloudState=0;
				break;
			}
		case 'r':
			if(rainState==0)
			{
				rainState=1;
				break;
			}
			if(rainState==1)
			{
				rainState=0;
				break;
			}
		case 'R':
			if(rainState==0)
			{
				rainState=1;
				break;
			}
			if(rainState==1)
			{
				rainState=0;
				break;
			}
	};
}

void init()
{
    glClearColor(0.5294, 0.8078, 0.9216, 1.0);
    glutKeyboardFunc(MyKeyboardFunc);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("OpenGL");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000, timer, 0);
    
   
    init();
    glutMainLoop();
    
}
