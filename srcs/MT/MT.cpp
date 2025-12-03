#include "../../includes/MT/MT.h"

int		MT_ToRad(int angle){return (int)MT_ToRadf(angle);}

double	MT_ToRadf(double angle)
{
	double result;

	result = angle * M_PI;
	result /= 180;

	return result;
}

/* Converts radians to degrees*/
double	MT_ToDegf(double angle)
{
	double result;

	result = angle * 180;
	result /= M_PI;

	return result;
}
int		MT_ToDeg(int angle)
{
	int result;

	result = angle * 180;
	result /= M_PI;

	return result;
}

/* Returns the square of the distance between two point */
double	MT_GetDistancef(double x1, double y1, double x2, double y2)
{
	double	d_x, d_y;

	d_x = x2 - x1;
	d_y = y2 - y1;
	return ((d_x * d_x) + (d_y * d_y));
}

int		MT_GetDistance(int x1, int y1, int x2, int y2)
{
	int	d_x, d_y;

	d_x = x2 - x1;
	d_y = y2 - y1;
	return ((d_x * d_x) + (d_y * d_y));
}

int		MT_ScaleNumber(int input, MT_Vector2 old_scale, MT_Vector2 new_scale)
{
	int		result;
	int		range;
	double	tmp;

	range = (old_scale.x - old_scale.y);

	tmp = input - old_scale.x;
	tmp /= range;
	tmp *= (new_scale.x - new_scale.y);
	result = tmp + new_scale.y;

	return result;
}

double		MT_ScaleNumberf(double input, MT_Vector2 old_scale, MT_Vector2 new_scale)
{
	double	result;
	double	range;
	double	tmp;

	range = (old_scale.y - old_scale.x);

	tmp = input - old_scale.x;
	tmp /= range;
	tmp *= (new_scale.y - new_scale.x);
	result = tmp + new_scale.x;

	return result;
}
double	MT_GetDistance2D(MT_Vector2 A, MT_Vector2 B)
{
	return MT_GetDistancef(A.x, A.y, B.x, B.y);
}

double	MT_GetDistance3D(MT_Vector3 A, MT_Vector3 B)
{
	double x;
	double y;
	double z;

	x = (B.x - A.x) * (B.x - A.x);
	y = (B.y - A.y) * (B.y - A.y);
	z = (B.z - A.z) * (B.z - A.z);

	return sqrt(x + y + z);
}
// int		MT_GCM(int a, int b)
// {
// 	int tmp;

// 	if (a == 0)
// 		return b;
// 	if (b == 0 || b == a)
// 		return a;

// 	//Figure out the binary algorithm here
// }

MT_circle MT_CircleInit(int size, MT_Vector2 origin)
{
	MT_circle circle;

	circle.origin = origin;
	circle.size = size;

	return circle;
}

int MT_GCD(int m, int n)
{
	int tmp;

	if (m > n)
	{
		tmp = m;
		m = n;
		n = tmp;
	}

	while (1)
	{
		m = m % n;
		if (!m)
			return (n < 0) ? (-n) : (n);
		n = n % m;
		if (!n)
			return (m < 0) ? (-m) : (m);
	}
}
