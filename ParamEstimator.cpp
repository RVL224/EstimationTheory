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

fMatrix*	CParamEstimator::SolveOptParam(fVector*	pfVecOptParam)
{
    if(this->EstiMethod==LS)
    {
        cout << "LS" << endl;
        fVector V((*this->LSP.pVec_Z).Size());
        fMatrix Vv((*this->LSP.pVec_Z).Size(),(*this->LSP.pVec_Z).Size());

        *pfVecOptParam = (Inverse(ATranspA(*(this->LSP.pMat_H)))*Transp(*(this->LSP.pMat_H))*(*(this->LSP.pVec_Z)));
        // pfVecOptParam->Show();

        V = (*this->LSP.pVec_Z) - (*this->LSP.pMat_H)*(*pfVecOptParam);
        // V.Show();

        // Vv = Cov(V);
        // Vv.Show();
        // return &Vv;
    }
}

void CParamEstimator::SetParamEstiMethod(ParamEstiMethod Method)
{
    EstiMethod = Method;
}

void CParamEstimator::SetMethodParameters(ParamEstiMethod Method, void*	pParam)
{
    if(Method == LS)
    {
        // EstiP = (LS_Param *)pParam;
        LSP = *((LS_Param *)pParam);
        
    }
    if(Method == LS)
    {
        // EstiP = (WLS_Param *)pParam;
        WLSP = *((WLS_Param *)pParam);
    }
    if(Method == ML)
    {
        // EstiP = (ML_Param *)pParam;
        MLP = *((ML_Param *)pParam);
    }
}

ParamEstiMethod	CParamEstimator::GetParamEstiMethod(void) const
{
    return ParamEstiMethod(EstiMethod);
}