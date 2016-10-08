CC = g++
LIBS = -lGL -lglut -lGLU -lm 

SRC = tutorial_05.cpp
BIN = tutorial_05

all	:	$(BIN)

$(BIN)	:	$(SRC)
	$(CC) $(SRC) -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *~ *.aux *.log
