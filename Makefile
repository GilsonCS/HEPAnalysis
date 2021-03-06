ROOTGLIBS =`root-config --glibs` -lMinuit -lTMVA
LIBS = `root-config --glibs` -L/usr/X11R6/lib -lm -ldl -lstdc++ -Wl,--no-as-needed $(ROOTGLIBS)

CXXFLAGS = -O3 -Wall --exceptions `root-config --ldflags --cflags` -I./

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

RunAnalysis: HEPAnalysis.o HEPFunctions.o HEPObjects.o _Example3.o _Example2.o _Example1.o _SgnEff.o RunAnalysis.o  
	$(CXX) -o RunAnalysis RunAnalysis.o HEPAnalysis.o HEPFunctions.o HEPObjects.o _Example3.o _Example2.o _Example1.o _SgnEff.o  $(LDFLAGS) $(LIBS)
clean:
	rm -f RunAnalysis
	rm -f *.o
	rm -f *~
	rm -f *.so
	rm -f Loader_C.d
