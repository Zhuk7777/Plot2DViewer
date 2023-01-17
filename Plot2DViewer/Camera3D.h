#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include <windows.h>
#include"Camera2D.h"
#include"Vector.h"
#include"Matrix.h"
#include"AffineTransform3D.h"

class Camera3D : public Camera2D
{
protected:
	Vector N, T, Ov;
	double F;

	Matrix<>WorldToView, ViewToProject, WorldToProject;

public:

	Camera3D(double L, double R, double B, double _T) :Camera2D(L, R, B, _T)
	{
		double coordinatesOv[3] = { 4,4,4 };
		setOv(coordinatesOv, 3);

		double coordinatesT[3] = { 0,1,0 };
		setT(coordinatesT, 3);

		double coordinatesN[3] = { 1,1,1 };
		setN(coordinatesN, 3);

		setF(25);

		UpdateCamera();
		

	}

	Vector getN()
	{
		return N;
	}

	Vector getT()
	{
		return T;
	}

	Vector getOv()
	{
		return Ov;
	}

	double getF()
	{
		return F;
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
		Vector Iv(3), Jv(3), Kv(3);

		Iv = getIv();
		Jv = getJv();
		Kv = getKv();

		double WV[16] = {
		 Iv[1],Iv[2],Iv[3],-Iv.scalarMultiplication(Ov),
		 Jv[1],Jv[2],Jv[3],-Jv.scalarMultiplication(Ov),
		 Kv[1],Kv[2],Kv[3],-Kv.scalarMultiplication(Ov),
		 0,    0,    0,     1 };

		WorldToView.setMatrix(4, 4, WV);

		double param = -1 / F;
		double VP[16] = {
			1,0, 0,  0,
			0,1, 0,  0,
			0,0,param,1};

		ViewToProject.setMatrix(3, 4, VP);

		WorldToProject = ViewToProject * WorldToView;

	}



	Vector getIv()
	{
		Vector Iv(3);
		Iv = T.vectorMultiplication(N);
		Iv = Iv / Iv.normOfVec();
		return Iv;
	}

	Vector getKv()
	{
		Vector Kv(3);
		Kv = N;
		Kv = Kv / Kv.normOfVec();
		return Kv;

	}

	Vector getJv()
	{
		Vector Jv(3), Kv(3), Iv(3);

		Kv = getKv();
		Iv = getIv();
		Jv = Kv.vectorMultiplication(Iv);


		return Jv;
	}

	void Drag3D(int X, int Y)
	{
		double deltaX = previousX - ScreenToWorldX(X);
		double VerN[] = { N[1],N[2],N[3],1 };
		Matrix<> VERN(4, 1, VerN);
		VERN = Translation(-T[1], -T[2], -T[3]) * VERN;
		if (deltaX > 0)
			VERN = RotationY(-0.01) * VERN;
		else
			VERN = RotationY(0.01) * VERN;
		VERN = Translation(T[1], T[2], T[3]) * VERN;
		for (int i = 1; i < 3; i++)
			N[i] = VERN(i, 1);

		UpdateCamera();
		

	}

};


#endif CAMERA_3D_H