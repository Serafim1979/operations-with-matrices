#ifndef MYMATRIX_H_
#define MYMATRIX_H_
//////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//////////////////////////////////////////////////////
#define MMAXITERATIONS 10
#define LINELEN 4096
//////////////////////////////////////////////////////
#define RMISMATCH       110
#define CMISMATCH       111
#define NOTSQUARE       112
#define ALLOCFAIL       113
#define FILEREADFAIL    114
#define ROWPARSEFAIL    115
#define COLPARSEFAIL    116
#define RCMISMATCH      117
#define INDEXOUTOFRANGE 118
#define LENMISMATCH     119
#define NULLARG         120
//////////////////////////////////////////////////////
typedef struct
{
    int rows;
    int cols;
    double *val;
}MATRIX_T;
//////////////////////////////////////////////////////
MATRIX_T * m_new(int nrows, int ncols);
void m_free(MATRIX_T * m);
const char * m_errmsg(int errcode);
void m_resetter(void);
void m_setter(int errcode);
int m_errcode(void);
MATRIX_T * m_assign_arr2(MATRIX_T * a, int nrows, int ncols, double * arr);
MATRIX_T * m_assign_arr1(MATRIX_T * a, int alen, double *arr);
char * m_getline(FILE * fp);
MATRIX_T * m_fnew(FILE * fp);
void m_printf(char *label, char *format, MATRIX_T * a);

#endif // MYMATRIX_H_
