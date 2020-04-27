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
        // cout << (LS_Param*)pParam << endl;
        // EstiP = (LS_Param *)pParam;
        LS_Param *LSP = (LS_Param *)pParam;

        cout << "H" << endl;
        LSP->pMat_H->Show();
        cout << "Z" << endl;
        LSP->pVec_Z->Show();
    }
}

ParamEstiMethod	CParamEstimator::GetParamEstiMethod(void) const
{
    cout << EstiMethod << endl;
}
