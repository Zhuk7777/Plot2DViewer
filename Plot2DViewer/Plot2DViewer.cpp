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
			scene.UpdateCamera();
			scene.Render3D(dc);
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

	case WM_KEYDOWN:
	{
		switch (wParam)
		{

		case VK_LEFT://0x58
		{
			scene.model3d.Apply3D(Translation(-0.5, 0, 0));
			break;

			/*if (::GetKeyState(0x52) & 0x8000)
				scene.model.Apply(Rotation(0.17));
			else if (::GetKeyState(0x54) & 0x8000)
				scene.model.Apply(Translation(-0.5, 0));
			else
			scene.Move(-4, 0);
			
			break;*/

		}

		case VK_RIGHT:
		{
			scene.model3d.Apply3D(Translation(0.5, 0, 0));
			break;

			/*if (::GetKeyState(0x52) & 0x8000)
				scene.model.Apply(Rotation(-0.17));
			else if (::GetKeyState(0x54) & 0x8000)
				scene.model.Apply(Translation(0.5, 0));
			else
				scene.Move(4, 0);
			break;*/
		}

		case VK_UP:
		{

			scene.model3d.Apply3D(Translation(0, 0.5, 0));
			break;
			/*if (::GetKeyState(0x54) & 0x8000)
				scene.model.Apply(Translation(0, 0.5));
			else
				scene.Move(0, 4);
			break;*/
		}

		case VK_DOWN:
		{
			scene.model3d.Apply3D(Translation(0, -0.5, 0));
			break;

			/*if (::GetKeyState(0x54) & 0x8000)
				scene.model.Apply(Translation(0, -0.5));
			else
				scene.Move(0, -4);
			break;*/
		}

		case 0x57:
		{
			scene.model3d.Apply3D(Translation(0, 0, 0.5));
			break;
		}

		case 0x53:
		{
			scene.model3d.Apply3D(Translation(0, 0, -0.5));
			break;
		}

		case VK_OEM_PLUS:
		{
			scene.model3d.Apply3D(Scaling(1.2, 1.2, 1.2));
			break;

		}

		case VK_OEM_MINUS:
		{
			scene.model3d.Apply3D(Scaling(0.8, 0.8, 0.8));
			break;
		}

		case 0x58:
		{
			scene.model3d.Apply3D(RotationX(0.17));
			break;
		}

		case 0x59:
		{

			scene.model3d.Apply3D(RotationY(0.17));
			break;
		}

		case 0x5A:
		{
			scene.model3d.Apply3D(RotationZ(0.17));
			break;
		}

		case 0x4D:
		{
			scene.model3d.Apply3D(Mapping3D());
			break;
		}


		case 0x31:
		{
			double coordinatesOv[3] = { 3,3,8 };
			scene.setOv(coordinatesOv, 3);

			double coordinatesT[3] = { 0,1,0 };
			scene.setT(coordinatesT, 3);

			double coordinatesN[3] = { 0,0,1 };
			scene.setN(coordinatesN, 3);
			break;
		}

		case 0x32:
		{
			double coordinatesOv[3] = { 4,4,4 };
			scene.setOv(coordinatesOv, 3);

			double coordinatesT[3] = { 0,1,0 };
			scene.setT(coordinatesT, 3);

			double coordinatesN[3] = { 1,1,1 };
			scene.setN(coordinatesN, 3);
			break;
		}

		case 0x33:
		{
			double coordinatesOv[3] = { 3,3,4 };
			scene.setOv(coordinatesOv, 3);

			double coordinatesT[3] = { 0,1,0 };
			scene.setT(coordinatesT, 3);

			double coordinatesN[3] = { 1,0,0 };
			scene.setN(coordinatesN, 3);
			break;
		}

		case 0x34://4 - ��������� ����� x
		{
			scene.model3d.Apply3D(Mapping3Dx());
			break;
		}

		case 0x35://5- ��������� ����� y
		{
			scene.model3d.Apply3D(Mapping3Dy());
			break;
		}

		case 0x36://6-��������� ����� z
		{
			scene.model3d.Apply3D(Mapping3Dz());
			break;
		}

		case 0x37://7-��������� ����� xy
		{
			scene.model3d.Apply3D(MappingXY());
			break;
		}

		case 0x38://8-��������� ����� zx
		{
			scene.model3d.Apply3D(MappingZX());
			break;
		}

		case 0x39://9-��������� ����� yz
		{
			scene.model3d.Apply3D(MappingYZ());
			break;
		}


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


		}
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}


	case WM_MOUSEWHEEL:
	{
		/*if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			scene.IncreaseSize(pt.x, pt.y, 1.2);
		else
			scene.DecreaseSize(pt.x, pt.y, 1.2);
		InvalidateRect(hWnd, nullptr, false);
		return DefWindowProc(hWnd, msg, wParam, lParam);*/
		double F = scene.getF();
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			F *= 1.1;
			scene.setF(F);
		}
		else
		{
			F *= 0.9;
			scene.setF(F);
		}
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
