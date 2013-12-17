#include <GL/glut.h>
#include <GL/gl.h>
#define window_width 320
#define window_height 240

void main_loop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void GL_Setup(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(0.0f, 0.0f, 1.0f, 1.0f); //0, 0 is the center of the screen.
	glMatrixMode(GL_PROJECTION);
	glColor3f(0.25f, 0.0f, 0.25f);
	
	gluOrtho2D(0, window_width, 0, window_height);
	glScalef(1, -1, 1);
	glTranslatef(0, -window_height, 0);
	
	glBegin(GL_QUADS);
	
	glVertex2f(16, 16);
	glVertex2f(32, 16);
	glVertex2f(32, 32);
	glVertex2f(16, 32);
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glEnd();
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(window_width, window_height);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("BRYCE");
	glutIdleFunc(main_loop);
	GL_Setup(window_width, window_height);
	glutDisplayFunc(display);
	glutMainLoop();
}
