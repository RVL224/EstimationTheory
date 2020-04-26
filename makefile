main:testAP.cpp fVector.o fMatrix.o ParamEstimator.o
	g++ testAP.cpp fVector.o fMatrix.o ParamEstimator.o -o testAP.o

fVector.o:fVector.cpp
	g++ -c fVector.cpp

fMatrix.o:fMatrix.cpp
	g++ -c fMatrix.cpp

ParamEstimator.o:ParamEstimator.cpp
	g++ -c ParamEstimator.cpp

clean:
	rm -f *.o