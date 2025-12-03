/*
 * This header contains all of the functions for matrix operations
 */
#ifndef MATRICES_H
# define MATRICES_H

# include "MT_structs.h"

/*Adds B to A */
void MT_MatrixAdd(MT_Matrix *a, MT_Matrix b);
/* Substracts B from A */
void MT_MatrixSub(MT_Matrix *a, MT_Matrix b);

/* Multiplies A by SCALAR*/
void MT_MatrixScale(MT_Matrix *a, double scalar);

/* @returns A matrix that is the result of the multiplication of A by B*/
MT_Matrix MT_MatrixMult(MT_Matrix a, MT_Matrix b);

/*Duplicates given matrix*/
MT_Matrix MT_MatrixDup(MT_Matrix mat);

#endif
