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
        // fVector c(pfVecOptParam->Size());
        // LS_Param *LSP = (LS_Param *)EstiP;
        // LSP->pMat_H->Show(); 
        // *pfVecOptParam = (Inverse(ATranspA(*(LSP->pMat_H)))*Transp(*(LSP->pMat_H))*(*(LSP->pVec_Z)));
        // pfVecOptParam->Show();   

        // Inverse(ATranspA(*(this->LSP.pMat_H)))*Transp(*(this->LSP.pMat_H)).Show();
        // Inverse(ATranspA(*(this->LSP.pMat_H))).Show();
        // Transp(*(this->LSP.pMat_H)).Show();
        *pfVecOptParam = (Inverse(ATranspA(*(this->LSP.pMat_H)))*Transp(*(this->LSP.pMat_H))*(*(this->LSP.pVec_Z)));
        pfVecOptParam->Show();
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