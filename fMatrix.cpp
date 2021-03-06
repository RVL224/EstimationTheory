#include <iostream>
#include <string.h>
#include <iomanip>
#include <math.h>
#include "fMatrix.h"
#include "lib/linalg.h"
using namespace std;
using namespace alglib;

fMatrix  operator +  ( const fMatrix &A, const fMatrix &B)
{
    fMatrix c(A.rows,A.cols);
    for(int i=0;i<A.rows*A.cols;i++)
    {
        c.elem[i] = A.elem[i]+B.elem[i];
    }
    return c;
}

fMatrix  operator -  ( const fMatrix &A, const fMatrix &B)
{
    fMatrix c(A.rows,A.cols);
    for(int i=0;i<A.rows*A.cols;i++)
    {
        c.elem[i] = A.elem[i]-B.elem[i];
    }
    return c;
}

fMatrix  operator -  ( const fMatrix &A)
{
    fMatrix c(A.rows,A.cols);
    for(int i=0;i<A.rows*A.cols;i++)
    {
        c.elem[i] = -A.elem[i];
    }
    return c;
}

fMatrix  operator *  ( const fMatrix &A, Float n )
{
    fMatrix c(A.rows,A.cols);
    for(int i=0;i<A.rows*A.cols;i++)
    {
        c.elem[i] = n*A.elem[i];
    }
    return c;
}

fMatrix  operator *  ( Float n, const fMatrix &A ) 
{
    fMatrix c(A.rows,A.cols);
    for(int i=0;i<A.rows*A.cols;i++)
    {
        c.elem[i] = n*A.elem[i];
    }
    return c;
}

fMatrix  operator /  ( const fMatrix &A, Float n)
{
    fMatrix c(A.rows,A.cols);
    for(int i=0;i<A.rows*A.cols;i++)
    {
        c.elem[i] = A.elem[i]/n;
    }
    return c;
}

fMatrix  operator *  ( const fMatrix &A, const fMatrix &B )
{
    fMatrix c(A.rows,B.cols);
    if(A.cols != B.rows)
    {
        cout<<"shape error !!!"<<endl;
        return 0;
    }
    for(int i=0;i<A.rows*B.cols;i++)
    {
        Float sum = 0;
        int d = i/B.cols;
        int n = i%B.cols;

        for(int j=0;j<A.cols;j++)
        {
            sum += A.elem[d*A.cols+j]*B.elem[n+j*B.cols];
        }
        
        c.elem[i] = sum;
    }
    // cout << A.rows*B.cols<<endl;
    return c;
}

fVector  operator *  ( const fMatrix &A, const fVector &B )
{
    fVector c(A.rows);
    for(int i=0;i<A.rows;i++)
    {
        double sum = 0;
        for(int j=0;j<B.Size();j++)
        {
            sum += A.elem[i*B.Size()+j]*B.Array()[j];
        }
        c.Array()[i] = sum;
    }
        // cout<< B.Array()[i]<<endl;
    return c;
}

fVector  operator *  ( const fVector &A , const fMatrix &B )
{
    fVector c(B.cols);
    for(int i=0;i<B.rows;i++)
    {
        double sum = 0;
        for(int j=0;j<A.Size();j++)
        {
            sum += A.Array()[j]*B.elem[i+j*B.cols];
        }
        c.Array()[i] = sum;
    }
    return c;
}

fMatrix& operator += (fMatrix &A, const fMatrix &B )
{
    for(int i=0;i<A.rows*A.cols;i++)
    {
        A.elem[i] += B.elem[i];
    }
    return A;
}

fMatrix& operator -= (fMatrix &A, const fMatrix &B )
{
    for(int i=0;i<A.rows*A.cols;i++)
    {
        A.elem[i] -= B.elem[i];
    }
    return A;
}

fMatrix& operator *= (fMatrix &A,  Float n )
{
    for(int i=0;i<A.rows*A.cols;i++)
    {
        A.elem[i] *= n;
    }
    return A;
}

fMatrix& operator /= (fMatrix &A,  Float n )
{
    for(int i=0;i<A.rows*A.cols;i++)
    {
        A.elem[i] /= n;
    }
    return A;
}

fMatrix& operator *= (fMatrix &A, const fMatrix &B )
{   
    if(A.cols != B.rows)
    {
        cout<<"shape error !!!"<<endl;
        exit(1);
    }
    fMatrix c(A.rows,B.cols);
    for(int i=0;i<A.rows*B.cols;i++)
    {
        Float sum = 0;
        int d = i/B.cols;
        int n = i%B.cols;

        for(int j=0;j<A.cols;j++)
        {
            sum += A.elem[d*A.cols+j]*B.elem[n+j*B.cols];
        }
        
        // cout << sum << endl;
        c.elem[i] = sum; 
    }
    A = c;
    // cout << A.rows*B.cols<<endl;
    return A;
}

