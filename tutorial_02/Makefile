CC = g++

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS = -lGL -lglut -lGLU -lm
endif
ifeq ($(UNAME_S),Darwin)
    LIBS = -framework OpenGL -framework GLUT
endif

SRC = tutorial_02.cpp
BIN = tutorial_02

all	:	$(BIN)

$(BIN)	:	$(SRC)
	$(CC) $(SRC) -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *~
