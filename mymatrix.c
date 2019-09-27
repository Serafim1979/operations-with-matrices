#include "mymatrix.h"
////////////////////////////////////////////////////////////////
static int mmercode = 0;
static char line[LINELEN];
//////////////////////////////////////////////////////////////
static int mdx(MATRIX_T * a, int i, int j)
{
    return i * a->cols + j;
}
//////////////////////////////////////////////////////////////
#define mdx(a,i,j) (i)*(a)->cols+(j)
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
////////////////////////////////////////////////////////////////
MATRIX_T * m_assign_arr2(MATRIX_T * a, int nrows, int ncols, double * arr)
{
    int len;
    if(a == NULL)
    {
        mmercode = NULLARG;
        return a;
    }
    if(nrows != a->rows)
    {
        mmercode = RMISMATCH;
        return a;
    }
    if(ncols != a->cols)
    {
        mmercode = CMISMATCH;
        return a;
    }
    len = nrows * ncols;
    return m_assign_arr1(a, len, arr);
}
////////////////////////////////////////////////////////////////
MATRIX_T * m_assign_arr1(MATRIX_T * a, int alen, double *arr)
{
    int i, j, index;
    if(a == NULL)
    {
        mmercode = NULLARG;
        return a;
    }
    if(alen != a->rows * a->cols)
    {
        mmercode = LENMISMATCH;
        return a;
    }
    index = 0;
    for(i = 0; i < a->rows; i++)
    {
        for(j = 0; j < a->cols; j++)
        {
            a->val[index] = arr[index];
            index++;
        }
    }
}
////////////////////////////////////////////////////////////////
char * m_getline(FILE * fp)
{
    do
    {
        if(!fgets(line, LINELEN, fp))
        {
            mmercode = FILEREADFAIL;
            return NULL;
        }
    }while(*line == '#');
    return line;
}
////////////////////////////////////////////////////////////////
MATRIX_T * m_fnew(FILE * fp)
{
    int i, j, rows, cols, index;
    char *tok;
    char *lineptr;
    MATRIX_T *a;

    if(!m_getline(fp)){return NULL;}
    if(!(tok = strtok(line, ",")))
    {
        mmercode = ROWPARSEFAIL;
        return NULL;
    }
    if(strcmp(tok, "rows"))
    {
        mmercode = ROWPARSEFAIL;
        return NULL;
    }
    if(!(tok = strtok(NULL, ",")))
    {
        mmercode = ROWPARSEFAIL;
        return NULL;
    }
    rows = atoi(tok);
    if(!rows)
    {
        mmercode = ROWPARSEFAIL;
        return NULL;
    }

    if(!m_getline(fp)){return NULL;}
    if(!(tok = strtok(line, ",")))
    {
        mmercode = COLPARSEFAIL;
        return NULL;
    }
    if(strcmp(tok, "cols"))
    {
        mmercode = COLPARSEFAIL;
        return NULL;
    }
    if(!(tok = strtok(NULL, ",")))
    {
        mmercode = COLPARSEFAIL;
        return NULL;
    }
    cols = atoi(tok);
    if(!cols)
    {
        mmercode = COLPARSEFAIL;
        return NULL;
    }

    if(!(a = m_new(rows, cols)))
        return NULL;
    index = 0;
    for(i = 0; i < rows; i++)
    {
        if(!m_getline(fp))
        {
            m_free;
            return NULL;
        }
        lineptr = line;
        for(j = 0; j < cols; j++)
        {
            if(!(tok = strtok(lineptr, ",")))
            {
                m_free;
                return NULL;
            }
            a->val[index] = atof(tok);
            index++;
            lineptr = NULL;
        }
    }
    return a;
}
////////////////////////////////////////////////////////////////
void m_printf(char *label, char *format, MATRIX_T * a)
{
    int i, j;
    if(a == NULL)
    {
        printf("m_printf NULL argument error\n");
        return;
    }
    printf("%s\n", label);
    printf("rows = %d, cols = %d\n", a->rows, a->cols);
    for(i = 0; i < a->rows; i++)
    {
        for(j = 0; j < a->cols; j++)
        {
            printf(format, a->val[mdx(a, i, j)]);
        }
        printf("\n");
    }
}
////////////////////////////////////////////////////////////////
