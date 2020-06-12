CXX = g++
CXXFLAGS = -Wall

Anahash: AnagramSolver.o Driver.cpp
	$(CXX) $(CXXFLAGS) AnagramSolver.o Driver.cpp -o Driver

AnagramSolver.o: AnagramSolver.cpp AnagramSolver.h
	$(CXX) $(CXXFLAGS) -c AnagramSolver.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./Anahash
