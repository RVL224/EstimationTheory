#include <iostream>
#include <math.h> 
#include "fVector.h"
#include "fMatrix.h"
#include "ParamEstimator.h"
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
    fMatrix A(nPointsNum*2,8);
    fVector Z(nPointsNum*2);

    for(int i=0;i<nPointsNum*2;i+=2)
    {
        Float ax[8] = {x1(i/2), y1(i/2), 1, 0, 0, 0, -x2(i/2)*x1(i/2), -x2(i/2)*y1(i/2)};
        Float ay[8] = {0, 0, 0, x1(i/2), y1(i/2), 1, -y2(i/2)*x1(i/2), -y2(i/2)*y1(i/2)};
        fVector buffer_ax(ax,8);
        fVector buffer_ay(ay,8);
        // buffer_ax.Show(RowVec);
        // buffer_ay.Show(RowVec);
        A.SetRow(i  ,buffer_ax);
        A.SetRow(i+1,buffer_ay);
        
        Z(i)   = x2(i/2);
        Z(i+1) = y2(i/2);
    }

    // Step 5. Estimate the normalized homography H 0 by one of the parameter estimators
    CParamEstimator CPE;
	CPE.SetParamEstiMethod(LS);
    LS_Param param = {&A,&Z,NULL};
    fVector H(A.GetCols());
    CPE.SetMethodParameters(LS,&param);
	CPE.SolveOptParam(&H);
    // **************************
    Float *buffer_h = new Float[9];
    for(int i=0;i<H.Size();i++)
    {
        buffer_h[i] = H.Array()[i];
    }

    buffer_h[8] = 1;
    fMatrix MatH(buffer_h, 3, 3);
    MatH.Show();

    //	Step 6.Recovery the initial homography from the two transformmatrices
    MatH = Inverse(T2) * MatH * T1;
    // MatH.Show();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            pHomography[i * 3 + j] = MatH(i, j);
        }
    }

    fMatrix x_p(3, nPointsNum);
    fVector ones(nPointsNum);
    for(int i=0;i<ones.Size();i++)
    {
        ones(i) = 1.0;
    }

    // x_p = [ x1 ; y1 ; 1 ]
    x_p.SetRow(0, xs);
    x_p.SetRow(1, ys);
    x_p.SetRow(2, ones);
    //****************************
    Float H1[9] = {0.0162 , 0.0008, -1.3281, -0.0008, 0.0152, -6.6273, 0.00016, 0.0001, 0.9306};
    fMatrix MatH1(H1,3,3);
    //****************************

    // x_p = [ x2 ; y2 ; z2 ]
    x_p = MatH1 * x_p; //	x_p = H*[xs';ys';ones(1,length(xs))];

    /***************************************************************  Normalization  *********************************************************************************/
    // x_p = [ x2/z2 ; y2/z2 ; 1 ]
    fVector buffer_1(nPointsNum), buffer_2(nPointsNum), buffer_3(nPointsNum);
    buffer_1 = x_p.GetRow(0);
    buffer_2 = x_p.GetRow(1);
    buffer_3 = x_p.GetRow(2);

    buffer_1 = buffer_1 / buffer_3;
    buffer_2 = buffer_2 / buffer_3;
    buffer_3 = buffer_3 / buffer_3;

    x_p.SetRow(0, buffer_1);
    x_p.SetRow(1, buffer_2);
    x_p.SetRow(2, buffer_3);
    

    // x_p.Show();
    // for(int i=0;i<nPointsNum ;i++)
    // {
    //     cout << x_p(0,i) << "," ;
    // }
    // cout << endl;
    // for(int i=0;i<nPointsNum ;i++)
    // {
    //     cout << x_p(1,i) << "," ;
    // }
    // cout << endl;


}