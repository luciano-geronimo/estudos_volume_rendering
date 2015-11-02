//#include "matrizes.h"
//vtkPerspectiveTransform* createOrthoProjection(double xmin, double xmax, double ymin, double ymax, double znear, double zfar)
//{
//	vtkPerspectiveTransform* trans = vtkPerspectiveTransform::New();
//	trans->Ortho(xmin, xmax, ymin, ymax, znear, zfar);
//	trans->Update();
//	return trans;
//}
//
//vtkPerspectiveTransform* createPerspectiveProjection(double angle, double aspect, double znear, double zfar)
//{
//	vtkPerspectiveTransform* trans = vtkPerspectiveTransform::New();
//	trans->Perspective(angle, aspect, znear, zfar);
//	trans->Update();
//	return trans;
//}
//
//void ChangeLookAtView(const double eye[3], const double focus[3], const double viewup[3], vtkPerspectiveTransform* in_mat)
//{
//	in_mat->Identity();
//	in_mat->SetupCamera(eye, focus, viewup);
//	//trans->Identity();
//	in_mat->Update();
//}
//
////Cria uma transformação de visão, a look at
//vtkPerspectiveTransform* CreateLookAtView(const double eye[3], const double focus[3], const double viewup[3])
//{
//	vtkPerspectiveTransform* trans = vtkPerspectiveTransform::New();
//	trans->SetupCamera(eye, focus, viewup);
//	//trans->Identity();
//	trans->Update();
//	return trans;
//}
