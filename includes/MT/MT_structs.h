/// This header contains all the structs and types used in MT files

#ifndef  MT_STRUCTS_H
# define MT_STRUCTS_H

typedef struct	s_vect2
{
	double		x;
	double		y;
}				MT_Vector2;

typedef struct	s_vect3
{
	double		x;
	double		y;
	double		z;
}				MT_Vector3;

typedef struct	s_matrix
{
	int m;
	int n;
	double matrix[4][4];
}				MT_Matrix;

typedef struct s_circle
{
	MT_Vector2 	origin;
	int			size;
}				MT_circle;

typedef struct s_triangle2d
{
	MT_Vector2 a;
	MT_Vector2 b;
	MT_Vector2 c;
}				MT_Triangle2D;

typedef struct s_triangle3d
{
	MT_Vector3 a;
	MT_Vector3 b;
	MT_Vector3 c;
}				MT_Triangle3D;

#endif
