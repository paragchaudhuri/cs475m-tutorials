CC = g++
LIBS = -framework OpenGL -framework GLUT

SRC = tutorial_02.cpp
BIN = tutorial_02

all	:	$(BIN)

$(BIN)	:	$(SRC)
	$(CC) $(SRC) -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *~
