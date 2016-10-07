CC = g++
LIBS = -lGL -lglut -lGLU -lm -lGLEW

SRC = GLShaderUtils.cpp tutorial_06.cpp
BIN = tutorial_06

all	:	$(BIN)

$(BIN)	:	$(SRC) GLShaderUtils.h
	$(CC) $(SRC) -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *.aux *.log *.out *~
