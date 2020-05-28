#include<iostream>
#include<string.h>
#include <math.h>
#include "fVector.h"
using namespace std;


fVector operator + ( const fVector &A, const fVector &B)
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = A.elem[i]+B.elem[i];
    }
    return c;
}

fVector operator - ( const fVector &A, const fVector &B)
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = A.elem[i]-B.elem[i];
    }
    return c;
}

fVector operator - ( const fVector &A)
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = -A.elem[i];
    }
    return c;
}

fVector operator - ( const fVector &A, Float n)
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = A.elem[i]-n;
    }
    return c;
}

fVector operator - ( Float n, const fVector &A)
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = n-A.elem[i];
    }
    return c;
}

fVector operator * ( const fVector &A, Float n )
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = A.elem[i]*n;
    }
    return c;
}

fVector operator * ( Float n, const fVector &A )
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = A.elem[i]*n;
    }
    return c;
}

fVector operator / ( const fVector &A, Float n)
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = A.elem[i]/n;
    }
    return c;
}

fVector operator / ( const fVector &A, const fVector &B)
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = A.elem[i]/B.elem[i];
    }
    return c;
}

double operator * ( const fVector &A, const fVector &B)
{
    double n=0;
    for(int i=0;i<A.size;i++)
    {
        n += A.elem[i]*B.elem[i];
    }
    return n;
}

fVector  operator ^  ( const fVector &A, const fVector &B)
{
    if(A.size != 3 && B.size !=3)
    {
        cout << "vector shape error";
        return 0; 
    }
    fVector c(A.size);
    c.elem[0] = A.elem[1]*B.elem[2] - A.elem[2]*B.elem[1];
    c.elem[1] = -A.elem[0]*B.elem[2] + A.elem[2]*B.elem[0];
    c.elem[2] = A.elem[0]*B.elem[1] - A.elem[1]*B.elem[0];
    
    return c;
}

fVector& operator += ( fVector &A, const fVector &B)
{
    for(int i=0;i<A.size;i++)
    {
        A.elem[i] += B.elem[i];
    }
    return A;
}

fVector& operator -= ( fVector &A, const fVector &B)
{
    for(int i=0;i<A.size;i++)
    {
        A.elem[i] -= B.elem[i];
    }
    return A;
}

fVector& operator *= ( fVector &A, Float b)
{
    for(int i=0;i<A.size;i++)
    {
        A.elem[i] *= b;
    }
    return A;
}

fVector& operator /= ( fVector &A, Float b)
{
    for(int i=0;i<A.size;i++)
    {
        A.elem[i] /= b;
    }
    return A;
}

fVector &fVector::operator=(const fVector &A)
{
    if (this != &A)
    {
        delete[] this->elem;
        this->elem = new Float[A.size];
        this->size = A.size;
        for(int i=0;i<A.size;i++)
        {
            this->elem[i] = A.elem[i];
        }
    }
    return *this;
}

// fVector operator + ( const fVector &A, const fVector &B)
// {
//     return fVector(A.elem[0]+B.elem[0],A.elem[1]+B.elem[1],A.elem[2]+B.elem[2]);
// }

/*-------------------------------------------------------------------------*
 *                                                                         *
 *  FRIEND FUNCTIONS                                                       *
 *                                                                         *
 *-------------------------------------------------------------------------*/
fVector Min ( const fVector &A, const fVector &B )
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        if(A.elem[i]>=B.elem[i])
            c.elem[i] = B.elem[i];
        if(A.elem[i]<B.elem[i])
            c.elem[i] = A.elem[i];
    }
    return c;
}

fVector Max ( const fVector &A, const fVector &B )
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        if(A.elem[i]>=B.elem[i])
            c.elem[i] = A.elem[i];
        if(A.elem[i]<B.elem[i])
            c.elem[i] = B.elem[i];
    }
    return c;
}

double  Dist ( const fVector &A, const fVector &B )
{
    double n=0;
    for(int i=0;i<A.size;i++)
    {
        n += pow((A.elem[i]-B.elem[i]),2);
    }
    return sqrt(n);
}

double  Mean ( const fVector &A )
{
    double n=0;
    for(int i=0;i<A.size;i++)
    {
        n += A.elem[i];
    }
    return n/A.size;
}

double  Var  ( const fVector &A )
{
    double n;
    double x = Mean(A);
    for(int i=0;i<A.size;i++)
    {
        n += pow((A.elem[i]-x),2);
    }
    return n/(A.size-1);
}

double  Std  ( const fVector &A )
{
    return sqrt(Var(A));
}

fVector  Normalize   ( const fVector &A )
{
    fVector c(A.size);
    double mean,std;
    mean = Mean(A);
    std = Std(A);
    // cout << mean << endl << std << endl; 
    for(int i=0;i<A.size;i++)
    {
        c.elem[i]= (A.elem[i]-mean)/std;

    }
    return c;
}

fVector  Sqrt   ( const fVector &A )
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = sqrt(A.elem[i]);
    }
    return c;
}

fVector Pow(const fVector &A,Float num)
{
    fVector c(A.size);
    for(int i=0;i<A.size;i++)
    {
        c.elem[i] = pow(A.elem[i],num);
    }
    return c;
}
double  OneNorm  ( const fVector &A )
{
    double n=0;
    for(int i=0;i<A.size;i++)
    {
        n += A.elem[i];
    }
    return n;
}

double  TwoNorm  ( const fVector &A )
{
    double n=0;
    for(int i=0;i<A.size;i++)
    {
        n += pow(A.elem[i],2);
    }
    return sqrt(n);
}

double  TwoNormSqr  ( const fVector &A )
{
    return pow(TwoNorm(A),2);
}

fVector::fVector(int size)
{
    this->size = size;
    elem = new Float[size];
}

fVector::fVector(Float a,Float b,Float c)
{
    // elem = NULL;
    elem = new Float[3];
    size = 3;
    elem[0] = a;
    elem[1] = b;
    elem[2] = c;
}

fVector::fVector( const fVector &A)
{   
    size = A.size;
    elem = new Float[size];
    memcpy(elem,&A.elem[0],sizeof(Float)*size);
}

fVector::fVector( const Float *x, int n )
{
    elem = NULL;
    size = n;
    elem = new Float[n];
    memcpy(elem,x,sizeof(Float)*size);
}

fVector::fVector( int n , const Float *x )
{
    elem = NULL;
    size = n;
    elem = new Float[n];
    memcpy(elem,x,sizeof(Float)*size);
}

fVector::~fVector()
{
    if (elem)
    {
        delete elem;
        elem = NULL;
    }
    
}

void fVector::Show(VecType Type) const
{
    if(Type==1)
    {
        for(int i=0;i<size;i++)
                {
                    // if(i!=(size-1))
                    //     cout<<elem[i]<<" ";
                    // else
                        cout<<elem[i]<<endl;
                }
    }
    if(Type==2)
    {
        for(int i=0;i<size;i++)
        {
            if(i!=(size-1))
                cout<<elem[i]<<" ";
            else
                cout<<elem[i]<<endl;
        }
    }

}

// void ShowVector ( const fVector &A, VecType Type)