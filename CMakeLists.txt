CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(EstimationTheory)

add_executable(testAP testAP.cpp fVector.cpp fMatrix.cpp ParamEstimator.cpp lib/alglibinternal.cpp lib/alglibmisc.cpp lib/ap.cpp lib/linalg.cpp)
add_executable(testHomo testHomo.cpp fVector.cpp fMatrix.cpp ParamEstimator.cpp MatchingPoints.cpp HomoEstimator.cpp lib/alglibinternal.cpp lib/alglibmisc.cpp lib/ap.cpp lib/linalg.cpp)