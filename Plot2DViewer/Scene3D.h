#ifndef SCENE_3D_H
#define SCENE_3D_H

#include "Camera3D.h"
#include"Model3D.h"

class Scene3D : public Camera3D
{
public:
	Model3D model;
	Scene3D(double _L, double _R, double _B, double _T) : Camera3D(_L, _R, _B, _T)
	{
		int e[] = { 1,2,1,3,1,4,1,5,2,3,3,4,3,5,4,5 };
		Matrix<int> E(8, 2, e);
		//int e[] = { 1,2,1,3,2,3 };
		/*Matrix<int> E(3, 2, e);*/



		double v[] = { 1,2,3,1,3,1,2,1,-1,-1,1,1,1,1,1 };
		Matrix<> V(3, 5, v);
		/*double v[] = { 1,3,3,2,2,1,1,1,1 };
		Matrix<> V(3, 3, v);*/

		model.setVerAndVerg(V, E);
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

};



#endif SCENE_3D_H