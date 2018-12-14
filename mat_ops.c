/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   mat_ops.c
Author: koromodako
Date:   2016-10-19
Purpose:
    This file contains the implementation of operations on matrices listed in 
    mat_ops.h
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "mat_ops.h"
#include <stdio.h>
/* return the positive value of val */
#define abs(val) ((val)>0? (val): -(val))
/* return the maximum value of a and b */
#define max(a,b) ((a)>(b)? (a): (b))
/*-----------------------------------------------------------------------------
sqmat_cmp
    Compare two square matrices to see if they are equal
A [in]
    First square matrix to compare
B [in]
    Second square matrix to compare
n [in]
    Size of the square matrix
int [ret]
    0 if matrices are equal,
    1 if matrices are not equal
-----------------------------------------------------------------------------*/
int sqmat_cmp(double **A, double **B, int n)
{
    int ret, i, j;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j) {
            if (A[i][j]!=B[i][j]) {
                ret=1;
                goto end;
            }
        }
    }
    ret=0;
end:
    return ret;
}
/*-----------------------------------------------------------------------------
sqmat_row_mult
    Fill ridx row of R matrix with the result of the multiplication of the 
    ridx row of A and all columns of B
A [in]
    First square matrix operand
B [in]
    Second square matrix operand
R [in]
    Result matrix
n [in]
    Size of the square matrix
b [in]
    Block size to use in square matrix multiplication
void [ret]
-----------------------------------------------------------------------------*/
void sqmat_row_mult(double **A, double **B, double **R, int ridx, int n, int b)
{
    int j, k, q, r, a;
    for (k=0; k<n/b; ++k) {
        for (j=0; j<n/b; ++j) {
            for (r= 0; r<b; ++r) {
                a = A[ridx][k*b+r];
                for (q=0; q<b; ++q) {
                    R[ridx][j*b+q] += a * B[k*b+r][j*b+q];
                }
            }
        }
    }
}
/*-----------------------------------------------------------------------------
sqmat_mult
    Fill R with the result of matrix multiplication of A and B using 
    kij-blocked algorithm
A [in]
    First square matrix operand
B [in]
    Second square matrix operand
R [in]
    Result matrix
n [in]
    Size of the square matrix
b [in]
    Block size to use in square matrix multiplication
void [ret]
-----------------------------------------------------------------------------*/
void sqmat_mult(double **A, double **B, double **R, int n, int b)
{
    int i, j, k, p, q, r, a;
    for (k=0; k<n/b; ++k) {
        for (i=0; i<n/b; ++i) {
            for (j=0; j<n/b; ++j) {
                for (r= 0; r<b; ++r) {
                    for (p=0; p<b; ++p) {
                        a = A[i*b+p][k*b+r];
                        for (q=0; q<b; ++q) {
                            R[i*b+p][j*b+q] += a * B[k*b+r][j*b+q];
                        }
                    }
                }
            }
        }
    }
}
/*-----------------------------------------------------------------------------
sqmat_vect_norm
    Compute the norm the idx-th row/column of n-by-n square matrix M depending
    on given orientation 
M [in]
    Matrix to use to compute the norm
idx [in]
    Index of the row/column in the matrix. /!\ Must be in [0,n-1]
o [in]
    Orientation describe if the operation concerns a Row or a Column
n [in]
    Size of the square matrix
double [ret]
    Norm value of given row/column
-----------------------------------------------------------------------------*/
double sqmat_vect_norm(double **M, int idx, Orientation o, int n)
{
    double norm=0.;
    int k;
    switch (o) {
        case Row:
            for (k=0; k<n; ++k) {
                norm += abs(M[idx][k]);
            }
            break;
        case Column:
            for (k=0; k<n; ++k) {
                norm += abs(M[k][idx]);
            }
            break;
    }
    return norm;
}
/*-----------------------------------------------------------------------------
sqmat_one_norm
    Computes the one-norm value of the n-by-n matrix M. 
M [in]
    Matrix for which the one-norm value must be computed
n [in]
    Size of the square matrix
double [ret]
    One-norm value of the matrix
-----------------------------------------------------------------------------*/
double sqmat_one_norm(double **M, int n) 
{
    int i, j;
    double norm=0, cnorm;
    for (j=0; j<n; ++j) {
        cnorm=0;
        for (i=0; i<n; ++i) {
            cnorm += abs(M[i][j]);
        }
        norm = max(norm, cnorm);
    }
    return norm;
}