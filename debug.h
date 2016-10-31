/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   debug.h
Author: paul dautry
Date:   2016-10-20
Purpose:
    This file contains the definitions of debug operations on matrices
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef _DEBUG_H_
#define _DEBUG_H_ 
/*-----------------------------------------------------------------------------
sqmat_print
    Print the content of a matrix
A [in]
    Matrix to print
n [in]
    Size of the matrix
int [ret]
-----------------------------------------------------------------------------*/
int sqmat_print(double **A, int n);

#endif /*_DEBUG_H_*/