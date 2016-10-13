CC = g++

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS = -lGL -lglut -lGLU -lm 
endif
ifeq ($(UNAME_S),Darwin)
    LIBS = -framework OpenGL -framework GLUT
endif

SRC = tutorial_04.cpp
BIN = tutorial_04

all	:	$(BIN)

$(BIN)	:	HNode.hpp HNode.cpp $(SRC) 
	$(CC) $(SRC) HNode.cpp -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *~ *.aux *.log
