#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include"Data.h"
#include"Model2D.h"


class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);

public:
	Model2D model;
	Scene2D(double _L, double _R, double _B, double _T) : Camera2D(_L, _R, _B, _T)
	{
		int e[] = { 1,2,1,3,1,4,1,5,2,3,3,4,3,5,4,5 };
		Matrix<int> E(8, 2, e);
		//int e[] = { 1,2,1,3,2,3 };
		/*Matrix<int> E(3, 2, e);*/

		

		double v[] = { 1,2,3,1,3,1,2,1,-1,-1,1,1,1,1,1 };
		Matrix<> V(3, 5, v);
		/*double v[] = { 1,3,3,2,2,1,1,1,1 };
		Matrix<> V(3, 3, v);*/

		model.setVerAndEd(V, E);
	}

	void Render(HDC dc, bool axes = true)
	{
		if (axes)
			Axes(dc);

		HPEN redPen, blackPen;
		redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(dc, redPen);

		for (int i = 1; i <= model.getCountEdges(); i++)
		{

			int* row = model.getEdge(i);
			MoveTo(model.GetVertexX(row[0]), model.GetVertexY(row[0]));
			LineTo(dc, model.GetVertexX(row[1]), model.GetVertexY(row[1]));
		}

		SelectObject(dc, blackPen);
	}

	void Plot(HDC dc, Func f,Func f2=NULL, bool axes=true)
	{
		if (axes)
			Axes(dc);

		HPEN redPen, blackPen;
		redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(dc, redPen);

		int n = W;
		double t;

		if (f2)
			MoveTo(f(tMin), f2(tMin));
		else
			MoveTo(tMin, f(tMin));

		for (int i = 1; i <= n; i++)
		{
			t = tMin + (tMax - tMin) * i / n;
			if (f2)
				LineTo(dc, f(t), f2(t));
			else
				LineTo(dc, t, f(t));

		}
		SelectObject(dc, blackPen);
	}
};

#endif SCENE_2D_H
