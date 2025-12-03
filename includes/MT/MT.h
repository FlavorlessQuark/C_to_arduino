/// This header consists of basic mathematical functions not present in math.h
/// Most of the functions below are simple conversions

#ifndef MT_H
# define MT_H

# include <math.h>
# include "MT_structs.h"


# ifndef M_PI
#  define M_PI (3.14159265358979323846)
# endif

#ifndef NULL
    # define NULL (void *)0x0
#endif
# define MAX(a, b)\
({ 	__typeof__ (a) _a = (a);\
	__typeof__ (b) _b = (b);\
	(_a > _b) ? (a) : (b);})\

# define MIN(a, b)\
({ 	__typeof__ (a) _a = (a);\
	__typeof__ (b) _b = (b);\
	(_a < _b) ? (a) : (b);})\

/* Converts degrees to radians*/
int		MT_ToRad(int angle);
double	MT_ToRadf(double angle);

/* Converts radians to degrees*/
int		MT_ToDeg(int angle);
double	MT_ToDegf(double angle);

/* Returns the square of the distance between two point */
double	MT_GetDistancef(double x1, double y1, double x2, double y2);
int		MT_GetDistance(int x1, int y1, int x2, int y2);

double	MT_GetDistance2D(MT_Vector2 A, MT_Vector2 B);
double	MT_GetDistance3D(MT_Vector3 A, MT_Vector3 B);

/* Scales a INPUT to a range
 * @param input : Number to be scaled
 * @param old_scale : the current range of the number where x = min and y = max
 * @param new_scale : the new range of the number where x = min and y = max
*/
double	MT_ScaleNumberf(double input, MT_Vector2 old_scale, MT_Vector2 new_scale);
/* Scales a INPUT to a range
 * @param input : Number to be scaled
 * @param old_scale : the current range of the number where x = min and y = max
 * @param new_scale : the new range of the number where x = min and y = max
*/
int		MT_ScaleNumber(int input, MT_Vector2 old_scale, MT_Vector2 new_scale);

int		MT_GCD(int m, int n);

int 	MT_LCM(int a, int b);

MT_circle MT_CircleInit(int size, MT_Vector2 origin);

#endif
