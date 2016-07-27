CC = g++
LIBS = -lGL -lglut

SRC = tutorial_01.cpp
BIN = turotial_01

all	:	$(BIN)

$(BIN)	:	$(SRC)
	$(CC) $(SRC) -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *~
