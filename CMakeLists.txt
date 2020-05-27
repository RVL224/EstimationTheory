CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(EstimationTheory)

add_executable(testHomo testHomo.cpp fVector.cpp fMatrix.cpp ParamEstimator.cpp MatchingPoints.cpp HomoEstimator.cpp)