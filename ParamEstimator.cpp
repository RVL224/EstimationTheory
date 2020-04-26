#include<iostream>
#include "ParamEstimator.h"
#include "fMatrix.h"
using namespace std;


CParamEstimator::CParamEstimator(void)
{
    Float C[9] = {0.9649, 0.9572, 0.1419, 
				  0.1576, 0.4854, 0.4218, 
				  0.9706, 0.8003, 0.9157};
    fMatrix a(C,3,3);
    cout << "Construct OK" << endl;
}

CParamEstimator::~CParamEstimator()
{
}

// void CParamEstimator::SetParamEstiMethod(ParamEstiMethod Method)
// {
//     if (Method == 1)
//     {
        
//     }
// }