fVector& operator *= (fVector &A, const fMatrix &B )
{
    fVector c(A.Size());
    for(int i=0;i<B.cols;i++)
    {
        Float sum = 0;
        for(int j=0;j<A.Size();j++)
        {   
            // cout << A.Array()[j];
            sum += A.Array()[j]*B.elem[j*3+i];
            // cout << A.Array()[j] << " " << B.elem[j*3+i] << endl;
        }
        // cout <<  sum << endl;
        c.Array()[i] = sum;
    }
    A=c;
    return A;
}

fMatrix &fMatrix::operator=( const fMatrix &M )
{
    if (this != &M)
    {
        delete[] this->elem;
        this->elem = new Float[M.rows * M.cols];
        this->rows = M.rows;
        this->cols = M.cols;
        for (int i = 0; i < M.rows * M.cols; i++)
        {
            this->elem[i] = M.elem[i];
        }
    }
    return *this;
}

fVector  fMatrix::GetCol( int col ) const
{
    fVector c(this->rows);
    for(int i=0;i<this->rows;i++)
    {
        c.Array()[i] = this->elem[i*this->cols+col];
    }
    return c;
}

fVector  fMatrix::GetRow( int row ) const
{
    fVector c(this->cols);
    for(int i=0;i<this->cols;i++)
    {
        c.Array()[i] = this->elem[this->cols*row+i];
    }
    return c;
}

void    fMatrix::SetRow( int row, const fVector &A )
{
    for(int i=0;i<this->cols;i++)
    {
        this->elem[row*this->cols+i] = A.Array()[i];
    }
}

fMatrix  Transp      ( const fMatrix &A )
{
    fMatrix c(A.cols,A.rows);
    for(int i=0;i<A.cols;i++)
    {
        for(int j=0;j<A.rows;j++)
        {
            c.elem[i*A.rows+j] = A.elem[j*A.cols+i];
        }
    }
    return c;
}

fMatrix  AATransp    ( const fMatrix &A )
{
    return A * Transp(A);
}

fMatrix  ATranspA    ( const fMatrix &A )
{
    return Transp(A) * A;
}

fMatrix  Outer (const fVector &A, const fVector &B )
{
    fMatrix c(A.Size(),B.Size());
    for(int i=0;i<A.Size()*B.Size();i++)
    {
        c.elem[i] = A.Array()[i/c.rows]*B.Array()[i%c.rows];
    }
    return c;
}
fMatrix Identity	( int nSize )
{
    fMatrix c(nSize ,nSize );
    for(int i=0;i<nSize*nSize;i++)
    {
        if(i/nSize==i%nSize)
        {
            c.elem[i] = 1;
        }
        else
        {
            c.elem[i] = 0;
        }
    }
    return c;
}

fMatrix  Diag        ( const fVector &A)
{
    fMatrix c(A.Size(),A.Size());
    for(int i=0;i<A.Size()*A.Size();i++)
    {
        if(i/A.Size()==i%A.Size())
        {
            c.elem[i] = A.Array()[i/A.Size()];
        }
        else
        {
            c.elem[i] = 0;
        }    
    }
    return c;
}

fVector  Diag        ( const fMatrix &A )
{
    if(A.rows != A.cols)
    {
        cout << "shape error!" <<endl;
        return 0;
    }

    fVector c(A.rows);
    for(int i=0;i<A.rows*A.cols;i++)
    {
        if(i/A.rows==i%A.cols)
        {
            c.Array()[i/A.rows] = A.elem[i];
        }    
    }
    return c;
}

fMatrix  Diag        ( Float A, Float B, Float C )
{
    fMatrix c(3,3);
    for(int i=0;i<9;i++)
    {
        c.elem[i] = 0;
    }
    c.elem[0] = A;
    c.elem[4] = B;
    c.elem[8] = C;
    return c;
}

double   Determinant ( const fMatrix &A )
{
    if(A.cols!=A.rows)
    {
        cout << "shape error!" <<endl;
        return 0;
    }
    double mul;
    double sum = 0;

    if (A.rows == 2)
    {
        sum = A.elem[0]*A.elem[3]-A.elem[1]*A.elem[2];
        return sum;
    }
    
    for(int i=0;i<A.cols;i++)
    {
        int n=0;
        fMatrix c(A.cols-1,A.cols-1);
        for(int j=A.cols;j<A.cols*A.rows;j++)
        {
            if(j%A.cols != i)
            {
                c.elem[n] = A.elem[j];
                n++;
                // cout << j << " ";
            }
        }
        // cout << endl;
        
        if(i%2 == 0)
            sum += A.elem[i]*Determinant(c);
            // cout << Determinant(c) << " ";
        if(i%2 == 1)
            sum -= A.elem[i]*Determinant(c);
            // cout << Determinant(c) << " ";
    }
    return sum;
}

