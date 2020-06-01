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

        *pfVecOptParam = (Inverse_by_ALGLIB(ATranspA(*(this->LSP.pMat_H)))*Transp(*(this->LSP.pMat_H))*(*(this->LSP.pVec_Z)));
        pfVecOptParam->Show();

        V = (*this->LSP.pVec_Z) - (*this->LSP.pMat_H)*(*pfVecOptParam);
        // V.Show();
        // return &Vv;
    }
    else if(this->EstiMethod==WLS)
    {
        cout << "WLS" << endl;
        fVector V((*this->WLSP.pVec_Z).Size());
        fMatrix Vv((*this->WLSP.pVec_Z).Size(),(*this->WLSP.pVec_Z).Size());
        fMatrix Inv_ATAH(Inverse_by_ALGLIB(ATranspA(*(this->WLSP.pMat_H))));

        *pfVecOptParam = ( Inv_ATAH * Transp(*(this->WLSP.pMat_H)) * (*(this->WLSP.pVec_Z)) );
        pfVecOptParam->Show();

        V = (*this->WLSP.pVec_Z) - ((*this->WLSP.pMat_H)*(*pfVecOptParam));
        // V.Show();

        Vv = Cov(V);
        // Vv.Show();
        Vv = Diag(Diag(Vv));
        // Vv.Show();
        *this->WLSP.pMat_W = Inverse_by_ALGLIB(Vv);
        // this->WLSP.pMat_W->Show();


        fMatrix Inv_ATAVH(Inverse_by_ALGLIB((Transp(*this->WLSP.pMat_H))*(*this->WLSP.pMat_W)*(*this->WLSP.pMat_H)));
        // ((Transp(*this->WLSP.pMat_H))).Show();
        // Inv_ATAVH.Show();
        *pfVecOptParam = Inv_ATAVH * Transp(*this->WLSP.pMat_H) * (*this->WLSP.pMat_W) * (*(this->WLSP.pVec_Z));
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
    if(Method == WLS)
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