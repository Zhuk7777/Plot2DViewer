#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:

	double L, R, B, T;					// Мировые координаты границ рабочей области окна
	int W, H;							// Разрешение рабочей области окна

	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return (X - L) / (R - L) * W;
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return (T - Y) / (T - B) * H;
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		return L + (R - L) * ((double(X) + 0.5) / double(W));
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		return T - (T - B) * ((double(Y) + 0.5) / double(H));
	}

private:

	double posX = 0, posY = 0;// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
	bool isDragging = false;
	double previousX = 0, previousY = 0;

public:
	Camera2D(double L, double R, double B, double T) : L(L), R(R), B(B), T(T)
	{
	}
	void Clear(HDC dc)
	{
		Rectangle(dc, 0, 0, W, H);
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);

		W = r.right - 1;
		H = r.bottom - 1;

		double resolution = double(H) / double(W);

		double BNew = (B + T) / 2 - (R - L) / 2 * resolution;
		double TNew = (B + T) / 2 + (R - L) / 2 * resolution;

		B = BNew;
		T = TNew;
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
	}
	void LineTo(HDC dc, double X, double Y)
	{
		MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), NULL);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);
	}
	void Axes(HDC dc)// Отрисовка координатных осей
	{
		HPEN cyanPen, blackPen, redPen;
		cyanPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
		redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(dc, cyanPen);


		for (int i = L; i <= R; i++)
		{
			MoveTo(i, 0);
			LineTo(dc, i, T);
			MoveTo(i, 0);
			LineTo(dc, i, B);
		}

		for (int i = B; i <= T; i++)
		{
			MoveTo(0, i);
			LineTo(dc, L, i);
			MoveTo(0, i);
			LineTo(dc, R, i);
		}

		SelectObject(dc, blackPen);

		MoveTo(0, B);//ось x
		LineTo(dc, 0, T);

		MoveTo(L, 0);//ось y
		LineTo(dc, R, 0);
	}

	void StartDragging(int X, int Y)
	{
		previousX = ScreenToWorldX(X);
		previousY = ScreenToWorldY(Y);
		isDragging = true;

	}
	void Drag(int X, int Y)
	{
		double deltaX = previousX - ScreenToWorldX(X), deltaY = previousY - ScreenToWorldY(Y);// previousX - ScreenToWorldX(X) ,previousY - ScreenToWorldY(Y);
		double pX = (R - L) / W, pY = (T - B) / H;

		L = L + pX * deltaX*3;
		R = R + pX * deltaX*3;
		
		B = B + pY * deltaY*3;
		T = T + pY * deltaY*3;

	}
	void StopDragging()
	{
		isDragging = false;
	}
	bool IsDragging()
	{
		return isDragging;
	}

	void Move(double X, double Y)
	{
		double pX = (R - L) / W, pY = (T - B) / H;

		L = L + pX * X;
		R = R + pX * X;

		B = B + pY * Y;
		T = T + pY * Y;
	}

	void IncreaseSize(int X, int Y, double k)
	{
		k = 1 / k;

		double XWr = ScreenToWorldX(X);
		double YWr = ScreenToWorldY(Y);

		L = XWr - (XWr - L) * k;
		R = XWr + (R - XWr) * k;
		B = YWr - (YWr - B) * k;
		T = YWr + (T - YWr) * k;

	}

	void DecreaseSize(int X, int Y, double k)
	{
		double XWr = ScreenToWorldX(X);
		double YWr = ScreenToWorldY(Y);

		L = XWr - (XWr - L) * k;
		R = XWr + (R - XWr) * k;
		B = YWr - (YWr - B) * k;
		T = YWr + (T - YWr) * k;
	}
};

#endif CAMERA_2D_H
