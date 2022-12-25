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
		int verg[] = { 2,3,4,1,3,4,1,2,3,1,2,4 };
		Matrix<int> VERG(4, 3, verg);


		double vert[] = { 1,1,4,3,0,0,0,3,7,3,2,3,1,1,1,1 };
		Matrix<> VERT(4, 4, vert);


		model3d.setVerAndVerg(VERT, VERG);

		double xyzVer[] = {Ov[1],getIv()[1]*100,getJv()[1]*100,getKv()[1]*100,
						   Ov[2],getIv()[2]*100,getJv()[2]*100,getKv()[2]*100,
						   Ov[3],getIv()[3]*100,getJv()[3]*100,getKv()[3]*100,
		                   1,    1,             1,             1};

		Matrix<> XYZVER(4, 4, xyzVer);

		int xyzVerg[] = { 1,2,3,
						  1,4,3 };
		Matrix<int> XYZVERG(2, 3, xyzVerg);

		XYZ.setVerAndVerg(XYZVER, XYZVERG);

		/*double vertX[] = { Ov[1],getIv()[1],
					   Ov[2],getIv()[2],
					   Ov[3],getIv()[3],
					   1,    1 };

		int edgesX[] = { 1,2 };
		Matrix<> VertX(4, 3, vertX);
		Matrix<int> EdgesX(1, 2, edgesX);
		Model2D axisX(VertX, EdgesX);*/


	}

	void Render(HDC dc, bool axes = true)
	{
		XYZ.Project(ViewToProject);
		model3d.Project(WorldToProject);
		Model2D model2d(model3d.GetVertices3D(), model3d.getEdges());
		Model2D XYZ2D(XYZ.GetVertices3D(), XYZ.getEdges());
		
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

};



#endif SCENE_3D_H