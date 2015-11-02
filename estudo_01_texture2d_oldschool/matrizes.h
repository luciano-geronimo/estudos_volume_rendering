#ifndef __matrizes_h
#include <vtkTransform.h>
#include <vtkPerspectiveTransform.h>
//Cria uma transforma��o de proje��o ortogonal
vtkPerspectiveTransform* createOrthoProjection(double xmin, double xmax, double ymin, double ymax, double znear, double zfar);
//Cria uma transforma��o de proje��o perspectiva
vtkPerspectiveTransform* createPerspectiveProjection(double angle, double aspect, double znear, double zfar);
//Cria uma transforma��o de vis�o, a look at
vtkPerspectiveTransform* CreateLookAtView(const double eye[3], const double focus[3], const double viewup[3]);

void ChangeLookAtView(const double eye[3], const double focus[3], const double viewup[3], vtkPerspectiveTransform* in_mat);

#endif