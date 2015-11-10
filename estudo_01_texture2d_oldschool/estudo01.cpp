#include <stdlib.h>
#include <gl/glew.h>
#include <gl/glut.h>
#include <exception>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include <vtkSmartPointer.h>
#include <vtkPerspectiveTransform.h>
#include <vtkTransform.h>

//As matrizes
vtkSmartPointer<vtkPerspectiveTransform> projecao_matrix;
vtkSmartPointer<vtkPerspectiveTransform> view_matrix;
vtkSmartPointer<vtkTransform> model_matrix;
GLuint mvp_matrix_id;
//ponteiro para os dados do buffer
GLuint vertex_array;
GLfloat* vertex_buffer_data = nullptr;
GLushort* index_buffer_data = nullptr;
//Compila o shader do tipo dado, usando o código fonte dado e retorna o 
//id do shader
GLuint compile_shader_object(GLenum type, const std::string sourceCode);
//Mecanismos para pegar o log do shader program passado como param.
std::string get_shader_log(GLuint id);
//checa por erros de opengl e lança exceção caso tenha
void check_error();
//Carrega textos como strings de c++
std::string load_text(const char* path);
//Define a função que vai tratar do evento de exibição
void my_display_callback();
//define a funcão que vai tratar do evento de teclado.
void my_keyboard_callback(unsigned char key, int x, int y);
//inicialização da geometria. A flag controla se já foi inicializada, a init_geometry faz a inicialização.
bool is_geometria_initialized = false;
bool init_geometry();
//Faz a carga dos shaders
void load_shaders();
//ponteiro pro programa do shader
GLuint shader_program = 0;