double   Trace       ( const fMatrix &A )
{
    if(A.cols!=A.rows)
    {
        cout << "shape error!" <<endl;
        return 0;
    }
    double sum = 0;
    for(int i=0;i<A.rows*A.cols;i++)
    {
        if(i/A.cols==i%A.rows)
        {
            sum += A.elem[i];
        }
    }
    return sum;
}

fMatrix  Inverse  ( const fMatrix &A)
{
    if(A.cols!=A.rows)
    {
        cout << "shape error!" <<endl;
        return 0;
    }
    if(A.cols==2)
    {
        fMatrix c(2,2);
        c.elem[0] = A.elem[3];
        c.elem[1] = -A.elem[1];
        c.elem[2] = -A.elem[2];
        c.elem[3] = A.elem[0];
        return c/Determinant(A);
    }
    fMatrix c(A.rows,A.cols);
    fMatrix d(A.rows-1,A.cols-1);
    for(int i=0;i<A.cols*A.rows;i++)
    {
        // fMatrix d(A.rows-1,A.cols-1);
        int n = 0;
        for(int j=0;j<A.cols*A.rows;j++)
        {
            if(j/A.rows != i/A.rows && j%A.cols != i%A.cols)
            {
                d.elem[n] = A.elem[j];
                // cout<<j;
                n++;
            }
        }
        // cout <<endl;
        // for(int k=0;k<4;k++)
        // {
        //     cout << d.elem[k] << " ";
        // }
        // cout<<"   det="<<Determinant(d)<<endl;
        if (i%2 == 0)
        {
            c.elem[i] = Determinant(d)/Determinant(A);
        }
        else
        {
            c.elem[i] = -Determinant(d)/Determinant(A);
        }
        
        // c = Transp(c);
    
    }
    return Transp(c);
}

fMatrix  Inverse_by_ALGLIB(const fMatrix &aMat)
{
	fMatrix inverse(aMat.rows,aMat.cols);
	real_2d_array a;
	a.setlength(aMat.rows, aMat.cols);
	for (int i = 0; i < aMat.rows; i++)
	{
		for (int j = 0; j < aMat.cols; j++)
		{
			a[i][j] = aMat.elem[i * aMat.cols + j];
		}
	}
	setnworkers(4);
	ae_int_t info;
	matinvreport rep;
	rmatrixinverse(a, info, rep);
	for (int i = 0; i < aMat.rows; i++)
	{
		for (int j = 0; j < aMat.cols; j++)
		{
			inverse.elem[i * aMat.cols + j] = a[i][j];
		}
	}
	return inverse;
}

fVector  Mean		( const fMatrix &A )
{
    fVector c(A.rows);
    Float n;
    for(int i=0;i<A.rows;i++)
    {
        n = 0;
        for(int j=0;j<A.cols;j++)
        {
            n += A.elem[i+j*A.cols];
            // cout << A.elem[i*A.cols+j] << " ";
        }
        // cout << endl;
        c.Array()[i] = n / A.cols;
    }
    return c;
}

fMatrix  Cov    ( const fMatrix &A )
{
    fVector Am = Mean(A);
    fMatrix c(A);
    for(int i=0;i<A.cols;i++)
    {
        for(int j=0;j<A.cols;j++)
        {
            c.elem[i*A.cols+j] -= Am.Array()[j]; 
        }
    }
    return (Transp(c)*c) / (A.rows-1);
}
fMatrix  Cov	( const fVector &A )
{
    return Cov(Outer(A,A)); 
}

void fMatrix::Show() const
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cout<<setiosflags(ios::fixed)<<setprecision(4)<<elem[i*cols+j]<<" ";
        }
        cout<<endl;
    }
}
fMatrix::fMatrix( int n_rows, int n_cols)
{   
    this->rows = n_rows;
    this->cols = n_cols;
    elem = new Float[rows*cols];
}

fMatrix::fMatrix( const fMatrix & A)
{
    rows = A.rows;
    cols = A.cols;
    elem = new Float[rows*cols];
    memcpy(elem,&A.elem[0],sizeof(Float)*rows*cols);
} 

fMatrix::fMatrix( Float *Array, int n_rows , int n_cols  )
{
    elem = NULL;
    rows = n_rows;
    cols = n_cols;
    elem = new Float[rows*cols];
    memcpy(elem,Array,sizeof(Float)*rows*cols);
}

fMatrix::fMatrix( int n_rows , int n_cols , Float *Array )
{
    elem = NULL;
    rows = n_rows;
    cols = n_cols;
    elem = new Float[rows*cols];
    memcpy(elem,Array,sizeof(Float)*rows*cols);
}

fMatrix::~fMatrix(void)
{
    if (elem)
    {
        delete elem;
        elem = NULL;
    }   
}