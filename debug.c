/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   debug.c
Author: paul dautry
Date:   2016-10-20
Purpose:
    This file contains the implementation of debug operations listed  
    in debug.h 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "debug.h"
#include <stdio.h>
/*-----------------------------------------------------------------------------
sqmat_print
    Print the content of a matrix
A [in]
    Matrix to print
n [in]
    Size of the matrix
int [ret]
-----------------------------------------------------------------------------*/
int sqmat_print(double **A, int n)
{
    int ret, i, j;
    if (A==NULL||n<2) {
        ret=-1;
        goto end;
    }
    for (i=0; i<n; ++i) {
        printf("% 3d: ", i);
        for (j=0; j<n; ++j) {
            printf("% 10.2f ", A[i][j]);
        }
        printf("\n");
    }
    ret=0;
end:
    return ret;
}