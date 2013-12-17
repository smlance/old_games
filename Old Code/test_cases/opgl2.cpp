#include <GL/glut.h>
#include <GL/gl.h>
#define window_width 320
#define window_height 240

void renderPrimitive(void)
{
	glutWireCube(2.0f);
}

void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -5.0f);
	renderPrimitive();
	glFlush();
}

void reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //resets projection matrix
	
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); //camera FOV
				//angle, aspect ratio, near, far
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(320, 240);
	glutCreateWindow("bstc");
	
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
}
