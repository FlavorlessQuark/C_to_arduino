#include "../includes/IK.h"


int IK_JointADD(IK_Chain *chain, double angle, double length)
{
	if (chain->len >= JOINT_COUNT)
		return 0;
	chain->chain[chain->len].angle = angle;
	chain->chain[chain->len].length = length;
	chain->len++;
	return 1;
}

// void IK_Init(IK_Chain *chain)
// {
	// chain = (IK_Chain *)calloc(JOINT_COUNT, sizeof(*chain));
// 	chain->len = 0;
// }

int CalcAngle(IK_Chain *chain, MT_Vector2 target, MT_Vector2 *endPoint)// flags bad, but how else..?
{
	int i;
	MT_Vector2	pos_to_target;
	MT_Vector2	pos_to_end;
	MT_Vector2	position;
	MT_Vector2	v_corrected;
	double		a_ptm;
	double		a_pte;
	double		angle;

	MT_Vector2 dvec;

	i = chain->len - 1;
	position = *endPoint;
	v_corrected = position;
	while (i >= 0)
	{
		if (MT_GetDistance2D(target, *endPoint) <= MIN_DIST)
			return 1;

		position.x -= chain->chain[i].vec.x;
		position.y -= chain->chain[i].vec.y;

		pos_to_end.x = position.x - endPoint->x;
		pos_to_end.y = position.y - endPoint->y;
		pos_to_target.x = position.x - target.x;
		pos_to_target.y = position.y - target.y;


		a_ptm = MT_V2Heading180_Deg(pos_to_target);
		a_pte = MT_V2Heading180_Deg(pos_to_end);
		chain->chain[i].angle += a_ptm - a_pte;
		dvec = MT_V2FromAngle_Deg(chain->chain[i].angle, chain->chain[i].length);

		endPoint->x -= chain->chain[i].vec.x - dvec.x;
		endPoint->y -= chain->chain[i].vec.y - dvec.y;
		dvec.x += position.x;
		dvec.y += position.y;
		i--;
	}

	return 	0;
}

void IK_Solve(IK_Chain *chain, MT_Vector2 target)
{
	int i;
	int iter;
	double angle;

	MT_Vector2 endPoint;

	i = 0;
	iter = 0;
	endPoint = chain->start;
	while (i < chain->len)
	{
		chain->chain[i].vec = MT_V2FromAngle_Deg(chain->chain[i].angle, chain->chain[i].length);

		endPoint.x += chain->chain[i].vec.x;
		endPoint.y += chain->chain[i].vec.y;
		i++;
	}

	while (iter < MAX_ITER)
	{
		if (CalcAngle(chain, target, &endPoint) == TRUE)
			return ;
		iter++;
	}
}
