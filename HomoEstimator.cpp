#include <iostream>
#include <math.h> 
#include "fVector.h"
#include "fMatrix.h"
#include "HomoEstimator.h"
using namespace std;
Float cvHomography(Float* pHomography, Float* pDst_points, Float* pSrc_points, int nPointsNum)
{
    return 0;
}


Float lsHomography(Float* pHomography, Float* pDst_points, Float* pSrc_points, int nPointsNum)
{
    //	Step 1.Given correspondences between two images.
    fVector xr(nPointsNum), yr(nPointsNum), xs(nPointsNum), ys(nPointsNum);
    for (int i = 0; i < nPointsNum; i++)
    {
        xr(i) = *(pDst_points + i * 2);
        yr(i) = *(pDst_points + (i * 2 + 1));
        xs(i) = *(pSrc_points + i * 2);
        ys(i) = *(pSrc_points + (i * 2 + 1));
    }

    // Step 2.Compute two transform matrices that normalize the imagecoordinates of all correspond ences.
    double xs_m = Mean(xs),
           ys_m = Mean(ys),
           xr_m = Mean(xr),
           yr_m = Mean(yr);

    double s1 = sqrt(2.0) / (Mean(Sqrt(Pow(xs - xs_m, 2) + Pow(ys - ys_m, 2)))),
           s2 = sqrt(2.0) / (Mean(Sqrt(Pow(xr - xr_m, 2) + Pow(yr - yr_m, 2))));

    Float buffer_T1[9] = {s1, 0.0, -1 * s1 * xs_m,
                          0.0, s1, -1 * s1 * ys_m,
                          0.0, 0.0, 1.0},

          buffer_T2[9] = {s2, 0.0, -1 * s2 * xr_m,
                          0.0, s2, -1 * s2 * yr_m,
                          0.0, 0.0, 1.0};

    fMatrix T1(buffer_T1, 3, 3), T2(buffer_T2, 3, 3);

    //	Step 3.Normalize all coorespondences by the two transform matrices.
    fVector x1(nPointsNum), y1(nPointsNum), x2(nPointsNum), y2(nPointsNum);
    x1 = s1 * xs - (s1 * ys_m);
    y1 = s1 * ys - (s1 * ys_m);
    x2 = s2 * xr - (s2 * xr_m);
    y2 = s2 * yr - (s2 * yr_m);

    //	Step 4.Generate the observation matrix and observation vector Z by using the normalized correspondences.
    
}