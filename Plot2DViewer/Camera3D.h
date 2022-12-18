#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include <windows.h>
#include"Camera2D.h"
#include"Vector.h"
#include"Matrix.h"

class Camera3D : public Camera2D
{
	Vector N, T, Ov;
	double F;

	Matrix<>WorldToView, ViewToProject, WorldToProject;

public:

	Camera3D(double L, double R, double B, double _T) :Camera2D(L, R, B, _T)
	{
		double coordinatesOv[3] = { 0,0,0 };
		setOv(coordinatesOv, 3);

		double coordinatesT[3] = { 0,1,0 };
		setT(coordinatesT, 3);

		double coordinatesN[3] = { 0,0,1 };
		setN(coordinatesN, 3);

		UpdateCamera();
		

	}

	void setN(double* _N,int size)
	{
		N.setVector(_N, size);
	}

	void setT(double* _T, int size)
	{
		T.setVector(_T, size);
	}

	void setOv(double* _Ov, int size)
	{
		Ov.setVector(_Ov, size);
	}

	void setF(double _F)
	{
		F = _F;
	}

	void UpdateCamera()
	{
		Vector Iv, Jv, Kv;

		Iv = T.vectorMultiplication(N);
		Iv = Iv / Iv.normOfVec();

		Kv = N;
		Kv = Kv / Kv.normOfVec();

		Jv = Kv.vectorMultiplication(Iv);

		double WV[16] = {
		 Iv[1],Iv[2],Iv[3],-Iv.scalarMultiplication(Ov),
		 Jv[1],Jv[2],Jv[3],-Jv.scalarMultiplication(Ov),
		 Kv[1],Kv[2],Kv[3],-Kv.scalarMultiplication(Ov),
		 0,    0,    0,     1 };

		WorldToView.setMatrix(4, 4, WV);

		double VP[16] = {
			1,0, 0,  0,
			0,1, 0,  0,
			0,0,-1 / F,1};

		ViewToProject.setMatrix(4, 4, VP);

		WorldToProject = ViewToProject * WorldToView;

	}

};


#endif CAMERA_3D_H