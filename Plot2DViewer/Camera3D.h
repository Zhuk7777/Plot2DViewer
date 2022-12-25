#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include <windows.h>
#include"Camera2D.h"
#include"Vector.h"
#include"Matrix.h"

class Camera3D : public Camera2D
{
protected:
	Vector N, T, Ov;
	double F;

	Matrix<>WorldToView, ViewToProject, WorldToProject;

public:

	Camera3D(double L, double R, double B, double _T) :Camera2D(L, R, B, _T)
	{
		double coordinatesOv[3] = { 0,0,0 };
		setOv(coordinatesOv, 3);

		double coordinatesT[3] = { 1,2,3 };
		setT(coordinatesT, 3);

		double coordinatesN[3] = { 4,0,1 };
		setN(coordinatesN, 3);

		setF(25);

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

		double VP[16] = {
			1,0, 0,  0,
			0,1, 0,  0,
			0,0,-1 / F,1};

		ViewToProject.setMatrix(3, 4, VP);

		WorldToProject = ViewToProject * WorldToView;

	}

	/*void Axes(HDC dc)
	{
		HPEN cyanPen, blackPen, redPen;
		cyanPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
		blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(dc, cyanPen);

		Vector Iv(3), Jv(3), Kv(3);

		Iv = getIv();
		Jv = getJv();
		Kv = getKv();

		Iv = Iv * 100;
		Jv = Jv * 100;
		Kv = Kv * 100;

		Vector IvU(4), JvU(4), KvU(4);
		for (int i = 1; i <= 3; i++)
		{
			IvU[i] = Iv[i];
			JvU[i] = Jv[i];
			KvU[i] = Kv[i];
		}

		IvU[4] = 1;
		JvU[4] = 1;
		KvU[4] = 1;

		double** xyz
	}*/

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


};


#endif CAMERA_3D_H