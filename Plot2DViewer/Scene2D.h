#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include"Data.h"


class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
public:
	Scene2D(double _L, double _R, double _B, double _T) : Camera2D(_L, _R, _B, _T)
	{
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
