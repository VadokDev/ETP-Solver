CC=g++
CFLAGS=-I.
DEPS = Instance.h FcSolver.h
OBJ = Instance.o FcSolver.o main.o 

%.o: %.cpp $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

ETPSolver: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

clean:
	-rm *.o $(OBJ) ETPSolver