//#include <gl/glew.h>
//#include <gl/glut.h>
//#include <exception>
//
//#include <iostream>
//#include <string>
//
//#include <vtkSmartPointer.h>
//#include <vtkDICOMImageReader.h>
//#include <vtkImageData.h>
//#include <vtkPNGReader.h>
//#include <cstdlib>
////Macro de verificação de erro do opengl autocontida. Lança uma std::exception caso exista um erro de opengl.
//#define TEST_OPENGL_ERROR {GLenum error_code = glGetError(); if (error_code != GL_NO_ERROR){std::string error = "OpenGL error = "; char buff[100]; _itoa_s(error_code, buff, 10);error += buff; error += " @"; error += __FUNCTION__; error+=" ln ";char _b[100];_itoa_s(__LINE__, _b,10); error+=_b ;std::cout << error << std::endl; throw std::exception(error.c_str()); }}
//
//
//	
//
////Estrutura de dados do volume.
//struct Volume
//{
//	double dimensions[3];
//	double spacing[3];
//	double origin[3];
//	GLuint *texture_ids;
//	short* volume_data;
//};
//
////Implementa uma câmera simples, via gluLookAt. 
//class Camera
//{
//private:
//	double* eye_pos;
//	double* focus_pos;
//	double* up_vector;
//public:
//	enum Axis {X=0, Y=1, Z=2};
//	Camera()
//	{
//		eye_pos = new double[3];
//		focus_pos = new double[3];
//		up_vector = new double[3];
//		SetEyePos(0, 0, 10);
//		SetFocus(0, 0, 0);
//		SetUpVector(0, 1, 0);
//	}
//	~Camera()
//	{
//		delete[] eye_pos;
//		delete[] focus_pos;
//		delete[] up_vector;
//	}
//	void ChangeEye(Axis axis, double val)
//	{
//		eye_pos[axis] = eye_pos[axis]+val;
//	}
//	void SetEyePos(double x, double y, double z)
//	{
//		eye_pos[0] = x;
//		eye_pos[1] = y;
//		eye_pos[2] = z;
//	}
//	void SetFocus(double x, double y, double z)
//	{
//		focus_pos[0] = x;
//		focus_pos[1] = y;
//		focus_pos[2] = z;
//	}
//	void SetUpVector(double x, double y, double z)
//	{
//		up_vector[0] = x;
//		up_vector[1] = y;
//		up_vector[2] = z;
//	}
//
//	void Apply()
//	{
//		gluLookAt(eye_pos[0], eye_pos[1], eye_pos[2], focus_pos[0], focus_pos[1], focus_pos[2], up_vector[0], up_vector[1], up_vector[2]);
//	}
//};
////Lista de texturas pro teste de blending
//GLuint texturas[5];
//GLuint textura_scalars[1];
////id da 1a textura, de teste.
//GLuint texture_id[1];
//unsigned char* texbuffer = nullptr;
//float ratio;
//Camera* cam = nullptr;
////Callback do teclado.
//void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
//{
//	if (key == 'w')
//	{
//		cam->ChangeEye(Camera::Z, 1);
//	}
//	if (key == 's')
//	{
//		cam->ChangeEye(Camera::Z, -1);
//	}
//	if (key == 'a')
//	{
//		cam->ChangeEye(Camera::X, 1);
//	}
//	if (key == 'd')
//	{
//		cam->ChangeEye(Camera::X, -1);
//	}
//	if (key == 'q')
//	{
//		cam->ChangeEye(Camera::Y, 1);
//	}
//	if (key == 'e')
//	{
//		cam->ChangeEye(Camera::Y, -1);
//	}
//}
////Renderização da cena
//void display(void)
//{
//	const int plane_size = 5;
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	cam->Apply();
//	
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	
//	//glBindTexture(GL_TEXTURE_2D, texture_id[0]);
//	for (int i = 0; i < 5; i++)
//	{
//		glBindTexture(GL_TEXTURE_2D, texturas[i]);
//		glBegin(GL_TRIANGLES);
//		glTexCoord2f(0, 0);
//		glVertex3f(-plane_size, -plane_size, i);
//		glTexCoord2f(1, 0); 
//		glVertex3f(plane_size, -plane_size, i);
//		glTexCoord2f(0, 1);
//		glVertex3f(-plane_size, plane_size, i);
//		
//		glTexCoord2f(0, 1);
//		glVertex3f(-plane_size, plane_size, i);
//		glTexCoord2f(1, 1);
//		glVertex3f(plane_size, plane_size, i);
//		glTexCoord2f(1, 0);
//		glVertex3f(plane_size, -plane_size, i);
//		glEnd();
//	}
//
//
//	glBindTexture(GL_TEXTURE_2D, textura_scalars[1]);
//
//	glBegin(GL_QUADS);
//	glTexCoord2f(0, 0); glVertex3f(-plane_size, -plane_size, 10);
//	glTexCoord2f(0, 1); glVertex3f(plane_size, -plane_size, 10);
//	glTexCoord2f(1, 1); glVertex3f(plane_size, plane_size, 10);
//	glTexCoord2f(1, 0); glVertex3f(-plane_size, plane_size, 10);
//	glEnd();
//
//	glutSwapBuffers();
//}
////callback do redimensionamento
//void reshape(int w, int h)
//{
//	// Prevent a divide by zero, when window is too short
//	// (you cant make a window of zero width).
//	if (h == 0)
//		h = 1;
//
//	ratio = 1.0f * w / h;
//	// Reset the coordinate system before modifying
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	// Set the viewport to be the entire window
//	glViewport(0, 0, w, h);
//
//	// Set the clipping volume
//	gluPerspective(80, ratio, 1, 200);
//
//}
//
//GLubyte *image01, *image02, *image03, *image04, *image05;
//
//GLubyte* load_and_bind_png_pro_teste(const std::string filepath, int qual_textura)
//{
//	vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
//	reader->SetFileName(filepath.c_str());
//	reader->Update();
//	reader->GetOutput()->Print(std::cout);
//	const int dim_x = reader->GetOutput()->GetExtent()[1] + 1;
//	const int dim_y = reader->GetOutput()->GetExtent()[3] + 1;
//	GLubyte *i = new GLubyte[dim_x * dim_y * 4];
//	memcpy(i, reader->GetOutput()->GetScalarPointer(), dim_x * dim_y * 4);
//	//Cria a textura 1
//	glBindTexture(GL_TEXTURE_2D, texturas[qual_textura]);
//	glEnable(GL_TEXTURE_2D);
//	glTexImage2D(GL_TEXTURE_2D, 0, 4, dim_x, dim_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, i);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	
//	//glBindTexture(GL_TEXTURE_2D, 0);
//	return i;
//}
//
////Carrega a série e gera a tabela de texturas.
//Volume* load_data(const char* filepath)
//{
//	vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
//	reader->SetDirectoryName(filepath);
//	reader->Update();
//	vtkImageData* img = reader->GetOutput();
//	Volume *vol = new Volume;
//	memset(vol, 0, sizeof(Volume));
//	vol->dimensions[0] = img->GetExtent()[1] + 1;
//	vol->dimensions[1] = img->GetExtent()[3] + 1;
//	vol->dimensions[2] = img->GetExtent()[5] + 1;
//	vol->origin[0] = img->GetOrigin()[0];
//	vol->origin[1] = img->GetOrigin()[1];
//	vol->origin[2] = img->GetOrigin()[2];
//	vol->spacing[0] = img->GetSpacing()[0];
//	vol->spacing[1] = img->GetSpacing()[1];
//	vol->spacing[2] = img->GetSpacing()[2];
//	int num_elem = vol->dimensions[0] * vol->dimensions[1] * vol->dimensions[2];
//	vol->volume_data = new short[num_elem]; 
//	memcpy(vol->volume_data, img->GetScalarPointer(), num_elem * sizeof(short));
//	//a partir daqui tenho tudo que preciso. Posso criar as texturas ao longo do eixo z
//	glGenTextures(vol->dimensions[2], vol->texture_ids);
//	TEST_OPENGL_ERROR;
//	//para cada fatia, criar a textura
//	for (int z = 0; z < vol->dimensions[2]; z++)
//	{
//		glBindTexture(GL_TEXTURE_2D, vol->texture_ids[z]);
//		glEnable(GL_TEXTURE_2D);
////		glTexImage2D(GL_TEXTURE_2D, 0, 1, vol->dimensions[0], vol->dimensions[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, i);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	}
//	return vol;
//}
////Função de inicialização. É aqui que eu seto flags da máquina de estados do OpenGL e carrego o volume.
//void init(void)
//{
//		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
//		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
//		glEnable(GL_COLOR_MATERIAL);
//		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//		glDisable(GL_DEPTH_TEST); glDepthFunc(GL_LEQUAL);
//		glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//
//
//
//		//Volume* vol = load_data("C://dicom/Marching Man");
//	//glEnable(GL_TEXTURE_2D);
//	////a textura DE TESTE é aqui
//	//if (!(texbuffer = (unsigned char*)malloc(128 * 128 * 3)))
//	//	throw std::exception(__FUNCTION__);
//
//	//for (int i = 0; i < 128 * 128 * 3; i=i+3)
//	//{
//	//	texbuffer[i] = 255;
//	//	texbuffer[i + 1] = 255 * rand();
//	//	texbuffer[i + 2] = 255 * rand();
//	//}
//
//	////glGenTextures(1, texture_id);
//	////glBindTexture(GL_TEXTURE_2D, texture_id[0]);
//	////glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, texbuffer);
//	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
//	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering
//
//
//	//agora as texturas pro estudo do blending - serão carregadas usando as libs pq não quero aprender a carregar imagem complexa.
//	//1)carga dos arquivos
//	char* __pfilepath = new char[500];
//	GetModuleFileNameA(nullptr, __pfilepath, 500); //C:\\Users\\luciano\\Documents\\programacao\\real_time_volume_rendering\\estudo_01_texture2d_oldschool\\Debug\\estudo01.exe
//	std::string path(__pfilepath);
//	path.replace(path.length() - 12, path.length(), "");
//	const std::string path_arq01 = path + "one.png";
//	const std::string path_arq02 = path + "two.png";
//	const std::string path_arq03 = path + "three.png";
//	const std::string path_arq04 = path + "four.png";
//	const std::string path_arq05 = path + "five.png";
//	//Carrega as texturas de teste
//	glGenTextures(5, texturas);
//
//	image01 = load_and_bind_png_pro_teste(path_arq01, 0);
//
//	image02 = load_and_bind_png_pro_teste(path_arq02, 1);
//
//	image03 = load_and_bind_png_pro_teste(path_arq03, 2);
//
//	image04 = load_and_bind_png_pro_teste(path_arq04, 3);
//
//	image05 = load_and_bind_png_pro_teste(path_arq05, 4);
//
//	//Cria a textura escalar pra teste de pixel map
//	//lut
//	glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
//	GLushort redMap[] = { 0, 65535, 65535, 0 };
//	GLushort greenMap[] = { 65535, 0, 65535, 65535 };
//	GLushort blueMap[] = { 65535, 65535, 0, 0 };
//	GLushort ALPHAMap[] = { 65535, 65535, 0, 0 };
//	glPixelMapusv(GL_PIXEL_MAP_I_TO_R, 4, redMap);
//	glPixelMapusv(GL_PIXEL_MAP_I_TO_G, 4, greenMap);
//	glPixelMapusv(GL_PIXEL_MAP_I_TO_B, 4, blueMap);
//	glPixelMapusv(GL_PIXEL_MAP_I_TO_A, 4, ALPHAMap);
//	//imagem
//	static unsigned char* scalar_map_buffer = new unsigned char[128 * 128 * 1];
//	memset(scalar_map_buffer, 1, 128 * 128 * sizeof(unsigned char));
//	//textura
//	glGenTextures(1, textura_scalars);
//	glBindTexture(GL_TEXTURE_2D, textura_scalars[0]);
//	glEnable(GL_TEXTURE_2D);
//	
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_COLOR_INDEX, GL_UNSIGNED_BYTE, scalar_map_buffer);
//	TEST_OPENGL_ERROR;
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering
//
//
//}
////Função principal do programa.
//int main(int argc, char *argv[])
//{
//	try
//	{
//		cam = new Camera();
//		glutInit(&argc, argv);
//		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//		glutInitWindowPosition(0, 0);
//		glutInitWindowSize(500, 500);
//		glutCreateWindow("Volume Rendering via Textura2d implementado com opengl legacy");
//		init();
//		glutDisplayFunc(display);
//		glutReshapeFunc(reshape);
//		glutKeyboardFunc(keyboard);
//		glutIdleFunc(display);
//		glutMainLoop();
//		delete cam;
//	}
//	catch (std::exception& ex)
//	{
//		std::cout << ex.what() << std::endl;
//		throw ex;
//	}
//	return EXIT_SUCCESS;
//}
