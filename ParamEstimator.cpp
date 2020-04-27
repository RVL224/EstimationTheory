#include<iostream>
#include "ParamEstimator.h"
#include "fMatrix.h"
using namespace std;


CParamEstimator::CParamEstimator(void)
{
    // cout << "Construct OK" << endl;
}

CParamEstimator::~CParamEstimator()
{
}

void CParamEstimator::SetParamEstiMethod(ParamEstiMethod Method)
{
    EstiMethod = Method;
}

void CParamEstimator::SetMethodParameters(ParamEstiMethod Method, void*	pParam)
{
    if(Method == LS)
    {
        cout << "LS" << endl;
    }
}

ParamEstiMethod	CParamEstimator::GetParamEstiMethod(void) const
{
    cout << EstiMethod << endl;
}

