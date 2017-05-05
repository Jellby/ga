/* $Id: matmul.h,v 1.15.4.1 2006-12-22 13:05:22 manoj Exp $ */
#ifndef _MATMUL_H_
#define _MATMUL_H_

#include "ga.h"
#include "global.h"
#include "globalp.h"
#include "message.h"
#include "base.h"

#if HAVE_MATH_H
#   include <math.h>
#endif
#include "armci.h"

#define sgemm_ F77_FUNC(sgemm,SGEMM)
#define dgemm_ F77_FUNC(dgemm,DGEMM)
#define zgemm_ F77_FUNC(zgemm,ZGEMM)
#define cgemm_ F77_FUNC(cgemm,CGEMM)

#if NOFORT
#   define BlasInt int
#elif BLAS_SIZE == SIZEOF_F77_INTEGER
#   define BlasInt Integer
#elif BLAS_SIZE == SIZEOF_SHORT
#   define BlasInt short
#elif BLAS_SIZE == SIZEOF_INT
#   define BlasInt int
#elif BLAS_SIZE == SIZEOF_LONG
#   define BlasInt long
#elif BLAS_SIZE == SIZEOF_LONG_LONG
#   define BlasInt long long
#endif

#if defined(F2C_HIDDEN_STRING_LENGTH_AFTER_ARGS)
extern void sgemm_(char *TRANSA, char *TRANSB, BlasInt *M, BlasInt *N, BlasInt *K, Real *ALPHA, Real *A, BlasInt *LDA, Real *B, BlasInt *LDB, Real *BETA, Real *C, BlasInt *LDC, int alen, int blen);
extern void dgemm_(char *TRANSA, char *TRANSB, BlasInt *M, BlasInt *N, BlasInt *K, DoublePrecision *ALPHA, DoublePrecision *A, BlasInt *LDA, DoublePrecision *B, BlasInt *LDB, DoublePrecision *BETA, DoublePrecision *C, BlasInt *LDC, int alen, int blen);
extern void zgemm_(char *TRANSA, char *TRANSB, BlasInt *M, BlasInt *N, BlasInt *K, DoubleComplex *ALPHA, DoubleComplex *A, BlasInt *LDA, DoubleComplex *B, BlasInt *LDB, DoubleComplex *BETA, DoubleComplex *C, BlasInt *LDC, int alen, int blen);
extern void cgemm_(char *TRANSA, char *TRANSB, BlasInt *M, BlasInt *N, BlasInt *K, SingleComplex *ALPHA, SingleComplex *A, BlasInt *LDA, SingleComplex *B, BlasInt *LDB, SingleComplex *BETA, SingleComplex *C, BlasInt *LDC, int alen, int blen);
#else
extern void sgemm_(char *TRANSA, int alen, char *TRANSB, int blen, BlasInt *M, BlasInt *N, BlasInt *K, Real *ALPHA, Real *A, BlasInt *LDA, Real *B, BlasInt *LDB, Real *BETA, Real *C, BlasInt *LDC);
extern void dgemm_(char *TRANSA, int alen, char *TRANSB, int blen, BlasInt *M, BlasInt *N, BlasInt *K, DoublePrecision *ALPHA, DoublePrecision *A, BlasInt *LDA, DoublePrecision *B, BlasInt *LDB, DoublePrecision *BETA, DoublePrecision *C, BlasInt *LDC);
extern void zgemm_(char *TRANSA, int alen, char *TRANSB, int blen, BlasInt *M, BlasInt *N, BlasInt *K, DoubleComplex *ALPHA, DoubleComplex *A, BlasInt *LDA, DoubleComplex *B, BlasInt *LDB, DoubleComplex *BETA, DoubleComplex *C, BlasInt *LDC);
extern void cgemm_(char *TRANSA, int alen, char *TRANSB, int blen, BlasInt *M, BlasInt *N, BlasInt *K, SingleComplex *ALPHA, SingleComplex *A, BlasInt *LDA, SingleComplex *B, BlasInt *LDB, SingleComplex *BETA, SingleComplex *C, BlasInt *LDC);
#endif

#if NOFORT
#   define BLAS_SGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    xb_sgemm(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc)
#   define BLAS_DGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    xb_dgemm(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc)
#   define BLAS_ZGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    xb_zgemm(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc)
#   define BLAS_CGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    xb_cgemm(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc)
#elif F2C_HIDDEN_STRING_LENGTH_AFTER_ARGS
#   define BLAS_SGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    sgemm_(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc, 1, 1)
#   define BLAS_DGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    dgemm_(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc, 1, 1)
#   define BLAS_ZGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    zgemm_(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc, 1, 1)
#   define BLAS_CGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    cgemm_(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc, 1, 1)
#else
#   define BLAS_SGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    sgemm_(ta, 1, tb, 1, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc)
#   define BLAS_DGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    dgemm_(ta, 1, tb, 1, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc)
#   define BLAS_ZGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    zgemm_(ta, 1, tb, 1, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc)
#   define BLAS_CGEMM(ta, tb, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc) \
    cgemm_(ta, 1, tb, 1, i, j, k, alpha, a, lda, b, ldb, beta, c, ldc)
#endif


/* min acceptable amount of memory (in elements) and default chunk size */
#  define MINMEM 64
#  define CHUNK_SIZE 256
#  define MAX_CHUNKS 1024
#  define BLOCK_SIZE 1024 /* temp buf size for pinning */
#  define GA_ASPECT_RATIO 3
#  define NUM_MATS 3 
#  define MINTASKS 10 /* increase this if there is high load imbalance */
#  define EXTRA 4

#define MIN_CHUNK_SIZE 256

#define SET   1
#define UNSET 0

static int _gai_matmul_patch_flag = 0; 
Integer gNbhdlA[2], gNbhdlB[2], gNbhdlC[2];/* for A and B matrix */
typedef struct {
  int lo[2]; /* 2 elements: ilo and klo */
  int hi[2];
  int dim[2];
  int chunkBId;
  short int do_put;
}task_list_t;

extern void FATR  ga_nbget_(Integer *g_a, Integer *ilo, Integer *ihi, 
			    Integer *jlo, Integer *jhi, void *buf, 
			    Integer *ld, Integer *nbhdl);

extern logical ngai_patch_intersect(Integer *lo, Integer *hi,
                                    Integer *lop, Integer *hip, Integer ndim);
    
#define VECTORCHECK(rank,dims,dim1,dim2, ilo, ihi, jlo, jhi) \
  if(rank>2)  gai_error("rank is greater than 2",rank); \
  else if(rank==2) {dim1=dims[0]; dim2=dims[1];} \
  else if(rank==1) {if((ihi-ilo)>0) { dim1=dims[0]; dim2=1;} \
                    else { dim1=1; dim2=dims[0];}} \
  else gai_error("rank must be atleast 1",rank);

#define WAIT_GET_BLOCK(nbhdl) ga_nbwait_(nbhdl)

#endif /* _MATMUL_H_ */
