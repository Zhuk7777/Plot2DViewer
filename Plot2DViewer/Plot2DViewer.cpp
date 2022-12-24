#include <windows.h>
#include <windowsx.h>
#include"Data.h"
#include"Matrix.h"
#include"AffineTransform3D.h"
#include"Model3D.h"
#include"Scene3D.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основна€ процедура
{
	// ѕерва€ составл€юща€ часть основной процедуры - создание окна: сначала описываетс€ оконный класс wc, затем создаЄтс€ окно hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// им€ оконной процедуры, закрепленной за данным классом
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// идентификатор приложени€, содержащий адрес начала выделенной ему области пам€ти
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// им€ оконного класса, используемое при создании экземпл€ров окна
	RegisterClass(&wc);								// регистраци€ класса wc

	HWND hWnd = CreateWindow(						// hWnd - дескриптор, идентифицирующий окно; функци€ создани€ окна заполн€ет дескриптор hWnd ненулевым значением
		(LPCSTR)"MainWindowClass",					// им€ оконного класса
		(LPCSTR)"Plot2D Viewer",					// заголовок окна
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200,200,400,400,							// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ¬тора€ составл€юща€ часть основной процедуры - основной цикл обработки системных сообщений, который ожидает сообщени€ и рассылает их соответствующим окнам
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// функци€ GetMessage выбирает из очереди сообщение и заносит его в структуру msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// функци€ DispatchMessage оповещает систему о необходимости вызова оконной процедуры
	}

	return 0;
}

// ¬ основном модуле объ€вл€етс€ только одна глобальна€ переменна€ - создаЄтс€ объект класса Scene2D
// ¬се дальнейшие действи€ осуществл€ютс€ посредством обращени€ к методам, реализованным в этом классе
Scene3D scene(L,R,B,T);

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконна€ процедура принимает и обрабатывает все сообщени€, отправленные окну
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

	//	case 0x5A://1-ое задание
	//	{
	//		double x = scene.model.GetVertexX(1), y = scene.model.GetVertexY(1);
	//		scene.model.Apply(Translation(-x, -y));
	//		scene.model.Apply(Mapping());
	//		scene.model.Apply(Translation(x, y));
	//		break;
	//	}

	//	case 0x53://2-ое задание
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
