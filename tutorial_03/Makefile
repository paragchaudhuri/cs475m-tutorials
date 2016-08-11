CC = g++
LIBS = -lGL -lglut -lGLU -lm 

SRC = tutorial_03.cpp
BIN = tutorial_03

all	:	$(BIN)

$(BIN)	:	$(SRC)
	$(CC) $(SRC) -g -o $(BIN) $(LIBS) 

clean	:
	rm -f $(BIN) *~ *.aux *.log
