#include <GL/glut.h>
#include <GL/gl.h>
#define window_width 320
#define window_height 240

void display(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(320, 240);
	glutCreateWindow("bstc");
	
	glutDisplayFunc(display);
	
	glutMainLoop();
}
