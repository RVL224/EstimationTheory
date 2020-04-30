/*
 *	ParamEstimator.h
 *
 *	Description:
 *		Basic class of parameter estimator
 *
 *
 *		
 * 	History:
 *	 	Author			Date			Modify Reason		
 *		----------------------------------------------------------------
 *		Chi-Yi Tsai		2014/01/25		File Creation    
 *
 */
 
#ifndef PARAM_ESTIMATOR_ENUM_METHODS
#define PARAM_ESTIMATOR_ENUM_METHODS

#include "fMatrix.h"

enum ParamEstiMethod {LS = 1, WLS = 2, ML = 3};

typedef struct	st_LS_Param
{
	fMatrix*	pMat_H;
	fVector*	pVec_Z;
	// Optional	(for error-variance computing)
	fMatrix*	pMat_Vz;
} LS_Param;

typedef struct	st_WLS_Param
{
	fMatrix*	pMat_H;
	fMatrix*	pMat_W;
	fVector*	pVec_Z;
	// Optional	(for error-variance computing)
	fMatrix*	pMat_Vz;
} WLS_Param;

typedef struct	st_ML_Param
{
	fMatrix*	pMat_H;
	fVector*	pVec_Z;
	// Necessary for state estimation and error-variance computing
	fMatrix*	pMat_Vz;
} ML_Param;

#endif // PARAM_ESTIMATOR_ENUM_METHODS

#ifndef __PARAM_ESTIMATOR_INCLUDED__
#define __PARAM_ESTIMATOR_INCLUDED__

class CParamEstimator
{
public:
	CParamEstimator(void);
	~CParamEstimator();

	fMatrix*	SolveOptParam(fVector*	pfVecOptParam);

	void		SetParamEstiMethod(ParamEstiMethod Method);
	void		SetMethodParameters(ParamEstiMethod Method, void*	pParam);
	
	ParamEstiMethod	GetParamEstiMethod(void) const;
	void*		GetMethodParameters(ParamEstiMethod Method) const;

	private:
		int EstiMethod;
		//ParamEstiMethod
		LS_Param LSP;
		WLS_Param WLSP;
		ML_Param MLP;
		// void* EstiP;
};

#endif // __PARAM_ESTIMATOR_INCLUDED__