#include <iostream>
#include "MatchingPoints.h"
#include "HomoEstimator.h"
using namespace std;

int main()
{
    Float g_H1[9] = {0};
    // cout << g_nNumPoints << endl;

    lsHomography(g_H1,g_Ref_X,g_x1,g_nNumPoints);

    return 0;
}