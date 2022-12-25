#ifndef MODEL_3D_H
#define MODEL_3D_H

#include <string>
#include "Matrix.h"
#include"AffineTransform3D.h"

class Model3D
{
private:
	Matrix<> Vertices;
	Matrix<int> Verges;
	Matrix<> ComulativeAT;
	Matrix<> InitialVertices;

public:
	Model3D() : Vertices(), Verges(), InitialVertices(), ComulativeAT(Identity3D()) {}
	Model3D(const Matrix<> Vertices, const Matrix<int> Verges) :Vertices(Vertices), Verges(Verges),
		InitialVertices(Vertices), ComulativeAT(Identity3D()) {}

	void setVerAndVerg(Matrix<> Vertices, Matrix<int> Verges)
	{
		this->Vertices = Vertices;
		this->Verges = Verges;

		InitialVertices = Vertices;
		ComulativeAT = Identity3D();

	}

	/*int getCountEdges() { Matrix<int> Edges = getEdges(); return Edges.getCountRows(); }
	int getCountVertices() { return Vertices.getCountCols(); }*/
	int getCountVerges() { return Verges.getCountRows(); }

	Matrix<> GetVertices3D() { return Vertices; }
	Matrix<int> GetVerges() { return Verges; }

	/*double GetVertexX(int i) { return Vertices(1, i) / Vertices(4, i); }
	double GetVertexY(int i) { return Vertices(2, i) / Vertices(4, i); }
	double GetVertexZ(int i) { return Vertices(3, i) / Vertices(4, i); }

	int* getEdge(int i)
	{
		Matrix<int>Edges = getEdges();
		int* row = new int[2];
		for (int j = 0; j <= 1; j++)
		{
			row[j] = Edges(i, j + 1);
		}

		return row;

	}*/

	Matrix<int> getEdges()
	{
		Matrix<int> Edges(getCountVerges() * 3, 2);
		int j = 1;

		for (int i = 1; i <= getCountVerges(); i++)
		{
			Edges(j, 1) = Verges(i, 1);
			Edges(j, 2) = Verges(i, 2);
			j++;

			Edges(j, 1) = Verges(i, 1);
			Edges(j, 2) = Verges(i, 3);
			j++;

			Edges(j, 1) = Verges(i, 2);
			Edges(j, 2) = Verges(i, 3);
			j++;
		}

		return Edges;


	}

	void Apply3D(Matrix<> A)
	{
		ComulativeAT = A * ComulativeAT;
		Vertices = ComulativeAT * InitialVertices;
	}

	void Project(Matrix<> P)
	{
		Vertices = P * Vertices;
	}

};

#endif MODEL_3D_H