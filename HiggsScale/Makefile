HERWIG_LDFLAGS=`herwig-config --ldflags`
HERWIG_LDLIBS=`herwig-config --ldlibs`
HERWIG_CPPFLAGS=`herwig-config --cppflags`
CXX=g++
CXXFLAGS=-std=c++11 -fPIC -shared

all: HiggsMTScale.so Rivet

Rivet:
	./makeRivet.sh

HiggsMTScale.so: HiggsMTScale.cc HiggsMTScale.h
	$(CXX) $(CXXFLAGS) $(HERWIG_LDFLAGS) $(HERWIG_LDLIBS) $(HERWIG_CPPFLAGS) -o HiggsMTScale.so HiggsMTScale.cc

clean:
	rm *.o
