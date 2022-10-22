#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:

	double L, R, B, T;					// ������� ���������� ������ ������� ������� ����
	int W, H;							// ���������� ������� ������� ����

	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return (X - L) / (R - L) * W;
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return (T - Y) / (T - B) * H;
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return L + (R - L) * (X + 0.5) / W;
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return T - (T - B) * (Y + 0.5) / H;
	}

private:

	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)

public:
	Camera2D(double L, double R, double B, double T) : L(L), R(R), B(B), T(T)
	{
		H = B - 1;
		W = R - 1;
		posX = 0.0;
		posY = 0.0;
	}
	void Clear(HDC dc)
	{
		Rectangle(dc, 0, 0, W, H);
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);

		W = r.right;
		H = r.bottom;

		B = (B + T) / 2 - (R - L) / 2 * H / W;
		T = (B + T) / 2 + (R - L) / 2 * H / W;

		// ������ ��������� ���������� ��� ��������� �������� ����
		// � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� L, R, B, T ����� �������, ����� ���������� ���������� �������� �� ������������ ����
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// ����������� ������������ ������� (posX, posY)
		// �������� ��������, ��� �� ��������� � ������� �����������
	}
	void LineTo(HDC dc, double X, double Y)
	{
		MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), NULL);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
	}
	void Axes(HDC dc)// ��������� ������������ ����
	{
		HPEN cyanPen, blackPen, redPen;
		cyanPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
		redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(dc, cyanPen);


		for(int i=L;i<=R;i++)
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

		MoveTo(0, B);//��� x
		LineTo(dc,0, T);

		MoveTo(L, 0);//��� y
		LineTo(dc, R, 0);
	}
};

#endif CAMERA_2D_H