/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   mat_thd_ops.h
Author: paul dautry
Date:   2016-10-19
Purpose:
    This file contains the definition of thread routines operating on matrices
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef _MAT_THD_OPS_H_
#define _MAT_THD_OPS_H_
#include <pthread.h>
/*=============================================================================
                    Thread routines input structures
=============================================================================*/
/*-----------------------------------------------------------------------------
MatMultInput
-----------------------------------------------------------------------------*/
typedef struct {
    double **A;     /* first matrix operand */
    double **B;     /* second matrix operand */
    double **R;     /* result matrix */
    int n;          /* size of the matrix */
    int thd_count;  /* number of threads computing the matrix */
    int thd_num;    /* id of the thread */
} MatMultInput;
/*-----------------------------------------------------------------------------
MatOneNormInput
-----------------------------------------------------------------------------*/
typedef struct {
    double **M;                 /* matrix */
    int n;                      /* size of the matrix */
    int thd_num;                /* id of the thread */
    int thd_count;              /* number of threads computing the matrix */
    pthread_mutex_t *norm_mtx;  /* mutex of shared norm element */
    double *norm;               /* shared norm result */
} MatOneNormInput;
/*=============================================================================
                            Thread routines
=============================================================================*/
/*-----------------------------------------------------------------------------
sqmat_thd_mult
    Computes the multiplication for a slice of matrix
arg [in]
    MatMultInput structures containing parameters
void* [ret]
-----------------------------------------------------------------------------*/
void *sqmat_thd_mult(void *arg);
/*-----------------------------------------------------------------------------
sqmat_thd_one_norm
    Computes the one norm value for a slice of matrix
arg [in]
    MatOneNormInput structures containing parameters
void* [ret]
-----------------------------------------------------------------------------*/
void *sqmat_thd_one_norm(void *arg);

#endif /*_MAT_THD_OPS_H_*/