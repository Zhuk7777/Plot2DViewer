#ifndef SCENE_3D_H
#define SCENE_3D_H

#include "Camera3D.h"
#include"Model3D.h"
#include"Model2D.h"

class Scene3D : public Camera3D
{
public:
	Model3D model3d;
	Scene3D(double _L, double _R, double _B, double _T) : Camera3D(_L, _R, _B, _T)
	{
		int verg[] = { 2,3,4,1,3,4,1,2,3,1,2,4 };
		Matrix<int> VERG(4, 3, verg);


		double vert[] = { 1,1,4,3,0,0,0,3,7,3,2,3,1,1,1,1 };
		Matrix<> VERT(4, 4, vert);


		model3d.setVerAndVerg(VERT, VERG);
	}

	void Render(HDC dc, bool axes = true)
	{
		/*if (axes)
			Axes(dc);*/

		model3d.Project(WorldToProject);
		Model2D model2d(model3d.GetVertices3D(), model3d.getEdges());
		
		HPEN redPen, blackPen;
		redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(dc, redPen);

		for (int i = 1; i <= model2d.getCountEdges(); i++)
		{

			int* row = model2d.getEdge(i);
			MoveTo(model2d.GetVertexX(row[0]), model2d.GetVertexY(row[0]));
			LineTo(dc, model2d.GetVertexX(row[1]), model2d.GetVertexY(row[1]));
		}

		SelectObject(dc, blackPen);
	}

};



#endif SCENE_3D_H