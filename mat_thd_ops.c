/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   mat_thd_ops.c
Author: koromodako
Date:   2016-10-19
Purpose:
    This file contains the implementation of thread routines operating on 
    matrices listed in mat_thd_ops.h 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "mat_thd_ops.h"
#include "mat_ops.h"
/* return the maximum value of a and b */
#define max(a,b) ((a)>(b)? (a): (b))
/*-----------------------------------------------------------------------------
sqmat_thd_mult
    Computes the multiplication for a slice of matrix
arg [in]
    MatMultInput structures containing parameters
void* [ret]
-----------------------------------------------------------------------------*/
void *sqmat_thd_mult(void *arg)
{
    int k, rc;
    MatMultInput *input = (MatMultInput*)(arg);
    rc=input->n/input->thd_count;
    for (k=0; k<rc; ++k) {
        sqmat_row_mult(input->A, input->B, input->R, 
                       input->thd_num*rc+k, 
                       input->n, 
                       input->thd_count);    
    }
    pthread_exit(NULL);
}
/*-----------------------------------------------------------------------------
sqmat_thd_one_norm
    Computes the one norm value for a slice of matrix
arg [in]
    MatOneNormInput structures containing parameters
void* [ret]
-----------------------------------------------------------------------------*/
void *sqmat_thd_one_norm(void *arg)
{
    int k, rc;
    double lnorm=0;
    MatOneNormInput *input = (MatOneNormInput*)(arg);
    rc = input->n/input->thd_count;
    for (k=0; k<rc; ++k) {
        lnorm = max(lnorm, 
                    sqmat_vect_norm(input->M, 
                                    input->thd_num*rc+k, 
                                    Column, 
                                    input->n));
    }
    pthread_mutex_lock(input->norm_mtx);
    *(input->norm) = max(lnorm, *(input->norm));
    pthread_mutex_unlock(input->norm_mtx);
    pthread_exit(NULL);
}