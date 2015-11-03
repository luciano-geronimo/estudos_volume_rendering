#include <stdlib.h>
#include <gl/glew.h>
#include <gl/glut.h>
#include <exception>

#include <vector>
//ponteiro para os dados do buffer
GLuint vertex_array;
GLfloat* vertex_buffer_data = nullptr;
GLushort* index_buffer_data = nullptr;
//Define a função que vai tratar do evento de exibição
void my_display_callback();
//define a funcão que vai tratar do evento de teclado.
void my_keyboard_callback(unsigned char key, int x, int y);
//inicialização da geometria. A flag controla se já foi inicializada, a init_geometry faz a inicialização.
bool is_geometria_initialized = false;
bool init_geometry();
//Funcão de entrada do programa - cria os contextos da Glut, inicializa a Glew e seta os callbacks
//do ciclo de vida da Glut.
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//Inicialização
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);//Setagem do modo de tela
	//tamanho, posição e nome da janela
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Teste OpenGL moderno");
	//callbacks
	glutDisplayFunc(my_display_callback);
	glutKeyboardFunc(my_keyboard_callback);
	//Inicialização da glew
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
	//envia um evento de exibição
	glutPostRedisplay();
}
void my_keyboard_callback(unsigned char key, int x, int y)
{
	
}
bool init_geometry()
{
	const int numero_de_triangulos = 2;
	//Define os vértices e a relação entre eles. Os vértices são usados pelo 
	//vertex shader enquanto a ordem dos mesmos é usada pra gerar geometria no
	//geometry shader. Os valores que definem os vértices são definidos na
	//lst_vertex_data enquanto os índices são definidos na lst_index_data. Usei
	//as funçõs da stl para facilitar minha vida, só fazendo a passagem para
	//ponteiros de baixo nível no passo final, o envio pra placa de vídeo.
	//Define os vértices
	std::vector<GLfloat> lst_vertex_data; 
	int z = 0;
	for (int i = 0; i < numero_de_triangulos; i++)
	{
		auto size = 1;
		if (i%2)
		{
			lst_vertex_data.push_back(-size); lst_vertex_data.push_back(-size); lst_vertex_data.push_back(z);
			lst_vertex_data.push_back(-size); lst_vertex_data.push_back(size); lst_vertex_data.push_back(z);
			lst_vertex_data.push_back(size); lst_vertex_data.push_back(-size); lst_vertex_data.push_back(z);
		}
		else
		{
			lst_vertex_data.push_back(size); lst_vertex_data.push_back(-size); lst_vertex_data.push_back(z);
			lst_vertex_data.push_back(-size); lst_vertex_data.push_back(size); lst_vertex_data.push_back(z);
			lst_vertex_data.push_back(size); lst_vertex_data.push_back(size); lst_vertex_data.push_back(z);
			z = z + 1;
		}
	}
	vertex_buffer_data = new GLfloat[lst_vertex_data.size()];
	std::copy(lst_vertex_data.begin(), lst_vertex_data.end(), vertex_buffer_data);
	//define a lista de índices
	std::vector<GLushort> lst_index_data;
	for (int i = 0; i < lst_vertex_data.size() / 3; i++)//dividido por 3 pq cada vértice ocupa 3 elementos no vetor e estou criando 1 indice / vertice.
	{
		lst_index_data.push_back(i);
	}
	index_buffer_data = new GLushort[lst_index_data.size()];
	std::copy(lst_index_data.begin(), lst_index_data.end(), index_buffer_data);
	//Agora que os dados existem na memória numa forma que o opengl pode entende-los posso criar o VAO (vertex
	//array object) que vai, com seus vertex buffer objects, ser o dado no mundo do opengl.
	GLuint vertex_buffer, index_buffer;
	//criação dos IDs no opengl.
	glGenVertexArrays(1, &vertex_array);
	glGenBuffers(1, &vertex_buffer);
	glGenBuffers(1, &index_buffer);
	//escolhe qual vertex array object eu quero trabalhar - a partir desse momento todas as operações serão nela.
	glBindVertexArray(vertex_array);
	//escolhe com qua buffer eu quero trabalhar. O vertex buffer object é usado para copiar os dados para dentro do 
	//vertex array object escolhido anteriormente.
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lst_vertex_data.size(), vertex_buffer_data, GL_STATIC_DRAW);
	//Seta como o buffer será passado pro vertex shader
	GLint pos_attrib = glGetAttribLocation(shader_progream, "vertex");//pega o id da variável de shader 
	glEnableVertexAttribArray(pos_attrib);//ativa a array pro vertex - o attrib receberá a lista de vertices definida usando o VBO atual
	glVertexAttribPointer(pos_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//passa pro atributo.
	//Agora é hora de setar os índices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*lst_index_data.size(), index_buffer_data, GL_STATIC_DRAW);
	//acabei de trabalhar com o VAO, desvinculo-o
	glBindVertexArray(0);
	return false;
}