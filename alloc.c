/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   alloc.c
Author: paul dautry
Date:   2016-10-19
Purpose:
    This file contains the implementation of allocation/free operations listed 
    in alloc.h
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "alloc.h"
#include <stdlib.h>
#include <stdio.h>
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
int sqmat_alloc(double ***M, int n, InitMode mode, double init)
{
    int ret, i, j;
    /* test */
    if ((*M)!=NULL||n<2) {
        ret=-1;
        goto end;
    }
    /* alloc */
    (*M)=(double**)malloc(n*sizeof(double*));
    if (*M==NULL) {
        ret=-1;
        goto end;   
    }
    if (mode==InitRand||mode==InitConst) {
        (*M)[0]=(double*)malloc(n*n*sizeof(double));
    } else {
        (*M)[0]=(double*)calloc(n*n, sizeof(double));    
    }
    if ((*M)[0]==NULL) {
        ret=-1;
        goto end;   
    }
    /* init M */
    for (i=1; i<n; ++i) {
        (*M)[i]=(*M)[0]+i*n;
    }
    /* init M values */
    if (mode==InitConst) {
        for (i=0; i<n; ++i) {
            for (j=0; j<n; ++j) {
                (*M)[i][j]=init;
            }
        }
    }
    /* success */
    ret=0;
end:
    if (ret!=0) {
        sqmat_free(*M);
    }
    return ret;
}
/*-----------------------------------------------------------------------------
sqmat_free
    Free memory used to store
M [in]
    Matrix
Mm [in]
    Matrix memory zone
-----------------------------------------------------------------------------*/
void sqmat_free(double **M)
{
    if (M[0]!=NULL) {
        free(M[0]);
    }
    if (M!=NULL) {
        free(M);
    }
}
