CC = g++
LIBS = -lGL -lglut -lGLU -lm 

SRC = tutorial_04.cpp
BIN = tutorial_04

all	:	$(BIN)

$(BIN)	:	HNode.hpp HNode.cpp $(SRC) 
	$(CC) $(SRC) HNode.cpp -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *~ *.aux *.log
