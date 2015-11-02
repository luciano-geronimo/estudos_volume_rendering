#include <stdlib.h>
#include <gl/glew.h>
#include <gl/glut.h>
#include <exception>
void displayCall();
void myKeyboard(unsigned char key, int x, int y);
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Teste OpenGL moderno");
	glutDisplayFunc(displayCall);
	if (glewInit() != GLEW_OK)
		throw std::exception("glewInit failed");
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();
	return EXIT_SUCCESS;
}
void displayCall()
{
	glClearColor(0.2, 0.2, 0.2, 1);
	glutSwapBuffers();
	glutPostRedisplay();
}
void myKeyboard(unsigned char key, int x, int y)
{
	
}
