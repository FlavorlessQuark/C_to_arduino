#ifndef VECTOR3_H
# define VECTOR3_H

# include "MT.h"

/*Returns a vector */
MT_Vector3 MT_V3FromAngle_Deg(double x_angle, double y_angle, double magnitude);
MT_Vector3 MT_V3FromAngle_Rad(double x_angle, double y_angle, double magnitude);

/*Returns a vector that is the result og basic math operations*/

MT_Vector3 MT_V3Sub(MT_Vector3 a, MT_Vector3 b);
MT_Vector3 MT_V3Add(MT_Vector3 a, MT_Vector3 b);
MT_Vector3 MT_V3Scale(MT_Vector3 a, double scalar);

double MT_V3Dot(MT_Vector3 a, MT_Vector3 b, double *angle);
double MT_V3Abs(MT_Vector3 a);

/* Returns the angle between two vectors */
double MT_V3Angle_Rad(MT_Vector3 a, MT_Vector2 b);
double MT_V3Angle_Deg(MT_Vector3 a, MT_Vector2 b);

/*Returns a Vector that is the result of a rotation by the given angle (in degrees or radians)*/

MT_Vector3 MT_V3Rot_Deg(MT_Vector3 vec, double rot_angle);
MT_Vector3 MT_V3Rot_Rad(MT_Vector3 vec, double rot_angle);

/*Returns a vector that is opposite to the one given*/
MT_Vector3 MT_V3Invert(MT_Vector3 vec);
MT_Vector3 MT_V3Normalize(MT_Vector3 vec);

/*Returns the magnitude of a vector*/
double MT_V3Mag(MT_Vector3 vec);

/*Returns the angle of a vector relative to the x axis */

double MT_V3Heading180_Deg(MT_Vector3 vec);
double MT_V3Heading180_Rad(MT_Vector3 vec);

double MT_V3Heading360_Deg(MT_Vector3 vec);
double MT_V3Heading360_Rad(MT_Vector3 vec);

#endif
