#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
public:
	Scene2D(double L, double R, double B, double T) : Camera2D(L, R, B, T)
	{
	}
	void Plot(HDC dc, Func f, bool axes=true)
	{
		if (axes)
			Axes(dc);

		HPEN redPen, blackPen;
		redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(dc, redPen);
		SelectObject(dc, blackPen);

		// ���������� ������� ������� f
		// ����� ������������ � �������� ��������� ������� f ���������� ��� ������� �������:
		// f(x);
	}
};

#endif SCENE_2D_H
