#include "../../includes/MT/MT_vec2.h"

static double convert_180(double angle)
{
	if (angle < 0)
		angle = (angle * -1) + 180;
	return angle;
}

/*Returns a vector */
MT_Vector2 MT_V2FromAngle_Deg(double angle, double magnitude)
{
	MT_Vector2 vec;

	vec.x = cos(MT_ToRadf(angle)) * magnitude;
	vec.y = sin(MT_ToRadf(angle)) * magnitude;

	return vec;
}

MT_Vector2 MT_V2FromAngle_Rad(double angle, double magnitude)
{
	MT_Vector2 vec;

	vec.x = cos(angle) * magnitude;
	vec.y = sin(angle) * magnitude;

	return vec;
}

/*Returns a vector that is the result og basic math operations*/
MT_Vector2 MT_V2Sub(MT_Vector2 a, MT_Vector2 b)
{
	MT_Vector2 vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;

	return vec;
}

MT_Vector2 MT_V2Add(MT_Vector2 a, MT_Vector2 b)
{
	MT_Vector2 vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;

	return vec;
}

MT_Vector2 MT_V2Scale(MT_Vector2 vec, double scalar)
{
	MT_Vector2 new_vec;

	new_vec.x = vec.x * scalar;
	new_vec.y = vec.y * scalar;

	return new_vec;
}

double MT_V2Dot(MT_Vector2 a, MT_Vector2 b, double* angle)
{
	if (angle != NULL)
		return MT_V2Mag(a) * MT_V2Mag(a) * cos(*angle);
	return (a.x * b.x) + (a.y * b.y);
}

MT_Vector2 MT_V2Abs(MT_Vector2 a)
{
	MT_Vector2 result;

	result.x = fabs(a.x);
	result.y = fabs(a.y);
	return result;
}

/* Returns the angle between two vectors */
double MT_V2Angle_Rad(MT_Vector2 a, MT_Vector2 b)
{
	double angle, m_a, m_b;

	m_a = sqrt(MT_V2Mag(a));
	m_b = sqrt(MT_V2Mag(b));
	angle = (a.x * a.y) + (b.x * b.y);
	angle /= (m_a * m_b);

	return acos(angle);
}

double MT_V2Angle_Deg(MT_Vector2 a, MT_Vector2 b)
{
	return (MT_ToDegf(MT_V2Angle_Rad(a, b)));
}

/*Returns a Vector that is the result of a rotation by the given angle (in degrees or radians)*/
MT_Vector2 MT_V2Rot_Deg(MT_Vector2 vec, double rot_angle)
{
	double current_angle;

	current_angle =  MT_V2Heading360_Deg(vec);
	current_angle += rot_angle;
	while (current_angle > 360)
		current_angle -= 360;
	while (current_angle < 0)
		current_angle += 360;

	return MT_V2FromAngle_Deg(current_angle, MT_V2Mag(vec));
}

MT_Vector2 MT_V2Rot_Rad(MT_Vector2 vec, double rot_angle){
	return MT_V2Rot_Deg(vec, MT_ToDegf(rot_angle));
}

/*Returns a vector that is opposite to the one given*/
MT_Vector2 MT_V2Invert(MT_Vector2 vec)
{
	MT_Vector2 new_vec;

	new_vec.x = vec.x * -1;
	new_vec.y =	vec.y * -1;
	return new_vec;
}

MT_Vector2 MT_V2Normalize(MT_Vector2 vec)
{
	MT_Vector2 result;
	double mag;

	mag = MT_V2Mag(vec);
	result.x = vec.x / mag;
	result.y = vec.y / mag;

	return result;
}

/*Returns the square of the magnitude of a vector*/
double MT_V2Mag(MT_Vector2 vec)
{
	return sqrt(MT_GetDistancef(0, 0, vec.x, vec.y));
}

/*Returns the angle of a vector relative to the x axis */
double  MT_V2Heading180_Deg(MT_Vector2 vec){ return MT_ToDegf(atan2(vec.y, vec.x));}
double  MT_V2Heading180_Rad(MT_Vector2 vec){ return atan2(vec.y, vec.x); }


double  MT_V2Heading360_Deg(MT_Vector2 vec)
{
	double angle;

	angle = MT_ToDegf(atan2(vec.y, vec.x));

	return convert_180(angle);
}

double  MT_V2Heading360_Rad(MT_Vector2 vec)
{
	return MT_ToRadf(MT_V2Heading180_Deg(vec));
}
