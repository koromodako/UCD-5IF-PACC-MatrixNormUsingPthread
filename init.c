/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   init.c
Author: paul dautry
Date:   2016-10-19
Purpose:
    Contains function implementations related to matrix initialisation.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "init.h"
#include <stdlib.h>
/*-----------------------------------------------------------------------------
sqmat_fill
    Fill the matrix using the following function f(i,j)=(j<=i? 1: 0)
M [in]
    Square matrix to fill
n [in]
    Size of the square matrix
-----------------------------------------------------------------------------*/
void sqmat_fill(double **M, int n)
{
    int i, j;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            M[i][j]=(j<=i? 1: 0); 
        }
    }
}
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
void sqmat_fill_const(double **M, int n, double val)
{
    int i, j;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            M[i][j]=val; 
        }
    }
}
/*-----------------------------------------------------------------------------
sqmat_fill_mult
    Fill the matrix using the value returned by 
    f(i,j)=
M [in]
    Square matrix to initialize
n [in]
    Size of the square matrix
void [ret]
-----------------------------------------------------------------------------*/
void sqmat_fill_mult(double **M, int n)
{
    int i, j;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            M[i][j]=(j<=i? i+1-j: 0);
        }
    }   
}