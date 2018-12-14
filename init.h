/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   init.h
Author: koromodako
Date:   2016-10-19
Purpose:
    Contains function definitions related to matrix initialisation.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef _INIT_H_
#define _INIT_H_
/*-----------------------------------------------------------------------------
sqmat_fill
    Fill the matrix using the following function f(i,j)=min(i,j)
M [in]
    Square matrix to fill
n [in]
    Size of the square matrix
-----------------------------------------------------------------------------*/
void sqmat_fill(double **M, int n);
/*-----------------------------------------------------------------------------
sqmat_fill_const
    Fill the given matrix with a constant value
M [in]
    Square matrix to fill
n [in]
    Size of the square matrix
val [in]
    Constant value to put in each cell of the matrix
void [ret]    
-----------------------------------------------------------------------------*/
void sqmat_fill_const(double **M, int n, double val);
/*-----------------------------------------------------------------------------
sqmat_fill_mult
    Fill the matrix using the value returned by 
    f(i,j,k)=sum[k=0..n](min(i,k)*min(k,j))
M [in]
    Square matrix to initialize
n [in]
    Size of the square matrix
void [ret]
-----------------------------------------------------------------------------*/
void sqmat_fill_mult(double **M, int n);

#endif /*_INIT_H_*/