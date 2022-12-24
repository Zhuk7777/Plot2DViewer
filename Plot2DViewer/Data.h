#define _USE_MATH_DEFINES
#include <cmath>

double					// Исходные значения параметров L, R, B, T
	L=-5,
	R=5,
	B=-5,
	T=5;

double//границы интервала и значения постоянных a,b,p
   tMin = -6.3,
   tMax = 12.5,
   a = 1,
   b = 2,
   p = 1;

double Parabola(double x)
{
	return x*x-2;
}

double Sinusoid(double x)
{
	return sin(x);
}

double xElliptical(double fi)
{
	return a * p * cos(fi);
}

double yElliptical(double fi)
{
	return b * p * sin(fi);
}

double laba2(double x)
{
	return (0.5 * x) - 4;
}
