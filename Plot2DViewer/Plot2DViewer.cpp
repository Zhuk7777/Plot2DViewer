#include <windows.h>
#include <windowsx.h>
#include"Data.h"
#include"Matrix.h"
#include"AffineTransform3D.h"
#include"Model3D.h"
#include"Scene3D.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� �������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Plot2D Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200,200,400,400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Scene2D
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������
Scene3D scene(L,R,B,T);

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	POINT pt;
	pt.x = GET_X_LPARAM(lParam);
	pt.y = GET_Y_LPARAM(lParam);
	ScreenToClient(hWnd, &pt);
	switch(msg)
	{
	case WM_PAINT:
		{
			HDC dc = GetDC(hWnd);
			scene.Clear(dc);
			scene.Render(dc);
			//scene.Plot(dc, Sinusoid, nullptr, false);
			ReleaseDC(hWnd,dc);
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}

	case WM_SIZE:
		{
			HDC dc = GetDC(hWnd);
			scene.SetResolution(dc);
			ReleaseDC(hWnd,dc);
			InvalidateRect(hWnd,nullptr,false);
			return 0;
		}

	case WM_LBUTTONDOWN:
	{
		
		scene.StartDragging(pt.x, pt.y);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (scene.IsDragging())
		{
			scene.Drag(pt.x, pt.y);
			InvalidateRect(hWnd, nullptr, false);
		}
		return 0;
	}
	case WM_LBUTTONUP:
	{
		scene.StopDragging();
		return 0;
	}

	//case WM_KEYDOWN:
	//{
	//	switch (wParam)
	//	{

	//	case VK_LEFT:
	//	{
	//		if (::GetKeyState(0x52) & 0x8000)
	//			scene.model.Apply(Rotation(0.17));
	//		else if (::GetKeyState(0x54) & 0x8000)
	//			scene.model.Apply(Translation(-0.5, 0));
	//		else
	//		scene.Move(-4, 0);
	//		
	//		break;
	//	}

	//	case VK_RIGHT:
	//	{
	//		if (::GetKeyState(0x52) & 0x8000)
	//			scene.model.Apply(Rotation(-0.17));
	//		else if (::GetKeyState(0x54) & 0x8000)
	//			scene.model.Apply(Translation(0.5, 0));
	//		else
	//			scene.Move(4, 0);
	//		break;
	//	}

	//	case VK_UP:
	//	{
	//		if (::GetKeyState(0x54) & 0x8000)
	//			scene.model.Apply(Translation(0, 0.5));
	//		else
	//			scene.Move(0, 4);
	//		break;
	//	}

	//	case VK_DOWN:
	//	{
	//		if (::GetKeyState(0x54) & 0x8000)
	//			scene.model.Apply(Translation(0, -0.5));
	//		else
	//			scene.Move(0, -4);
	//		break;
	//	}

	//	case VK_OEM_PLUS:
	//	{
	//		scene.model.Apply(Scaling(1.2, 1.2));
	//		break;

	//	}

	//	case VK_OEM_MINUS:
	//	{
	//		scene.model.Apply(Scaling(0.8, 0.8));
	//		break;
	//	}

	//	case 0x58:
	//	{
	//		scene.model.Apply(MappingX());
	//		break;
	//	}

	//	case 0x59:
	//	{
	//		scene.model.Apply(MappingY());
	//		break;
	//	}

	//	case 0x4D:
	//	{
	//		scene.model.Apply(Mapping());
	//		break;
	//	}

	//	case 0x5A://1-�� �������
	//	{
	//		double x = scene.model.GetVertexX(1), y = scene.model.GetVertexY(1);
	//		scene.model.Apply(Translation(-x, -y));
	//		scene.model.Apply(Mapping());
	//		scene.model.Apply(Translation(x, y));
	//		break;
	//	}

	//	case 0x53://2-�� �������
	//	{
	//		scene.model.Apply(Translation(0, 4));
	//		scene.model.Apply(Rotation(-0.46));
	//		//scene.model.Apply(Scaling(1.2, 1));
	//		scene.model.Apply(MappingX());
	//		scene.model.Apply(Rotation(0.46));
	//		scene.model.Apply(Translation(0, -4));
	//		break;

	//	}


	//	}
	//	InvalidateRect(hWnd, nullptr, false);
	//	return 0;
	//}


	case WM_MOUSEWHEEL:
	{
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			scene.IncreaseSize(pt.x, pt.y, 1.2);
		else
			scene.DecreaseSize(pt.x, pt.y, 1.2);
		InvalidateRect(hWnd, nullptr, false);
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

	default:
		{
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	}
	return 0;
}
