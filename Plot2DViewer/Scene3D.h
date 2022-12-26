#ifndef SCENE_3D_H
#define SCENE_3D_H

#include "Camera3D.h"
#include"Model3D.h"
#include"Model2D.h"
#include"Vector.h"

class Scene3D : public Camera3D
{
public:
	Model3D model3d;
	Model3D XYZ;
	Scene3D(double _L, double _R, double _B, double _T) : Camera3D(_L, _R, _B, _T)
	{

		/*int verg[] = { 2,3,4,1,3,4,1,2,3,1,2,4 };
		Matrix<int> VERG(4, 3, verg);


		double vert[] = { 1,1,4,3,0,0,0,3,7,3,2,3,1,1,1,1 };
		Matrix<> VERT(4, 4, vert);*/

		double vert[] = { 1,1,1,1,0,0,0,0,
						  0,0,1,1,1,1,0,0,
						  0,1,0,1,0,1,0,1,
						  1,1,1,1,1,1,1,1 };
		Matrix<> VERT(4, 8, vert);

		int verg[] = {1,2,3,
		              2,3,4,
		              1,3,7,
		              3,5,7,
		              5,6,7,
		              6,7,8,
		              3,4,6,
		              3,5,6,
		              1,2,7,
		              2,7,8,
		              3,4,5,
		              4,5,6};
		Matrix<int> VERG(12, 3, verg);


		model3d.setVerAndVerg(VERT, VERG);


		double xyzVer[] = { 0,10,0, 0,
						    0,0, 10,0,
						    0,0, 0, 10, 
		                    1,1, 1, 1};
		Matrix<> XYZVER(4, 4, xyzVer);

		int xyzVerg[] = { 1,2,3,
						  1,4,3 };
		Matrix<int> XYZVERG(2, 3, xyzVerg);

		XYZ.setVerAndVerg(XYZVER, XYZVERG);

	}
	/*int ed[] = { 1,2,1,3,1,7,2,8,2,4,3,4,3,5,4,6,5,6,5,7,6,8,7,8 };
		Matrix<int> Edges2(11, 2, ed);*/
	void Render3D(HDC dc, bool axes = true)
	{
		Model2D model2d(model3d.Project(WorldToProject),model3d.getEdges());
		Model2D XYZ2D(XYZ.Project(WorldToProject), XYZ.getEdges());
		
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

		if (axes) {
			for (int i = 1; i <= XYZ2D.getCountEdges(); i++)
			{
				int* row = XYZ2D.getEdge(i);
				if (row[0] == 2 && row[1] == 3)
					continue;
				if (row[0] == 4 && row[1] == 3)
					continue;

				MoveTo(XYZ2D.GetVertexX(row[0]), XYZ2D.GetVertexY(row[0]));
				LineTo(dc, XYZ2D.GetVertexX(row[1]), XYZ2D.GetVertexY(row[1]));
			}
		}
	}

};



#endif SCENE_3D_H