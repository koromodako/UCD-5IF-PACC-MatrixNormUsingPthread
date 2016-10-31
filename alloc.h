/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   alloc.h
Author: paul dautry
Date:   2016-10-19
Purpose:
    This file defines the implementation of allocation/free operations on 
    matrices
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef _ALLOC_H_
#define _ALLOC_H_
/*-----------------------------------------------------------------------------
InitMode
    Enumeration of the modes used to initialize matrix's values
-----------------------------------------------------------------------------*/
typedef enum _InitMode {
    InitZero,
    InitConst,
    InitRand
} InitMode;
/*-----------------------------------------------------------------------------
sqmat_alloc
    Allocate memory to store (row-wise) a square matrix of size m    
M [out]
    Matrix
n [in]
    Size of the matrix
mode [in]
    Initialization mode for matrix values
init [in]
    Initial value of all the matrix
-----------------------------------------------------------------------------*/
int sqmat_alloc(double ***M, int n, InitMode mode, double init);
/*-----------------------------------------------------------------------------
sqmat_free
    Free memory used to store
M [in]
    Matrix
Mm [in]
    Matrix memory zone
-----------------------------------------------------------------------------*/
void sqmat_free(double **M);

#endif /* _ALLOC_H_ */