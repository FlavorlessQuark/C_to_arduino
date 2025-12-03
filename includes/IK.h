#ifndef IK_H
# define IK_H

# include "MT/MT.h"
# include "MT/MT_vec2.h"
# define TRUE	1
# define FALSE	0
# define JOINT_COUNT 3
# define MAX_ITER 10
# define MIN_DIST 1

typedef struct	Joint
{
	double		angle;
	double		length;
	MT_Vector2	vec;
}				IK_Joint;

typedef struct IK_Chain_t
{
	int				len;
	MT_Vector2		start;
	IK_Joint		chain[JOINT_COUNT];
}				IK_Chain;

// void    IK_Init(IK_Chain *chain);
int     IK_JointADD(IK_Chain *chain, double angle, double length);
void    IK_Solve(IK_Chain *chain, MT_Vector2 target);

#endif
