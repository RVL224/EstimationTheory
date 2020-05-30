#include <iostream>
#include "MatchingPoints.h"
#include "HomoEstimator.h"
using namespace std;

int main()
{
    Float g_H1[9] = {0};
    Float g_H2[9] = {0};
    Float g_H3[9] = {0};
    Float g_H4[9] = {0};
    Float g_H5[9] = {0};
    // cout << g_nNumPoints << endl;
    wlsHomography(g_H1,g_Ref_X,g_x5,g_nNumPoints);
    // lsHomography(g_H2,g_Ref_X,g_x2,g_nNumPoints);
    // lsHomography(g_H3,g_Ref_X,g_x3,g_nNumPoints);
    // lsHomography(g_H4,g_Ref_X,g_x4,g_nNumPoints);
    // lsHomography(g_H5,g_Ref_X,g_x5,g_nNumPoints);

    fMatrix MatH1(g_H1,3,3);
    // fMatrix MatH2(g_H2,3,3);
    // fMatrix MatH3(g_H3,3,3);
    // fMatrix MatH4(g_H4,3,3);
    // fMatrix MatH5(g_H5,3,3);

    // cout << "H1 \n";
    // MatH1.Show();
    // cout << "H2 \n";
    // MatH2.Show();
    // cout << "H3 \n";
    // MatH3.Show();
    // cout << "H4 \n";
    // MatH4.Show();
    // cout << "H5 \n";
    // MatH5.Show();

    return 0;
}