//Funcão de entrada do programa - cria os contextos da Glut, inicializa a Glew e seta os callbacks
//do ciclo de vida da Glut.
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//Inicialização
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//Setagem do modo de tela
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Pega as matrizes e as passa pro shaders.
	vtkMatrix4x4* pm = projecao_matrix->GetMatrix();
	vtkMatrix4x4* vm = view_matrix->GetMatrix();
	vtkMatrix4x4* mm = model_matrix->GetMatrix();
	//mvp
	vtkMatrix4x4* result = vtkMatrix4x4::New();
	vtkMatrix4x4::Multiply4x4(mm, vm, result);
	vtkMatrix4x4::Multiply4x4(result, pm, result);
	//copia
	double m_result[16];
	vtkMatrix4x4::DeepCopy(m_result, result);
	//binda o shader
	glUseProgram(shader_program);

	//passa a matriz pro shader
	glUniformMatrix4fv(mvp_matrix_id, 1, GL_TRUE, (float*)&m_result);
	//desenha o vao
	glBindVertexArray(vertex_array);
	glDrawElementsBaseVertex(GL_TRIANGLES, 1000000, GL_UNSIGNED_SHORT, nullptr, 0);
	glBindVertexArray(0);
	//mvp_matrix_id
	
	//
	//glBindVertexArray(this->vertex_array);
	//glDrawElementsBaseVertex(GL_TRIANGLES, 1000000, GL_UNSIGNED_SHORT, nullptr, 0);
	//glBindVertexArray(0);
	//Desenha.
	//envia um evento de exibição
	glutPostRedisplay();
	//faz a passagem do backbuffer pro frontbuffer
	glutSwapBuffers();

}
void my_keyboard_callback(unsigned char key, int x, int y)
{
	
}
void load_shaders()
{
	//carrega o vertex shader
	std::string vs_text = load_text("vertexShader.txt");
	GLuint vs_id = 0;
	vs_id = compile_shader_object(GL_VERTEX_SHADER, vs_text);
	//carrega o fragment shader
	std::string fs_text = load_text("fragmentShader.txt");
	GLuint fs_id = 0;
	fs_id = compile_shader_object(GL_FRAGMENT_SHADER, fs_text);
	//linka
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vs_id);
	glAttachShader(shader_program, fs_id);
	glLinkProgram(shader_program);
	GLint is_ok = -1;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &is_ok);
	if (!is_ok)
	{
		std::string erro = get_shader_log(shader_program);
		std::cout << erro << std::endl;
	}
	//guarda o id dos uniforms.
	mvp_matrix_id = glGetUniformLocationARB(shader_program, "mvp");
	check_error();
	if (mvp_matrix_id == -1)
	{
		std::string erro = "a uniform mvp nao está ativa.";
		std::cout << erro << std::endl;
		throw std::exception(erro.c_str());
	}
}
bool init_geometry()
{
	//cria as matrizes
	projecao_matrix = vtkSmartPointer<vtkPerspectiveTransform>::New();
	projecao_matrix->Ortho(-2.0, 2.0, -2.0, 2.0, -2, 2);
	projecao_matrix->Update();
	view_matrix = vtkSmartPointer<vtkPerspectiveTransform>::New();
	view_matrix->SetupCamera(0, 0, 2, 0, 0, 0, 0, 1, 0);
	view_matrix->Update();
	model_matrix = vtkSmartPointer<vtkTransform>::New();
	model_matrix->Identity();
	model_matrix->Update();
	//cria os shaders.
	load_shaders();
	const int numero_de_triangulos = 2;
	//Define os vértices e a relação entre eles. Os vértices são usados pelo 
	//vertex shader enquanto a ordem dos mesmos é usada pra gerar geometria no
	//geometry shader. Os valores que definem os vértices são definidos na
	//lst_vertex_data enquanto os índices são definidos na lst_index_data. Usei
	//as funçõs da stl para facilitar minha vida, só fazendo a passagem para
	//ponteiros de baixo nível no passo final, o envio pra placa de vídeo.
	//Define os vértices
	std::vector<GLfloat> lst_vertex_data; 
	float z = 0;
	for (float i = 0; i < numero_de_triangulos; i = i+1)
	{
		float size = 1;
		if (((int)i)%2)
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
	for (unsigned int i = 0; i < lst_vertex_data.size() / 3; i++)//dividido por 3 pq cada vértice ocupa 3 elementos no vetor e estou criando 1 indice / vertice.
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
	GLint pos_attrib = glGetAttribLocation(shader_program, "vertex");//pega o id da variável de shader 
	glEnableVertexAttribArray(pos_attrib);//ativa a array pro vertex - o attrib receberá a lista de vertices definida usando o VBO atual
	glVertexAttribPointer(pos_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//passa pro atributo.
	//Agora é hora de setar os índices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*lst_index_data.size(), index_buffer_data, GL_STATIC_DRAW);
	//acabei de trabalhar com o VAO, desvinculo-o
	glBindVertexArray(0);
	return true;
}
std::string load_text(const char* path)
{
	std::stringstream textStream;
	std::string ln;
	std::ifstream file;
	file.open(path);
	if (file.is_open())
	{
		while (std::getline(file, ln))
		{
			textStream << ln << std::endl;
		}
		file.close();
	}
	else
	{
		std::string str = "arquivo nao encontrado - ";
		str += path;
		throw std::exception(str.c_str());
	}
	return textStream.str();
}
void check_error(){
	GLenum error = glGetError();
	switch (error){
	case 0: return;
	case GL_INVALID_ENUM: throw std::exception("GL error: Invalid enum"); break;
	case GL_INVALID_VALUE: throw std::exception("GL error : Invalid value"); break;
	case GL_INVALID_OPERATION: throw std::exception("GL error: Invalid operation"); break;
	case GL_STACK_OVERFLOW: throw std::exception("GL error: Stack overflow"); break;
	case GL_STACK_UNDERFLOW: throw std::exception("GL error: Stack underflow"); break;
	case GL_OUT_OF_MEMORY: throw std::exception("GL error: Out of memory"); break;
	case GL_TABLE_TOO_LARGE: throw std::exception("GL error: Table too large"); break;
	default: throw std::exception("GL error: Unknown");
	}
}
std::string get_shader_log(GLuint id)
{
	GLint logSize;
	char* log;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize);//pega o tamanho do log do shader
	log = new char[logSize];
	glGetShaderInfoLog(id, logSize, NULL, log);//pega a string.
	std::string result(log);
	return result;
}
GLuint compile_shader_object(GLenum type, const std::string sourceCode)
{
	GLuint shader;
	GLint shaderOK;

	const char* __src = sourceCode.c_str();
	const GLchar** src = (const GLchar**)&__src;
	shader = glCreateShader(type);//cria o shader vazio.
	
	glShaderSource(shader, 1, src, nullptr);//Seta o código fonte
	check_error();
	glCompileShader(shader);
	check_error();
	//vê se compilou. Se não compilou mostra porque não compilou.
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderOK);
	if (!shaderOK)
	{
		std::string erro = get_shader_log(shader);
		std::cout << erro << std::endl;
		throw std::exception(erro.c_str());
	}
	return shader;
}