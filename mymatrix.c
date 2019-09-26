#include "mymatrix.h"
////////////////////////////////////////////////////////////////
static int mmercode = 0;
////////////////////////////////////////////////////////////////
void m_setter(int errcode)
{
    mmercode = errcode;
}
////////////////////////////////////////////////////////////////
void m_resetter(void)
{
    mmercode = 0;
}
////////////////////////////////////////////////////////////////
const char * m_errmsg(int errcode)
{
    switch(errcode)
    {
    case RMISMATCH:
        return "row mismatch";
    case CMISMATCH:
        return "column mismatch";
    case NOTSQUARE:
        return "not a square matrix";
    case ALLOCFAIL:
        return "allocation failure";
    case FILEREADFAIL:
        return "file read failure";
    case ROWPARSEFAIL:
        return "row parse failure";
    case COLPARSEFAIL:
        return "column parse failure";
    case RCMISMATCH:
        return "row-column mismatch";
    case INDEXOUTOFRANGE:
        return "index out of range";
    case LENMISMATCH:
        return "length mismatch";
    case NULLARG:
        return "NULL argument";
    default:
        return NULL;
    }
}
////////////////////////////////////////////////////////////////
int m_errcode(void)
{
    return mmercode;
}
////////////////////////////////////////////////////////////////
MATRIX_T *
m_new(int nrows, int ncols)
{
    double *temp;
    MATRIX_T *m = NULL;

    if((temp = malloc(nrows * ncols * sizeof(double))) == NULL)
    {
        mmercode = ALLOCFAIL;
        return NULL;
    }
    if((m = malloc(sizeof(MATRIX_T))) == NULL)
    {
        mmercode = ALLOCFAIL;
        free(temp);
        return NULL;
    }
    m->rows = nrows;
    m->cols = ncols;
    m->val = temp;
    return m;
}
////////////////////////////////////////////////////////////////
void m_free(MATRIX_T * m)
{
    if(m == NULL)
        return;
    free(m->val);
    free(m);
}
