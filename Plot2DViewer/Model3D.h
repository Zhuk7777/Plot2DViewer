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

	Matrix<int> removingDuplicateInEdgeMatr(Matrix<int>Edges,int rows)
	{
		int* row = new int[2];
		int* indRows = new int[rows];

		for (int i = 0; i < rows; i++)
			indRows[i] = 0;

		for (int i = 2; i <= rows; i++)
		{
			row[0] = Edges(i, 1);
			row[1] = Edges(i, 2);
			if (isDuplicate(Edges, i - 1, row) == true)
				indRows[i - 1] = 1;
		}

		int countEdges = 0;
		for (int i = 0; i < rows; i++)
			if (indRows[i] == 0)
				countEdges++;

		int iNE = 1;
		Matrix<int> NewEdges(countEdges, 2);
		for (int i = 1; i <= rows; i++)
		{
			if (indRows[i - 1] != 1)
			{
				for (int j = 1; j <= 2; j++)
					NewEdges(iNE, j) = Edges(i, j);
				iNE++;
			}
		}

		return NewEdges;
	}

	bool isDuplicate(Matrix<int>Edges, int rows,int* row)
	{
		for (int i = 1; i <= rows; i++)
			if (row[0] == Edges(i, 1) && row[1] == Edges(i, 2))
				return true;

		return false;

	}

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

	int getCountEdges3D() { Matrix<int> Edges = getEdges(); return Edges.getCountRows(); }
	int getCountVertices3D() { return Vertices.getCountCols(); }
	int getCountVerges() { return Verges.getCountRows(); }

	Matrix<> GetVertices3D() { return Vertices; }
	Matrix<int> GetVerges() { return Verges; }

	double GetVertexX3D(int i) { return Vertices(1, i) / Vertices(4, i); }
	double GetVertexY3D(int i) { return Vertices(2, i) / Vertices(4, i); }
	double GetVertexZ3D(int i) { return Vertices(3, i) / Vertices(4, i); }

	int* getEdge3D(int i)
	{
		Matrix<int>Edges = getEdges();
		int* row = new int[2];
		for (int j = 1; j <= 2; j++)
		{
			row[j-1] = Edges(i, j);
		}

		return row;

	}

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

		Matrix<int> NewEdges;
		NewEdges = removingDuplicateInEdgeMatr(Edges, getCountVerges() * 3);

		return NewEdges;


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