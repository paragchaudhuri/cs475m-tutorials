CC = g++

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS = -lGL -lglut -lGLU -lm
endif
ifeq ($(UNAME_S),Darwin)
    LIBS = -framework OpenGL -framework GLUT
endif

SRC = tutorial_03.cpp
BIN = tutorial_03

all	:	$(BIN)

$(BIN)	:	$(SRC)
	$(CC) $(SRC) -g -o $(BIN) $(LIBS) 

clean	:
	rm -f $(BIN) *~ *.aux *.log
