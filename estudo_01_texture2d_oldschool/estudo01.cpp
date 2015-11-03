#include <stdlib.h>
#include <gl/glew.h>
#include <gl/glut.h>
#include <exception>
//Define a fun��o que vai tratar do evento de exibi��o
void my_display_callback();
//define a func�o que vai tratar do evento de teclado.
void my_keyboard_callback(unsigned char key, int x, int y);
//inicializa��o da geometria. A flag controla se j� foi inicializada, a init_geometry faz a inicializa��o.
bool is_geometria_initialized = false;
bool init_geometry();
//Func�o de entrada do programa - cria os contextos da Glut, inicializa a Glew e seta os callbacks
//do ciclo de vida da Glut.
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//Inicializa��o
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);//Setagem do modo de tela
	//tamanho, posi��o e nome da janela
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Teste OpenGL moderno");
	//callbacks
	glutDisplayFunc(my_display_callback);
	glutKeyboardFunc(my_keyboard_callback);
	//Inicializa��o da glew
	if (glewInit() != GLEW_OK)
		throw std::exception("glewInit failed");
	//Inicio do ciclo da glut.
	glutMainLoop();
	return EXIT_SUCCESS;
}
void my_display_callback()
{
	if (!is_geometria_initialized)
		is_geometria_initialized = init_geometry();
	//Limpa a tela
	glClearColor(0.2, 0.2, 0.2, 1);
	//faz a passagem do backbuffer pro frontbuffer
	glutSwapBuffers();
	//envia um evento de exibi��o
	glutPostRedisplay();
}
void my_keyboard_callback(unsigned char key, int x, int y)
{
	
}

bool init_geometry()
{
	return false;
}