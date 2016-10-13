CC = g++

SRC = GLShaderUtils.cpp tutorial_06.cpp
BIN = tutorial_06

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS = -lGL -lglut -lGLU -lGLEW
endif
ifeq ($(UNAME_S),Darwin)
    LIBS = -framework OpenGL -framework GLUT
endif

all	:	$(BIN)

$(BIN)	:	$(SRC) GLShaderUtils.h
	$(CC) $(SRC) -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *.aux *.log *.out *~
