/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   mat_ops.h
Author: koromodako
Date:   2016-10-19
Purpose:
    This file contains the definition of operations on matrices.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef _MAT_OPS_H_
#define _MAT_OPS_H_
/*-----------------------------------------------------------------------------
Orientation
    Describe which orientation certain algorithm have to consider when working 
    on a matrix.
-----------------------------------------------------------------------------*/
typedef enum {
    Row,        /* row orientation */
    Column      /* column orientation */
} Orientation;
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
int sqmat_cmp(double **A, double **B, int n);
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
void sqmat_row_mult(double **A, double **B, double **R, 
                    int ridx, int n, int b);
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
void sqmat_mult(double **A, double **B, double **R, int n, int b);
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
double sqmat_vect_norm(double **M, int idx, Orientation o, int n);
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
double sqmat_one_norm(double **M, int n);


#endif /*_MAT_OPS_H_*/
 
