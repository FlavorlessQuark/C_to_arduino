#ifndef VECTOR2_H
# define VECTOR2_H

# include "MT.h"

/*Returns a vector */
MT_Vector2 MT_V2FromAngle_Deg(double angle, double magnitude);
MT_Vector2 MT_V2FromAngle_Rad(double angle, double magnitude);

/*Returns a vector that is the result og basic math operations*/
MT_Vector2 MT_V2Sub(MT_Vector2 a, MT_Vector2 b);
MT_Vector2 MT_V2Add(MT_Vector2 a, MT_Vector2 b);
MT_Vector2 MT_V2Mult(MT_Vector2 a, double scalar);

double 		MT_V2Dot(MT_Vector2 a, MT_Vector2 b, double *angle);
MT_Vector2 	MT_V2Abs(MT_Vector2 a);
MT_Vector3 	MT_V2Cross(MT_Vector2 a, MT_Vector2 b, double angle);

/* Returns the angle between two vectors */
double MT_V2Angle_Rad(MT_Vector2 a, MT_Vector2 b);
double MT_V2Angle_Deg(MT_Vector2 a, MT_Vector2 b);

/*Returns a Vector that is the result of a rotation by the given angle (in degrees or radians)*/
MT_Vector2 MT_V2Rot_Deg(MT_Vector2 vec, double rot_angle);
MT_Vector2 MT_V2Rot_Rad(MT_Vector2 vec, double rot_angle);

/*Returns a vector that is opposite to the one given*/
MT_Vector2 MT_V2Invert(MT_Vector2 vec);
MT_Vector2 MT_V2Normalize(MT_Vector2 vec);

/*Returns the magnitude of a vector*/
double MT_V2Mag(MT_Vector2 vec);
/*Returns the angle of a vector relative to the x axis */
double MT_V2Heading180_Deg(MT_Vector2 vec);
double MT_V2Heading180_Rad(MT_Vector2 vec);

double MT_V2Heading360_Deg(MT_Vector2 vec);
double MT_V2Heading360_Rad(MT_Vector2 vec);

#endif
