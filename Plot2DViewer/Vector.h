#ifndef VECTOR_H
#define VECTOR_H

#include<string>
#include<cmath>

class Vector
{
	double* elements;
	int size;

public:
	Vector(int obj_size=0) :size(obj_size)
	{
		elements = new double[size];
		for (int i = 0; i < size; i++)
			elements[i] = 0;
	}

	~Vector()
	{
		delete[]elements;
	}

	Vector(const Vector& obj)
	{
		size = obj.size;
		elements = new double[size];
		for (int i = 0; i < size; i++)
			elements[i] = obj.elements[i];
	}

	void setVector(double* obj, int obj_size)
	{
		size = obj_size;
		delete[]elements;
		elements = new double[size];

		for (int i = 0; i < size; i++)
			elements[i] = obj[i];
	}

	double scalarMultiplication(Vector obj)
	{
		double result = 0;
		for (int i = 0; i < size; i++)
			result += obj.elements[i] * elements[i];
		return result;
	}

	double normOfVec()
	{
		return sqrt(scalarMultiplication(*this));

	}

	double angleBetweenVectors(Vector obj)
	{
		double result = scalarMultiplication(obj);
		result /= normOfVec() * obj.normOfVec();
		result = acos(result);

		return result;

	}

	Vector vectorMultiplication(Vector obj)
	{
		Vector result(size);
		for (int i = 0; i < size; i++)
			result.elements[i] = elements[(i + 1) % size] * obj.elements[(i + 2) % size] - elements[(i + 2) % size] * obj.elements[(i + 1) % size];
		return result;
	}

	double& operator[](int ind)
	{
		return elements[ind - 1];
	}

	Vector& operator=(const Vector& obj)
	{
		size = obj.size;
		for (int i = 0; i < size; i++)
			elements[i] = obj.elements[i];

		return *this;
	}

	Vector& operator+(const Vector obj)
	{
		Vector result(size);
		for (int i = 0; i < size; i++)
			result.elements[i] = obj.elements[i] + elements[i];
		return result;
	}

	Vector& operator-(const Vector obj)
	{
		Vector result(size);
		for (int i = 0; i < size; i++)
			result.elements[i] = obj.elements[i] - elements[i];
		return result;
	}	

	Vector& operator/(double value)
	{
		for (int i = 0; i < size; i++)
			elements[i] /= value;
		return *this;
	}

	Vector& operator*(double value)
	{
		for (int i = 0; i < size; i++)
			elements[i] *= value;
		return *this;
	}

};
#endif VECTOR_H
