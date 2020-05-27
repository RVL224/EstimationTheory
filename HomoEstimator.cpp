#include "fVector.h"
#include "fMatrix.h"
#include "HomoEstimator.h"

Float cvHomography(Float* pHomography, Float* pDst_points, Float* pSrc_points, int nPointsNum)
{
    return 0;
}


Float lsHomography(Float* pHomography, Float* pDst_points, Float* pSrc_points, int nPointsNum)
{
    fMatrix x(pDst_points,256,2);
    x.Show();
}