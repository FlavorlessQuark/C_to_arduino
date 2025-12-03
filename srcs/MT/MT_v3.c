#include "MT_vec3.h"

MT_Vector3 MT_V3Sub(MT_Vector3 a, MT_Vector3 b)
{
	MT_Vector3 vec;

	vec.x = a.x - b.x; 
	vec.y = a.y - b.y; 
	vec.z = a.z - b.z;

	return vec;
}

MT_Vector3 MT_V3Add(MT_Vector3 a, MT_Vector3 b)
{
	MT_Vector3 vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;

	return vec;
}

MT_Vector3 MT_V3Scale(MT_Vector3 a, double scalar)
{
	MT_Vector3 vec;

	vec.x = a.x * scalar;
	vec.y = a.y * scalar;
	vec.z = a.z * scalar;

	return vec;
}

double MT_V3Abs(MT_Vector3 a)
{
	return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

double MT_V3Dot(MT_Vector3 a, MT_Vector3 b, double *angle)
{
	if (angle != NULL)
		return MT_V3Mag(a) * MT_V3Mag(a) * cos(*angle);
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

MT_Vector3 MT_V3FromAngle_Deg(double x_angle, double y_angle, double magnitude)
{
	MT_Vector3 result;

	result.x = cos(MT_ToRadf(y_angle)) * sin(MT_ToRadf(x_angle)) * magnitude;
	result.y = sin(MT_ToRadf(y_angle)) * magnitude;
	result.z = cos(MT_ToRadf(y_angle)) * cos(MT_ToRadf(x_angle)) * magnitude;

	return result;
}

MT_Vector3 MT_V3Normalize(MT_Vector3 vec)
{
	MT_Vector3 result;
	double mag;

	mag = MT_V3Mag(vec);

	result.x = vec.x / mag;
	result.y = vec.y / mag;
	result.z = vec.z / mag;

	return result;
}

double MT_V3Mag(MT_Vector3 vec)
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}