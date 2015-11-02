#ifndef __teste_tex_2d
#include "../packages/nupengl.core.0.1.0.1/build/native/include/gl/glut.h"

GLuint id_textura_teste;

unsigned char* buffer_textura_teste;

int largura_textura_teste, altura_textura_teste;

void createTexturaTeste()
{
	//pega o id da textura
	glGenTextures(1, &id_textura_teste);
}

#endif