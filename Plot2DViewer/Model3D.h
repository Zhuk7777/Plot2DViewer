#ifndef MODEL_3D_H
#define MODEL_3D_H

#include <string>
#include "Matrix.h"
#include"AffineTransform3D.h"

class Model2D
{
private:
	Matrix<> Vertices;
	Matrix<int> Edges;
	Matrix<int>
	Matrix<> ComulativeAT;
	Matrix<> InitialVertices;

public:
	Model2D() : Vertices(), Edges(), InitialVertices(), ComulativeAT(Identity()) {}
	Model2D(const Matrix<> Vertices, const Matrix<int> Edges) :Vertices(Vertices), Edges(Edges),
		InitialVertices(Vertices), ComulativeAT(Identity()) {}

	void setVerAndEd(Matrix<> Vertices, Matrix<int> Edges)
	{
		this->Vertices = Vertices;
		this->Edges = Edges;

		InitialVertices = Vertices;
		ComulativeAT = Identity();

	}

	int getCountEdges() { return Edges.getCountRows(); }
	int getCountVertices() { return Vertices.getCountCols(); }

	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }

	double GetVertexX(int i) { return Vertices(1, i) / Vertices(3, i); }
	double GetVertexY(int i) { return Vertices(2, i) / Vertices(3, i); }

	int* getEdge(int i)
	{
		int* row = new int[2];
		for (int j = 0; j <= 1; j++)
		{
			row[j] = Edges(i, j + 1);
		}

		return row;

	}

	void Apply(Matrix<> A)
	{
		ComulativeAT = A * ComulativeAT;
		Vertices = ComulativeAT * InitialVertices;
	}

};

#endif MODEL_2D_H