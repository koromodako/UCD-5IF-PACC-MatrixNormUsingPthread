/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   main.c
Author: koromodako
Date:   2016-10-21
Purpose:
    Contains program entry point and parallel and serial code functions.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "alloc.h"
#include "init.h"
#include "debug.h"
#include "mat_ops.h"
#include "mat_thd_ops.h"
#include "time_macro.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
/*=============================================================================
                                Global variables
=============================================================================*/
double **A;
double **B;
double **R;
int n;
int p;
int initialized;
/*=============================================================================
                               Function prototypes
=============================================================================*/
int cpu_count(void);
int init(void);
int serial_code(void);
int parallel_code(void);
void terminate(void);
/*=============================================================================
                                 Main function
=============================================================================*/
int main(int argc, char **argv)
{
    int ret;
    double norm;
    DECL_TIMEIT_VARS();
    initialized=0;
    if ((p=cpu_count())<0) {
        ret=-1;
        goto end;
    }
    printf("[INF] %d processors available.\n", p);
    if (argc<3) {
        printf("[ERR] Usage: ./distmatnorm <int:N> (serial|parallel)\n");
        ret=-1;
        goto end;
    }
    n = atoi(argv[1]);
    if (n==0||n%p!=0) {
        printf("[ERR] mat_size must be above zero and a multiple of processor"
               " count!\n");
        ret=-1;
        goto end;
    }
    printf("[INF] Running with square matrices of size %d.\n", n);
    if (init()!=0) {
        printf("[ERR] Initialization failed! Aborting.\n");
        ret=-1;
        goto end;
    }
    if (!strcmp(argv[2],"serial")) {
        printf("[INF] Running serial code...\n");
        TIMEIT("serial_code took %.5f seconds to execute.\n", 
            norm, serial_code);
    } else if (!strcmp(argv[2],"parallel")) {
        printf("[INF] Running in parallel code...\n");
        TIMEIT("parallel_code took %.5f seconds to execute.\n", 
            norm, parallel_code);
    } else {

        printf("[ERR] Version is not serial or parallel!\n");
        ret=-1;
        goto end;
    }
    printf("[INF] Norm is %.3f in %.5f seconds\n", norm, elapsed);
    ret=0;
end:
    terminate();
    return ret;
}
/*=============================================================================
                             Function realisations
=============================================================================*/
int cpu_count(void)
{
    FILE *fp;
    int ret, h=0, eol=0, c;
    /* Open the command for reading. */
    fp = popen("lscpu -p=cpu", "r");
    if (fp == NULL) {
        printf("[ERR] Failed to run lscpu!\n" );
        ret=-1;
        goto end;
    }
    /* Read the output a line at a time - output it. */
    do {
        c = fgetc(fp);
        if (c=='#') {
            h++;
        } else if(c=='\n') {
            eol++;
        }
    } while(c!=EOF);
    ret=eol-h;
    /* close */
    pclose(fp);
end:
    return ret;
}

int init(void)
{
    printf("[INF] Allocating memory...");
    int ret;
    if ((ret=sqmat_alloc(&A, n, InitRand, 0.))!=0) {
        goto end;
    }
    if ((ret=sqmat_alloc(&B, n, InitRand, 0.))!=0) {
        goto end;
    }
    if ((ret=sqmat_alloc(&R, n, InitZero, 0.))!=0) {
        goto end;
    }
    printf("done.\n[INF] Filling matrices...");
    sqmat_fill(A, n);
    sqmat_fill(B, n);
    printf("done.\n");
    initialized=1;
    ret=0;
end:
    if (ret!=0) {
        printf("error!\n");
    }
    return ret;
}

int serial_code(void)
{
    sqmat_mult(A, B, R, n, n/p);
    return sqmat_one_norm(R, n);
}

int parallel_code(void)
{
    /* shared variables */
    int k;
    void *status;
    pthread_mutex_t norm_mtx;
    double norm=0;
    /* init mutex */
    pthread_mutex_init(&norm_mtx, NULL);
    /* alloc arrays */
    pthread_t *thrds=(pthread_t*)malloc(p*sizeof(pthread_t));
    MatMultInput *mmi=(MatMultInput*)malloc(p*sizeof(MatMultInput));
    MatOneNormInput *moni=(MatOneNormInput*)malloc(p*sizeof(MatOneNormInput));
    /* step 1 : parallel matrix multiplication */
    for (k=0; k<p; ++k) {
        mmi[k].A=A;
        mmi[k].B=B;
        mmi[k].R=R;
        mmi[k].n=n;
        mmi[k].thd_count=p;
        mmi[k].thd_num=k;
        pthread_create(&(thrds[k]), NULL, sqmat_thd_mult, (void*)&(mmi[k]));
    }
    for (k=0; k<p; ++k) {
        pthread_join(thrds[k], &status);
    }
    /* step 2 : parallel matrix one-norm */
    for (k=0; k<p; ++k) {
        moni[k].M=R;
        moni[k].n=n;
        moni[k].thd_count=p;
        moni[k].thd_num=k;
        moni[k].norm_mtx=&norm_mtx;
        moni[k].norm=&norm;
        pthread_create(&(thrds[k]), NULL, 
                       sqmat_thd_one_norm, (void*)&(moni[k]));   
    }
    for (k=0; k<p; ++k) {
        pthread_join(thrds[k], &status);
    }
    /* free */
    free(moni);
    free(mmi);
    free(thrds);
    /* destroy mutex */
    pthread_mutex_destroy(&norm_mtx);
    /* ret */
    return norm;
}

void terminate(void)
{
    if (initialized==1) {
        printf("[INF] Terminating...");
        sqmat_free(R);
        sqmat_free(B);
        sqmat_free(A);
        printf("done!\n");
    }
}