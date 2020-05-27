/*
 *	HomoEstimator.h
 *
 *	Description:
 *		Basic functions for initial homography estimation
 *
 *
 *		
 * 	History:
 *	 	Author			Date			Modify Reason		
 *		----------------------------------------------------------------
 *		Chi-Yi Tsai		2018/05/09		File Creation    
 *		
 *
 */

#ifndef Float
#ifdef DOUBLE_PRECISION
#define Float	double
#else
#define Float	float
#endif
#endif 

Float cvHomography(Float* pHomography, Float* pDst_points, Float* pSrc_points, int nPointsNum);
Float lsHomography(Float* pHomography, Float* pDst_points, Float* pSrc_points, int nPointsNum);
Float wlsHomography(Float* pHomography, Float* pDst_points, Float* pSrc_points, int nPointsNum);
Float mlHomography(Float* pHomography, Float* pDst_points, Float* pSrc_points, int nPointsNum);
Float lmvHomography(Float* pHomography, Float* pDst_points, Float* pSrc_points, int nPointsNum);
