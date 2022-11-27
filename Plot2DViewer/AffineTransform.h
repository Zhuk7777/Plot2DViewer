#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H
#include"Matrix.h"

Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Identity()//тождественное АП;
{
	double I[9] = {
		1,0,0,
		0,1,0,
		0,0,1 };
	return Matrix<>(3, 3, I);
}

Matrix<> Rotation(double t) //поворот на угол t;
{
	double R[9] = {
		cos(t),-sin(t),0,
		sin(t),cos(t),0,
		0,0,1 };
	return Matrix<>(3, 3, R);
}

Matrix<> Rotation(double c, double s)//поворот на угол, косинус и синус которого пропорциональны величинам c и s;
{
	double R[9] = {
		c,-s,0,
		s,c,0,
		0,0,1 };
	return Matrix<>(3, 3, R);
}

Matrix<> Scaling(double kx, double ky)//масштабирование;
{
	double S[9] = {
		kx,0,0,
		0,ky,0,
		0,0,1 };
	return Matrix<>(3, 3, S);
}

//Mapping(различные виды отражений)
Matrix<> MappingX()
{
	double M[9] = {
		1,0,0,
		0,-1,0,
		0,0,1 };
	return Matrix<>(3, 3, M);
}

Matrix<> MappingY()
{
	double M[9] = {
		-1,0,0,
		0,1,0,
		0,0,1 };
	return Matrix<>(3, 3, M);
}

Matrix<> Mapping()
{
	double M[9] = {
		-1,0,0,
		0,-1,0,
		0,0,1 };
	return Matrix<>(3, 3, M);
}

#endif AFFINE_TRANSFORM_H
